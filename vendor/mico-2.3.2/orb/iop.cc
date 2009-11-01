/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1997-98 Kay Roemer & Arno Puder
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Send comments and/or bug reports to:
 *                 mico@informatik.uni-frankfurt.de
 */

#define MICO_CONF_IMR
#define MICO_CONF_INTERCEPT

#include <CORBA-SMALL.h>
#ifndef _WINDOWS
#include <string.h>
#endif
#include <iostream.h>
#include <mico/impl.h>
#include <mico/template_impl.h>
#include <mico/util.h>


static MICO::CodesetConvDB the_codeset_db;


/****************************** misc dtors *******************************/


MICO::GIOPConnCallback::~GIOPConnCallback ()
{
}


/***************************** GIOPInContext *****************************/


MICO::GIOPInContext::GIOPInContext (GIOPCodec *codec, CORBA::Buffer *buf,
				    CORBA::CodesetConv *csc,
				    CORBA::CodesetConv *wcsc)
{
    _buf = buf;
    _delete_buf = TRUE;

    _dc = codec->dc_proto();
    _dc->buffer (buf, FALSE);
    _dc->converter (csc, FALSE);
    _dc->wconverter (wcsc, FALSE);
}

MICO::GIOPInContext::~GIOPInContext ()
{
    if (_delete_buf)
	delete _buf;
}

void
MICO::GIOPInContext::buffer (CORBA::Buffer *b)
{
    if (_delete_buf)
	delete _buf;

    _dc->buffer (b, FALSE);
    _buf = b;
    _delete_buf = FALSE;
}

void
MICO::GIOPInContext::converters (CORBA::CodesetConv *csc,
				 CORBA::CodesetConv *wcsc)
{
    _dc->converter (csc, FALSE);
    _dc->wconverter (wcsc, FALSE);
}

CORBA::DataDecoder *
MICO::GIOPInContext::_retn ()
{
    assert (_delete_buf);
    _delete_buf = FALSE;
    return _dc->clone (_buf, TRUE,
		       _dc->converter(), FALSE,
		       _dc->wconverter(), FALSE);
}


/***************************** GIOPOutContext *****************************/


MICO::GIOPOutContext::GIOPOutContext (GIOPCodec *codec,
				      CORBA::CodesetConv *csc,
				      CORBA::CodesetConv *wcsc)
{
    _buf = new CORBA::Buffer;
    _delete_buf = TRUE;

    _ec = codec->ec_proto();
    _ec->buffer (_buf, FALSE);
    _ec->converter (csc, FALSE);
    _ec->wconverter (wcsc, FALSE);
}

MICO::GIOPOutContext::GIOPOutContext (CORBA::DataEncoder *ec)
{
    _buf = ec->buffer();
    _delete_buf = FALSE;

    _ec = ec;
}

MICO::GIOPOutContext::~GIOPOutContext ()
{
    if (_delete_buf)
	delete _buf;
}

void
MICO::GIOPOutContext::converters (CORBA::CodesetConv *csc,
				  CORBA::CodesetConv *wcsc)
{
    _ec->converter (csc, FALSE);
    _ec->wconverter (wcsc, FALSE);
}

void
MICO::GIOPOutContext::reset()
{
    _buf->reset();
}

CORBA::Buffer *
MICO::GIOPOutContext::_retn()
{
    assert (_delete_buf);
    _delete_buf = FALSE;
    return _buf;
}


/******************************* GIOPCodec *******************************/


MICO::GIOPCodec::GIOPCodec (CORBA::DataDecoder *_dc, CORBA::DataEncoder *_ec)
    : _dc_proto(_dc), _ec_proto(_ec)
{
    _giop_ver = 0x0100;

    GIOPOutContext ctx (this);
    _size_offset = put_header (ctx, CORBA::GIOP::Request);
    _headerlen = ctx.ec()->buffer()->length();
}

MICO::GIOPCodec::~GIOPCodec ()
{
    delete _ec_proto;
    delete _dc_proto;
}

CORBA::ULong
MICO::GIOPCodec::put_header (GIOPOutContext &out, CORBA::GIOP::MsgType mt)
{
    CORBA::ULong key;

    CORBA::DataEncoder *ec = out.ec();

    ec->struct_begin();
    {
	ec->arr_begin();
	{
	    // these are really chars, but must be encoded in latin1 ...
	    ec->put_chars_raw ((CORBA::Char *)"GIOP", 4);
	}
	ec->arr_end();

	ec->struct_begin();
	{
	    ec->put_octet ((CORBA::Octet)(_giop_ver >> 8));
	    ec->put_octet ((CORBA::Octet)_giop_ver);
	}
	ec->struct_end();

        if (_giop_ver == 0x0100) {
            ec->put_boolean (ec->byteorder() == CORBA::LittleEndian);
        } else {
            ec->put_octet ((ec->byteorder() == CORBA::LittleEndian)
                ? GIOP_BYTEORDER_BIT : 0);
        }
	ec->put_octet (mt);
	key = ec->buffer()->wpos();
	ec->put_ulong (0);
    }
    ec->struct_end();

    return key;
}

void
MICO::GIOPCodec::put_contextlist (GIOPOutContext &out,
				  const CORBA::IOP::ServiceContextList &ctx,
				  CORBA::Boolean codesets)
{
    CORBA::DataEncoder *ec = out.ec();

    if (CORBA::Codeset::disabled())
	codesets = FALSE;

    ec->seq_begin (ctx.length() + !!codesets);
    {
	CORBA::DataEncoder::EncapsState state;
	for (CORBA::ULong i = 0; i < ctx.length(); ++i) {
	    ec->struct_begin();
	    {
		ec->put_ulong (ctx[i].context_id);
		ec->encaps_begin (state);
		if (ctx[i].context_data.length() > 0) {
		    ec->put_octets (
			(const CORBA::Octet *)&ctx[i].context_data[0],
			ctx[i].context_data.length());
		}
		ec->encaps_end (state);
	    }
	    ec->struct_end();
	}

	if (codesets) {
	    // code set service
	    CORBA::Codeset::CodesetId csid = 0, wcsid = 0;

	    if (ec->converter())
		csid = ec->converter()->to()->id();
	    if (ec->wconverter())
		wcsid = ec->wconverter()->to()->id();

	    ec->struct_begin();
	    {
		ec->put_ulong (CORBA::IOP::CodeSets);
		ec->encaps_begin (state);
		ec->struct_begin ();
		{
		    ec->put_ulong (csid);
		    ec->put_ulong (wcsid);
		}
		ec->struct_end ();
		ec->encaps_end (state);
	    }
	    ec->struct_end();
	}
    }
    ec->seq_end ();
}

void
MICO::GIOPCodec::put_target (GIOPOutContext &out, CORBA::Object_ptr obj)
{
    CORBA::DataEncoder *ec = out.ec();

    // XXX assumes all the profiles of an IOR have the same objectkey ...
    CORBA::IORProfile *prof = obj->_ior()->profile ();
    assert (prof);

    CORBA::Long objkeylen;
    const CORBA::Octet *objkey = prof->objectkey (objkeylen);

    if (_giop_ver < 0x0102) {
	ec->seq_begin (objkeylen);
	ec->put_octets (objkey, objkeylen);
	ec->seq_end ();
    } else {
	ec->union_begin();
	{
	    CORBA::GIOP::AddressingDisposition kind = CORBA::GIOP::KeyAddr;
	    ec->put_short (kind);
	    ec->seq_begin (objkeylen);
	    ec->put_octets (objkey, objkeylen);
	    ec->seq_end ();
	}
	ec->union_end();
    }
}

CORBA::Boolean
MICO::GIOPCodec::put_args (GIOPOutContext &out, CORBA::ORBRequest *req,
			   CORBA::Boolean inp)
{
    CORBA::DataEncoder *ec = out.ec();

    ec->struct_begin ();
    {
	if (inp) {
	    if (!req->get_in_args (ec))
		return FALSE;
	} else {
	    CORBA::Boolean is_except;
	    if (!req->get_out_args (ec, is_except))
		return FALSE;
	}
    }
    ec->struct_end ();
    return TRUE;
}

void
MICO::GIOPCodec::put_size (GIOPOutContext &out, CORBA::ULong key)
{
    CORBA::DataEncoder *ec = out.ec();

    CORBA::ULong end_pos = ec->buffer()->wpos();
    ec->buffer()->wseek_beg (key);
    ec->put_ulong (end_pos - ec->buffer()->rpos() - _headerlen);
    ec->buffer()->wseek_beg (end_pos);
}

CORBA::Boolean
MICO::GIOPCodec::put_invoke_request (GIOPOutContext &out,
				     CORBA::ULong req_id,
				     CORBA::Octet response_flags,
				     CORBA::Object_ptr obj,
				     CORBA::ORBRequest *req,
				     CORBA::Principal_ptr pr)
{
    CORBA::DataEncoder *ec = out.ec();

    CORBA::ByteOrder bo = ec->byteorder();
    if (!strcmp (req->type(), "giop"))
        ec->byteorder (((GIOPRequest *)req)->input_byteorder());

    CORBA::ULong key = put_header (out, CORBA::GIOP::Request);

    ec->struct_begin ();
    {
	if (_giop_ver < 0x0102) {
	    put_contextlist (out, *req->context(), TRUE);
	    ec->put_ulong (req_id);
	    ec->put_boolean (response_flags);
	    if (_giop_ver != 0x0100)
		ec->put_octets ((CORBA::Octet*)"\0\0\0", 3);
	    put_target (out, obj);
	    ec->put_string_raw (req->op_name());
	    ec->put_principal (pr ? *pr : CORBA::Principal());
	} else {
	    ec->put_ulong (req_id);
	    ec->put_octet (response_flags);
	    ec->put_octets ((CORBA::Octet*)"\0\0\0", 3);
	    put_target (out, obj);
	    ec->put_string_raw (req->op_name());
	    put_contextlist (out, *req->context(), TRUE);
	}
    }
    ec->struct_end ();

    if (_giop_ver >= 0x0102)
	ec->buffer()->walign (ec->max_alignment());

    if (!put_args (out, req, TRUE)) {
	ec->byteorder (bo);
	return FALSE;
    }

    if (!Interceptor::ClientInterceptor::_idle()) {
	CORBA::Environment env;
	ec->buffer()->rseek_rel (_headerlen);
	if (!Interceptor::ClientInterceptor::_exec_output_message (
	    ec->buffer(), &env)) {
	    ec->byteorder (bo);
	    return FALSE;
	}
	ec->buffer()->rseek_rel (-_headerlen);
    }

    put_size (out, key);

    ec->byteorder (bo);
    return TRUE;
}

CORBA::Boolean
MICO::GIOPCodec::put_invoke_reply_offset (GIOPOutContext &out,
					  CORBA::ORBRequest *req)
{
    CORBA::DataEncoder *ec = out.ec();

    ec->buffer()->wseek_rel (_headerlen);

    ec->struct_begin ();
    {
	put_contextlist (out, *req->context());
	ec->put_ulong (0);
	ec->enumeration (0);
    }
    ec->struct_end ();

    return TRUE;
}

CORBA::Boolean
MICO::GIOPCodec::put_invoke_reply (GIOPOutContext &out,
				   CORBA::ULong req_id,
				   CORBA::GIOP::ReplyStatusType stat,
				   CORBA::Object_ptr obj,
				   CORBA::ORBRequest *req)
{
    CORBA::DataEncoder *ec = out.ec();

    CORBA::ByteOrder bo = ec->byteorder();
    if (!strcmp (req->type(), "giop"))
        ec->byteorder (((GIOPRequest *)req)->output_byteorder());

    CORBA::ULong key = put_header (out, CORBA::GIOP::Reply);

    ec->struct_begin ();
    {
	if (_giop_ver < 0x0102) {
	    put_contextlist (out, *req->context());
	    ec->put_ulong (req_id);
	    ec->enumeration ((CORBA::ULong)stat);
	} else {
	    ec->put_ulong (req_id);
	    ec->enumeration ((CORBA::ULong)stat);
	    put_contextlist (out, *req->context());
	}
    }
    ec->struct_end ();

    switch (stat) {
    case CORBA::GIOP::NO_EXCEPTION:
    case CORBA::GIOP::USER_EXCEPTION:
    case CORBA::GIOP::SYSTEM_EXCEPTION:
	if (_giop_ver >= 0x0102) {
	    ec->buffer()->walign (ec->max_alignment());
	}
	if (!put_args (out, req, FALSE)) {
	    ec->byteorder (bo);
	    return FALSE;
	}
	break;

    case CORBA::GIOP::LOCATION_FORWARD:
    case CORBA::GIOP::LOCATION_FORWARD_PERM:
	ec->put_ior (*obj->_ior());
	break;

    default:
	assert (0);
	break;
    }

    if (!Interceptor::ServerInterceptor::_idle()) {
	CORBA::Environment env;
	ec->buffer()->rseek_rel (_headerlen);
	if (!Interceptor::ServerInterceptor::_exec_output_message (
	    ec->buffer(), &env)) {
	    ec->byteorder (bo);
	    return FALSE;
	}
	ec->buffer()->rseek_rel (-_headerlen);
    }

    put_size (out, key);

    ec->byteorder (bo);
    return TRUE;
}

CORBA::Boolean
MICO::GIOPCodec::put_cancel_request (GIOPOutContext &out, CORBA::ULong req_id)
{
    CORBA::DataEncoder *ec = out.ec();

    CORBA::ULong key = put_header (out, CORBA::GIOP::CancelRequest);

    ec->struct_begin();
    {
	ec->put_ulong (req_id);
    }
    ec->struct_end();

    put_size (out, key);
    return TRUE;
}

CORBA::Boolean
MICO::GIOPCodec::put_locate_request (GIOPOutContext &out,
				     CORBA::ULong req_id,
				     CORBA::Object_ptr obj)
{
    CORBA::DataEncoder *ec = out.ec();

    CORBA::ULong key = put_header (out, CORBA::GIOP::LocateRequest);

    ec->struct_begin();
    {
	ec->put_ulong (req_id);
	put_target (out, obj);
    }
    ec->struct_end();

    put_size (out, key);
    return TRUE;
}

CORBA::Boolean
MICO::GIOPCodec::put_locate_reply (GIOPOutContext &out,
				   CORBA::ULong req_id,
				   CORBA::GIOP::LocateStatusType stat,
				   CORBA::Object_ptr obj)
{
    CORBA::DataEncoder *ec = out.ec();

    CORBA::ULong key = put_header (out, CORBA::GIOP::LocateReply);

    ec->struct_begin();
    {
	ec->put_ulong (req_id);
	ec->enumeration ((CORBA::ULong)stat);
    }
    ec->struct_end();

    switch (stat) {
    case CORBA::GIOP::OBJECT_FORWARD:
    case CORBA::GIOP::OBJECT_FORWARD_PERM:
	ec->put_ior (*obj->_ior());
	break;
    }
    put_size (out, key);
    return TRUE;
}

CORBA::Boolean
MICO::GIOPCodec::put_bind_request (GIOPOutContext &out, CORBA::ULong req_id,
				   const char *repoid,
				   const CORBA::ORB::ObjectTag &oid)
{
    /*
     * mapped to an invocation:
     *   GIOP::LocateStatusType _bind (in string repoid,
     *				       in sequence<octet> oid,
     *				       out object obj);
     */
    CORBA::DataEncoder *ec = out.ec();

    CORBA::ULong key = put_header (out, CORBA::GIOP::Request);

    ec->struct_begin ();
    {
	CORBA::Object_var obj = new CORBA::Object (new CORBA::IOR);
	obj->_ior()->add_profile (new GIOPSimpleProf);

	if (_giop_ver < 0x0102) {
	    put_contextlist (out, CORBA::IOP::ServiceContextList());
	    ec->put_ulong (req_id);
	    ec->put_boolean (TRUE);
	    if (_giop_ver != 0x0100) {
		ec->put_octets ((CORBA::Octet*)"\0\0\0", 3);
	    }
	    put_target (out, obj);
	    ec->put_string ("_bind");
	    ec->put_principal (CORBA::Principal());
	} else {
	    ec->put_ulong (req_id);
	    ec->put_octet (1);
	    ec->put_octets ((CORBA::Octet*)"\0\0\0", 3);
	    put_target (out, obj);
	    ec->put_string ("_bind");
	    put_contextlist (out, CORBA::IOP::ServiceContextList());
	}
    }
    ec->struct_end ();

    if (_giop_ver >= 0x0102)
	ec->buffer()->walign (ec->max_alignment());

    ec->struct_begin ();
    {
	ec->put_string (repoid);
	ec->seq_begin (oid.length());
	if (oid.length() > 0)
	    ec->put_octets ((const CORBA::Octet *)&oid[0], oid.length());
	ec->seq_end ();
    }
    ec->struct_end ();

    if (!Interceptor::ClientInterceptor::_idle()) {
	CORBA::Environment env;
	ec->buffer()->rseek_rel (_headerlen);
	if (!Interceptor::ClientInterceptor::_exec_output_message (
	    ec->buffer(), &env)) {
	    return FALSE;
	}
	ec->buffer()->rseek_rel (-_headerlen);
    }

    put_size (out, key);
    return TRUE;
}

CORBA::Boolean
MICO::GIOPCodec::put_bind_reply (GIOPOutContext &out,
				 CORBA::ULong req_id,
				 CORBA::GIOP::LocateStatusType stat,
				 CORBA::Object_ptr obj)
{
    /*
     * mapped to an invocation:
     *   GIOP::LocateStatusType _bind (in string repoid,
     *				       in sequence<octet> oid,
     *				       out object obj);
     */
    CORBA::DataEncoder *ec = out.ec();

    CORBA::ULong key = put_header (out, CORBA::GIOP::Reply);

    ec->struct_begin ();
    {
	if (_giop_ver < 0x0102) {
	    put_contextlist (out, CORBA::IOP::ServiceContextList());
	    ec->put_ulong (req_id);
	    ec->enumeration ((CORBA::ULong)CORBA::GIOP::NO_EXCEPTION);
	} else {
	    ec->put_ulong (req_id);
	    ec->enumeration ((CORBA::ULong)CORBA::GIOP::NO_EXCEPTION);
	    put_contextlist (out, CORBA::IOP::ServiceContextList());
	}
    }
    ec->struct_end ();

    if (_giop_ver >= 0x0102)
	ec->buffer()->walign (ec->max_alignment());

    ec->struct_begin ();
    {
	ec->enumeration ((CORBA::ULong)stat);
	ec->put_ior (stat == CORBA::GIOP::OBJECT_HERE
		     ? *obj->_ior() : CORBA::IOR());
    }
    ec->struct_end ();

    if (!Interceptor::ServerInterceptor::_idle()) {
	CORBA::Environment env;
	ec->buffer()->rseek_rel (_headerlen);
	if (!Interceptor::ServerInterceptor::_exec_output_message (
	    ec->buffer(), &env)) {
	    return FALSE;
	}
	ec->buffer()->rseek_rel (-_headerlen);
    }

    put_size (out, key);
    return TRUE;
}

CORBA::Boolean
MICO::GIOPCodec::put_close_msg (GIOPOutContext &out)
{
    CORBA::DataEncoder *ec = out.ec();

    CORBA::ULong key = put_header (out, CORBA::GIOP::CloseConnection);
    put_size (out, key);
    return TRUE;
}

CORBA::Boolean
MICO::GIOPCodec::put_error_msg (GIOPOutContext &out)
{
    CORBA::DataEncoder *ec = out.ec();

    CORBA::ULong key = put_header (out, CORBA::GIOP::MessageError);
    put_size (out, key);
    return TRUE;
}

#define check(exp) if (!(exp)) return FALSE

CORBA::Boolean
MICO::GIOPCodec::get_header (GIOPInContext &in, CORBA::GIOP::MsgType &mt,
			     CORBA::ULong &sz, CORBA::Octet &flags)
{
    CORBA::DataDecoder *dc = in.dc();

    CORBA::Boolean b;
    CORBA::Octet o;
    CORBA::Char c;

    check (dc->struct_begin());
    {
	check (dc->arr_begin());
	{
	    CORBA::Char magic[5];
	    magic[4] = 0;

	    // these are really chars, but must be encoded in latin1 ...
	    check (dc->get_chars_raw (magic, 4) &&
		   !strcmp ((char*)magic, "GIOP"));
	}
	check (dc->arr_end());

	check (dc->struct_begin());
	{
	    CORBA::Octet min, maj;
	    CORBA::UShort ver;

	    check (dc->get_octet (maj));
	    check (dc->get_octet (min));

	    ver = ((maj << 8) | min);
	    check (ver <= 0x0102);
	    _giop_ver = ver;
	}
	check (dc->struct_end());

        if (_giop_ver == 0x0100) {
            check (dc->get_boolean (b));
            dc->byteorder (b ? CORBA::LittleEndian
                           : CORBA::BigEndian);
            flags = b ? 1 : 0;
        } else {
            check (dc->get_octet (flags));
            dc->byteorder ((flags & GIOP_BYTEORDER_BIT) ? CORBA::LittleEndian
                           : CORBA::BigEndian);
        }
	check (dc->get_octet (o));
	mt = (CORBA::GIOP::MsgType)o;
	check (dc->get_ulong (sz));
    }
    check (dc->struct_end());
    return TRUE;
}

CORBA::Boolean
MICO::GIOPCodec::get_contextlist (GIOPInContext &in,
				  CORBA::IOP::ServiceContextList &ctx,
				  CORBA::Boolean codesets)
{
    CORBA::DataDecoder *dc = in.dc();

    CORBA::Codeset::CodesetId csid = 0, wcsid = 0;

    CORBA::ULong len;
    CORBA::DataDecoder::EncapsState state;
    check (dc->seq_begin (len));
    ctx.length (len);
    {
	CORBA::ULong context_id;
	for (CORBA::ULong i = 0; i < ctx.length(); ) {
	    check (dc->struct_begin());
	    {
		check (dc->get_ulong (context_id));
		check (dc->encaps_begin (state, len));
		if (context_id == CORBA::IOP::CodeSets) {
		    // code set service ...
		    ctx.length (ctx.length()-1);
		    check (dc->struct_begin());
		    {
			check (dc->get_ulong (csid));
			check (dc->get_ulong (wcsid));
		    }
		    check (dc->struct_end());
		} else {
		    // other service ...
		    ctx[i].context_id = context_id;
		    ctx[i].context_data.length (len);
		    if (len > 0) {
			check (dc->get_octets (
			    &ctx[i].context_data[0],
			    ctx[i].context_data.length()));
		    }
		    ++i;
		}
		check (dc->encaps_end (state));
	    }
	    check (dc->struct_end());
	}
    }
    check (dc->seq_end ());

    // set up code sets ...
    if (codesets && !CORBA::Codeset::disabled()) {
	CORBA::CodesetConv *wconv = 0, *conv = 0;

	if (csid)
	    conv = the_codeset_db.find (csid, CORBA::Codeset::special_cs(
		CORBA::Codeset::NativeCS)->id());

	if (wcsid)
	    wconv = the_codeset_db.find (wcsid, CORBA::Codeset::special_cs(
		CORBA::Codeset::NativeWCS)->id());

	in.converters (conv, wconv);
    }
    return TRUE;
}

CORBA::Boolean
MICO::GIOPCodec::get_target (GIOPInContext &in, CORBA::Object_ptr obj)
{
    CORBA::DataDecoder *dc = in.dc();

    if (_giop_ver < 0x0102) {
	CORBA::ULong objkeylen;
	CORBA::Octet *objkey;

	obj->_ior()->add_profile (new GIOPSimpleProf);

	check (dc->seq_begin (objkeylen));
        check (dc->buffer()->length() >= objkeylen);
	objkey = dc->buffer()->data();
	dc->buffer()->rseek_rel (objkeylen);
	check (dc->seq_end ());

	obj->_ior()->objectkey (objkey, objkeylen);
    } else {
	check (dc->union_begin());
	{
	    CORBA::GIOP::AddressingDisposition kind;
	    check (dc->get_short (kind));
	    if (kind == CORBA::GIOP::KeyAddr) {
		obj->_ior()->add_profile (new GIOPSimpleProf);

		CORBA::ULong objkeylen;
		CORBA::Octet *objkey;

		check (dc->seq_begin (objkeylen));
                check (dc->buffer()->length() >= objkeylen);
		objkey = dc->buffer()->data();
		dc->buffer()->rseek_rel (objkeylen);
		check (dc->seq_end ());

		obj->_ior()->objectkey (objkey, objkeylen);
	    } else if (kind == CORBA::GIOP::ProfileAddr) {
		CORBA::IORProfile *prof = CORBA::IORProfile::decode (*dc);
		check (prof);
		obj->_ior()->add_profile (prof);
	    } else if (kind == CORBA::GIOP::ReferenceAddr) {
		check (dc->struct_begin());
		{
		    CORBA::ULong index;
		    check (dc->get_ulong (index));
		    check (dc->get_ior (*obj->_ior()));
		}
		check (dc->struct_end());
	    } else {
		return FALSE;
	    }
	}
	check (dc->union_end());
    }
    return TRUE;
}

CORBA::Boolean
MICO::GIOPCodec::check_header (GIOPInContext &in, CORBA::GIOP::MsgType &mt,
			       CORBA::ULong &sz, CORBA::Octet &flags)
{
    CORBA::ULong pos = in.dc()->buffer()->rpos ();
    CORBA::Boolean ret = get_header (in, mt, sz, flags);
    in.dc()->buffer()->rseek_beg (pos);
    return ret;
}

CORBA::Boolean
MICO::GIOPCodec::get_invoke_request (GIOPInContext &in,
				     CORBA::ULong &req_id,
				     CORBA::Octet &response_flags,
				     CORBA::Object_ptr obj,
				     CORBA::ORBRequest * &req,
				     CORBA::Principal_ptr pr)
{
    CORBA::DataDecoder *dc = in.dc();

    if (!Interceptor::ServerInterceptor::_idle()) {
	CORBA::Environment env;
	if (!Interceptor::ServerInterceptor::_exec_input_message (
	    dc->buffer(), &env)) {
	    return FALSE;
	}
    }

    CORBA::String_var opname;
    CORBA::IOP::ServiceContextList ctx;

    check (dc->struct_begin ());
    {
	if (_giop_ver < 0x0102) {
	    check (get_contextlist (in, ctx, TRUE));
	    check (dc->get_ulong (req_id));
	    check (dc->get_boolean (response_flags));
	    if (_giop_ver != 0x0100) {
		CORBA::Octet o[3];
		check (dc->get_octets (o, 3));
	    }
	    check (get_target (in, obj));
	    check (dc->get_string_raw (opname.out()));
	    check (dc->get_principal (*pr));
	} else {
	    check (dc->get_ulong (req_id));
	    check (dc->get_octet (response_flags));
	    CORBA::Octet o[3];
	    check (dc->get_octets (o, 3));
	    check (get_target (in, obj));
	    check (dc->get_string_raw (opname.out()));
	    check (get_contextlist (in, ctx, TRUE));
	}
    }
    check (dc->struct_end ());

    if (_giop_ver >= 0x0102)
	// if there are no arguments aligning might fail ...
	dc->buffer()->ralign (dc->max_alignment());

    req = new GIOPRequest (opname, in._retn(), this);
    req->context (&ctx);

    return TRUE;
}

CORBA::Boolean
MICO::GIOPCodec::get_invoke_reply1 (GIOPInContext &in,
				    CORBA::ULong &req_id,
				    CORBA::GIOP::ReplyStatusType &stat,
				    CORBA::IOP::ServiceContextList &ctx)
{
    CORBA::DataDecoder *dc = in.dc();

    if (!Interceptor::ClientInterceptor::_idle()) {
	CORBA::Environment env;
	if (!Interceptor::ClientInterceptor::_exec_input_message (
	    dc->buffer(), &env)) {
	    return FALSE;
	}
    }

    CORBA::ULong k;

    check (dc->struct_begin ());
    {
	if (_giop_ver < 0x0102) {
	    check (get_contextlist (in, ctx));
	    check (dc->get_ulong (req_id));
	    check (dc->enumeration (k));
	    stat = (CORBA::GIOP::ReplyStatusType)k;
	} else {
	    check (dc->get_ulong (req_id));
	    check (dc->enumeration (k));
	    stat = (CORBA::GIOP::ReplyStatusType)k;
	    check (get_contextlist (in, ctx));
	}
    }
    check (dc->struct_end ());

    if (_giop_ver >= 0x0102)
	// if there are no arguments aligning might fail ...
	dc->buffer()->ralign (dc->max_alignment());

    return TRUE;
}

CORBA::Boolean
MICO::GIOPCodec::get_invoke_reply2 (GIOPInContext &in,
				    CORBA::ULong req_id,
				    CORBA::GIOP::ReplyStatusType stat,
				    CORBA::Object_ptr &obj,
				    CORBA::ORBRequest *req,
				    CORBA::IOP::ServiceContextList &ctx)
{
    CORBA::DataDecoder *dc = in.dc();

    obj = CORBA::Object::_nil();

    switch (stat) {
    case CORBA::GIOP::NO_EXCEPTION:
	if (req) {
	    // may be NULL for a bind()
	    req->context (&ctx);
	    return req->set_out_args (dc, FALSE);
	}
	break;

    case CORBA::GIOP::USER_EXCEPTION:
    case CORBA::GIOP::SYSTEM_EXCEPTION:
	if (req) {
	    // may be NULL for a bind()
	    req->context (&ctx);
	    return req->set_out_args (dc, TRUE);
	}
	break;

    case CORBA::GIOP::LOCATION_FORWARD:
    case CORBA::GIOP::LOCATION_FORWARD_PERM: {
        CORBA::IOR *ior = new CORBA::IOR ("", CORBA::IOR::IORProfileVec());
        check (dc->get_ior (*ior));
	CORBA::ORB_var orb = CORBA::ORB_instance ("mico-local-orb");
        obj = orb->ior_to_object (ior);
	break;
    }
    case CORBA::GIOP::NEEDS_ADDRESSING_MODE: {
	CORBA::GIOP::AddressingDisposition kind;
	check (dc->get_short (kind));
	// XXX
	assert (0);
	break;
    }
    default:
	assert (0);
	break;
    }
    return TRUE;
}

CORBA::Boolean
MICO::GIOPCodec::get_cancel_request (GIOPInContext &in, CORBA::ULong &req_id)
{
    CORBA::DataDecoder *dc = in.dc();

    check (dc->struct_begin());
    {
	check (dc->get_ulong (req_id));
    }
    check (dc->struct_end());
    return TRUE;
}

CORBA::Boolean
MICO::GIOPCodec::get_locate_request (GIOPInContext &in,
				     CORBA::ULong &req_id,
				     CORBA::Object_ptr obj)
{
    CORBA::DataDecoder *dc = in.dc();

    check (dc->struct_begin());
    {
	check (dc->get_ulong (req_id));
	check (get_target (in, obj));
    }
    check (dc->struct_end());
    return TRUE;
}

CORBA::Boolean
MICO::GIOPCodec::get_locate_reply (GIOPInContext &in,
				   CORBA::ULong &req_id,
				   CORBA::GIOP::LocateStatusType &stat,
				   CORBA::Object_ptr &obj)
{
    CORBA::DataDecoder *dc = in.dc();

    CORBA::ULong k;

    check (dc->struct_begin());
    {
	check (dc->get_ulong (req_id));
	check (dc->enumeration (k));
	stat = (CORBA::GIOP::LocateStatusType)k;
    }
    check (dc->struct_end());

    switch (stat) {
    case CORBA::GIOP::OBJECT_FORWARD:
    case CORBA::GIOP::OBJECT_FORWARD_PERM: {
	CORBA::IOR *ior = new CORBA::IOR;
	check (dc->get_ior (*ior));
	CORBA::ORB_var orb = CORBA::ORB_instance ("mico-local-orb");
	obj = orb->ior_to_object (ior);
	break;
    }
    case CORBA::GIOP::LOC_SYSTEM_EXCEPTION: {
	CORBA::Exception *ex = CORBA::Exception::_decode (*dc);
	check (ex);
	// XXX
	assert (0);
	break;
    }
    case CORBA::GIOP::LOC_NEEDS_ADDRESSING_MODE: {
	CORBA::GIOP::AddressingDisposition kind;
	check (dc->get_short (kind));
	// XXX
	assert (0);
	break;
    }
    default:
	obj = CORBA::Object::_nil();
	break;
    }
    return TRUE;
}

CORBA::Boolean
MICO::GIOPCodec::get_bind_request (GIOPInContext &in, char * &repoid,
				   CORBA::ORB::ObjectTag &oid)
{
    /*
     * mapped to an invocation:
     *   GIOP::LocateStatusType _bind (in string repoid,
     *				       in sequence<octet> oid,
     *				       out object obj);
     * at this point only the invoke request in args are left in the
     * buffer...
     */
    CORBA::DataDecoder *dc = in.dc();

    check (dc->struct_begin ());
    {
	check (dc->get_string (repoid));
	CORBA::ULong l;
	check (dc->seq_begin (l));
	oid.length (l);
	if (l > 0)
	    check (dc->get_octets (&oid[0], oid.length()));
	check (dc->seq_end ());
    }
    check (dc->struct_end ());

    return TRUE;
}

CORBA::Boolean
MICO::GIOPCodec::get_bind_reply (GIOPInContext &in,
				 CORBA::GIOP::LocateStatusType &stat,
				 CORBA::Object_ptr &obj)
{
    /*
     * mapped to an invocation:
     *   GIOP::LocateStatusType _bind (in string repoid,
     *				       in sequence<octet> oid,
     *				       out object obj);
     * at this point only the invoke reply out args/result are left in the
     * buffer...
     */
    CORBA::DataDecoder *dc = in.dc();

    CORBA::ULong k;
    CORBA::IOR ior;

    obj = CORBA::Object::_nil();

    check (dc->struct_begin ());
    {
	check (dc->enumeration (k));
	stat = (CORBA::GIOP::LocateStatusType)k;
	check (dc->get_ior (ior));
    }
    check (dc->struct_end ());

    CORBA::ORB_var orb = CORBA::ORB_instance ("mico-local-orb");
    obj = orb->ior_to_object (new CORBA::IOR (ior));
    return TRUE;
}

CORBA::Boolean
MICO::GIOPCodec::get_close_msg (GIOPInContext &in)
{
    CORBA::DataDecoder *dc = in.dc();
    return TRUE;
}

CORBA::Boolean
MICO::GIOPCodec::get_error_msg (GIOPInContext &in)
{
    CORBA::DataDecoder *dc = in.dc();
    return TRUE;
}

CORBA::Boolean
MICO::GIOPCodec::get_fragment_header (GIOPInContext &in, CORBA::ULong &req_id,
				      CORBA::Boolean &has_id)
{
    CORBA::DataDecoder *dc = in.dc();

    if (_giop_ver < 0x0102) {
	has_id = FALSE;
	return TRUE;
    }

    check (dc->get_ulong (req_id));
    has_id = TRUE;
    return TRUE;
}

#undef check


/****************************** GIOPRequest *****************************/


MICO::GIOPRequest::GIOPRequest (const char *op, CORBA::DataDecoder *indata,
				GIOPCodec *c)
{
    _codec = GIOPCodec::_duplicate (c);

    CORBA::CodesetConv *conv = indata->converter();
    CORBA::CodesetConv *wconv = indata->wconverter();
    CORBA::CodesetConv *rconv = 0;
    CORBA::CodesetConv *rwconv = 0;

    if (conv) {
	rconv = the_codeset_db.reverse (conv);
    }
    if (wconv) {
	rwconv = the_codeset_db.reverse (wconv);
    }
    _opname = op;
    _idc = indata;
    _istart = _idc->buffer()->rpos();

    _oec = _idc->encoder (&_obuf, FALSE, rconv, FALSE, rwconv,FALSE);
    _ostart = 0;
#if 0
    _odc = _idc->clone (&_obuf, FALSE, conv, FALSE, wconv, FALSE);
#endif
    _is_except = FALSE;
}

MICO::GIOPRequest::~GIOPRequest ()
{
    CORBA::release (_codec);
    delete _idc;
    delete _oec;
#if 0
    delete _odc;
#endif
}

const char *
MICO::GIOPRequest::op_name()
{
    return _opname.c_str();
}

CORBA::Boolean
MICO::GIOPRequest::get_in_args (CORBA::NVList_ptr iparams,
				CORBA::Context_ptr &ctx)
{
    _idc->buffer()->rseek_beg (_istart);

    if (iparams->count() == 0 && _idc->buffer()->length() == 0)
	return TRUE;

    CORBA::Any *a;
    CORBA::TypeCode_var tc;
    CORBA::Boolean ret;

    // share one state for all arguments
    CORBA::DataDecoder::ValueState vstate;
    _idc->valuestate (&vstate, FALSE);

    for (CORBA::ULong i = 0; i < iparams->count(); ++i) {
	if (iparams->item(i)->flags() & (CORBA::ARG_IN|CORBA::ARG_INOUT)) {
	    a = iparams->item(i)->value();
	    tc = a->type();
	    ret = a->demarshal (tc, *_idc);
	    if (!ret) {
		_idc->valuestate (0);
                return FALSE;
	    }
	}
    }
    if (_idc->buffer()->length() > 0) {
	ctx = new CORBA::Context ("");
	if (!_idc->get_context (*ctx)) {
	    CORBA::release (ctx);
	    ctx = CORBA::Context::_nil();
	}
    }
    _idc->valuestate (0);
    return TRUE;
}

CORBA::Boolean
MICO::GIOPRequest::get_in_args (StaticAnyList *iparams,
				CORBA::Context_ptr &ctx)
{
    _idc->buffer()->rseek_beg (_istart);

    if (iparams->size() == 0 && _idc->buffer()->length() == 0)
	return TRUE;

    CORBA::Boolean ret;

    // share one state for all arguments
    CORBA::DataDecoder::ValueState vstate;
    _idc->valuestate (&vstate, FALSE);

    for (mico_vec_size_type i = 0; i < iparams->size(); ++i) {
	if ((*iparams)[i]->flags() & (CORBA::ARG_IN|CORBA::ARG_INOUT)) {
	    ret = (*iparams)[i]->demarshal (*_idc);
            if (!ret) {
		_idc->valuestate (0);
                return FALSE;
	    }
	}
    }
    if (_idc->buffer()->length() > 0) {
	ctx = new CORBA::Context ("");
	if (!_idc->get_context (*ctx)) {
	    CORBA::release (ctx);
	    ctx = CORBA::Context::_nil();
	}
    }
    _idc->valuestate (0);
    return TRUE;
}

CORBA::Boolean
MICO::GIOPRequest::get_in_args (CORBA::DataEncoder *ec)
{
    // XXX alignment, byteorder, differing codecs ???
    assert (!strcmp (ec->type(), _idc->type()));
    assert (ec->byteorder() == _idc->byteorder());

    _idc->buffer()->rseek_beg (_istart);
    ec->put_octets (_idc->buffer()->data(), _idc->buffer()->length());
    return TRUE;
}

CORBA::Boolean
MICO::GIOPRequest::get_out_args (CORBA::Any *res, CORBA::NVList_ptr oparams,
				 CORBA::Exception *&except)
{
#if 0
    except = 0;
    _odc->buffer()->rseek_beg (_ostart);

    if (!_is_except && !res && oparams->count() == 0 &&
	_odc->buffer()->length() == 0)
	return TRUE;

    // share one state for all arguments
    CORBA::DataDecoder::ValueState vstate;
    _odc->valuestate (&vstate, FALSE);

    if (_is_except) {
	except = CORBA::Exception::_decode (*_odc);
	assert (except);
    } else {
	CORBA::TypeCode_var tc;
	CORBA::Boolean ret;
	CORBA::Any *a;

	if (res) {
	    tc = res->type();
	    if (!tc->equal (CORBA::_tc_void)) {
		ret = res->demarshal (tc, *_odc);
                if (!ret) {
		    _odc->valuestate (0);
                    return FALSE;
		}
	    }
	}
	for (CORBA::ULong i = 0; i < oparams->count(); ++i) {
	    if (oparams->item(i)->flags() & (CORBA::ARG_OUT|CORBA::ARG_INOUT)){
		a = oparams->item(i)->value();
		tc = a->type();
		ret = a->demarshal (tc, *_odc);
                if (!ret) {
		    _odc->valuestate (0);
                    return FALSE;
		}
	    }
	}
    }
    _odc->valuestate (0);
#else
    assert (0);
#endif
    return TRUE;
}

CORBA::Boolean
MICO::GIOPRequest::get_out_args (CORBA::StaticAny *res,
				 StaticAnyList *oparams,
				 CORBA::Exception *&except)
{
#if 0
    except = 0;
    _odc->buffer()->rseek_beg (_ostart);

    if (!_is_except && !res && oparams->size() == 0 &&
	_odc->buffer()->length() == 0)
	return TRUE;

    // share one state for all arguments
    CORBA::DataDecoder::ValueState vstate;
    _odc->valuestate (&vstate, FALSE);

    if (_is_except) {
	except = CORBA::Exception::_decode (*_odc);
	assert (except);
    } else {
	CORBA::Boolean ret;
	if (res) {
	    ret = res->demarshal (*_odc);
            if (!ret) {
		_odc->valuestate (0);
                return FALSE;
	    }
	}
	for (mico_vec_size_type i = 0; i < oparams->size(); ++i) {
	    if ((*oparams)[i]->flags() & (CORBA::ARG_OUT|CORBA::ARG_INOUT)){
		ret = (*oparams)[i]->demarshal (*_odc);
		if (!ret) {
		    _odc->valuestate (0);
                    return FALSE;
		}
	    }
	}
    }
    _odc->valuestate (0);
#else
    assert (0);
#endif
    return TRUE;
}

CORBA::Boolean
MICO::GIOPRequest::get_out_args (CORBA::DataEncoder *ec, CORBA::Boolean &is_ex)
{
    // XXX alignment, byteorder, differing codecs ???
    assert (!strcmp (ec->type(), _oec->type()));
    assert (ec->byteorder() == _oec->byteorder());

    _oec->buffer()->rseek_beg (_ostart);
    ec->put_octets (_oec->buffer()->data(), _oec->buffer()->length());
    is_ex = _is_except;

    return TRUE;
}

CORBA::Boolean
MICO::GIOPRequest::set_out_args (CORBA::Any *res, CORBA::NVList_ptr oparams)
{
    _is_except = FALSE;
    _oec->buffer()->reset();

    if (!res && oparams->count() == 0)
	return TRUE;

    if (_codec->version() < 0x0102) {
	// this is to get alignment right
	GIOPOutContext out (_oec);
	_codec->put_invoke_reply_offset (out, this);
	_ostart = _oec->buffer()->wpos();
    }
    _oec->buffer()->rseek_beg (_ostart);

    // share one state for all arguments
    CORBA::DataEncoder::ValueState vstate;
    _oec->valuestate (&vstate, FALSE);

    if (res) {
	if (!res->marshal (*_oec))
	    return FALSE;
    }
    for (CORBA::ULong i = 0; i < oparams->count(); ++i) {
	if (oparams->item(i)->flags() & (CORBA::ARG_OUT|CORBA::ARG_INOUT)) {
	    if (!oparams->item(i)->value()->marshal (*_oec))
		return FALSE;
	}
    }
    _oec->valuestate (0);
    return TRUE;
}

CORBA::Boolean
MICO::GIOPRequest::set_out_args (CORBA::StaticAny *res,
				 StaticAnyList *oparams)
{
    _is_except = FALSE;
    _oec->buffer()->reset();

    if (!res && oparams->size() == 0)
	return TRUE;

    if (_codec->version() < 0x0102) {
	// this is to get alignment right
	GIOPOutContext out (_oec);
	_codec->put_invoke_reply_offset (out, this);
	_ostart = _oec->buffer()->wpos();
    }
    _oec->buffer()->rseek_beg (_ostart);

    // share one state for all arguments
    CORBA::DataEncoder::ValueState vstate;
    _oec->valuestate (&vstate, FALSE);

    if (res) {
	if (!res->marshal (*_oec))
	    return FALSE;
    }
    for (mico_vec_size_type i = 0; i < oparams->size(); ++i) {
	if ((*oparams)[i]->flags() & (CORBA::ARG_OUT|CORBA::ARG_INOUT)) {
	    if (!(*oparams)[i]->marshal (*_oec))
		return FALSE;
	}
    }
    _oec->valuestate (0);
    return TRUE;
}

void
MICO::GIOPRequest::set_out_args (CORBA::Exception *except)
{
    _oec->buffer()->reset();

    if (_codec->version() < 0x0102) {
	// this is to get alignment right
	GIOPOutContext out (_oec);
	_codec->put_invoke_reply_offset (out, this);
	_ostart = _oec->buffer()->wpos();
    }
    _oec->buffer()->rseek_beg (_ostart);

    // share one state for all arguments
    CORBA::DataEncoder::ValueState vstate;
    _oec->valuestate (&vstate, FALSE);

    _is_except = TRUE;
    except->_encode (*_oec);

    _oec->valuestate (0);
}

CORBA::Boolean
MICO::GIOPRequest::set_out_args (CORBA::DataDecoder *dc, CORBA::Boolean is_ex)
{
    _oec->buffer()->reset();

    if (_codec->version() < 0x0102) {
	// this is to get alignment right
	GIOPOutContext out (_oec);
	_codec->put_invoke_reply_offset (out, this);
	_ostart = _oec->buffer()->wpos();
    }
    _oec->buffer()->rseek_beg (_ostart);

    // XXX alignment, byteorder, differing codecs ???
    assert (!strcmp (dc->type(), _oec->type()));
    assert (dc->byteorder() == _oec->byteorder());

    _oec->put_octets (dc->buffer()->data(), dc->buffer()->length());
    dc->buffer()->rseek_rel (dc->buffer()->length());
    _is_except = is_ex;
    return TRUE;
}

CORBA::Boolean
MICO::GIOPRequest::copy_out_args (CORBA::ORBRequest *req)
{
    if (this == req)
	return TRUE;

    // copy service context list
    copy_svc (req);

    assert (_oec);

    _oec->buffer()->reset();

    if (_codec->version() < 0x0102) {
	// this is to get alignment right
	GIOPOutContext out (_oec);
	_codec->put_invoke_reply_offset (out, this);
	_ostart = _oec->buffer()->wpos();
    }
    _oec->buffer()->rseek_beg (_ostart);

    req->get_out_args (_oec, _is_except);
    return TRUE;
}

CORBA::Boolean
MICO::GIOPRequest::copy_in_args (CORBA::ORBRequest *req)
{
    assert (0);
    return FALSE;
}

const char *
MICO::GIOPRequest::type ()
{
    return "giop";
}

CORBA::ByteOrder
MICO::GIOPRequest::input_byteorder ()
{
    return _idc->byteorder();
}

CORBA::ByteOrder
MICO::GIOPRequest::output_byteorder ()
{
    return _oec->byteorder();
}

CORBA::Codeset::CodesetId
MICO::GIOPRequest::csid()
{
    return _idc->converter() ? _idc->converter()->from()->id() : 0;
}
    
CORBA::Codeset::CodesetId
MICO::GIOPRequest::wcsid ()
{
    return _idc->wconverter() ? _idc->wconverter()->from()->id() : 0;
}


/***************************** GIOPSimpleProf ****************************/


MICO::GIOPSimpleProf::GIOPSimpleProf ()
    : _objkey (0), _length (0)
{
}

MICO::GIOPSimpleProf::GIOPSimpleProf (const GIOPSimpleProf &p)
    : _objkey (0), _length (0)
{
    if (p._objkey) {
	_objkey = new CORBA::Octet[_length = p._length];
	memcpy (_objkey, p._objkey, p._length);
    }
}

MICO::GIOPSimpleProf::~GIOPSimpleProf ()
{
    if (_objkey)
	delete[] _objkey;
}

MICO::GIOPSimpleProf &
MICO::GIOPSimpleProf::operator= (const GIOPSimpleProf &p)
{
    if (this != &p)
	objectkey (p._objkey, p._length);
    return *this;
}

void
MICO::GIOPSimpleProf::encode (CORBA::DataEncoder &) const
{
    assert (0);
}

const CORBA::Address *
MICO::GIOPSimpleProf::addr () const
{
    assert (0);
    return 0;
}

CORBA::IORProfile::ProfileId
MICO::GIOPSimpleProf::id () const
{
    return 10000;
}

CORBA::IORProfile::ProfileId
MICO::GIOPSimpleProf::encode_id () const
{
    return 10000;
}

void
MICO::GIOPSimpleProf::objectkey (CORBA::Octet *o, CORBA::Long l)
{
    if (_objkey)
	delete[] _objkey;
    _objkey = new CORBA::Octet[_length = l];
    memcpy (_objkey, o, l);
}

const CORBA::Octet *
MICO::GIOPSimpleProf::objectkey (CORBA::Long &l) const
{
    l = _length;
    if (!_objkey)
	return (const CORBA::Octet *)"";
    return _objkey;
}

CORBA::Boolean
MICO::GIOPSimpleProf::reachable ()
{
    return TRUE;
}

void
MICO::GIOPSimpleProf::print (ostream &o) const
{
  o << "GIOP Simple Profile" << endl;
}

CORBA::IORProfile *
MICO::GIOPSimpleProf::clone () const
{
    return new GIOPSimpleProf (*this);
}

CORBA::Long
MICO::GIOPSimpleProf::compare (const CORBA::IORProfile &p) const
{
    if (p.id() != id())
	return (CORBA::Long)id() - (CORBA::Long)p.id();
    const GIOPSimpleProf &gp = (const GIOPSimpleProf &)p;
    if (_length != gp._length)
	return (CORBA::Long)_length - (CORBA::Long)gp._length;
    return mico_key_compare (_objkey, gp._objkey, _length);
}

CORBA::Boolean
MICO::GIOPSimpleProf::operator== (const CORBA::IORProfile &p) const
{
    return compare (p) == 0;
}

CORBA::Boolean
MICO::GIOPSimpleProf::operator< (const CORBA::IORProfile &p) const
{
    return compare (p) < 0;
}


/******************************* GIOPConn *******************************/


MICO::GIOPConn::GIOPConn (CORBA::ORB_ptr orb, CORBA::Transport *transp,
			  GIOPConnCallback *cb, GIOPCodec *codec,
			  CORBA::Long tmout)
    : _inctx (codec, new CORBA::Buffer())
{
    _disp = orb->dispatcher();
    _orb = orb;
    _transp = transp;
    _cb = cb;
    // we take over ownership of codec ...
    _codec = codec;

    _inbuf = new CORBA::Buffer;
    _inlen = _codec->header_length ();
    _inflags = 0;
    _infrag = 0;
    _inbufs = 0;

    _refcnt = 0;
    _idle_tmout = tmout;
    _have_tmout = FALSE;
    _have_wselect = FALSE;

    _transp->block (MICO::IIOPProxy::isblocking());
    _transp->rselect (_disp, this);

    check_idle ();
}

MICO::GIOPConn::~GIOPConn ()
{
    assert (_refcnt >= 0);

    list<CORBA::Buffer *>::iterator i;
    for (i = _outbufs.begin(); i != _outbufs.end(); ++i)
	delete *i;

    _disp->remove (this, CORBA::Dispatcher::Timer);
    _transp->rselect (_disp, 0);
    _transp->wselect (_disp, 0);
    delete _transp;
    delete _inbuf;
    CORBA::release (_codec);

    // do not delete: disp
}

void
MICO::GIOPConn::do_read ()
{
    while (42) {
	assert (_inlen > 0);
	CORBA::Long r = _transp->read (*_inbuf, _inlen);
#if 1
	if (r < 0) {
            /*
             * workaround for a problem on Linux and Win32
             * (and probably other OSes as well):
             *   if you send something on a TCP connection that has
             *   been closed by the peer you will get an error on
             *   the next read() instead of beeing able to read
             *   the remaining data until you reach EOF.
             */
            r = _transp->read (*_inbuf, _inlen);
        }
#endif
	if (r < 0 || (r == 0 && _transp->eof())) {
	    // connection broken or EOF
	    _transp->rselect (_disp, 0);
	    _transp->wselect (_disp, 0);
	    _cb->callback (this, GIOPConnCallback::Closed);
	    break;
	} else if (r > 0) {
	    _inlen -= r;
	    if (_inbuf->length() == _codec->header_length()) {
		// header completely received
		assert (_inlen == 0);
		CORBA::GIOP::MsgType mt;
		_inctx.buffer (_inbuf);
		if (!_codec->check_header (_inctx, mt, _inlen, _inflags)) {
		    // garbled message, send it to input handler ...
		    assert (!_inbufs);
		    _inbufs = _inbuf;
		    _inbuf = new CORBA::Buffer;
		    _inlen = _codec->header_length ();
		    if (!_cb->callback (this, GIOPConnCallback::InputReady) ||
			MICO::IIOPProxy::isblocking())
			break;
		    continue;
		}
		if (mt == CORBA::GIOP::Fragment) {
		    // a fragment, append contents to infrag ...
		    if (_codec->version() >= 0x0102) {
			// XXX read fragment header
			assert (0);
		    }
		    assert (_infrag);
		    delete _inbuf;
		    _inbuf = _infrag;
		    _infrag = 0;
		}
	    }
	    if (_inlen == 0) {
		// message completely received
		if (_inflags & GIOP_FRAGMENT_BIT) {
		    // more fragments follow ...
		    assert (!_infrag);
		    _infrag = _inbuf;
		    _inbuf = new CORBA::Buffer;
		    _inlen = _codec->header_length();
		} else {
		    assert (!_inbufs);
		    _inbufs = _inbuf;
		    _inbuf = new CORBA::Buffer;
		    _inlen = _codec->header_length ();
		    if (!_cb->callback (this, GIOPConnCallback::InputReady) ||
			MICO::IIOPProxy::isblocking())
			break;
		}
	    }
	} else if (r == 0) {
	    break;
	} else {
	    assert (0);
	}
    }
}

void
MICO::GIOPConn::do_write ()
{
    while (42) {
	assert (_outbufs.size() > 0);
	CORBA::Buffer *b = _outbufs.front();
	CORBA::Long r = _transp->write (*b, b->length());
	if (r > 0) {
	    if (b->length() == 0) {
		// message completely sent
		delete b;
		_outbufs.pop_front();
		if (_outbufs.size() == 0) {
		    check_idle ();
		    break;
		}
	    }
	} else if (r < 0) {
	    // connection broken
	    _transp->rselect (_disp, 0);
	    _transp->wselect (_disp, 0);
	    _cb->callback (this, GIOPConnCallback::Closed);
	    break;
	} else if (r == 0) {
	    break;
	} else {
	    assert (0);
	}
    }
}

void
MICO::GIOPConn::callback (CORBA::Transport *,
			  CORBA::TransportCallback::Event ev)
{
    switch (ev) {
    case Read:
	do_read ();
	break;

    case Write:
	do_write ();
	break;

    default:
	assert (0);
    }
}

void
MICO::GIOPConn::callback (CORBA::Dispatcher *d,
			  CORBA::DispatcherCallback::Event ev)
{
    switch (ev) {
    case CORBA::Dispatcher::Timer:
	_cb->callback (this, GIOPConnCallback::Idle);
	break;
    case CORBA::Dispatcher::Moved:
	_disp = d;
        break;
    default:
	assert (0);
    }
}

void
MICO::GIOPConn::check_idle ()
{
    if (_idle_tmout > 0 && _refcnt == 0 && _outbufs.size() == 0) {
        if (_have_tmout)
            _disp->remove (this, CORBA::Dispatcher::Timer);
	_disp->tm_event (this, _idle_tmout);
	_have_tmout = TRUE;
    }
    if (_have_wselect && _outbufs.size() == 0) {
        _transp->wselect (_disp, 0);
        _have_wselect = FALSE;
    }
}

void
MICO::GIOPConn::check_busy ()
{
    if (_have_tmout && (_refcnt > 0 || _outbufs.size() > 0)) {
	_disp->remove (this, CORBA::Dispatcher::Timer);
	_have_tmout = FALSE;
    }
    if (!_have_wselect && _outbufs.size() > 0) {
        _transp->wselect (_disp, this);
        _have_wselect = TRUE;
    }
}

CORBA::Boolean
MICO::GIOPConn::check_events ()
{
    if (_transp->isreadable()) {
        do_read();
        return TRUE;
    }
    return FALSE;
}

void
MICO::GIOPConn::ref ()
{
    ++_refcnt;
    check_busy ();
}

CORBA::Boolean
MICO::GIOPConn::deref (CORBA::Boolean all)
{
    if (all)
	_refcnt = 0;
    else
	--_refcnt;
    check_idle ();
    return (_refcnt <= 0);
}

void
MICO::GIOPConn::output (CORBA::Buffer *b)
{
    // try to write as much as possible immediatly
    if (_outbufs.size() == 0) {
	_transp->write (*b, b->length());
	if (b->length() == 0) {
	    delete b;
	    return;
	}
	_outbufs.push_back (b);
    } else {
	_outbufs.push_back (b);
	do_write ();
    }
    check_busy ();
}

CORBA::Buffer *
MICO::GIOPConn::input ()
{
    CORBA::Buffer *b = _inbufs;
    _inbufs = 0;
    return b;
}

void
MICO::GIOPConn::flush ()
{
    CORBA::Boolean isblock = _transp->isblocking();
    _transp->block (TRUE);
    while (_outbufs.size() > 0) {
	CORBA::Buffer *b = _outbufs.front();
	_outbufs.pop_front();
	int i = _transp->write (*b, b->length());
	delete b;
    }
    _transp->block (isblock);
}

void
MICO::GIOPConn::buffering (CORBA::Boolean dobuffering)
{
    _transp->buffering (dobuffering);
}

void
MICO::GIOPConn::cancel (CORBA::ULong reqid)
{
    // XXX kill pending fragment if reqid matches

    // for now disallow CancelRequests inbetween fragments
    assert (!_infrag);
}


/******************************* IIOPProxy ******************************/


CORBA::Boolean MICO::IIOPProxy::_isblocking = FALSE;

MICO::IIOPProxy::IIOPProxy (CORBA::ORB_ptr orb)
{
    /*
     * these are the IOR profile types we can handle.
     */
    _valid_profiles.push_back (CORBA::IORProfile::TAG_INTERNET_IOP);
    _valid_profiles.push_back (CORBA::IORProfile::TAG_UNIX_IOP);
    _valid_profiles.push_back (CORBA::IORProfile::TAG_UDP_IOP);
    _valid_profiles.push_back (CORBA::IORProfile::TAG_SSL_INTERNET_IOP);
    _valid_profiles.push_back (CORBA::IORProfile::TAG_SSL_UNIX_IOP);
    _valid_profiles.push_back (CORBA::IORProfile::TAG_SSL_UDP_IOP);

    _orb = orb;

    _cache_used = FALSE;
    _cache_rec = new IIOPProxyInvokeRec;

    _orb->register_oa (this, OAPriorityRemote);
}

MICO::IIOPProxy::~IIOPProxy ()
{
    _orb->unregister_oa (this);
    /*
     * the address keys point to GIOPConn::Transport->addr(), so do not
     * delete them.
     * the GIOPConn entries in the 'ids' map just pointers to the entries
     * in the 'conns' map, so do not delete them
     */
    for (MapAddrConn::iterator i0 = _conns.begin(); i0 != _conns.end(); ++i0)
	delete (*i0).second;
    for (MapIdConn::iterator i1 = _ids.begin(); i1 != _ids.end(); ++i1)
	delete (*i1).second;

    delete _cache_rec;
}

MICO::IIOPProxyInvokeRec *
MICO::IIOPProxy::create_invoke ()
{
    if (!_cache_used) {
	_cache_used = TRUE;
	return _cache_rec;
    }

    return new IIOPProxyInvokeRec;
}

MICO::IIOPProxyInvokeRec *
MICO::IIOPProxy::get_invoke (MsgId id)
{
    if (_cache_used && _cache_rec->id() == id)
	return _cache_rec;

    MapIdConn::iterator i = _ids.find (id);
    return i == _ids.end() ? 0 : (*i).second;
}

void
MICO::IIOPProxy::add_invoke (IIOPProxyInvokeRec *rec)
{
    if (_cache_rec == rec)
	return;

    _ids[rec->id()] = rec;
}

void
MICO::IIOPProxy::del_invoke (MsgId id)
{
    if (_cache_used && _cache_rec->id() == id) {
	_cache_rec->free();
	_cache_used = FALSE;
	return;
    }
    MapIdConn::iterator i = _ids.find (id);
    if (i != _ids.end()) {
	delete (*i).second;
	_ids.erase (i);
    }
}

void
MICO::IIOPProxy::abort_invoke (MsgId id)
{
    // make invocation fail; notify orb ...
    MICODebug::instance()->tracer()
	<< "invocation(" << id << ") aborted" << endl;

    switch (_orb->request_type (id)) {
    case CORBA::RequestInvoke: {
	CORBA::Object_var obj = new CORBA::Object (new CORBA::IOR);
	CORBA::Request_var req =
	    new CORBA::Request (obj, "someop");
	LocalRequest orbreq (req);
	orbreq.set_out_args (
	    new CORBA::TRANSIENT (0, CORBA::COMPLETED_MAYBE));
	_orb->answer_invoke (id, CORBA::InvokeSysEx,
			     CORBA::Object::_nil(), &orbreq);
	break;
    }
    case CORBA::RequestLocate:
	_orb->answer_locate (id, CORBA::LocateUnknown,
			     CORBA::Object::_nil());
	break;
	
    case CORBA::RequestBind:
	_orb->answer_bind (id, CORBA::LocateUnknown,
			   CORBA::Object::_nil());
	break;

    default:
	assert (0);
    }
    del_invoke (id);
}

void
MICO::IIOPProxy::redo_invoke (MsgId id)
{
    // redo invocation ...
    MICODebug::instance()->tracer()
	<< "invocation(" << id << ") redone" << endl;

    del_invoke (id);
    _orb->redo_request (id);
}

MICO::GIOPConn *
MICO::IIOPProxy::make_conn (const CORBA::Address *addr,
			    CORBA::Boolean docreate)
{
    MapAddrConn::iterator i = _conns.find (addr);
    if (i != _conns.end()) {
#if 1
        /*
         * the check_events() is a workaround for a problem
         * on Linux and Win32 (and probably other OSes as well):
         *   if you send something on a TCP connection that has
         *   been closed by the peer you will get an error on
         *   the next read() instead of beeing able to read
         *   the remaining data until you reach EOF.
         */
        if ((*i).second->check_events()) {
            while ((i = _conns.find (addr)) != _conns.end()) {
                if (!(*i).second->check_events())
                    return (*i).second;
            }
        } else
#endif
            return (*i).second;
    }
    if (!docreate)
	return 0;
    MICODebug::instance()->tracer()
	<< "making new connection to " << addr->stringify() << endl;
    CORBA::Transport *t = addr->make_transport();
    if (!t->connect (addr)) {
        MICODebug::instance()->tracer()
            << "connect: " << t->errormsg() << endl;
        delete t;
        return 0;
    }
    GIOPConn *conn =
	new GIOPConn (_orb, t, this,
		      new GIOPCodec (new CDRDecoder, new CDREncoder),
		      0L /* no tmout */);
    _conns[t->peer()] = conn;
    return conn;
}

MICO::GIOPConn *
MICO::IIOPProxy::make_conn (CORBA::Object_ptr obj)
{
    CORBA::IORProfile *prof;
    const CORBA::Address *addr;
    MICO::GIOPConn *conn;

    CORBA::Policy_var policy =
	obj->_get_policy (MICOPolicy::TRANSPORTPREF_POLICY_TYPE);
    MICOPolicy::TransportPrefPolicy_var tpp =
	MICOPolicy::TransportPrefPolicy::_narrow (policy);
    assert (!CORBA::is_nil (tpp));

    MICOPolicy::TransportPrefPolicy::ProfileTagSeq *prefs =
	tpp->preferences_nocopy();

    for (CORBA::ULong i = 0; i < prefs->length(); ++i) {
        prof = obj->_ior()->profile ((*prefs)[i]);
        while (prof) {
	    addr = prof->addr ();
	    assert (addr);
	    GIOPConn *conn = make_conn (addr);
	    if (conn)
		return conn;
            prof = obj->_ior()->profile ((*prefs)[i], FALSE, prof);
	}
    }
    return 0;
}

void
MICO::IIOPProxy::kill_conn (GIOPConn *conn, CORBA::Boolean redo)
{
    CORBA::Boolean again;

    do {
	again = FALSE;
	for (MapAddrConn::iterator i = _conns.begin(); i != _conns.end(); ++i) {
	    if ((*i).second == conn) {
		_conns.erase (i);
		again = TRUE;
		break;
	    }
	}
    } while (again);

    // abort/redo pending requests for this connection

    if (_cache_used && _cache_rec->conn() == conn) {
	if (redo) {
	    redo_invoke (_cache_rec->id());
	} else {
	    abort_invoke (_cache_rec->id());
	}
    }
	
    do {
	again = FALSE;
	IIOPProxyInvokeRec *rec;
	for (MapIdConn::iterator i = _ids.begin(); i != _ids.end(); ++i) {
	    rec = (*i).second;
	    if (rec->conn() != conn)
		continue;

	    if (redo) {
		redo_invoke (rec->id());
	    } else {
		abort_invoke (rec->id());
	    }
	    again = TRUE;
	    break;
	}
    } while (again);
    delete conn;
}

void
MICO::IIOPProxy::conn_error (GIOPConn *conn, CORBA::Boolean send_error)
{
    if (!send_error) {
	kill_conn (conn);
	return;
    }

    GIOPOutContext out (conn->codec());
    conn->codec()->put_error_msg (out);
    conn->output (out._retn());
    // prepare shutdown (i.e. wait until MessageError has been sent)
    conn->deref (TRUE);
}

CORBA::Boolean
MICO::IIOPProxy::get_codeset_ids (CORBA::Object_ptr obj,
				  CORBA::Codeset::CodesetId &csid,
				  CORBA::Codeset::CodesetId &wcsid)
{
    CORBA::IORProfile *prof;
    MICO::CodesetComponent *csc = 0;

    prof = obj->_ior()->profile (CORBA::IORProfile::TAG_MULTIPLE_COMPONENTS,
				 TRUE);
    if (prof) {
	CORBA::MultiComponent *mc =
	    ((MICO::MultiCompProfile *)prof)->components();
	CORBA::Component *comp =
	    mc->component (CORBA::Component::TAG_CODE_SETS);
	if (comp)
	    csc = (MICO::CodesetComponent *)comp;
    }

    if (csc) {
	csid = csc->selected_cs();
	wcsid = csc->selected_wcs();
    } else {
	// no code set info, use defaults ...
	csid = CORBA::Codeset::special_cs(CORBA::Codeset::DefaultCS)->id();
	wcsid = CORBA::Codeset::special_cs(CORBA::Codeset::DefaultWCS)->id();
    }
    return TRUE;
}

const char *
MICO::IIOPProxy::get_oaid () const
{
    return "mico-iiop-proxy";
}

CORBA::Boolean
MICO::IIOPProxy::has_object (CORBA::Object_ptr obj)
{
    CORBA::IOR *tmpl = _orb->ior_template();
    /*
     * we have every object whose IOR has a profile tag that is listed
     * in valid_profiles and the profile doesnt point to this process
     * (to prevent infinite loops when trying to talk to nonexisting
     * objects in existent servers).
     */
    for (mico_vec_size_type i = 0; i < _valid_profiles.size(); ++i) {
        CORBA::IORProfile *p1, *p2;
        p1 = obj->_ior()->profile (_valid_profiles[i]);
        if (p1) {
            p2 = tmpl->profile (_valid_profiles[i]);
            return !p2 || !(*p1 == *p2);
        }
    }
    return FALSE;
}

CORBA::Boolean
MICO::IIOPProxy::is_local () const
{
    return FALSE;
}

CORBA::Boolean
MICO::IIOPProxy::invoke (MsgId msgid, CORBA::Object_ptr obj,
			 CORBA::ORBRequest *req,
			 CORBA::Principal_ptr pr, CORBA::Boolean response_exp)
{
    GIOPConn *conn = make_conn (obj);
    if (!conn) {
        CORBA::COMM_FAILURE ex;
	req->set_out_args (&ex);
	_orb->answer_invoke (msgid, CORBA::InvokeSysEx, CORBA::Object::_nil(),
			     req);
	return FALSE;
    }

    // set up code set converters 
    CORBA::Codeset::CodesetId csid = 0, wcsid = 0;
    CORBA::CodesetConv *conv = 0, *wconv = 0;

    if (!CORBA::Codeset::disabled()) {
	if (!strcmp (req->type(), "giop")) {
	    // its a GIOP request, use code sets that the client selected
	    GIOPRequest *greq = (GIOPRequest *)req;
	    csid = greq->csid();
	    wcsid = greq->wcsid();
	    if (csid) {
		conv = the_codeset_db.find (csid, csid);
	    }
	    if (wcsid) {
		wconv = the_codeset_db.find (wcsid, wcsid);
	    }
	} else {
	    // run code set selection algorithm
	    CORBA::Boolean r = get_codeset_ids (obj, csid, wcsid);
	    assert (r);

	    if (csid) {
		conv = the_codeset_db.find (
		    CORBA::Codeset::special_cs(CORBA::Codeset::NativeCS)->id(),
		    csid);
	    }
	    if (wcsid) {
		wconv = the_codeset_db.find (
		    CORBA::Codeset::special_cs(CORBA::Codeset::NativeWCS)->id(),
		    wcsid);
	    }
	}
    }

    GIOPOutContext out (conn->codec(), conv, wconv);
    if (!conn->codec()->put_invoke_request (out, msgid, response_exp,
					    obj, req, pr)) {
        CORBA::MARSHAL ex;
	req->set_out_args (&ex);
	_orb->answer_invoke (msgid, CORBA::InvokeSysEx, CORBA::Object::_nil(),
			     req);
	return FALSE;
    }

    if (response_exp) {
	conn->ref();
	IIOPProxyInvokeRec *rec = create_invoke();
	rec->init (msgid, conn, req, csid, wcsid);
	add_invoke (rec);
    }
    conn->buffering (!response_exp);
    conn->output (out._retn());
    if (response_exp && _isblocking)
	conn->do_read ();
    return TRUE;
}

CORBA::Boolean
MICO::IIOPProxy::bind (MsgId msgid, const char *repoid,
		       const CORBA::ORB::ObjectTag &oid,
		       CORBA::Address *addr)
{
    if (!addr || addr->is_local())
	return FALSE;

    GIOPConn *conn = make_conn (addr);
    if (!conn) {
        _orb->answer_bind (msgid, CORBA::LocateUnknown, CORBA::Object::_nil());
        return TRUE;
    }

    GIOPOutContext out (conn->codec());
    conn->codec()->put_bind_request (out, msgid, repoid, oid);

    conn->ref();
    //assert (_ids.count (msgid) == 0);
    IIOPProxyInvokeRec *rec = create_invoke();
    rec->init (msgid, conn);
    add_invoke (rec);

    conn->output (out._retn());
    return TRUE;
}

CORBA::Boolean
MICO::IIOPProxy::locate (MsgId msgid, CORBA::Object_ptr obj)
{
    GIOPConn *conn = make_conn (obj);
    if (!conn) {
	_orb->answer_locate (msgid, CORBA::LocateUnknown,
			     CORBA::Object::_nil());
	return FALSE;
    }

    GIOPOutContext out (conn->codec());
    conn->codec()->put_locate_request (out, msgid, obj);

    conn->ref();
    //assert (_ids.count (msgid) == 0);
    IIOPProxyInvokeRec *rec = create_invoke();
    rec->init (msgid, conn);
    add_invoke (rec);

    conn->output (out._retn());
    return TRUE;
}

CORBA::Object_ptr
MICO::IIOPProxy::skeleton (CORBA::Object_ptr)
{
    assert (0);
    return CORBA::Object::_nil ();
}

void
MICO::IIOPProxy::cancel (MsgId msgid)
{
    IIOPProxyInvokeRec *rec = get_invoke (msgid);
    if (!rec)
	return;

    GIOPOutContext out (rec->conn()->codec());
    rec->conn()->codec()->put_cancel_request (out, msgid);

    rec->conn()->output (out._retn());
    rec->conn()->deref ();

    del_invoke (msgid);
}

void
MICO::IIOPProxy::shutdown (CORBA::Boolean wait_for_completion)
{
    // XXX make sure all invocations have completed
    _orb->answer_shutdown (this);
}

void
MICO::IIOPProxy::answer_invoke (CORBA::ULong, CORBA::Object_ptr,
				CORBA::ORBRequest *, CORBA::InvokeStatus)
{
    assert (0);
}

void
MICO::IIOPProxy::exec_invoke_reply (GIOPInContext &in, CORBA::ULong req_id,
				    CORBA::GIOP::ReplyStatusType stat,
				    CORBA::Object_ptr obj,
				    CORBA::ORBRequest *req,
				    GIOPConn *conn)
{
    switch (_orb->request_type (req_id)) {
    case CORBA::RequestBind: {
	// it was a bind
	CORBA::GIOP::LocateStatusType bind_stat;
	CORBA::Object_ptr bind_obj;

	if (stat != CORBA::GIOP::NO_EXCEPTION ||
	    !conn->codec()->get_bind_reply (in, bind_stat, bind_obj) ||
	    bind_stat != CORBA::GIOP::OBJECT_HERE) {
	    _orb->answer_bind (req_id, CORBA::LocateUnknown,
			       CORBA::Object::_nil());
	} else {
	    _orb->answer_bind (req_id, CORBA::LocateHere, bind_obj);
	    CORBA::release (bind_obj);
	}
	break;
    }
    case CORBA::RequestInvoke: {
	// it was a normal invocation
	CORBA::InvokeStatus orb_stat = CORBA::InvokeOk;

	switch (stat) {
	case CORBA::GIOP::NO_EXCEPTION:
	    orb_stat = CORBA::InvokeOk;
	    break;

	case CORBA::GIOP::USER_EXCEPTION:
	    orb_stat = CORBA::InvokeUsrEx;
	    break;

	case CORBA::GIOP::SYSTEM_EXCEPTION:
	    orb_stat = CORBA::InvokeSysEx;
	    break;

	case CORBA::GIOP::LOCATION_FORWARD:
	case CORBA::GIOP::LOCATION_FORWARD_PERM:
	    orb_stat = CORBA::InvokeForward;
	    break;

	default:
	    assert (0);
	    break;
	}
	_orb->answer_invoke (req_id, orb_stat, obj, req);
	break;
    }
    case CORBA::RequestUnknown:
	// request was canceled or reply contains invalid id
	break;
    default:
	assert (0);
    }
}

CORBA::Boolean
MICO::IIOPProxy::handle_invoke_reply (GIOPConn *conn, GIOPInContext &in)
{
    CORBA::ULong req_id;
    CORBA::GIOP::ReplyStatusType stat;
    CORBA::Object_ptr obj = CORBA::Object::_nil();
    CORBA::IOP::ServiceContextList ctx;

    // XXX take care, get_invoke_reply() does a in._retn()
    if (!conn->codec()->get_invoke_reply1 (in, req_id, stat, ctx)) {
	MICODebug::instance()->printer()
	    << "cannot decode Reply1" << endl;
	conn_error (conn);
	return FALSE;
    }

    IIOPProxyInvokeRec *rec = get_invoke (req_id);
    if (!rec) {
	// has been canceled; cancel() did the deref() already
	return TRUE;
    }

    if (!CORBA::Codeset::disabled()) {
	/*
	 * set up code set converters. this must be done before
	 * get_invoke_reply2(), because it creates a GIOPRequest
	 * which needs these converters.
	 */
	CORBA::CodesetConv *conv = 0, *wconv = 0;

	if (rec->csid())
	    conv = the_codeset_db.find (
		rec->csid(),
		CORBA::Codeset::special_cs(CORBA::Codeset::NativeCS)->id());

	if (rec->wcsid())
	    wconv = the_codeset_db.find (
		rec->wcsid(),
		CORBA::Codeset::special_cs(CORBA::Codeset::NativeWCS)->id());

	in.converters (conv, wconv);
    }

    if (!conn->codec()->get_invoke_reply2 (in, req_id, stat, obj,
					   rec->request(), ctx)) {
	MICODebug::instance()->printer()
	    << "reply marshalling error" << endl;
        if (rec->request()) {
            CORBA::MARSHAL ex (0, CORBA::COMPLETED_MAYBE);
            rec->request()->set_out_args (&ex);
            stat = CORBA::GIOP::SYSTEM_EXCEPTION;
        }
    }
    exec_invoke_reply (in, req_id, stat, obj, rec->request(), conn);
    CORBA::release (obj);

    conn->deref();
    del_invoke (req_id);

    return TRUE;
}

CORBA::Boolean
MICO::IIOPProxy::handle_locate_reply (GIOPConn *conn, GIOPInContext &in)
{
    CORBA::ULong req_id;
    CORBA::GIOP::LocateStatusType stat = CORBA::GIOP::OBJECT_HERE;
    CORBA::LocateStatus orb_stat = CORBA::LocateHere;
    CORBA::Object_ptr obj = CORBA::Object::_nil();

    if (!conn->codec()->get_locate_reply (in, req_id, stat, obj)) {
	MICODebug::instance()->printer()
	    << "cannot decode LocateReply" << endl;
	conn_error (conn);
	return FALSE;
    }
    IIOPProxyInvokeRec *rec = get_invoke (req_id);
    if (!rec) {
	// has been canceled; cancel() did the deref() already
	return TRUE;
    }
    switch (stat) {
    case CORBA::GIOP::UNKNOWN_OBJECT:
	orb_stat = CORBA::LocateUnknown;
	break;

    case CORBA::GIOP::OBJECT_HERE:
	orb_stat = CORBA::LocateHere;
	break;

    case CORBA::GIOP::OBJECT_FORWARD:
    case CORBA::GIOP::OBJECT_FORWARD_PERM:
	orb_stat = CORBA::LocateForward;
	break;

    default:
	assert (0);
	break;
    }
    _orb->answer_locate (req_id, orb_stat, obj);
    CORBA::release (obj);

    conn->deref();
    del_invoke (req_id);

    return TRUE;
}

CORBA::Boolean
MICO::IIOPProxy::handle_input (GIOPConn *conn)
{
    GIOPInContext in (conn->codec(), conn->input());

    CORBA::GIOP::MsgType mt;
    CORBA::ULong size;
    CORBA::Octet flags;

    // XXX size is wrong for fragmented messages ...
    if (!conn->codec()->get_header (in, mt, size, flags)) {
	MICODebug::instance()->printer()
	    << "cannot decode header" << endl;
	conn_error (conn);
	return FALSE;
    }
    switch (mt) {
    case CORBA::GIOP::Reply:
	return handle_invoke_reply (conn, in);

    case CORBA::GIOP::LocateReply:
	return handle_locate_reply (conn, in);

    case CORBA::GIOP::CloseConnection:
	if (!conn->codec()->get_close_msg (in)) {
	    MICODebug::instance()->printer()
		<< "cannot decode CloseConnection" << endl;
	    conn_error (conn);
	} else {
	    MICODebug::instance()->tracer()
		<< "got CloseConnection" << endl;
	    kill_conn (conn, TRUE);
	}
	return FALSE;

    case CORBA::GIOP::MessageError:
	if (!conn->codec()->get_error_msg (in)) {
	    MICODebug::instance()->printer()
		<< "cannot decode MessageError" << endl;
	    conn_error (conn, FALSE);
	    break;
	}
	MICODebug::instance()->printer()
	    << "got MessageError" << endl;
	kill_conn (conn);
	return FALSE;

    default:
	MICODebug::instance()->printer()
	    << "bad message type: " << mt << endl;
	break;
    }
    return TRUE;
}

CORBA::Boolean
MICO::IIOPProxy::callback (GIOPConn *conn, GIOPConnCallback::Event ev)
{
    switch (ev) {
    case GIOPConnCallback::InputReady:
	return handle_input (conn);

    case GIOPConnCallback::Idle:
	MICODebug::instance()->tracer()
	    << "shutting down idle conn" << endl;
	kill_conn (conn);
	return FALSE;

    case GIOPConnCallback::Closed:
	MICODebug::instance()->tracer()
	    << "conn closed or broken" << endl;
	kill_conn (conn);
	return FALSE;

    default:
	assert (0);
    }
    return TRUE;
}


/************************* IIOPServerInvokeRec ************************/


MICO::IIOPServerInvokeRec::IIOPServerInvokeRec ()
{
    _conn = 0;
    _req = 0;
    _obj = 0;
    _pr = 0;
}


MICO::IIOPServerInvokeRec::~IIOPServerInvokeRec ()
{
    CORBA::release (_req);
    CORBA::release (_obj);
    CORBA::release (_pr);

    // XXX do not free connection
}

void
MICO::IIOPServerInvokeRec::free ()
{
    CORBA::release (_req);
    CORBA::release (_obj);
    CORBA::release (_pr);

    _conn = 0;
    _req = 0;
    _obj = 0;
    _pr = 0;
}

void
MICO::IIOPServerInvokeRec::init_invoke (
    GIOPConn *conn, MsgId reqid,
    MsgId orbid, CORBA::ORBRequest *req,
    CORBA::Object_ptr obj,
    CORBA::Principal_ptr pr)
{
    _conn = conn;
    _orbid = orbid;
    _reqid = reqid;
    _req = req;
    _obj = obj;
    _pr = pr;
}

void
MICO::IIOPServerInvokeRec::init_locate (
    GIOPConn *conn, MsgId reqid,
    MsgId orbid, CORBA::Object_ptr obj)
{
    _conn = conn;
    _orbid = orbid;
    _reqid = reqid;
    _req = CORBA::ORBRequest::_nil();
    _obj = obj;
    _pr = CORBA::Principal::_nil();
}


/******************************* IIOPServer *****************************/


MICO::IIOPServer::IIOPServer (CORBA::ORB_ptr orb)
{
    _orb = orb;

    _cache_used = FALSE;
    _cache_rec = new IIOPServerInvokeRec;

    // we only register as an OA to be notified of shutdown...
    _orb->register_oa (this, OAPriorityRemote);
}

MICO::IIOPServer::~IIOPServer ()
{
    _orb->unregister_oa (this);
    /*
     * the GIOPConn entries in the 'orbids' and 'reqids' maps are just
     * pointers to the entries in the 'conns' list, so do not delete them
     */
    for (ListConn::iterator i0 = _conns.begin(); i0 != _conns.end(); ++i0)
	delete *i0;
    if (_cache_used)
	_orb->cancel (_cache_rec->orbid());
    for (MapIdConn::iterator i1 = _orbids.begin(); i1 != _orbids.end(); ++i1) {
	_orb->cancel ((*i1).first);
	delete (*i1).second;
    }
    for (mico_vec_size_type i2 = 0; i2 < _tservers.size(); ++i2) {
	_tservers[i2]->aselect (_orb->dispatcher(), 0);
	delete _tservers[i2];
    }
}

CORBA::Boolean
MICO::IIOPServer::listen (CORBA::Address *addr, CORBA::Address *fwproxyaddr)
{
    CORBA::IORProfile *prof;
    CORBA::TransportServer *tserv = addr->make_transport_server ();
    if (!tserv->bind (addr)) {
        MICODebug::instance()->printer()
	    << "cannot bind to " << addr->stringify() << ": "
            << tserv->errormsg() << endl;
        return FALSE;
    }
    tserv->block (MICO::IIOPProxy::isblocking());
    tserv->aselect (_orb->dispatcher(), this);

    if (!fwproxyaddr) {
        prof = tserv->addr()->make_ior_profile ((CORBA::Octet *)"", 1,
						CORBA::MultiComponent());
    } else {
        prof = fwproxyaddr->make_ior_profile ((CORBA::Octet *)"", 1,
                                              CORBA::MultiComponent());
    }


    /*
     * install an IIOP profile tag in the ORB's object template.
     * object adapters will use this template to generate new object
     * references...
     */
    MICODebug::instance()->tracer()
	<< "binding to " << prof->addr()->stringify() << endl;

    _orb->ior_template()->add_profile (prof);

    _tservers.push_back (tserv);
    return TRUE;
}

CORBA::Boolean
MICO::IIOPServer::listen ()
{
    InetAddress addr ("0.0.0.0", 0);
    return listen (&addr, 0);
}

MICO::IIOPServerInvokeRec *
MICO::IIOPServer::create_invoke ()
{
    if (!_cache_used) {
	_cache_used = TRUE;
	return _cache_rec;
    }

    return new IIOPServerInvokeRec;
}

MICO::IIOPServerInvokeRec *
MICO::IIOPServer::get_invoke_reqid (MsgId msgid, GIOPConn *conn)
{
    if (_cache_used && _cache_rec->reqid() == msgid &&
	_cache_rec->conn() == conn)
	return _cache_rec;

    // XXX slow, but only needed for cancel

    IIOPServerInvokeRec *rec;
    for (MapIdConn::iterator i = _orbids.begin(); i != _orbids.end(); ++i) {
	rec = (*i).second;
	if (rec->reqid() == msgid && rec->conn() == conn)
	    return rec;
    }
    return 0;
}

MICO::IIOPServerInvokeRec *
MICO::IIOPServer::get_invoke_orbid (MsgId msgid)
{
    if (_cache_used && _cache_rec->orbid() == msgid)
	return _cache_rec;

    MapIdConn::iterator i = _orbids.find (msgid);
    return (i != _orbids.end() ? (*i).second : 0);
}

void
MICO::IIOPServer::add_invoke (IIOPServerInvokeRec *rec)
{
    if (_cache_rec == rec)
	return;

    //assert (_orbids.count (rec->orbid()) == 0);
    _orbids[rec->orbid()] = rec;
}

void
MICO::IIOPServer::del_invoke_orbid (MsgId msgid)
{
    if (_cache_used && _cache_rec->orbid() == msgid) {
	_cache_rec->free();
	_cache_used = FALSE;
	return;
    }

    MapIdConn::iterator i = _orbids.find (msgid);
    if (i != _orbids.end()) {
	delete (*i).second;
	_orbids.erase (i);
    }
}

void
MICO::IIOPServer::del_invoke_reqid (MsgId msgid, GIOPConn *conn)
{
    if (_cache_used && _cache_rec->reqid() == msgid &&
	_cache_rec->conn() == conn) {
	_cache_rec->free();
	_cache_used = FALSE;
	return;
    }

    // XXX slow, but rarely used
    IIOPServerInvokeRec *rec;
    for (MapIdConn::iterator i = _orbids.begin(); i != _orbids.end(); ++i) {
	rec = (*i).second;
	if (rec->reqid() == msgid && rec->conn() == conn) {
	    delete rec;
	    _orbids.erase (i);
	    break;
	}
    }
}

void
MICO::IIOPServer::abort_invoke_orbid (MsgId msgid)
{
    _orb->cancel (msgid);
    del_invoke_orbid (msgid);
}

void
MICO::IIOPServer::kill_conn (GIOPConn *conn)
{
    CORBA::Boolean again;

    do {
	again = FALSE;
	for (ListConn::iterator i = _conns.begin(); i != _conns.end(); ++i) {
	    if (*i == conn) {
		_conns.erase (i);
		again = TRUE;
		break;
	    }
	}
    } while (again);

    // abort pending invocations for this connection

    if (_cache_used && _cache_rec->conn() == conn) {
	_orb->cancel (_cache_rec->orbid());
	_cache_used = FALSE;
    }

    do {
	again = FALSE;
	IIOPServerInvokeRec *rec;
	for (MapIdConn::iterator i = _orbids.begin(); i != _orbids.end(); ++i) {
	    rec = (*i).second;
	    if (rec->conn() == conn) {
		abort_invoke_orbid (rec->orbid());
		again = TRUE;
		break;
	    }
	}
    } while (again);
    delete conn;
}

void
MICO::IIOPServer::conn_error (GIOPConn *conn, CORBA::Boolean send_error)
{
    if (!send_error) {
	kill_conn (conn);
	return;
    }

    GIOPOutContext out (conn->codec());
    conn->codec()->put_error_msg (out);
    conn->output (out._retn());
    conn->deref (TRUE);
    conn->flush();
}

void
MICO::IIOPServer::conn_closed (GIOPConn *conn)
{
    GIOPOutContext out (conn->codec());
    conn->codec()->put_close_msg (out);
    conn->output (out._retn());
    conn->deref (TRUE);
    conn->flush();
}

CORBA::Boolean
MICO::IIOPServer::handle_input (GIOPConn *conn)
{
    GIOPInContext in (conn->codec(), conn->input());

    CORBA::GIOP::MsgType mt;
    CORBA::ULong size;
    CORBA::Octet flags;

    // XXX size is wrong for fragmented messages ...
    if (!conn->codec()->get_header (in, mt, size, flags)) {
	MICODebug::instance()->printer()
	    << "cannot decode header" << endl;
	conn_error (conn);
	return FALSE;
    }
    switch (mt) {
    case CORBA::GIOP::Request:
	return handle_invoke_request (conn, in);

    case CORBA::GIOP::LocateRequest:
	return handle_locate_request (conn, in);

    case CORBA::GIOP::MessageError:
	if (!conn->codec()->get_error_msg (in)) {
	    MICODebug::instance()->printer()
		<< "cannot decode MessageError" << endl;
	    conn_error (conn, FALSE);
	} else {
	    MICODebug::instance()->printer()
		<< "got MessageError" << endl;
	    kill_conn (conn);
	}
	return FALSE;

    case CORBA::GIOP::CancelRequest:
	return handle_cancel_request (conn, in);

    default:
	MICODebug::instance()->printer()
	    << "bad message type: " << mt << endl;
	break;
    }
    return TRUE;
}

MICO::IIOPServer::MsgId
MICO::IIOPServer::exec_invoke_request (GIOPInContext &in,
				       CORBA::Object_ptr obj, 
				       CORBA::ORBRequest *req,
				       CORBA::Principal_ptr pr,
				       CORBA::Boolean resp_exp,
				       GIOPConn *conn,
				       MsgId orbid)
{
    if (!strcmp (req->op_name(), "_bind")) {
	// its a bind
	CORBA::String_var repoid;
	CORBA::ORB::ObjectTag oid;
	CORBA::Boolean r = conn->codec()->get_bind_request (in, repoid.out(),
							    oid);
	assert (r);
	/*
	 * orb makes copies of repoid and oid so we can delete them
	 * after the call to bind_async()
	 */
	return _orb->bind_async (repoid, oid, 0, this, orbid);
    } else {
	// its a normal invocation
	return _orb->invoke_async (obj, req, pr, resp_exp, this, orbid);
    }
}

CORBA::Boolean
MICO::IIOPServer::handle_invoke_request (GIOPConn *conn, GIOPInContext &in)
{
    CORBA::ULong req_id;
    CORBA::Boolean resp;
    CORBA::ORBRequest *req;
    CORBA::Principal_ptr pr = conn->transport()->get_principal();
    CORBA::Object_ptr obj = new CORBA::Object (new CORBA::IOR);

    // XXX take care, get_invoke_request() does a in._retn()
    if (!conn->codec()->get_invoke_request (in, req_id, resp, obj, req, pr)) {
	CORBA::release (obj);
	CORBA::release (pr);
	MICODebug::instance()->printer()
	    << "cannot decode Request" << endl;
	conn_error (conn);
	return FALSE;
    }
    // XXX obj is incomplete, see IOR::operator== ...

    /*
     * code sets are set up in get_contextlist(). GIOPRequest will
     * set up converters for out args, so we dont need to do anything
     * special.
     */

    /*
     * must install the invocation record before we call the ORB, because
     * may invoke callback before returning from invoke_async ...
     */
    MsgId orbid = _orb->new_msgid();
    if (resp) {
	conn->ref ();
	IIOPServerInvokeRec *rec = create_invoke();
	rec->init_invoke (conn, req_id, orbid, req, obj, pr);
	add_invoke (rec);
    }
    MsgId orbid2 = exec_invoke_request (in, obj, req, pr, resp, conn, orbid);
    assert (orbid == orbid2 || (orbid2 == 0 && !resp));

    if (!resp) {
	CORBA::release (req);
	CORBA::release (obj);
	CORBA::release (pr);
    }

    // maybe the connection was closed inbetween: make do_read() break
    return FALSE;
}

CORBA::Boolean
MICO::IIOPServer::handle_locate_request (GIOPConn *conn, GIOPInContext &in)
{
    CORBA::ULong req_id;
    CORBA::Object_ptr obj = new CORBA::Object (new CORBA::IOR);

    if (!conn->codec()->get_locate_request (in, req_id, obj)) {
	CORBA::release (obj);
	MICODebug::instance()->printer()
	    << "cannot decode LocateRequest" << endl;
	conn_error (conn);
	return FALSE;
    }
    // XXX obj is incomplete, see IOR::operator== ...

    /*
     * must install the invocation record before we call the ORB, because
     * may invoke callback before returning from invoke_async ...
     */
    MsgId orbid = _orb->new_msgid();
    conn->ref ();
    IIOPServerInvokeRec *rec = create_invoke();
    rec->init_locate (conn, req_id, orbid, obj);
    add_invoke (rec);

    MsgId orbid2 = _orb->locate_async (obj, this, orbid);
    assert (orbid == orbid2);

    // maybe the connection was closed inbetween: make do_read() break
    return FALSE;
}

CORBA::Boolean
MICO::IIOPServer::handle_cancel_request (GIOPConn *conn, GIOPInContext &in)
{
    CORBA::ULong req_id;

    if (!conn->codec()->get_cancel_request (in, req_id)) {
	MICODebug::instance()->printer()
	    << "cannot decode CancelRequest" << endl;
	conn_error (conn);
	return FALSE;
    }
    conn->cancel (req_id);

    IIOPServerInvokeRec *rec = get_invoke_reqid (req_id, conn);
    if (!rec) {
	// request already finished or no such id
	return TRUE;
    }
    MsgId orbid = rec->orbid();

    // maybe rec->conn() != conn ...
    // connection might be deleted during call to orb->cancel() ...
    rec->conn()->deref ();
    del_invoke_orbid (orbid);
    
    _orb->cancel (orbid);

    // maybe the connection was closed inbetween: make do_read() break
    return FALSE;
}

void
MICO::IIOPServer::handle_invoke_reply (MsgId msgid)
{
    CORBA::ORBRequest *req;
    CORBA::Object_ptr obj = CORBA::Object::_nil();
    CORBA::InvokeStatus stat = _orb->get_invoke_reply (msgid, obj, req);

    IIOPServerInvokeRec *rec = get_invoke_orbid (msgid);
    if (!rec) {
        // invocation canceled (perhaps connection to client broken)
	CORBA::release (obj);
        return;
    }

    CORBA::GIOP::ReplyStatusType giop_stat = CORBA::GIOP::NO_EXCEPTION;
    switch (stat) {
    case CORBA::InvokeSysEx:
	giop_stat = CORBA::GIOP::SYSTEM_EXCEPTION;
	break;

    case CORBA::InvokeUsrEx:
	giop_stat = CORBA::GIOP::USER_EXCEPTION;
	break;

    case CORBA::InvokeOk:
	giop_stat = CORBA::GIOP::NO_EXCEPTION;
	break;

    case CORBA::InvokeForward:
	giop_stat = CORBA::GIOP::LOCATION_FORWARD;
	break;
    }

    GIOPOutContext out (rec->conn()->codec());
    if (!rec->conn()->codec()->put_invoke_reply (out, rec->reqid(), giop_stat,
						 obj, req)) {
	out.reset ();
	CORBA::MARSHAL ex;
	req->set_out_args (&ex);
	rec->conn()->codec()->put_invoke_reply (out, rec->reqid(),
						CORBA::GIOP::SYSTEM_EXCEPTION,
						obj, req);
    }
    CORBA::release (obj);

    rec->conn()->output (out._retn());
    rec->conn()->deref ();
    del_invoke_orbid (rec->orbid());
}

void
MICO::IIOPServer::handle_locate_reply (MsgId msgid)
{
    CORBA::Object_ptr obj = CORBA::Object::_nil();
    CORBA::LocateStatus stat = _orb->get_locate_reply (msgid, obj);

    IIOPServerInvokeRec *rec = get_invoke_orbid (msgid);
    if (!rec) {
        // invocation canceled (perhaps connection to client broken)
	CORBA::release (obj);
        return;
    }

    CORBA::GIOP::LocateStatusType giop_stat = CORBA::GIOP::OBJECT_HERE;
    switch (stat) {
    case CORBA::LocateHere:
	giop_stat = CORBA::GIOP::OBJECT_HERE;
	break;

    case CORBA::LocateUnknown:
	giop_stat = CORBA::GIOP::UNKNOWN_OBJECT;
	break;

    case CORBA::LocateForward:
	giop_stat = CORBA::GIOP::OBJECT_FORWARD;
	break;
    }

    GIOPOutContext out (rec->conn()->codec());
    rec->conn()->codec()->put_locate_reply (out, rec->reqid(), giop_stat, obj);
    CORBA::release (obj);

    rec->conn()->output (out._retn());
    rec->conn()->deref ();
    del_invoke_orbid (rec->orbid());
}

void
MICO::IIOPServer::handle_bind_reply (MsgId msgid)
{
    CORBA::Object_ptr obj = CORBA::Object::_nil();
    CORBA::LocateStatus stat = _orb->get_bind_reply (msgid, obj);

    IIOPServerInvokeRec *rec = get_invoke_orbid (msgid);
    if (!rec) {
        // invocation canceled (perhaps connection to client broken)
	CORBA::release (obj);
        return;
    }

    CORBA::GIOP::LocateStatusType giop_stat = CORBA::GIOP::OBJECT_HERE;
    switch (stat) {
    case CORBA::LocateHere:
	giop_stat = CORBA::GIOP::OBJECT_HERE;
	break;

    case CORBA::LocateUnknown:
	giop_stat = CORBA::GIOP::UNKNOWN_OBJECT;
	break;

    case CORBA::LocateForward:
	giop_stat = CORBA::GIOP::OBJECT_FORWARD;
	break;
    }

    GIOPOutContext out (rec->conn()->codec());
    rec->conn()->codec()->put_bind_reply (out, rec->reqid(), giop_stat, obj);
    CORBA::release (obj);

    rec->conn()->output (out._retn());
    rec->conn()->deref ();
    del_invoke_orbid (rec->orbid());
}

const char *
MICO::IIOPServer::get_oaid () const
{
    return "mico-iiop-server";
}

CORBA::Boolean
MICO::IIOPServer::has_object (CORBA::Object_ptr)
{
    return FALSE;
}

CORBA::Boolean
MICO::IIOPServer::is_local () const
{
    // so we shutdown() after all local adapters which might
    // need IIOPServer for shutdown ...
    return FALSE;
}

CORBA::Boolean
MICO::IIOPServer::invoke (MsgId, CORBA::Object_ptr,
			  CORBA::ORBRequest *,
			  CORBA::Principal_ptr, CORBA::Boolean)
{
    assert (0);
    return TRUE;
}

CORBA::Boolean
MICO::IIOPServer::bind (MsgId, const char *,
			const CORBA::ORB::ObjectTag &,
			CORBA::Address *)
{
    return FALSE;
}

CORBA::Boolean
MICO::IIOPServer::locate (MsgId, CORBA::Object_ptr)
{
    assert (0);
    return FALSE;
}

CORBA::Object_ptr
MICO::IIOPServer::skeleton (CORBA::Object_ptr)
{
    assert (0);
    return CORBA::Object::_nil ();
}

void
MICO::IIOPServer::cancel (MsgId)
{
    assert (0);
}

void
MICO::IIOPServer::shutdown (CORBA::Boolean wait_for_completion)
{
    for (mico_vec_size_type i2 = 0; i2 < _tservers.size(); ++i2) {
	_tservers[i2]->aselect (_orb->dispatcher(), 0);
	delete _tservers[i2];
    }
    _tservers.erase (_tservers.begin(), _tservers.end());

    /*
     * the GIOPConn entries in the 'orbids' and 'reqids' maps are just
     * pointers to the entries in the 'conns' list, so do not delete them
     */
    for (ListConn::iterator i0 = _conns.begin(); i0 != _conns.end(); ++i0) {
	conn_closed (*i0);
	delete *i0;
    }
    _conns.erase (_conns.begin(), _conns.end());

    if (_cache_used)
	_orb->cancel (_cache_rec->orbid());
    for (MapIdConn::iterator i1 = _orbids.begin(); i1 != _orbids.end(); ++i1) {
	_orb->cancel ((*i1).first);
	delete (*i1).second;
    }
    _orbids.erase (_orbids.begin(), _orbids.end());
    _cache_used = FALSE;

    _orb->answer_shutdown (this);
}

void
MICO::IIOPServer::answer_invoke (CORBA::ULong, CORBA::Object_ptr,
				 CORBA::ORBRequest *, CORBA::InvokeStatus)
{
    assert (0);
}

void
MICO::IIOPServer::callback (CORBA::ORB_ptr, MsgId msgid,
			    CORBA::ORBCallback::Event ev)
{
    switch (ev) {
    case CORBA::ORBCallback::Invoke:
	handle_invoke_reply (msgid);
	break;

    case CORBA::ORBCallback::Locate:
	handle_locate_reply (msgid);
	break;

    case CORBA::ORBCallback::Bind:
	handle_bind_reply (msgid);
	break;

    default:
	assert (0);
    }
}

CORBA::Boolean
MICO::IIOPServer::callback (GIOPConn *conn, GIOPConnCallback::Event ev)
{
    switch (ev) {
    case GIOPConnCallback::InputReady:
	return handle_input (conn);

    case GIOPConnCallback::Idle:
	MICODebug::instance()->tracer()
	    << "shutting down idle conn" << endl;
	conn_closed (conn);
	kill_conn (conn);
	return FALSE;

    case GIOPConnCallback::Closed: {
	MICODebug::instance()->tracer()
	    << "conn closed or broken" << endl;
	const CORBA::Address *addr = conn->transport()->peer();
	assert (addr);
	Interceptor::ConnInterceptor::
	    _exec_client_disconnect (addr->stringify().c_str());
	kill_conn (conn);
	return FALSE;
    }
    default:
	assert (0);
    }
    return TRUE;
}

void
MICO::IIOPServer::callback (CORBA::TransportServer *tserv,
			    CORBA::TransportServerCallback::Event ev)
{
    switch (ev) {
    case CORBA::TransportServerCallback::Accept: {
	CORBA::Transport *t = tserv->accept();
	if (t) {
	    MICODebug::instance()->tracer()
		<< "new connection from " << t->peer()->stringify() << endl;
            if (t->bad()) {
                MICODebug::instance()->tracer()
                    << "bad conn: " << t->errormsg() << endl;
                delete t;
                break;
            }
	    const CORBA::Address *addr = t->peer();
	    assert (addr);
	    CORBA::Boolean r = Interceptor::ConnInterceptor::
		_exec_client_connect (addr->stringify().c_str());
	    if (!r) {
		delete t;
		break;
	    }
	    GIOPConn *conn =
		new GIOPConn (_orb, t, this,
			      new GIOPCodec (new CDRDecoder, new CDREncoder),
			      0L /* no tmout */);
	    _conns.push_back (conn);
	}
	break;
    }
    default:
	assert (0);
    }
}

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

#include <CORBA-SMALL.h>
#ifndef _WINDOWS
#include <string.h>
#endif
#include <iostream.h>
#include <mico/impl.h>
#include <mico/template_impl.h>
#include <mico/util.h>

/**************************** DataEncoder ******************************/


CORBA::DataEncoder::DataEncoder ()
{
    buf = new Buffer;
    dofree_buf = TRUE;
    conv = 0;
    dofree_conv = FALSE;
    wconv = 0;
    dofree_wconv = FALSE;
    vstate = 0;
    dofree_vstate = FALSE;
}

CORBA::DataEncoder::DataEncoder (Buffer *b, Boolean dofree_b,
                                 CodesetConv *c, Boolean dofree_c,
                                 CodesetConv *wc, Boolean dofree_wc,
				 ValueState *vs, Boolean dofree_vs)
{
    buf = b;
    dofree_buf = dofree_b;
    conv = c;
    dofree_conv = dofree_c;
    wconv = wc;
    dofree_wconv = dofree_wc;
    vstate = vs;
    dofree_vstate = dofree_vs;
}

CORBA::DataEncoder::~DataEncoder ()
{
    if (dofree_buf)
	delete buf;
    if (dofree_conv && conv)
        delete conv;
    if (dofree_wconv && wconv)
        delete wconv;
    if (dofree_vstate && vstate)
	delete vstate;
}

void
CORBA::DataEncoder::put_buffer (const Buffer &b)
{
    buf->put (b.data(), b.length());
}

void
CORBA::DataEncoder::put_octets (const void *data, ULong len)
{
    buf->put (data, len);
}

void
CORBA::DataEncoder::put_string (const string &s)
{
    put_string (s.c_str());
}

void
CORBA::DataEncoder::put_string_raw (const string &s)
{
    put_string_raw (s.c_str());
}

void
CORBA::DataEncoder::put_context (const Context &ctx, ContextList_ptr clist)
{
    ctx.encode (*this, clist);
}

void
CORBA::DataEncoder::put_principal (const Principal &pr)
{
    pr.encode (*this);
}

void
CORBA::DataEncoder::put_any (const Any &a)
{
    a.encode (*this);
}

void
CORBA::DataEncoder::put_typecode (const TypeCode &t)
{
    t.encode (*this);
}

void
CORBA::DataEncoder::put_ior (const IOR &ior)
{
    ior.encode (*this);
}

void
CORBA::DataEncoder::enumeration (ULong val)
{
    put_ulong (val);
}

void
CORBA::DataEncoder::struct_begin ()
{
}

void
CORBA::DataEncoder::struct_end ()
{
}

void
CORBA::DataEncoder::except_begin (const string &repoid)
{
    put_string (repoid);
}

void
CORBA::DataEncoder::except_end ()
{
}

void
CORBA::DataEncoder::seq_begin (ULong l)
{
    put_ulong (l);
}

void
CORBA::DataEncoder::seq_end ()
{
}

void
CORBA::DataEncoder::encaps_begin (EncapsState &state)
{
    /*
     * XXX [12-9] says the aligment base for the encapsulated data
     * is the first octet of the encapsulated data.
     */
    state.align = buffer()->walign_base ();
    state.bo = byteorder();
    state.pos = buffer()->wpos();

    put_ulong (0);

    buffer()->walign_base (buffer()->wpos());

    put_octet (byteorder() == CORBA::LittleEndian ? TRUE : FALSE);
}

void
CORBA::DataEncoder::encaps_end (EncapsState &state)
{
    byteorder (state.bo);
    buffer()->walign_base (state.align);

    ULong end = buffer()->wpos();

    buffer()->wseek_beg (state.pos);
    put_ulong (0);

    ULong data_start = buffer()->wpos();
    buffer()->wseek_beg (state.pos);
    put_ulong (end-data_start);

    buffer()->wseek_beg (end);
}

void
CORBA::DataEncoder::delayed_seq_begin (DelayedSeqState &state)
{
    state.pos = buffer()->wpos();
    put_ulong (0);
}

void
CORBA::DataEncoder::delayed_seq_end (DelayedSeqState &state, ULong l)
{
    ULong pos = buffer()->wpos();
    buffer()->wseek_beg (state.pos);
    put_ulong (l);
    buffer()->wseek_beg (pos);
}

void
CORBA::DataEncoder::union_begin ()
{
}

void
CORBA::DataEncoder::union_end ()
{
}

void
CORBA::DataEncoder::arr_begin ()
{
}

void
CORBA::DataEncoder::arr_end ()
{
}

void
CORBA::DataEncoder::value_begin (const string &url,
				 const vector<string> &repoids,
				 Boolean chunked,
				 Long &value_id)
{
    assert (vstate);
    value_begin (url, repoids, chunked, value_id, *vstate);
}

void
CORBA::DataEncoder::value_begin (const string &url,
				 const vector<string> &repoids,
				 Boolean chunked,
				 Long &value_id,
				 ValueState &state)
{
    if (state.chunk_level <= state.nesting_level && state.tag_pos >= 0) {
	// close the previous chunk
	if (state.tag_pos + sizeof(Long) == buf->wpos()) {
	    // chunk is empty
	    buf->wseek_beg (state.tag_pos);
	} else {
	    // chunk contains data, write out chunk length
	    Long wpos = buf->wpos();
	    buf->wseek_beg (state.tag_pos);
	    put_long (wpos - state.tag_pos - sizeof (Long));
	    buf->wseek_beg (wpos);
	}
    }

    state.nesting_level += 1;
    if (chunked && state.chunk_level > state.nesting_level)
	state.chunk_level = state.nesting_level;

    Long value_tag = 0x7fffff00;

    if (url.length() > 0)
	// url
	value_tag |= 0x01;

    if (repoids.size() == 1) {
	// single repoid
	value_tag |= 0x02;
    } else if (repoids.size() > 1) {
	// repoid sequence
	value_tag |= 0x06;
    }

    if (state.chunk_level <= state.nesting_level)
	// chunked
	value_tag |= 0x08;

    put_long (value_tag);

    // +1 to avoid value_id 0
    value_id = buf->wpos() - sizeof(Long) + 1;

    if (url.length() > 0)
	put_string (url);

    if (repoids.size() == 1) {
	put_string (repoids[0]);
    } else if (repoids.size() > 1) {
	seq_begin (repoids.size());
	for (mico_vec_size_type i = 0; i < repoids.size(); ++i)
	    put_string (repoids[i]);
	seq_end();
    }

    if (state.chunk_level <= state.nesting_level) {
	// chunked, write out tag for next chunk
	put_long (0);
	state.tag_pos = buf->wpos() - sizeof (Long);
    }
}

void
CORBA::DataEncoder::value_end (Long value_id)
{
    assert (vstate);
    value_end (value_id, *vstate);
}

void
CORBA::DataEncoder::value_end (Long value_id, ValueState &state)
{
    assert (state.nesting_level > 0);

    if (!(state.chunk_level <= state.nesting_level)) {
	// not chunked
	state.nesting_level -= 1;
	return;
    }

    if (state.tag_pos >= 0) {
	// close the previous chunk
	if (state.tag_pos + sizeof(Long) == buf->wpos()) {
	    // chunk is empty
	    buf->wseek_beg (state.tag_pos);
	} else {
	    // chunk contains data, write out chunk length
	    Long wpos = buf->wpos();
	    buf->wseek_beg (state.tag_pos);
	    put_long (wpos - state.tag_pos - sizeof (Long));
	    buf->wseek_beg (wpos);
	}
    }

    // write end tag
    put_long (-state.nesting_level);

    state.nesting_level -= 1;
    if (state.nesting_level > 0 &&
	state.chunk_level <= state.nesting_level) {
	// still chunked, write out tag for next chunk
	put_long (0);
	state.tag_pos = buf->wpos() - sizeof (Long);
    } else {
	// now follows unchunked data (or no data at all)
	state.chunk_level = 0x7fffffff;
	state.tag_pos = -1;
    }
}

void
CORBA::DataEncoder::value_ref (Long value_id)
{
    if (value_id == 0) {
	// nil
	put_long (0);
    } else {
	// indirection
	put_long (0xffffffff);
	// -1 because value_id is buffer pos of referred value +1
	put_long (value_id - 1 - buf->wpos());
    }
}

void
CORBA::DataEncoder::buffer (Buffer *b, Boolean release)
{
    if (dofree_buf)
	delete buf;
    buf = b;
    dofree_buf = release;
}

void
CORBA::DataEncoder::converter (CodesetConv *c, Boolean release)
{
    if (dofree_conv && conv)
	delete conv;
    conv = c;
    dofree_conv = release;
}

void
CORBA::DataEncoder::wconverter (CodesetConv *c, Boolean release)
{
    if (dofree_wconv && wconv)
	delete wconv;
    wconv = c;
    dofree_wconv = release;
}

void
CORBA::DataEncoder::valuestate (ValueState *vs, Boolean release)
{
    if (dofree_vstate && vstate)
	delete vstate;
    vstate = vs;
    dofree_vstate = release;
}

CORBA::ByteOrder
CORBA::DataEncoder::byteorder () const
{
#if defined(HAVE_BYTEORDER_BE)
    return CORBA::BigEndian;
#else
    return CORBA::LittleEndian;
#endif
}

void
CORBA::DataEncoder::byteorder (CORBA::ByteOrder bo)
{
    assert (bo == byteorder());
}


/**************************** DataDecoder ******************************/


CORBA::DataDecoder::DataDecoder (Buffer *b, Boolean dofree_b,
                                 CodesetConv *c, Boolean dofree_c,
                                 CodesetConv *wc, Boolean dofree_wc,
				 ValueState *vs, Boolean dofree_vs)
{
    buf = b;
    dofree_buf = dofree_b;
    conv = c;
    dofree_conv = dofree_c;
    wconv = wc;
    dofree_wconv = dofree_wc;
    vstate = vs;
    dofree_vstate = dofree_vs;
}

CORBA::DataDecoder::~DataDecoder ()
{
    if (dofree_buf)
	delete buf;
    if (dofree_conv && conv)
        delete conv;
    if (dofree_wconv && wconv)
        delete wconv;
    if (dofree_vstate && vstate)
	delete vstate;
}

CORBA::Boolean
CORBA::DataDecoder::get_octets (void *data, ULong len)
{
    return buf->get (data, len);
}

CORBA::Boolean
CORBA::DataDecoder::get_string (string &str)
{
    char *s;
    if (!get_string (s))
        return FALSE;
    str = s;
    CORBA::string_free (s);
    return TRUE;
}

CORBA::Boolean
CORBA::DataDecoder::get_string_raw (string &str)
{
    char *s;
    if (!get_string_raw (s))
        return FALSE;
    str = s;
    CORBA::string_free (s);
    return TRUE;
}

CORBA::Boolean
CORBA::DataDecoder::get_context (Context &ctx)
{
    return ctx.decode (*this);
}

CORBA::Boolean
CORBA::DataDecoder::get_principal (Principal &pr)
{
    return pr.decode (*this);
}

CORBA::Boolean
CORBA::DataDecoder::get_any (Any &a)
{
    return a.decode (*this);
}

CORBA::Boolean
CORBA::DataDecoder::get_typecode (TypeCode &t)
{
    return t.decode (*this);
}

CORBA::Boolean
CORBA::DataDecoder::get_ior (IOR &ior)
{
    return ior.decode (*this);
}

CORBA::Boolean
CORBA::DataDecoder::enumeration (ULong &val)
{
    return get_ulong (val);
}

CORBA::Boolean
CORBA::DataDecoder::struct_begin ()
{
    return TRUE;
}

CORBA::Boolean
CORBA::DataDecoder::struct_end ()
{
    return TRUE;
}

CORBA::Boolean
CORBA::DataDecoder::except_begin (string &repoid)
{
    return get_string (repoid);
}

CORBA::Boolean
CORBA::DataDecoder::except_end ()
{
    return TRUE;
}

CORBA::Boolean
CORBA::DataDecoder::seq_begin (ULong &l)
{
    return get_ulong (l);
}

CORBA::Boolean
CORBA::DataDecoder::seq_end ()
{
    return TRUE;
}

CORBA::Boolean
CORBA::DataDecoder::encaps_begin (EncapsState &state, ULong &len)
{
    /*
     * XXX [12-9] says the aligment base for the encapsulated data
     * is the first octet of the encapsulated data.
     */
    state.align = buffer()->ralign_base();
    state.bo = byteorder();

    if (!get_ulong (len))
	return FALSE;
    --len;

    buffer()->ralign_base (buffer()->rpos());

    Octet bo;
    if (!get_octet (bo))
	return FALSE;
    byteorder (bo == 0 ? CORBA::BigEndian : CORBA::LittleEndian);
    return TRUE;
}

CORBA::Boolean
CORBA::DataDecoder::encaps_end (EncapsState &state)
{
    byteorder (state.bo);
    buffer()->ralign_base (state.align);
    return TRUE;
}

CORBA::Boolean
CORBA::DataDecoder::union_begin ()
{
    return TRUE;
}

CORBA::Boolean
CORBA::DataDecoder::union_end ()
{
    return TRUE;
}

CORBA::Boolean
CORBA::DataDecoder::arr_begin ()
{
    return TRUE;
}

CORBA::Boolean
CORBA::DataDecoder::arr_end ()
{
    return TRUE;
}


CORBA::Boolean
CORBA::DataDecoder::get_indirect_string (string &s)
{
    Long tag, rpos = buf->rpos();

    if (!get_long (tag))
	return FALSE;
    if (tag == 0xffffffff) {
	// indirection
	Long indir;
	rpos = buf->rpos();
	if (!get_long (indir))
	    return FALSE;
	indir += rpos;
	rpos = buf->rpos();
	if (!buf->rseek_beg (indir))
	    return FALSE;
	if (!get_string (s))
	    return FALSE;
	buf->rseek_beg (rpos);
    } else {
	// string
	buf->rseek_beg (rpos);
	if (!get_string (s))
	    return FALSE;
    }
    return TRUE;
}

CORBA::Boolean
CORBA::DataDecoder::get_indirect_string_seq (vector<string> &v)
{
    Long tag, rpos = buf->rpos();

    if (!get_long (tag))
	return FALSE;
    if (tag == 0xffffffff) {
	// indirection
	Long indir;
	rpos = buf->rpos();
	if (!get_long (indir))
	    return FALSE;
	indir += rpos;
	rpos = buf->rpos();
	if (!buf->rseek_beg (indir))
	    return FALSE;

	ULong len;
	string s;
	if (!seq_begin (len))
	    return FALSE;
	for (ULong i = 0; i < len; ++i) {
	    if (!get_string (s))
		return FALSE;
	    v.push_back (s);
	}
	if (!seq_end ())
	    return FALSE;
	buf->rseek_beg (rpos);
    } else {
	// sequence<string>
	buf->rseek_beg (rpos);

	ULong len;
	string s;
	if (!seq_begin (len))
	    return FALSE;
	for (ULong i = 0; i < len; ++i) {
	    if (!get_string (s))
		return FALSE;
	    v.push_back (s);
	}
	if (!seq_end ())
	    return FALSE;
    }
    return TRUE;
}

CORBA::Boolean
CORBA::DataDecoder::value_begin (string &url,
				 vector<string> &repoids,
				 Long &value_id,
				 Boolean &is_ref)
{
    assert (vstate);
    return value_begin (url, repoids, value_id, is_ref, *vstate);
}

CORBA::Boolean
CORBA::DataDecoder::value_begin (string &url,
				 vector<string> &repoids,
				 Long &value_id,
				 Boolean &is_ref,
				 ValueState &state)
{
    Long value_tag;

    if (!get_long (value_tag))
	return FALSE;

    if (value_tag == 0xffffffff) {
	// indirection
	Long indir, rpos = buf->rpos();
	if (!get_long (indir))
	    return FALSE;

	// +1 to avoid value_id 0
	value_id = rpos + indir + 1;

	MapIdState::iterator i = state.skipped.find (value_id);
	if (i != state.skipped.end() && (*i).second.saved_pos < 0) {
	    // the actual encoding of the value has been
	    // skipped, so we have to decode it now instead
	    // of returning an indirection ...
	    ValueState1 tmp_state = state.s;
	    tmp_state.saved_pos = buf->rpos();

	    state.s = (*i).second;
	    (*i).second = tmp_state;

	    buf->rseek_beg (value_id-1);
	    return value_begin (url, repoids, value_id, is_ref, state);
	} else {
	    // already decoded earlier, return an indirection
	    is_ref = TRUE;
	    return TRUE;
	}
    }
    if (value_tag == 0) {
	// nil
	value_id = 0;
	is_ref = TRUE;
	return TRUE;
    }
    if (!(0x7fffff00 <= value_tag && value_tag <= 0x7fffffff)) {
	MICODebug::instance()->tracer()
	    << "DataDecoder::value_begin(): bad tag: "
	    << "0x" << hex << value_tag << endl;
        return FALSE;
    }
    
    // value
    // +1 to avoid value_id 0
    value_id = buf->rpos() - sizeof (Long) + 1;
    is_ref = FALSE;

    if (value_tag & 0x01) {
	// url
	if (!get_indirect_string (url))
	    return FALSE;
    }

    repoids.erase (repoids.begin(), repoids.end());
    if ((value_tag & 0x06) == 0x02) {
	// one repoid
	string s;
	if (!get_indirect_string (s))
	    return FALSE;
	repoids.push_back (s);
    } else if ((value_tag & 0x06) == 0x06) {
	// sequence of repoids
	if (!get_indirect_string_seq (repoids))
	    return FALSE;
    }

    state.s.nesting_level += 1;

    if (value_tag & 0x08) {
	// chunk flag
	if (state.s.chunk_level > state.s.nesting_level)
	    state.s.chunk_level = state.s.nesting_level;
    }

    if (state.s.chunk_level <= state.s.nesting_level) {
	// chunked
	state.s.data_nesting_level += 1;

	// try to open next chunk
	Long tag, rpos = buf->rpos();

	if (!get_long (tag))
	    return FALSE;

	if (0 < tag && tag < 0x7fffff00) {
	    // ok, its a chunk
	    rpos = buf->rpos();
	    // make sure next tag is no block size tag, which
	    // is currently not supported, because then we
	    // had to check for end of chunk after each get_*
	    // operation ...
	    if (!buf->rseek_rel (tag))
		return FALSE;
	    if (!get_long (tag))
		return FALSE;
	    assert (!(0 < tag && tag < 0x7fffff00));
	}
	buf->rseek_beg (rpos);
    }
    return TRUE;
}

CORBA::Boolean
CORBA::DataDecoder::value_end (Long finished_value_id)
{
    assert (vstate);
    return value_end (finished_value_id, *vstate);
}

CORBA::Boolean
CORBA::DataDecoder::value_end (Long finished_value_id, ValueState &state)
{
    // must not be called if value_begin() returned an indirection or nil,
    // i.e. if is_ref == TRUE!

    assert (state.s.nesting_level > 0);

    MapIdState::iterator i = state.skipped.find (finished_value_id);
    if (i != state.skipped.end() && (*i).second.saved_pos >= 0) {
	// we just finished decoding a value that had been
	// skipped earlier ...
	buf->rseek_beg ((*i).second.saved_pos);

	state.s = (*i).second;
	state.s.saved_pos = -1;

	state.skipped.erase (i);
	return TRUE;
    }

    if (!(state.s.chunk_level <= state.s.nesting_level)) {
	// not chunked
	state.s.nesting_level -= 1;
	return TRUE;
    }

    if (state.s.data_nesting_level < state.s.nesting_level) {
	// we already read the end tag ...
	state.s.nesting_level -= 1;
	return TRUE;
    }

    // skip until we read our end tag
    while (state.s.data_nesting_level >= state.s.nesting_level) {
	Long tag, rpos = buf->rpos();
	if (!get_long (tag))
	    return FALSE;
	if (0 < tag && tag < 0x7fffff00) {
	    // chunk
	    if (!buf->rseek_rel (tag))
		return FALSE;
	} else if (tag < 0) {
	    // end tag
	    if (state.s.data_nesting_level > -tag-1) {
		state.s.data_nesting_level = -tag-1;
	    } else {
		MICODebug::instance()->tracer()
		    << "DataDecoder::value_end(): bad end tag: "
		    << tag << " (ignored)" << endl;
	    }
	} else {
	    // value or value_ref or nil
	    buf->rseek_beg (rpos);

	    string url;
	    vector<string> repoids;
	    Long value_id;
	    Boolean is_ref;
	    ValueState1 saved_state = state.s;

	    if (!value_begin (url, repoids, value_id, is_ref, state))
		return FALSE;
	    if (!is_ref) {
		if (!value_end (value_id, state))
		    return FALSE;
		// later we may come across indirections that refer
		// to the value we just skipped. when we come across
		// the first such reference we have to treat the
		// indirection as if is was the value itself. therefore
		// we have to save the state ...
		saved_state.saved_pos = -1;
		state.skipped[value_id] = saved_state;
	    }
	}
    }
    state.s.nesting_level -= 1;

    while (state.s.data_nesting_level > 0 &&
	   state.s.chunk_level <= state.s.data_nesting_level) {
	// still chunked, eat next end tag
	Long tag, rpos = buf->rpos();
	if (!get_long (tag))
	    return FALSE;

	if (tag < 0) {
	    // end tag
	    if (state.s.data_nesting_level > -tag-1) {
		state.s.data_nesting_level = -tag-1;
	    } else {
		MICODebug::instance()->tracer()
		    << "DataDecoder::value_end(): bad end tag: "
		    << tag << " (ignored)" << endl;
	    }
	} else {
	    // some other tag
	    buf->rseek_beg (rpos);
	    break;
	}
    }
    if (state.s.data_nesting_level > 0 &&
	state.s.chunk_level <= state.s.data_nesting_level) {
	// still chunked, try to open next chunk
	Long tag, rpos = buf->rpos();

	if (!get_long (tag))
	    return FALSE;

	if (0 < tag && tag < 0x7fffff00) {
	    // ok, its a chunk
	    rpos = buf->rpos();
	    // make sure next tag is no block size tag, which
	    // is currently not supported, because then we
	    // had to check for end of chunk after each get_*
	    // operation ...
	    if (!buf->rseek_rel (tag))
		return FALSE;
	    if (!get_long (tag))
		return FALSE;
	    assert (!(0 < tag && tag < 0x7fffff00));
	}
	buf->rseek_beg (rpos);
    } else {
	// now follows unchunked data (or no data at all)
	state.s.chunk_level = 0x7fffffff;
    }
    return TRUE;
}

void
CORBA::DataDecoder::buffer (Buffer *b, Boolean release)
{
    if (dofree_buf)
	delete buf;
    buf = b;
    dofree_buf = release;
}

void
CORBA::DataDecoder::converter (CodesetConv *c, Boolean release)
{
    if (dofree_conv && conv)
	delete conv;
    conv = c;
    dofree_conv = release;
}

void
CORBA::DataDecoder::wconverter (CodesetConv *c, Boolean release)
{
    if (dofree_wconv && wconv)
	delete wconv;
    wconv = c;
    dofree_wconv = release;
}

void
CORBA::DataDecoder::valuestate (ValueState *vs, Boolean release)
{
    if (dofree_vstate && vstate)
	delete vstate;
    vstate = vs;
    dofree_vstate = release;
}

CORBA::ByteOrder
CORBA::DataDecoder::byteorder () const
{
#if defined(HAVE_BYTEORDER_BE)
    return CORBA::BigEndian;
#else
    return CORBA::LittleEndian;
#endif
}

void
CORBA::DataDecoder::byteorder (CORBA::ByteOrder bo)
{
    assert (bo == byteorder());
}


/**************************** SimpleEncoder ******************************/


MICO::SimpleEncoder::SimpleEncoder ()
{
}

MICO::SimpleEncoder::SimpleEncoder (CORBA::Buffer *b, CORBA::Boolean dofree_b,
                                    CORBA::CodesetConv *c,
                                    CORBA::Boolean dofree_c,
                                    CORBA::CodesetConv *wc,
                                    CORBA::Boolean dofree_wc,
				    ValueState *vs,
				    CORBA::Boolean dofree_vs)
    : CORBA::DataEncoder (b, dofree_b, c, dofree_c, wc, dofree_wc,
			  vs, dofree_vs)
{
}

MICO::SimpleEncoder::~SimpleEncoder ()
{
}

void
MICO::SimpleEncoder::put_short (CORBA::Short s)
{
    buf->put (&s, sizeof (s));
}

void
MICO::SimpleEncoder::put_ushort (CORBA::UShort us)
{
    buf->put (&us, sizeof (us));
}

void
MICO::SimpleEncoder::put_long (CORBA::Long l)
{
    buf->put (&l, sizeof (l));
}

void
MICO::SimpleEncoder::put_longlong (CORBA::LongLong l)
{
    buf->put (&l, sizeof (l));
}

void
MICO::SimpleEncoder::put_ulong (CORBA::ULong ul)
{
    buf->put (&ul, sizeof (ul));
}

void
MICO::SimpleEncoder::put_ulonglong (CORBA::ULongLong ul)
{
    buf->put (&ul, sizeof (ul));
}

void
MICO::SimpleEncoder::put_float (CORBA::Float f)
{
    buf->put (&f, sizeof (f));
}

void
MICO::SimpleEncoder::put_double (CORBA::Double d)
{
    buf->put (&d, sizeof (d));
}

void
MICO::SimpleEncoder::put_longdouble (CORBA::LongDouble d)
{
    buf->put (&d, sizeof (d));
}

void
MICO::SimpleEncoder::put_char (CORBA::Char c)
{
    buf->put (&c, sizeof (c));
}

void
MICO::SimpleEncoder::put_char_raw (CORBA::Char c)
{
    buf->put (&c, sizeof (c));
}

void
MICO::SimpleEncoder::put_wchar (CORBA::WChar c)
{
    buf->put (&c, sizeof (c));
}

void
MICO::SimpleEncoder::put_octet (CORBA::Octet o)
{
    buf->put (&o, sizeof (o));
}

void
MICO::SimpleEncoder::put_boolean (CORBA::Boolean b)
{
    buf->put (&b, sizeof (b));
}

void
MICO::SimpleEncoder::put_shorts (const CORBA::Short *p, CORBA::ULong l)
{
    buf->put (p, l*sizeof(CORBA::Short));
}

void
MICO::SimpleEncoder::put_ushorts (const CORBA::UShort *p, CORBA::ULong l)
{
    buf->put (p, l*sizeof(CORBA::UShort));
}

void
MICO::SimpleEncoder::put_longs (const CORBA::Long *p, CORBA::ULong l)
{
    buf->put (p, l*sizeof(CORBA::Long));
}

void
MICO::SimpleEncoder::put_longlongs (const CORBA::LongLong *p, CORBA::ULong l)
{
    buf->put (p, l*sizeof(CORBA::LongLong));
}

void
MICO::SimpleEncoder::put_ulongs (const CORBA::ULong *p, CORBA::ULong l)
{
    buf->put (p, l*sizeof(CORBA::ULong));
}

void
MICO::SimpleEncoder::put_ulonglongs (const CORBA::ULongLong *p, CORBA::ULong l)
{
    buf->put (p, l*sizeof(CORBA::ULongLong));
}

void
MICO::SimpleEncoder::put_floats (const CORBA::Float *p, CORBA::ULong l)
{
    buf->put (p, l*sizeof(CORBA::Float));
}

void
MICO::SimpleEncoder::put_doubles (const CORBA::Double *p, CORBA::ULong l)
{
    buf->put (p, l*sizeof(CORBA::Double));
}

void
MICO::SimpleEncoder::put_longdoubles (const CORBA::LongDouble *p,
				      CORBA::ULong l)
{
    buf->put (p, l*sizeof(CORBA::LongDouble));
}

void
MICO::SimpleEncoder::put_chars (const CORBA::Char *p, CORBA::ULong l)
{
    buf->put (p, l);
}

void
MICO::SimpleEncoder::put_chars_raw (const CORBA::Char *p, CORBA::ULong l)
{
    buf->put (p, l);
}

void
MICO::SimpleEncoder::put_wchars (const CORBA::WChar *p, CORBA::ULong l)
{
    buf->put (p, l*sizeof(CORBA::WChar));
}

void
MICO::SimpleEncoder::put_booleans (const CORBA::Boolean *p, CORBA::ULong l)
{
    buf->put (p, l);
}

void
MICO::SimpleEncoder::put_string (const char *s)
{
    CORBA::ULong len = strlen (s) + 1;
    put_ulong (len);
    buf->put (s, len);
}

void
MICO::SimpleEncoder::put_string_raw (const char *s)
{
    CORBA::ULong len = strlen (s) + 1;
    put_ulong (len);
    buf->put (s, len);
}

void
MICO::SimpleEncoder::put_wstring (const wchar_t *s)
{
    CORBA::ULong len = xwcslen (s) + 1;
    put_ulong (len);
    buf->put (s, len*sizeof(wchar_t));
}

void
MICO::SimpleEncoder::put_fixed (const FixedBase::FixedValue &value,
				CORBA::UShort digits,
				CORBA::Short scale)
{
    assert (value.length() == (CORBA::ULong)digits+1);
    put_octets (&value[0], value.length());
}

CORBA::DataEncoder *
MICO::SimpleEncoder::clone () const
{
    return new SimpleEncoder (new CORBA::Buffer (*buf), TRUE,
			      (conv ? conv->clone() : 0), TRUE,
			      (wconv ? wconv->clone() : 0), TRUE);
}

CORBA::DataEncoder *
MICO::SimpleEncoder::clone (CORBA::Buffer *b, CORBA::Boolean dofree_b,
                            CORBA::CodesetConv *c,
                            CORBA::Boolean dofree_c,
                            CORBA::CodesetConv *wc,
                            CORBA::Boolean dofree_wc,
			    ValueState *vs,
			    CORBA::Boolean dofree_vs) const
{
    return new SimpleEncoder (b, dofree_b, c, dofree_c, wc, dofree_wc,
			      vs, dofree_vs);
}

CORBA::DataDecoder *
MICO::SimpleEncoder::decoder () const
{
    return new SimpleDecoder (new CORBA::Buffer (*buf), TRUE,
			      (conv ? conv->clone() : 0), TRUE,
			      (wconv ? wconv->clone() : 0), TRUE,
			      0, TRUE);
}

CORBA::DataDecoder *
MICO::SimpleEncoder::decoder (CORBA::Buffer *b, CORBA::Boolean dofree_b,
			      CORBA::CodesetConv *c,
			      CORBA::Boolean dofree_c,
			      CORBA::CodesetConv *wc,
			      CORBA::Boolean dofree_wc) const
{
    return new SimpleDecoder (b, dofree_b, c, dofree_c, wc, dofree_wc,
			      0, TRUE);
}

const char *
MICO::SimpleEncoder::type () const
{
    return "simple";
}

CORBA::ULong
MICO::SimpleEncoder::max_alignment () const
{
    return 1;
}


/**************************** SimpleDecoder ******************************/


MICO::SimpleDecoder::SimpleDecoder ()
    : CORBA::DataDecoder (new CORBA::Buffer, TRUE)
{
}

MICO::SimpleDecoder::SimpleDecoder (CORBA::Buffer *b, CORBA::Boolean dofree_b,
                                    CORBA::CodesetConv *c,
                                    CORBA::Boolean dofree_c,
                                    CORBA::CodesetConv *wc,
                                    CORBA::Boolean dofree_wc,
				    ValueState *vs,
				    CORBA::Boolean dofree_vs)
    : CORBA::DataDecoder (b, dofree_b, c, dofree_c, wc, dofree_wc,
			  vs, dofree_vs)
{
}

MICO::SimpleDecoder::~SimpleDecoder ()
{
}

CORBA::Boolean
MICO::SimpleDecoder::get_short (CORBA::Short &s)
{
    return buf->get (&s, sizeof (s));
}

CORBA::Boolean
MICO::SimpleDecoder::get_ushort (CORBA::UShort &us)
{
    return buf->get (&us, sizeof (us));
}

CORBA::Boolean
MICO::SimpleDecoder::get_long (CORBA::Long &l)
{
    return buf->get (&l, sizeof (l));
}

CORBA::Boolean
MICO::SimpleDecoder::get_longlong (CORBA::LongLong &l)
{
    return buf->get (&l, sizeof (l));
}

CORBA::Boolean
MICO::SimpleDecoder::get_ulong (CORBA::ULong &ul)
{
    return buf->get (&ul, sizeof (ul));
}

CORBA::Boolean
MICO::SimpleDecoder::get_ulonglong (CORBA::ULongLong &ul)
{
    return buf->get (&ul, sizeof (ul));
}

CORBA::Boolean
MICO::SimpleDecoder::get_float (CORBA::Float &f)
{
    return buf->get (&f, sizeof (f));
}

CORBA::Boolean
MICO::SimpleDecoder::get_double (CORBA::Double &d)
{
    return buf->get (&d, sizeof (d));
}

CORBA::Boolean
MICO::SimpleDecoder::get_longdouble (CORBA::LongDouble &d)
{
    return buf->get (&d, sizeof (d));
}

CORBA::Boolean
MICO::SimpleDecoder::get_char (CORBA::Char &c)
{
    return buf->get (&c, sizeof (c));
}

CORBA::Boolean
MICO::SimpleDecoder::get_char_raw (CORBA::Char &c)
{
    return buf->get (&c, sizeof (c));
}

CORBA::Boolean
MICO::SimpleDecoder::get_wchar (CORBA::WChar &c)
{
    return buf->get (&c, sizeof (c));
}

CORBA::Boolean
MICO::SimpleDecoder::get_octet (CORBA::Octet &o)
{
    return buf->get (&o, sizeof (o));
}

CORBA::Boolean
MICO::SimpleDecoder::get_boolean (CORBA::Boolean &b)
{
    return buf->get (&b, sizeof (b));
}

CORBA::Boolean
MICO::SimpleDecoder::get_shorts (CORBA::Short *p, CORBA::ULong l)
{
    l *= sizeof (CORBA::Short);
    return buf->get (p, l);
}

CORBA::Boolean
MICO::SimpleDecoder::get_ushorts (CORBA::UShort *p, CORBA::ULong l)
{
    l *= sizeof (CORBA::UShort);
    return buf->get (p, l);
}

CORBA::Boolean
MICO::SimpleDecoder::get_longs (CORBA::Long *p, CORBA::ULong l)
{
    l *= sizeof (CORBA::Long);
    return buf->get (p, l);
}

CORBA::Boolean
MICO::SimpleDecoder::get_longlongs (CORBA::LongLong *p, CORBA::ULong l)
{
    l *= sizeof (CORBA::LongLong);
    return buf->get (p, l);
}

CORBA::Boolean
MICO::SimpleDecoder::get_ulongs (CORBA::ULong *p, CORBA::ULong l)
{
    l *= sizeof (CORBA::ULong);
    return buf->get (p, l);
}

CORBA::Boolean
MICO::SimpleDecoder::get_ulonglongs (CORBA::ULongLong *p, CORBA::ULong l)
{
    l *= sizeof (CORBA::ULongLong);
    return buf->get (p, l);
}

CORBA::Boolean
MICO::SimpleDecoder::get_floats (CORBA::Float *p, CORBA::ULong l)
{
    l *= sizeof (CORBA::Float);
    return buf->get (p, l);
}

CORBA::Boolean
MICO::SimpleDecoder::get_doubles (CORBA::Double *p, CORBA::ULong l)
{
    l *= sizeof (CORBA::Double);
    return buf->get (p, l);
}

CORBA::Boolean
MICO::SimpleDecoder::get_longdoubles (CORBA::LongDouble *p,
				      CORBA::ULong l)
{
    l *= sizeof (CORBA::LongDouble);
    return buf->get (p, l);
}

CORBA::Boolean
MICO::SimpleDecoder::get_chars (CORBA::Char *p, CORBA::ULong l)
{
    return buf->get (p, l);
}

CORBA::Boolean
MICO::SimpleDecoder::get_chars_raw (CORBA::Char *p, CORBA::ULong l)
{
    return buf->get (p, l);
}

CORBA::Boolean
MICO::SimpleDecoder::get_wchars (CORBA::WChar *p, CORBA::ULong l)
{
    l *= sizeof (CORBA::WChar);
    return buf->get (p, l);
}

CORBA::Boolean
MICO::SimpleDecoder::get_booleans (CORBA::Boolean *p, CORBA::ULong l)
{
    return buf->get (p, l);
}

CORBA::Boolean
MICO::SimpleDecoder::get_string (char *&s)
{
    CORBA::ULong len;
    if (!get_ulong (len))
	return FALSE;
    assert (len >= 1);
    s = CORBA::string_alloc (len-1);
    if (!buf->get (s, len)) {
	CORBA::string_free (s);
	return FALSE;
    }
    assert (s[len-1] == 0);
    return TRUE;
}

CORBA::Boolean
MICO::SimpleDecoder::get_string_raw (char *&s)
{
    CORBA::ULong len;
    if (!get_ulong (len))
	return FALSE;
    assert (len >= 1);
    s = CORBA::string_alloc (len-1);
    if (!buf->get (s, len)) {
	CORBA::string_free (s);
	return FALSE;
    }
    assert (s[len-1] == 0);
    return TRUE;
}

CORBA::Boolean
MICO::SimpleDecoder::get_wstring (wchar_t *&s)
{
    CORBA::ULong len;
    if (!get_ulong (len))
	return FALSE;
    assert (len >= 1);
    s = CORBA::wstring_alloc (len-1);
    if (!buf->get (s, len*sizeof(wchar_t))) {
	CORBA::wstring_free (s);
	return FALSE;
    }
    assert (s[len-1] == 0);
    return TRUE;
}

CORBA::Boolean
MICO::SimpleDecoder::get_fixed (FixedBase::FixedValue &value,
				CORBA::UShort digits,
				CORBA::Short scale)
{
    value.length (digits+1);
    return get_octets (&value[0], value.length());
}

CORBA::DataDecoder *
MICO::SimpleDecoder::clone () const
{
    return new SimpleDecoder (new CORBA::Buffer (*buf), TRUE,
			      (conv ? conv->clone() : 0), TRUE,
			      (wconv ? wconv->clone() : 0), TRUE);
}

CORBA::DataDecoder *
MICO::SimpleDecoder::clone (CORBA::Buffer *b, CORBA::Boolean dofree_b,
                            CORBA::CodesetConv *c,
                            CORBA::Boolean dofree_c,
                            CORBA::CodesetConv *wc,
                            CORBA::Boolean dofree_wc,
			    ValueState *vs,
			    CORBA::Boolean dofree_vs) const
{
    return new SimpleDecoder (b, dofree_b, c, dofree_c, wc, dofree_wc,
			      vs, dofree_vs);
}

CORBA::DataEncoder *
MICO::SimpleDecoder::encoder () const
{
    return new SimpleEncoder (new CORBA::Buffer (*buf), TRUE,
			      (conv ? conv->clone() : 0), TRUE,
			      (wconv ? wconv->clone() : 0), TRUE,
			      0, TRUE);
}

CORBA::DataEncoder *
MICO::SimpleDecoder::encoder (CORBA::Buffer *b, CORBA::Boolean dofree_b,
			      CORBA::CodesetConv *c,
			      CORBA::Boolean dofree_c,
			      CORBA::CodesetConv *wc,
			      CORBA::Boolean dofree_wc) const
{
    return new SimpleEncoder (b, dofree_b, c, dofree_c, wc, dofree_wc,
			      0, TRUE);
}

const char *
MICO::SimpleDecoder::type () const
{
    return "simple";
}

CORBA::ULong
MICO::SimpleDecoder::max_alignment () const
{
    return 1;
}


/**************************** CDREncoder ******************************/

static inline void swap2 (void *d, const void *s)
{
    ((CORBA::Octet *)d)[0] = ((CORBA::Octet *)s)[1];
    ((CORBA::Octet *)d)[1] = ((CORBA::Octet *)s)[0];
}

static inline void swap4 (void *d, const void *s)
{
    ((CORBA::Octet *)d)[0] = ((CORBA::Octet *)s)[3];
    ((CORBA::Octet *)d)[1] = ((CORBA::Octet *)s)[2];
    ((CORBA::Octet *)d)[2] = ((CORBA::Octet *)s)[1];
    ((CORBA::Octet *)d)[3] = ((CORBA::Octet *)s)[0];
}

static inline void swap8 (void *d, const void *s)
{
    ((CORBA::Octet *)d)[0] = ((CORBA::Octet *)s)[7];
    ((CORBA::Octet *)d)[1] = ((CORBA::Octet *)s)[6];
    ((CORBA::Octet *)d)[2] = ((CORBA::Octet *)s)[5];
    ((CORBA::Octet *)d)[3] = ((CORBA::Octet *)s)[4];
    ((CORBA::Octet *)d)[4] = ((CORBA::Octet *)s)[3];
    ((CORBA::Octet *)d)[5] = ((CORBA::Octet *)s)[2];
    ((CORBA::Octet *)d)[6] = ((CORBA::Octet *)s)[1];
    ((CORBA::Octet *)d)[7] = ((CORBA::Octet *)s)[0];
}

static inline void swap16 (void *d, const void *s)
{
    ((CORBA::Octet *)d)[0]  = ((CORBA::Octet *)s)[15];
    ((CORBA::Octet *)d)[1]  = ((CORBA::Octet *)s)[14];
    ((CORBA::Octet *)d)[2]  = ((CORBA::Octet *)s)[13];
    ((CORBA::Octet *)d)[3]  = ((CORBA::Octet *)s)[12];
    ((CORBA::Octet *)d)[4]  = ((CORBA::Octet *)s)[11];
    ((CORBA::Octet *)d)[5]  = ((CORBA::Octet *)s)[10];
    ((CORBA::Octet *)d)[6]  = ((CORBA::Octet *)s)[9];
    ((CORBA::Octet *)d)[7]  = ((CORBA::Octet *)s)[8];
    ((CORBA::Octet *)d)[8]  = ((CORBA::Octet *)s)[7];
    ((CORBA::Octet *)d)[9]  = ((CORBA::Octet *)s)[6];
    ((CORBA::Octet *)d)[10] = ((CORBA::Octet *)s)[5];
    ((CORBA::Octet *)d)[11] = ((CORBA::Octet *)s)[4];
    ((CORBA::Octet *)d)[12] = ((CORBA::Octet *)s)[3];
    ((CORBA::Octet *)d)[13] = ((CORBA::Octet *)s)[2];
    ((CORBA::Octet *)d)[14] = ((CORBA::Octet *)s)[1];
    ((CORBA::Octet *)d)[15] = ((CORBA::Octet *)s)[0];
}

MICO::CDREncoder::CDREncoder ()
{
#ifdef HAVE_BYTEORDER_BE
    mach_bo = CORBA::BigEndian;
#else
    mach_bo = CORBA::LittleEndian;
#endif
    data_bo = mach_bo;
}

MICO::CDREncoder::CDREncoder (CORBA::Buffer *b, CORBA::Boolean dofree_b,
			      CORBA::ByteOrder _bo,
                              CORBA::CodesetConv *c, CORBA::Boolean dofree_c,
                              CORBA::CodesetConv *wc, CORBA::Boolean dofree_wc,
			      ValueState *vs, CORBA::Boolean dofree_vs)
    : CORBA::DataEncoder (b, dofree_b, c, dofree_c, wc, dofree_wc,
			  vs, dofree_vs)
{
#ifdef HAVE_BYTEORDER_BE
    mach_bo = CORBA::BigEndian;
#else
    mach_bo = CORBA::LittleEndian;
#endif
    data_bo = (_bo == CORBA::DefaultEndian) ? mach_bo : _bo;
}

MICO::CDREncoder::~CDREncoder ()
{
}

void
MICO::CDREncoder::put_short (CORBA::Short s)
{
    if (mach_bo == data_bo) {
	buf->put2 (&s);
    } else {
	CORBA::Short s2;
	swap2 (&s2, &s);
	buf->put2 (&s2);
    }
}

void
MICO::CDREncoder::put_ushort (CORBA::UShort us)
{
    if (mach_bo == data_bo) {
	buf->put2 (&us);
    } else {
	CORBA::UShort us2;
	swap2 (&us2, &us);
	buf->put2 (&us2);
    }
}

void
MICO::CDREncoder::put_long (CORBA::Long l)
{
    if (mach_bo == data_bo) {
	buf->put4 (&l);
    } else {
	CORBA::Long l2;
	swap4 (&l2, &l);
	buf->put4 (&l2);
    }
}

void
MICO::CDREncoder::put_longlong (CORBA::LongLong l)
{
    if (mach_bo == data_bo) {
	buf->put8 (&l);
    } else {
	CORBA::LongLong l2;
	swap8 (&l2, &l);
	buf->put8 (&l2);
    }
}

void
MICO::CDREncoder::put_ulong (CORBA::ULong ul)
{
    if (mach_bo == data_bo) {
	buf->put4 (&ul);
    } else {
	CORBA::ULong ul2;
	swap4 (&ul2, &ul);
	buf->put4 (&ul2);
    }
}

void
MICO::CDREncoder::put_ulonglong (CORBA::ULongLong ul)
{
    if (mach_bo == data_bo) {
	buf->put8 (&ul);
    } else {
	CORBA::ULongLong ul2;
	swap8 (&ul2, &ul);
	buf->put8 (&ul2);
    }
}

void
MICO::CDREncoder::put_float (CORBA::Float f)
{
#ifdef HAVE_IEEE_FP
    if (mach_bo == data_bo) {
	buf->put4 (&f);
    } else {
	CORBA::Float f2;
	swap4 (&f2, &f);
	buf->put4 (&f2);
    }
#else
    CORBA::Octet b[4];
    mico_float2ieee (b, f);
    if (mach_bo == data_bo) {
	buf->put4 (b);
    } else {
	CORBA::Octet b2[4];
	swap4 (b2, b);
	buf->put4 (b2);
    }
#endif
}

void
MICO::CDREncoder::put_double (CORBA::Double d)
{
#ifdef HAVE_IEEE_FP
    if (mach_bo == data_bo) {
	buf->put8 (&d);
    } else {
	CORBA::Double d2;
	swap8 (&d2, &d);
	buf->put8 (&d2);
    }
#else
    CORBA::Octet b[8];
    mico_double2ieee (b, d);
    if (mach_bo == data_bo) {
	buf->put8 (b);
    } else {
	CORBA::Octet b2[8];
	swap8 (b2, b);
	buf->put8 (b2);
    }
#endif
}

void
MICO::CDREncoder::put_longdouble (CORBA::LongDouble d)
{
#if defined(HAVE_IEEE_FP) && SIZEOF_LONG_DOUBLE == 16
    if (mach_bo == data_bo) {
	buf->put16 (&d);
    } else {
	CORBA::LongDouble d2;
	swap16 (&d2, &d);
	buf->put16 (&d2);
    }
#else
    CORBA::Octet b[16];
    mico_ldouble2ieee (b, d);
    if (mach_bo == data_bo) {
	buf->put16 (b);
    } else {
	CORBA::Octet b2[16];
	swap16 (b2, b);
	buf->put16 (b2);
    }
#endif
}

void
MICO::CDREncoder::put_char (CORBA::Char c)
{
    if (!conv || conv->from()->id() == conv->to()->id()) {
        buf->put1 (&c);
        return;
    }

    CORBA::Long written = conv->encode (&c, 1, *this, FALSE);

    // XXX multibyte chars are not allowed ...
    assert (written == 1);
}

void
MICO::CDREncoder::put_char_raw (CORBA::Char c)
{
    buf->put1 (&c);
}

void
MICO::CDREncoder::put_wchar (CORBA::WChar c)
{
    if (!wconv) {
        // XXX fallback codeset is UTF-16, encoded as unsigned short
        put_ushort ((CORBA::UShort)c);
        return;
    }

    CORBA::Long written = wconv->encode (&c, 1, *this, FALSE);

    // XXX multibyte chars are not allowed ...
    assert (written == 1);
}

void
MICO::CDREncoder::put_octet (CORBA::Octet o)
{
    buf->put1 (&o);
}

void
MICO::CDREncoder::put_boolean (CORBA::Boolean b)
{
    buf->put1 (&b);
}

void
MICO::CDREncoder::put_shorts (const CORBA::Short *p, CORBA::ULong l)
{
    buf->walign (2);
    if (mach_bo == data_bo) {
	buf->put (p, 2*l);
    } else {
	buf->resize (2*l);
	CORBA::Short *d = (CORBA::Short *)buf->wdata();
	for (CORBA::Long i = l; --i >= 0; ++d, ++p)
	    swap2 (d, p);
	buf->wseek_rel (2*l);
    }
}

void
MICO::CDREncoder::put_ushorts (const CORBA::UShort *p, CORBA::ULong l)
{
    buf->walign (2);
    if (mach_bo == data_bo) {
	buf->put (p, 2*l);
    } else {
	buf->resize (2*l);
	CORBA::UShort *d = (CORBA::UShort *)buf->wdata();
	for (CORBA::Long i = l; --i >= 0; ++d, ++p)
	    swap2 (d, p);
	buf->wseek_rel (2*l);
    }
}

void
MICO::CDREncoder::put_longs (const CORBA::Long *p, CORBA::ULong l)
{
    buf->walign (4);
    if (mach_bo == data_bo) {
	buf->put (p, 4*l);
    } else {
	buf->resize (4*l);
	CORBA::Long *d = (CORBA::Long *)buf->wdata();
	for (CORBA::Long i = l; --i >= 0; ++d, ++p)
	    swap4 (d, p);
	buf->wseek_rel (4*l);
    }
}

void
MICO::CDREncoder::put_longlongs (const CORBA::LongLong *p, CORBA::ULong l)
{
    buf->walign (8);
    if (mach_bo == data_bo) {
	buf->put (p, 8*l);
    } else {
	buf->resize (8*l);
	CORBA::LongLong *d = (CORBA::LongLong *)buf->wdata();
	for (CORBA::Long i = l; --i >= 0; ++d, ++p)
	    swap8 (d, p);
	buf->wseek_rel (8*l);
    }
}

void
MICO::CDREncoder::put_ulongs (const CORBA::ULong *p, CORBA::ULong l)
{
    buf->walign (4);
    if (mach_bo == data_bo) {
	buf->put (p, 4*l);
    } else {
	buf->resize (4*l);
	CORBA::ULong *d = (CORBA::ULong *)buf->wdata();
	for (CORBA::Long i = l; --i >= 0; ++d, ++p)
	    swap4 (d, p);
	buf->wseek_rel (4*l);
    }
}

void
MICO::CDREncoder::put_ulonglongs (const CORBA::ULongLong *p, CORBA::ULong l)
{
    buf->walign (8);
    if (mach_bo == data_bo) {
	buf->put (p, 8*l);
    } else {
	buf->resize (8*l);
	CORBA::ULongLong *d = (CORBA::ULongLong *)buf->wdata();
	for (CORBA::Long i = l; --i >= 0; ++d, ++p)
	    swap8 (d, p);
	buf->wseek_rel (8*l);
    }
}

void
MICO::CDREncoder::put_floats (const CORBA::Float *p, CORBA::ULong l)
{
    for (CORBA::Long i = l; --i >= 0; ++p)
	put_float (*p);
}

void
MICO::CDREncoder::put_doubles (const CORBA::Double *p, CORBA::ULong l)
{
    for (CORBA::Long i = l; --i >= 0; ++p)
	put_double (*p);
}

void
MICO::CDREncoder::put_longdoubles (const CORBA::LongDouble *p, CORBA::ULong l)
{
    for (CORBA::Long i = l; --i >= 0; ++p)
	put_longdouble (*p);
}

void
MICO::CDREncoder::put_chars (const CORBA::Char *p, CORBA::ULong l)
{
    for (CORBA::Long i = l; --i >= 0; ++p)
	put_char (*p);
}

void
MICO::CDREncoder::put_chars_raw (const CORBA::Char *p, CORBA::ULong l)
{
    buf->put (p, l);
}

void
MICO::CDREncoder::put_wchars (const CORBA::WChar *p, CORBA::ULong l)
{
    for (CORBA::Long i = l; --i >= 0; ++p)
	put_wchar (*p);
}

void
MICO::CDREncoder::put_booleans (const CORBA::Boolean *p, CORBA::ULong l)
{
    buf->put (p, l);
}

void
MICO::CDREncoder::put_string (const char *s)
{
    if (!conv || conv->from()->id() == conv->to()->id()) {
        CORBA::ULong len = strlen (s) + 1;
        put_ulong (len);
        put_octets (s, len);
        return;
    }

    DelayedSeqState state;
    delayed_seq_begin (state);
    CORBA::Long written = conv->encode ((CORBA::Char *)s, strlen (s), *this);
    assert (written >= 0);
    delayed_seq_end (state, written);
}

void
MICO::CDREncoder::put_string_raw (const char *s)
{
    CORBA::ULong len = strlen (s) + 1;
    put_ulong (len);
    put_octets (s, len);
}

void
MICO::CDREncoder::put_wstring (const wchar_t *s)
{
    if (!wconv) {
        CORBA::ULong len = xwcslen (s) + 1;
        put_ulong (len);
        for (CORBA::ULong i = 0; i < len; ++i)
            // fallback codeset is UTF-16
            put_ushort (s[i]);
        return;
    }

    DelayedSeqState state;
    delayed_seq_begin (state);
    CORBA::Long written = wconv->encode ((CORBA::WChar *)s, xwcslen (s),*this);
    assert (written >= 0);
    delayed_seq_end (state, written);
}

void
MICO::CDREncoder::put_fixed (const FixedBase::FixedValue &value,
			     CORBA::UShort digits,
			     CORBA::Short scale)
{
    assert (value.length() == (CORBA::ULong)digits+1);

    int s = 0, n = value.length();

    if (n == 1) {
	put_octet ((CORBA::Octet)value[0] ? 0xd : 0xc);
	return;
    }
    if ((n & 1)) {
	put_octet ((CORBA::Octet)value[0]);
	s = 1;
    }
    for (int i = s; i < n-2; i+=2)
	put_octet (((CORBA::Octet)value[i] << 4) | (CORBA::Octet)value[i+1]);
    put_octet (((CORBA::Octet)value[n-2] << 4) |
	       ((CORBA::Octet)value[n-1] ? 0xd : 0xc));
}

CORBA::DataEncoder *
MICO::CDREncoder::clone () const
{
    return new CDREncoder (new CORBA::Buffer (*buf), TRUE, data_bo,
			   (conv ? conv->clone() : 0), TRUE,
			   (wconv ? wconv->clone() : 0), TRUE,
			   (vstate ? new ValueState (*vstate) : 0), TRUE);
}

CORBA::DataEncoder *
MICO::CDREncoder::clone (CORBA::Buffer *b, CORBA::Boolean dofree_b,
                         CORBA::CodesetConv *c, CORBA::Boolean dofree_c,
                         CORBA::CodesetConv *wc,
			 CORBA::Boolean dofree_wc,
			 ValueState *vs, CORBA::Boolean dofree_vs) const
{
    return new CDREncoder (b, dofree_b, data_bo, c, dofree_c, wc, dofree_wc,
			   vs, dofree_vs);
}

CORBA::DataDecoder *
MICO::CDREncoder::decoder () const
{
    return new CDRDecoder (new CORBA::Buffer (*buf), TRUE, data_bo,
			   (conv ? conv->clone() : 0), TRUE,
			   (wconv ? wconv->clone() : 0), TRUE,
			   0, TRUE);
}

CORBA::DataDecoder *
MICO::CDREncoder::decoder (CORBA::Buffer *b, CORBA::Boolean dofree_b,
			   CORBA::CodesetConv *c, CORBA::Boolean dofree_c,
			   CORBA::CodesetConv *wc,
			   CORBA::Boolean dofree_wc) const
{
    return new CDRDecoder (b, dofree_b, data_bo, c, dofree_c, wc, dofree_wc,
			   0, TRUE);
}

const char *
MICO::CDREncoder::type () const
{
    return "cdr";
}

CORBA::ByteOrder
MICO::CDREncoder::byteorder () const
{
    return data_bo;
}

void
MICO::CDREncoder::byteorder (CORBA::ByteOrder _bo)
{
    data_bo = _bo;
}

CORBA::ULong
MICO::CDREncoder::max_alignment () const
{
    return 8;
}


/**************************** CDRDecoder ******************************/


MICO::CDRDecoder::CDRDecoder ()
    : CORBA::DataDecoder (new CORBA::Buffer, TRUE)
{
#ifdef HAVE_BYTEORDER_BE
    mach_bo = CORBA::BigEndian;
#else
    mach_bo = CORBA::LittleEndian;
#endif
    data_bo = mach_bo;
}

MICO::CDRDecoder::CDRDecoder (CORBA::Buffer *b, CORBA::Boolean dofree_b,
			      CORBA::ByteOrder _bo,
                              CORBA::CodesetConv *c, CORBA::Boolean dofree_c,
                              CORBA::CodesetConv *wc, CORBA::Boolean dofree_wc,
			      ValueState *vs, CORBA::Boolean dofree_vs)
    : CORBA::DataDecoder (b, dofree_b, c, dofree_c, wc, dofree_wc,
			  vs, dofree_vs)
{
#ifdef HAVE_BYTEORDER_BE
    mach_bo = CORBA::BigEndian;
#else
    mach_bo = CORBA::LittleEndian;
#endif
    data_bo = (_bo == CORBA::DefaultEndian) ? mach_bo : _bo;
}

MICO::CDRDecoder::~CDRDecoder ()
{
}

CORBA::Boolean
MICO::CDRDecoder::get_short (CORBA::Short &s)
{
    if (data_bo == mach_bo)
	return buf->get2 (&s);

    CORBA::Short s2;
    if (!buf->get2 (&s2))
	return FALSE;
    swap2 (&s, &s2);
    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_ushort (CORBA::UShort &us)
{
    if (data_bo == mach_bo)
	return buf->get2 (&us);

    CORBA::UShort us2;
    if (!buf->get2 (&us2))
	return FALSE;
    swap2 (&us, &us2);
    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_long (CORBA::Long &l)
{
    if (data_bo == mach_bo)
	return buf->get4 (&l);

    CORBA::Long l2;
    if (!buf->get4 (&l2))
	return FALSE;
    swap4 (&l, &l2);
    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_longlong (CORBA::LongLong &l)
{
    if (data_bo == mach_bo)
	return buf->get8 (&l);

    CORBA::LongLong l2;
    if (!buf->get8 (&l2))
	return FALSE;
    swap8 (&l, &l2);
    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_ulong (CORBA::ULong &ul)
{
    if (data_bo == mach_bo)
	return buf->get4 (&ul);

    CORBA::ULong ul2;
    if (!buf->get4 (&ul2))
	return FALSE;
    swap4 (&ul, &ul2);
    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_ulonglong (CORBA::ULongLong &ul)
{
    if (data_bo == mach_bo)
	return buf->get8 (&ul);

    CORBA::ULongLong ul2;
    if (!buf->get8 (&ul2))
	return FALSE;
    swap8 (&ul, &ul2);
    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_float (CORBA::Float &f)
{
#ifdef HAVE_IEEE_FP
    if (data_bo == mach_bo)
	return buf->get4 (&f);

    CORBA::Float f2;
    if (!buf->get4 (&f2))
	return FALSE;
    swap4 (&f, &f2);
#else
    CORBA::Octet b[4];
    if (data_bo == mach_bo) {
	if (!buf->get4 (b))
	    return FALSE;
	mico_ieee2float (b, f);
	return TRUE;
    }

    CORBA::Octet b2[4];
    if (!buf->get4 (b2))
	return FALSE;
    swap4 (&b, &b2);
    mico_ieee2float (b, f);
#endif
    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_double (CORBA::Double &d)
{
#ifdef HAVE_IEEE_FP
    if (data_bo == mach_bo)
	return buf->get8 (&d);

    CORBA::Double d2;
    if (!buf->get8 (&d2))
	return FALSE;
    swap8 (&d, &d2);
#else
    CORBA::Octet b[8];
    if (data_bo == mach_bo) {
	if (!buf->get8 (b))
	    return FALSE;
	mico_ieee2double (b, d);
	return TRUE;
    }

    CORBA::Octet b2[8];
    if (!buf->get8 (b2))
	return FALSE;
    swap8 (&b, &b2);
    mico_ieee2double (b, d);
#endif
    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_longdouble (CORBA::LongDouble &d)
{
#if defined(HAVE_IEEE_FP) && SIZEOF_LONG_DOUBLE == 16
    if (data_bo == mach_bo)
	return buf->get16 (&d);

    CORBA::LongDouble d2;
    if (!buf->get16 (&d2))
	return FALSE;
    swap16 (&d, &d2);
#else
    CORBA::Octet b[16];
    if (data_bo == mach_bo) {
	if (!buf->get16 (b))
	    return FALSE;
	mico_ieee2ldouble (b, d);
	return TRUE;
    }

    CORBA::Octet b2[16];
    if (!buf->get16 (b2))
	return FALSE;
    swap16 (&b, &b2);
    mico_ieee2ldouble (b, d);
#endif
    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_char (CORBA::Char &c)
{
    if (!conv || conv->from()->id() == conv->to()->id()) {
        return buf->get1 (&c);
    }

    assert (conv->to()->max_codepoints() <= 25);
    CORBA::Char to[50];

    // XXX only one byte characters allowed ...
    CORBA::Long read = conv->decode (*this, 1, to, FALSE);
    if (read < 0)
	return FALSE;

    c = *to;

    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_char_raw (CORBA::Char &c)
{
    return buf->get1 (&c);
}

CORBA::Boolean
MICO::CDRDecoder::get_wchar (CORBA::WChar &c)
{
    if (!wconv) {
        // XXX fallback codeset is UTF-16, encoded as unsigned short
        CORBA::UShort us;
        if (!get_ushort (us))
            return FALSE;
        c = (CORBA::WChar)us;
        return TRUE;
    }

    assert (wconv->to()->max_codepoints() <= 25);
    CORBA::WChar to[50];

    // XXX only one byte characters allowed ...
    CORBA::Long read = wconv->decode (*this, 1, to, FALSE);
    if (read < 0)
	return FALSE;

    c = *to;

    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_octet (CORBA::Octet &o)
{
    return buf->get1 (&o);
}

CORBA::Boolean
MICO::CDRDecoder::get_boolean (CORBA::Boolean &b)
{
    return buf->get1 (&b);
}

CORBA::Boolean
MICO::CDRDecoder::get_shorts (CORBA::Short *p, CORBA::ULong l)
{
    if (!buf->ralign (2))
	return FALSE;

    if (data_bo == mach_bo)
	return buf->get (p, 2*l);

    if (buf->length() < 2*l)
	return FALSE;

    CORBA::Short *s = (CORBA::Short *)buf->data();
    for (CORBA::Long i = l; --i >= 0; ++p, ++s)
	swap2 (p, s);
    buf->rseek_rel (2*l);

    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_ushorts (CORBA::UShort *p, CORBA::ULong l)
{
    if (!buf->ralign (2))
	return FALSE;

    if (data_bo == mach_bo)
	return buf->get (p, 2*l);

    if (buf->length() < 2*l)
	return FALSE;

    CORBA::UShort *s = (CORBA::UShort *)buf->data();
    for (CORBA::Long i = l; --i >= 0; ++p, ++s)
	swap2 (p, s);
    buf->rseek_rel (2*l);

    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_longs (CORBA::Long *p, CORBA::ULong l)
{
    if (!buf->ralign (4))
	return FALSE;

    if (data_bo == mach_bo)
	return buf->get (p, 4*l);

    if (buf->length() < 4*l)
	return FALSE;

    CORBA::Long *s = (CORBA::Long *)buf->data();
    for (CORBA::Long i = l; --i >= 0; ++p, ++s)
	swap4 (p, s);
    buf->rseek_rel (4*l);

    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_longlongs (CORBA::LongLong *p, CORBA::ULong l)
{
    if (!buf->ralign (8))
	return FALSE;

    if (data_bo == mach_bo)
	return buf->get (p, 8*l);

    if (buf->length() < 8*l)
	return FALSE;

    CORBA::LongLong *s = (CORBA::LongLong *)buf->data();
    for (CORBA::Long i = l; --i >= 0; ++p, ++s)
	swap8 (p, s);
    buf->rseek_rel (8*l);

    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_ulongs (CORBA::ULong *p, CORBA::ULong l)
{
    if (!buf->ralign (4))
	return FALSE;

    if (data_bo == mach_bo)
	return buf->get (p, 4*l);

    if (buf->length() < 4*l)
	return FALSE;

    CORBA::ULong *s = (CORBA::ULong *)buf->data();
    for (CORBA::Long i = l; --i >= 0; ++p, ++s)
	swap4 (p, s);
    buf->rseek_rel (4*l);

    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_ulonglongs (CORBA::ULongLong *p, CORBA::ULong l)
{
    if (!buf->ralign (8))
	return FALSE;

    if (data_bo == mach_bo)
	return buf->get (p, 8*l);

    if (buf->length() < 8*l)
	return FALSE;

    CORBA::ULongLong *s = (CORBA::ULongLong *)buf->data();
    for (CORBA::Long i = l; --i >= 0; ++p, ++s)
	swap8 (p, s);
    buf->rseek_rel (8*l);

    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_floats (CORBA::Float *p, CORBA::ULong l)
{
    for (CORBA::Long i = l; --i >= 0; ++p) {
	if (!get_float (*p))
	    return FALSE;
    }
    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_doubles (CORBA::Double *p, CORBA::ULong l)
{
    for (CORBA::Long i = l; --i >= 0; ++p) {
	if (!get_double (*p))
	    return FALSE;
    }
    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_longdoubles (CORBA::LongDouble *p, CORBA::ULong l)
{
    for (CORBA::Long i = l; --i >= 0; ++p) {
	if (!get_longdouble (*p))
	    return FALSE;
    }
    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_chars (CORBA::Char *p, CORBA::ULong l)
{
    for (CORBA::Long i = l; --i >= 0; ++p) {
	if (!get_char (*p))
	    return FALSE;
    }
    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_chars_raw (CORBA::Char *p, CORBA::ULong l)
{
    return buf->get (p, l);
}

CORBA::Boolean
MICO::CDRDecoder::get_wchars (CORBA::WChar *p, CORBA::ULong l)
{
    for (CORBA::Long i = l; --i >= 0; ++p) {
	if (!get_wchar (*p))
	    return FALSE;
    }
    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_booleans (CORBA::Boolean *p, CORBA::ULong l)
{
    return buf->get (p, l);
}

CORBA::Boolean
MICO::CDRDecoder::get_string (char *&s)
{
    CORBA::ULong len;
    if (!get_ulong (len))
        return FALSE;
    assert (len >= 1);

    if (!conv || conv->from()->id() == conv->to()->id()) {
        s = CORBA::string_alloc (len-1);
        if (!buf->get (s, len)) {
            CORBA::string_free (s);
            return FALSE;
        }
        assert (s[len-1] == 0);
        return TRUE;
    }

    s = CORBA::string_alloc (conv->to()->guess_size (len-1));

    CORBA::Long read = conv->decode (*this, len, (CORBA::Char *)s, FALSE);
    if (read < 0)
	return FALSE;

    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_string_raw (char *&s)
{
    CORBA::ULong len;
    if (!get_ulong (len))
        return FALSE;
    assert (len >= 1);

    s = CORBA::string_alloc (len-1);
    if (!buf->get (s, len)) {
	CORBA::string_free (s);
	return FALSE;
    }
    assert (s[len-1] == 0);
    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_wstring (wchar_t *&s)
{
    CORBA::ULong len;
    if (!get_ulong (len))
        return FALSE;
    assert (len >= 1);

    if (!wconv) {
        s = CORBA::wstring_alloc (len-1);
	CORBA::UShort u;
        for (CORBA::ULong i = 0; i < len; ++i) {
            // default code set if UTF-16 ...
            if (!get_ushort (u)) {
                CORBA::wstring_free (s);
                return FALSE;
            }
            s[i] = u;
        }
        assert (s[len-1] == 0);
        return TRUE;
    }

    s = CORBA::wstring_alloc (wconv->to()->guess_size (len-1));

    CORBA::Long read = wconv->decode (*this, len, (CORBA::WChar *)s, FALSE);
    if (read < 0)
	return FALSE;

    return TRUE;
}

CORBA::Boolean
MICO::CDRDecoder::get_fixed (FixedBase::FixedValue &value,
			     CORBA::UShort digits,
			     CORBA::Short scale)
{
    value.length (digits+1);

    int s = 0, n = value.length();
    CORBA::Octet o;

    if (n == 1) {
	if (!get_octet (o))
	    return FALSE;
	value[0] = ((o & 0xf) == 0xd);
	return TRUE;
    }
    if ((n & 1)) {
	if (!get_octet (o))
	    return FALSE;
	value[0] = (o & 0xf);
	s = 1;
    }
    for (int i = s; i < n-2; i+=2) {
	if (!get_octet (o))
	    return FALSE;
	value[i] = ((o >> 4) & 0xf);
	value[i+1] = (o & 0xf);
    }
    if (!get_octet (o))
	return FALSE;
    value[n-2] = ((o >> 4) & 0xf);
    value[n-1] = ((o & 0xf) == 0xd);
    return TRUE;
}

CORBA::DataDecoder *
MICO::CDRDecoder::clone () const
{
    return new CDRDecoder (new CORBA::Buffer (*buf), TRUE, data_bo,
			   (conv ? conv->clone() : 0), TRUE,
			   (wconv ? wconv->clone() : 0), TRUE,
			   (vstate ? new ValueState (*vstate) : 0), TRUE);
}

CORBA::DataDecoder *
MICO::CDRDecoder::clone (CORBA::Buffer *b, CORBA::Boolean dofree_b,
                         CORBA::CodesetConv *c, CORBA::Boolean dofree_c,
                         CORBA::CodesetConv *wc,
			 CORBA::Boolean dofree_wc,
			 ValueState *vs,
			 CORBA::Boolean dofree_vs) const
{
    return new CDRDecoder (b, dofree_b, data_bo, c, dofree_c, wc, dofree_wc,
			   vs, dofree_vs);
}

CORBA::DataEncoder *
MICO::CDRDecoder::encoder () const
{
    return new CDREncoder (new CORBA::Buffer (*buf), TRUE, data_bo,
			   (conv ? conv->clone() : 0), TRUE,
			   (wconv ? wconv->clone() : 0), TRUE,
			   0, TRUE);
}

CORBA::DataEncoder *
MICO::CDRDecoder::encoder (CORBA::Buffer *b, CORBA::Boolean dofree_b,
			   CORBA::CodesetConv *c, CORBA::Boolean dofree_c,
			   CORBA::CodesetConv *wc,
			   CORBA::Boolean dofree_wc) const
{
    return new CDREncoder (b, dofree_b, data_bo, c, dofree_c, wc, dofree_wc,
			   0, TRUE);
}

const char *
MICO::CDRDecoder::type () const
{
    return "cdr";
}

CORBA::ByteOrder
MICO::CDRDecoder::byteorder () const
{
    return data_bo;
}

void
MICO::CDRDecoder::byteorder (CORBA::ByteOrder _bo)
{
    data_bo = _bo;
}

CORBA::ULong
MICO::CDRDecoder::max_alignment () const
{
    return 8;
}

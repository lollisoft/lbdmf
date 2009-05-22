
-- Class Currency of type FORM found.
				
-- Class Cobmisc of type FORM found.
				
-- Class Cohead of type FORM found.
				
-- Class cobmisc of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table cobmisc for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE cobmisc
CREATE TABLE "cobmisc" (
	"cobmisc_id" INTEGER PRIMARY KEY,
	"cobmisc_cohead_id" INTEGER,
	"cobmisc_shipvia" TEXT,
	"cobmisc_paymentref" TEXT,
	"cobmisc_notes" TEXT,
	"cobmisc_invcnumber" INTEGER,
	"cobmisc_posted" BOOLEAN,
	"cobmisc_misc_accnt_id" INTEGER,
	"cobmisc_misc_descrip" TEXT,
	"cobmisc_closeorder" BOOLEAN,
	"cobmisc_curr_id" INTEGER,
	"cobmisc_invchead_id" INTEGER,
	"cobmisc_taxauth_id" INTEGER,
	"cobmisc_tax_curr_id" INTEGER,
	"cobmisc_adjtax_id" INTEGER,
	"cobmisc_adjtaxtype_id" INTEGER,
	"cobmisc_freighttax_id" INTEGER,
	"cobmisc_freighttaxtype_id" INTEGER
);

-- Class cohead of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table cohead for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE cohead
CREATE TABLE "cohead" (
	"cohead_id" INTEGER PRIMARY KEY,
	"cohead_number" TEXT,
	"cohead_cust_id" INTEGER,
	"cohead_custponumber" TEXT,
	"cohead_type" BPCHAR,
	"cohead_warehous_id" INTEGER,
	"cohead_shipto_id" INTEGER,
	"cohead_shiptoname" TEXT,
	"cohead_shiptoaddress1" TEXT,
	"cohead_shiptoaddress2" TEXT,
	"cohead_shiptoaddress3" TEXT,
	"cohead_shiptoaddress4" TEXT,
	"cohead_shiptoaddress5" TEXT,
	"cohead_salesrep_id" INTEGER,
	"cohead_terms_id" INTEGER,
	"cohead_origin" BPCHAR,
	"cohead_fob" TEXT,
	"cohead_shipvia" TEXT,
	"cohead_shiptocity" TEXT,
	"cohead_shiptostate" TEXT,
	"cohead_shiptozipcode" TEXT,
	"cohead_imported" BOOLEAN,
	"cohead_ordercomments" TEXT,
	"cohead_shipcomments" TEXT,
	"cohead_shiptophone" TEXT,
	"cohead_shipchrg_id" INTEGER,
	"cohead_shipform_id" INTEGER,
	"cohead_billtoname" TEXT,
	"cohead_billtoaddress1" TEXT,
	"cohead_billtoaddress2" TEXT,
	"cohead_billtoaddress3" TEXT,
	"cohead_billtocity" TEXT,
	"cohead_billtostate" TEXT,
	"cohead_billtozipcode" TEXT,
	"cohead_misc_accnt_id" INTEGER,
	"cohead_misc_descrip" TEXT,
	"cohead_holdtype" BPCHAR,
	"cohead_prj_id" INTEGER,
	"cohead_wasquote" BOOLEAN,
	"cohead_shipcomplete" BOOLEAN,
	"cohead_creator" TEXT,
	"cohead_quote_number" TEXT,
	"cohead_billtocountry" TEXT,
	"cohead_shiptocountry" TEXT,
	"cohead_curr_id" INTEGER,
	"cohead_taxauth_id" INTEGER,
	"cohead_calcfreight" BOOLEAN,
	"cohead_shipto_cntct_id" INTEGER,
	"cohead_shipto_cntct_honorific" TEXT,
	"cohead_shipto_cntct_first_name" TEXT,
	"cohead_shipto_cntct_middle" TEXT,
	"cohead_shipto_cntct_last_name" TEXT,
	"cohead_shipto_cntct_suffix" TEXT,
	"cohead_shipto_cntct_phone" TEXT,
	"cohead_shipto_cntct_title" TEXT,
	"cohead_shipto_cntct_fax" TEXT,
	"cohead_shipto_cntct_email" TEXT,
	"cohead_billto_cntct_id" INTEGER,
	"cohead_billto_cntct_honorific" TEXT,
	"cohead_billto_cntct_first_name" TEXT,
	"cohead_billto_cntct_middle" TEXT,
	"cohead_billto_cntct_last_name" TEXT,
	"cohead_billto_cntct_suffix" TEXT,
	"cohead_billto_cntct_phone" TEXT,
	"cohead_billto_cntct_title" TEXT,
	"cohead_billto_cntct_fax" TEXT,
	"cohead_billto_cntct_email" TEXT
);

-- Class curr_symbol of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table curr_symbol for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE curr_symbol
CREATE TABLE "curr_symbol" (
	"curr_id" INTEGER PRIMARY KEY,
	"curr_base" BOOLEAN,
	"curr_name" TEXT,
	"curr_symbol" TEXT,
	"curr_abbr" TEXT
);

-- Class acalitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table acalitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE acalitem
CREATE TABLE "acalitem" (
	"acalitem_id" INTEGER PRIMARY KEY,
	"acalitem_calhead_id" INTEGER,
	"acalitem_periodlength" INTEGER,
	"acalitem_name" TEXT
);

-- Class accnt of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table accnt for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE accnt
CREATE TABLE "accnt" (
	"accnt_id" INTEGER PRIMARY KEY,
	"accnt_number" TEXT,
	"accnt_descrip" TEXT,
	"accnt_comments" TEXT,
	"accnt_profit" TEXT,
	"accnt_sub" TEXT,
	"accnt_type" BPCHAR,
	"accnt_extref" TEXT,
	"accnt_company" TEXT,
	"accnt_closedpost" BOOLEAN,
	"accnt_forwardupdate" BOOLEAN,
	"accnt_subaccnttype_code" TEXT,
	"accnt_curr_id" INTEGER
);

-- Class addr of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table addr for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE addr
CREATE TABLE "addr" (
	"addr_id" INTEGER PRIMARY KEY,
	"addr_active" BOOLEAN,
	"addr_line1" TEXT,
	"addr_line2" TEXT,
	"addr_line3" TEXT,
	"addr_city" TEXT,
	"addr_state" TEXT,
	"addr_postalcode" TEXT,
	"addr_country" TEXT,
	"addr_notes" TEXT,
	"addr_number" TEXT
);

-- Class alarm of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table alarm for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE alarm
CREATE TABLE "alarm" (
	"alarm_id" INTEGER PRIMARY KEY,
	"alarm_number" TEXT,
	"alarm_event" BOOLEAN,
	"alarm_email" BOOLEAN,
	"alarm_sysmsg" BOOLEAN,
	"alarm_time_offset" INTEGER,
	"alarm_time_qualifier" TEXT,
	"alarm_creator" TEXT,
	"alarm_event_recipient" TEXT,
	"alarm_email_recipient" TEXT,
	"alarm_sysmsg_recipient" TEXT,
	"alarm_source" TEXT,
	"alarm_source_id" INTEGER
);

-- Class apaccnt of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table apaccnt for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE apaccnt
CREATE TABLE "apaccnt" (
	"apaccnt_id" INTEGER PRIMARY KEY,
	"apaccnt_vendtype_id" INTEGER,
	"apaccnt_vendtype" TEXT,
	"apaccnt_ap_accnt_id" INTEGER,
	"apaccnt_prepaid_accnt_id" INTEGER,
	"apaccnt_discount_accnt_id" INTEGER
);

-- Class apapply of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table apapply for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE apapply
CREATE TABLE "apapply" (
	"apapply_id" INTEGER PRIMARY KEY,
	"apapply_vend_id" INTEGER,
	"apapply_username" TEXT,
	"apapply_source_apopen_id" INTEGER,
	"apapply_source_doctype" TEXT,
	"apapply_source_docnumber" TEXT,
	"apapply_target_apopen_id" INTEGER,
	"apapply_target_doctype" TEXT,
	"apapply_target_docnumber" TEXT,
	"apapply_journalnumber" INTEGER,
	"apapply_curr_id" INTEGER
);

-- Class apchk of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table apchk for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE apchk
CREATE TABLE "apchk" (
	"apchk_id" INTEGER,
	"apchk_vend_id" INTEGER,
	"apchk_bankaccnt_id" INTEGER,
	"apchk_printed" BOOLEAN,
	"apchk_number" INTEGER,
	"apchk_void" BOOLEAN,
	"apchk_replaced" BOOLEAN,
	"apchk_posted" BOOLEAN,
	"apchk_rec" BOOLEAN,
	"apchk_misc" BOOLEAN,
	"apchk_expcat_id" INTEGER,
	"apchk_for" TEXT,
	"apchk_notes" TEXT,
	"apchk_journalnumber" INTEGER,
	"apchk_curr_id" INTEGER,
	"apchk_deleted" BOOLEAN
);

-- Class apchkitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table apchkitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE apchkitem
CREATE TABLE "apchkitem" (
	"apchkitem_id" INTEGER,
	"apchkitem_apchk_id" INTEGER,
	"apchkitem_vouchernumber" TEXT,
	"apchkitem_ponumber" TEXT,
	"apchkitem_invcnumber" TEXT,
	"apchkitem_apopen_id" INTEGER,
	"apchkitem_curr_id" INTEGER
);

-- Class apcreditapply of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table apcreditapply for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE apcreditapply
CREATE TABLE "apcreditapply" (
	"apcreditapply_id" INTEGER PRIMARY KEY,
	"apcreditapply_source_apopen_id" INTEGER,
	"apcreditapply_target_apopen_id" INTEGER,
	"apcreditapply_curr_id" INTEGER
);

-- Class apopen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table apopen for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE apopen
CREATE TABLE "apopen" (
	"apopen_id" INTEGER PRIMARY KEY,
	"apopen_terms_id" INTEGER,
	"apopen_vend_id" INTEGER,
	"apopen_doctype" BPCHAR,
	"apopen_docnumber" TEXT,
	"apopen_notes" TEXT,
	"apopen_posted" BOOLEAN,
	"apopen_reference" TEXT,
	"apopen_invcnumber" TEXT,
	"apopen_ponumber" TEXT,
	"apopen_journalnumber" INTEGER,
	"apopen_open" BOOLEAN,
	"apopen_username" TEXT,
	"apopen_discount" BOOLEAN,
	"apopen_accnt_id" INTEGER,
	"apopen_curr_id" INTEGER,
	"apopen_void" BOOLEAN
);

-- Class apselect of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table apselect for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE apselect
CREATE TABLE "apselect" (
	"apselect_id" INTEGER PRIMARY KEY,
	"apselect_apopen_id" INTEGER,
	"apselect_bankaccnt_id" INTEGER,
	"apselect_curr_id" INTEGER
);

-- Class araccnt of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table araccnt for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE araccnt
CREATE TABLE "araccnt" (
	"araccnt_id" INTEGER PRIMARY KEY,
	"araccnt_custtype_id" INTEGER,
	"araccnt_custtype" TEXT,
	"araccnt_freight_accnt_id" INTEGER,
	"araccnt_ar_accnt_id" INTEGER,
	"araccnt_prepaid_accnt_id" INTEGER,
	"araccnt_deferred_accnt_id" INTEGER
);

-- Class arapply of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table arapply for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE arapply
CREATE TABLE "arapply" (
	"arapply_id" INTEGER PRIMARY KEY,
	"arapply_cust_id" INTEGER,
	"arapply_source_doctype" TEXT,
	"arapply_source_docnumber" TEXT,
	"arapply_target_doctype" TEXT,
	"arapply_target_docnumber" TEXT,
	"arapply_fundstype" TEXT,
	"arapply_refnumber" TEXT,
	"arapply_closed" BOOLEAN,
	"arapply_journalnumber" TEXT,
	"arapply_source_aropen_id" INTEGER,
	"arapply_target_aropen_id" INTEGER,
	"arapply_username" TEXT,
	"arapply_curr_id" INTEGER
);

-- Class arcreditapply of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table arcreditapply for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE arcreditapply
CREATE TABLE "arcreditapply" (
	"arcreditapply_id" INTEGER PRIMARY KEY,
	"arcreditapply_source_aropen_id" INTEGER,
	"arcreditapply_target_aropen_id" INTEGER,
	"arcreditapply_curr_id" INTEGER
);

-- Class armemo of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table armemo for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE armemo
CREATE TABLE "armemo" (
	"armemo_id" INTEGER PRIMARY KEY,
	"armemo_cust_id" INTEGER,
	"armemo_docnumber" TEXT,
	"armemo_accnt_id" INTEGER,
	"armemo_comments" TEXT,
	"armemo_curr_id" INTEGER
);

-- Class aropen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table aropen for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE aropen
CREATE TABLE "aropen" (
	"aropen_id" INTEGER PRIMARY KEY,
	"aropen_terms_id" INTEGER,
	"aropen_cust_id" INTEGER,
	"aropen_doctype" BPCHAR,
	"aropen_docnumber" TEXT,
	"aropen_applyto" TEXT,
	"aropen_ponumber" TEXT,
	"aropen_notes" TEXT,
	"aropen_posted" BOOLEAN,
	"aropen_salesrep_id" INTEGER,
	"aropen_commission_paid" BOOLEAN,
	"aropen_ordernumber" TEXT,
	"aropen_cobmisc_id" INTEGER,
	"aropen_journalnumber" INTEGER,
	"aropen_open" BOOLEAN,
	"aropen_username" TEXT,
	"aropen_rsncode_id" INTEGER,
	"aropen_salescat_id" INTEGER,
	"aropen_accnt_id" INTEGER,
	"aropen_curr_id" INTEGER
);

-- Class aropenco of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table aropenco for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE aropenco
CREATE TABLE "aropenco" (
	"aropenco_aropen_id" INTEGER PRIMARY KEY,
	"aropenco_cohead_id" INTEGER,
	"aropenco_curr_id" INTEGER
);

-- Class asohist of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table asohist for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE asohist
CREATE TABLE "asohist" (
	"asohist_id" INTEGER PRIMARY KEY,
	"asohist_cust_id" INTEGER,
	"asohist_itemsite_id" INTEGER,
	"asohist_ordernumber" TEXT,
	"asohist_invcnumber" TEXT,
	"asohist_billtoname" TEXT,
	"asohist_billtoaddress1" TEXT,
	"asohist_billtoaddress2" TEXT,
	"asohist_billtoaddress3" TEXT,
	"asohist_billtocity" TEXT,
	"asohist_billtostate" TEXT,
	"asohist_billtozip" TEXT,
	"asohist_shiptoname" TEXT,
	"asohist_shiptoaddress1" TEXT,
	"asohist_shiptoaddress2" TEXT,
	"asohist_shiptoaddress3" TEXT,
	"asohist_shiptocity" TEXT,
	"asohist_shiptostate" TEXT,
	"asohist_shiptozip" TEXT,
	"asohist_shipto_id" INTEGER,
	"asohist_shipvia" TEXT,
	"asohist_salesrep_id" INTEGER,
	"asohist_tax_id" INTEGER,
	"asohist_misc_type" BPCHAR,
	"asohist_misc_descrip" TEXT,
	"asohist_misc_id" INTEGER,
	"asohist_commissionpaid" BOOLEAN,
	"asohist_doctype" TEXT,
	"asohist_imported" BOOLEAN,
	"asohist_ponumber" TEXT,
	"asohist_curr_id" INTEGER,
	"asohist_taxtype_id" INTEGER
);

-- Class asshead of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table asshead for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE asshead
CREATE TABLE "asshead" (
	"asshead_id" INTEGER PRIMARY KEY,
	"asshead_item_id" INTEGER,
	"asshead_docnum" TEXT,
	"asshead_revision" TEXT
);

-- Class assitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table assitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE assitem
CREATE TABLE "assitem" (
	"assitem_id" INTEGER PRIMARY KEY,
	"assitem_parent_item_id" INTEGER,
	"assitem_item_id" INTEGER,
	"assitem_seqnumber" INTEGER
);

-- Class backup_ccpay of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table backup_ccpay for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE backup_ccpay
CREATE TABLE "backup_ccpay" (
	"ccpay_id" INTEGER,
	"ccpay_ccard_id" INTEGER,
	"ccpay_cust_id" INTEGER,
	"ccpay_auth" BOOLEAN,
	"ccpay_status" BPCHAR,
	"ccpay_type" BPCHAR,
	"ccpay_auth_charge" BPCHAR,
	"ccpay_order_number" INTEGER,
	"ccpay_order_number_seq" INTEGER,
	"ccpay_pfpro_pnref" TEXT,
	"ccpay_pfpro_result" INTEGER,
	"ccpay_pfpro_cvv2match" BPCHAR,
	"ccpay_pfpro_respmsg" TEXT,
	"ccpay_pfpro_authcode" BPCHAR,
	"ccpay_pfpro_avsaddr" BPCHAR,
	"ccpay_pfpro_avszip" BPCHAR,
	"ccpay_pfpro_iavs" BPCHAR,
	"ccpay_yp_r_avs" TEXT,
	"ccpay_yp_r_ordernum" TEXT,
	"ccpay_yp_r_error" TEXT,
	"ccpay_yp_r_approved" TEXT,
	"ccpay_yp_r_code" TEXT,
	"ccpay_yp_r_message" TEXT,
	"ccpay_yp_r_ref" TEXT,
	"ccpay_yp_r_tdate" TEXT,
	"ccpay_yp_r_tax" TEXT,
	"ccpay_yp_r_shipping" TEXT,
	"ccpay_yp_r_score" INTEGER,
	"ccpay_by_username" TEXT,
	"ccpay_curr_id" INTEGER
);

-- Class backup_payco of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table backup_payco for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE backup_payco
CREATE TABLE "backup_payco" (
	"payco_ccpay_id" INTEGER,
	"payco_cohead_id" INTEGER,
	"payco_curr_id" INTEGER
);

-- Class backup_usr of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table backup_usr for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE backup_usr
CREATE TABLE "backup_usr" (
	"usr_id" INTEGER,
	"usr_username" TEXT,
	"usr_propername" TEXT,
	"usr_passwd" TEXT,
	"usr_locale_id" INTEGER,
	"usr_initials" TEXT,
	"usr_agent" BOOLEAN,
	"usr_active" BOOLEAN,
	"usr_email" TEXT,
	"usr_dept_id" INTEGER,
	"usr_shift_id" INTEGER,
	"usr_window" TEXT
);

-- Class bankaccnt of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table bankaccnt for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE bankaccnt
CREATE TABLE "bankaccnt" (
	"bankaccnt_id" INTEGER PRIMARY KEY,
	"bankaccnt_name" TEXT,
	"bankaccnt_descrip" TEXT,
	"bankaccnt_bankname" TEXT,
	"bankaccnt_accntnumber" TEXT,
	"bankaccnt_ar" BOOLEAN,
	"bankaccnt_ap" BOOLEAN,
	"bankaccnt_nextchknum" INTEGER,
	"bankaccnt_type" BPCHAR,
	"bankaccnt_accnt_id" INTEGER,
	"bankaccnt_check_form_id" INTEGER,
	"bankaccnt_userec" BOOLEAN,
	"bankaccnt_rec_accnt_id" INTEGER,
	"bankaccnt_curr_id" INTEGER,
	"bankaccnt_notes" TEXT,
	"bankaccnt_routing" TEXT,
	"bankaccnt_ach_enabled" BOOLEAN,
	"bankaccnt_ach_origin" TEXT,
	"bankaccnt_ach_genchecknum" BOOLEAN,
	"bankaccnt_ach_leadtime" INTEGER,
	"bankaccnt_ach_lastfileid" BPCHAR,
	"bankaccnt_ach_origintype" TEXT,
	"bankaccnt_ach_originname" TEXT,
	"bankaccnt_ach_desttype" TEXT,
	"bankaccnt_ach_fed_dest" TEXT,
	"bankaccnt_ach_destname" TEXT,
	"bankaccnt_ach_dest" TEXT
);

-- Class bankadj of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table bankadj for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE bankadj
CREATE TABLE "bankadj" (
	"bankadj_id" INTEGER PRIMARY KEY,
	"bankadj_bankaccnt_id" INTEGER,
	"bankadj_bankadjtype_id" INTEGER,
	"bankadj_username" TEXT,
	"bankadj_docnumber" TEXT,
	"bankadj_notes" TEXT,
	"bankadj_sequence" INTEGER,
	"bankadj_posted" BOOLEAN,
	"bankadj_curr_id" INTEGER
);

-- Class bankadjtype of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table bankadjtype for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE bankadjtype
CREATE TABLE "bankadjtype" (
	"bankadjtype_id" INTEGER PRIMARY KEY,
	"bankadjtype_name" TEXT,
	"bankadjtype_descrip" TEXT,
	"bankadjtype_accnt_id" INTEGER,
	"bankadjtype_iscredit" BOOLEAN
);

-- Class bankrec of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table bankrec for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE bankrec
CREATE TABLE "bankrec" (
	"bankrec_id" INTEGER PRIMARY KEY,
	"bankrec_username" TEXT,
	"bankrec_bankaccnt_id" INTEGER,
	"bankrec_posted" BOOLEAN
);

-- Class bankrecitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table bankrecitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE bankrecitem
CREATE TABLE "bankrecitem" (
	"bankrecitem_id" INTEGER PRIMARY KEY,
	"bankrecitem_bankrec_id" INTEGER,
	"bankrecitem_source" TEXT,
	"bankrecitem_source_id" INTEGER,
	"bankrecitem_cleared" BOOLEAN
);

-- Class billingeditlist of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table billingeditlist for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE billingeditlist
CREATE TABLE "billingeditlist" (
	"orderid" INTEGER,
	"itemid" INTEGER,
	"documentnumber" TEXT,
	"cust_number" TEXT,
	"billtoname" TEXT,
	"ordernumber" TEXT,
	"linenumber" INTEGER,
	"item" TEXT,
	"itemdescrip" TEXT,
	"iteminvuom" TEXT,
	"f_qtytobill" TEXT,
	"f_price" TEXT,
	"f_extprice" TEXT,
	"sence" TEXT,
	"account" TEXT,
	"curr_id" INTEGER
);

-- Class bomhead of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table bomhead for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE bomhead
CREATE TABLE "bomhead" (
	"bomhead_id" INTEGER PRIMARY KEY,
	"bomhead_item_id" INTEGER,
	"bomhead_serial" INTEGER,
	"bomhead_docnum" TEXT,
	"bomhead_revision" TEXT,
	"bomhead_rev_id" INTEGER
);

-- Class bomitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table bomitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE bomitem
CREATE TABLE "bomitem" (
	"bomitem_id" INTEGER PRIMARY KEY,
	"bomitem_parent_item_id" INTEGER,
	"bomitem_seqnumber" INTEGER,
	"bomitem_item_id" INTEGER,
	"bomitem_status" BPCHAR,
	"bomitem_createwo" BOOLEAN,
	"bomitem_issuemethod" BPCHAR,
	"bomitem_schedatwooper" BOOLEAN,
	"bomitem_ecn" TEXT,
	"bomitem_subtype" BPCHAR,
	"bomitem_uom_id" INTEGER,
	"bomitem_rev_id" INTEGER,
	"bomitem_booitem_seq_id" INTEGER,
	"bomitem_char_id" INTEGER,
	"bomitem_value" TEXT,
	"bomitem_notes" TEXT,
	"bomitem_ref" TEXT
);

-- Class bomitemsub of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table bomitemsub for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE bomitemsub
CREATE TABLE "bomitemsub" (
	"bomitemsub_id" INTEGER PRIMARY KEY,
	"bomitemsub_bomitem_id" INTEGER,
	"bomitemsub_item_id" INTEGER,
	"bomitemsub_rank" INTEGER
);

-- Class bomwork of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table bomwork for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE bomwork
CREATE TABLE "bomwork" (
	"bomwork_id" INTEGER PRIMARY KEY,
	"bomwork_set_id" INTEGER,
	"bomwork_seqnumber" INTEGER,
	"bomwork_item_id" INTEGER,
	"bomwork_item_type" BPCHAR,
	"bomwork_status" BPCHAR,
	"bomwork_level" INTEGER,
	"bomwork_parent_id" INTEGER,
	"bomwork_parent_seqnumber" INTEGER,
	"bomwork_createwo" BOOLEAN,
	"bomwork_issuemethod" BPCHAR,
	"bomwork_char_id" INTEGER,
	"bomwork_value" TEXT,
	"bomwork_notes" TEXT,
	"bomwork_ref" TEXT,
	"bomwork_bomitem_id" INTEGER,
	"bomwork_ecn" TEXT
);

-- Class brddist of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table brddist for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE brddist
CREATE TABLE "brddist" (
	"brddist_id" INTEGER PRIMARY KEY,
	"brddist_wo_id" INTEGER,
	"brddist_itemsite_id" INTEGER,
	"brddist_posted" BOOLEAN
);

-- Class budget of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table budget for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE budget
CREATE TABLE "budget" (
	"budget_id" INTEGER,
	"budget_period_id" INTEGER,
	"budget_accnt_id" INTEGER
);

-- Class budghead of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table budghead for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE budghead
CREATE TABLE "budghead" (
	"budghead_id" INTEGER PRIMARY KEY,
	"budghead_name" TEXT,
	"budghead_descrip" TEXT
);

-- Class budgitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table budgitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE budgitem
CREATE TABLE "budgitem" (
	"budgitem_id" INTEGER PRIMARY KEY,
	"budgitem_budghead_id" INTEGER,
	"budgitem_period_id" INTEGER,
	"budgitem_accnt_id" INTEGER
);

-- Class calhead of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table calhead for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE calhead
CREATE TABLE "calhead" (
	"calhead_id" INTEGER PRIMARY KEY,
	"calhead_type" BPCHAR,
	"calhead_name" TEXT,
	"calhead_descrip" TEXT,
	"calhead_origin" BPCHAR
);

-- Class carrier of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table carrier for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE carrier
CREATE TABLE "carrier" (
	"carrier_id" INTEGER PRIMARY KEY,
	"carrier_name" TEXT,
	"carrier_comments" TEXT
);

-- Class cashrcpt of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table cashrcpt for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE cashrcpt
CREATE TABLE "cashrcpt" (
	"cashrcpt_id" INTEGER PRIMARY KEY,
	"cashrcpt_cust_id" INTEGER,
	"cashrcpt_fundstype" BPCHAR,
	"cashrcpt_docnumber" TEXT,
	"cashrcpt_bankaccnt_id" INTEGER,
	"cashrcpt_notes" TEXT,
	"cashrcpt_salescat_id" INTEGER,
	"cashrcpt_curr_id" INTEGER,
	"cashrcpt_usecustdeposit" BOOLEAN
);

-- Class cashrcptitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table cashrcptitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE cashrcptitem
CREATE TABLE "cashrcptitem" (
	"cashrcptitem_id" INTEGER PRIMARY KEY,
	"cashrcptitem_cashrcpt_id" INTEGER,
	"cashrcptitem_aropen_id" INTEGER
);

-- Class cashrcptmisc of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table cashrcptmisc for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE cashrcptmisc
CREATE TABLE "cashrcptmisc" (
	"cashrcptmisc_id" INTEGER PRIMARY KEY,
	"cashrcptmisc_cashrcpt_id" INTEGER,
	"cashrcptmisc_accnt_id" INTEGER,
	"cashrcptmisc_notes" TEXT
);

-- Class ccard of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table ccard for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE ccard
CREATE TABLE "ccard" (
	"ccard_id" INTEGER PRIMARY KEY,
	"ccard_seq" INTEGER,
	"ccard_cust_id" INTEGER,
	"ccard_active" BOOLEAN,
	"ccard_debit" BOOLEAN,
	"ccard_type" BPCHAR,
	"ccard_added_by_username" TEXT,
	"ccard_last_updated_by_username" TEXT
);

-- Class ccardaud of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table ccardaud for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE ccardaud
CREATE TABLE "ccardaud" (
	"ccardaud_id" INTEGER PRIMARY KEY,
	"ccardaud_ccard_id" INTEGER,
	"ccardaud_ccard_seq_old" INTEGER,
	"ccardaud_ccard_seq_new" INTEGER,
	"ccardaud_ccard_cust_id_old" INTEGER,
	"ccardaud_ccard_cust_id_new" INTEGER,
	"ccardaud_ccard_active_old" BOOLEAN,
	"ccardaud_ccard_active_new" BOOLEAN,
	"ccardaud_ccard_debit_old" BOOLEAN,
	"ccardaud_ccard_debit_new" BOOLEAN,
	"ccardaud_ccard_type_old" BPCHAR,
	"ccardaud_ccard_type_new" BPCHAR,
	"ccardaud_ccard_last_updated_by_username" TEXT
);

-- Class ccpay of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table ccpay for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE ccpay
CREATE TABLE "ccpay" (
	"ccpay_id" INTEGER PRIMARY KEY,
	"ccpay_ccard_id" INTEGER,
	"ccpay_cust_id" INTEGER,
	"ccpay_auth" BOOLEAN,
	"ccpay_status" BPCHAR,
	"ccpay_type" BPCHAR,
	"ccpay_auth_charge" BPCHAR,
	"ccpay_order_number" TEXT,
	"ccpay_order_number_seq" INTEGER,
	"ccpay_r_avs" TEXT,
	"ccpay_r_ordernum" TEXT,
	"ccpay_r_error" TEXT,
	"ccpay_r_approved" TEXT,
	"ccpay_r_code" TEXT,
	"ccpay_r_message" TEXT,
	"ccpay_r_ref" TEXT,
	"ccpay_yp_r_tdate" TEXT,
	"ccpay_r_tax" TEXT,
	"ccpay_r_shipping" TEXT,
	"ccpay_yp_r_score" INTEGER,
	"ccpay_by_username" TEXT,
	"ccpay_curr_id" INTEGER
);

-- Class char of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table char for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE char
CREATE TABLE "char" (
	"char_id" INTEGER PRIMARY KEY,
	"char_name" TEXT,
	"char_items" BOOLEAN,
	"char_options" BOOLEAN,
	"char_attributes" BOOLEAN,
	"char_lotserial" BOOLEAN,
	"char_notes" TEXT,
	"char_customers" BOOLEAN,
	"char_crmaccounts" BOOLEAN,
	"char_addresses" BOOLEAN,
	"char_contacts" BOOLEAN,
	"char_opportunity" BOOLEAN,
	"char_employees" BOOLEAN
);

-- Class charass of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table charass for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE charass
CREATE TABLE "charass" (
	"charass_id" INTEGER PRIMARY KEY,
	"charass_target_type" TEXT,
	"charass_target_id" INTEGER,
	"charass_char_id" INTEGER,
	"charass_value" TEXT,
	"charass_default" BOOLEAN
);

-- Class checkhead of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table checkhead for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE checkhead
CREATE TABLE "checkhead" (
	"checkhead_id" INTEGER PRIMARY KEY,
	"checkhead_recip_id" INTEGER,
	"checkhead_recip_type" TEXT,
	"checkhead_bankaccnt_id" INTEGER,
	"checkhead_printed" BOOLEAN,
	"checkhead_number" INTEGER,
	"checkhead_void" BOOLEAN,
	"checkhead_replaced" BOOLEAN,
	"checkhead_posted" BOOLEAN,
	"checkhead_rec" BOOLEAN,
	"checkhead_misc" BOOLEAN,
	"checkhead_expcat_id" INTEGER,
	"checkhead_for" TEXT,
	"checkhead_notes" TEXT,
	"checkhead_journalnumber" INTEGER,
	"checkhead_curr_id" INTEGER,
	"checkhead_deleted" BOOLEAN,
	"checkhead_ach_batch" TEXT
);

-- Class checkitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table checkitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE checkitem
CREATE TABLE "checkitem" (
	"checkitem_id" INTEGER PRIMARY KEY,
	"checkitem_checkhead_id" INTEGER,
	"checkitem_ponumber" TEXT,
	"checkitem_vouchernumber" TEXT,
	"checkitem_invcnumber" TEXT,
	"checkitem_apopen_id" INTEGER,
	"checkitem_aropen_id" INTEGER,
	"checkitem_curr_id" INTEGER,
	"checkitem_cmnumber" TEXT,
	"checkitem_ranumber" TEXT
);

-- Class checkrecip of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table checkrecip for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE checkrecip
CREATE TABLE "checkrecip" (
	"checkrecip_id" INTEGER,
	"checkrecip_type" TEXT,
	"checkrecip_number" TEXT,
	"checkrecip_name" TEXT,
	"checkrecip_gltrans_source" TEXT,
	"checkrecip_accnt_id" INTEGER,
	"checkrecip_addr_id" INTEGER
);

-- Class classcode of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table classcode for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE classcode
CREATE TABLE "classcode" (
	"classcode_id" INTEGER PRIMARY KEY,
	"classcode_code" TEXT,
	"classcode_descrip" TEXT,
	"classcode_mfg" BOOLEAN
);

-- Class cmd of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table cmd for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE cmd
CREATE TABLE "cmd" (
	"cmd_id" INTEGER PRIMARY KEY,
	"cmd_module" TEXT,
	"cmd_title" TEXT,
	"cmd_descrip" TEXT,
	"cmd_privname" TEXT,
	"cmd_executable" TEXT,
	"cmd_name" TEXT
);

-- Class cmdarg of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table cmdarg for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE cmdarg
CREATE TABLE "cmdarg" (
	"cmdarg_id" INTEGER PRIMARY KEY,
	"cmdarg_cmd_id" INTEGER,
	"cmdarg_order" INTEGER,
	"cmdarg_arg" TEXT
);

-- Class cmhead of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table cmhead for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE cmhead
CREATE TABLE "cmhead" (
	"cmhead_id" INTEGER PRIMARY KEY,
	"cmhead_number" TEXT,
	"cmhead_posted" BOOLEAN,
	"cmhead_invcnumber" TEXT,
	"cmhead_custponumber" TEXT,
	"cmhead_cust_id" INTEGER,
	"cmhead_shipto_id" INTEGER,
	"cmhead_shipto_name" TEXT,
	"cmhead_shipto_address1" TEXT,
	"cmhead_shipto_address2" TEXT,
	"cmhead_shipto_address3" TEXT,
	"cmhead_shipto_city" TEXT,
	"cmhead_shipto_state" TEXT,
	"cmhead_shipto_zipcode" TEXT,
	"cmhead_salesrep_id" INTEGER,
	"cmhead_tax_id" INTEGER,
	"cmhead_comments" TEXT,
	"cmhead_printed" BOOLEAN,
	"cmhead_billtoname" TEXT,
	"cmhead_billtoaddress1" TEXT,
	"cmhead_billtoaddress2" TEXT,
	"cmhead_billtoaddress3" TEXT,
	"cmhead_billtocity" TEXT,
	"cmhead_billtostate" TEXT,
	"cmhead_billtozip" TEXT,
	"cmhead_hold" BOOLEAN,
	"cmhead_misc_accnt_id" INTEGER,
	"cmhead_misc_descrip" TEXT,
	"cmhead_rsncode_id" INTEGER,
	"cmhead_curr_id" INTEGER,
	"cmhead_taxauth_id" INTEGER,
	"cmhead_tax_curr_id" INTEGER,
	"cmhead_adjtax_id" INTEGER,
	"cmhead_adjtaxtype_id" INTEGER,
	"cmhead_freighttax_id" INTEGER,
	"cmhead_freighttaxtype_id" INTEGER,
	"cmhead_billtocountry" TEXT,
	"cmhead_shipto_country" TEXT,
	"cmhead_rahead_id" INTEGER
);

-- Class cmitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table cmitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE cmitem
CREATE TABLE "cmitem" (
	"cmitem_id" INTEGER PRIMARY KEY,
	"cmitem_cmhead_id" INTEGER,
	"cmitem_linenumber" INTEGER,
	"cmitem_itemsite_id" INTEGER,
	"cmitem_comments" TEXT,
	"cmitem_rsncode_id" INTEGER,
	"cmitem_tax_id" INTEGER,
	"cmitem_taxtype_id" INTEGER,
	"cmitem_qty_uom_id" INTEGER,
	"cmitem_price_uom_id" INTEGER,
	"cmitem_raitem_id" INTEGER
);

-- Class cmnttype of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table cmnttype for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE cmnttype
CREATE TABLE "cmnttype" (
	"cmnttype_id" INTEGER PRIMARY KEY,
	"cmnttype_name" TEXT,
	"cmnttype_descrip" TEXT,
	"cmnttype_usedin" TEXT,
	"cmnttype_sys" BOOLEAN
);

-- Class cntct of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table cntct for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE cntct
CREATE TABLE "cntct" (
	"cntct_id" INTEGER PRIMARY KEY,
	"cntct_crmacct_id" INTEGER,
	"cntct_addr_id" INTEGER,
	"cntct_first_name" TEXT,
	"cntct_last_name" TEXT,
	"cntct_honorific" TEXT,
	"cntct_initials" TEXT,
	"cntct_active" BOOLEAN,
	"cntct_phone" TEXT,
	"cntct_phone2" TEXT,
	"cntct_fax" TEXT,
	"cntct_email" TEXT,
	"cntct_webaddr" TEXT,
	"cntct_notes" TEXT,
	"cntct_title" TEXT,
	"cntct_number" TEXT,
	"cntct_middle" TEXT,
	"cntct_suffix" TEXT,
	"cntct_owner_username" TEXT
);

-- Class cntslip of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table cntslip for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE cntslip
CREATE TABLE "cntslip" (
	"cntslip_id" INTEGER PRIMARY KEY,
	"cntslip_cnttag_id" INTEGER,
	"cntslip_user_id" INTEGER,
	"cntslip_posted" BOOLEAN,
	"cntslip_number" TEXT,
	"cntslip_comments" TEXT,
	"cntslip_location_id" INTEGER,
	"cntslip_lotserial" TEXT
);

-- Class cobill of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table cobill for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE cobill
CREATE TABLE "cobill" (
	"cobill_id" INTEGER PRIMARY KEY,
	"cobill_coitem_id" INTEGER,
	"cobill_invcnum" INTEGER,
	"cobill_toclose" BOOLEAN,
	"cobill_cobmisc_id" INTEGER,
	"cobill_select_username" TEXT,
	"cobill_invcitem_id" INTEGER,
	"cobill_tax_id" INTEGER,
	"cobill_taxtype_id" INTEGER
);

-- Class cohist of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table cohist for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE cohist
CREATE TABLE "cohist" (
	"cohist_id" INTEGER PRIMARY KEY,
	"cohist_cust_id" INTEGER,
	"cohist_itemsite_id" INTEGER,
	"cohist_shipvia" TEXT,
	"cohist_ordernumber" TEXT,
	"cohist_invcnumber" TEXT,
	"cohist_shipto_id" INTEGER,
	"cohist_salesrep_id" INTEGER,
	"cohist_imported" BOOLEAN,
	"cohist_billtoname" TEXT,
	"cohist_billtoaddress1" TEXT,
	"cohist_billtoaddress2" TEXT,
	"cohist_billtoaddress3" TEXT,
	"cohist_billtocity" TEXT,
	"cohist_billtostate" TEXT,
	"cohist_billtozip" TEXT,
	"cohist_shiptoname" TEXT,
	"cohist_shiptoaddress1" TEXT,
	"cohist_shiptoaddress2" TEXT,
	"cohist_shiptoaddress3" TEXT,
	"cohist_shiptocity" TEXT,
	"cohist_shiptostate" TEXT,
	"cohist_shiptozip" TEXT,
	"cohist_commissionpaid" BOOLEAN,
	"cohist_misc_type" BPCHAR,
	"cohist_misc_descrip" TEXT,
	"cohist_misc_id" INTEGER,
	"cohist_tax_id" INTEGER,
	"cohist_doctype" TEXT,
	"cohist_ponumber" TEXT,
	"cohist_curr_id" INTEGER,
	"cohist_sequence" INTEGER,
	"cohist_taxtype_id" INTEGER
);

-- Class coitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table coitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE coitem
CREATE TABLE "coitem" (
	"coitem_id" INTEGER PRIMARY KEY,
	"coitem_cohead_id" INTEGER,
	"coitem_linenumber" INTEGER,
	"coitem_itemsite_id" INTEGER,
	"coitem_status" BPCHAR,
	"coitem_order_id" INTEGER,
	"coitem_memo" TEXT,
	"coitem_imported" BOOLEAN,
	"coitem_custpn" TEXT,
	"coitem_order_type" BPCHAR,
	"coitem_close_username" TEXT,
	"coitem_substitute_item_id" INTEGER,
	"coitem_creator" TEXT,
	"coitem_tax_id" INTEGER,
	"coitem_qty_uom_id" INTEGER,
	"coitem_price_uom_id" INTEGER,
	"coitem_warranty" BOOLEAN,
	"coitem_cos_accnt_id" INTEGER,
	"coitem_subnumber" INTEGER,
	"coitem_firm" BOOLEAN
);

-- Class comment of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table comment for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE comment
CREATE TABLE "comment" (
	"comment_id" INTEGER PRIMARY KEY,
	"comment_source_id" INTEGER,
	"comment_user" TEXT,
	"comment_text" TEXT,
	"comment_cmnttype_id" INTEGER,
	"comment_source" TEXT
);

-- Class company of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table company for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE company
CREATE TABLE "company" (
	"company_id" INTEGER PRIMARY KEY,
	"company_number" TEXT,
	"company_descrip" TEXT,
	"company_currency_id" INTEGER,
	"company_external" BOOLEAN,
	"company_server" TEXT,
	"company_port" INTEGER,
	"company_database" TEXT
);

-- Class coship of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table coship for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE coship
CREATE TABLE "coship" (
	"coship_id" INTEGER,
	"coship_coitem_id" INTEGER,
	"coship_shipped" BOOLEAN,
	"coship_invoiced" BOOLEAN,
	"coship_cosmisc_id" INTEGER,
	"coship_trans_username" TEXT,
	"coship_invcitem_id" INTEGER
);

-- Class cosmisc of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table cosmisc for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE cosmisc
CREATE TABLE "cosmisc" (
	"cosmisc_id" INTEGER,
	"cosmisc_cohead_id" INTEGER,
	"cosmisc_shipvia" TEXT,
	"cosmisc_notes" TEXT,
	"cosmisc_shipchrg_id" INTEGER,
	"cosmisc_shipform_id" INTEGER,
	"cosmisc_shipped" BOOLEAN,
	"cosmisc_sfstatus" BPCHAR,
	"cosmisc_tracknum" TEXT,
	"cosmisc_number" TEXT
);

-- Class costcat of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table costcat for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE costcat
CREATE TABLE "costcat" (
	"costcat_id" INTEGER PRIMARY KEY,
	"costcat_code" TEXT,
	"costcat_descrip" TEXT,
	"costcat_asset_accnt_id" INTEGER,
	"costcat_liability_accnt_id" INTEGER,
	"costcat_adjustment_accnt_id" INTEGER,
	"costcat_matusage_accnt_id" INTEGER,
	"costcat_purchprice_accnt_id" INTEGER,
	"costcat_laboroverhead_accnt_id" INTEGER,
	"costcat_scrap_accnt_id" INTEGER,
	"costcat_invcost_accnt_id" INTEGER,
	"costcat_wip_accnt_id" INTEGER,
	"costcat_shipasset_accnt_id" INTEGER,
	"costcat_mfgscrap_accnt_id" INTEGER,
	"costcat_transform_accnt_id" INTEGER,
	"costcat_freight_accnt_id" INTEGER,
	"costcat_toliability_accnt_id" INTEGER
);

-- Class costelem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table costelem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE costelem
CREATE TABLE "costelem" (
	"costelem_id" INTEGER PRIMARY KEY,
	"costelem_type" TEXT,
	"costelem_sys" BOOLEAN,
	"costelem_po" BOOLEAN,
	"costelem_active" BOOLEAN,
	"costelem_exp_accnt_id" INTEGER,
	"costelem_cost_item_id" INTEGER
);

-- Class costhist of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table costhist for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE costhist
CREATE TABLE "costhist" (
	"costhist_id" INTEGER PRIMARY KEY,
	"costhist_item_id" INTEGER,
	"costhist_costelem_id" INTEGER,
	"costhist_type" BPCHAR,
	"costhist_user_id" INTEGER,
	"costhist_lowlevel" BOOLEAN,
	"costhist_oldcurr_id" INTEGER,
	"costhist_newcurr_id" INTEGER
);

-- Class costupdate of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table costupdate for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE costupdate
CREATE TABLE "costupdate" (
	"costupdate_item_id" INTEGER,
	"costupdate_lowlevel_code" INTEGER,
	"costupdate_item_type" BPCHAR
);

-- Class country of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table country for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE country
CREATE TABLE "country" (
	"country_id" INTEGER PRIMARY KEY,
	"country_abbr" BPCHAR,
	"country_name" TEXT,
	"country_curr_abbr" BPCHAR,
	"country_curr_name" TEXT,
	"country_curr_number" BPCHAR,
	"country_curr_symbol" TEXT,
	"country_qt_number" INTEGER
);

-- Class creditmemoeditlist of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table creditmemoeditlist for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE creditmemoeditlist
CREATE TABLE "creditmemoeditlist" (
	"orderid" INTEGER,
	"itemid" INTEGER,
	"documentnumber" TEXT,
	"cust_number" TEXT,
	"billtoname" TEXT,
	"ordernumber" TEXT,
	"linenumber" INTEGER,
	"item" TEXT,
	"itemdescrip" TEXT,
	"iteminvuom" TEXT,
	"qtytobill" TEXT,
	"price" TEXT,
	"extprice" TEXT,
	"sence" TEXT,
	"account" TEXT
);

-- Class crmacct of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table crmacct for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE crmacct
CREATE TABLE "crmacct" (
	"crmacct_id" INTEGER PRIMARY KEY,
	"crmacct_number" TEXT,
	"crmacct_name" TEXT,
	"crmacct_active" BOOLEAN,
	"crmacct_type" BPCHAR,
	"crmacct_cust_id" INTEGER,
	"crmacct_competitor_id" INTEGER,
	"crmacct_partner_id" INTEGER,
	"crmacct_prospect_id" INTEGER,
	"crmacct_vend_id" INTEGER,
	"crmacct_cntct_id_1" INTEGER,
	"crmacct_cntct_id_2" INTEGER,
	"crmacct_parent_id" INTEGER,
	"crmacct_notes" TEXT,
	"crmacct_taxauth_id" INTEGER,
	"crmacct_owner_username" TEXT
);

-- Class curr of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table curr for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE curr
CREATE TABLE "curr" (
	"curr_id" INTEGER PRIMARY KEY,
	"curr_name" TEXT,
	"curr_symbol" TEXT,
	"curr_fractional" INTEGER,
	"curr_accnt_id" INTEGER
);

-- Class curr_rate of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table curr_rate for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE curr_rate
CREATE TABLE "curr_rate" (
	"curr_rate_id" INTEGER PRIMARY KEY,
	"curr_id" INTEGER
);

-- Class cust of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table cust for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE cust
CREATE TABLE "cust" (
	"cust_id" INTEGER PRIMARY KEY,
	"cust_active" BOOLEAN,
	"cust_custtype_id" INTEGER,
	"cust_salesrep_id" INTEGER,
	"cust_name" TEXT,
	"cust_address1" TEXT,
	"cust_address2" TEXT,
	"cust_address3" TEXT,
	"cust_city" TEXT,
	"cust_state" TEXT,
	"cust_zipcode" TEXT,
	"cust_contact" TEXT,
	"cust_phone" TEXT,
	"cust_fax" TEXT,
	"cust_email" TEXT,
	"cust_corraddress1" TEXT,
	"cust_corraddress2" TEXT,
	"cust_corraddress3" TEXT,
	"cust_corrcity" TEXT,
	"cust_corrstate" TEXT,
	"cust_corrzipcode" TEXT,
	"cust_corrcontact" TEXT,
	"cust_corrphone" TEXT,
	"cust_corrfax" TEXT,
	"cust_corremail" TEXT,
	"cust_creditlmt" INTEGER,
	"cust_creditrating" TEXT,
	"cust_financecharge" BOOLEAN,
	"cust_backorder" BOOLEAN,
	"cust_partialship" BOOLEAN,
	"cust_terms_id" INTEGER,
	"cust_tax_id" INTEGER,
	"cust_taxidnum" TEXT,
	"cust_balmethod" BPCHAR,
	"cust_ffshipto" BOOLEAN,
	"cust_shipform_id" INTEGER,
	"cust_shipvia" TEXT,
	"cust_blanketpos" BOOLEAN,
	"cust_shipchrg_id" INTEGER,
	"cust_creditstatus" BPCHAR,
	"cust_comments" TEXT,
	"cust_ffbillto" BOOLEAN,
	"cust_country" TEXT,
	"cust_corrcountry" TEXT,
	"cust_usespos" BOOLEAN,
	"cust_number" TEXT,
	"cust_exported" BOOLEAN,
	"cust_emaildelivery" BOOLEAN,
	"cust_ediemail" TEXT,
	"cust_edisubject" TEXT,
	"cust_edifilename" TEXT,
	"cust_ediemailbody" TEXT,
	"cust_autoupdatestatus" BOOLEAN,
	"cust_autoholdorders" BOOLEAN,
	"cust_edicc" TEXT,
	"cust_ediprofile_id" INTEGER,
	"cust_preferred_warehous_id" INTEGER,
	"cust_curr_id" INTEGER,
	"cust_creditlmt_curr_id" INTEGER
);

-- Class custform of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table custform for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE custform
CREATE TABLE "custform" (
	"custform_id" INTEGER PRIMARY KEY,
	"custform_custtype_id" INTEGER,
	"custform_custtype" TEXT,
	"custform_invoice_report_id" INTEGER,
	"custform_creditmemo_report_id" INTEGER,
	"custform_quote_report_id" INTEGER,
	"custform_packinglist_report_id" INTEGER,
	"custform_statement_report_id" INTEGER,
	"custform_sopicklist_report_id" INTEGER
);

-- Class custgrp of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table custgrp for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE custgrp
CREATE TABLE "custgrp" (
	"custgrp_id" INTEGER PRIMARY KEY,
	"custgrp_name" TEXT,
	"custgrp_descrip" TEXT
);

-- Class custgrpitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table custgrpitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE custgrpitem
CREATE TABLE "custgrpitem" (
	"custgrpitem_id" INTEGER PRIMARY KEY,
	"custgrpitem_custgrp_id" INTEGER,
	"custgrpitem_cust_id" INTEGER
);

-- Class custinfo of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table custinfo for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE custinfo
CREATE TABLE "custinfo" (
	"cust_id" INTEGER PRIMARY KEY,
	"cust_active" BOOLEAN,
	"cust_custtype_id" INTEGER,
	"cust_salesrep_id" INTEGER,
	"cust_name" TEXT,
	"cust_creditlmt" INTEGER,
	"cust_creditrating" TEXT,
	"cust_financecharge" BOOLEAN,
	"cust_backorder" BOOLEAN,
	"cust_partialship" BOOLEAN,
	"cust_terms_id" INTEGER,
	"cust_tax_id" INTEGER,
	"cust_taxidnum" TEXT,
	"cust_balmethod" BPCHAR,
	"cust_ffshipto" BOOLEAN,
	"cust_shipform_id" INTEGER,
	"cust_shipvia" TEXT,
	"cust_blanketpos" BOOLEAN,
	"cust_shipchrg_id" INTEGER,
	"cust_creditstatus" BPCHAR,
	"cust_comments" TEXT,
	"cust_ffbillto" BOOLEAN,
	"cust_usespos" BOOLEAN,
	"cust_number" TEXT,
	"cust_exported" BOOLEAN,
	"cust_emaildelivery" BOOLEAN,
	"cust_ediemail" TEXT,
	"cust_edisubject" TEXT,
	"cust_edifilename" TEXT,
	"cust_ediemailbody" TEXT,
	"cust_autoupdatestatus" BOOLEAN,
	"cust_autoholdorders" BOOLEAN,
	"cust_edicc" TEXT,
	"cust_ediprofile_id" INTEGER,
	"cust_preferred_warehous_id" INTEGER,
	"cust_curr_id" INTEGER,
	"cust_creditlmt_curr_id" INTEGER,
	"cust_cntct_id" INTEGER,
	"cust_corrcntct_id" INTEGER,
	"cust_taxauth_id" INTEGER,
	"cust_soemaildelivery" BOOLEAN,
	"cust_soediemail" TEXT,
	"cust_soedisubject" TEXT,
	"cust_soedifilename" TEXT,
	"cust_soediemailbody" TEXT,
	"cust_soedicc" TEXT,
	"cust_soediprofile_id" INTEGER,
	"cust_gracedays" INTEGER,
	"cust_ediemailhtml" BOOLEAN,
	"cust_soediemailhtml" BOOLEAN
);

-- Class custtype of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table custtype for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE custtype
CREATE TABLE "custtype" (
	"custtype_id" INTEGER PRIMARY KEY,
	"custtype_code" TEXT,
	"custtype_descrip" TEXT,
	"custtype_char" BOOLEAN
);

-- Class dept of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table dept for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE dept
CREATE TABLE "dept" (
	"dept_id" INTEGER PRIMARY KEY,
	"dept_number" TEXT,
	"dept_name" TEXT
);

-- Class destination of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table destination for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE destination
CREATE TABLE "destination" (
	"destination_id" INTEGER PRIMARY KEY,
	"destination_name" TEXT,
	"destination_city" TEXT,
	"destination_state" TEXT,
	"destination_comments" TEXT
);

-- Class ediprofile of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table ediprofile for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE ediprofile
CREATE TABLE "ediprofile" (
	"ediprofile_id" INTEGER PRIMARY KEY,
	"ediprofile_name" TEXT,
	"ediprofile_notes" TEXT,
	"ediprofile_type" TEXT,
	"ediprofile_option1" TEXT,
	"ediprofile_option2" TEXT,
	"ediprofile_option3" TEXT,
	"ediprofile_option4" TEXT,
	"ediprofile_option5" TEXT
);

-- Class emp of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table emp for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE emp
CREATE TABLE "emp" (
	"emp_id" INTEGER PRIMARY KEY,
	"emp_code" TEXT,
	"emp_number" TEXT,
	"emp_active" BOOLEAN,
	"emp_cntct_id" INTEGER,
	"emp_warehous_id" INTEGER,
	"emp_mgr_emp_id" INTEGER,
	"emp_wage_type" TEXT,
	"emp_wage_curr_id" INTEGER,
	"emp_wage_period" TEXT,
	"emp_dept_id" INTEGER,
	"emp_shift_id" INTEGER,
	"emp_usr_id" INTEGER,
	"emp_notes" TEXT,
	"emp_image_id" INTEGER
);

-- Class empgrp of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table empgrp for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE empgrp
CREATE TABLE "empgrp" (
	"empgrp_id" INTEGER PRIMARY KEY,
	"empgrp_name" TEXT,
	"empgrp_descrip" TEXT
);

-- Class empgrpitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table empgrpitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE empgrpitem
CREATE TABLE "empgrpitem" (
	"empgrpitem_id" INTEGER PRIMARY KEY,
	"empgrpitem_empgrp_id" INTEGER,
	"empgrpitem_emp_id" INTEGER
);

-- Class evntlog of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table evntlog for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE evntlog
CREATE TABLE "evntlog" (
	"evntlog_id" INTEGER PRIMARY KEY,
	"evntlog_evnttype_id" INTEGER,
	"evntlog_ord_id" INTEGER,
	"evntlog_action" TEXT,
	"evntlog_warehous_id" INTEGER,
	"evntlog_number" TEXT,
	"evntlog_ordtype" BPCHAR,
	"evntlog_username" TEXT
);

-- Class evntnot of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table evntnot for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE evntnot
CREATE TABLE "evntnot" (
	"evntnot_id" INTEGER PRIMARY KEY,
	"evntnot_evnttype_id" INTEGER,
	"evntnot_warehous_id" INTEGER,
	"evntnot_username" TEXT
);

-- Class evnttype of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table evnttype for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE evnttype
CREATE TABLE "evnttype" (
	"evnttype_id" INTEGER PRIMARY KEY,
	"evnttype_name" TEXT,
	"evnttype_descrip" TEXT,
	"evnttype_module" TEXT
);

-- Class expcat of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table expcat for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE expcat
CREATE TABLE "expcat" (
	"expcat_id" INTEGER PRIMARY KEY,
	"expcat_code" TEXT,
	"expcat_descrip" TEXT,
	"expcat_exp_accnt_id" INTEGER,
	"expcat_liability_accnt_id" INTEGER,
	"expcat_active" BOOLEAN,
	"expcat_purchprice_accnt_id" INTEGER,
	"expcat_freight_accnt_id" INTEGER
);

-- Class flcol of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table flcol for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE flcol
CREATE TABLE "flcol" (
	"flcol_id" INTEGER PRIMARY KEY,
	"flcol_flhead_id" INTEGER,
	"flcol_name" TEXT,
	"flcol_descrip" TEXT,
	"flcol_report_id" INTEGER,
	"flcol_month" BOOLEAN,
	"flcol_quarter" BOOLEAN,
	"flcol_year" BOOLEAN,
	"flcol_showdb" BOOLEAN,
	"flcol_prcnt" BOOLEAN,
	"flcol_priortype" BPCHAR,
	"flcol_priormonth" BOOLEAN,
	"flcol_priorquarter" BOOLEAN,
	"flcol_prioryear" BPCHAR,
	"flcol_priorprcnt" BOOLEAN,
	"flcol_priordiff" BOOLEAN,
	"flcol_priordiffprcnt" BOOLEAN,
	"flcol_budget" BOOLEAN,
	"flcol_budgetprcnt" BOOLEAN,
	"flcol_budgetdiff" BOOLEAN,
	"flcol_budgetdiffprcnt" BOOLEAN
);

-- Class flgrp of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table flgrp for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE flgrp
CREATE TABLE "flgrp" (
	"flgrp_id" INTEGER PRIMARY KEY,
	"flgrp_flhead_id" INTEGER,
	"flgrp_flgrp_id" INTEGER,
	"flgrp_order" INTEGER,
	"flgrp_name" TEXT,
	"flgrp_descrip" TEXT,
	"flgrp_subtotal" BOOLEAN,
	"flgrp_summarize" BOOLEAN,
	"flgrp_subtract" BOOLEAN,
	"flgrp_showstart" BOOLEAN,
	"flgrp_showend" BOOLEAN,
	"flgrp_showdelta" BOOLEAN,
	"flgrp_showbudget" BOOLEAN,
	"flgrp_showstartprcnt" BOOLEAN,
	"flgrp_showendprcnt" BOOLEAN,
	"flgrp_showdeltaprcnt" BOOLEAN,
	"flgrp_showbudgetprcnt" BOOLEAN,
	"flgrp_prcnt_flgrp_id" INTEGER,
	"flgrp_showdiff" BOOLEAN,
	"flgrp_showdiffprcnt" BOOLEAN,
	"flgrp_showcustom" BOOLEAN,
	"flgrp_showcustomprcnt" BOOLEAN,
	"flgrp_usealtsubtotal" BOOLEAN,
	"flgrp_altsubtotal" TEXT
);

-- Class flhead of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table flhead for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE flhead
CREATE TABLE "flhead" (
	"flhead_id" INTEGER PRIMARY KEY,
	"flhead_name" TEXT,
	"flhead_descrip" TEXT,
	"flhead_showtotal" BOOLEAN,
	"flhead_showstart" BOOLEAN,
	"flhead_showend" BOOLEAN,
	"flhead_showdelta" BOOLEAN,
	"flhead_showbudget" BOOLEAN,
	"flhead_showdiff" BOOLEAN,
	"flhead_showcustom" BOOLEAN,
	"flhead_custom_label" TEXT,
	"flhead_usealttotal" BOOLEAN,
	"flhead_alttotal" TEXT,
	"flhead_usealtbegin" BOOLEAN,
	"flhead_altbegin" TEXT,
	"flhead_usealtend" BOOLEAN,
	"flhead_altend" TEXT,
	"flhead_usealtdebits" BOOLEAN,
	"flhead_altdebits" TEXT,
	"flhead_usealtcredits" BOOLEAN,
	"flhead_altcredits" TEXT,
	"flhead_usealtbudget" BOOLEAN,
	"flhead_altbudget" TEXT,
	"flhead_usealtdiff" BOOLEAN,
	"flhead_altdiff" TEXT,
	"flhead_type" BPCHAR,
	"flhead_active" BOOLEAN,
	"flhead_sys" BOOLEAN
);

-- Class flitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table flitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE flitem
CREATE TABLE "flitem" (
	"flitem_id" INTEGER PRIMARY KEY,
	"flitem_flhead_id" INTEGER,
	"flitem_flgrp_id" INTEGER,
	"flitem_order" INTEGER,
	"flitem_accnt_id" INTEGER,
	"flitem_showstart" BOOLEAN,
	"flitem_showend" BOOLEAN,
	"flitem_showdelta" BOOLEAN,
	"flitem_showbudget" BOOLEAN,
	"flitem_subtract" BOOLEAN,
	"flitem_showstartprcnt" BOOLEAN,
	"flitem_showendprcnt" BOOLEAN,
	"flitem_showdeltaprcnt" BOOLEAN,
	"flitem_showbudgetprcnt" BOOLEAN,
	"flitem_prcnt_flgrp_id" INTEGER,
	"flitem_showdiff" BOOLEAN,
	"flitem_showdiffprcnt" BOOLEAN,
	"flitem_showcustom" BOOLEAN,
	"flitem_showcustomprcnt" BOOLEAN,
	"flitem_custom_source" BPCHAR,
	"flitem_company" TEXT,
	"flitem_profit" TEXT,
	"flitem_number" TEXT,
	"flitem_sub" TEXT,
	"flitem_type" BPCHAR,
	"flitem_subaccnttype_code" TEXT
);

-- Class flrpt of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table flrpt for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE flrpt
CREATE TABLE "flrpt" (
	"flrpt_flhead_id" INTEGER,
	"flrpt_period_id" INTEGER,
	"flrpt_username" TEXT,
	"flrpt_order" INTEGER,
	"flrpt_level" INTEGER,
	"flrpt_type" TEXT,
	"flrpt_type_id" INTEGER,
	"flrpt_parent_id" INTEGER,
	"flrpt_altname" TEXT,
	"flrpt_accnt_id" INTEGER,
	"flrpt_interval" BPCHAR
);

-- Class flspec of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table flspec for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE flspec
CREATE TABLE "flspec" (
	"flspec_id" INTEGER PRIMARY KEY,
	"flspec_flhead_id" INTEGER,
	"flspec_flgrp_id" INTEGER,
	"flspec_order" INTEGER,
	"flspec_name" TEXT,
	"flspec_type" TEXT,
	"flspec_showstart" BOOLEAN,
	"flspec_showend" BOOLEAN,
	"flspec_showdelta" BOOLEAN,
	"flspec_showbudget" BOOLEAN,
	"flspec_subtract" BOOLEAN,
	"flspec_showstartprcnt" BOOLEAN,
	"flspec_showendprcnt" BOOLEAN,
	"flspec_showdeltaprcnt" BOOLEAN,
	"flspec_showbudgetprcnt" BOOLEAN,
	"flspec_showdiff" BOOLEAN,
	"flspec_showdiffprcnt" BOOLEAN,
	"flspec_prcnt_flgrp_id" INTEGER,
	"flspec_showcustom" BOOLEAN,
	"flspec_showcustomprcnt" BOOLEAN,
	"flspec_custom_source" BPCHAR
);

-- Class form of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table form for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE form
CREATE TABLE "form" (
	"form_id" INTEGER PRIMARY KEY,
	"form_name" TEXT,
	"form_descrip" TEXT,
	"form_report_id" INTEGER,
	"form_key" TEXT
);

-- Class freightclass of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table freightclass for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE freightclass
CREATE TABLE "freightclass" (
	"freightclass_id" INTEGER PRIMARY KEY,
	"freightclass_code" TEXT,
	"freightclass_descrip" TEXT
);

-- Class glseries of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table glseries for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE glseries
CREATE TABLE "glseries" (
	"glseries_id" INTEGER PRIMARY KEY,
	"glseries_sequence" INTEGER,
	"glseries_doctype" BPCHAR,
	"glseries_docnumber" TEXT,
	"glseries_accnt_id" INTEGER,
	"glseries_source" TEXT,
	"glseries_notes" TEXT
);

-- Class gltrans of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table gltrans for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE gltrans
CREATE TABLE "gltrans" (
	"gltrans_id" INTEGER PRIMARY KEY,
	"gltrans_exported" BOOLEAN,
	"gltrans_sequence" INTEGER,
	"gltrans_accnt_id" INTEGER,
	"gltrans_source" TEXT,
	"gltrans_docnumber" TEXT,
	"gltrans_misc_id" INTEGER,
	"gltrans_notes" TEXT,
	"gltrans_journalnumber" INTEGER,
	"gltrans_posted" BOOLEAN,
	"gltrans_doctype" TEXT,
	"gltrans_rec" BOOLEAN,
	"gltrans_username" TEXT
);

-- Class grp of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table grp for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE grp
CREATE TABLE "grp" (
	"grp_id" INTEGER PRIMARY KEY,
	"grp_name" TEXT,
	"grp_descrip" TEXT
);

-- Class grppriv of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table grppriv for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE grppriv
CREATE TABLE "grppriv" (
	"grppriv_id" INTEGER PRIMARY KEY,
	"grppriv_grp_id" INTEGER,
	"grppriv_priv_id" INTEGER
);

-- Class headlock of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table headlock for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE headlock
CREATE TABLE "headlock" (
	"headlock_head_id" INTEGER PRIMARY KEY,
	"headlock_table" TEXT,
	"headlock_username" TEXT,
	"headlock_procpid" INTEGER
);

-- Class hnfc of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table hnfc for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE hnfc
CREATE TABLE "hnfc" (
	"hnfc_id" INTEGER PRIMARY KEY,
	"hnfc_code" TEXT
);

-- Class image of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table image for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE image
CREATE TABLE "image" (
	"image_id" INTEGER PRIMARY KEY,
	"image_name" TEXT,
	"image_descrip" TEXT,
	"image_data" TEXT
);

-- Class imageass of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table imageass for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE imageass
CREATE TABLE "imageass" (
	"imageass_id" INTEGER PRIMARY KEY,
	"imageass_source_id" INTEGER,
	"imageass_source" TEXT,
	"imageass_image_id" INTEGER,
	"imageass_purpose" BPCHAR
);

-- Class incdt of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table incdt for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE incdt
CREATE TABLE "incdt" (
	"incdt_id" INTEGER PRIMARY KEY,
	"incdt_number" INTEGER,
	"incdt_crmacct_id" INTEGER,
	"incdt_cntct_id" INTEGER,
	"incdt_summary" TEXT,
	"incdt_descrip" TEXT,
	"incdt_item_id" INTEGER,
	"incdt_status" BPCHAR,
	"incdt_assigned_username" TEXT,
	"incdt_incdtcat_id" INTEGER,
	"incdt_incdtseverity_id" INTEGER,
	"incdt_incdtpriority_id" INTEGER,
	"incdt_incdtresolution_id" INTEGER,
	"incdt_lotserial" TEXT,
	"incdt_ls_id" INTEGER,
	"incdt_aropen_id" INTEGER,
	"incdt_owner_username" TEXT
);

-- Class incdtcat of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table incdtcat for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE incdtcat
CREATE TABLE "incdtcat" (
	"incdtcat_id" INTEGER PRIMARY KEY,
	"incdtcat_name" TEXT,
	"incdtcat_order" INTEGER,
	"incdtcat_descrip" TEXT,
	"incdtcat_ediprofile_id" INTEGER
);

-- Class incdthist of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table incdthist for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE incdthist
CREATE TABLE "incdthist" (
	"incdthist_id" INTEGER PRIMARY KEY,
	"incdthist_incdt_id" INTEGER,
	"incdthist_change" BPCHAR,
	"incdthist_target_id" INTEGER,
	"incdthist_username" TEXT,
	"incdthist_descrip" TEXT
);

-- Class incdtpriority of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table incdtpriority for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE incdtpriority
CREATE TABLE "incdtpriority" (
	"incdtpriority_id" INTEGER PRIMARY KEY,
	"incdtpriority_name" TEXT,
	"incdtpriority_order" INTEGER,
	"incdtpriority_descrip" TEXT
);

-- Class incdtresolution of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table incdtresolution for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE incdtresolution
CREATE TABLE "incdtresolution" (
	"incdtresolution_id" INTEGER PRIMARY KEY,
	"incdtresolution_name" TEXT,
	"incdtresolution_order" INTEGER,
	"incdtresolution_descrip" TEXT
);

-- Class incdtseverity of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table incdtseverity for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE incdtseverity
CREATE TABLE "incdtseverity" (
	"incdtseverity_id" INTEGER PRIMARY KEY,
	"incdtseverity_name" TEXT,
	"incdtseverity_order" INTEGER,
	"incdtseverity_descrip" TEXT
);

-- Class invchead of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table invchead for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE invchead
CREATE TABLE "invchead" (
	"invchead_id" INTEGER PRIMARY KEY,
	"invchead_cust_id" INTEGER,
	"invchead_shipto_id" INTEGER,
	"invchead_ordernumber" TEXT,
	"invchead_posted" BOOLEAN,
	"invchead_printed" BOOLEAN,
	"invchead_invcnumber" TEXT,
	"invchead_ponumber" TEXT,
	"invchead_shipvia" TEXT,
	"invchead_fob" TEXT,
	"invchead_billto_name" TEXT,
	"invchead_billto_address1" TEXT,
	"invchead_billto_address2" TEXT,
	"invchead_billto_address3" TEXT,
	"invchead_billto_city" TEXT,
	"invchead_billto_state" TEXT,
	"invchead_billto_zipcode" TEXT,
	"invchead_billto_phone" TEXT,
	"invchead_shipto_name" TEXT,
	"invchead_shipto_address1" TEXT,
	"invchead_shipto_address2" TEXT,
	"invchead_shipto_address3" TEXT,
	"invchead_shipto_city" TEXT,
	"invchead_shipto_state" TEXT,
	"invchead_shipto_zipcode" TEXT,
	"invchead_shipto_phone" TEXT,
	"invchead_salesrep_id" INTEGER,
	"invchead_terms_id" INTEGER,
	"invchead_misc_descrip" TEXT,
	"invchead_misc_accnt_id" INTEGER,
	"invchead_paymentref" TEXT,
	"invchead_notes" TEXT,
	"invchead_billto_country" TEXT,
	"invchead_shipto_country" TEXT,
	"invchead_prj_id" INTEGER,
	"invchead_curr_id" INTEGER,
	"invchead_taxauth_id" INTEGER,
	"invchead_tax_curr_id" INTEGER,
	"invchead_adjtax_id" INTEGER,
	"invchead_adjtaxtype_id" INTEGER,
	"invchead_freighttax_id" INTEGER,
	"invchead_freighttaxtype_id" INTEGER,
	"invchead_recurring" BOOLEAN,
	"invchead_recurring_interval" INTEGER,
	"invchead_recurring_type" TEXT,
	"invchead_recurring_invchead_id" INTEGER,
	"invchead_shipchrg_id" INTEGER
);

-- Class invcitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table invcitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE invcitem
CREATE TABLE "invcitem" (
	"invcitem_id" INTEGER PRIMARY KEY,
	"invcitem_invchead_id" INTEGER,
	"invcitem_linenumber" INTEGER,
	"invcitem_item_id" INTEGER,
	"invcitem_warehous_id" INTEGER,
	"invcitem_custpn" TEXT,
	"invcitem_number" TEXT,
	"invcitem_descrip" TEXT,
	"invcitem_notes" TEXT,
	"invcitem_salescat_id" INTEGER,
	"invcitem_tax_id" INTEGER,
	"invcitem_taxtype_id" INTEGER,
	"invcitem_qty_uom_id" INTEGER,
	"invcitem_price_uom_id" INTEGER,
	"invcitem_coitem_id" INTEGER
);

-- Class invcnt of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table invcnt for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE invcnt
CREATE TABLE "invcnt" (
	"invcnt_id" INTEGER PRIMARY KEY,
	"invcnt_itemsite_id" INTEGER,
	"invcnt_cnt_usr_id" INTEGER,
	"invcnt_posted" BOOLEAN,
	"invcnt_post_usr_id" INTEGER,
	"invcnt_comments" TEXT,
	"invcnt_priority" BOOLEAN,
	"invcnt_tag_usr_id" INTEGER,
	"invcnt_tagnumber" TEXT,
	"invcnt_invhist_id" INTEGER,
	"invcnt_location_id" INTEGER
);

-- Class invdetail of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table invdetail for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE invdetail
CREATE TABLE "invdetail" (
	"invdetail_id" INTEGER PRIMARY KEY,
	"invdetail_transtype" BPCHAR,
	"invdetail_invhist_id" INTEGER,
	"invdetail_location_id" INTEGER,
	"invdetail_comments" TEXT,
	"invdetail_invcitem_id" INTEGER,
	"invdetail_ls_id" INTEGER
);

-- Class invhist of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table invhist for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE invhist
CREATE TABLE "invhist" (
	"invhist_id" INTEGER PRIMARY KEY,
	"invhist_itemsite_id" INTEGER,
	"invhist_transtype" BPCHAR,
	"invhist_invuom" TEXT,
	"invhist_ordnumber" TEXT,
	"invhist_docnumber" TEXT,
	"invhist_acct_id" INTEGER,
	"invhist_xfer_warehous_id" INTEGER,
	"invhist_comments" TEXT,
	"invhist_posted" BOOLEAN,
	"invhist_imported" BOOLEAN,
	"invhist_hasdetail" BOOLEAN,
	"invhist_ordtype" TEXT,
	"invhist_analyze" BOOLEAN,
	"invhist_user" TEXT,
	"invhist_costmethod" BPCHAR
);

-- Class ipsass of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table ipsass for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE ipsass
CREATE TABLE "ipsass" (
	"ipsass_id" INTEGER PRIMARY KEY,
	"ipsass_ipshead_id" INTEGER,
	"ipsass_cust_id" INTEGER,
	"ipsass_custtype_id" INTEGER,
	"ipsass_custtype_pattern" TEXT,
	"ipsass_shipto_id" INTEGER,
	"ipsass_shipto_pattern" TEXT
);

-- Class ipsfreight of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table ipsfreight for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE ipsfreight
CREATE TABLE "ipsfreight" (
	"ipsfreight_id" INTEGER PRIMARY KEY,
	"ipsfreight_ipshead_id" INTEGER,
	"ipsfreight_type" BPCHAR,
	"ipsfreight_warehous_id" INTEGER,
	"ipsfreight_shipzone_id" INTEGER,
	"ipsfreight_freightclass_id" INTEGER,
	"ipsfreight_shipvia" TEXT
);

-- Class ipshead of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table ipshead for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE ipshead
CREATE TABLE "ipshead" (
	"ipshead_id" INTEGER PRIMARY KEY,
	"ipshead_name" TEXT,
	"ipshead_descrip" TEXT,
	"ipshead_curr_id" INTEGER
);

-- Class ipsitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table ipsitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE ipsitem
CREATE TABLE "ipsitem" (
	"ipsitem_id" INTEGER PRIMARY KEY,
	"ipsitem_ipshead_id" INTEGER,
	"ipsitem_item_id" INTEGER,
	"ipsitem_qty_uom_id" INTEGER,
	"ipsitem_price_uom_id" INTEGER
);

-- Class ipsitemchar of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table ipsitemchar for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE ipsitemchar
CREATE TABLE "ipsitemchar" (
	"ipsitemchar_id" INTEGER PRIMARY KEY,
	"ipsitemchar_ipsitem_id" INTEGER,
	"ipsitemchar_char_id" INTEGER,
	"ipsitemchar_value" TEXT
);

-- Class ipsprice of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table ipsprice for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE ipsprice
CREATE TABLE "ipsprice" (
	"ipsprice_id" INTEGER,
	"ipsprice_source" TEXT,
	"ipsprice_ipshead_id" INTEGER,
	"ipsprice_item_id" INTEGER
);

-- Class ipsprodcat of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table ipsprodcat for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE ipsprodcat
CREATE TABLE "ipsprodcat" (
	"ipsprodcat_id" INTEGER PRIMARY KEY,
	"ipsprodcat_ipshead_id" INTEGER,
	"ipsprodcat_prodcat_id" INTEGER
);

-- Class item of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table item for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE item
CREATE TABLE "item" (
	"item_id" INTEGER PRIMARY KEY,
	"item_number" TEXT,
	"item_descrip1" TEXT,
	"item_descrip2" TEXT,
	"item_classcode_id" INTEGER,
	"item_picklist" BOOLEAN,
	"item_comments" TEXT,
	"item_sold" BOOLEAN,
	"item_fractional" BOOLEAN,
	"item_active" BOOLEAN,
	"item_type" BPCHAR,
	"item_prodcat_id" INTEGER,
	"item_exclusive" BOOLEAN,
	"item_config" BOOLEAN,
	"item_extdescrip" TEXT,
	"item_upccode" TEXT,
	"item_planning_type" BPCHAR,
	"item_inv_uom_id" INTEGER,
	"item_price_uom_id" INTEGER,
	"item_warrdays" INTEGER,
	"item_freightclass_id" INTEGER
);

-- Class itemalias of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table itemalias for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE itemalias
CREATE TABLE "itemalias" (
	"itemalias_id" INTEGER PRIMARY KEY,
	"itemalias_item_id" INTEGER,
	"itemalias_number" TEXT,
	"itemalias_comments" TEXT,
	"itemalias_usedescrip" BOOLEAN,
	"itemalias_descrip1" TEXT,
	"itemalias_descrip2" TEXT
);

-- Class itemcost of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table itemcost for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE itemcost
CREATE TABLE "itemcost" (
	"itemcost_id" INTEGER PRIMARY KEY,
	"itemcost_item_id" INTEGER,
	"itemcost_costelem_id" INTEGER,
	"itemcost_lowlevel" BOOLEAN,
	"itemcost_curr_id" INTEGER
);

-- Class itemfile of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table itemfile for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE itemfile
CREATE TABLE "itemfile" (
	"itemfile_id" INTEGER,
	"itemfile_item_id" INTEGER,
	"itemfile_title" TEXT,
	"itemfile_url" TEXT
);

-- Class itemgrp of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table itemgrp for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE itemgrp
CREATE TABLE "itemgrp" (
	"itemgrp_id" INTEGER PRIMARY KEY,
	"itemgrp_name" TEXT,
	"itemgrp_descrip" TEXT
);

-- Class itemgrpitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table itemgrpitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE itemgrpitem
CREATE TABLE "itemgrpitem" (
	"itemgrpitem_id" INTEGER PRIMARY KEY,
	"itemgrpitem_itemgrp_id" INTEGER,
	"itemgrpitem_item_id" INTEGER
);

-- Class itemimage of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table itemimage for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE itemimage
CREATE TABLE "itemimage" (
	"itemimage_id" INTEGER,
	"itemimage_item_id" INTEGER,
	"itemimage_image_id" INTEGER,
	"itemimage_purpose" BPCHAR
);

-- Class itemloc of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table itemloc for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE itemloc
CREATE TABLE "itemloc" (
	"itemloc_id" INTEGER PRIMARY KEY,
	"itemloc_itemsite_id" INTEGER,
	"itemloc_location_id" INTEGER,
	"itemloc_consolflag" BOOLEAN,
	"itemloc_ls_id" INTEGER
);

-- Class itemlocdist of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table itemlocdist for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE itemlocdist
CREATE TABLE "itemlocdist" (
	"itemlocdist_id" INTEGER PRIMARY KEY,
	"itemlocdist_itemlocdist_id" INTEGER,
	"itemlocdist_source_type" BPCHAR,
	"itemlocdist_source_id" INTEGER,
	"itemlocdist_series" INTEGER,
	"itemlocdist_invhist_id" INTEGER,
	"itemlocdist_itemsite_id" INTEGER,
	"itemlocdist_reqlotserial" BOOLEAN,
	"itemlocdist_flush" BOOLEAN,
	"itemlocdist_distlotserial" BOOLEAN,
	"itemlocdist_ls_id" INTEGER,
	"itemlocdist_order_type" TEXT,
	"itemlocdist_order_id" INTEGER
);

-- Class itemlocpost of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table itemlocpost for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE itemlocpost
CREATE TABLE "itemlocpost" (
	"itemlocpost_id" INTEGER PRIMARY KEY,
	"itemlocpost_itemlocseries" INTEGER,
	"itemlocpost_glseq" INTEGER
);

-- Class itemsite of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table itemsite for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE itemsite
CREATE TABLE "itemsite" (
	"itemsite_id" INTEGER PRIMARY KEY,
	"itemsite_item_id" INTEGER,
	"itemsite_warehous_id" INTEGER,
	"itemsite_cyclecountfreq" INTEGER,
	"itemsite_supply" BOOLEAN,
	"itemsite_loccntrl" BOOLEAN,
	"itemsite_leadtime" INTEGER,
	"itemsite_abcclass" BPCHAR,
	"itemsite_issuemethod" BPCHAR,
	"itemsite_controlmethod" BPCHAR,
	"itemsite_active" BOOLEAN,
	"itemsite_plancode_id" INTEGER,
	"itemsite_costcat_id" INTEGER,
	"itemsite_eventfence" INTEGER,
	"itemsite_sold" BOOLEAN,
	"itemsite_stocked" BOOLEAN,
	"itemsite_freeze" BOOLEAN,
	"itemsite_location_id" INTEGER,
	"itemsite_useparams" BOOLEAN,
	"itemsite_useparamsmanual" BOOLEAN,
	"itemsite_soldranking" INTEGER,
	"itemsite_createpr" BOOLEAN,
	"itemsite_location" TEXT,
	"itemsite_location_comments" TEXT,
	"itemsite_notes" TEXT,
	"itemsite_perishable" BOOLEAN,
	"itemsite_autoabcclass" BOOLEAN,
	"itemsite_ordergroup" INTEGER,
	"itemsite_disallowblankwip" BOOLEAN,
	"itemsite_mps_timefence" INTEGER,
	"itemsite_createwo" BOOLEAN,
	"itemsite_warrpurc" BOOLEAN,
	"itemsite_autoreg" BOOLEAN,
	"itemsite_costmethod" BPCHAR,
	"itemsite_ordergroup_first" BOOLEAN
);

-- Class itemsrc of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table itemsrc for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE itemsrc
CREATE TABLE "itemsrc" (
	"itemsrc_id" INTEGER PRIMARY KEY,
	"itemsrc_item_id" INTEGER,
	"itemsrc_vend_id" INTEGER,
	"itemsrc_vend_item_number" TEXT,
	"itemsrc_vend_item_descrip" TEXT,
	"itemsrc_comments" TEXT,
	"itemsrc_vend_uom" TEXT,
	"itemsrc_leadtime" INTEGER,
	"itemsrc_ranking" INTEGER,
	"itemsrc_active" BOOLEAN,
	"itemsrc_manuf_name" TEXT,
	"itemsrc_manuf_item_number" TEXT,
	"itemsrc_manuf_item_descrip" TEXT
);

-- Class itemsrcp of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table itemsrcp for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE itemsrcp
CREATE TABLE "itemsrcp" (
	"itemsrcp_id" INTEGER PRIMARY KEY,
	"itemsrcp_itemsrc_id" INTEGER,
	"itemsrcp_curr_id" INTEGER
);

-- Class itemsub of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table itemsub for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE itemsub
CREATE TABLE "itemsub" (
	"itemsub_id" INTEGER PRIMARY KEY,
	"itemsub_parent_item_id" INTEGER,
	"itemsub_sub_item_id" INTEGER,
	"itemsub_rank" INTEGER
);

-- Class itemtax of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table itemtax for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE itemtax
CREATE TABLE "itemtax" (
	"itemtax_id" INTEGER PRIMARY KEY,
	"itemtax_item_id" INTEGER,
	"itemtax_taxauth_id" INTEGER,
	"itemtax_taxtype_id" INTEGER
);

-- Class itemtrans of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table itemtrans for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE itemtrans
CREATE TABLE "itemtrans" (
	"itemtrans_id" INTEGER PRIMARY KEY,
	"itemtrans_source_item_id" INTEGER,
	"itemtrans_target_item_id" INTEGER
);

-- Class itemuom of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table itemuom for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE itemuom
CREATE TABLE "itemuom" (
	"itemuom_id" INTEGER PRIMARY KEY,
	"itemuom_itemuomconv_id" INTEGER,
	"itemuom_uomtype_id" INTEGER
);

-- Class itemuomconv of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table itemuomconv for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE itemuomconv
CREATE TABLE "itemuomconv" (
	"itemuomconv_id" INTEGER PRIMARY KEY,
	"itemuomconv_item_id" INTEGER,
	"itemuomconv_from_uom_id" INTEGER,
	"itemuomconv_to_uom_id" INTEGER,
	"itemuomconv_fractional" BOOLEAN
);

-- Class jrnluse of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table jrnluse for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE jrnluse
CREATE TABLE "jrnluse" (
	"jrnluse_id" INTEGER PRIMARY KEY,
	"jrnluse_number" INTEGER,
	"jrnluse_use" TEXT
);

-- Class labelform of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table labelform for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE labelform
CREATE TABLE "labelform" (
	"labelform_id" INTEGER PRIMARY KEY,
	"labelform_name" TEXT,
	"labelform_report_id" INTEGER,
	"labelform_perpage" INTEGER
);

-- Class lang of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table lang for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE lang
CREATE TABLE "lang" (
	"lang_id" INTEGER PRIMARY KEY,
	"lang_qt_number" INTEGER,
	"lang_abbr3" TEXT,
	"lang_abbr2" TEXT,
	"lang_name" TEXT
);

-- Class locale of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table locale for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE locale
CREATE TABLE "locale" (
	"locale_id" INTEGER PRIMARY KEY,
	"locale_code" TEXT,
	"locale_descrip" TEXT,
	"locale_lang_file" TEXT,
	"locale_dateformat" TEXT,
	"locale_currformat" TEXT,
	"locale_qtyformat" TEXT,
	"locale_comments" TEXT,
	"locale_qtyperformat" TEXT,
	"locale_salespriceformat" TEXT,
	"locale_extpriceformat" TEXT,
	"locale_timeformat" TEXT,
	"locale_timestampformat" TEXT,
	"local_costformat" TEXT,
	"locale_costformat" TEXT,
	"locale_purchpriceformat" TEXT,
	"locale_uomratioformat" TEXT,
	"locale_intervalformat" TEXT,
	"locale_lang_id" INTEGER,
	"locale_country_id" INTEGER,
	"locale_error_color" TEXT,
	"locale_warning_color" TEXT,
	"locale_emphasis_color" TEXT,
	"locale_altemphasis_color" TEXT,
	"locale_expired_color" TEXT,
	"locale_future_color" TEXT,
	"locale_curr_scale" INTEGER,
	"locale_salesprice_scale" INTEGER,
	"locale_purchprice_scale" INTEGER,
	"locale_extprice_scale" INTEGER,
	"locale_cost_scale" INTEGER,
	"locale_qty_scale" INTEGER,
	"locale_qtyper_scale" INTEGER,
	"locale_uomratio_scale" INTEGER
);

-- Class location of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table location for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE location
CREATE TABLE "location" (
	"location_id" INTEGER PRIMARY KEY,
	"location_warehous_id" INTEGER,
	"location_name" TEXT,
	"location_descrip" TEXT,
	"location_restrict" BOOLEAN,
	"location_netable" BOOLEAN,
	"location_whsezone_id" INTEGER,
	"location_aisle" TEXT,
	"location_rack" TEXT,
	"location_bin" TEXT
);

-- Class locitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table locitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE locitem
CREATE TABLE "locitem" (
	"locitem_id" INTEGER PRIMARY KEY,
	"locitem_location_id" INTEGER,
	"locitem_item_id" INTEGER
);

-- Class metasql of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table metasql for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE metasql
CREATE TABLE "metasql" (
	"metasql_id" INTEGER PRIMARY KEY,
	"metasql_group" TEXT,
	"metasql_name" TEXT,
	"metasql_notes" TEXT,
	"metasql_query" TEXT,
	"metasql_lastuser" TEXT
);

-- Class metric of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table metric for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE metric
CREATE TABLE "metric" (
	"metric_id" INTEGER PRIMARY KEY,
	"metric_name" TEXT,
	"metric_value" TEXT,
	"metric_module" TEXT
);

-- Class metricenc of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table metricenc for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE metricenc
CREATE TABLE "metricenc" (
	"metricenc_id" INTEGER PRIMARY KEY,
	"metricenc_name" TEXT,
	"metricenc_module" TEXT
);

-- Class msg of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table msg for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE msg
CREATE TABLE "msg" (
	"msg_id" INTEGER PRIMARY KEY,
	"msg_text" TEXT,
	"msg_username" TEXT
);

-- Class msguser of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table msguser for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE msguser
CREATE TABLE "msguser" (
	"msguser_id" INTEGER PRIMARY KEY,
	"msguser_msg_id" INTEGER,
	"msguser_username" TEXT
);

-- Class obsolete_poheadcol of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table obsolete_poheadcol for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE obsolete_poheadcol
CREATE TABLE "obsolete_poheadcol" (
	"pohead_id" INTEGER,
	"pohead_release" INTEGER,
	"pohead_prj_id" INTEGER,
	"pohead_ppdcol" BPCHAR,
	"pohead_specmsg" TEXT
);

-- Class obsolete_poitemcol of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table obsolete_poitemcol for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE obsolete_poitemcol
CREATE TABLE "obsolete_poitemcol" (
	"poitem_id" INTEGER,
	"poitem_vend_id" INTEGER,
	"poitem_nocharge" BOOLEAN
);

-- Class ophead of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table ophead for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE ophead
CREATE TABLE "ophead" (
	"ophead_id" INTEGER PRIMARY KEY,
	"ophead_name" TEXT,
	"ophead_crmacct_id" INTEGER,
	"ophead_owner_username" TEXT,
	"ophead_opstage_id" INTEGER,
	"ophead_opsource_id" INTEGER,
	"ophead_optype_id" INTEGER,
	"ophead_probability_prcnt" INTEGER,
	"ophead_notes" TEXT,
	"ophead_curr_id" INTEGER
);

-- Class opsource of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table opsource for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE opsource
CREATE TABLE "opsource" (
	"opsource_id" INTEGER PRIMARY KEY,
	"opsource_name" TEXT,
	"opsource_descrip" TEXT
);

-- Class opstage of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table opstage for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE opstage
CREATE TABLE "opstage" (
	"opstage_id" INTEGER PRIMARY KEY,
	"opstage_name" TEXT,
	"opstage_descrip" TEXT,
	"opstage_order" INTEGER
);

-- Class optype of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table optype for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE optype
CREATE TABLE "optype" (
	"optype_id" INTEGER PRIMARY KEY,
	"optype_name" TEXT,
	"optype_descrip" TEXT
);

-- Class orderhead of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table orderhead for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE orderhead
CREATE TABLE "orderhead" (
	"orderhead_id" INTEGER,
	"orderhead_type" TEXT,
	"orderhead_number" TEXT,
	"orderhead_status" TEXT,
	"orderhead_linecount" INTEGER,
	"orderhead_from_id" INTEGER,
	"orderhead_from" TEXT,
	"orderhead_to_id" INTEGER,
	"orderhead_to" TEXT,
	"orderhead_curr_id" INTEGER,
	"orderhead_agent_username" TEXT,
	"orderhead_shipvia" TEXT
);

-- Class orderitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table orderitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE orderitem
CREATE TABLE "orderitem" (
	"orderitem_id" INTEGER,
	"orderitem_orderhead_type" TEXT,
	"orderitem_orderhead_id" INTEGER,
	"orderitem_linenumber" INTEGER,
	"orderitem_status" TEXT,
	"orderitem_itemsite_id" INTEGER,
	"orderitem_qty_uom_id" INTEGER,
	"orderitem_unitcost_curr_id" INTEGER,
	"orderitem_freight_curr_id" INTEGER
);

-- Class orderseq of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table orderseq for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE orderseq
CREATE TABLE "orderseq" (
	"orderseq_id" INTEGER PRIMARY KEY,
	"orderseq_name" TEXT,
	"orderseq_number" INTEGER,
	"orderseq_table" TEXT,
	"orderseq_numcol" TEXT
);

-- Class pack of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table pack for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE pack
CREATE TABLE "pack" (
	"pack_id" INTEGER PRIMARY KEY,
	"pack_head_id" INTEGER,
	"pack_head_type" TEXT,
	"pack_shiphead_id" INTEGER,
	"pack_printed" BOOLEAN
);

-- Class payaropen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table payaropen for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE payaropen
CREATE TABLE "payaropen" (
	"payaropen_ccpay_id" INTEGER PRIMARY KEY,
	"payaropen_aropen_id" INTEGER,
	"payaropen_curr_id" INTEGER
);

-- Class payco of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table payco for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE payco
CREATE TABLE "payco" (
	"payco_ccpay_id" INTEGER,
	"payco_cohead_id" INTEGER,
	"payco_curr_id" INTEGER
);

-- Class period of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table period for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE period
CREATE TABLE "period" (
	"period_id" INTEGER PRIMARY KEY,
	"period_closed" BOOLEAN,
	"period_freeze" BOOLEAN,
	"period_initial" BOOLEAN,
	"period_name" TEXT,
	"period_yearperiod_id" INTEGER,
	"period_quarter" INTEGER
);

-- Class pkgdep of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table pkgdep for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE pkgdep
CREATE TABLE "pkgdep" (
	"pkgdep_id" INTEGER PRIMARY KEY,
	"pkgdep_pkghead_id" INTEGER,
	"pkgdep_parent_pkghead_id" INTEGER
);

-- Class pkghead of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table pkghead for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE pkghead
CREATE TABLE "pkghead" (
	"pkghead_id" INTEGER PRIMARY KEY,
	"pkghead_name" TEXT,
	"pkghead_descrip" TEXT,
	"pkghead_version" TEXT,
	"pkghead_developer" TEXT,
	"pkghead_notes" TEXT,
	"pkghead_indev" BOOLEAN
);

-- Class pkgitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table pkgitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE pkgitem
CREATE TABLE "pkgitem" (
	"pkgitem_id" INTEGER PRIMARY KEY,
	"pkgitem_pkghead_id" INTEGER,
	"pkgitem_type" TEXT,
	"pkgitem_item_id" INTEGER,
	"pkgitem_name" TEXT,
	"pkgitem_descrip" TEXT
);

-- Class plancode of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table plancode for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE plancode
CREATE TABLE "plancode" (
	"plancode_id" INTEGER PRIMARY KEY,
	"plancode_code" TEXT,
	"plancode_name" TEXT,
	"plancode_mpsexplosion" BPCHAR,
	"plancode_consumefcst" BOOLEAN
);

-- Class pohead of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table pohead for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE pohead
CREATE TABLE "pohead" (
	"pohead_id" INTEGER PRIMARY KEY,
	"pohead_status" BPCHAR,
	"pohead_number" TEXT,
	"pohead_vend_id" INTEGER,
	"pohead_fob" TEXT,
	"pohead_shipvia" TEXT,
	"pohead_comments" TEXT,
	"pohead_printed" BOOLEAN,
	"pohead_terms_id" INTEGER,
	"pohead_warehous_id" INTEGER,
	"pohead_vendaddr_id" INTEGER,
	"pohead_agent_username" TEXT,
	"pohead_curr_id" INTEGER,
	"pohead_saved" BOOLEAN
);

-- Class poitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table poitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE poitem
CREATE TABLE "poitem" (
	"poitem_id" INTEGER PRIMARY KEY,
	"poitem_status" BPCHAR,
	"poitem_pohead_id" INTEGER,
	"poitem_linenumber" INTEGER,
	"poitem_wohead_id" INTEGER,
	"poitem_itemsite_id" INTEGER,
	"poitem_vend_item_descrip" TEXT,
	"poitem_vend_uom" TEXT,
	"poitem_vend_item_number" TEXT,
	"poitem_comments" TEXT,
	"poitem_expcat_id" INTEGER,
	"poitem_itemsrc_id" INTEGER,
	"poitem_soitem_id" INTEGER,
	"poitem_prj_id" INTEGER,
	"poitem_bom_rev_id" INTEGER,
	"poitem_boo_rev_id" INTEGER,
	"poitem_manuf_name" TEXT,
	"poitem_manuf_item_number" TEXT,
	"poitem_manuf_item_descrip" TEXT
);

-- Class porecv of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table porecv for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE porecv
CREATE TABLE "porecv" (
	"porecv_id" INTEGER,
	"porecv_ponumber" TEXT,
	"porecv_itemsite_id" INTEGER,
	"porecv_vend_id" INTEGER,
	"porecv_vend_item_number" TEXT,
	"porecv_vend_item_descrip" TEXT,
	"porecv_vend_uom" TEXT,
	"porecv_posted" BOOLEAN,
	"porecv_invoiced" BOOLEAN,
	"porecv_trans_usr_id" INTEGER,
	"porecv_poitem_id" INTEGER,
	"porecv_linenumber" INTEGER,
	"porecv_vohead_id" INTEGER,
	"porecv_agent_username" TEXT,
	"porecv_notes" TEXT,
	"porecv_curr_id" INTEGER,
	"porecv_voitem_id" INTEGER
);

-- Class poreject of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table poreject for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE poreject
CREATE TABLE "poreject" (
	"poreject_id" INTEGER PRIMARY KEY,
	"poreject_ponumber" TEXT,
	"poreject_itemsite_id" INTEGER,
	"poreject_vend_id" INTEGER,
	"poreject_vend_item_number" TEXT,
	"poreject_vend_item_descrip" TEXT,
	"poreject_vend_uom" TEXT,
	"poreject_posted" BOOLEAN,
	"poreject_rjctcode_id" INTEGER,
	"poreject_trans_usr_id" INTEGER,
	"poreject_poitem_id" INTEGER,
	"poreject_invoiced" BOOLEAN,
	"poreject_vohead_id" INTEGER,
	"poreject_agent_username" TEXT,
	"poreject_voitem_id" INTEGER
);

-- Class potype of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table potype for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE potype
CREATE TABLE "potype" (
	"potype_id" INTEGER PRIMARY KEY,
	"potype_name" TEXT,
	"potype_descrip" TEXT
);

-- Class pr of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table pr for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE pr
CREATE TABLE "pr" (
	"pr_id" INTEGER PRIMARY KEY,
	"pr_number" INTEGER,
	"pr_subnumber" INTEGER,
	"pr_status" BPCHAR,
	"pr_order_type" BPCHAR,
	"pr_order_id" INTEGER,
	"pr_poitem_id" INTEGER,
	"pr_itemsite_id" INTEGER,
	"pr_prj_id" INTEGER
);

-- Class prftcntr of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table prftcntr for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE prftcntr
CREATE TABLE "prftcntr" (
	"prftcntr_id" INTEGER PRIMARY KEY,
	"prftcntr_number" TEXT,
	"prftcntr_descrip" TEXT
);

-- Class priv of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table priv for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE priv
CREATE TABLE "priv" (
	"priv_id" INTEGER PRIMARY KEY,
	"priv_module" TEXT,
	"priv_name" TEXT,
	"priv_descrip" TEXT
);

-- Class prj of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table prj for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE prj
CREATE TABLE "prj" (
	"prj_id" INTEGER PRIMARY KEY,
	"prj_number" TEXT,
	"prj_name" TEXT,
	"prj_descrip" TEXT,
	"prj_status" BPCHAR,
	"prj_so" BOOLEAN,
	"prj_wo" BOOLEAN,
	"prj_po" BOOLEAN,
	"prj_owner_username" TEXT,
	"prj_usr_id" INTEGER
);

-- Class prjtask of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table prjtask for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE prjtask
CREATE TABLE "prjtask" (
	"prjtask_id" INTEGER PRIMARY KEY,
	"prjtask_number" TEXT,
	"prjtask_name" TEXT,
	"prjtask_descrip" TEXT,
	"prjtask_prj_id" INTEGER,
	"prjtask_anyuser" BOOLEAN,
	"prjtask_status" BPCHAR,
	"prjtask_owner_username" TEXT,
	"prjtask_usr_id" INTEGER
);

-- Class prjtaskuser of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table prjtaskuser for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE prjtaskuser
CREATE TABLE "prjtaskuser" (
	"prjtaskuser_id" INTEGER PRIMARY KEY,
	"prjtaskuser_prjtask_id" INTEGER,
	"prjtaskuser_usr_id" INTEGER
);

-- Class prodcat of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table prodcat for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE prodcat
CREATE TABLE "prodcat" (
	"prodcat_id" INTEGER PRIMARY KEY,
	"prodcat_code" TEXT,
	"prodcat_descrip" TEXT
);

-- Class prospect of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table prospect for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE prospect
CREATE TABLE "prospect" (
	"prospect_id" INTEGER PRIMARY KEY,
	"prospect_active" BOOLEAN,
	"prospect_number" TEXT,
	"prospect_name" TEXT,
	"prospect_cntct_id" INTEGER,
	"prospect_taxauth_id" INTEGER,
	"prospect_comments" TEXT,
	"prospect_salesrep_id" INTEGER,
	"prospect_warehous_id" INTEGER
);

-- Class quhead of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table quhead for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE quhead
CREATE TABLE "quhead" (
	"quhead_id" INTEGER PRIMARY KEY,
	"quhead_number" INTEGER,
	"quhead_cust_id" INTEGER,
	"quhead_shipto_id" INTEGER,
	"quhead_shiptoname" TEXT,
	"quhead_shiptoaddress1" TEXT,
	"quhead_shiptoaddress2" TEXT,
	"quhead_shiptoaddress3" TEXT,
	"quhead_shiptocity" TEXT,
	"quhead_shiptostate" TEXT,
	"quhead_shiptozipcode" TEXT,
	"quhead_shiptophone" TEXT,
	"quhead_salesrep_id" INTEGER,
	"quhead_tax_id" INTEGER,
	"quhead_terms_id" INTEGER,
	"quhead_origin" BPCHAR,
	"quhead_ordercomments" TEXT,
	"quhead_shipcomments" TEXT,
	"quhead_billtoname" TEXT,
	"quhead_billtoaddress1" TEXT,
	"quhead_billtoaddress2" TEXT,
	"quhead_billtoaddress3" TEXT,
	"quhead_billtocity" TEXT,
	"quhead_billtostate" TEXT,
	"quhead_billtozip" TEXT,
	"quhead_custponumber" TEXT,
	"quhead_fob" TEXT,
	"quhead_shipvia" TEXT,
	"quhead_warehous_id" INTEGER,
	"quhead_prj_id" INTEGER,
	"quhead_misc_accnt_id" INTEGER,
	"quhead_misc_descrip" TEXT,
	"quhead_billtocountry" TEXT,
	"quhead_shiptocountry" TEXT,
	"quhead_curr_id" INTEGER,
	"quhead_taxauth_id" INTEGER,
	"quhead_imported" BOOLEAN,
	"quhead_calcfreight" BOOLEAN,
	"quhead_shipto_cntct_id" INTEGER,
	"quhead_shipto_cntct_honorific" TEXT,
	"quhead_shipto_cntct_first_name" TEXT,
	"quhead_shipto_cntct_middle" TEXT,
	"quhead_shipto_cntct_last_name" TEXT,
	"quhead_shipto_cntct_suffix" TEXT,
	"quhead_shipto_cntct_phone" TEXT,
	"quhead_shipto_cntct_title" TEXT,
	"quhead_shipto_cntct_fax" TEXT,
	"quhead_shipto_cntct_email" TEXT,
	"quhead_billto_cntct_id" INTEGER,
	"quhead_billto_cntct_honorific" TEXT,
	"quhead_billto_cntct_first_name" TEXT,
	"quhead_billto_cntct_middle" TEXT,
	"quhead_billto_cntct_last_name" TEXT,
	"quhead_billto_cntct_suffix" TEXT,
	"quhead_billto_cntct_phone" TEXT,
	"quhead_billto_cntct_title" TEXT,
	"quhead_billto_cntct_fax" TEXT,
	"quhead_billto_cntct_email" TEXT
);

-- Class quitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table quitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE quitem
CREATE TABLE "quitem" (
	"quitem_id" INTEGER PRIMARY KEY,
	"quitem_quhead_id" INTEGER,
	"quitem_linenumber" INTEGER,
	"quitem_itemsite_id" INTEGER,
	"quitem_memo" TEXT,
	"quitem_custpn" TEXT,
	"quitem_createorder" BOOLEAN,
	"quitem_order_warehous_id" INTEGER,
	"quitem_item_id" INTEGER,
	"quitem_tax_id" INTEGER,
	"quitem_imported" BOOLEAN,
	"quitem_qty_uom_id" INTEGER,
	"quitem_price_uom_id" INTEGER
);

-- Class rcalitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table rcalitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE rcalitem
CREATE TABLE "rcalitem" (
	"rcalitem_id" INTEGER PRIMARY KEY,
	"rcalitem_calhead_id" INTEGER,
	"rcalitem_offsettype" BPCHAR,
	"rcalitem_offsetcount" INTEGER,
	"rcalitem_periodtype" BPCHAR,
	"rcalitem_periodcount" INTEGER,
	"rcalitem_name" TEXT
);

-- Class recv of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table recv for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE recv
CREATE TABLE "recv" (
	"recv_id" INTEGER PRIMARY KEY,
	"recv_order_type" TEXT,
	"recv_order_number" TEXT,
	"recv_orderitem_id" INTEGER,
	"recv_agent_username" TEXT,
	"recv_itemsite_id" INTEGER,
	"recv_vend_id" INTEGER,
	"recv_vend_item_number" TEXT,
	"recv_vend_item_descrip" TEXT,
	"recv_vend_uom" TEXT,
	"recv_purchcost_curr_id" INTEGER,
	"recv_recvcost_curr_id" INTEGER,
	"recv_freight_curr_id" INTEGER,
	"recv_posted" BOOLEAN,
	"recv_invoiced" BOOLEAN,
	"recv_vohead_id" INTEGER,
	"recv_voitem_id" INTEGER,
	"recv_trans_usr_name" TEXT,
	"recv_notes" TEXT,
	"recv_splitfrom_id" INTEGER
);

-- Class remitto of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table remitto for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE remitto
CREATE TABLE "remitto" (
	"remitto_name" TEXT,
	"remitto_address1" TEXT,
	"remitto_address2" TEXT,
	"remitto_address3" TEXT,
	"remitto_citystatezip" TEXT,
	"remitto_country" TEXT,
	"remitto_phone" TEXT
);

-- Class report of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE report
CREATE TABLE "report" (
	"report_id" INTEGER PRIMARY KEY,
	"report_name" TEXT,
	"report_sys" BOOLEAN,
	"report_source" TEXT,
	"report_descrip" TEXT,
	"report_grade" INTEGER
);

-- Class rjctcode of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table rjctcode for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE rjctcode
CREATE TABLE "rjctcode" (
	"rjctcode_id" INTEGER PRIMARY KEY,
	"rjctcode_code" TEXT,
	"rjctcode_descrip" TEXT
);

-- Class rsncode of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table rsncode for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE rsncode
CREATE TABLE "rsncode" (
	"rsncode_id" INTEGER PRIMARY KEY,
	"rsncode_code" TEXT,
	"rsncode_descrip" TEXT
);

-- Class sale of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table sale for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE sale
CREATE TABLE "sale" (
	"sale_id" INTEGER PRIMARY KEY,
	"sale_name" TEXT,
	"sale_descrip" TEXT,
	"sale_ipshead_id" INTEGER
);

-- Class salesaccnt of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table salesaccnt for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE salesaccnt
CREATE TABLE "salesaccnt" (
	"salesaccnt_id" INTEGER PRIMARY KEY,
	"salesaccnt_custtype_id" INTEGER,
	"salesaccnt_prodcat_id" INTEGER,
	"salesaccnt_warehous_id" INTEGER,
	"salesaccnt_sales_accnt_id" INTEGER,
	"salesaccnt_credit_accnt_id" INTEGER,
	"salesaccnt_cos_accnt_id" INTEGER,
	"salesaccnt_custtype" TEXT,
	"salesaccnt_prodcat" TEXT,
	"salesaccnt_returns_accnt_id" INTEGER,
	"salesaccnt_cor_accnt_id" INTEGER,
	"salesaccnt_cow_accnt_id" INTEGER
);

-- Class salescat of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table salescat for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE salescat
CREATE TABLE "salescat" (
	"salescat_id" INTEGER PRIMARY KEY,
	"salescat_active" BOOLEAN,
	"salescat_name" TEXT,
	"salescat_descrip" TEXT,
	"salescat_sales_accnt_id" INTEGER,
	"salescat_prepaid_accnt_id" INTEGER,
	"salescat_ar_accnt_id" INTEGER
);

-- Class saleshistory of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table saleshistory for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE saleshistory
CREATE TABLE "saleshistory" (
	"cohist_id" INTEGER,
	"cohist_cust_id" INTEGER,
	"cohist_itemsite_id" INTEGER,
	"cohist_shipvia" TEXT,
	"cohist_ordernumber" TEXT,
	"cohist_invcnumber" TEXT,
	"cohist_shipto_id" INTEGER,
	"cohist_salesrep_id" INTEGER,
	"cohist_imported" BOOLEAN,
	"cohist_billtoname" TEXT,
	"cohist_billtoaddress1" TEXT,
	"cohist_billtoaddress2" TEXT,
	"cohist_billtoaddress3" TEXT,
	"cohist_billtocity" TEXT,
	"cohist_billtostate" TEXT,
	"cohist_billtozip" TEXT,
	"cohist_shiptoname" TEXT,
	"cohist_shiptoaddress1" TEXT,
	"cohist_shiptoaddress2" TEXT,
	"cohist_shiptoaddress3" TEXT,
	"cohist_shiptocity" TEXT,
	"cohist_shiptostate" TEXT,
	"cohist_shiptozip" TEXT,
	"cohist_commissionpaid" BOOLEAN,
	"cohist_misc_type" BPCHAR,
	"cohist_misc_descrip" TEXT,
	"cohist_misc_id" INTEGER,
	"cohist_tax_id" INTEGER,
	"cohist_doctype" TEXT,
	"cohist_ponumber" TEXT,
	"cohist_curr_id" INTEGER,
	"cohist_sequence" INTEGER,
	"cohist_taxtype_id" INTEGER,
	"invoicenumber" TEXT,
	"cust_id" INTEGER,
	"cust_number" TEXT,
	"cust_name" TEXT,
	"cust_curr_id" INTEGER,
	"cust_custtype_id" INTEGER,
	"custtype_code" TEXT,
	"salesrep_number" TEXT,
	"salesrep_name" TEXT,
	"shipzone_id" INTEGER,
	"shipzone_name" TEXT,
	"itemsite_warehous_id" INTEGER,
	"itemsite_item_id" INTEGER,
	"item_number" TEXT,
	"item_descrip1" TEXT,
	"itemdescription" TEXT,
	"item_prodcat_id" INTEGER,
	"warehous_code" TEXT,
	"currabbr" TEXT,
	"cohist_invcdate_xtnullrole" TEXT,
	"cohist_qtyshipped_xtnumericrole" TEXT,
	"cohist_unitprice_xtnumericrole" TEXT,
	"baseunitprice_xtnumericrole" TEXT,
	"custunitprice_xtnumericrole" TEXT,
	"custextprice_xtnumericrole" TEXT,
	"extprice_xtnumericrole" TEXT,
	"baseextprice_xtnumericrole" TEXT,
	"cohist_unitcost_xtnumericrole" TEXT,
	"extcost_xtnumericrole" TEXT,
	"cohist_commission_xtnumericrole" TEXT,
	"basecommission_xtnumericrole" TEXT,
	"cohist_qtyshipped_xttotalrole" INTEGER,
	"custextprice_xttotalrole" INTEGER,
	"baseextprice_xttotalrole" INTEGER,
	"extcost_xttotalrole" INTEGER,
	"basecommission_xttotalrole" INTEGER
);

-- Class salesquoteitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table salesquoteitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE salesquoteitem
CREATE TABLE "salesquoteitem" (
	"orderitem_id" INTEGER,
	"orderitem_orderhead_type" TEXT,
	"orderitem_orderhead_id" INTEGER,
	"orderitem_linenumber" INTEGER,
	"orderitem_status" BPCHAR,
	"orderitem_itemsite_id" INTEGER,
	"orderitem_qty_uom_id" INTEGER,
	"orderitem_unitcost_curr_id" INTEGER,
	"orderitem_freight" TEXT,
	"orderitem_freight_received" TEXT,
	"orderitem_freight_curr_id" INTEGER
);

-- Class salesrep of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table salesrep for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE salesrep
CREATE TABLE "salesrep" (
	"salesrep_id" INTEGER PRIMARY KEY,
	"salesrep_active" BOOLEAN,
	"salesrep_number" TEXT,
	"salesrep_name" TEXT,
	"salesrep_method" BPCHAR,
	"salesrep_emp_id" INTEGER
);

-- Class script of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table script for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE script
CREATE TABLE "script" (
	"script_id" INTEGER PRIMARY KEY,
	"script_name" TEXT,
	"script_order" INTEGER,
	"script_enabled" BOOLEAN,
	"script_source" TEXT,
	"script_notes" TEXT
);

-- Class sequence of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table sequence for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE sequence
CREATE TABLE "sequence" (
	"sequence_value" INTEGER
);

-- Class shift of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table shift for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE shift
CREATE TABLE "shift" (
	"shift_id" INTEGER PRIMARY KEY,
	"shift_number" TEXT,
	"shift_name" TEXT
);

-- Class shipchrg of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table shipchrg for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE shipchrg
CREATE TABLE "shipchrg" (
	"shipchrg_id" INTEGER PRIMARY KEY,
	"shipchrg_name" TEXT,
	"shipchrg_descrip" TEXT,
	"shipchrg_custfreight" BOOLEAN,
	"shipchrg_handling" BPCHAR
);

-- Class shipdata of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table shipdata for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE shipdata
CREATE TABLE "shipdata" (
	"shipdata_cohead_number" TEXT,
	"shipdata_cosmisc_tracknum" TEXT,
	"shipdata_cosmisc_packnum_tracknum" TEXT,
	"shipdata_shipper" TEXT,
	"shipdata_billing_option" TEXT,
	"shipdata_package_type" TEXT,
	"shipdata_void_ind" BPCHAR,
	"shipdata_shiphead_number" TEXT,
	"shipdata_base_freight_curr_id" INTEGER,
	"shipdata_total_freight_curr_id" INTEGER
);

-- Class shipdatasum of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table shipdatasum for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE shipdatasum
CREATE TABLE "shipdatasum" (
	"shipdatasum_cohead_number" TEXT,
	"shipdatasum_cosmisc_tracknum" TEXT,
	"shipdatasum_cosmisc_packnum_tracknum" TEXT,
	"shipdatasum_shipper" TEXT,
	"shipdatasum_billing_option" TEXT,
	"shipdatasum_package_type" TEXT,
	"shipdatasum_shipped" BOOLEAN,
	"shipdatasum_shiphead_number" TEXT,
	"shipdatasum_base_freight_curr_id" INTEGER,
	"shipdatasum_total_freight_curr_id" INTEGER
);

-- Class shipform of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table shipform for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE shipform
CREATE TABLE "shipform" (
	"shipform_id" INTEGER PRIMARY KEY,
	"shipform_name" TEXT,
	"shipform_report_id" INTEGER
);

-- Class shiphead of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table shiphead for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE shiphead
CREATE TABLE "shiphead" (
	"shiphead_id" INTEGER PRIMARY KEY,
	"shiphead_order_id" INTEGER,
	"shiphead_order_type" TEXT,
	"shiphead_number" TEXT,
	"shiphead_shipvia" TEXT,
	"shiphead_freight_curr_id" INTEGER,
	"shiphead_notes" TEXT,
	"shiphead_shipped" BOOLEAN,
	"shiphead_shipchrg_id" INTEGER,
	"shiphead_shipform_id" INTEGER,
	"shiphead_sfstatus" BPCHAR,
	"shiphead_tracknum" TEXT
);

-- Class shipitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table shipitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE shipitem
CREATE TABLE "shipitem" (
	"shipitem_id" INTEGER PRIMARY KEY,
	"shipitem_orderitem_id" INTEGER,
	"shipitem_shiphead_id" INTEGER,
	"shipitem_shipped" BOOLEAN,
	"shipitem_trans_username" TEXT,
	"shipitem_invoiced" BOOLEAN,
	"shipitem_invcitem_id" INTEGER,
	"shipitem_invhist_id" INTEGER
);

-- Class shipto of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table shipto for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE shipto
CREATE TABLE "shipto" (
	"shipto_id" INTEGER PRIMARY KEY,
	"shipto_cust_id" INTEGER,
	"shipto_name" TEXT,
	"shipto_address1" TEXT,
	"shipto_address2" TEXT,
	"shipto_address3" TEXT,
	"shipto_city" TEXT,
	"shipto_state" TEXT,
	"shipto_zipcode" TEXT,
	"shipto_taxcode_id" INTEGER,
	"shipto_salesrep_id" INTEGER,
	"shipto_phone" TEXT,
	"shipto_comments" TEXT,
	"shipto_shipcomments" TEXT,
	"shipto_contact" TEXT,
	"shipto_fax" TEXT,
	"shipto_email" TEXT,
	"shipto_shipzone_id" INTEGER,
	"shipto_shipvia" TEXT,
	"shipto_shipform_id" INTEGER,
	"shipto_shipchrg_id" INTEGER,
	"shipto_active" BOOLEAN,
	"shipto_default" BOOLEAN,
	"shipto_num" TEXT,
	"shipto_ediprofile_id" INTEGER,
	"shipto_country" TEXT
);

-- Class shiptoinfo of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table shiptoinfo for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE shiptoinfo
CREATE TABLE "shiptoinfo" (
	"shipto_id" INTEGER PRIMARY KEY,
	"shipto_cust_id" INTEGER,
	"shipto_name" TEXT,
	"shipto_taxcode_id" INTEGER,
	"shipto_salesrep_id" INTEGER,
	"shipto_comments" TEXT,
	"shipto_shipcomments" TEXT,
	"shipto_shipzone_id" INTEGER,
	"shipto_shipvia" TEXT,
	"shipto_shipform_id" INTEGER,
	"shipto_shipchrg_id" INTEGER,
	"shipto_active" BOOLEAN,
	"shipto_default" BOOLEAN,
	"shipto_num" TEXT,
	"shipto_ediprofile_id" INTEGER,
	"shipto_cntct_id" INTEGER,
	"shipto_addr_id" INTEGER,
	"shipto_taxauth_id" INTEGER
);

-- Class shipvia of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table shipvia for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE shipvia
CREATE TABLE "shipvia" (
	"shipvia_id" INTEGER PRIMARY KEY,
	"shipvia_code" TEXT,
	"shipvia_descrip" TEXT
);

-- Class shipzone of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table shipzone for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE shipzone
CREATE TABLE "shipzone" (
	"shipzone_id" INTEGER PRIMARY KEY,
	"shipzone_name" TEXT,
	"shipzone_descrip" TEXT
);

-- Class sitetype of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table sitetype for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE sitetype
CREATE TABLE "sitetype" (
	"sitetype_id" INTEGER PRIMARY KEY,
	"sitetype_name" TEXT,
	"sitetype_descrip" TEXT
);

-- Class soheadlock of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table soheadlock for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE soheadlock
CREATE TABLE "soheadlock" (
	"soheadlock_sohead_id" INTEGER,
	"soheadlock_username" TEXT,
	"soheadlock_procpid" INTEGER
);

-- Class sopack of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table sopack for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE sopack
CREATE TABLE "sopack" (
	"sopack_id" INTEGER,
	"sopack_sohead_id" INTEGER,
	"sopack_printed" BOOLEAN,
	"sopack_cosmisc_id" INTEGER
);

-- Class stdjrnl of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table stdjrnl for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE stdjrnl
CREATE TABLE "stdjrnl" (
	"stdjrnl_id" INTEGER PRIMARY KEY,
	"stdjrnl_name" TEXT,
	"stdjrnl_descrip" TEXT,
	"stdjrnl_notes" TEXT
);

-- Class stdjrnlgrp of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table stdjrnlgrp for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE stdjrnlgrp
CREATE TABLE "stdjrnlgrp" (
	"stdjrnlgrp_id" INTEGER PRIMARY KEY,
	"stdjrnlgrp_name" TEXT,
	"stdjrnlgrp_descrip" TEXT
);

-- Class stdjrnlgrpitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table stdjrnlgrpitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE stdjrnlgrpitem
CREATE TABLE "stdjrnlgrpitem" (
	"stdjrnlgrpitem_id" INTEGER PRIMARY KEY,
	"stdjrnlgrpitem_stdjrnl_id" INTEGER,
	"stdjrnlgrpitem_toapply" INTEGER,
	"stdjrnlgrpitem_applied" INTEGER,
	"stdjrnlgrpitem_stdjrnlgrp_id" INTEGER
);

-- Class stdjrnlitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table stdjrnlitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE stdjrnlitem
CREATE TABLE "stdjrnlitem" (
	"stdjrnlitem_id" INTEGER PRIMARY KEY,
	"stdjrnlitem_stdjrnl_id" INTEGER,
	"stdjrnlitem_accnt_id" INTEGER,
	"stdjrnlitem_notes" TEXT
);

-- Class stdopn of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table stdopn for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE stdopn
CREATE TABLE "stdopn" (
	"stdopn_id" INTEGER PRIMARY KEY,
	"stdopn_number" TEXT,
	"stdopn_descrip1" TEXT,
	"stdopn_descrip2" TEXT,
	"stdopn_wrkcnt_id" INTEGER,
	"stdopn_toolref" TEXT,
	"stdopn_stdtimes" BOOLEAN,
	"stdopn_reportsetup" BOOLEAN,
	"stdopn_reportrun" BOOLEAN,
	"stdopn_produom" TEXT,
	"stdopn_sucosttype" BPCHAR,
	"stdopn_rncosttype" BPCHAR,
	"stdopn_instructions" TEXT
);

-- Class subaccnt of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table subaccnt for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE subaccnt
CREATE TABLE "subaccnt" (
	"subaccnt_id" INTEGER PRIMARY KEY,
	"subaccnt_number" TEXT,
	"subaccnt_descrip" TEXT
);

-- Class subaccnttype of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table subaccnttype for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE subaccnttype
CREATE TABLE "subaccnttype" (
	"subaccnttype_id" INTEGER PRIMARY KEY,
	"subaccnttype_accnt_type" BPCHAR,
	"subaccnttype_code" TEXT,
	"subaccnttype_descrip" TEXT
);

-- Class tax of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table tax for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE tax
CREATE TABLE "tax" (
	"tax_id" INTEGER PRIMARY KEY,
	"tax_code" TEXT,
	"tax_descrip" TEXT,
	"tax_sales_accnt_id" INTEGER,
	"tax_freight" BOOLEAN,
	"tax_cumulative" BOOLEAN,
	"tax_salesb_accnt_id" INTEGER,
	"tax_salesc_accnt_id" INTEGER
);

-- Class taxauth of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table taxauth for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE taxauth
CREATE TABLE "taxauth" (
	"taxauth_id" INTEGER PRIMARY KEY,
	"taxauth_code" TEXT,
	"taxauth_name" TEXT,
	"taxauth_extref" TEXT,
	"taxauth_addr_id" INTEGER,
	"taxauth_curr_id" INTEGER,
	"taxauth_county" TEXT,
	"taxauth_accnt_id" INTEGER
);

-- Class taxreg of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table taxreg for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE taxreg
CREATE TABLE "taxreg" (
	"taxreg_id" INTEGER PRIMARY KEY,
	"taxreg_rel_id" INTEGER,
	"taxreg_rel_type" BPCHAR,
	"taxreg_taxauth_id" INTEGER,
	"taxreg_number" TEXT
);

-- Class taxsel of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table taxsel for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE taxsel
CREATE TABLE "taxsel" (
	"taxsel_id" INTEGER PRIMARY KEY,
	"taxsel_taxauth_id" INTEGER,
	"taxsel_taxtype_id" INTEGER,
	"taxsel_tax_id" INTEGER
);

-- Class taxtype of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table taxtype for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE taxtype
CREATE TABLE "taxtype" (
	"taxtype_id" INTEGER PRIMARY KEY,
	"taxtype_name" TEXT,
	"taxtype_descrip" TEXT,
	"taxtype_sys" BOOLEAN
);

-- Class terms of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table terms for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE terms
CREATE TABLE "terms" (
	"terms_id" INTEGER PRIMARY KEY,
	"terms_code" TEXT,
	"terms_descrip" TEXT,
	"terms_type" BPCHAR,
	"terms_duedays" INTEGER,
	"terms_discdays" INTEGER,
	"terms_cutoffday" INTEGER,
	"terms_ap" BOOLEAN,
	"terms_ar" BOOLEAN
);

-- Class todoassoc of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table todoassoc for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE todoassoc
CREATE TABLE "todoassoc" (
	"todoassoc_id" INTEGER PRIMARY KEY,
	"todoassoc_todoitem_id" INTEGER,
	"todoassoc_other_id" INTEGER,
	"todoassoc_other_type" BPCHAR
);

-- Class todoitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table todoitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE todoitem
CREATE TABLE "todoitem" (
	"todoitem_id" INTEGER PRIMARY KEY,
	"todoitem_usr_id" INTEGER,
	"todoitem_name" TEXT,
	"todoitem_description" TEXT,
	"todoitem_incdt_id" INTEGER,
	"todoitem_creator_username" TEXT,
	"todoitem_status" BPCHAR,
	"todoitem_active" BOOLEAN,
	"todoitem_seq" INTEGER,
	"todoitem_notes" TEXT,
	"todoitem_crmacct_id" INTEGER,
	"todoitem_ophead_id" INTEGER,
	"todoitem_owner_username" TEXT,
	"todoitem_priority_id" INTEGER
);

-- Class trialbal of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table trialbal for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE trialbal
CREATE TABLE "trialbal" (
	"trialbal_id" INTEGER PRIMARY KEY,
	"trialbal_period_id" INTEGER,
	"trialbal_accnt_id" INTEGER,
	"trialbal_dirty" BOOLEAN
);

-- Class uiform of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table uiform for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE uiform
CREATE TABLE "uiform" (
	"uiform_id" INTEGER PRIMARY KEY,
	"uiform_name" TEXT,
	"uiform_order" INTEGER,
	"uiform_enabled" BOOLEAN,
	"uiform_source" TEXT,
	"uiform_notes" TEXT
);

-- Class uom of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table uom for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE uom
CREATE TABLE "uom" (
	"uom_id" INTEGER PRIMARY KEY,
	"uom_name" TEXT,
	"uom_descrip" TEXT,
	"uom_item_weight" BOOLEAN
);

-- Class uomconv of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table uomconv for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE uomconv
CREATE TABLE "uomconv" (
	"uomconv_id" INTEGER PRIMARY KEY,
	"uomconv_from_uom_id" INTEGER,
	"uomconv_to_uom_id" INTEGER,
	"uomconv_fractional" BOOLEAN
);

-- Class uomtype of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table uomtype for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE uomtype
CREATE TABLE "uomtype" (
	"uomtype_id" INTEGER PRIMARY KEY,
	"uomtype_name" TEXT,
	"uomtype_descrip" TEXT,
	"uomtype_multiple" BOOLEAN
);

-- Class url of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table url for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE url
CREATE TABLE "url" (
	"url_id" INTEGER PRIMARY KEY,
	"url_source_id" INTEGER,
	"url_source" TEXT,
	"url_title" TEXT,
	"url_url" TEXT
);

-- Class usr of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table usr for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE usr
CREATE TABLE "usr" (
	"usr_id" INTEGER PRIMARY KEY,
	"usr_username" TEXT,
	"usr_propername" TEXT,
	"usr_passwd" TEXT,
	"usr_locale_id" INTEGER,
	"usr_initials" TEXT,
	"usr_agent" BOOLEAN,
	"usr_active" BOOLEAN,
	"usr_email" TEXT,
	"usr_window" TEXT
);

-- Class usrgrp of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table usrgrp for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE usrgrp
CREATE TABLE "usrgrp" (
	"usrgrp_id" INTEGER PRIMARY KEY,
	"usrgrp_grp_id" INTEGER,
	"usrgrp_username" TEXT
);

-- Class usrpref of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table usrpref for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE usrpref
CREATE TABLE "usrpref" (
	"usrpref_id" INTEGER PRIMARY KEY,
	"usrpref_name" TEXT,
	"usrpref_value" TEXT,
	"usrpref_username" TEXT
);

-- Class usrpriv of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table usrpriv for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE usrpriv
CREATE TABLE "usrpriv" (
	"usrpriv_id" INTEGER PRIMARY KEY,
	"usrpriv_priv_id" INTEGER,
	"usrpriv_username" TEXT
);

-- Class vend of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table vend for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE vend
CREATE TABLE "vend" (
	"vend_id" INTEGER PRIMARY KEY,
	"vend_name" TEXT,
	"vend_address1" TEXT,
	"vend_address2" TEXT,
	"vend_address3" TEXT,
	"vend_city" TEXT,
	"vend_state" TEXT,
	"vend_zip" TEXT,
	"vend_contact1" TEXT,
	"vend_phone1" TEXT,
	"vend_contact2" TEXT,
	"vend_phone2" TEXT,
	"vend_active" BOOLEAN,
	"vend_po" BOOLEAN,
	"vend_comments" TEXT,
	"vend_pocomments" TEXT,
	"vend_number" TEXT,
	"vend_fax1" TEXT,
	"vend_fax2" TEXT,
	"vend_email1" TEXT,
	"vend_email2" TEXT,
	"vend_1099" BOOLEAN,
	"vend_exported" BOOLEAN,
	"vend_fobsource" BPCHAR,
	"vend_fob" TEXT,
	"vend_terms_id" INTEGER,
	"vend_shipvia" TEXT,
	"vend_vendtype_id" INTEGER,
	"vend_qualified" BOOLEAN,
	"vend_ediemail" TEXT,
	"vend_ediemailbody" TEXT,
	"vend_edisubject" TEXT,
	"vend_edifilename" TEXT,
	"vend_accntnum" TEXT,
	"vend_emailpodelivery" BOOLEAN,
	"vend_restrictpurch" BOOLEAN,
	"vend_edicc" TEXT,
	"vend_country" TEXT,
	"vend_curr_id" INTEGER
);

-- Class vendaddr of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table vendaddr for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE vendaddr
CREATE TABLE "vendaddr" (
	"vendaddr_id" INTEGER PRIMARY KEY,
	"vendaddr_vend_id" INTEGER,
	"vendaddr_code" TEXT,
	"vendaddr_name" TEXT,
	"vendaddr_address1" TEXT,
	"vendaddr_address2" TEXT,
	"vendaddr_address3" TEXT,
	"vendaddr_contact1" TEXT,
	"vendaddr_phone1" TEXT,
	"vendaddr_fax1" TEXT,
	"vendaddr_city" TEXT,
	"vendaddr_state" TEXT,
	"vendaddr_zipcode" TEXT,
	"vendaddr_country" TEXT
);

-- Class vendaddrinfo of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table vendaddrinfo for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE vendaddrinfo
CREATE TABLE "vendaddrinfo" (
	"vendaddr_id" INTEGER PRIMARY KEY,
	"vendaddr_vend_id" INTEGER,
	"vendaddr_code" TEXT,
	"vendaddr_name" TEXT,
	"vendaddr_comments" TEXT,
	"vendaddr_cntct_id" INTEGER,
	"vendaddr_addr_id" INTEGER,
	"vendaddr_taxauth_id" INTEGER
);

-- Class vendinfo of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table vendinfo for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE vendinfo
CREATE TABLE "vendinfo" (
	"vend_id" INTEGER PRIMARY KEY,
	"vend_name" TEXT,
	"vend_active" BOOLEAN,
	"vend_po" BOOLEAN,
	"vend_comments" TEXT,
	"vend_pocomments" TEXT,
	"vend_number" TEXT,
	"vend_1099" BOOLEAN,
	"vend_exported" BOOLEAN,
	"vend_fobsource" BPCHAR,
	"vend_fob" TEXT,
	"vend_terms_id" INTEGER,
	"vend_shipvia" TEXT,
	"vend_vendtype_id" INTEGER,
	"vend_qualified" BOOLEAN,
	"vend_ediemail" TEXT,
	"vend_ediemailbody" TEXT,
	"vend_edisubject" TEXT,
	"vend_edifilename" TEXT,
	"vend_accntnum" TEXT,
	"vend_emailpodelivery" BOOLEAN,
	"vend_restrictpurch" BOOLEAN,
	"vend_edicc" TEXT,
	"vend_curr_id" INTEGER,
	"vend_cntct1_id" INTEGER,
	"vend_cntct2_id" INTEGER,
	"vend_addr_id" INTEGER,
	"vend_match" BOOLEAN,
	"vend_taxauth_id" INTEGER,
	"vend_ach_enabled" BOOLEAN,
	"vend_ach_accnttype" TEXT,
	"vend_ach_use_vendinfo" BOOLEAN,
	"vend_ach_indiv_number" TEXT,
	"vend_ach_indiv_name" TEXT,
	"vend_ediemailhtml" BOOLEAN
);

-- Class vendtype of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table vendtype for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE vendtype
CREATE TABLE "vendtype" (
	"vendtype_id" INTEGER PRIMARY KEY,
	"vendtype_code" TEXT,
	"vendtype_descrip" TEXT
);

-- Class vodist of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table vodist for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE vodist
CREATE TABLE "vodist" (
	"vodist_id" INTEGER PRIMARY KEY,
	"vodist_poitem_id" INTEGER,
	"vodist_vohead_id" INTEGER,
	"vodist_costelem_id" INTEGER,
	"vodist_accnt_id" INTEGER,
	"vodist_expcat_id" INTEGER
);

-- Class vohead of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table vohead for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE vohead
CREATE TABLE "vohead" (
	"vohead_id" INTEGER PRIMARY KEY,
	"vohead_number" TEXT,
	"vohead_pohead_id" INTEGER,
	"vohead_posted" BOOLEAN,
	"vohead_invcnumber" TEXT,
	"vohead_1099" BOOLEAN,
	"vohead_reference" TEXT,
	"vohead_terms_id" INTEGER,
	"vohead_vend_id" INTEGER,
	"vohead_curr_id" INTEGER,
	"vohead_taxauth_id" INTEGER,
	"vohead_tax_curr_id" INTEGER,
	"vohead_adjtax_id" INTEGER,
	"vohead_adjtaxtype_id" INTEGER,
	"vohead_freighttax_id" INTEGER,
	"vohead_freighttaxtype_id" INTEGER,
	"vohead_misc" BOOLEAN
);

-- Class voitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table voitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE voitem
CREATE TABLE "voitem" (
	"voitem_id" INTEGER PRIMARY KEY,
	"voitem_vohead_id" INTEGER,
	"voitem_poitem_id" INTEGER,
	"voitem_close" BOOLEAN,
	"voitem_tax_id" INTEGER,
	"voitem_taxtype_id" INTEGER
);

-- Class voucheringeditlist of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table voucheringeditlist for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE voucheringeditlist
CREATE TABLE "voucheringeditlist" (
	"vendid" INTEGER,
	"orderid" INTEGER,
	"itemid" INTEGER,
	"vouchernumber" TEXT,
	"ponumber" TEXT,
	"invoicenumber" TEXT,
	"itemnumber" TEXT,
	"description" TEXT,
	"itemtype" TEXT,
	"iteminvuom" TEXT,
	"f_qty" TEXT,
	"f_cost" TEXT,
	"account" TEXT
);

-- Class warehous of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table warehous for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE warehous
CREATE TABLE "warehous" (
	"warehous_id" INTEGER PRIMARY KEY,
	"warehous_code" TEXT,
	"warehous_descrip" TEXT,
	"warehous_addr1" TEXT,
	"warehous_addr2" TEXT,
	"warehous_addr3" TEXT,
	"warehous_addr4" TEXT,
	"warehous_city" TEXT,
	"warehous_state" TEXT,
	"warehous_zip" TEXT,
	"warehous_country" TEXT,
	"warehous_fob" TEXT,
	"warehous_active" BOOLEAN,
	"warehous_sitetype_id" INTEGER,
	"warehous_counttag_prefix" TEXT,
	"warehous_counttag_number" INTEGER,
	"warehous_bol_prefix" TEXT,
	"warehous_bol_number" INTEGER,
	"warehous_shipping" BOOLEAN,
	"warehous_useslips" BOOLEAN,
	"warehous_usezones" BOOLEAN,
	"warehous_aislesize" INTEGER,
	"warehous_aislealpha" BOOLEAN,
	"warehous_racksize" INTEGER,
	"warehous_rackalpha" BOOLEAN,
	"warehous_binsize" INTEGER,
	"warehous_binalpha" BOOLEAN,
	"warehous_locationsize" INTEGER,
	"warehous_locationalpha" BOOLEAN,
	"warehous_enforcearbl" BOOLEAN,
	"warehous_default_accnt_id" INTEGER
);

-- Class whsezone of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table whsezone for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE whsezone
CREATE TABLE "whsezone" (
	"whsezone_id" INTEGER PRIMARY KEY,
	"whsezone_warehous_id" INTEGER,
	"whsezone_name" TEXT,
	"whsezone_descrip" TEXT
);

-- Class whsinfo of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table whsinfo for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE whsinfo
CREATE TABLE "whsinfo" (
	"warehous_id" INTEGER PRIMARY KEY,
	"warehous_code" TEXT,
	"warehous_descrip" TEXT,
	"warehous_fob" TEXT,
	"warehous_active" BOOLEAN,
	"warehous_counttag_prefix" TEXT,
	"warehous_counttag_number" INTEGER,
	"warehous_bol_prefix" TEXT,
	"warehous_bol_number" INTEGER,
	"warehous_shipping" BOOLEAN,
	"warehous_useslips" BOOLEAN,
	"warehous_usezones" BOOLEAN,
	"warehous_aislesize" INTEGER,
	"warehous_aislealpha" BOOLEAN,
	"warehous_racksize" INTEGER,
	"warehous_rackalpha" BOOLEAN,
	"warehous_binsize" INTEGER,
	"warehous_binalpha" BOOLEAN,
	"warehous_locationsize" INTEGER,
	"warehous_locationalpha" BOOLEAN,
	"warehous_enforcearbl" BOOLEAN,
	"warehous_default_accnt_id" INTEGER,
	"warehous_cntct_id" INTEGER,
	"warehous_addr_id" INTEGER,
	"warehous_taxauth_id" INTEGER,
	"warehous_transit" BOOLEAN,
	"warehous_shipform_id" INTEGER,
	"warehous_shipvia_id" INTEGER,
	"warehous_shipcomments" TEXT,
	"warehous_costcat_id" INTEGER,
	"warehous_sitetype_id" INTEGER
);

-- Class wo of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table wo for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE wo
CREATE TABLE "wo" (
	"wo_id" INTEGER PRIMARY KEY,
	"wo_number" INTEGER,
	"wo_subnumber" INTEGER,
	"wo_status" BPCHAR,
	"wo_itemsite_id" INTEGER,
	"wo_ordtype" BPCHAR,
	"wo_ordid" INTEGER,
	"wo_adhoc" BOOLEAN,
	"wo_itemcfg_series" INTEGER,
	"wo_imported" BOOLEAN,
	"wo_prodnotes" TEXT,
	"wo_prj_id" INTEGER,
	"wo_priority" INTEGER,
	"wo_bom_rev_id" INTEGER,
	"wo_boo_rev_id" INTEGER,
	"wo_cosmethod" BPCHAR
);

-- Class womatl of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table womatl for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE womatl
CREATE TABLE "womatl" (
	"womatl_id" INTEGER PRIMARY KEY,
	"womatl_wo_id" INTEGER,
	"womatl_itemsite_id" INTEGER,
	"womatl_picklist" BOOLEAN,
	"womatl_status" BPCHAR,
	"womatl_imported" BOOLEAN,
	"womatl_createwo" BOOLEAN,
	"womatl_issuemethod" BPCHAR,
	"womatl_wooper_id" INTEGER,
	"womatl_bomitem_id" INTEGER,
	"womatl_schedatwooper" BOOLEAN,
	"womatl_uom_id" INTEGER,
	"womatl_notes" TEXT,
	"womatl_ref" TEXT
);

-- Class womatlpost of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table womatlpost for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE womatlpost
CREATE TABLE "womatlpost" (
	"womatlpost_id" INTEGER PRIMARY KEY,
	"womatlpost_womatl_id" INTEGER,
	"womatlpost_invhist_id" INTEGER
);

-- Class womatlvar of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table womatlvar for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE womatlvar
CREATE TABLE "womatlvar" (
	"womatlvar_id" INTEGER PRIMARY KEY,
	"womatlvar_number" INTEGER,
	"womatlvar_subnumber" INTEGER,
	"womatlvar_parent_itemsite_id" INTEGER,
	"womatlvar_component_itemsite_id" INTEGER,
	"womatlvar_bomitem_id" INTEGER,
	"womatlvar_ref" TEXT,
	"womatlvar_notes" TEXT
);

-- Class woopervar of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table woopervar for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE woopervar
CREATE TABLE "woopervar" (
	"woopervar_id" INTEGER PRIMARY KEY,
	"woopervar_number" INTEGER,
	"woopervar_subnumber" INTEGER,
	"woopervar_parent_itemsite_id" INTEGER,
	"woopervar_booitem_id" INTEGER,
	"woopervar_wrkcnt_id" INTEGER,
	"woopervar_seqnumber" INTEGER
);

-- Class workglhead of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table workglhead for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE workglhead
CREATE TABLE "workglhead" (
	"workglhead_id" INTEGER PRIMARY KEY,
	"workglhead_usr_id" INTEGER
);

-- Class workglitem of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table workglitem for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE workglitem
CREATE TABLE "workglitem" (
	"workglitem_id" INTEGER PRIMARY KEY,
	"workglitem_workglhead_id" INTEGER,
	"workglitem_account" TEXT,
	"workglitem_account_desc" TEXT,
	"workglitem_accnt_type" BPCHAR,
	"workglitem_subaccnttype_code" TEXT
);

-- Class workgltotal of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table workgltotal for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE workgltotal
CREATE TABLE "workgltotal" (
	"workgltotal_id" INTEGER PRIMARY KEY,
	"workgltotal_workglhead_id" INTEGER
);

-- Class workgltotaleq of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table workgltotaleq for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE workgltotaleq
CREATE TABLE "workgltotaleq" (
	"workgltotaleq_id" INTEGER PRIMARY KEY,
	"workgltotaleq_workglhead_id" INTEGER
);

-- Class xsltmap of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table xsltmap for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE xsltmap
CREATE TABLE "xsltmap" (
	"xsltmap_id" INTEGER PRIMARY KEY,
	"xsltmap_name" TEXT,
	"xsltmap_doctype" TEXT,
	"xsltmap_system" TEXT,
	"xsltmap_import" TEXT,
	"xsltmap_export" TEXT
);

-- Class yearperiod of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table yearperiod for Postbooks_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE yearperiod
CREATE TABLE "yearperiod" (
	"yearperiod_id" INTEGER PRIMARY KEY,
	"yearperiod_closed" BOOLEAN
);

-- Class Currency of type FORM found.
				
-- Class Cobmisc of type FORM found.
				
-- Class Cohead of type FORM found.
				
-- Class cobmisc of type ENTITY found.

-- Generate application tables cobmisc for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class cohead of type ENTITY found.

-- Generate application tables cohead for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class curr_symbol of type ENTITY found.

-- Generate application tables curr_symbol for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class acalitem of type ENTITY found.

-- Generate application tables acalitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class accnt of type ENTITY found.

-- Generate application tables accnt for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class addr of type ENTITY found.

-- Generate application tables addr for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class alarm of type ENTITY found.

-- Generate application tables alarm for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class apaccnt of type ENTITY found.

-- Generate application tables apaccnt for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class apapply of type ENTITY found.

-- Generate application tables apapply for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class apchk of type ENTITY found.

-- Generate application tables apchk for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class apchkitem of type ENTITY found.

-- Generate application tables apchkitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class apcreditapply of type ENTITY found.

-- Generate application tables apcreditapply for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class apopen of type ENTITY found.

-- Generate application tables apopen for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class apselect of type ENTITY found.

-- Generate application tables apselect for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class araccnt of type ENTITY found.

-- Generate application tables araccnt for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class arapply of type ENTITY found.

-- Generate application tables arapply for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class arcreditapply of type ENTITY found.

-- Generate application tables arcreditapply for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class armemo of type ENTITY found.

-- Generate application tables armemo for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class aropen of type ENTITY found.

-- Generate application tables aropen for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class aropenco of type ENTITY found.

-- Generate application tables aropenco for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class asohist of type ENTITY found.

-- Generate application tables asohist for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class asshead of type ENTITY found.

-- Generate application tables asshead for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class assitem of type ENTITY found.

-- Generate application tables assitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class backup_ccpay of type ENTITY found.

-- Generate application tables backup_ccpay for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class backup_payco of type ENTITY found.

-- Generate application tables backup_payco for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class backup_usr of type ENTITY found.

-- Generate application tables backup_usr for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class bankaccnt of type ENTITY found.

-- Generate application tables bankaccnt for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class bankadj of type ENTITY found.

-- Generate application tables bankadj for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class bankadjtype of type ENTITY found.

-- Generate application tables bankadjtype for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class bankrec of type ENTITY found.

-- Generate application tables bankrec for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class bankrecitem of type ENTITY found.

-- Generate application tables bankrecitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class billingeditlist of type ENTITY found.

-- Generate application tables billingeditlist for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class bomhead of type ENTITY found.

-- Generate application tables bomhead for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class bomitem of type ENTITY found.

-- Generate application tables bomitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class bomitemsub of type ENTITY found.

-- Generate application tables bomitemsub for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class bomwork of type ENTITY found.

-- Generate application tables bomwork for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class brddist of type ENTITY found.

-- Generate application tables brddist for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class budget of type ENTITY found.

-- Generate application tables budget for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class budghead of type ENTITY found.

-- Generate application tables budghead for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class budgitem of type ENTITY found.

-- Generate application tables budgitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class calhead of type ENTITY found.

-- Generate application tables calhead for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class carrier of type ENTITY found.

-- Generate application tables carrier for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class cashrcpt of type ENTITY found.

-- Generate application tables cashrcpt for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class cashrcptitem of type ENTITY found.

-- Generate application tables cashrcptitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class cashrcptmisc of type ENTITY found.

-- Generate application tables cashrcptmisc for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class ccard of type ENTITY found.

-- Generate application tables ccard for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class ccardaud of type ENTITY found.

-- Generate application tables ccardaud for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class ccpay of type ENTITY found.

-- Generate application tables ccpay for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class char of type ENTITY found.

-- Generate application tables char for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class charass of type ENTITY found.

-- Generate application tables charass for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class checkhead of type ENTITY found.

-- Generate application tables checkhead for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class checkitem of type ENTITY found.

-- Generate application tables checkitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class checkrecip of type ENTITY found.

-- Generate application tables checkrecip for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class classcode of type ENTITY found.

-- Generate application tables classcode for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class cmd of type ENTITY found.

-- Generate application tables cmd for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class cmdarg of type ENTITY found.

-- Generate application tables cmdarg for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class cmhead of type ENTITY found.

-- Generate application tables cmhead for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class cmitem of type ENTITY found.

-- Generate application tables cmitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class cmnttype of type ENTITY found.

-- Generate application tables cmnttype for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class cntct of type ENTITY found.

-- Generate application tables cntct for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class cntslip of type ENTITY found.

-- Generate application tables cntslip for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class cobill of type ENTITY found.

-- Generate application tables cobill for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class cohist of type ENTITY found.

-- Generate application tables cohist for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class coitem of type ENTITY found.

-- Generate application tables coitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class comment of type ENTITY found.

-- Generate application tables comment for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class company of type ENTITY found.

-- Generate application tables company for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class coship of type ENTITY found.

-- Generate application tables coship for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class cosmisc of type ENTITY found.

-- Generate application tables cosmisc for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class costcat of type ENTITY found.

-- Generate application tables costcat for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class costelem of type ENTITY found.

-- Generate application tables costelem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class costhist of type ENTITY found.

-- Generate application tables costhist for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class costupdate of type ENTITY found.

-- Generate application tables costupdate for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class country of type ENTITY found.

-- Generate application tables country for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class creditmemoeditlist of type ENTITY found.

-- Generate application tables creditmemoeditlist for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class crmacct of type ENTITY found.

-- Generate application tables crmacct for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class curr of type ENTITY found.

-- Generate application tables curr for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class curr_rate of type ENTITY found.

-- Generate application tables curr_rate for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class cust of type ENTITY found.

-- Generate application tables cust for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class custform of type ENTITY found.

-- Generate application tables custform for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class custgrp of type ENTITY found.

-- Generate application tables custgrp for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class custgrpitem of type ENTITY found.

-- Generate application tables custgrpitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class custinfo of type ENTITY found.

-- Generate application tables custinfo for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class custtype of type ENTITY found.

-- Generate application tables custtype for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class dept of type ENTITY found.

-- Generate application tables dept for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class destination of type ENTITY found.

-- Generate application tables destination for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class ediprofile of type ENTITY found.

-- Generate application tables ediprofile for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class emp of type ENTITY found.

-- Generate application tables emp for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class empgrp of type ENTITY found.

-- Generate application tables empgrp for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class empgrpitem of type ENTITY found.

-- Generate application tables empgrpitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class evntlog of type ENTITY found.

-- Generate application tables evntlog for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class evntnot of type ENTITY found.

-- Generate application tables evntnot for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class evnttype of type ENTITY found.

-- Generate application tables evnttype for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class expcat of type ENTITY found.

-- Generate application tables expcat for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class flcol of type ENTITY found.

-- Generate application tables flcol for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class flgrp of type ENTITY found.

-- Generate application tables flgrp for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class flhead of type ENTITY found.

-- Generate application tables flhead for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class flitem of type ENTITY found.

-- Generate application tables flitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class flrpt of type ENTITY found.

-- Generate application tables flrpt for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class flspec of type ENTITY found.

-- Generate application tables flspec for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class form of type ENTITY found.

-- Generate application tables form for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class freightclass of type ENTITY found.

-- Generate application tables freightclass for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class glseries of type ENTITY found.

-- Generate application tables glseries for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class gltrans of type ENTITY found.

-- Generate application tables gltrans for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class grp of type ENTITY found.

-- Generate application tables grp for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class grppriv of type ENTITY found.

-- Generate application tables grppriv for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class headlock of type ENTITY found.

-- Generate application tables headlock for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class hnfc of type ENTITY found.

-- Generate application tables hnfc for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class image of type ENTITY found.

-- Generate application tables image for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class imageass of type ENTITY found.

-- Generate application tables imageass for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class incdt of type ENTITY found.

-- Generate application tables incdt for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class incdtcat of type ENTITY found.

-- Generate application tables incdtcat for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class incdthist of type ENTITY found.

-- Generate application tables incdthist for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class incdtpriority of type ENTITY found.

-- Generate application tables incdtpriority for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class incdtresolution of type ENTITY found.

-- Generate application tables incdtresolution for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class incdtseverity of type ENTITY found.

-- Generate application tables incdtseverity for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class invchead of type ENTITY found.

-- Generate application tables invchead for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class invcitem of type ENTITY found.

-- Generate application tables invcitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class invcnt of type ENTITY found.

-- Generate application tables invcnt for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class invdetail of type ENTITY found.

-- Generate application tables invdetail for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class invhist of type ENTITY found.

-- Generate application tables invhist for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class ipsass of type ENTITY found.

-- Generate application tables ipsass for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class ipsfreight of type ENTITY found.

-- Generate application tables ipsfreight for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class ipshead of type ENTITY found.

-- Generate application tables ipshead for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class ipsitem of type ENTITY found.

-- Generate application tables ipsitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class ipsitemchar of type ENTITY found.

-- Generate application tables ipsitemchar for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class ipsprice of type ENTITY found.

-- Generate application tables ipsprice for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class ipsprodcat of type ENTITY found.

-- Generate application tables ipsprodcat for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class item of type ENTITY found.

-- Generate application tables item for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class itemalias of type ENTITY found.

-- Generate application tables itemalias for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class itemcost of type ENTITY found.

-- Generate application tables itemcost for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class itemfile of type ENTITY found.

-- Generate application tables itemfile for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class itemgrp of type ENTITY found.

-- Generate application tables itemgrp for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class itemgrpitem of type ENTITY found.

-- Generate application tables itemgrpitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class itemimage of type ENTITY found.

-- Generate application tables itemimage for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class itemloc of type ENTITY found.

-- Generate application tables itemloc for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class itemlocdist of type ENTITY found.

-- Generate application tables itemlocdist for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class itemlocpost of type ENTITY found.

-- Generate application tables itemlocpost for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class itemsite of type ENTITY found.

-- Generate application tables itemsite for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class itemsrc of type ENTITY found.

-- Generate application tables itemsrc for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class itemsrcp of type ENTITY found.

-- Generate application tables itemsrcp for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class itemsub of type ENTITY found.

-- Generate application tables itemsub for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class itemtax of type ENTITY found.

-- Generate application tables itemtax for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class itemtrans of type ENTITY found.

-- Generate application tables itemtrans for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class itemuom of type ENTITY found.

-- Generate application tables itemuom for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class itemuomconv of type ENTITY found.

-- Generate application tables itemuomconv for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class jrnluse of type ENTITY found.

-- Generate application tables jrnluse for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class labelform of type ENTITY found.

-- Generate application tables labelform for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class lang of type ENTITY found.

-- Generate application tables lang for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class locale of type ENTITY found.

-- Generate application tables locale for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class location of type ENTITY found.

-- Generate application tables location for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class locitem of type ENTITY found.

-- Generate application tables locitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class metasql of type ENTITY found.

-- Generate application tables metasql for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class metric of type ENTITY found.

-- Generate application tables metric for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class metricenc of type ENTITY found.

-- Generate application tables metricenc for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class msg of type ENTITY found.

-- Generate application tables msg for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class msguser of type ENTITY found.

-- Generate application tables msguser for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class obsolete_poheadcol of type ENTITY found.

-- Generate application tables obsolete_poheadcol for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class obsolete_poitemcol of type ENTITY found.

-- Generate application tables obsolete_poitemcol for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class ophead of type ENTITY found.

-- Generate application tables ophead for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class opsource of type ENTITY found.

-- Generate application tables opsource for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class opstage of type ENTITY found.

-- Generate application tables opstage for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class optype of type ENTITY found.

-- Generate application tables optype for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class orderhead of type ENTITY found.

-- Generate application tables orderhead for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class orderitem of type ENTITY found.

-- Generate application tables orderitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class orderseq of type ENTITY found.

-- Generate application tables orderseq for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class pack of type ENTITY found.

-- Generate application tables pack for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class payaropen of type ENTITY found.

-- Generate application tables payaropen for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class payco of type ENTITY found.

-- Generate application tables payco for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class period of type ENTITY found.

-- Generate application tables period for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class pkgdep of type ENTITY found.

-- Generate application tables pkgdep for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class pkghead of type ENTITY found.

-- Generate application tables pkghead for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class pkgitem of type ENTITY found.

-- Generate application tables pkgitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class plancode of type ENTITY found.

-- Generate application tables plancode for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class pohead of type ENTITY found.

-- Generate application tables pohead for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class poitem of type ENTITY found.

-- Generate application tables poitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class porecv of type ENTITY found.

-- Generate application tables porecv for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class poreject of type ENTITY found.

-- Generate application tables poreject for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class potype of type ENTITY found.

-- Generate application tables potype for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class pr of type ENTITY found.

-- Generate application tables pr for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class prftcntr of type ENTITY found.

-- Generate application tables prftcntr for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class priv of type ENTITY found.

-- Generate application tables priv for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class prj of type ENTITY found.

-- Generate application tables prj for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class prjtask of type ENTITY found.

-- Generate application tables prjtask for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class prjtaskuser of type ENTITY found.

-- Generate application tables prjtaskuser for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class prodcat of type ENTITY found.

-- Generate application tables prodcat for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class prospect of type ENTITY found.

-- Generate application tables prospect for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class quhead of type ENTITY found.

-- Generate application tables quhead for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class quitem of type ENTITY found.

-- Generate application tables quitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class rcalitem of type ENTITY found.

-- Generate application tables rcalitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class recv of type ENTITY found.

-- Generate application tables recv for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class remitto of type ENTITY found.

-- Generate application tables remitto for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class report of type ENTITY found.

-- Generate application tables report for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class rjctcode of type ENTITY found.

-- Generate application tables rjctcode for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class rsncode of type ENTITY found.

-- Generate application tables rsncode for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class sale of type ENTITY found.

-- Generate application tables sale for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class salesaccnt of type ENTITY found.

-- Generate application tables salesaccnt for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class salescat of type ENTITY found.

-- Generate application tables salescat for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class saleshistory of type ENTITY found.

-- Generate application tables saleshistory for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class salesquoteitem of type ENTITY found.

-- Generate application tables salesquoteitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class salesrep of type ENTITY found.

-- Generate application tables salesrep for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class script of type ENTITY found.

-- Generate application tables script for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class sequence of type ENTITY found.

-- Generate application tables sequence for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class shift of type ENTITY found.

-- Generate application tables shift for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class shipchrg of type ENTITY found.

-- Generate application tables shipchrg for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class shipdata of type ENTITY found.

-- Generate application tables shipdata for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class shipdatasum of type ENTITY found.

-- Generate application tables shipdatasum for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class shipform of type ENTITY found.

-- Generate application tables shipform for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class shiphead of type ENTITY found.

-- Generate application tables shiphead for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class shipitem of type ENTITY found.

-- Generate application tables shipitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class shipto of type ENTITY found.

-- Generate application tables shipto for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class shiptoinfo of type ENTITY found.

-- Generate application tables shiptoinfo for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class shipvia of type ENTITY found.

-- Generate application tables shipvia for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class shipzone of type ENTITY found.

-- Generate application tables shipzone for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class sitetype of type ENTITY found.

-- Generate application tables sitetype for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class soheadlock of type ENTITY found.

-- Generate application tables soheadlock for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class sopack of type ENTITY found.

-- Generate application tables sopack for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class stdjrnl of type ENTITY found.

-- Generate application tables stdjrnl for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class stdjrnlgrp of type ENTITY found.

-- Generate application tables stdjrnlgrp for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class stdjrnlgrpitem of type ENTITY found.

-- Generate application tables stdjrnlgrpitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class stdjrnlitem of type ENTITY found.

-- Generate application tables stdjrnlitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class stdopn of type ENTITY found.

-- Generate application tables stdopn for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class subaccnt of type ENTITY found.

-- Generate application tables subaccnt for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class subaccnttype of type ENTITY found.

-- Generate application tables subaccnttype for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class tax of type ENTITY found.

-- Generate application tables tax for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class taxauth of type ENTITY found.

-- Generate application tables taxauth for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class taxreg of type ENTITY found.

-- Generate application tables taxreg for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class taxsel of type ENTITY found.

-- Generate application tables taxsel for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class taxtype of type ENTITY found.

-- Generate application tables taxtype for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class terms of type ENTITY found.

-- Generate application tables terms for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class todoassoc of type ENTITY found.

-- Generate application tables todoassoc for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class todoitem of type ENTITY found.

-- Generate application tables todoitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class trialbal of type ENTITY found.

-- Generate application tables trialbal for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class uiform of type ENTITY found.

-- Generate application tables uiform for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class uom of type ENTITY found.

-- Generate application tables uom for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class uomconv of type ENTITY found.

-- Generate application tables uomconv for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class uomtype of type ENTITY found.

-- Generate application tables uomtype for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class url of type ENTITY found.

-- Generate application tables url for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class usr of type ENTITY found.

-- Generate application tables usr for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class usrgrp of type ENTITY found.

-- Generate application tables usrgrp for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class usrpref of type ENTITY found.

-- Generate application tables usrpref for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class usrpriv of type ENTITY found.

-- Generate application tables usrpriv for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class vend of type ENTITY found.

-- Generate application tables vend for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class vendaddr of type ENTITY found.

-- Generate application tables vendaddr for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class vendaddrinfo of type ENTITY found.

-- Generate application tables vendaddrinfo for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class vendinfo of type ENTITY found.

-- Generate application tables vendinfo for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class vendtype of type ENTITY found.

-- Generate application tables vendtype for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class vodist of type ENTITY found.

-- Generate application tables vodist for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class vohead of type ENTITY found.

-- Generate application tables vohead for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class voitem of type ENTITY found.

-- Generate application tables voitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class voucheringeditlist of type ENTITY found.

-- Generate application tables voucheringeditlist for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class warehous of type ENTITY found.

-- Generate application tables warehous for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class whsezone of type ENTITY found.

-- Generate application tables whsezone for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class whsinfo of type ENTITY found.

-- Generate application tables whsinfo for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class wo of type ENTITY found.

-- Generate application tables wo for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class womatl of type ENTITY found.

-- Generate application tables womatl for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class womatlpost of type ENTITY found.

-- Generate application tables womatlpost for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class womatlvar of type ENTITY found.

-- Generate application tables womatlvar for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class woopervar of type ENTITY found.

-- Generate application tables woopervar for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class workglhead of type ENTITY found.

-- Generate application tables workglhead for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class workglitem of type ENTITY found.

-- Generate application tables workglitem for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class workgltotal of type ENTITY found.

-- Generate application tables workgltotal for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class workgltotaleq of type ENTITY found.

-- Generate application tables workgltotaleq for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class xsltmap of type ENTITY found.

-- Generate application tables xsltmap for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class yearperiod of type ENTITY found.

-- Generate application tables yearperiod for Postbooks_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Generate Sqlite application relations for table cobmisc for Postbooks_Entities
ALTER TABLE "cobmisc" ADD CONSTRAINT "cst_cobmisc_curr_symbol_curr_id" FOREIGN KEY ( "cobmisc_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

ALTER TABLE "cobmisc" ADD CONSTRAINT "cst_cobmisc_invchead_invchead_id" FOREIGN KEY ( "cobmisc_invchead_id" ) REFERENCES "invchead" ( "invchead_id" );

ALTER TABLE "cobmisc" ADD CONSTRAINT "cst_cobmisc_taxauth_taxauth_id" FOREIGN KEY ( "cobmisc_taxauth_id" ) REFERENCES "taxauth" ( "taxauth_id" );

ALTER TABLE "cobmisc" ADD CONSTRAINT "cst_cobmisc_curr_symbol_curr_id" FOREIGN KEY ( "cobmisc_tax_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

ALTER TABLE "cobmisc" ADD CONSTRAINT "cst_cobmisc_tax_tax_id" FOREIGN KEY ( "cobmisc_adjtax_id" ) REFERENCES "tax" ( "tax_id" );

ALTER TABLE "cobmisc" ADD CONSTRAINT "cst_cobmisc_taxtype_taxtype_id" FOREIGN KEY ( "cobmisc_adjtaxtype_id" ) REFERENCES "taxtype" ( "taxtype_id" );

ALTER TABLE "cobmisc" ADD CONSTRAINT "cst_cobmisc_tax_tax_id" FOREIGN KEY ( "cobmisc_freighttax_id" ) REFERENCES "tax" ( "tax_id" );

ALTER TABLE "cobmisc" ADD CONSTRAINT "cst_cobmisc_taxtype_taxtype_id" FOREIGN KEY ( "cobmisc_freighttaxtype_id" ) REFERENCES "taxtype" ( "taxtype_id" );

-- Generate Sqlite application relations for table cohead for Postbooks_Entities
ALTER TABLE "cohead" ADD CONSTRAINT "cst_cohead_custinfo_cust_id" FOREIGN KEY ( "cohead_cust_id" ) REFERENCES "custinfo" ( "cust_id" );

ALTER TABLE "cohead" ADD CONSTRAINT "cst_cohead_whsinfo_warehous_id" FOREIGN KEY ( "cohead_warehous_id" ) REFERENCES "whsinfo" ( "warehous_id" );

ALTER TABLE "cohead" ADD CONSTRAINT "cst_cohead_shiptoinfo_shipto_id" FOREIGN KEY ( "cohead_shipto_id" ) REFERENCES "shiptoinfo" ( "shipto_id" );

ALTER TABLE "cohead" ADD CONSTRAINT "cst_cohead_salesrep_salesrep_id" FOREIGN KEY ( "cohead_salesrep_id" ) REFERENCES "salesrep" ( "salesrep_id" );

ALTER TABLE "cohead" ADD CONSTRAINT "cst_cohead_terms_terms_id" FOREIGN KEY ( "cohead_terms_id" ) REFERENCES "terms" ( "terms_id" );

ALTER TABLE "cohead" ADD CONSTRAINT "cst_cohead_shipform_shipform_id" FOREIGN KEY ( "cohead_shipform_id" ) REFERENCES "shipform" ( "shipform_id" );

ALTER TABLE "cohead" ADD CONSTRAINT "cst_cohead_accnt_accnt_id" FOREIGN KEY ( "cohead_misc_accnt_id" ) REFERENCES "accnt" ( "accnt_id" );

ALTER TABLE "cohead" ADD CONSTRAINT "cst_cohead_prj_prj_id" FOREIGN KEY ( "cohead_prj_id" ) REFERENCES "prj" ( "prj_id" );

ALTER TABLE "cohead" ADD CONSTRAINT "cst_cohead_curr_symbol_curr_id" FOREIGN KEY ( "cohead_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

ALTER TABLE "cohead" ADD CONSTRAINT "cst_cohead_taxauth_taxauth_id" FOREIGN KEY ( "cohead_taxauth_id" ) REFERENCES "taxauth" ( "taxauth_id" );

-- Generate Sqlite application relations for table curr_symbol for Postbooks_Entities
-- Generate Sqlite application relations for table acalitem for Postbooks_Entities
-- Generate Sqlite application relations for table accnt for Postbooks_Entities
ALTER TABLE "accnt" ADD CONSTRAINT "cst_accnt_curr_symbol_curr_id" FOREIGN KEY ( "accnt_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

-- Generate Sqlite application relations for table addr for Postbooks_Entities
-- Generate Sqlite application relations for table alarm for Postbooks_Entities
-- Generate Sqlite application relations for table apaccnt for Postbooks_Entities
-- Generate Sqlite application relations for table apapply for Postbooks_Entities
ALTER TABLE "apapply" ADD CONSTRAINT "cst_apapply_curr_symbol_curr_id" FOREIGN KEY ( "apapply_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

-- Generate Sqlite application relations for table apchk for Postbooks_Entities
-- Generate Sqlite application relations for table apchkitem for Postbooks_Entities
-- Generate Sqlite application relations for table apcreditapply for Postbooks_Entities
ALTER TABLE "apcreditapply" ADD CONSTRAINT "cst_apcreditapply_curr_symbol_curr_id" FOREIGN KEY ( "apcreditapply_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

-- Generate Sqlite application relations for table apopen for Postbooks_Entities
ALTER TABLE "apopen" ADD CONSTRAINT "cst_apopen_curr_symbol_curr_id" FOREIGN KEY ( "apopen_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

-- Generate Sqlite application relations for table apselect for Postbooks_Entities
ALTER TABLE "apselect" ADD CONSTRAINT "cst_apselect_curr_symbol_curr_id" FOREIGN KEY ( "apselect_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

-- Generate Sqlite application relations for table araccnt for Postbooks_Entities
-- Generate Sqlite application relations for table arapply for Postbooks_Entities
ALTER TABLE "arapply" ADD CONSTRAINT "cst_arapply_curr_symbol_curr_id" FOREIGN KEY ( "arapply_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

-- Generate Sqlite application relations for table arcreditapply for Postbooks_Entities
ALTER TABLE "arcreditapply" ADD CONSTRAINT "cst_arcreditapply_curr_symbol_curr_id" FOREIGN KEY ( "arcreditapply_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

-- Generate Sqlite application relations for table armemo for Postbooks_Entities
ALTER TABLE "armemo" ADD CONSTRAINT "cst_armemo_curr_symbol_curr_id" FOREIGN KEY ( "armemo_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

-- Generate Sqlite application relations for table aropen for Postbooks_Entities
ALTER TABLE "aropen" ADD CONSTRAINT "cst_aropen_curr_symbol_curr_id" FOREIGN KEY ( "aropen_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

-- Generate Sqlite application relations for table aropenco for Postbooks_Entities
-- Generate Sqlite application relations for table asohist for Postbooks_Entities
ALTER TABLE "asohist" ADD CONSTRAINT "cst_asohist_curr_symbol_curr_id" FOREIGN KEY ( "asohist_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

ALTER TABLE "asohist" ADD CONSTRAINT "cst_asohist_taxtype_taxtype_id" FOREIGN KEY ( "asohist_taxtype_id" ) REFERENCES "taxtype" ( "taxtype_id" );

-- Generate Sqlite application relations for table asshead for Postbooks_Entities
-- Generate Sqlite application relations for table assitem for Postbooks_Entities
-- Generate Sqlite application relations for table backup_ccpay for Postbooks_Entities
-- Generate Sqlite application relations for table backup_payco for Postbooks_Entities
-- Generate Sqlite application relations for table backup_usr for Postbooks_Entities
-- Generate Sqlite application relations for table bankaccnt for Postbooks_Entities
ALTER TABLE "bankaccnt" ADD CONSTRAINT "cst_bankaccnt_curr_symbol_curr_id" FOREIGN KEY ( "bankaccnt_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

-- Generate Sqlite application relations for table bankadj for Postbooks_Entities
ALTER TABLE "bankadj" ADD CONSTRAINT "cst_bankadj_curr_symbol_curr_id" FOREIGN KEY ( "bankadj_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

-- Generate Sqlite application relations for table bankadjtype for Postbooks_Entities
-- Generate Sqlite application relations for table bankrec for Postbooks_Entities
-- Generate Sqlite application relations for table bankrecitem for Postbooks_Entities
-- Generate Sqlite application relations for table billingeditlist for Postbooks_Entities
-- Generate Sqlite application relations for table bomhead for Postbooks_Entities
ALTER TABLE "bomhead" ADD CONSTRAINT "cst_bomhead_item_item_id" FOREIGN KEY ( "bomhead_item_id" ) REFERENCES "item" ( "item_id" );

-- Generate Sqlite application relations for table bomitem for Postbooks_Entities
ALTER TABLE "bomitem" ADD CONSTRAINT "cst_bomitem_item_item_id" FOREIGN KEY ( "bomitem_parent_item_id" ) REFERENCES "item" ( "item_id" );

ALTER TABLE "bomitem" ADD CONSTRAINT "cst_bomitem_item_item_id" FOREIGN KEY ( "bomitem_item_id" ) REFERENCES "item" ( "item_id" );

ALTER TABLE "bomitem" ADD CONSTRAINT "cst_bomitem_uom_uom_id" FOREIGN KEY ( "bomitem_uom_id" ) REFERENCES "uom" ( "uom_id" );

ALTER TABLE "bomitem" ADD CONSTRAINT "cst_bomitem_char_char_id" FOREIGN KEY ( "bomitem_char_id" ) REFERENCES "char" ( "char_id" );

-- Generate Sqlite application relations for table bomitemsub for Postbooks_Entities
ALTER TABLE "bomitemsub" ADD CONSTRAINT "cst_bomitemsub_bomitem_bomitem_id" FOREIGN KEY ( "bomitemsub_bomitem_id" ) REFERENCES "bomitem" ( "bomitem_id" );

ALTER TABLE "bomitemsub" ADD CONSTRAINT "cst_bomitemsub_item_item_id" FOREIGN KEY ( "bomitemsub_item_id" ) REFERENCES "item" ( "item_id" );

-- Generate Sqlite application relations for table bomwork for Postbooks_Entities
ALTER TABLE "bomwork" ADD CONSTRAINT "cst_bomwork_char_char_id" FOREIGN KEY ( "bomwork_char_id" ) REFERENCES "char" ( "char_id" );

-- Generate Sqlite application relations for table brddist for Postbooks_Entities
-- Generate Sqlite application relations for table budget for Postbooks_Entities
-- Generate Sqlite application relations for table budghead for Postbooks_Entities
-- Generate Sqlite application relations for table budgitem for Postbooks_Entities
ALTER TABLE "budgitem" ADD CONSTRAINT "cst_budgitem_budghead_budghead_id" FOREIGN KEY ( "budgitem_budghead_id" ) REFERENCES "budghead" ( "budghead_id" );

ALTER TABLE "budgitem" ADD CONSTRAINT "cst_budgitem_period_period_id" FOREIGN KEY ( "budgitem_period_id" ) REFERENCES "period" ( "period_id" );

ALTER TABLE "budgitem" ADD CONSTRAINT "cst_budgitem_accnt_accnt_id" FOREIGN KEY ( "budgitem_accnt_id" ) REFERENCES "accnt" ( "accnt_id" );

-- Generate Sqlite application relations for table calhead for Postbooks_Entities
-- Generate Sqlite application relations for table carrier for Postbooks_Entities
-- Generate Sqlite application relations for table cashrcpt for Postbooks_Entities
ALTER TABLE "cashrcpt" ADD CONSTRAINT "cst_cashrcpt_custinfo_cust_id" FOREIGN KEY ( "cashrcpt_cust_id" ) REFERENCES "custinfo" ( "cust_id" );

ALTER TABLE "cashrcpt" ADD CONSTRAINT "cst_cashrcpt_bankaccnt_bankaccnt_id" FOREIGN KEY ( "cashrcpt_bankaccnt_id" ) REFERENCES "bankaccnt" ( "bankaccnt_id" );

ALTER TABLE "cashrcpt" ADD CONSTRAINT "cst_cashrcpt_curr_symbol_curr_id" FOREIGN KEY ( "cashrcpt_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

-- Generate Sqlite application relations for table cashrcptitem for Postbooks_Entities
ALTER TABLE "cashrcptitem" ADD CONSTRAINT "cst_cashrcptitem_cashrcpt_cashrcpt_id" FOREIGN KEY ( "cashrcptitem_cashrcpt_id" ) REFERENCES "cashrcpt" ( "cashrcpt_id" );

ALTER TABLE "cashrcptitem" ADD CONSTRAINT "cst_cashrcptitem_aropen_aropen_id" FOREIGN KEY ( "cashrcptitem_aropen_id" ) REFERENCES "aropen" ( "aropen_id" );

-- Generate Sqlite application relations for table cashrcptmisc for Postbooks_Entities
ALTER TABLE "cashrcptmisc" ADD CONSTRAINT "cst_cashrcptmisc_cashrcpt_cashrcpt_id" FOREIGN KEY ( "cashrcptmisc_cashrcpt_id" ) REFERENCES "cashrcpt" ( "cashrcpt_id" );

ALTER TABLE "cashrcptmisc" ADD CONSTRAINT "cst_cashrcptmisc_accnt_accnt_id" FOREIGN KEY ( "cashrcptmisc_accnt_id" ) REFERENCES "accnt" ( "accnt_id" );

-- Generate Sqlite application relations for table ccard for Postbooks_Entities
-- Generate Sqlite application relations for table ccardaud for Postbooks_Entities
-- Generate Sqlite application relations for table ccpay for Postbooks_Entities
-- Generate Sqlite application relations for table char for Postbooks_Entities
-- Generate Sqlite application relations for table charass for Postbooks_Entities
-- Generate Sqlite application relations for table checkhead for Postbooks_Entities
ALTER TABLE "checkhead" ADD CONSTRAINT "cst_checkhead_bankaccnt_bankaccnt_id" FOREIGN KEY ( "checkhead_bankaccnt_id" ) REFERENCES "bankaccnt" ( "bankaccnt_id" );

ALTER TABLE "checkhead" ADD CONSTRAINT "cst_checkhead_expcat_expcat_id" FOREIGN KEY ( "checkhead_expcat_id" ) REFERENCES "expcat" ( "expcat_id" );

ALTER TABLE "checkhead" ADD CONSTRAINT "cst_checkhead_curr_symbol_curr_id" FOREIGN KEY ( "checkhead_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

-- Generate Sqlite application relations for table checkitem for Postbooks_Entities
ALTER TABLE "checkitem" ADD CONSTRAINT "cst_checkitem_checkhead_checkhead_id" FOREIGN KEY ( "checkitem_checkhead_id" ) REFERENCES "checkhead" ( "checkhead_id" );

ALTER TABLE "checkitem" ADD CONSTRAINT "cst_checkitem_apopen_apopen_id" FOREIGN KEY ( "checkitem_apopen_id" ) REFERENCES "apopen" ( "apopen_id" );

ALTER TABLE "checkitem" ADD CONSTRAINT "cst_checkitem_aropen_aropen_id" FOREIGN KEY ( "checkitem_aropen_id" ) REFERENCES "aropen" ( "aropen_id" );

ALTER TABLE "checkitem" ADD CONSTRAINT "cst_checkitem_curr_symbol_curr_id" FOREIGN KEY ( "checkitem_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

-- Generate Sqlite application relations for table checkrecip for Postbooks_Entities
-- Generate Sqlite application relations for table classcode for Postbooks_Entities
-- Generate Sqlite application relations for table cmd for Postbooks_Entities
-- Generate Sqlite application relations for table cmdarg for Postbooks_Entities
ALTER TABLE "cmdarg" ADD CONSTRAINT "cst_cmdarg_cmd_cmd_id" FOREIGN KEY ( "cmdarg_cmd_id" ) REFERENCES "cmd" ( "cmd_id" );

-- Generate Sqlite application relations for table cmhead for Postbooks_Entities
ALTER TABLE "cmhead" ADD CONSTRAINT "cst_cmhead_curr_symbol_curr_id" FOREIGN KEY ( "cmhead_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

ALTER TABLE "cmhead" ADD CONSTRAINT "cst_cmhead_taxauth_taxauth_id" FOREIGN KEY ( "cmhead_taxauth_id" ) REFERENCES "taxauth" ( "taxauth_id" );

ALTER TABLE "cmhead" ADD CONSTRAINT "cst_cmhead_curr_symbol_curr_id" FOREIGN KEY ( "cmhead_tax_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

ALTER TABLE "cmhead" ADD CONSTRAINT "cst_cmhead_tax_tax_id" FOREIGN KEY ( "cmhead_adjtax_id" ) REFERENCES "tax" ( "tax_id" );

ALTER TABLE "cmhead" ADD CONSTRAINT "cst_cmhead_taxtype_taxtype_id" FOREIGN KEY ( "cmhead_adjtaxtype_id" ) REFERENCES "taxtype" ( "taxtype_id" );

ALTER TABLE "cmhead" ADD CONSTRAINT "cst_cmhead_tax_tax_id" FOREIGN KEY ( "cmhead_freighttax_id" ) REFERENCES "tax" ( "tax_id" );

ALTER TABLE "cmhead" ADD CONSTRAINT "cst_cmhead_taxtype_taxtype_id" FOREIGN KEY ( "cmhead_freighttaxtype_id" ) REFERENCES "taxtype" ( "taxtype_id" );

-- Generate Sqlite application relations for table cmitem for Postbooks_Entities
ALTER TABLE "cmitem" ADD CONSTRAINT "cst_cmitem_cmhead_cmhead_id" FOREIGN KEY ( "cmitem_cmhead_id" ) REFERENCES "cmhead" ( "cmhead_id" );

ALTER TABLE "cmitem" ADD CONSTRAINT "cst_cmitem_taxtype_taxtype_id" FOREIGN KEY ( "cmitem_taxtype_id" ) REFERENCES "taxtype" ( "taxtype_id" );

ALTER TABLE "cmitem" ADD CONSTRAINT "cst_cmitem_uom_uom_id" FOREIGN KEY ( "cmitem_qty_uom_id" ) REFERENCES "uom" ( "uom_id" );

ALTER TABLE "cmitem" ADD CONSTRAINT "cst_cmitem_uom_uom_id" FOREIGN KEY ( "cmitem_price_uom_id" ) REFERENCES "uom" ( "uom_id" );

-- Generate Sqlite application relations for table cmnttype for Postbooks_Entities
-- Generate Sqlite application relations for table cntct for Postbooks_Entities
ALTER TABLE "cntct" ADD CONSTRAINT "cst_cntct_crmacct_crmacct_id" FOREIGN KEY ( "cntct_crmacct_id" ) REFERENCES "crmacct" ( "crmacct_id" );

ALTER TABLE "cntct" ADD CONSTRAINT "cst_cntct_addr_addr_id" FOREIGN KEY ( "cntct_addr_id" ) REFERENCES "addr" ( "addr_id" );

-- Generate Sqlite application relations for table cntslip for Postbooks_Entities
-- Generate Sqlite application relations for table cobill for Postbooks_Entities
ALTER TABLE "cobill" ADD CONSTRAINT "cst_cobill_invcitem_invcitem_id" FOREIGN KEY ( "cobill_invcitem_id" ) REFERENCES "invcitem" ( "invcitem_id" );

ALTER TABLE "cobill" ADD CONSTRAINT "cst_cobill_taxtype_taxtype_id" FOREIGN KEY ( "cobill_taxtype_id" ) REFERENCES "taxtype" ( "taxtype_id" );

-- Generate Sqlite application relations for table cohist for Postbooks_Entities
ALTER TABLE "cohist" ADD CONSTRAINT "cst_cohist_curr_symbol_curr_id" FOREIGN KEY ( "cohist_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

ALTER TABLE "cohist" ADD CONSTRAINT "cst_cohist_taxtype_taxtype_id" FOREIGN KEY ( "cohist_taxtype_id" ) REFERENCES "taxtype" ( "taxtype_id" );

-- Generate Sqlite application relations for table coitem for Postbooks_Entities
ALTER TABLE "coitem" ADD CONSTRAINT "cst_coitem_cohead_cohead_id" FOREIGN KEY ( "coitem_cohead_id" ) REFERENCES "cohead" ( "cohead_id" );

ALTER TABLE "coitem" ADD CONSTRAINT "cst_coitem_itemsite_itemsite_id" FOREIGN KEY ( "coitem_itemsite_id" ) REFERENCES "itemsite" ( "itemsite_id" );

ALTER TABLE "coitem" ADD CONSTRAINT "cst_coitem_itemsite_itemsite_id" FOREIGN KEY ( "coitem_substitute_item_id" ) REFERENCES "itemsite" ( "itemsite_id" );

ALTER TABLE "coitem" ADD CONSTRAINT "cst_coitem_tax_tax_id" FOREIGN KEY ( "coitem_tax_id" ) REFERENCES "tax" ( "tax_id" );

ALTER TABLE "coitem" ADD CONSTRAINT "cst_coitem_uom_uom_id" FOREIGN KEY ( "coitem_qty_uom_id" ) REFERENCES "uom" ( "uom_id" );

ALTER TABLE "coitem" ADD CONSTRAINT "cst_coitem_uom_uom_id" FOREIGN KEY ( "coitem_price_uom_id" ) REFERENCES "uom" ( "uom_id" );

ALTER TABLE "coitem" ADD CONSTRAINT "cst_coitem_accnt_accnt_id" FOREIGN KEY ( "coitem_cos_accnt_id" ) REFERENCES "accnt" ( "accnt_id" );

-- Generate Sqlite application relations for table comment for Postbooks_Entities
ALTER TABLE "comment" ADD CONSTRAINT "cst_comment_cmnttype_cmnttype_id" FOREIGN KEY ( "comment_cmnttype_id" ) REFERENCES "cmnttype" ( "cmnttype_id" );

-- Generate Sqlite application relations for table company for Postbooks_Entities
-- Generate Sqlite application relations for table coship for Postbooks_Entities
-- Generate Sqlite application relations for table cosmisc for Postbooks_Entities
-- Generate Sqlite application relations for table costcat for Postbooks_Entities
ALTER TABLE "costcat" ADD CONSTRAINT "cst_costcat_accnt_accnt_id" FOREIGN KEY ( "costcat_toliability_accnt_id" ) REFERENCES "accnt" ( "accnt_id" );

-- Generate Sqlite application relations for table costelem for Postbooks_Entities
-- Generate Sqlite application relations for table costhist for Postbooks_Entities
ALTER TABLE "costhist" ADD CONSTRAINT "cst_costhist_curr_symbol_curr_id" FOREIGN KEY ( "costhist_oldcurr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

ALTER TABLE "costhist" ADD CONSTRAINT "cst_costhist_curr_symbol_curr_id" FOREIGN KEY ( "costhist_newcurr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

-- Generate Sqlite application relations for table costupdate for Postbooks_Entities
-- Generate Sqlite application relations for table country for Postbooks_Entities
-- Generate Sqlite application relations for table creditmemoeditlist for Postbooks_Entities
-- Generate Sqlite application relations for table crmacct for Postbooks_Entities
ALTER TABLE "crmacct" ADD CONSTRAINT "cst_crmacct_custinfo_cust_id" FOREIGN KEY ( "crmacct_cust_id" ) REFERENCES "custinfo" ( "cust_id" );

ALTER TABLE "crmacct" ADD CONSTRAINT "cst_crmacct_prospect_prospect_id" FOREIGN KEY ( "crmacct_prospect_id" ) REFERENCES "prospect" ( "prospect_id" );

ALTER TABLE "crmacct" ADD CONSTRAINT "cst_crmacct_cntct_cntct_id" FOREIGN KEY ( "crmacct_cntct_id_1" ) REFERENCES "cntct" ( "cntct_id" );

ALTER TABLE "crmacct" ADD CONSTRAINT "cst_crmacct_cntct_cntct_id" FOREIGN KEY ( "crmacct_cntct_id_2" ) REFERENCES "cntct" ( "cntct_id" );

ALTER TABLE "crmacct" ADD CONSTRAINT "cst_crmacct_crmacct_crmacct_id" FOREIGN KEY ( "crmacct_parent_id" ) REFERENCES "crmacct" ( "crmacct_id" );

ALTER TABLE "crmacct" ADD CONSTRAINT "cst_crmacct_taxauth_taxauth_id" FOREIGN KEY ( "crmacct_taxauth_id" ) REFERENCES "taxauth" ( "taxauth_id" );

-- Generate Sqlite application relations for table curr for Postbooks_Entities
-- Generate Sqlite application relations for table curr_rate for Postbooks_Entities
ALTER TABLE "curr_rate" ADD CONSTRAINT "cst_curr_rate_curr_symbol_curr_id" FOREIGN KEY ( "curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

-- Generate Sqlite application relations for table cust for Postbooks_Entities
-- Generate Sqlite application relations for table custform for Postbooks_Entities
-- Generate Sqlite application relations for table custgrp for Postbooks_Entities
-- Generate Sqlite application relations for table custgrpitem for Postbooks_Entities
-- Generate Sqlite application relations for table custinfo for Postbooks_Entities
ALTER TABLE "custinfo" ADD CONSTRAINT "cst_custinfo_custtype_custtype_id" FOREIGN KEY ( "cust_custtype_id" ) REFERENCES "custtype" ( "custtype_id" );

ALTER TABLE "custinfo" ADD CONSTRAINT "cst_custinfo_salesrep_salesrep_id" FOREIGN KEY ( "cust_salesrep_id" ) REFERENCES "salesrep" ( "salesrep_id" );

ALTER TABLE "custinfo" ADD CONSTRAINT "cst_custinfo_terms_terms_id" FOREIGN KEY ( "cust_terms_id" ) REFERENCES "terms" ( "terms_id" );

ALTER TABLE "custinfo" ADD CONSTRAINT "cst_custinfo_shipform_shipform_id" FOREIGN KEY ( "cust_shipform_id" ) REFERENCES "shipform" ( "shipform_id" );

ALTER TABLE "custinfo" ADD CONSTRAINT "cst_custinfo_curr_symbol_curr_id" FOREIGN KEY ( "cust_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

ALTER TABLE "custinfo" ADD CONSTRAINT "cst_custinfo_curr_symbol_curr_id" FOREIGN KEY ( "cust_creditlmt_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

ALTER TABLE "custinfo" ADD CONSTRAINT "cst_custinfo_cntct_cntct_id" FOREIGN KEY ( "cust_cntct_id" ) REFERENCES "cntct" ( "cntct_id" );

ALTER TABLE "custinfo" ADD CONSTRAINT "cst_custinfo_cntct_cntct_id" FOREIGN KEY ( "cust_corrcntct_id" ) REFERENCES "cntct" ( "cntct_id" );

ALTER TABLE "custinfo" ADD CONSTRAINT "cst_custinfo_taxauth_taxauth_id" FOREIGN KEY ( "cust_taxauth_id" ) REFERENCES "taxauth" ( "taxauth_id" );

-- Generate Sqlite application relations for table custtype for Postbooks_Entities
-- Generate Sqlite application relations for table dept for Postbooks_Entities
-- Generate Sqlite application relations for table destination for Postbooks_Entities
-- Generate Sqlite application relations for table ediprofile for Postbooks_Entities
-- Generate Sqlite application relations for table emp for Postbooks_Entities
ALTER TABLE "emp" ADD CONSTRAINT "cst_emp_cntct_cntct_id" FOREIGN KEY ( "emp_cntct_id" ) REFERENCES "cntct" ( "cntct_id" );

ALTER TABLE "emp" ADD CONSTRAINT "cst_emp_whsinfo_warehous_id" FOREIGN KEY ( "emp_warehous_id" ) REFERENCES "whsinfo" ( "warehous_id" );

ALTER TABLE "emp" ADD CONSTRAINT "cst_emp_emp_emp_id" FOREIGN KEY ( "emp_mgr_emp_id" ) REFERENCES "emp" ( "emp_id" );

ALTER TABLE "emp" ADD CONSTRAINT "cst_emp_curr_symbol_curr_id" FOREIGN KEY ( "emp_wage_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

ALTER TABLE "emp" ADD CONSTRAINT "cst_emp_dept_dept_id" FOREIGN KEY ( "emp_dept_id" ) REFERENCES "dept" ( "dept_id" );

ALTER TABLE "emp" ADD CONSTRAINT "cst_emp_shift_shift_id" FOREIGN KEY ( "emp_shift_id" ) REFERENCES "shift" ( "shift_id" );

ALTER TABLE "emp" ADD CONSTRAINT "cst_emp_usr_usr_id" FOREIGN KEY ( "emp_usr_id" ) REFERENCES "usr" ( "usr_id" );

ALTER TABLE "emp" ADD CONSTRAINT "cst_emp_image_image_id" FOREIGN KEY ( "emp_image_id" ) REFERENCES "image" ( "image_id" );

-- Generate Sqlite application relations for table empgrp for Postbooks_Entities
-- Generate Sqlite application relations for table empgrpitem for Postbooks_Entities
ALTER TABLE "empgrpitem" ADD CONSTRAINT "cst_empgrpitem_empgrp_empgrp_id" FOREIGN KEY ( "empgrpitem_empgrp_id" ) REFERENCES "empgrp" ( "empgrp_id" );

ALTER TABLE "empgrpitem" ADD CONSTRAINT "cst_empgrpitem_emp_emp_id" FOREIGN KEY ( "empgrpitem_emp_id" ) REFERENCES "emp" ( "emp_id" );

-- Generate Sqlite application relations for table evntlog for Postbooks_Entities
-- Generate Sqlite application relations for table evntnot for Postbooks_Entities
-- Generate Sqlite application relations for table evnttype for Postbooks_Entities
-- Generate Sqlite application relations for table expcat for Postbooks_Entities
-- Generate Sqlite application relations for table flcol for Postbooks_Entities
-- Generate Sqlite application relations for table flgrp for Postbooks_Entities
-- Generate Sqlite application relations for table flhead for Postbooks_Entities
-- Generate Sqlite application relations for table flitem for Postbooks_Entities
-- Generate Sqlite application relations for table flrpt for Postbooks_Entities
-- Generate Sqlite application relations for table flspec for Postbooks_Entities
-- Generate Sqlite application relations for table form for Postbooks_Entities
-- Generate Sqlite application relations for table freightclass for Postbooks_Entities
-- Generate Sqlite application relations for table glseries for Postbooks_Entities
-- Generate Sqlite application relations for table gltrans for Postbooks_Entities
-- Generate Sqlite application relations for table grp for Postbooks_Entities
-- Generate Sqlite application relations for table grppriv for Postbooks_Entities
ALTER TABLE "grppriv" ADD CONSTRAINT "cst_grppriv_grp_grp_id" FOREIGN KEY ( "grppriv_grp_id" ) REFERENCES "grp" ( "grp_id" );

-- Generate Sqlite application relations for table headlock for Postbooks_Entities
-- Generate Sqlite application relations for table hnfc for Postbooks_Entities
-- Generate Sqlite application relations for table image for Postbooks_Entities
-- Generate Sqlite application relations for table imageass for Postbooks_Entities
ALTER TABLE "imageass" ADD CONSTRAINT "cst_imageass_image_image_id" FOREIGN KEY ( "imageass_image_id" ) REFERENCES "image" ( "image_id" );

-- Generate Sqlite application relations for table incdt for Postbooks_Entities
ALTER TABLE "incdt" ADD CONSTRAINT "cst_incdt_crmacct_crmacct_id" FOREIGN KEY ( "incdt_crmacct_id" ) REFERENCES "crmacct" ( "crmacct_id" );

ALTER TABLE "incdt" ADD CONSTRAINT "cst_incdt_cntct_cntct_id" FOREIGN KEY ( "incdt_cntct_id" ) REFERENCES "cntct" ( "cntct_id" );

ALTER TABLE "incdt" ADD CONSTRAINT "cst_incdt_item_item_id" FOREIGN KEY ( "incdt_item_id" ) REFERENCES "item" ( "item_id" );

ALTER TABLE "incdt" ADD CONSTRAINT "cst_incdt_incdtcat_incdtcat_id" FOREIGN KEY ( "incdt_incdtcat_id" ) REFERENCES "incdtcat" ( "incdtcat_id" );

ALTER TABLE "incdt" ADD CONSTRAINT "cst_incdt_incdtseverity_incdtseverity_id" FOREIGN KEY ( "incdt_incdtseverity_id" ) REFERENCES "incdtseverity" ( "incdtseverity_id" );

ALTER TABLE "incdt" ADD CONSTRAINT "cst_incdt_incdtpriority_incdtpriority_id" FOREIGN KEY ( "incdt_incdtpriority_id" ) REFERENCES "incdtpriority" ( "incdtpriority_id" );

ALTER TABLE "incdt" ADD CONSTRAINT "cst_incdt_incdtresolution_incdtresolution_id" FOREIGN KEY ( "incdt_incdtresolution_id" ) REFERENCES "incdtresolution" ( "incdtresolution_id" );

ALTER TABLE "incdt" ADD CONSTRAINT "cst_incdt_aropen_aropen_id" FOREIGN KEY ( "incdt_aropen_id" ) REFERENCES "aropen" ( "aropen_id" );

-- Generate Sqlite application relations for table incdtcat for Postbooks_Entities
ALTER TABLE "incdtcat" ADD CONSTRAINT "cst_incdtcat_ediprofile_ediprofile_id" FOREIGN KEY ( "incdtcat_ediprofile_id" ) REFERENCES "ediprofile" ( "ediprofile_id" );

-- Generate Sqlite application relations for table incdthist for Postbooks_Entities
ALTER TABLE "incdthist" ADD CONSTRAINT "cst_incdthist_incdt_incdt_id" FOREIGN KEY ( "incdthist_incdt_id" ) REFERENCES "incdt" ( "incdt_id" );

-- Generate Sqlite application relations for table incdtpriority for Postbooks_Entities
-- Generate Sqlite application relations for table incdtresolution for Postbooks_Entities
-- Generate Sqlite application relations for table incdtseverity for Postbooks_Entities
-- Generate Sqlite application relations for table invchead for Postbooks_Entities
ALTER TABLE "invchead" ADD CONSTRAINT "cst_invchead_curr_symbol_curr_id" FOREIGN KEY ( "invchead_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

ALTER TABLE "invchead" ADD CONSTRAINT "cst_invchead_taxauth_taxauth_id" FOREIGN KEY ( "invchead_taxauth_id" ) REFERENCES "taxauth" ( "taxauth_id" );

ALTER TABLE "invchead" ADD CONSTRAINT "cst_invchead_curr_symbol_curr_id" FOREIGN KEY ( "invchead_tax_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

ALTER TABLE "invchead" ADD CONSTRAINT "cst_invchead_tax_tax_id" FOREIGN KEY ( "invchead_adjtax_id" ) REFERENCES "tax" ( "tax_id" );

ALTER TABLE "invchead" ADD CONSTRAINT "cst_invchead_taxtype_taxtype_id" FOREIGN KEY ( "invchead_adjtaxtype_id" ) REFERENCES "taxtype" ( "taxtype_id" );

ALTER TABLE "invchead" ADD CONSTRAINT "cst_invchead_tax_tax_id" FOREIGN KEY ( "invchead_freighttax_id" ) REFERENCES "tax" ( "tax_id" );

ALTER TABLE "invchead" ADD CONSTRAINT "cst_invchead_taxtype_taxtype_id" FOREIGN KEY ( "invchead_freighttaxtype_id" ) REFERENCES "taxtype" ( "taxtype_id" );

-- Generate Sqlite application relations for table invcitem for Postbooks_Entities
ALTER TABLE "invcitem" ADD CONSTRAINT "cst_invcitem_invchead_invchead_id" FOREIGN KEY ( "invcitem_invchead_id" ) REFERENCES "invchead" ( "invchead_id" );

ALTER TABLE "invcitem" ADD CONSTRAINT "cst_invcitem_taxtype_taxtype_id" FOREIGN KEY ( "invcitem_taxtype_id" ) REFERENCES "taxtype" ( "taxtype_id" );

ALTER TABLE "invcitem" ADD CONSTRAINT "cst_invcitem_uom_uom_id" FOREIGN KEY ( "invcitem_qty_uom_id" ) REFERENCES "uom" ( "uom_id" );

ALTER TABLE "invcitem" ADD CONSTRAINT "cst_invcitem_uom_uom_id" FOREIGN KEY ( "invcitem_price_uom_id" ) REFERENCES "uom" ( "uom_id" );

-- Generate Sqlite application relations for table invcnt for Postbooks_Entities
-- Generate Sqlite application relations for table invdetail for Postbooks_Entities
-- Generate Sqlite application relations for table invhist for Postbooks_Entities
-- Generate Sqlite application relations for table ipsass for Postbooks_Entities
ALTER TABLE "ipsass" ADD CONSTRAINT "cst_ipsass_ipshead_ipshead_id" FOREIGN KEY ( "ipsass_ipshead_id" ) REFERENCES "ipshead" ( "ipshead_id" );

-- Generate Sqlite application relations for table ipsfreight for Postbooks_Entities
ALTER TABLE "ipsfreight" ADD CONSTRAINT "cst_ipsfreight_ipshead_ipshead_id" FOREIGN KEY ( "ipsfreight_ipshead_id" ) REFERENCES "ipshead" ( "ipshead_id" );

ALTER TABLE "ipsfreight" ADD CONSTRAINT "cst_ipsfreight_whsinfo_warehous_id" FOREIGN KEY ( "ipsfreight_warehous_id" ) REFERENCES "whsinfo" ( "warehous_id" );

ALTER TABLE "ipsfreight" ADD CONSTRAINT "cst_ipsfreight_shipzone_shipzone_id" FOREIGN KEY ( "ipsfreight_shipzone_id" ) REFERENCES "shipzone" ( "shipzone_id" );

ALTER TABLE "ipsfreight" ADD CONSTRAINT "cst_ipsfreight_freightclass_freightclass_id" FOREIGN KEY ( "ipsfreight_freightclass_id" ) REFERENCES "freightclass" ( "freightclass_id" );

-- Generate Sqlite application relations for table ipshead for Postbooks_Entities
ALTER TABLE "ipshead" ADD CONSTRAINT "cst_ipshead_curr_symbol_curr_id" FOREIGN KEY ( "ipshead_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

-- Generate Sqlite application relations for table ipsitem for Postbooks_Entities
ALTER TABLE "ipsitem" ADD CONSTRAINT "cst_ipsitem_ipshead_ipshead_id" FOREIGN KEY ( "ipsitem_ipshead_id" ) REFERENCES "ipshead" ( "ipshead_id" );

ALTER TABLE "ipsitem" ADD CONSTRAINT "cst_ipsitem_item_item_id" FOREIGN KEY ( "ipsitem_item_id" ) REFERENCES "item" ( "item_id" );

ALTER TABLE "ipsitem" ADD CONSTRAINT "cst_ipsitem_uom_uom_id" FOREIGN KEY ( "ipsitem_qty_uom_id" ) REFERENCES "uom" ( "uom_id" );

ALTER TABLE "ipsitem" ADD CONSTRAINT "cst_ipsitem_uom_uom_id" FOREIGN KEY ( "ipsitem_price_uom_id" ) REFERENCES "uom" ( "uom_id" );

-- Generate Sqlite application relations for table ipsitemchar for Postbooks_Entities
ALTER TABLE "ipsitemchar" ADD CONSTRAINT "cst_ipsitemchar_ipsitem_ipsitem_id" FOREIGN KEY ( "ipsitemchar_ipsitem_id" ) REFERENCES "ipsitem" ( "ipsitem_id" );

ALTER TABLE "ipsitemchar" ADD CONSTRAINT "cst_ipsitemchar_char_char_id" FOREIGN KEY ( "ipsitemchar_char_id" ) REFERENCES "char" ( "char_id" );

-- Generate Sqlite application relations for table ipsprice for Postbooks_Entities
-- Generate Sqlite application relations for table ipsprodcat for Postbooks_Entities
-- Generate Sqlite application relations for table item for Postbooks_Entities
ALTER TABLE "item" ADD CONSTRAINT "cst_item_classcode_classcode_id" FOREIGN KEY ( "item_classcode_id" ) REFERENCES "classcode" ( "classcode_id" );

ALTER TABLE "item" ADD CONSTRAINT "cst_item_uom_uom_id" FOREIGN KEY ( "item_inv_uom_id" ) REFERENCES "uom" ( "uom_id" );

ALTER TABLE "item" ADD CONSTRAINT "cst_item_uom_uom_id" FOREIGN KEY ( "item_price_uom_id" ) REFERENCES "uom" ( "uom_id" );

ALTER TABLE "item" ADD CONSTRAINT "cst_item_freightclass_freightclass_id" FOREIGN KEY ( "item_freightclass_id" ) REFERENCES "freightclass" ( "freightclass_id" );

-- Generate Sqlite application relations for table itemalias for Postbooks_Entities
ALTER TABLE "itemalias" ADD CONSTRAINT "cst_itemalias_item_item_id" FOREIGN KEY ( "itemalias_item_id" ) REFERENCES "item" ( "item_id" );

-- Generate Sqlite application relations for table itemcost for Postbooks_Entities
ALTER TABLE "itemcost" ADD CONSTRAINT "cst_itemcost_item_item_id" FOREIGN KEY ( "itemcost_item_id" ) REFERENCES "item" ( "item_id" );

ALTER TABLE "itemcost" ADD CONSTRAINT "cst_itemcost_costelem_costelem_id" FOREIGN KEY ( "itemcost_costelem_id" ) REFERENCES "costelem" ( "costelem_id" );

ALTER TABLE "itemcost" ADD CONSTRAINT "cst_itemcost_curr_symbol_curr_id" FOREIGN KEY ( "itemcost_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

-- Generate Sqlite application relations for table itemfile for Postbooks_Entities
-- Generate Sqlite application relations for table itemgrp for Postbooks_Entities
-- Generate Sqlite application relations for table itemgrpitem for Postbooks_Entities
-- Generate Sqlite application relations for table itemimage for Postbooks_Entities
-- Generate Sqlite application relations for table itemloc for Postbooks_Entities
-- Generate Sqlite application relations for table itemlocdist for Postbooks_Entities
-- Generate Sqlite application relations for table itemlocpost for Postbooks_Entities
-- Generate Sqlite application relations for table itemsite for Postbooks_Entities
ALTER TABLE "itemsite" ADD CONSTRAINT "cst_itemsite_item_item_id" FOREIGN KEY ( "itemsite_item_id" ) REFERENCES "item" ( "item_id" );

ALTER TABLE "itemsite" ADD CONSTRAINT "cst_itemsite_whsinfo_warehous_id" FOREIGN KEY ( "itemsite_warehous_id" ) REFERENCES "whsinfo" ( "warehous_id" );

ALTER TABLE "itemsite" ADD CONSTRAINT "cst_itemsite_plancode_plancode_id" FOREIGN KEY ( "itemsite_plancode_id" ) REFERENCES "plancode" ( "plancode_id" );

ALTER TABLE "itemsite" ADD CONSTRAINT "cst_itemsite_costcat_costcat_id" FOREIGN KEY ( "itemsite_costcat_id" ) REFERENCES "costcat" ( "costcat_id" );

-- Generate Sqlite application relations for table itemsrc for Postbooks_Entities
ALTER TABLE "itemsrc" ADD CONSTRAINT "cst_itemsrc_item_item_id" FOREIGN KEY ( "itemsrc_item_id" ) REFERENCES "item" ( "item_id" );

ALTER TABLE "itemsrc" ADD CONSTRAINT "cst_itemsrc_vendinfo_vend_id" FOREIGN KEY ( "itemsrc_vend_id" ) REFERENCES "vendinfo" ( "vend_id" );

-- Generate Sqlite application relations for table itemsrcp for Postbooks_Entities
ALTER TABLE "itemsrcp" ADD CONSTRAINT "cst_itemsrcp_itemsrc_itemsrc_id" FOREIGN KEY ( "itemsrcp_itemsrc_id" ) REFERENCES "itemsrc" ( "itemsrc_id" );

ALTER TABLE "itemsrcp" ADD CONSTRAINT "cst_itemsrcp_curr_symbol_curr_id" FOREIGN KEY ( "itemsrcp_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

-- Generate Sqlite application relations for table itemsub for Postbooks_Entities
ALTER TABLE "itemsub" ADD CONSTRAINT "cst_itemsub_item_item_id" FOREIGN KEY ( "itemsub_parent_item_id" ) REFERENCES "item" ( "item_id" );

ALTER TABLE "itemsub" ADD CONSTRAINT "cst_itemsub_item_item_id" FOREIGN KEY ( "itemsub_sub_item_id" ) REFERENCES "item" ( "item_id" );

-- Generate Sqlite application relations for table itemtax for Postbooks_Entities
ALTER TABLE "itemtax" ADD CONSTRAINT "cst_itemtax_item_item_id" FOREIGN KEY ( "itemtax_item_id" ) REFERENCES "item" ( "item_id" );

ALTER TABLE "itemtax" ADD CONSTRAINT "cst_itemtax_taxauth_taxauth_id" FOREIGN KEY ( "itemtax_taxauth_id" ) REFERENCES "taxauth" ( "taxauth_id" );

ALTER TABLE "itemtax" ADD CONSTRAINT "cst_itemtax_taxtype_taxtype_id" FOREIGN KEY ( "itemtax_taxtype_id" ) REFERENCES "taxtype" ( "taxtype_id" );

-- Generate Sqlite application relations for table itemtrans for Postbooks_Entities
-- Generate Sqlite application relations for table itemuom for Postbooks_Entities
ALTER TABLE "itemuom" ADD CONSTRAINT "cst_itemuom_itemuomconv_itemuomconv_id" FOREIGN KEY ( "itemuom_itemuomconv_id" ) REFERENCES "itemuomconv" ( "itemuomconv_id" );

ALTER TABLE "itemuom" ADD CONSTRAINT "cst_itemuom_uomtype_uomtype_id" FOREIGN KEY ( "itemuom_uomtype_id" ) REFERENCES "uomtype" ( "uomtype_id" );

-- Generate Sqlite application relations for table itemuomconv for Postbooks_Entities
ALTER TABLE "itemuomconv" ADD CONSTRAINT "cst_itemuomconv_item_item_id" FOREIGN KEY ( "itemuomconv_item_id" ) REFERENCES "item" ( "item_id" );

ALTER TABLE "itemuomconv" ADD CONSTRAINT "cst_itemuomconv_uom_uom_id" FOREIGN KEY ( "itemuomconv_from_uom_id" ) REFERENCES "uom" ( "uom_id" );

ALTER TABLE "itemuomconv" ADD CONSTRAINT "cst_itemuomconv_uom_uom_id" FOREIGN KEY ( "itemuomconv_to_uom_id" ) REFERENCES "uom" ( "uom_id" );

-- Generate Sqlite application relations for table jrnluse for Postbooks_Entities
-- Generate Sqlite application relations for table labelform for Postbooks_Entities
-- Generate Sqlite application relations for table lang for Postbooks_Entities
-- Generate Sqlite application relations for table locale for Postbooks_Entities
-- Generate Sqlite application relations for table location for Postbooks_Entities
-- Generate Sqlite application relations for table locitem for Postbooks_Entities
-- Generate Sqlite application relations for table metasql for Postbooks_Entities
-- Generate Sqlite application relations for table metric for Postbooks_Entities
-- Generate Sqlite application relations for table metricenc for Postbooks_Entities
-- Generate Sqlite application relations for table msg for Postbooks_Entities
-- Generate Sqlite application relations for table msguser for Postbooks_Entities
-- Generate Sqlite application relations for table obsolete_poheadcol for Postbooks_Entities
-- Generate Sqlite application relations for table obsolete_poitemcol for Postbooks_Entities
-- Generate Sqlite application relations for table ophead for Postbooks_Entities
ALTER TABLE "ophead" ADD CONSTRAINT "cst_ophead_crmacct_crmacct_id" FOREIGN KEY ( "ophead_crmacct_id" ) REFERENCES "crmacct" ( "crmacct_id" );

ALTER TABLE "ophead" ADD CONSTRAINT "cst_ophead_opstage_opstage_id" FOREIGN KEY ( "ophead_opstage_id" ) REFERENCES "opstage" ( "opstage_id" );

ALTER TABLE "ophead" ADD CONSTRAINT "cst_ophead_opsource_opsource_id" FOREIGN KEY ( "ophead_opsource_id" ) REFERENCES "opsource" ( "opsource_id" );

ALTER TABLE "ophead" ADD CONSTRAINT "cst_ophead_optype_optype_id" FOREIGN KEY ( "ophead_optype_id" ) REFERENCES "optype" ( "optype_id" );

-- Generate Sqlite application relations for table opsource for Postbooks_Entities
-- Generate Sqlite application relations for table opstage for Postbooks_Entities
-- Generate Sqlite application relations for table optype for Postbooks_Entities
-- Generate Sqlite application relations for table orderhead for Postbooks_Entities
-- Generate Sqlite application relations for table orderitem for Postbooks_Entities
-- Generate Sqlite application relations for table orderseq for Postbooks_Entities
-- Generate Sqlite application relations for table pack for Postbooks_Entities
ALTER TABLE "pack" ADD CONSTRAINT "cst_pack_shiphead_shiphead_id" FOREIGN KEY ( "pack_shiphead_id" ) REFERENCES "shiphead" ( "shiphead_id" );

-- Generate Sqlite application relations for table payaropen for Postbooks_Entities
-- Generate Sqlite application relations for table payco for Postbooks_Entities
ALTER TABLE "payco" ADD CONSTRAINT "cst_payco_ccpay_ccpay_id" FOREIGN KEY ( "payco_ccpay_id" ) REFERENCES "ccpay" ( "ccpay_id" );

ALTER TABLE "payco" ADD CONSTRAINT "cst_payco_cohead_cohead_id" FOREIGN KEY ( "payco_cohead_id" ) REFERENCES "cohead" ( "cohead_id" );

-- Generate Sqlite application relations for table period for Postbooks_Entities
-- Generate Sqlite application relations for table pkgdep for Postbooks_Entities
ALTER TABLE "pkgdep" ADD CONSTRAINT "cst_pkgdep_pkghead_pkghead_id" FOREIGN KEY ( "pkgdep_pkghead_id" ) REFERENCES "pkghead" ( "pkghead_id" );

ALTER TABLE "pkgdep" ADD CONSTRAINT "cst_pkgdep_pkghead_pkghead_id" FOREIGN KEY ( "pkgdep_parent_pkghead_id" ) REFERENCES "pkghead" ( "pkghead_id" );

-- Generate Sqlite application relations for table pkghead for Postbooks_Entities
-- Generate Sqlite application relations for table pkgitem for Postbooks_Entities
ALTER TABLE "pkgitem" ADD CONSTRAINT "cst_pkgitem_pkghead_pkghead_id" FOREIGN KEY ( "pkgitem_pkghead_id" ) REFERENCES "pkghead" ( "pkghead_id" );

-- Generate Sqlite application relations for table plancode for Postbooks_Entities
-- Generate Sqlite application relations for table pohead for Postbooks_Entities
ALTER TABLE "pohead" ADD CONSTRAINT "cst_pohead_vendinfo_vend_id" FOREIGN KEY ( "pohead_vend_id" ) REFERENCES "vendinfo" ( "vend_id" );

ALTER TABLE "pohead" ADD CONSTRAINT "cst_pohead_terms_terms_id" FOREIGN KEY ( "pohead_terms_id" ) REFERENCES "terms" ( "terms_id" );

ALTER TABLE "pohead" ADD CONSTRAINT "cst_pohead_whsinfo_warehous_id" FOREIGN KEY ( "pohead_warehous_id" ) REFERENCES "whsinfo" ( "warehous_id" );

ALTER TABLE "pohead" ADD CONSTRAINT "cst_pohead_vendaddrinfo_vendaddr_id" FOREIGN KEY ( "pohead_vendaddr_id" ) REFERENCES "vendaddrinfo" ( "vendaddr_id" );

ALTER TABLE "pohead" ADD CONSTRAINT "cst_pohead_curr_symbol_curr_id" FOREIGN KEY ( "pohead_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

-- Generate Sqlite application relations for table poitem for Postbooks_Entities
ALTER TABLE "poitem" ADD CONSTRAINT "cst_poitem_wo_wo_id" FOREIGN KEY ( "poitem_wohead_id" ) REFERENCES "wo" ( "wo_id" );

ALTER TABLE "poitem" ADD CONSTRAINT "cst_poitem_itemsite_itemsite_id" FOREIGN KEY ( "poitem_itemsite_id" ) REFERENCES "itemsite" ( "itemsite_id" );

ALTER TABLE "poitem" ADD CONSTRAINT "cst_poitem_expcat_expcat_id" FOREIGN KEY ( "poitem_expcat_id" ) REFERENCES "expcat" ( "expcat_id" );

ALTER TABLE "poitem" ADD CONSTRAINT "cst_poitem_itemsrc_itemsrc_id" FOREIGN KEY ( "poitem_itemsrc_id" ) REFERENCES "itemsrc" ( "itemsrc_id" );

ALTER TABLE "poitem" ADD CONSTRAINT "cst_poitem_prj_prj_id" FOREIGN KEY ( "poitem_prj_id" ) REFERENCES "prj" ( "prj_id" );

-- Generate Sqlite application relations for table porecv for Postbooks_Entities
-- Generate Sqlite application relations for table poreject for Postbooks_Entities
-- Generate Sqlite application relations for table potype for Postbooks_Entities
-- Generate Sqlite application relations for table pr for Postbooks_Entities
-- Generate Sqlite application relations for table prftcntr for Postbooks_Entities
-- Generate Sqlite application relations for table priv for Postbooks_Entities
-- Generate Sqlite application relations for table prj for Postbooks_Entities
-- Generate Sqlite application relations for table prjtask for Postbooks_Entities
-- Generate Sqlite application relations for table prjtaskuser for Postbooks_Entities
-- Generate Sqlite application relations for table prodcat for Postbooks_Entities
-- Generate Sqlite application relations for table prospect for Postbooks_Entities
ALTER TABLE "prospect" ADD CONSTRAINT "cst_prospect_cntct_cntct_id" FOREIGN KEY ( "prospect_cntct_id" ) REFERENCES "cntct" ( "cntct_id" );

ALTER TABLE "prospect" ADD CONSTRAINT "cst_prospect_taxauth_taxauth_id" FOREIGN KEY ( "prospect_taxauth_id" ) REFERENCES "taxauth" ( "taxauth_id" );

ALTER TABLE "prospect" ADD CONSTRAINT "cst_prospect_salesrep_salesrep_id" FOREIGN KEY ( "prospect_salesrep_id" ) REFERENCES "salesrep" ( "salesrep_id" );

ALTER TABLE "prospect" ADD CONSTRAINT "cst_prospect_whsinfo_warehous_id" FOREIGN KEY ( "prospect_warehous_id" ) REFERENCES "whsinfo" ( "warehous_id" );

-- Generate Sqlite application relations for table quhead for Postbooks_Entities
ALTER TABLE "quhead" ADD CONSTRAINT "cst_quhead_shiptoinfo_shipto_id" FOREIGN KEY ( "quhead_shipto_id" ) REFERENCES "shiptoinfo" ( "shipto_id" );

ALTER TABLE "quhead" ADD CONSTRAINT "cst_quhead_salesrep_salesrep_id" FOREIGN KEY ( "quhead_salesrep_id" ) REFERENCES "salesrep" ( "salesrep_id" );

ALTER TABLE "quhead" ADD CONSTRAINT "cst_quhead_terms_terms_id" FOREIGN KEY ( "quhead_terms_id" ) REFERENCES "terms" ( "terms_id" );

ALTER TABLE "quhead" ADD CONSTRAINT "cst_quhead_whsinfo_warehous_id" FOREIGN KEY ( "quhead_warehous_id" ) REFERENCES "whsinfo" ( "warehous_id" );

ALTER TABLE "quhead" ADD CONSTRAINT "cst_quhead_prj_prj_id" FOREIGN KEY ( "quhead_prj_id" ) REFERENCES "prj" ( "prj_id" );

ALTER TABLE "quhead" ADD CONSTRAINT "cst_quhead_accnt_accnt_id" FOREIGN KEY ( "quhead_misc_accnt_id" ) REFERENCES "accnt" ( "accnt_id" );

ALTER TABLE "quhead" ADD CONSTRAINT "cst_quhead_curr_symbol_curr_id" FOREIGN KEY ( "quhead_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

ALTER TABLE "quhead" ADD CONSTRAINT "cst_quhead_taxauth_taxauth_id" FOREIGN KEY ( "quhead_taxauth_id" ) REFERENCES "taxauth" ( "taxauth_id" );

-- Generate Sqlite application relations for table quitem for Postbooks_Entities
ALTER TABLE "quitem" ADD CONSTRAINT "cst_quitem_tax_tax_id" FOREIGN KEY ( "quitem_tax_id" ) REFERENCES "tax" ( "tax_id" );

ALTER TABLE "quitem" ADD CONSTRAINT "cst_quitem_uom_uom_id" FOREIGN KEY ( "quitem_qty_uom_id" ) REFERENCES "uom" ( "uom_id" );

ALTER TABLE "quitem" ADD CONSTRAINT "cst_quitem_uom_uom_id" FOREIGN KEY ( "quitem_price_uom_id" ) REFERENCES "uom" ( "uom_id" );

-- Generate Sqlite application relations for table rcalitem for Postbooks_Entities
-- Generate Sqlite application relations for table recv for Postbooks_Entities
ALTER TABLE "recv" ADD CONSTRAINT "cst_recv_itemsite_itemsite_id" FOREIGN KEY ( "recv_itemsite_id" ) REFERENCES "itemsite" ( "itemsite_id" );

ALTER TABLE "recv" ADD CONSTRAINT "cst_recv_vendinfo_vend_id" FOREIGN KEY ( "recv_vend_id" ) REFERENCES "vendinfo" ( "vend_id" );

ALTER TABLE "recv" ADD CONSTRAINT "cst_recv_curr_symbol_curr_id" FOREIGN KEY ( "recv_purchcost_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

ALTER TABLE "recv" ADD CONSTRAINT "cst_recv_curr_symbol_curr_id" FOREIGN KEY ( "recv_recvcost_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

ALTER TABLE "recv" ADD CONSTRAINT "cst_recv_curr_symbol_curr_id" FOREIGN KEY ( "recv_freight_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

ALTER TABLE "recv" ADD CONSTRAINT "cst_recv_vohead_vohead_id" FOREIGN KEY ( "recv_vohead_id" ) REFERENCES "vohead" ( "vohead_id" );

ALTER TABLE "recv" ADD CONSTRAINT "cst_recv_voitem_voitem_id" FOREIGN KEY ( "recv_voitem_id" ) REFERENCES "voitem" ( "voitem_id" );

ALTER TABLE "recv" ADD CONSTRAINT "cst_recv_recv_recv_id" FOREIGN KEY ( "recv_splitfrom_id" ) REFERENCES "recv" ( "recv_id" );

-- Generate Sqlite application relations for table remitto for Postbooks_Entities
-- Generate Sqlite application relations for table report for Postbooks_Entities
-- Generate Sqlite application relations for table rjctcode for Postbooks_Entities
-- Generate Sqlite application relations for table rsncode for Postbooks_Entities
-- Generate Sqlite application relations for table sale for Postbooks_Entities
-- Generate Sqlite application relations for table salesaccnt for Postbooks_Entities
ALTER TABLE "salesaccnt" ADD CONSTRAINT "cst_salesaccnt_accnt_accnt_id" FOREIGN KEY ( "salesaccnt_returns_accnt_id" ) REFERENCES "accnt" ( "accnt_id" );

ALTER TABLE "salesaccnt" ADD CONSTRAINT "cst_salesaccnt_accnt_accnt_id" FOREIGN KEY ( "salesaccnt_cor_accnt_id" ) REFERENCES "accnt" ( "accnt_id" );

ALTER TABLE "salesaccnt" ADD CONSTRAINT "cst_salesaccnt_accnt_accnt_id" FOREIGN KEY ( "salesaccnt_cow_accnt_id" ) REFERENCES "accnt" ( "accnt_id" );

-- Generate Sqlite application relations for table salescat for Postbooks_Entities
-- Generate Sqlite application relations for table saleshistory for Postbooks_Entities
-- Generate Sqlite application relations for table salesquoteitem for Postbooks_Entities
-- Generate Sqlite application relations for table salesrep for Postbooks_Entities
ALTER TABLE "salesrep" ADD CONSTRAINT "cst_salesrep_emp_emp_id" FOREIGN KEY ( "salesrep_emp_id" ) REFERENCES "emp" ( "emp_id" );

-- Generate Sqlite application relations for table script for Postbooks_Entities
-- Generate Sqlite application relations for table sequence for Postbooks_Entities
-- Generate Sqlite application relations for table shift for Postbooks_Entities
-- Generate Sqlite application relations for table shipchrg for Postbooks_Entities
-- Generate Sqlite application relations for table shipdata for Postbooks_Entities
ALTER TABLE "shipdata" ADD CONSTRAINT "cst_shipdata_curr_symbol_curr_id" FOREIGN KEY ( "shipdata_base_freight_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

ALTER TABLE "shipdata" ADD CONSTRAINT "cst_shipdata_curr_symbol_curr_id" FOREIGN KEY ( "shipdata_total_freight_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

-- Generate Sqlite application relations for table shipdatasum for Postbooks_Entities
-- Generate Sqlite application relations for table shipform for Postbooks_Entities
-- Generate Sqlite application relations for table shiphead for Postbooks_Entities
ALTER TABLE "shiphead" ADD CONSTRAINT "cst_shiphead_curr_symbol_curr_id" FOREIGN KEY ( "shiphead_freight_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

ALTER TABLE "shiphead" ADD CONSTRAINT "cst_shiphead_shipchrg_shipchrg_id" FOREIGN KEY ( "shiphead_shipchrg_id" ) REFERENCES "shipchrg" ( "shipchrg_id" );

ALTER TABLE "shiphead" ADD CONSTRAINT "cst_shiphead_shipform_shipform_id" FOREIGN KEY ( "shiphead_shipform_id" ) REFERENCES "shipform" ( "shipform_id" );

-- Generate Sqlite application relations for table shipitem for Postbooks_Entities
ALTER TABLE "shipitem" ADD CONSTRAINT "cst_shipitem_shiphead_shiphead_id" FOREIGN KEY ( "shipitem_shiphead_id" ) REFERENCES "shiphead" ( "shiphead_id" );

ALTER TABLE "shipitem" ADD CONSTRAINT "cst_shipitem_invcitem_invcitem_id" FOREIGN KEY ( "shipitem_invcitem_id" ) REFERENCES "invcitem" ( "invcitem_id" );

ALTER TABLE "shipitem" ADD CONSTRAINT "cst_shipitem_invhist_invhist_id" FOREIGN KEY ( "shipitem_invhist_id" ) REFERENCES "invhist" ( "invhist_id" );

-- Generate Sqlite application relations for table shipto for Postbooks_Entities
-- Generate Sqlite application relations for table shiptoinfo for Postbooks_Entities
ALTER TABLE "shiptoinfo" ADD CONSTRAINT "cst_shiptoinfo_custinfo_cust_id" FOREIGN KEY ( "shipto_cust_id" ) REFERENCES "custinfo" ( "cust_id" );

ALTER TABLE "shiptoinfo" ADD CONSTRAINT "cst_shiptoinfo_salesrep_salesrep_id" FOREIGN KEY ( "shipto_salesrep_id" ) REFERENCES "salesrep" ( "salesrep_id" );

ALTER TABLE "shiptoinfo" ADD CONSTRAINT "cst_shiptoinfo_shipzone_shipzone_id" FOREIGN KEY ( "shipto_shipzone_id" ) REFERENCES "shipzone" ( "shipzone_id" );

ALTER TABLE "shiptoinfo" ADD CONSTRAINT "cst_shiptoinfo_shipform_shipform_id" FOREIGN KEY ( "shipto_shipform_id" ) REFERENCES "shipform" ( "shipform_id" );

ALTER TABLE "shiptoinfo" ADD CONSTRAINT "cst_shiptoinfo_addr_addr_id" FOREIGN KEY ( "shipto_addr_id" ) REFERENCES "addr" ( "addr_id" );

ALTER TABLE "shiptoinfo" ADD CONSTRAINT "cst_shiptoinfo_taxauth_taxauth_id" FOREIGN KEY ( "shipto_taxauth_id" ) REFERENCES "taxauth" ( "taxauth_id" );

-- Generate Sqlite application relations for table shipvia for Postbooks_Entities
-- Generate Sqlite application relations for table shipzone for Postbooks_Entities
-- Generate Sqlite application relations for table sitetype for Postbooks_Entities
-- Generate Sqlite application relations for table soheadlock for Postbooks_Entities
ALTER TABLE "soheadlock" ADD CONSTRAINT "cst_soheadlock_cohead_cohead_id" FOREIGN KEY ( "soheadlock_sohead_id" ) REFERENCES "cohead" ( "cohead_id" );

-- Generate Sqlite application relations for table sopack for Postbooks_Entities
-- Generate Sqlite application relations for table stdjrnl for Postbooks_Entities
-- Generate Sqlite application relations for table stdjrnlgrp for Postbooks_Entities
-- Generate Sqlite application relations for table stdjrnlgrpitem for Postbooks_Entities
-- Generate Sqlite application relations for table stdjrnlitem for Postbooks_Entities
-- Generate Sqlite application relations for table stdopn for Postbooks_Entities
-- Generate Sqlite application relations for table subaccnt for Postbooks_Entities
-- Generate Sqlite application relations for table subaccnttype for Postbooks_Entities
-- Generate Sqlite application relations for table tax for Postbooks_Entities
-- Generate Sqlite application relations for table taxauth for Postbooks_Entities
ALTER TABLE "taxauth" ADD CONSTRAINT "cst_taxauth_addr_addr_id" FOREIGN KEY ( "taxauth_addr_id" ) REFERENCES "addr" ( "addr_id" );

ALTER TABLE "taxauth" ADD CONSTRAINT "cst_taxauth_curr_symbol_curr_id" FOREIGN KEY ( "taxauth_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

ALTER TABLE "taxauth" ADD CONSTRAINT "cst_taxauth_accnt_accnt_id" FOREIGN KEY ( "taxauth_accnt_id" ) REFERENCES "accnt" ( "accnt_id" );

-- Generate Sqlite application relations for table taxreg for Postbooks_Entities
ALTER TABLE "taxreg" ADD CONSTRAINT "cst_taxreg_taxauth_taxauth_id" FOREIGN KEY ( "taxreg_taxauth_id" ) REFERENCES "taxauth" ( "taxauth_id" );

-- Generate Sqlite application relations for table taxsel for Postbooks_Entities
ALTER TABLE "taxsel" ADD CONSTRAINT "cst_taxsel_taxauth_taxauth_id" FOREIGN KEY ( "taxsel_taxauth_id" ) REFERENCES "taxauth" ( "taxauth_id" );

ALTER TABLE "taxsel" ADD CONSTRAINT "cst_taxsel_taxtype_taxtype_id" FOREIGN KEY ( "taxsel_taxtype_id" ) REFERENCES "taxtype" ( "taxtype_id" );

ALTER TABLE "taxsel" ADD CONSTRAINT "cst_taxsel_tax_tax_id" FOREIGN KEY ( "taxsel_tax_id" ) REFERENCES "tax" ( "tax_id" );

-- Generate Sqlite application relations for table taxtype for Postbooks_Entities
-- Generate Sqlite application relations for table terms for Postbooks_Entities
-- Generate Sqlite application relations for table todoassoc for Postbooks_Entities
ALTER TABLE "todoassoc" ADD CONSTRAINT "cst_todoassoc_todoitem_todoitem_id" FOREIGN KEY ( "todoassoc_todoitem_id" ) REFERENCES "todoitem" ( "todoitem_id" );

-- Generate Sqlite application relations for table todoitem for Postbooks_Entities
ALTER TABLE "todoitem" ADD CONSTRAINT "cst_todoitem_usr_usr_id" FOREIGN KEY ( "todoitem_usr_id" ) REFERENCES "usr" ( "usr_id" );

ALTER TABLE "todoitem" ADD CONSTRAINT "cst_todoitem_incdt_incdt_id" FOREIGN KEY ( "todoitem_incdt_id" ) REFERENCES "incdt" ( "incdt_id" );

ALTER TABLE "todoitem" ADD CONSTRAINT "cst_todoitem_crmacct_crmacct_id" FOREIGN KEY ( "todoitem_crmacct_id" ) REFERENCES "crmacct" ( "crmacct_id" );

ALTER TABLE "todoitem" ADD CONSTRAINT "cst_todoitem_ophead_ophead_id" FOREIGN KEY ( "todoitem_ophead_id" ) REFERENCES "ophead" ( "ophead_id" );

-- Generate Sqlite application relations for table trialbal for Postbooks_Entities
-- Generate Sqlite application relations for table uiform for Postbooks_Entities
-- Generate Sqlite application relations for table uom for Postbooks_Entities
-- Generate Sqlite application relations for table uomconv for Postbooks_Entities
ALTER TABLE "uomconv" ADD CONSTRAINT "cst_uomconv_uom_uom_id" FOREIGN KEY ( "uomconv_from_uom_id" ) REFERENCES "uom" ( "uom_id" );

ALTER TABLE "uomconv" ADD CONSTRAINT "cst_uomconv_uom_uom_id" FOREIGN KEY ( "uomconv_to_uom_id" ) REFERENCES "uom" ( "uom_id" );

-- Generate Sqlite application relations for table uomtype for Postbooks_Entities
-- Generate Sqlite application relations for table url for Postbooks_Entities
-- Generate Sqlite application relations for table usr for Postbooks_Entities
-- Generate Sqlite application relations for table usrgrp for Postbooks_Entities
ALTER TABLE "usrgrp" ADD CONSTRAINT "cst_usrgrp_grp_grp_id" FOREIGN KEY ( "usrgrp_grp_id" ) REFERENCES "grp" ( "grp_id" );

-- Generate Sqlite application relations for table usrpref for Postbooks_Entities
-- Generate Sqlite application relations for table usrpriv for Postbooks_Entities
-- Generate Sqlite application relations for table vend for Postbooks_Entities
-- Generate Sqlite application relations for table vendaddr for Postbooks_Entities
-- Generate Sqlite application relations for table vendaddrinfo for Postbooks_Entities
ALTER TABLE "vendaddrinfo" ADD CONSTRAINT "cst_vendaddrinfo_addr_addr_id" FOREIGN KEY ( "vendaddr_addr_id" ) REFERENCES "addr" ( "addr_id" );

ALTER TABLE "vendaddrinfo" ADD CONSTRAINT "cst_vendaddrinfo_taxauth_taxauth_id" FOREIGN KEY ( "vendaddr_taxauth_id" ) REFERENCES "taxauth" ( "taxauth_id" );

-- Generate Sqlite application relations for table vendinfo for Postbooks_Entities
ALTER TABLE "vendinfo" ADD CONSTRAINT "cst_vendinfo_vendtype_vendtype_id" FOREIGN KEY ( "vend_vendtype_id" ) REFERENCES "vendtype" ( "vendtype_id" );

ALTER TABLE "vendinfo" ADD CONSTRAINT "cst_vendinfo_curr_symbol_curr_id" FOREIGN KEY ( "vend_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

ALTER TABLE "vendinfo" ADD CONSTRAINT "cst_vendinfo_addr_addr_id" FOREIGN KEY ( "vend_addr_id" ) REFERENCES "addr" ( "addr_id" );

ALTER TABLE "vendinfo" ADD CONSTRAINT "cst_vendinfo_taxauth_taxauth_id" FOREIGN KEY ( "vend_taxauth_id" ) REFERENCES "taxauth" ( "taxauth_id" );

-- Generate Sqlite application relations for table vendtype for Postbooks_Entities
-- Generate Sqlite application relations for table vodist for Postbooks_Entities
-- Generate Sqlite application relations for table vohead for Postbooks_Entities
ALTER TABLE "vohead" ADD CONSTRAINT "cst_vohead_curr_symbol_curr_id" FOREIGN KEY ( "vohead_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

ALTER TABLE "vohead" ADD CONSTRAINT "cst_vohead_taxauth_taxauth_id" FOREIGN KEY ( "vohead_taxauth_id" ) REFERENCES "taxauth" ( "taxauth_id" );

ALTER TABLE "vohead" ADD CONSTRAINT "cst_vohead_curr_symbol_curr_id" FOREIGN KEY ( "vohead_tax_curr_id" ) REFERENCES "curr_symbol" ( "curr_id" );

ALTER TABLE "vohead" ADD CONSTRAINT "cst_vohead_tax_tax_id" FOREIGN KEY ( "vohead_adjtax_id" ) REFERENCES "tax" ( "tax_id" );

ALTER TABLE "vohead" ADD CONSTRAINT "cst_vohead_taxtype_taxtype_id" FOREIGN KEY ( "vohead_adjtaxtype_id" ) REFERENCES "taxtype" ( "taxtype_id" );

ALTER TABLE "vohead" ADD CONSTRAINT "cst_vohead_tax_tax_id" FOREIGN KEY ( "vohead_freighttax_id" ) REFERENCES "tax" ( "tax_id" );

ALTER TABLE "vohead" ADD CONSTRAINT "cst_vohead_taxtype_taxtype_id" FOREIGN KEY ( "vohead_freighttaxtype_id" ) REFERENCES "taxtype" ( "taxtype_id" );

-- Generate Sqlite application relations for table voitem for Postbooks_Entities
ALTER TABLE "voitem" ADD CONSTRAINT "cst_voitem_taxtype_taxtype_id" FOREIGN KEY ( "voitem_taxtype_id" ) REFERENCES "taxtype" ( "taxtype_id" );

-- Generate Sqlite application relations for table voucheringeditlist for Postbooks_Entities
-- Generate Sqlite application relations for table warehous for Postbooks_Entities
-- Generate Sqlite application relations for table whsezone for Postbooks_Entities
-- Generate Sqlite application relations for table whsinfo for Postbooks_Entities
ALTER TABLE "whsinfo" ADD CONSTRAINT "cst_whsinfo_accnt_accnt_id" FOREIGN KEY ( "warehous_default_accnt_id" ) REFERENCES "accnt" ( "accnt_id" );

ALTER TABLE "whsinfo" ADD CONSTRAINT "cst_whsinfo_cntct_cntct_id" FOREIGN KEY ( "warehous_cntct_id" ) REFERENCES "cntct" ( "cntct_id" );

ALTER TABLE "whsinfo" ADD CONSTRAINT "cst_whsinfo_addr_addr_id" FOREIGN KEY ( "warehous_addr_id" ) REFERENCES "addr" ( "addr_id" );

ALTER TABLE "whsinfo" ADD CONSTRAINT "cst_whsinfo_taxauth_taxauth_id" FOREIGN KEY ( "warehous_taxauth_id" ) REFERENCES "taxauth" ( "taxauth_id" );

ALTER TABLE "whsinfo" ADD CONSTRAINT "cst_whsinfo_shipform_shipform_id" FOREIGN KEY ( "warehous_shipform_id" ) REFERENCES "shipform" ( "shipform_id" );

ALTER TABLE "whsinfo" ADD CONSTRAINT "cst_whsinfo_shipvia_shipvia_id" FOREIGN KEY ( "warehous_shipvia_id" ) REFERENCES "shipvia" ( "shipvia_id" );

ALTER TABLE "whsinfo" ADD CONSTRAINT "cst_whsinfo_costcat_costcat_id" FOREIGN KEY ( "warehous_costcat_id" ) REFERENCES "costcat" ( "costcat_id" );

ALTER TABLE "whsinfo" ADD CONSTRAINT "cst_whsinfo_sitetype_sitetype_id" FOREIGN KEY ( "warehous_sitetype_id" ) REFERENCES "sitetype" ( "sitetype_id" );

-- Generate Sqlite application relations for table wo for Postbooks_Entities
-- Generate Sqlite application relations for table womatl for Postbooks_Entities
ALTER TABLE "womatl" ADD CONSTRAINT "cst_womatl_uom_uom_id" FOREIGN KEY ( "womatl_uom_id" ) REFERENCES "uom" ( "uom_id" );

-- Generate Sqlite application relations for table womatlpost for Postbooks_Entities
ALTER TABLE "womatlpost" ADD CONSTRAINT "cst_womatlpost_womatl_womatl_id" FOREIGN KEY ( "womatlpost_womatl_id" ) REFERENCES "womatl" ( "womatl_id" );

ALTER TABLE "womatlpost" ADD CONSTRAINT "cst_womatlpost_invhist_invhist_id" FOREIGN KEY ( "womatlpost_invhist_id" ) REFERENCES "invhist" ( "invhist_id" );

-- Generate Sqlite application relations for table womatlvar for Postbooks_Entities
-- Generate Sqlite application relations for table woopervar for Postbooks_Entities
-- Generate Sqlite application relations for table workglhead for Postbooks_Entities
-- Generate Sqlite application relations for table workglitem for Postbooks_Entities
-- Generate Sqlite application relations for table workgltotal for Postbooks_Entities
-- Generate Sqlite application relations for table workgltotaleq for Postbooks_Entities
-- Generate Sqlite application relations for table xsltmap for Postbooks_Entities
-- Generate Sqlite application relations for table yearperiod for Postbooks_Entities
//this file is part of nppColdFusion
//Copyright (C)2011 Ben Bluemel ( ben1982@gmail.com )
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "CFFunctions.h"
cfparameter::cfparameter()
{
	name = "notaparameter";
};
cfparameter::~cfparameter() {};
cffunction::cffunction()
{
	name = "notafunction";
	for ( int a = 0; a <=10; a++ ) {
		parameters[a] = cfparameter();
	}
};
cffunction::~cffunction() {};
cfpnumber_numeric ::cfpnumber_numeric ()
{
	name = "number";
	type = T_NUMERIC;

};
cfpnumber_numeric::~cfpnumber_numeric() {};




cfpwebservice_string ::cfpwebservice_string ()
{
	name = "webservice";
	type = T_STRING;

};
cfpwebservice_string::~cfpwebservice_string() {};




cfpnamespace_string ::cfpnamespace_string ()
{
	name = "namespace";
	type = T_STRING;

};
cfpnamespace_string::~cfpnamespace_string() {};




cfpname_string ::cfpname_string ()
{
	name = "name";
	type = T_STRING;

};
cfpname_string::~cfpname_string() {};




cfpvalue_string ::cfpvalue_string ()
{
	name = "value";
	type = T_STRING;

};
cfpvalue_string::~cfpvalue_string() {};




cfpmustunderstand_boolean ::cfpmustunderstand_boolean ()
{
	name = "mustunderstand";
	type = T_BOOLEAN;

};
cfpmustunderstand_boolean::~cfpmustunderstand_boolean() {};




cfpurl_string ::cfpurl_string ()
{
	name = "url";
	type = T_STRING;

};
cfpurl_string::~cfpurl_string() {};




cfpfunctionname_string ::cfpfunctionname_string ()
{
	name = "functionname";
	type = T_STRING;

};
cfpfunctionname_string::~cfpfunctionname_string() {};




cfparray_array ::cfparray_array ()
{
	name = "array";
	type = T_ARRAY;

};
cfparray_array::~cfparray_array() {};




cfpvalue_any ::cfpvalue_any ()
{
	name = "value";
	type = T_ANY;

};
cfpvalue_any::~cfpvalue_any() {};




cfpobject_any ::cfpobject_any ()
{
	name = "object";
	type = T_ANY;

};
cfpobject_any::~cfpobject_any() {};




cfpposition_numeric ::cfpposition_numeric ()
{
	name = "position";
	type = T_NUMERIC;

};
cfpposition_numeric::~cfpposition_numeric() {};




cfpobject_variablename ::cfpobject_variablename ()
{
	name = "object";
	type = T_VARIABLENAME;

};
cfpobject_variablename::~cfpobject_variablename() {};




cfparray_string ::cfparray_string ()
{
	name = "array";
	type = T_STRING;

};
cfparray_string::~cfparray_string() {};




cfpelementindex_numeric ::cfpelementindex_numeric ()
{
	name = "elementindex";
	type = T_NUMERIC;

};
cfpelementindex_numeric::~cfpelementindex_numeric() {};




cfpdimension_numeric ::cfpdimension_numeric ()
{
	name = "dimension";
	type = T_NUMERIC;

};
cfpdimension_numeric::~cfpdimension_numeric() {};




cfpvalue_object ::cfpvalue_object ()
{
	name = "value";
	type = T_OBJECT;

};
cfpvalue_object::~cfpvalue_object() {};




cfpsize_numeric ::cfpsize_numeric ()
{
	name = "size";
	type = T_NUMERIC;

};
cfpsize_numeric::~cfpsize_numeric() {};




cfpstart_pos_numeric ::cfpstart_pos_numeric ()
{
	name = "start_pos";
	type = T_NUMERIC;

};
cfpstart_pos_numeric::~cfpstart_pos_numeric() {};




cfpend_pos_numeric ::cfpend_pos_numeric ()
{
	name = "end_pos";
	type = T_NUMERIC;

};
cfpend_pos_numeric::~cfpend_pos_numeric() {};




cfpsort_type_string ::cfpsort_type_string ()
{
	name = "sort_type";
	type = T_STRING;

};
cfpsort_type_string::~cfpsort_type_string() {};




cfpsort_order_string ::cfpsort_order_string ()
{
	name = "sort_order";
	type = T_STRING;

};
cfpsort_order_string::~cfpsort_order_string() {};




cfpposition1_numeric ::cfpposition1_numeric ()
{
	name = "position1";
	type = T_NUMERIC;

};
cfpposition1_numeric::~cfpposition1_numeric() {};




cfpposition2_numeric ::cfpposition2_numeric ()
{
	name = "position2";
	type = T_NUMERIC;

};
cfpposition2_numeric::~cfpposition2_numeric() {};




cfpdelimiter_string ::cfpdelimiter_string ()
{
	name = "delimiter";
	type = T_STRING;

};
cfpdelimiter_string::~cfpdelimiter_string() {};




cfpstring_string ::cfpstring_string ()
{
	name = "string";
	type = T_STRING;

};
cfpstring_string::~cfpstring_string() {};




cfpbinaryencoding_string ::cfpbinaryencoding_string ()
{
	name = "binaryencoding";
	type = T_STRING;

};
cfpbinaryencoding_string::~cfpbinaryencoding_string() {};




cfpbinarydata_binary ::cfpbinarydata_binary ()
{
	name = "binarydata";
	type = T_BINARY;

};
cfpbinarydata_binary::~cfpbinarydata_binary() {};




cfpencoding_string ::cfpencoding_string ()
{
	name = "encoding";
	type = T_STRING;

};
cfpencoding_string::~cfpencoding_string() {};




cfpnumber1_numeric ::cfpnumber1_numeric ()
{
	name = "number1";
	type = T_NUMERIC;

};
cfpnumber1_numeric::~cfpnumber1_numeric() {};




cfpnumber2_numeric ::cfpnumber2_numeric ()
{
	name = "number2";
	type = T_NUMERIC;

};
cfpnumber2_numeric::~cfpnumber2_numeric() {};




cfpstart_numeric ::cfpstart_numeric ()
{
	name = "start";
	type = T_NUMERIC;

};
cfpstart_numeric::~cfpstart_numeric() {};




cfplength_numeric ::cfplength_numeric ()
{
	name = "length";
	type = T_NUMERIC;

};
cfplength_numeric::~cfplength_numeric() {};




cfpmask_numeric ::cfpmask_numeric ()
{
	name = "mask";
	type = T_NUMERIC;

};
cfpmask_numeric::~cfpmask_numeric() {};




cfpcount_numeric ::cfpcount_numeric ()
{
	name = "count";
	type = T_NUMERIC;

};
cfpcount_numeric::~cfpcount_numeric() {};




cfpid_string ::cfpid_string ()
{
	name = "id";
	type = T_STRING;

};
cfpid_string::~cfpid_string() {};




cfptype_string ::cfptype_string ()
{
	name = "type";
	type = T_STRING;

};
cfptype_string::~cfptype_string() {};




cfptimespan_datetime ::cfptimespan_datetime ()
{
	name = "timespan";
	type = T_DATETIME;

};
cfptimespan_datetime::~cfptimespan_datetime() {};




cfpideltime_datetime ::cfpideltime_datetime ()
{
	name = "ideltime";
	type = T_DATETIME;

};
cfpideltime_datetime::~cfpideltime_datetime() {};




cfpids_string ::cfpids_string ()
{
	name = "ids";
	type = T_STRING;

};
cfpids_string::~cfpids_string() {};




cfpthrowonerror_boolean ::cfpthrowonerror_boolean ()
{
	name = "throwonerror";
	type = T_BOOLEAN;

};
cfpthrowonerror_boolean::~cfpthrowonerror_boolean() {};




cfppropstruct_struct ::cfppropstruct_struct ()
{
	name = "propstruct";
	type = T_STRUCT;

};
cfppropstruct_struct::~cfppropstruct_struct() {};




cfpbinaryobject_binary ::cfpbinaryobject_binary ()
{
	name = "binaryobject";
	type = T_BINARY;

};
cfpbinaryobject_binary::~cfpbinaryobject_binary() {};




cfpstring1_string ::cfpstring1_string ()
{
	name = "string1";
	type = T_STRING;

};
cfpstring1_string::~cfpstring1_string() {};




cfpstring2_string ::cfpstring2_string ()
{
	name = "string2";
	type = T_STRING;

};
cfpstring2_string::~cfpstring2_string() {};




cfpyear_numeric ::cfpyear_numeric ()
{
	name = "year";
	type = T_NUMERIC;

};
cfpyear_numeric::~cfpyear_numeric() {};




cfpmonth_numeric ::cfpmonth_numeric ()
{
	name = "month";
	type = T_NUMERIC;

};
cfpmonth_numeric::~cfpmonth_numeric() {};




cfpday_numeric ::cfpday_numeric ()
{
	name = "day";
	type = T_NUMERIC;

};
cfpday_numeric::~cfpday_numeric() {};




cfphour_numeric ::cfphour_numeric ()
{
	name = "hour";
	type = T_NUMERIC;

};
cfphour_numeric::~cfphour_numeric() {};




cfpminute_numeric ::cfpminute_numeric ()
{
	name = "minute";
	type = T_NUMERIC;

};
cfpminute_numeric::~cfpminute_numeric() {};




cfpsecond_numeric ::cfpsecond_numeric ()
{
	name = "second";
	type = T_NUMERIC;

};
cfpsecond_numeric::~cfpsecond_numeric() {};




cfpcontext_string ::cfpcontext_string ()
{
	name = "context";
	type = T_STRING;

};
cfpcontext_string::~cfpcontext_string() {};




cfpclass_string ::cfpclass_string ()
{
	name = "class";
	type = T_STRING;

};
cfpclass_string::~cfpclass_string() {};




cfplocale_string ::cfplocale_string ()
{
	name = "locale";
	type = T_STRING;

};
cfplocale_string::~cfplocale_string() {};




cfpservername_string ::cfpservername_string ()
{
	name = "servername";
	type = T_STRING;

};
cfpservername_string::~cfpservername_string() {};




cfpcomponent_name_string ::cfpcomponent_name_string ()
{
	name = "component_name";
	type = T_STRING;

};
cfpcomponent_name_string::~cfpcomponent_name_string() {};




cfpurltowsdl_string ::cfpurltowsdl_string ()
{
	name = "urltowsdl";
	type = T_STRING;

};
cfpurltowsdl_string::~cfpurltowsdl_string() {};




cfpportname_string ::cfpportname_string ()
{
	name = "portname";
	type = T_STRING;

};
cfpportname_string::~cfpportname_string() {};




cfpdate_datetime ::cfpdate_datetime ()
{
	name = "date";
	type = T_DATETIME;

};
cfpdate_datetime::~cfpdate_datetime() {};




cfpdays_numeric ::cfpdays_numeric ()
{
	name = "days";
	type = T_NUMERIC;

};
cfpdays_numeric::~cfpdays_numeric() {};




cfphours_numeric ::cfphours_numeric ()
{
	name = "hours";
	type = T_NUMERIC;

};
cfphours_numeric::~cfphours_numeric() {};




cfpminutes_numeric ::cfpminutes_numeric ()
{
	name = "minutes";
	type = T_NUMERIC;

};
cfpminutes_numeric::~cfpminutes_numeric() {};




cfpseconds_numeric ::cfpseconds_numeric ()
{
	name = "seconds";
	type = T_NUMERIC;

};
cfpseconds_numeric::~cfpseconds_numeric() {};




cfpdatepart_string ::cfpdatepart_string ()
{
	name = "datepart";
	type = T_STRING;

};
cfpdatepart_string::~cfpdatepart_string() {};




cfpdate1_datetime ::cfpdate1_datetime ()
{
	name = "date1";
	type = T_DATETIME;

};
cfpdate1_datetime::~cfpdate1_datetime() {};




cfpdate2_datetime ::cfpdate2_datetime ()
{
	name = "date2";
	type = T_DATETIME;

};
cfpdate2_datetime::~cfpdate2_datetime() {};




cfpmask_string ::cfpmask_string ()
{
	name = "mask";
	type = T_STRING;

};
cfpmask_string::~cfpmask_string() {};




cfpday_of_week_numeric ::cfpday_of_week_numeric ()
{
	name = "day_of_week";
	type = T_NUMERIC;

};
cfpday_of_week_numeric::~cfpday_of_week_numeric() {};




cfpencrypted_string_string ::cfpencrypted_string_string ()
{
	name = "encrypted_string";
	type = T_STRING;

};
cfpencrypted_string_string::~cfpencrypted_string_string() {};




cfpkey_string ::cfpkey_string ()
{
	name = "key";
	type = T_STRING;

};
cfpkey_string::~cfpkey_string() {};




cfpalgorithm_string ::cfpalgorithm_string ()
{
	name = "algorithm";
	type = T_STRING;

};
cfpalgorithm_string::~cfpalgorithm_string() {};




cfpivorsalt_binary ::cfpivorsalt_binary ()
{
	name = "ivorsalt";
	type = T_BINARY;

};
cfpivorsalt_binary::~cfpivorsalt_binary() {};




cfpiterations_numeric ::cfpiterations_numeric ()
{
	name = "iterations";
	type = T_NUMERIC;

};
cfpiterations_numeric::~cfpiterations_numeric() {};




cfpbytes_string ::cfpbytes_string ()
{
	name = "bytes";
	type = T_STRING;

};
cfpbytes_string::~cfpbytes_string() {};




cfpjsonvar_string ::cfpjsonvar_string ()
{
	name = "jsonvar";
	type = T_STRING;

};
cfpjsonvar_string::~cfpjsonvar_string() {};




cfpstrictmapping_boolean ::cfpstrictmapping_boolean ()
{
	name = "strictmapping";
	type = T_BOOLEAN;

};
cfpstrictmapping_boolean::~cfpstrictmapping_boolean() {};




cfppath_string ::cfppath_string ()
{
	name = "path";
	type = T_STRING;

};
cfppath_string::~cfppath_string() {};




cfprecurse_boolean ::cfprecurse_boolean ()
{
	name = "recurse";
	type = T_BOOLEAN;

};
cfprecurse_boolean::~cfprecurse_boolean() {};




cfpabsolute_path_string ::cfpabsolute_path_string ()
{
	name = "absolute_path";
	type = T_STRING;

};
cfpabsolute_path_string::~cfpabsolute_path_string() {};




cfpreturntype_string ::cfpreturntype_string ()
{
	name = "returntype";
	type = T_STRING;

};
cfpreturntype_string::~cfpreturntype_string() {};




cfpfilter_string ::cfpfilter_string ()
{
	name = "filter";
	type = T_STRING;

};
cfpfilter_string::~cfpfilter_string() {};




cfpsort_string ::cfpsort_string ()
{
	name = "sort";
	type = T_STRING;

};
cfpsort_string::~cfpsort_string() {};




cfpnewpath_string ::cfpnewpath_string ()
{
	name = "newpath";
	type = T_STRING;

};
cfpnewpath_string::~cfpnewpath_string() {};




cfpvariable_name_variablename ::cfpvariable_name_variablename ()
{
	name = "variable_name";
	type = T_VARIABLENAME;

};
cfpvariable_name_variablename::~cfpvariable_name_variablename() {};




cfpvariable_object ::cfpvariable_object ()
{
	name = "variable";
	type = T_OBJECT;

};
cfpvariable_object::~cfpvariable_object() {};




cfpentity_variablename ::cfpentity_variablename ()
{
	name = "entity";
	type = T_VARIABLENAME;

};
cfpentity_variablename::~cfpentity_variablename() {};




cfpentityname_string ::cfpentityname_string ()
{
	name = "entityname";
	type = T_STRING;

};
cfpentityname_string::~cfpentityname_string() {};




cfpfiltercriteria_string ::cfpfiltercriteria_string ()
{
	name = "filtercriteria";
	type = T_STRING;

};
cfpfiltercriteria_string::~cfpfiltercriteria_string() {};




cfpunique_string ::cfpunique_string ()
{
	name = "unique";
	type = T_STRING;

};
cfpunique_string::~cfpunique_string() {};




cfpsortorder_string ::cfpsortorder_string ()
{
	name = "sortorder";
	type = T_STRING;

};
cfpsortorder_string::~cfpsortorder_string() {};




cfpoptions_string ::cfpoptions_string ()
{
	name = "options";
	type = T_STRING;

};
cfpoptions_string::~cfpoptions_string() {};




cfpsampleentity_string ::cfpsampleentity_string ()
{
	name = "sampleentity";
	type = T_STRING;

};
cfpsampleentity_string::~cfpsampleentity_string() {};




cfpunique_boolean ::cfpunique_boolean ()
{
	name = "unique";
	type = T_BOOLEAN;

};
cfpunique_boolean::~cfpunique_boolean() {};




cfpid_object ::cfpid_object ()
{
	name = "id";
	type = T_OBJECT;

};
cfpid_object::~cfpid_object() {};




cfpforceinsert_boolean ::cfpforceinsert_boolean ()
{
	name = "forceinsert";
	type = T_BOOLEAN;

};
cfpforceinsert_boolean::~cfpforceinsert_boolean() {};




cfporm_object_variablename ::cfporm_object_variablename ()
{
	name = "orm_object";
	type = T_VARIABLENAME;

};
cfporm_object_variablename::~cfporm_object_variablename() {};




cfpentity_name_string ::cfpentity_name_string ()
{
	name = "entity_name";
	type = T_STRING;

};
cfpentity_name_string::~cfpentity_name_string() {};




cfpexpression1_string ::cfpexpression1_string ()
{
	name = "expression1";
	type = T_STRING;

};
cfpexpression1_string::~cfpexpression1_string() {};




cfpexpression2_string ::cfpexpression2_string ()
{
	name = "expression2";
	type = T_STRING;

};
cfpexpression2_string::~cfpexpression2_string() {};




cfpexpressionn_string ::cfpexpressionn_string ()
{
	name = "expressionn";
	type = T_STRING;

};
cfpexpressionn_string::~cfpexpressionn_string() {};




cfprelative_path_string ::cfprelative_path_string ()
{
	name = "relative_path";
	type = T_STRING;

};
cfprelative_path_string::~cfprelative_path_string() {};




cfpfileobj_variablename ::cfpfileobj_variablename ()
{
	name = "fileobj";
	type = T_VARIABLENAME;

};
cfpfileobj_variablename::~cfpfileobj_variablename() {};




cfpsource_string ::cfpsource_string ()
{
	name = "source";
	type = T_STRING;

};
cfpsource_string::~cfpsource_string() {};




cfpdestination_string ::cfpdestination_string ()
{
	name = "destination";
	type = T_STRING;

};
cfpdestination_string::~cfpdestination_string() {};




cfpfilepath_string ::cfpfilepath_string ()
{
	name = "filepath";
	type = T_STRING;

};
cfpfilepath_string::~cfpfilepath_string() {};




cfpfileobject_object ::cfpfileobject_object ()
{
	name = "fileobject";
	type = T_OBJECT;

};
cfpfileobject_object::~cfpfileobject_object() {};




cfpmode_string ::cfpmode_string ()
{
	name = "mode";
	type = T_STRING;

};
cfpmode_string::~cfpmode_string() {};




cfpcharset_string ::cfpcharset_string ()
{
	name = "charset";
	type = T_STRING;

};
cfpcharset_string::~cfpcharset_string() {};




cfpfileobj_object ::cfpfileobj_object ()
{
	name = "fileobj";
	type = T_OBJECT;

};
cfpfileobj_object::~cfpfileobj_object() {};




cfpfile_variablename ::cfpfile_variablename ()
{
	name = "file";
	type = T_VARIABLENAME;

};
cfpfile_variablename::~cfpfile_variablename() {};




cfpattribute_string ::cfpattribute_string ()
{
	name = "attribute";
	type = T_STRING;

};
cfpattribute_string::~cfpattribute_string() {};




cfpbytes_numeric ::cfpbytes_numeric ()
{
	name = "bytes";
	type = T_NUMERIC;

};
cfpbytes_numeric::~cfpbytes_numeric() {};




cfpdata_string ::cfpdata_string ()
{
	name = "data";
	type = T_STRING;

};
cfpdata_string::~cfpdata_string() {};




cfpfile_object ::cfpfile_object ()
{
	name = "file";
	type = T_OBJECT;

};
cfpfile_object::~cfpfile_object() {};




cfptext_string ::cfptext_string ()
{
	name = "text";
	type = T_STRING;

};
cfptext_string::~cfptext_string() {};




cfpsubstring_string ::cfpsubstring_string ()
{
	name = "substring";
	type = T_STRING;

};
cfpsubstring_string::~cfpsubstring_string() {};




cfpset_string ::cfpset_string ()
{
	name = "set";
	type = T_STRING;

};
cfpset_string::~cfpset_string() {};




cfpradix_numeric ::cfpradix_numeric ()
{
	name = "radix";
	type = T_NUMERIC;

};
cfpradix_numeric::~cfpradix_numeric() {};




cfptagname_string ::cfptagname_string ()
{
	name = "tagname";
	type = T_STRING;

};
cfptagname_string::~cfptagname_string() {};




cfpinstancenumber_numeric ::cfpinstancenumber_numeric ()
{
	name = "instancenumber";
	type = T_NUMERIC;

};
cfpinstancenumber_numeric::~cfpinstancenumber_numeric() {};




cfpscope_name_string ::cfpscope_name_string ()
{
	name = "scope_name";
	type = T_STRING;

};
cfpscope_name_string::~cfpscope_name_string() {};




cfpjavaobject_object ::cfpjavaobject_object ()
{
	name = "javaobject";
	type = T_OBJECT;

};
cfpjavaobject_object::~cfpjavaobject_object() {};




cfpgatewayid_string ::cfpgatewayid_string ()
{
	name = "gatewayid";
	type = T_STRING;

};
cfpgatewayid_string::~cfpgatewayid_string() {};




cfpdatetime_datetime ::cfpdatetime_datetime ()
{
	name = "datetime";
	type = T_DATETIME;

};
cfpdatetime_datetime::~cfpdatetime_datetime() {};




cfpobject_object ::cfpobject_object ()
{
	name = "object";
	type = T_OBJECT;

};
cfpobject_object::~cfpobject_object() {};




cfpprinter_string ::cfpprinter_string ()
{
	name = "printer";
	type = T_STRING;

};
cfpprinter_string::~cfpprinter_string() {};




cfpinifile_string ::cfpinifile_string ()
{
	name = "inifile";
	type = T_STRING;

};
cfpinifile_string::~cfpinifile_string() {};




cfpinipath_string ::cfpinipath_string ()
{
	name = "inipath";
	type = T_STRING;

};
cfpinipath_string::~cfpinipath_string() {};




cfpsection_string ::cfpsection_string ()
{
	name = "section";
	type = T_STRING;

};
cfpsection_string::~cfpsection_string() {};




cfpentry_string ::cfpentry_string ()
{
	name = "entry";
	type = T_STRING;

};
cfpentry_string::~cfpentry_string() {};




cfpasxml_boolean ::cfpasxml_boolean ()
{
	name = "asxml";
	type = T_BOOLEAN;

};
cfpasxml_boolean::~cfpasxml_boolean() {};




cfpwebservice_object ::cfpwebservice_object ()
{
	name = "webservice";
	type = T_OBJECT;

};
cfpwebservice_object::~cfpwebservice_object() {};




cfpdir_string ::cfpdir_string ()
{
	name = "dir";
	type = T_STRING;

};
cfpdir_string::~cfpdir_string() {};




cfpprefix_string ::cfpprefix_string ()
{
	name = "prefix";
	type = T_STRING;

};
cfpprefix_string::~cfpprefix_string() {};




cfpindex_numeric ::cfpindex_numeric ()
{
	name = "index";
	type = T_NUMERIC;

};
cfpindex_numeric::~cfpindex_numeric() {};




cfpdelimiters_string ::cfpdelimiters_string ()
{
	name = "delimiters";
	type = T_STRING;

};
cfpdelimiters_string::~cfpdelimiters_string() {};




cfpfilesystemtype_string ::cfpfilesystemtype_string ()
{
	name = "filesystemtype";
	type = T_STRING;

};
cfpfilesystemtype_string::~cfpfilesystemtype_string() {};




cfpversion_numeric ::cfpversion_numeric ()
{
	name = "version";
	type = T_NUMERIC;

};
cfpversion_numeric::~cfpversion_numeric() {};




cfpcondition_boolean ::cfpcondition_boolean ()
{
	name = "condition";
	type = T_BOOLEAN;

};
cfpcondition_boolean::~cfpcondition_boolean() {};




cfpthickness_string ::cfpthickness_string ()
{
	name = "thickness";
	type = T_STRING;

};
cfpthickness_string::~cfpthickness_string() {};




cfpcolor_string ::cfpcolor_string ()
{
	name = "color";
	type = T_STRING;

};
cfpcolor_string::~cfpcolor_string() {};




cfpbordertype_string ::cfpbordertype_string ()
{
	name = "bordertype";
	type = T_STRING;

};
cfpbordertype_string::~cfpbordertype_string() {};




cfpblurradius_numeric ::cfpblurradius_numeric ()
{
	name = "blurradius";
	type = T_NUMERIC;

};
cfpblurradius_numeric::~cfpblurradius_numeric() {};




cfpx_numeric ::cfpx_numeric ()
{
	name = "x";
	type = T_NUMERIC;

};
cfpx_numeric::~cfpx_numeric() {};




cfpy_numeric ::cfpy_numeric ()
{
	name = "y";
	type = T_NUMERIC;

};
cfpy_numeric::~cfpy_numeric() {};




cfpwidth_numeric ::cfpwidth_numeric ()
{
	name = "width";
	type = T_NUMERIC;

};
cfpwidth_numeric::~cfpwidth_numeric() {};




cfpheight_numeric ::cfpheight_numeric ()
{
	name = "height";
	type = T_NUMERIC;

};
cfpheight_numeric::~cfpheight_numeric() {};




cfpdx_numeric ::cfpdx_numeric ()
{
	name = "dx";
	type = T_NUMERIC;

};
cfpdx_numeric::~cfpdx_numeric() {};




cfpdy_numeric ::cfpdy_numeric ()
{
	name = "dy";
	type = T_NUMERIC;

};
cfpdy_numeric::~cfpdy_numeric() {};




cfpstartangle_numeric ::cfpstartangle_numeric ()
{
	name = "startangle";
	type = T_NUMERIC;

};
cfpstartangle_numeric::~cfpstartangle_numeric() {};




cfparchangle_numeric ::cfparchangle_numeric ()
{
	name = "archangle";
	type = T_NUMERIC;

};
cfparchangle_numeric::~cfparchangle_numeric() {};




cfpfilled_boolean ::cfpfilled_boolean ()
{
	name = "filled";
	type = T_BOOLEAN;

};
cfpfilled_boolean::~cfpfilled_boolean() {};




cfpraised_boolean ::cfpraised_boolean ()
{
	name = "raised";
	type = T_BOOLEAN;

};
cfpraised_boolean::~cfpraised_boolean() {};




cfpname_object ::cfpname_object ()
{
	name = "name";
	type = T_OBJECT;

};
cfpname_object::~cfpname_object() {};




cfpctrlx1_string ::cfpctrlx1_string ()
{
	name = "ctrlx1";
	type = T_STRING;

};
cfpctrlx1_string::~cfpctrlx1_string() {};




cfpctrly1_numeric ::cfpctrly1_numeric ()
{
	name = "ctrly1";
	type = T_NUMERIC;

};
cfpctrly1_numeric::~cfpctrly1_numeric() {};




cfpctrlx2_numeric ::cfpctrlx2_numeric ()
{
	name = "ctrlx2";
	type = T_NUMERIC;

};
cfpctrlx2_numeric::~cfpctrlx2_numeric() {};




cfpctrly2_numeric ::cfpctrly2_numeric ()
{
	name = "ctrly2";
	type = T_NUMERIC;

};
cfpctrly2_numeric::~cfpctrly2_numeric() {};




cfpx1_numeric ::cfpx1_numeric ()
{
	name = "x1";
	type = T_NUMERIC;

};
cfpx1_numeric::~cfpx1_numeric() {};




cfpy1_numeric ::cfpy1_numeric ()
{
	name = "y1";
	type = T_NUMERIC;

};
cfpy1_numeric::~cfpy1_numeric() {};




cfpx2_numeric ::cfpx2_numeric ()
{
	name = "x2";
	type = T_NUMERIC;

};
cfpx2_numeric::~cfpx2_numeric() {};




cfpy2_numeric ::cfpy2_numeric ()
{
	name = "y2";
	type = T_NUMERIC;

};
cfpy2_numeric::~cfpy2_numeric() {};




cfpxcords_numeric ::cfpxcords_numeric ()
{
	name = "xcords";
	type = T_NUMERIC;

};
cfpxcords_numeric::~cfpxcords_numeric() {};




cfpycords_numeric ::cfpycords_numeric ()
{
	name = "ycords";
	type = T_NUMERIC;

};
cfpycords_numeric::~cfpycords_numeric() {};




cfpispolygon_boolean ::cfpispolygon_boolean ()
{
	name = "ispolygon";
	type = T_BOOLEAN;

};
cfpispolygon_boolean::~cfpispolygon_boolean() {};




cfparcwidth_numeric ::cfparcwidth_numeric ()
{
	name = "arcwidth";
	type = T_NUMERIC;

};
cfparcwidth_numeric::~cfparcwidth_numeric() {};




cfparcheight_numeric ::cfparcheight_numeric ()
{
	name = "archeight";
	type = T_NUMERIC;

};
cfparcheight_numeric::~cfparcheight_numeric() {};




cfpstr_string ::cfpstr_string ()
{
	name = "str";
	type = T_STRING;

};
cfpstr_string::~cfpstr_string() {};




cfpattributecollection_struct ::cfpattributecollection_struct ()
{
	name = "attributecollection";
	type = T_STRUCT;

};
cfpattributecollection_struct::~cfpattributecollection_struct() {};




cfptranspose_string ::cfptranspose_string ()
{
	name = "transpose";
	type = T_STRING;

};
cfptranspose_string::~cfptranspose_string() {};




cfpimagetype_string ::cfpimagetype_string ()
{
	name = "imagetype";
	type = T_STRING;

};
cfpimagetype_string::~cfpimagetype_string() {};




cfpcanvascolor_string ::cfpcanvascolor_string ()
{
	name = "canvascolor";
	type = T_STRING;

};
cfpcanvascolor_string::~cfpcanvascolor_string() {};




cfpsource1_string ::cfpsource1_string ()
{
	name = "source1";
	type = T_STRING;

};
cfpsource1_string::~cfpsource1_string() {};




cfpsource2_string ::cfpsource2_string ()
{
	name = "source2";
	type = T_STRING;

};
cfpsource2_string::~cfpsource2_string() {};




cfpimage1_string ::cfpimage1_string ()
{
	name = "image1";
	type = T_STRING;

};
cfpimage1_string::~cfpimage1_string() {};




cfpimage2_string ::cfpimage2_string ()
{
	name = "image2";
	type = T_STRING;

};
cfpimage2_string::~cfpimage2_string() {};




cfpinterpolation_string ::cfpinterpolation_string ()
{
	name = "interpolation";
	type = T_STRING;

};
cfpinterpolation_string::~cfpinterpolation_string() {};




cfpblurfactor_boolean ::cfpblurfactor_boolean ()
{
	name = "blurfactor";
	type = T_BOOLEAN;

};
cfpblurfactor_boolean::~cfpblurfactor_boolean() {};




cfpangle_numeric ::cfpangle_numeric ()
{
	name = "angle";
	type = T_NUMERIC;

};
cfpangle_numeric::~cfpangle_numeric() {};




cfpfitwidth_numeric ::cfpfitwidth_numeric ()
{
	name = "fitwidth";
	type = T_NUMERIC;

};
cfpfitwidth_numeric::~cfpfitwidth_numeric() {};




cfpfitheight_numeric ::cfpfitheight_numeric ()
{
	name = "fitheight";
	type = T_NUMERIC;

};
cfpfitheight_numeric::~cfpfitheight_numeric() {};




cfpblurfactor_numeric ::cfpblurfactor_numeric ()
{
	name = "blurfactor";
	type = T_NUMERIC;

};
cfpblurfactor_numeric::~cfpblurfactor_numeric() {};




cfpantialias_boolean ::cfpantialias_boolean ()
{
	name = "antialias";
	type = T_BOOLEAN;

};
cfpantialias_boolean::~cfpantialias_boolean() {};




cfppercent_numeric ::cfppercent_numeric ()
{
	name = "percent";
	type = T_NUMERIC;

};
cfppercent_numeric::~cfppercent_numeric() {};




cfpgain_numeric ::cfpgain_numeric ()
{
	name = "gain";
	type = T_NUMERIC;

};
cfpgain_numeric::~cfpgain_numeric() {};




cfpshear_numeric ::cfpshear_numeric ()
{
	name = "shear";
	type = T_NUMERIC;

};
cfpshear_numeric::~cfpshear_numeric() {};




cfpdirection_string ::cfpdirection_string ()
{
	name = "direction";
	type = T_STRING;

};
cfpdirection_string::~cfpdirection_string() {};




cfpshrx_numeric ::cfpshrx_numeric ()
{
	name = "shrx";
	type = T_NUMERIC;

};
cfpshrx_numeric::~cfpshrx_numeric() {};




cfpshry_numeric ::cfpshry_numeric ()
{
	name = "shry";
	type = T_NUMERIC;

};
cfpshry_numeric::~cfpshry_numeric() {};




cfpxtrans_numeric ::cfpxtrans_numeric ()
{
	name = "xtrans";
	type = T_NUMERIC;

};
cfpxtrans_numeric::~cfpxtrans_numeric() {};




cfpytrans_numeric ::cfpytrans_numeric ()
{
	name = "ytrans";
	type = T_NUMERIC;

};
cfpytrans_numeric::~cfpytrans_numeric() {};




cfpquality_string ::cfpquality_string ()
{
	name = "quality";
	type = T_STRING;

};
cfpquality_string::~cfpquality_string() {};




cfpoverwrite_boolean ::cfpoverwrite_boolean ()
{
	name = "overwrite";
	type = T_BOOLEAN;

};
cfpoverwrite_boolean::~cfpoverwrite_boolean() {};




cfpformat_string ::cfpformat_string ()
{
	name = "format";
	type = T_STRING;

};
cfpformat_string::~cfpformat_string() {};




cfpinhtmlformat_boolean ::cfpinhtmlformat_boolean ()
{
	name = "inhtmlformat";
	type = T_BOOLEAN;

};
cfpinhtmlformat_boolean::~cfpinhtmlformat_boolean() {};




cfpc1_string ::cfpc1_string ()
{
	name = "c1";
	type = T_STRING;

};
cfpc1_string::~cfpc1_string() {};




cfpradix_string ::cfpradix_string ()
{
	name = "radix";
	type = T_STRING;

};
cfpradix_string::~cfpradix_string() {};




cfpvariable_name_string ::cfpvariable_name_string ()
{
	name = "variable_name";
	type = T_STRING;

};
cfpvariable_name_string::~cfpvariable_name_string() {};




cfptypename_string ::cfptypename_string ()
{
	name = "typename";
	type = T_STRING;

};
cfptypename_string::~cfptypename_string() {};




cfpip_string ::cfpip_string ()
{
	name = "ip";
	type = T_STRING;

};
cfpip_string::~cfpip_string() {};




cfpvar_string ::cfpvar_string ()
{
	name = "var";
	type = T_STRING;

};
cfpvar_string::~cfpvar_string() {};




cfpipaddress_string ::cfpipaddress_string ()
{
	name = "ipaddress";
	type = T_STRING;

};
cfpipaddress_string::~cfpipaddress_string() {};




cfpvalue_variablename ::cfpvalue_variablename ()
{
	name = "value";
	type = T_VARIABLENAME;

};
cfpvalue_variablename::~cfpvalue_variablename() {};




cfpfile_string ::cfpfile_string ()
{
	name = "file";
	type = T_STRING;

};
cfpfile_string::~cfpfile_string() {};




cfprolelist_string ::cfprolelist_string ()
{
	name = "rolelist";
	type = T_STRING;

};
cfprolelist_string::~cfprolelist_string() {};




cfprole_name_string ::cfprole_name_string ()
{
	name = "role_name";
	type = T_STRING;

};
cfprole_name_string::~cfprole_name_string() {};




cfpmin_numeric ::cfpmin_numeric ()
{
	name = "min";
	type = T_NUMERIC;

};
cfpmin_numeric::~cfpmin_numeric() {};




cfpmax_numeric ::cfpmax_numeric ()
{
	name = "max";
	type = T_NUMERIC;

};
cfpmax_numeric::~cfpmax_numeric() {};




cfppattern_string ::cfppattern_string ()
{
	name = "pattern";
	type = T_STRING;

};
cfppattern_string::~cfppattern_string() {};




cfpvariable_string ::cfpvariable_string ()
{
	name = "variable";
	type = T_STRING;

};
cfpvariable_string::~cfpvariable_string() {};




cfplist_string ::cfplist_string ()
{
	name = "list";
	type = T_STRING;

};
cfplist_string::~cfplist_string() {};




cfpnew_delimiter_string ::cfpnew_delimiter_string ()
{
	name = "new_delimiter";
	type = T_STRING;

};
cfpnew_delimiter_string::~cfpnew_delimiter_string() {};




cfpqualifier_string ::cfpqualifier_string ()
{
	name = "qualifier";
	type = T_STRING;

};
cfpqualifier_string::~cfpqualifier_string() {};




cfpelements_string ::cfpelements_string ()
{
	name = "elements";
	type = T_STRING;

};
cfpelements_string::~cfpelements_string() {};




cfpincludeemptyfields_boolean ::cfpincludeemptyfields_boolean ()
{
	name = "includeemptyfields";
	type = T_BOOLEAN;

};
cfpincludeemptyfields_boolean::~cfpincludeemptyfields_boolean() {};




cfpmulticharacterdelimiter_boolean ::cfpmulticharacterdelimiter_boolean ()
{
	name = "multicharacterdelimiter";
	type = T_BOOLEAN;

};
cfpmulticharacterdelimiter_boolean::~cfpmulticharacterdelimiter_boolean() {};




cfpaddtoken_boolean ::cfpaddtoken_boolean ()
{
	name = "addtoken";
	type = T_BOOLEAN;

};
cfpaddtoken_boolean::~cfpaddtoken_boolean() {};




cfpstatuscode_numeric ::cfpstatuscode_numeric ()
{
	name = "statuscode";
	type = T_NUMERIC;

};
cfpstatuscode_numeric::~cfpstatuscode_numeric() {};




cfpcurrency_string ::cfpcurrency_string ()
{
	name = "currency";
	type = T_STRING;

};
cfpcurrency_string::~cfpcurrency_string() {};




cfpdt_string_string ::cfpdt_string_string ()
{
	name = "dt_string";
	type = T_STRING;

};
cfpdt_string_string::~cfpdt_string_string() {};




cfpcurrency_string_string ::cfpcurrency_string_string ()
{
	name = "currency_string";
	type = T_STRING;

};
cfpcurrency_string_string::~cfpcurrency_string_string() {};




cfptime_datetime ::cfptime_datetime ()
{
	name = "time";
	type = T_DATETIME;

};
cfptime_datetime::~cfptime_datetime() {};




cfpmonth_number_numeric ::cfpmonth_number_numeric ()
{
	name = "month_number";
	type = T_NUMERIC;

};
cfpmonth_number_numeric::~cfpmonth_number_numeric() {};




cfpparam1_object ::cfpparam1_object ()
{
	name = "param1";
	type = T_OBJECT;

};
cfpparam1_object::~cfpparam1_object() {};




cfpparam2_object ::cfpparam2_object ()
{
	name = "param2";
	type = T_OBJECT;

};
cfpparam2_object::~cfpparam2_object() {};




cfpbinaryobject_object ::cfpbinaryobject_object ()
{
	name = "binaryobject";
	type = T_OBJECT;

};
cfpbinaryobject_object::~cfpbinaryobject_object() {};




cfpcomponentname_string ::cfpcomponentname_string ()
{
	name = "componentname";
	type = T_STRING;

};
cfpcomponentname_string::~cfpcomponentname_string() {};




cfprelationname_string ::cfprelationname_string ()
{
	name = "relationname";
	type = T_STRING;

};
cfprelationname_string::~cfprelationname_string() {};




cfpcachename_string ::cfpcachename_string ()
{
	name = "cachename";
	type = T_STRING;

};
cfpcachename_string::~cfpcachename_string() {};




cfphql_string ::cfphql_string ()
{
	name = "hql";
	type = T_STRING;

};
cfphql_string::~cfphql_string() {};




cfpqueryoptions_string ::cfpqueryoptions_string ()
{
	name = "queryoptions";
	type = T_STRING;

};
cfpqueryoptions_string::~cfpqueryoptions_string() {};




cfppop_conversion_string ::cfppop_conversion_string ()
{
	name = "pop_conversion";
	type = T_STRING;

};
cfppop_conversion_string::~cfppop_conversion_string() {};




cfpexpressions_string ::cfpexpressions_string ()
{
	name = "expressions";
	type = T_STRING;

};
cfpexpressions_string::~cfpexpressions_string() {};




cfpquery_query ::cfpquery_query ()
{
	name = "query";
	type = T_QUERY;

};
cfpquery_query::~cfpquery_query() {};




cfpcolumn_name_string ::cfpcolumn_name_string ()
{
	name = "column_name";
	type = T_STRING;

};
cfpcolumn_name_string::~cfpcolumn_name_string() {};




cfpdatatype_string ::cfpdatatype_string ()
{
	name = "datatype";
	type = T_STRING;

};
cfpdatatype_string::~cfpdatatype_string() {};




cfparray_name_array ::cfparray_name_array ()
{
	name = "array_name";
	type = T_ARRAY;

};
cfparray_name_array::~cfparray_name_array() {};




cfpquery_string ::cfpquery_string ()
{
	name = "query";
	type = T_STRING;

};
cfpquery_string::~cfpquery_string() {};




cfppage_numeric ::cfppage_numeric ()
{
	name = "page";
	type = T_NUMERIC;

};
cfppage_numeric::~cfppage_numeric() {};




cfppagesize_numeric ::cfppagesize_numeric ()
{
	name = "pagesize";
	type = T_NUMERIC;

};
cfppagesize_numeric::~cfppagesize_numeric() {};




cfpcolumnlist_string ::cfpcolumnlist_string ()
{
	name = "columnlist";
	type = T_STRING;

};
cfpcolumnlist_string::~cfpcolumnlist_string() {};




cfpcolumntypelist_string ::cfpcolumntypelist_string ()
{
	name = "columntypelist";
	type = T_STRING;

};
cfpcolumntypelist_string::~cfpcolumntypelist_string() {};




cfpcolumn_string ::cfpcolumn_string ()
{
	name = "column";
	type = T_STRING;

};
cfpcolumn_string::~cfpcolumn_string() {};




cfprow_numeric ::cfprow_numeric ()
{
	name = "row";
	type = T_NUMERIC;

};
cfprow_numeric::~cfprow_numeric() {};




cfpcolumn_querycolumn ::cfpcolumn_querycolumn ()
{
	name = "column";
	type = T_QUERYCOLUMN;

};
cfpcolumn_querycolumn::~cfpcolumn_querycolumn() {};




cfpreg_expression_regex ::cfpreg_expression_regex ()
{
	name = "reg_expression";
	type = T_REGEX;

};
cfpreg_expression_regex::~cfpreg_expression_regex() {};




cfpreturnsubexpressions_boolean ::cfpreturnsubexpressions_boolean ()
{
	name = "returnsubexpressions";
	type = T_BOOLEAN;

};
cfpreturnsubexpressions_boolean::~cfpreturnsubexpressions_boolean() {};




cfpobjectname_object ::cfpobjectname_object ()
{
	name = "objectname";
	type = T_OBJECT;

};
cfpobjectname_object::~cfpobjectname_object() {};




cfpreg_expression_string ::cfpreg_expression_string ()
{
	name = "reg_expression";
	type = T_STRING;

};
cfpreg_expression_string::~cfpreg_expression_string() {};




cfpsubstring1_string ::cfpsubstring1_string ()
{
	name = "substring1";
	type = T_STRING;

};
cfpsubstring1_string::~cfpsubstring1_string() {};




cfpsubstring2_string ::cfpsubstring2_string ()
{
	name = "substring2";
	type = T_STRING;

};
cfpsubstring2_string::~cfpsubstring2_string() {};




cfpscope_string ::cfpscope_string ()
{
	name = "scope";
	type = T_STRING;

};
cfpscope_string::~cfpscope_string() {};




cfplist1_string ::cfplist1_string ()
{
	name = "list1";
	type = T_STRING;

};
cfplist1_string::~cfplist1_string() {};




cfplist2_string ::cfplist2_string ()
{
	name = "list2";
	type = T_STRING;

};
cfplist2_string::~cfplist2_string() {};




cfpdata_struct ::cfpdata_struct ()
{
	name = "data";
	type = T_STRUCT;

};
cfpdata_struct::~cfpdata_struct() {};




cfpvar_variablename ::cfpvar_variablename ()
{
	name = "var";
	type = T_VARIABLENAME;

};
cfpvar_variablename::~cfpvar_variablename() {};




cfpserializequerybycolumns_boolean ::cfpserializequerybycolumns_boolean ()
{
	name = "serializequerybycolumns";
	type = T_BOOLEAN;

};
cfpserializequerybycolumns_boolean::~cfpserializequerybycolumns_boolean() {};




cfpnew_locale_string ::cfpnew_locale_string ()
{
	name = "new_locale";
	type = T_STRING;

};
cfpnew_locale_string::~cfpnew_locale_string() {};




cfpduration_numeric ::cfpduration_numeric ()
{
	name = "duration";
	type = T_NUMERIC;

};
cfpduration_numeric::~cfpduration_numeric() {};




cfpspreadsheetobj_variablename ::cfpspreadsheetobj_variablename ()
{
	name = "spreadsheetobj";
	type = T_VARIABLENAME;

};
cfpspreadsheetobj_variablename::~cfpspreadsheetobj_variablename() {};




cfpstartrow_numeric ::cfpstartrow_numeric ()
{
	name = "startrow";
	type = T_NUMERIC;

};
cfpstartrow_numeric::~cfpstartrow_numeric() {};




cfpstartcolumn_numeric ::cfpstartcolumn_numeric ()
{
	name = "startcolumn";
	type = T_NUMERIC;

};
cfpstartcolumn_numeric::~cfpstartcolumn_numeric() {};




cfpinsert_boolean ::cfpinsert_boolean ()
{
	name = "insert";
	type = T_BOOLEAN;

};
cfpinsert_boolean::~cfpinsert_boolean() {};




cfpcolumn_numeric ::cfpcolumn_numeric ()
{
	name = "column";
	type = T_NUMERIC;

};
cfpcolumn_numeric::~cfpcolumn_numeric() {};




cfpendcolumn_numeric ::cfpendcolumn_numeric ()
{
	name = "endcolumn";
	type = T_NUMERIC;

};
cfpendcolumn_numeric::~cfpendcolumn_numeric() {};




cfpendrow_numeric ::cfpendrow_numeric ()
{
	name = "endrow";
	type = T_NUMERIC;

};
cfpendrow_numeric::~cfpendrow_numeric() {};




cfpimagefilepath_string ::cfpimagefilepath_string ()
{
	name = "imagefilepath";
	type = T_STRING;

};
cfpimagefilepath_string::~cfpimagefilepath_string() {};




cfpanchor_string ::cfpanchor_string ()
{
	name = "anchor";
	type = T_STRING;

};
cfpanchor_string::~cfpanchor_string() {};




cfpimagedata_string ::cfpimagedata_string ()
{
	name = "imagedata";
	type = T_STRING;

};
cfpimagedata_string::~cfpimagedata_string() {};




cfpinfo_struct ::cfpinfo_struct ()
{
	name = "info";
	type = T_STRUCT;

};
cfpinfo_struct::~cfpinfo_struct() {};




cfpsplitcolumn_numeric ::cfpsplitcolumn_numeric ()
{
	name = "splitcolumn";
	type = T_NUMERIC;

};
cfpsplitcolumn_numeric::~cfpsplitcolumn_numeric() {};




cfpsplitrow_numeric ::cfpsplitrow_numeric ()
{
	name = "splitrow";
	type = T_NUMERIC;

};
cfpsplitrow_numeric::~cfpsplitrow_numeric() {};




cfpposition_string ::cfpposition_string ()
{
	name = "position";
	type = T_STRING;

};
cfpposition_string::~cfpposition_string() {};




cfprange_numeric ::cfprange_numeric ()
{
	name = "range";
	type = T_NUMERIC;

};
cfprange_numeric::~cfprange_numeric() {};




cfpcolumns_string ::cfpcolumns_string ()
{
	name = "columns";
	type = T_STRING;

};
cfpcolumns_string::~cfpcolumns_string() {};




cfpauthor_string ::cfpauthor_string ()
{
	name = "author";
	type = T_STRING;

};
cfpauthor_string::~cfpauthor_string() {};




cfpcomment_string ::cfpcomment_string ()
{
	name = "comment";
	type = T_STRING;

};
cfpcomment_string::~cfpcomment_string() {};




cfprow_string ::cfprow_string ()
{
	name = "row";
	type = T_STRING;

};
cfprow_string::~cfprow_string() {};




cfpsheetname_string ::cfpsheetname_string ()
{
	name = "sheetname";
	type = T_STRING;

};
cfpsheetname_string::~cfpsheetname_string() {};




cfpxmlformat_boolean ::cfpxmlformat_boolean ()
{
	name = "xmlformat";
	type = T_BOOLEAN;

};
cfpxmlformat_boolean::~cfpxmlformat_boolean() {};




cfpfilename_string ::cfpfilename_string ()
{
	name = "filename";
	type = T_STRING;

};
cfpfilename_string::~cfpfilename_string() {};




cfpformula_string ::cfpformula_string ()
{
	name = "formula";
	type = T_STRING;

};
cfpformula_string::~cfpformula_string() {};




cfpcolumnnumber_numeric ::cfpcolumnnumber_numeric ()
{
	name = "columnnumber";
	type = T_NUMERIC;

};
cfpcolumnnumber_numeric::~cfpcolumnnumber_numeric() {};




cfpleftfooter_string ::cfpleftfooter_string ()
{
	name = "leftfooter";
	type = T_STRING;

};
cfpleftfooter_string::~cfpleftfooter_string() {};




cfpcenterfooter_string ::cfpcenterfooter_string ()
{
	name = "centerfooter";
	type = T_STRING;

};
cfpcenterfooter_string::~cfpcenterfooter_string() {};




cfprightfooter_string ::cfprightfooter_string ()
{
	name = "rightfooter";
	type = T_STRING;

};
cfprightfooter_string::~cfprightfooter_string() {};




cfpleftheader_string ::cfpleftheader_string ()
{
	name = "leftheader";
	type = T_STRING;

};
cfpleftheader_string::~cfpleftheader_string() {};




cfpcenterheader_string ::cfpcenterheader_string ()
{
	name = "centerheader";
	type = T_STRING;

};
cfpcenterheader_string::~cfpcenterheader_string() {};




cfprightheader_string ::cfprightheader_string ()
{
	name = "rightheader";
	type = T_STRING;

};
cfprightheader_string::~cfprightheader_string() {};




cfprownumber_numeric ::cfprownumber_numeric ()
{
	name = "rownumber";
	type = T_NUMERIC;

};
cfprownumber_numeric::~cfprownumber_numeric() {};




cfpend_numeric ::cfpend_numeric ()
{
	name = "end";
	type = T_NUMERIC;

};
cfpend_numeric::~cfpend_numeric() {};




cfprows_numeric ::cfprows_numeric ()
{
	name = "rows";
	type = T_NUMERIC;

};
cfprows_numeric::~cfprows_numeric() {};




cfppassword_string ::cfppassword_string ()
{
	name = "password";
	type = T_STRING;

};
cfppassword_string::~cfppassword_string() {};




cfpstruct1_struct ::cfpstruct1_struct ()
{
	name = "struct1";
	type = T_STRUCT;

};
cfpstruct1_struct::~cfpstruct1_struct() {};




cfpstruct2_struct ::cfpstruct2_struct ()
{
	name = "struct2";
	type = T_STRUCT;

};
cfpstruct2_struct::~cfpstruct2_struct() {};




cfpoverwriteflag_boolean ::cfpoverwriteflag_boolean ()
{
	name = "overwriteflag";
	type = T_BOOLEAN;

};
cfpoverwriteflag_boolean::~cfpoverwriteflag_boolean() {};




cfpstructure_struct ::cfpstructure_struct ()
{
	name = "structure";
	type = T_STRUCT;

};
cfpstructure_struct::~cfpstructure_struct() {};




cfpstructure_string ::cfpstructure_string ()
{
	name = "structure";
	type = T_STRING;

};
cfpstructure_string::~cfpstructure_string() {};




cfpindicatenotexisting_boolean ::cfpindicatenotexisting_boolean ()
{
	name = "indicatenotexisting";
	type = T_BOOLEAN;

};
cfpindicatenotexisting_boolean::~cfpindicatenotexisting_boolean() {};




cfptop_object ::cfptop_object ()
{
	name = "top";
	type = T_OBJECT;

};
cfptop_object::~cfptop_object() {};




cfppathdesired_string ::cfppathdesired_string ()
{
	name = "pathdesired";
	type = T_STRING;

};
cfppathdesired_string::~cfppathdesired_string() {};




cfpallowoverwrite_boolean ::cfpallowoverwrite_boolean ()
{
	name = "allowoverwrite";
	type = T_BOOLEAN;

};
cfpallowoverwrite_boolean::~cfpallowoverwrite_boolean() {};




cfpbase_struct ::cfpbase_struct ()
{
	name = "base";
	type = T_STRUCT;

};
cfpbase_struct::~cfpbase_struct() {};




cfpsorttype_string ::cfpsorttype_string ()
{
	name = "sorttype";
	type = T_STRING;

};
cfpsorttype_string::~cfpsorttype_string() {};




cfppathtosubelement_string ::cfppathtosubelement_string ()
{
	name = "pathtosubelement";
	type = T_STRING;

};
cfppathtosubelement_string::~cfppathtosubelement_string() {};




cfpthreadname_string ::cfpthreadname_string ()
{
	name = "threadname";
	type = T_STRING;

};
cfpthreadname_string::~cfpthreadname_string() {};




cfptimeout_numeric ::cfptimeout_numeric ()
{
	name = "timeout";
	type = T_NUMERIC;

};
cfptimeout_numeric::~cfptimeout_numeric() {};




cfpmessage_string ::cfpmessage_string ()
{
	name = "message";
	type = T_STRING;

};
cfpmessage_string::~cfpmessage_string() {};




cfpdetail_string ::cfpdetail_string ()
{
	name = "detail";
	type = T_STRING;

};
cfpdetail_string::~cfpdetail_string() {};




cfperrorcode_string ::cfperrorcode_string ()
{
	name = "errorcode";
	type = T_STRING;

};
cfperrorcode_string::~cfperrorcode_string() {};




cfpextendedinfo_string ::cfpextendedinfo_string ()
{
	name = "extendedinfo";
	type = T_STRING;

};
cfpextendedinfo_string::~cfpextendedinfo_string() {};




cfpstring_or_object_object ::cfpstring_or_object_object ()
{
	name = "string_or_object";
	type = T_OBJECT;

};
cfpstring_or_object_object::~cfpstring_or_object_object() {};




cfpbase64_or_object_object ::cfpbase64_or_object_object ()
{
	name = "base64_or_object";
	type = T_OBJECT;

};
cfpbase64_or_object_object::~cfpbase64_or_object_object() {};




cfpcfvar_object ::cfpcfvar_object ()
{
	name = "cfvar";
	type = T_OBJECT;

};
cfpcfvar_object::~cfpcfvar_object() {};




cfpjavascriptvar_string ::cfpjavascriptvar_string ()
{
	name = "javascriptvar";
	type = T_STRING;

};
cfpjavascriptvar_string::~cfpjavascriptvar_string() {};




cfpoutputformat_boolean ::cfpoutputformat_boolean ()
{
	name = "outputformat";
	type = T_BOOLEAN;

};
cfpoutputformat_boolean::~cfpoutputformat_boolean() {};




cfpasformat_boolean ::cfpasformat_boolean ()
{
	name = "asformat";
	type = T_BOOLEAN;

};
cfpasformat_boolean::~cfpasformat_boolean() {};




cfpany_value_object ::cfpany_value_object ()
{
	name = "any_value";
	type = T_OBJECT;

};
cfpany_value_object::~cfpany_value_object() {};




cfpabort_boolean ::cfpabort_boolean ()
{
	name = "abort";
	type = T_BOOLEAN;

};
cfpabort_boolean::~cfpabort_boolean() {};




cfpcategory_string ::cfpcategory_string ()
{
	name = "category";
	type = T_STRING;

};
cfpcategory_string::~cfpcategory_string() {};




cfpinline_boolean ::cfpinline_boolean ()
{
	name = "inline";
	type = T_BOOLEAN;

};
cfpinline_boolean::~cfpinline_boolean() {};




cfpsavepoint_string ::cfpsavepoint_string ()
{
	name = "savepoint";
	type = T_STRING;

};
cfpsavepoint_string::~cfpsavepoint_string() {};




cfpurlencodedstring_string ::cfpurlencodedstring_string ()
{
	name = "urlencodedstring";
	type = T_STRING;

};
cfpurlencodedstring_string::~cfpurlencodedstring_string() {};




cfprequesturl_string ::cfprequesturl_string ()
{
	name = "requesturl";
	type = T_STRING;

};
cfprequesturl_string::~cfprequesturl_string() {};




cfplimit_numeric ::cfplimit_numeric ()
{
	name = "limit";
	type = T_NUMERIC;

};
cfplimit_numeric::~cfplimit_numeric() {};




cfpstrip_boolean ::cfpstrip_boolean ()
{
	name = "strip";
	type = T_BOOLEAN;

};
cfpstrip_boolean::~cfpstrip_boolean() {};




cfpexpand_boolean ::cfpexpand_boolean ()
{
	name = "expand";
	type = T_BOOLEAN;

};
cfpexpand_boolean::~cfpexpand_boolean() {};




cfphide_string ::cfphide_string ()
{
	name = "hide";
	type = T_STRING;

};
cfphide_string::~cfphide_string() {};




cfpkeys_numeric ::cfpkeys_numeric ()
{
	name = "keys";
	type = T_NUMERIC;

};
cfpkeys_numeric::~cfpkeys_numeric() {};




cfplabel_string ::cfplabel_string ()
{
	name = "label";
	type = T_STRING;

};
cfplabel_string::~cfplabel_string() {};




cfpmetainfo_boolean ::cfpmetainfo_boolean ()
{
	name = "metainfo";
	type = T_BOOLEAN;

};
cfpmetainfo_boolean::~cfpmetainfo_boolean() {};




cfpoutput_string ::cfpoutput_string ()
{
	name = "output";
	type = T_STRING;

};
cfpoutput_string::~cfpoutput_string() {};




cfpshow_string ::cfpshow_string ()
{
	name = "show";
	type = T_STRING;

};
cfpshow_string::~cfpshow_string() {};




cfpshowudfs_boolean ::cfpshowudfs_boolean ()
{
	name = "showudfs";
	type = T_BOOLEAN;

};
cfpshowudfs_boolean::~cfpshowudfs_boolean() {};




cfptop_numeric ::cfptop_numeric ()
{
	name = "top";
	type = T_NUMERIC;

};
cfptop_numeric::~cfptop_numeric() {};




cfplog_string ::cfplog_string ()
{
	name = "log";
	type = T_STRING;

};
cfplog_string::~cfplog_string() {};




cfpapplication_boolean ::cfpapplication_boolean ()
{
	name = "application";
	type = T_BOOLEAN;

};
cfpapplication_boolean::~cfpapplication_boolean() {};




cfpelem_node ::cfpelem_node ()
{
	name = "elem";
	type = T_NODE;

};
cfpelem_node::~cfpelem_node() {};




cfpchildname_string ::cfpchildname_string ()
{
	name = "childname";
	type = T_STRING;

};
cfpchildname_string::~cfpchildname_string() {};




cfpn_numeric ::cfpn_numeric ()
{
	name = "n";
	type = T_NUMERIC;

};
cfpn_numeric::~cfpn_numeric() {};




cfpxmlobj_object ::cfpxmlobj_object ()
{
	name = "xmlobj";
	type = T_OBJECT;

};
cfpxmlobj_object::~cfpxmlobj_object() {};




cfpescapenewset_boolean ::cfpescapenewset_boolean ()
{
	name = "escapenewset";
	type = T_BOOLEAN;

};
cfpescapenewset_boolean::~cfpescapenewset_boolean() {};




cfpxmlnode_object ::cfpxmlnode_object ()
{
	name = "xmlnode";
	type = T_OBJECT;

};
cfpxmlnode_object::~cfpxmlnode_object() {};




cfpcasesensitive_boolean ::cfpcasesensitive_boolean ()
{
	name = "casesensitive";
	type = T_BOOLEAN;

};
cfpcasesensitive_boolean::~cfpcasesensitive_boolean() {};




cfpxmlstring_string ::cfpxmlstring_string ()
{
	name = "xmlstring";
	type = T_STRING;

};
cfpxmlstring_string::~cfpxmlstring_string() {};




cfpvalidator_string ::cfpvalidator_string ()
{
	name = "validator";
	type = T_STRING;

};
cfpvalidator_string::~cfpvalidator_string() {};




cfpxmldoc_object ::cfpxmldoc_object ()
{
	name = "xmldoc";
	type = T_OBJECT;

};
cfpxmldoc_object::~cfpxmldoc_object() {};




cfpxpathstring_string ::cfpxpathstring_string ()
{
	name = "xpathstring";
	type = T_STRING;

};
cfpxpathstring_string::~cfpxpathstring_string() {};




cfpxml_string ::cfpxml_string ()
{
	name = "xml";
	type = T_STRING;

};
cfpxml_string::~cfpxml_string() {};




cfpxsl_string ::cfpxsl_string ()
{
	name = "xsl";
	type = T_STRING;

};
cfpxsl_string::~cfpxsl_string() {};




cfpparameters_struct ::cfpparameters_struct ()
{
	name = "parameters";
	type = T_STRUCT;

};
cfpparameters_struct::~cfpparameters_struct() {};




cfpvalue_boolean ::cfpvalue_boolean ()
{
	name = "value";
	type = T_BOOLEAN;

};
cfpvalue_boolean::~cfpvalue_boolean() {};



#ifdef NPP_CFWHEELS


cfpproperty_string::cfpproperty_string()
{
	name = "property";
	type = T_STRING;

}

cfpproperty_string::~cfpproperty_string() {};












cfpcontroller_string::cfpcontroller_string()
{
	name = "controller";
	type = T_STRING;

}

cfpcontroller_string::~cfpcontroller_string() {};




cfpaction_string::cfpaction_string()
{
	name = "action";
	type = T_STRING;

}

cfpaction_string::~cfpaction_string() {};




cfpmethods_string::cfpmethods_string()
{
	name = "methods";
	type = T_STRING;

}

cfpmethods_string::~cfpmethods_string() {};




cfpwhere_string::cfpwhere_string()
{
	name = "where";
	type = T_STRING;

}

cfpwhere_string::~cfpwhere_string() {};




cfpinclude_string::cfpinclude_string()
{
	name = "include";
	type = T_STRING;

}

cfpinclude_string::~cfpinclude_string() {};




cfpdistinct_boolean::cfpdistinct_boolean()
{
	name = "distinct";
	type = T_BOOLEAN;

}

cfpdistinct_boolean::~cfpdistinct_boolean() {};





cfpforeignkey_string::cfpforeignkey_string()
{
	name = "foreignkey";
	type = T_STRING;

}

cfpforeignkey_string::~cfpforeignkey_string() {};




cfpjointype_string::cfpjointype_string()
{
	name = "jointype";
	type = T_STRING;

}

cfpjointype_string::~cfpjointype_string() {};




cfpwindowsize_numeric::cfpwindowsize_numeric()
{
	name = "windowsize";
	type = T_NUMERIC;

}

cfpwindowsize_numeric::~cfpwindowsize_numeric() {};




cfpalwaysshowanchors_boolean::cfpalwaysshowanchors_boolean()
{
	name = "alwaysshowanchors";
	type = T_BOOLEAN;

}

cfpalwaysshowanchors_boolean::~cfpalwaysshowanchors_boolean() {};




cfpanchordivider_string::cfpanchordivider_string()
{
	name = "anchordivider";
	type = T_STRING;

}

cfpanchordivider_string::~cfpanchordivider_string() {};




cfplinktocurrentpage_boolean::cfplinktocurrentpage_boolean()
{
	name = "linktocurrentpage";
	type = T_BOOLEAN;

}

cfplinktocurrentpage_boolean::~cfplinktocurrentpage_boolean() {};




cfpprepend_string::cfpprepend_string()
{
	name = "prepend";
	type = T_STRING;

}

cfpprepend_string::~cfpprepend_string() {};




cfpappend_string::cfpappend_string()
{
	name = "append";
	type = T_STRING;

}

cfpappend_string::~cfpappend_string() {};




cfpprependtopage_string::cfpprependtopage_string()
{
	name = "prependtopage";
	type = T_STRING;

}

cfpprependtopage_string::~cfpprependtopage_string() {};




cfpprependonfirst_boolean::cfpprependonfirst_boolean()
{
	name = "prependonfirst";
	type = T_BOOLEAN;

}

cfpprependonfirst_boolean::~cfpprependonfirst_boolean() {};




cfpappendtopage_string::cfpappendtopage_string()
{
	name = "appendtopage";
	type = T_STRING;

}

cfpappendtopage_string::~cfpappendtopage_string() {};




cfpappendonlast_boolean::cfpappendonlast_boolean()
{
	name = "appendonlast";
	type = T_BOOLEAN;

}

cfpappendonlast_boolean::~cfpappendonlast_boolean() {};




cfpclassforcurrent_string::cfpclassforcurrent_string()
{
	name = "classforcurrent";
	type = T_STRING;

}

cfpclassforcurrent_string::~cfpclassforcurrent_string() {};




cfphandle_string::cfphandle_string()
{
	name = "handle";
	type = T_STRING;

}

cfphandle_string::~cfphandle_string() {};




cfpshowsinglepage_boolean::cfpshowsinglepage_boolean()
{
	name = "showsinglepage";
	type = T_BOOLEAN;

}

cfpshowsinglepage_boolean::~cfpshowsinglepage_boolean() {};




cfpactions_string::cfpactions_string()
{
	name = "actions";
	type = T_STRING;

}

cfpactions_string::~cfpactions_string() {};




cfptime_numeric::cfptime_numeric()
{
	name = "time";
	type = T_NUMERIC;

}

cfptime_numeric::~cfptime_numeric() {};








cfpobjectname_any::cfpobjectname_any()
{
	name = "objectname";
	type = T_ANY;

}

cfpobjectname_any::~cfpobjectname_any() {};




cfpcheckedvalue_string::cfpcheckedvalue_string()
{
	name = "checkedvalue";
	type = T_STRING;

}

cfpcheckedvalue_string::~cfpcheckedvalue_string() {};




cfpuncheckedvalue_string::cfpuncheckedvalue_string()
{
	name = "uncheckedvalue";
	type = T_STRING;

}

cfpuncheckedvalue_string::~cfpuncheckedvalue_string() {};







cfplabelplacement_string::cfplabelplacement_string()
{
	name = "labelplacement";
	type = T_STRING;

}

cfplabelplacement_string::~cfplabelplacement_string() {};




cfpprependtolabel_string::cfpprependtolabel_string()
{
	name = "prependtolabel";
	type = T_STRING;

}

cfpprependtolabel_string::~cfpprependtolabel_string() {};




cfpappendtolabel_string::cfpappendtolabel_string()
{
	name = "appendtolabel";
	type = T_STRING;

}

cfpappendtolabel_string::~cfpappendtolabel_string() {};




cfperrorelement_string::cfperrorelement_string()
{
	name = "errorelement";
	type = T_STRING;

}

cfperrorelement_string::~cfperrorelement_string() {};




cfpchecked_boolean::cfpchecked_boolean()
{
	name = "checked";
	type = T_BOOLEAN;

}

cfpchecked_boolean::~cfpchecked_boolean() {};







cfppartial_any::cfppartial_any()
{
	name = "partial";
	type = T_ANY;

}

cfppartial_any::~cfppartial_any() {};




cfpgroup_string::cfpgroup_string()
{
	name = "group";
	type = T_STRING;

}

cfpgroup_string::~cfpgroup_string() {};




cfpcache_any::cfpcache_any()
{
	name = "cache";
	type = T_ANY;

}

cfpcache_any::~cfpcache_any() {};




cfplayout_string::cfplayout_string()
{
	name = "layout";
	type = T_STRING;

}

cfplayout_string::~cfplayout_string() {};




cfpspacer_string::cfpspacer_string()
{
	name = "spacer";
	type = T_STRING;

}

cfpspacer_string::~cfpspacer_string() {};




cfpproperties_struct::cfpproperties_struct()
{
	name = "properties";
	type = T_STRUCT;

}

cfpproperties_struct::~cfpproperties_struct() {};




cfpdefaults_boolean::cfpdefaults_boolean()
{
	name = "defaults";
	type = T_BOOLEAN;

}

cfpdefaults_boolean::~cfpdefaults_boolean() {};




cfpparameterize_any::cfpparameterize_any()
{
	name = "parameterize";
	type = T_ANY;

}

cfpparameterize_any::~cfpparameterize_any() {};




cfpconfirm_string::cfpconfirm_string()
{
	name = "confirm";
	type = T_STRING;

}

cfpconfirm_string::~cfpconfirm_string() {};




cfproute_string::cfproute_string()
{
	name = "route";
	type = T_STRING;

}

cfproute_string::~cfproute_string() {};




cfpkey_any::cfpkey_any()
{
	name = "key";
	type = T_ANY;

}

cfpkey_any::~cfpkey_any() {};




cfpparams_string::cfpparams_string()
{
	name = "params";
	type = T_STRING;

}

cfpparams_string::~cfpparams_string() {};




cfponlypath_boolean::cfponlypath_boolean()
{
	name = "onlypath";
	type = T_BOOLEAN;

}

cfponlypath_boolean::~cfponlypath_boolean() {};




cfphost_string::cfphost_string()
{
	name = "host";
	type = T_STRING;

}

cfphost_string::~cfphost_string() {};




cfpprotocol_string::cfpprotocol_string()
{
	name = "protocol";
	type = T_STRING;

}

cfpprotocol_string::~cfpprotocol_string() {};




cfpport_numeric::cfpport_numeric()
{
	name = "port";
	type = T_NUMERIC;

}

cfpport_numeric::~cfpport_numeric() {};




cfpdatasource_string::cfpdatasource_string()
{
	name = "datasource";
	type = T_STRING;

}

cfpdatasource_string::~cfpdatasource_string() {};




cfpusername_string::cfpusername_string()
{
	name = "username";
	type = T_STRING;

}

cfpusername_string::~cfpusername_string() {};






cfporder_string::cfporder_string()
{
	name = "order";
	type = T_STRING;

}

cfporder_string::~cfporder_string() {};




cfpseparator_string::cfpseparator_string()
{
	name = "separator";
	type = T_STRING;

}

cfpseparator_string::~cfpseparator_string() {};




cfpstartyear_numeric::cfpstartyear_numeric()
{
	name = "startyear";
	type = T_NUMERIC;

}

cfpstartyear_numeric::~cfpstartyear_numeric() {};




cfpendyear_numeric::cfpendyear_numeric()
{
	name = "endyear";
	type = T_NUMERIC;

}

cfpendyear_numeric::~cfpendyear_numeric() {};




cfpmonthdisplay_string::cfpmonthdisplay_string()
{
	name = "monthdisplay";
	type = T_STRING;

}

cfpmonthdisplay_string::~cfpmonthdisplay_string() {};




cfpincludeblank_any::cfpincludeblank_any()
{
	name = "includeblank";
	type = T_ANY;

}

cfpincludeblank_any::~cfpincludeblank_any() {};




cfpselected_string::cfpselected_string()
{
	name = "selected";
	type = T_STRING;

}

cfpselected_string::~cfpselected_string() {};




cfpobjectname_string::cfpobjectname_string()
{
	name = "objectname";
	type = T_STRING;

}

cfpobjectname_string::~cfpobjectname_string() {};




cfpdateorder_string::cfpdateorder_string()
{
	name = "dateorder";
	type = T_STRING;

}

cfpdateorder_string::~cfpdateorder_string() {};




cfptimeorder_string::cfptimeorder_string()
{
	name = "timeorder";
	type = T_STRING;

}

cfptimeorder_string::~cfptimeorder_string() {};




cfpminutestep_numeric::cfpminutestep_numeric()
{
	name = "minutestep";
	type = T_NUMERIC;

}

cfpminutestep_numeric::~cfpminutestep_numeric() {};




cfpdateseparator_string::cfpdateseparator_string()
{
	name = "dateseparator";
	type = T_STRING;

}

cfpdateseparator_string::~cfpdateseparator_string() {};




cfptimeseparator_string::cfptimeseparator_string()
{
	name = "timeseparator";
	type = T_STRING;

}

cfptimeseparator_string::~cfptimeseparator_string() {};




cfpinstantiate_boolean::cfpinstantiate_boolean()
{
	name = "instantiate";
	type = T_BOOLEAN;

}

cfpinstantiate_boolean::~cfpinstantiate_boolean() {};




cfp$softdeletecheck_boolean::cfp$softdeletecheck_boolean()
{
	name = "$softdeletecheck";
	type = T_BOOLEAN;

}

cfp$softdeletecheck_boolean::~cfp$softdeletecheck_boolean() {};




cfpparam_string::cfpparam_string()
{
	name = "param";
	type = T_STRING;

}

cfpparam_string::~cfpparam_string() {};




cfpshowduplicates_boolean::cfpshowduplicates_boolean()
{
	name = "showduplicates";
	type = T_BOOLEAN;

}

cfpshowduplicates_boolean::~cfpshowduplicates_boolean() {};




cfpprependtext_string::cfpprependtext_string()
{
	name = "prependtext";
	type = T_STRING;

}

cfpprependtext_string::~cfpprependtext_string() {};




cfpappendtext_string::cfpappendtext_string()
{
	name = "appendtext";
	type = T_STRING;

}

cfpappendtext_string::~cfpappendtext_string() {};




cfpwrapperelement_string::cfpwrapperelement_string()
{
	name = "wrapperelement";
	type = T_STRING;

}

cfpwrapperelement_string::~cfpwrapperelement_string() {};




cfpreload_boolean::cfpreload_boolean()
{
	name = "reload";
	type = T_BOOLEAN;

}

cfpreload_boolean::~cfpreload_boolean() {};




cfpthrough_string::cfpthrough_string()
{
	name = "through";
	type = T_STRING;

}

cfpthrough_string::~cfpthrough_string() {};




cfponly_string::cfponly_string()
{
	name = "only";
	type = T_STRING;

}

cfponly_string::~cfponly_string() {};




cfpexcept_string::cfpexcept_string()
{
	name = "except";
	type = T_STRING;

}

cfpexcept_string::~cfpexcept_string() {};




cfpselect_string::cfpselect_string()
{
	name = "select";
	type = T_STRING;

}

cfpselect_string::~cfpselect_string() {};




cfpmaxrows_numeric::cfpmaxrows_numeric()
{
	name = "maxrows";
	type = T_NUMERIC;

}

cfpmaxrows_numeric::~cfpmaxrows_numeric() {};




cfpreturnas_string::cfpreturnas_string()
{
	name = "returnas";
	type = T_STRING;

}

cfpreturnas_string::~cfpreturnas_string() {};








cfpshortcut_string::cfpshortcut_string()
{
	name = "shortcut";
	type = T_STRING;

}

cfpshortcut_string::~cfpshortcut_string() {};







cfpsources_string::cfpsources_string()
{
	name = "sources";
	type = T_STRING;

}

cfpsources_string::~cfpsources_string() {};




cfp$persisted_boolean::cfp$persisted_boolean()
{
	name = "$persisted";
	type = T_BOOLEAN;

}

cfp$persisted_boolean::~cfp$persisted_boolean() {};




cfpparam_any::cfpparam_any()
{
	name = "param";
	type = T_ANY;

}

cfpparam_any::~cfpparam_any() {};




cfpword_string::cfpword_string()
{
	name = "word";
	type = T_STRING;

}

cfpword_string::~cfpword_string() {};






cfpreturncount_boolean::cfpreturncount_boolean()
{
	name = "returncount";
	type = T_BOOLEAN;

}

cfpreturncount_boolean::~cfpreturncount_boolean() {};






cfpsql_string::cfpsql_string()
{
	name = "sql";
	type = T_STRING;

}

cfpsql_string::~cfpsql_string() {};




cfptagvalue_string::cfptagvalue_string()
{
	name = "tagvalue";
	type = T_STRING;

}

cfptagvalue_string::~cfptagvalue_string() {};




cfpback_boolean::cfpback_boolean()
{
	name = "back";
	type = T_BOOLEAN;

}

cfpback_boolean::~cfpback_boolean() {};








cfptemplate_string::cfptemplate_string()
{
	name = "template";
	type = T_STRING;

}

cfptemplate_string::~cfptemplate_string() {};




cfplayout_any::cfplayout_any()
{
	name = "layout";
	type = T_ANY;

}

cfplayout_any::~cfplayout_any() {};




cfp$showdebuginformation_any::cfp$showdebuginformation_any()
{
	name = "$showdebuginformation";
	type = T_ANY;

}

cfp$showdebuginformation_any::~cfp$showdebuginformation_any() {};




cfppartial_string::cfppartial_string()
{
	name = "partial";
	type = T_STRING;

}

cfppartial_string::~cfppartial_string() {};




cfptext_any::cfptext_any()
{
	name = "text";
	type = T_ANY;

}

cfptext_any::~cfptext_any() {};




cfpoptions_any::cfpoptions_any()
{
	name = "options";
	type = T_ANY;

}

cfpoptions_any::~cfpoptions_any() {};




cfpvaluefield_string::cfpvaluefield_string()
{
	name = "valuefield";
	type = T_STRING;

}

cfpvaluefield_string::~cfpvaluefield_string() {};




cfptextfield_string::cfptextfield_string()
{
	name = "textfield";
	type = T_STRING;

}

cfptextfield_string::~cfptextfield_string() {};




cfpmultiple_boolean::cfpmultiple_boolean()
{
	name = "multiple";
	type = T_BOOLEAN;

}

cfpmultiple_boolean::~cfpmultiple_boolean() {};




cfptemplates_string::cfptemplates_string()
{
	name = "templates";
	type = T_STRING;

}

cfptemplates_string::~cfptemplates_string() {};




cfpfrom_string::cfpfrom_string()
{
	name = "from";
	type = T_STRING;

}

cfpfrom_string::~cfpfrom_string() {};




cfpto_string::cfpto_string()
{
	name = "to";
	type = T_STRING;

}

cfpto_string::~cfpto_string() {};




cfpsubject_string::cfpsubject_string()
{
	name = "subject";
	type = T_STRING;

}

cfpsubject_string::~cfpsubject_string() {};




cfplayouts_any::cfplayouts_any()
{
	name = "layouts";
	type = T_ANY;

}

cfplayouts_any::~cfplayouts_any() {};




cfpdetectmultipart_boolean::cfpdetectmultipart_boolean()
{
	name = "detectmultipart";
	type = T_BOOLEAN;

}

cfpdetectmultipart_boolean::~cfpdetectmultipart_boolean() {};








cfpdisposition_string::cfpdisposition_string()
{
	name = "disposition";
	type = T_STRING;

}

cfpdisposition_string::~cfpdisposition_string() {};




cfpmethod_string::cfpmethod_string()
{
	name = "method";
	type = T_STRING;

}

cfpmethod_string::~cfpmethod_string() {};




cfpmultipart_boolean::cfpmultipart_boolean()
{
	name = "multipart";
	type = T_BOOLEAN;

}

cfpmultipart_boolean::~cfpmultipart_boolean() {};




cfpspamprotection_boolean::cfpspamprotection_boolean()
{
	name = "spamprotection";
	type = T_BOOLEAN;

}

cfpspamprotection_boolean::~cfpspamprotection_boolean() {};




cfpmedia_string::cfpmedia_string()
{
	name = "media";
	type = T_STRING;

}

cfpmedia_string::~cfpmedia_string() {};




cfpimage_string::cfpimage_string()
{
	name = "image";
	type = T_STRING;

}

cfpimage_string::~cfpimage_string() {};




cfpdisable_any::cfpdisable_any()
{
	name = "disable";
	type = T_ANY;

}

cfpdisable_any::~cfpdisable_any() {};




cfpcontent_string::cfpcontent_string()
{
	name = "content";
	type = T_STRING;

}

cfpcontent_string::~cfpcontent_string() {};




cfpif_string::cfpif_string()
{
	name = "if";
	type = T_STRING;

}

cfpif_string::~cfpif_string() {};




cfpunless_string::cfpunless_string()
{
	name = "unless";
	type = T_STRING;

}

cfpunless_string::~cfpunless_string() {};




cfpproperties_string::cfpproperties_string()
{
	name = "properties";
	type = T_STRING;

}

cfpproperties_string::~cfpproperties_string() {};




cfpwhen_string::cfpwhen_string()
{
	name = "when";
	type = T_STRING;

}

cfpwhen_string::~cfpwhen_string() {};





cfpallowblank_boolean::cfpallowblank_boolean()
{
	name = "allowblank";
	type = T_BOOLEAN;

}

cfpallowblank_boolean::~cfpallowblank_boolean() {};




cfpregex_string::cfpregex_string()
{
	name = "regex";
	type = T_STRING;

}

cfpregex_string::~cfpregex_string() {};




cfpexactly_numeric::cfpexactly_numeric()
{
	name = "exactly";
	type = T_NUMERIC;

}

cfpexactly_numeric::~cfpexactly_numeric() {};




cfpmaximum_numeric::cfpmaximum_numeric()
{
	name = "maximum";
	type = T_NUMERIC;

}

cfpmaximum_numeric::~cfpmaximum_numeric() {};




cfpminimum_numeric::cfpminimum_numeric()
{
	name = "minimum";
	type = T_NUMERIC;

}

cfpminimum_numeric::~cfpminimum_numeric() {};




cfpwithin_string::cfpwithin_string()
{
	name = "within";
	type = T_STRING;

}

cfpwithin_string::~cfpwithin_string() {};




cfponlyinteger_boolean::cfponlyinteger_boolean()
{
	name = "onlyinteger";
	type = T_BOOLEAN;

}

cfponlyinteger_boolean::~cfponlyinteger_boolean() {};







cfppost_any::cfppost_any()
{
	name = "post";
	type = T_ANY;

}

cfppost_any::~cfppost_any() {};




cfpget_any::cfpget_any()
{
	name = "get";
	type = T_ANY;

}

cfpget_any::~cfpget_any() {};




cfpajax_any::cfpajax_any()
{
	name = "ajax";
	type = T_ANY;

}

cfpajax_any::~cfpajax_any() {};




cfpcookie_string::cfpcookie_string()
{
	name = "cookie";
	type = T_STRING;

}

cfpcookie_string::~cfpcookie_string() {};




cfpsession_string::cfpsession_string()
{
	name = "session";
	type = T_STRING;

}

cfpsession_string::~cfpsession_string() {};




cfphandler_string::cfphandler_string()
{
	name = "handler";
	type = T_STRING;

}

cfphandler_string::~cfphandler_string() {};


#endif


cffunction getfunction( const char * input )
{

	if ( strcmp( input, "abs" ) == 0 ) {
		return cffabs();
	}

	if ( strcmp( input, "acos" ) == 0 ) {
		return cffacos();
	}

	if ( strcmp( input, "addsoaprequestheader" ) == 0 ) {
		return cffaddsoaprequestheader();
	}

	if ( strcmp( input, "addsoapresponseheader" ) == 0 ) {
		return cffaddsoapresponseheader();
	}

	if ( strcmp( input, "ajaxlink" ) == 0 ) {
		return cffajaxlink();
	}

	if ( strcmp( input, "ajaxonload" ) == 0 ) {
		return cffajaxonload();
	}

	if ( strcmp( input, "applicationstop" ) == 0 ) {
		return cffapplicationstop();
	}

	if ( strcmp( input, "arrayappend" ) == 0 ) {
		return cffarrayappend();
	}

	if ( strcmp( input, "arrayavg" ) == 0 ) {
		return cffarrayavg();
	}

	if ( strcmp( input, "arrayclear" ) == 0 ) {
		return cffarrayclear();
	}

	if ( strcmp( input, "arraycontains" ) == 0 ) {
		return cffarraycontains();
	}

	if ( strcmp( input, "arraydelete" ) == 0 ) {
		return cffarraydelete();
	}

	if ( strcmp( input, "arraydeleteat" ) == 0 ) {
		return cffarraydeleteat();
	}

	if ( strcmp( input, "arrayfind" ) == 0 ) {
		return cffarrayfind();
	}

	if ( strcmp( input, "arrayfindnocase" ) == 0 ) {
		return cffarrayfindnocase();
	}

	if ( strcmp( input, "arrayinsertat" ) == 0 ) {
		return cffarrayinsertat();
	}

	if ( strcmp( input, "arrayisdefined" ) == 0 ) {
		return cffarrayisdefined();
	}

	if ( strcmp( input, "arrayisempty" ) == 0 ) {
		return cffarrayisempty();
	}

	if ( strcmp( input, "arraylen" ) == 0 ) {
		return cffarraylen();
	}

	if ( strcmp( input, "arraymax" ) == 0 ) {
		return cffarraymax();
	}

	if ( strcmp( input, "arraymin" ) == 0 ) {
		return cffarraymin();
	}

	if ( strcmp( input, "arraynew" ) == 0 ) {
		return cffarraynew();
	}

	if ( strcmp( input, "arrayprepend" ) == 0 ) {
		return cffarrayprepend();
	}

	if ( strcmp( input, "arrayresize" ) == 0 ) {
		return cffarrayresize();
	}

	if ( strcmp( input, "arrayset" ) == 0 ) {
		return cffarrayset();
	}

	if ( strcmp( input, "arraysort" ) == 0 ) {
		return cffarraysort();
	}

	if ( strcmp( input, "arraysum" ) == 0 ) {
		return cffarraysum();
	}

	if ( strcmp( input, "arrayswap" ) == 0 ) {
		return cffarrayswap();
	}

	if ( strcmp( input, "arraytolist" ) == 0 ) {
		return cffarraytolist();
	}

	if ( strcmp( input, "asc" ) == 0 ) {
		return cffasc();
	}

	if ( strcmp( input, "asin" ) == 0 ) {
		return cffasin();
	}

	if ( strcmp( input, "atn" ) == 0 ) {
		return cffatn();
	}

	if ( strcmp( input, "binarydecode" ) == 0 ) {
		return cffbinarydecode();
	}

	if ( strcmp( input, "binaryencode" ) == 0 ) {
		return cffbinaryencode();
	}

	if ( strcmp( input, "bitand" ) == 0 ) {
		return cffbitand();
	}

	if ( strcmp( input, "bitmaskclear" ) == 0 ) {
		return cffbitmaskclear();
	}

	if ( strcmp( input, "bitmaskread" ) == 0 ) {
		return cffbitmaskread();
	}

	if ( strcmp( input, "bitmaskset" ) == 0 ) {
		return cffbitmaskset();
	}

	if ( strcmp( input, "bitnot" ) == 0 ) {
		return cffbitnot();
	}

	if ( strcmp( input, "bitor" ) == 0 ) {
		return cffbitor();
	}

	if ( strcmp( input, "bitshln" ) == 0 ) {
		return cffbitshln();
	}

	if ( strcmp( input, "bitshrn" ) == 0 ) {
		return cffbitshrn();
	}

	if ( strcmp( input, "bitxor" ) == 0 ) {
		return cffbitxor();
	}

	if ( strcmp( input, "cacheget" ) == 0 ) {
		return cffcacheget();
	}

	if ( strcmp( input, "cachegetallids" ) == 0 ) {
		return cffcachegetallids();
	}

	if ( strcmp( input, "cachegetmetadata" ) == 0 ) {
		return cffcachegetmetadata();
	}

	if ( strcmp( input, "cachegetproperties" ) == 0 ) {
		return cffcachegetproperties();
	}

	if ( strcmp( input, "cacheput" ) == 0 ) {
		return cffcacheput();
	}

	if ( strcmp( input, "cacheremove" ) == 0 ) {
		return cffcacheremove();
	}

	if ( strcmp( input, "cachesetproperties" ) == 0 ) {
		return cffcachesetproperties();
	}

	if ( strcmp( input, "ceiling" ) == 0 ) {
		return cffceiling();
	}

	if ( strcmp( input, "charsetdecode" ) == 0 ) {
		return cffcharsetdecode();
	}

	if ( strcmp( input, "charsetencode" ) == 0 ) {
		return cffcharsetencode();
	}

	if ( strcmp( input, "chr" ) == 0 ) {
		return cffchr();
	}

	if ( strcmp( input, "cjustify" ) == 0 ) {
		return cffcjustify();
	}

	if ( strcmp( input, "compare" ) == 0 ) {
		return cffcompare();
	}

	if ( strcmp( input, "comparenocase" ) == 0 ) {
		return cffcomparenocase();
	}

	if ( strcmp( input, "cos" ) == 0 ) {
		return cffcos();
	}

	if ( strcmp( input, "createdate" ) == 0 ) {
		return cffcreatedate();
	}

	if ( strcmp( input, "createdatetime" ) == 0 ) {
		return cffcreatedatetime();
	}

	if ( strcmp( input, "createobject" ) == 0 ) {
		return cffcreateobject();
	}

	if ( strcmp( input, "createodbcdate" ) == 0 ) {
		return cffcreateodbcdate();
	}

	if ( strcmp( input, "createodbcdatetime" ) == 0 ) {
		return cffcreateodbcdatetime();
	}

	if ( strcmp( input, "createodbctime" ) == 0 ) {
		return cffcreateodbctime();
	}

	if ( strcmp( input, "createtime" ) == 0 ) {
		return cffcreatetime();
	}

	if ( strcmp( input, "createtimespan" ) == 0 ) {
		return cffcreatetimespan();
	}

	if ( strcmp( input, "createuuid" ) == 0 ) {
		return cffcreateuuid();
	}

	if ( strcmp( input, "dateadd" ) == 0 ) {
		return cffdateadd();
	}

	if ( strcmp( input, "datecompare" ) == 0 ) {
		return cffdatecompare();
	}

	if ( strcmp( input, "dateconvert" ) == 0 ) {
		return cffdateconvert();
	}

	if ( strcmp( input, "datediff" ) == 0 ) {
		return cffdatediff();
	}

	if ( strcmp( input, "dateformat" ) == 0 ) {
		return cffdateformat();
	}

	if ( strcmp( input, "datepart" ) == 0 ) {
		return cffdatepart();
	}

	if ( strcmp( input, "day" ) == 0 ) {
		return cffday();
	}

	if ( strcmp( input, "dayofweek" ) == 0 ) {
		return cffdayofweek();
	}

	if ( strcmp( input, "dayofweekasstring" ) == 0 ) {
		return cffdayofweekasstring();
	}

	if ( strcmp( input, "dayofyear" ) == 0 ) {
		return cffdayofyear();
	}

	if ( strcmp( input, "daysinmonth" ) == 0 ) {
		return cffdaysinmonth();
	}

	if ( strcmp( input, "daysinyear" ) == 0 ) {
		return cffdaysinyear();
	}

	if ( strcmp( input, "de" ) == 0 ) {
		return cffde();
	}

	if ( strcmp( input, "decimalformat" ) == 0 ) {
		return cffdecimalformat();
	}

	if ( strcmp( input, "decrementvalue" ) == 0 ) {
		return cffdecrementvalue();
	}

	if ( strcmp( input, "decrypt" ) == 0 ) {
		return cffdecrypt();
	}

	if ( strcmp( input, "decryptbinary" ) == 0 ) {
		return cffdecryptbinary();
	}

	if ( strcmp( input, "deleteclientvariable" ) == 0 ) {
		return cffdeleteclientvariable();
	}

	if ( strcmp( input, "deserializejson" ) == 0 ) {
		return cffdeserializejson();
	}

	if ( strcmp( input, "directorycreate" ) == 0 ) {
		return cffdirectorycreate();
	}

	if ( strcmp( input, "directorydelete" ) == 0 ) {
		return cffdirectorydelete();
	}

	if ( strcmp( input, "directoryexists" ) == 0 ) {
		return cffdirectoryexists();
	}

	if ( strcmp( input, "directorylist" ) == 0 ) {
		return cffdirectorylist();
	}

	if ( strcmp( input, "directoryrename" ) == 0 ) {
		return cffdirectoryrename();
	}


	if ( strcmp( input, "dollarformat" ) == 0 ) {
		return cffdollarformat();
	}

	if ( strcmp( input, "dotnettocftype" ) == 0 ) {
		return cffdotnettocftype();
	}

	if ( strcmp( input, "duplicate" ) == 0 ) {
		return cffduplicate();
	}

	if ( strcmp( input, "encrypt" ) == 0 ) {
		return cffencrypt();
	}

	if ( strcmp( input, "encryptbinary" ) == 0 ) {
		return cffencryptbinary();
	}

	if ( strcmp( input, "entitydelete" ) == 0 ) {
		return cffentitydelete();
	}

	if ( strcmp( input, "entityload" ) == 0 ) {
		return cffentityload();
	}

	if ( strcmp( input, "entityload" ) == 0 ) {
		return cffentityload();
	}

	if ( strcmp( input, "entityloadbyexample" ) == 0 ) {
		return cffentityloadbyexample();
	}

	if ( strcmp( input, "entityloadbypk" ) == 0 ) {
		return cffentityloadbypk();
	}

	if ( strcmp( input, "entitymerge" ) == 0 ) {
		return cffentitymerge();
	}

	if ( strcmp( input, "entitynew" ) == 0 ) {
		return cffentitynew();
	}

	if ( strcmp( input, "entityreload" ) == 0 ) {
		return cffentityreload();
	}

	if ( strcmp( input, "entitysave" ) == 0 ) {
		return cffentitysave();
	}

	if ( strcmp( input, "entitytoquery" ) == 0 ) {
		return cffentitytoquery();
	}

	if ( strcmp( input, "evaluate" ) == 0 ) {
		return cffevaluate();
	}

	if ( strcmp( input, "exp" ) == 0 ) {
		return cffexp();
	}

	if ( strcmp( input, "expandpath" ) == 0 ) {
		return cffexpandpath();
	}

	if ( strcmp( input, "fileclose" ) == 0 ) {
		return cfffileclose();
	}

	if ( strcmp( input, "filecopy" ) == 0 ) {
		return cfffilecopy();
	}

	if ( strcmp( input, "filedelete" ) == 0 ) {
		return cfffiledelete();
	}

	if ( strcmp( input, "fileexists" ) == 0 ) {
		return cfffileexists();
	}

	if ( strcmp( input, "fileiseof" ) == 0 ) {
		return cfffileiseof();
	}

	if ( strcmp( input, "filemove" ) == 0 ) {
		return cfffilemove();
	}

	if ( strcmp( input, "fileopen" ) == 0 ) {
		return cfffileopen();
	}

	if ( strcmp( input, "fileread" ) == 0 ) {
		return cfffileread();
	}

	if ( strcmp( input, "filereadbinary" ) == 0 ) {
		return cfffilereadbinary();
	}

	if ( strcmp( input, "filereadline" ) == 0 ) {
		return cfffilereadline();
	}

	if ( strcmp( input, "fileseek" ) == 0 ) {
		return cfffileseek();
	}

	if ( strcmp( input, "filesetaccessmode" ) == 0 ) {
		return cfffilesetaccessmode();
	}

	if ( strcmp( input, "filesetattribute" ) == 0 ) {
		return cfffilesetattribute();
	}

	if ( strcmp( input, "filesetlastmodified" ) == 0 ) {
		return cfffilesetlastmodified();
	}

	if ( strcmp( input, "fileskipbytes" ) == 0 ) {
		return cfffileskipbytes();
	}

	if ( strcmp( input, "filewrite" ) == 0 ) {
		return cfffilewrite();
	}

	if ( strcmp( input, "filewriteline" ) == 0 ) {
		return cfffilewriteline();
	}

	if ( strcmp( input, "find" ) == 0 ) {
		return cfffind();
	}

	if ( strcmp( input, "findnocase" ) == 0 ) {
		return cfffindnocase();
	}

	if ( strcmp( input, "findoneof" ) == 0 ) {
		return cfffindoneof();
	}

	if ( strcmp( input, "firstdayofmonth" ) == 0 ) {
		return cfffirstdayofmonth();
	}

	if ( strcmp( input, "fix" ) == 0 ) {
		return cfffix();
	}

	if ( strcmp( input, "formatbasen" ) == 0 ) {
		return cffformatbasen();
	}

	if ( strcmp( input, "generatesecretkey" ) == 0 ) {
		return cffgeneratesecretkey();
	}

	if ( strcmp( input, "getauthuser" ) == 0 ) {
		return cffgetauthuser();
	}

	if ( strcmp( input, "getbasetagdata" ) == 0 ) {
		return cffgetbasetagdata();
	}

	if ( strcmp( input, "getbasetaglist" ) == 0 ) {
		return cffgetbasetaglist();
	}

	if ( strcmp( input, "getbasetemplatepath" ) == 0 ) {
		return cffgetbasetemplatepath();
	}

	if ( strcmp( input, "getclientvariableslist" ) == 0 ) {
		return cffgetclientvariableslist();
	}

	if ( strcmp( input, "getcomponentmetadata" ) == 0 ) {
		return cffgetcomponentmetadata();
	}

	if ( strcmp( input, "getcontextroot" ) == 0 ) {
		return cffgetcontextroot();
	}

	if ( strcmp( input, "getcurrenttemplatepath" ) == 0 ) {
		return cffgetcurrenttemplatepath();
	}

	if ( strcmp( input, "getdirectoryfrompath" ) == 0 ) {
		return cffgetdirectoryfrompath();
	}

	if ( strcmp( input, "getencoding" ) == 0 ) {
		return cffgetencoding();
	}

	if ( strcmp( input, "getexception" ) == 0 ) {
		return cffgetexception();
	}

	if ( strcmp( input, "getfilefrompath" ) == 0 ) {
		return cffgetfilefrompath();
	}

	if ( strcmp( input, "getfileinfo" ) == 0 ) {
		return cffgetfileinfo();
	}

	if ( strcmp( input, "getfunctionlist" ) == 0 ) {
		return cffgetfunctionlist();
	}

	if ( strcmp( input, "getgatewayhelper" ) == 0 ) {
		return cffgetgatewayhelper();
	}

	if ( strcmp( input, "gethttprequestdata" ) == 0 ) {
		return cffgethttprequestdata();
	}

	if ( strcmp( input, "gethttptimestring" ) == 0 ) {
		return cffgethttptimestring();
	}

	if ( strcmp( input, "getlocale" ) == 0 ) {
		return cffgetlocale();
	}

	if ( strcmp( input, "getlocaledisplayname" ) == 0 ) {
		return cffgetlocaledisplayname();
	}

	if ( strcmp( input, "getlocalhostip" ) == 0 ) {
		return cffgetlocalhostip();
	}

	if ( strcmp( input, "getmetadata" ) == 0 ) {
		return cffgetmetadata();
	}

	if ( strcmp( input, "getmetricdata" ) == 0 ) {
		return cffgetmetricdata();
	}

	if ( strcmp( input, "getpagecontext" ) == 0 ) {
		return cffgetpagecontext();
	}

	if ( strcmp( input, "getprinterinfo" ) == 0 ) {
		return cffgetprinterinfo();
	}

	if ( strcmp( input, "getprinterlist" ) == 0 ) {
		return cffgetprinterlist();
	}

	if ( strcmp( input, "getprofilesections" ) == 0 ) {
		return cffgetprofilesections();
	}

	if ( strcmp( input, "getprofilestring" ) == 0 ) {
		return cffgetprofilestring();
	}

	if ( strcmp( input, "getreadableimageformats" ) == 0 ) {
		return cffgetreadableimageformats();
	}

	if ( strcmp( input, "getsoaprequest" ) == 0 ) {
		return cffgetsoaprequest();
	}

	if ( strcmp( input, "getsoaprequestheader" ) == 0 ) {
		return cffgetsoaprequestheader();
	}

	if ( strcmp( input, "getsoapresponse" ) == 0 ) {
		return cffgetsoapresponse();
	}

	if ( strcmp( input, "getsoapresponseheader" ) == 0 ) {
		return cffgetsoapresponseheader();
	}

	if ( strcmp( input, "gettempdirectory" ) == 0 ) {
		return cffgettempdirectory();
	}

	if ( strcmp( input, "gettempfile" ) == 0 ) {
		return cffgettempfile();
	}

	if ( strcmp( input, "gettickcount" ) == 0 ) {
		return cffgettickcount();
	}

	if ( strcmp( input, "gettimezoneinfo" ) == 0 ) {
		return cffgettimezoneinfo();
	}

	if ( strcmp( input, "gettoken" ) == 0 ) {
		return cffgettoken();
	}

	if ( strcmp( input, "getuserroles" ) == 0 ) {
		return cffgetuserroles();
	}

	if ( strcmp( input, "getvfsmetadata" ) == 0 ) {
		return cffgetvfsmetadata();
	}

	if ( strcmp( input, "getwriteableimageformats" ) == 0 ) {
		return cffgetwriteableimageformats();
	}

	if ( strcmp( input, "hash" ) == 0 ) {
		return cffhash();
	}

	if ( strcmp( input, "hour" ) == 0 ) {
		return cffhour();
	}

	if ( strcmp( input, "htmlcodeformat" ) == 0 ) {
		return cffhtmlcodeformat();
	}

	if ( strcmp( input, "htmleditformat" ) == 0 ) {
		return cffhtmleditformat();
	}

	if ( strcmp( input, "iif" ) == 0 ) {
		return cffiif();
	}

	if ( strcmp( input, "imageaddborder" ) == 0 ) {
		return cffimageaddborder();
	}

	if ( strcmp( input, "imageblur" ) == 0 ) {
		return cffimageblur();
	}

	if ( strcmp( input, "imageclearrect" ) == 0 ) {
		return cffimageclearrect();
	}

	if ( strcmp( input, "imagecopy" ) == 0 ) {
		return cffimagecopy();
	}

	if ( strcmp( input, "imagecrop" ) == 0 ) {
		return cffimagecrop();
	}

	if ( strcmp( input, "imagedrawarc" ) == 0 ) {
		return cffimagedrawarc();
	}

	if ( strcmp( input, "imagedrawbeveledrect" ) == 0 ) {
		return cffimagedrawbeveledrect();
	}

	if ( strcmp( input, "imagedrawcubiccurve" ) == 0 ) {
		return cffimagedrawcubiccurve();
	}

	if ( strcmp( input, "imagedrawline" ) == 0 ) {
		return cffimagedrawline();
	}

	if ( strcmp( input, "imagedrawlines" ) == 0 ) {
		return cffimagedrawlines();
	}

	if ( strcmp( input, "imagedrawoval" ) == 0 ) {
		return cffimagedrawoval();
	}

	if ( strcmp( input, "imagedrawpoint" ) == 0 ) {
		return cffimagedrawpoint();
	}

	if ( strcmp( input, "imagedrawquadraticcurve" ) == 0 ) {
		return cffimagedrawquadraticcurve();
	}

	if ( strcmp( input, "imagedrawrect" ) == 0 ) {
		return cffimagedrawrect();
	}

	if ( strcmp( input, "imagedrawroundrect" ) == 0 ) {
		return cffimagedrawroundrect();
	}

	if ( strcmp( input, "imagedrawtext" ) == 0 ) {
		return cffimagedrawtext();
	}

	if ( strcmp( input, "imageflip" ) == 0 ) {
		return cffimageflip();
	}

	if ( strcmp( input, "imagegetblob" ) == 0 ) {
		return cffimagegetblob();
	}

	if ( strcmp( input, "imagegetbufferedimage" ) == 0 ) {
		return cffimagegetbufferedimage();
	}

	if ( strcmp( input, "imagegetexifmetadata" ) == 0 ) {
		return cffimagegetexifmetadata();
	}

	if ( strcmp( input, "imagegetexiftag" ) == 0 ) {
		return cffimagegetexiftag();
	}

	if ( strcmp( input, "imagegetheight" ) == 0 ) {
		return cffimagegetheight();
	}

	if ( strcmp( input, "imagegetiptcmetadata" ) == 0 ) {
		return cffimagegetiptcmetadata();
	}

	if ( strcmp( input, "imagegetiptctag" ) == 0 ) {
		return cffimagegetiptctag();
	}

	if ( strcmp( input, "imagegetwidth" ) == 0 ) {
		return cffimagegetwidth();
	}

	if ( strcmp( input, "imagegrayscale" ) == 0 ) {
		return cffimagegrayscale();
	}

	if ( strcmp( input, "imageinfo" ) == 0 ) {
		return cffimageinfo();
	}

	if ( strcmp( input, "imagenegative" ) == 0 ) {
		return cffimagenegative();
	}

	if ( strcmp( input, "imagenew" ) == 0 ) {
		return cffimagenew();
	}

	if ( strcmp( input, "imageoverlay" ) == 0 ) {
		return cffimageoverlay();
	}

	if ( strcmp( input, "imagepaste" ) == 0 ) {
		return cffimagepaste();
	}

	if ( strcmp( input, "imageread" ) == 0 ) {
		return cffimageread();
	}

	if ( strcmp( input, "imagereadbase64" ) == 0 ) {
		return cffimagereadbase64();
	}

	if ( strcmp( input, "imageresize" ) == 0 ) {
		return cffimageresize();
	}

	if ( strcmp( input, "imagerotate" ) == 0 ) {
		return cffimagerotate();
	}

	if ( strcmp( input, "imagerotatedrawingaxis" ) == 0 ) {
		return cffimagerotatedrawingaxis();
	}

	if ( strcmp( input, "imagescaletofit" ) == 0 ) {
		return cffimagescaletofit();
	}

	if ( strcmp( input, "imagesetantialiasing" ) == 0 ) {
		return cffimagesetantialiasing();
	}

	if ( strcmp( input, "imagesetbackgroundcolor" ) == 0 ) {
		return cffimagesetbackgroundcolor();
	}

	if ( strcmp( input, "imagesetdrawingcolor" ) == 0 ) {
		return cffimagesetdrawingcolor();
	}

	if ( strcmp( input, "imagesetdrawingstroke" ) == 0 ) {
		return cffimagesetdrawingstroke();
	}

	if ( strcmp( input, "imagesetdrawingtransparency" ) == 0 ) {
		return cffimagesetdrawingtransparency();
	}

	if ( strcmp( input, "imagesharpen" ) == 0 ) {
		return cffimagesharpen();
	}

	if ( strcmp( input, "imageshear" ) == 0 ) {
		return cffimageshear();
	}

	if ( strcmp( input, "imagesheardrawingaxis" ) == 0 ) {
		return cffimagesheardrawingaxis();
	}

	if ( strcmp( input, "imagetranslate" ) == 0 ) {
		return cffimagetranslate();
	}

	if ( strcmp( input, "imagetranslatedrawingaxis" ) == 0 ) {
		return cffimagetranslatedrawingaxis();
	}

	if ( strcmp( input, "imagewrite" ) == 0 ) {
		return cffimagewrite();
	}

	if ( strcmp( input, "imagewritebase64" ) == 0 ) {
		return cffimagewritebase64();
	}

	if ( strcmp( input, "imagexordrawingmode" ) == 0 ) {
		return cffimagexordrawingmode();
	}

	if ( strcmp( input, "incrementvalue" ) == 0 ) {
		return cffincrementvalue();
	}

	if ( strcmp( input, "inputbasen" ) == 0 ) {
		return cffinputbasen();
	}

	if ( strcmp( input, "insert" ) == 0 ) {
		return cffinsert();
	}

	if ( strcmp( input, "int" ) == 0 ) {
		return cffint();
	}

	if ( strcmp( input, "isarray" ) == 0 ) {
		return cffisarray();
	}

	if ( strcmp( input, "isbinary" ) == 0 ) {
		return cffisbinary();
	}

	if ( strcmp( input, "isboolean" ) == 0 ) {
		return cffisboolean();
	}

	if ( strcmp( input, "iscustomfunction" ) == 0 ) {
		return cffiscustomfunction();
	}

	if ( strcmp( input, "isdate" ) == 0 ) {
		return cffisdate();
	}

	if ( strcmp( input, "isddx" ) == 0 ) {
		return cffisddx();
	}

	if ( strcmp( input, "isdebugmode" ) == 0 ) {
		return cffisdebugmode();
	}

	if ( strcmp( input, "isdefined" ) == 0 ) {
		return cffisdefined();
	}

	if ( strcmp( input, "isimage" ) == 0 ) {
		return cffisimage();
	}

	if ( strcmp( input, "isimagefile" ) == 0 ) {
		return cffisimagefile();
	}

	if ( strcmp( input, "isinstanceof" ) == 0 ) {
		return cffisinstanceof();
	}

	if ( strcmp( input, "isipv6" ) == 0 ) {
		return cffisipv6();
	}

	if ( strcmp( input, "isjson" ) == 0 ) {
		return cffisjson();
	}

	if ( strcmp( input, "isleapyear" ) == 0 ) {
		return cffisleapyear();
	}

	if ( strcmp( input, "islocalhost" ) == 0 ) {
		return cffislocalhost();
	}

	if ( strcmp( input, "isnull" ) == 0 ) {
		return cffisnull();
	}

	if ( strcmp( input, "isnumeric" ) == 0 ) {
		return cffisnumeric();
	}

	if ( strcmp( input, "isnumericdate" ) == 0 ) {
		return cffisnumericdate();
	}

	if ( strcmp( input, "isobject" ) == 0 ) {
		return cffisobject();
	}

	if ( strcmp( input, "ispdffile" ) == 0 ) {
		return cffispdffile();
	}

	if ( strcmp( input, "ispdfobject" ) == 0 ) {
		return cffispdfobject();
	}

	if ( strcmp( input, "isquery" ) == 0 ) {
		return cffisquery();
	}

	if ( strcmp( input, "issimplevalue" ) == 0 ) {
		return cffissimplevalue();
	}

	if ( strcmp( input, "issoaprequest" ) == 0 ) {
		return cffissoaprequest();
	}

	if ( strcmp( input, "isspreadsheetfile" ) == 0 ) {
		return cffisspreadsheetfile();
	}

	if ( strcmp( input, "isspreadsheetobject" ) == 0 ) {
		return cffisspreadsheetobject();
	}

	if ( strcmp( input, "isstruct" ) == 0 ) {
		return cffisstruct();
	}

	if ( strcmp( input, "isuserinanyrole" ) == 0 ) {
		return cffisuserinanyrole();
	}

	if ( strcmp( input, "isuserinrole" ) == 0 ) {
		return cffisuserinrole();
	}

	if ( strcmp( input, "isuserloggedin" ) == 0 ) {
		return cffisuserloggedin();
	}

	if ( strcmp( input, "isvalid" ) == 0 ) {
		return cffisvalid();
	}

	if ( strcmp( input, "iswddx" ) == 0 ) {
		return cffiswddx();
	}

	if ( strcmp( input, "isxml" ) == 0 ) {
		return cffisxml();
	}

	if ( strcmp( input, "isxmlattribute" ) == 0 ) {
		return cffisxmlattribute();
	}

	if ( strcmp( input, "isxmldoc" ) == 0 ) {
		return cffisxmldoc();
	}

	if ( strcmp( input, "isxmlelem" ) == 0 ) {
		return cffisxmlelem();
	}

	if ( strcmp( input, "isxmlnode" ) == 0 ) {
		return cffisxmlnode();
	}

	if ( strcmp( input, "isxmlroot" ) == 0 ) {
		return cffisxmlroot();
	}

	if ( strcmp( input, "javacast" ) == 0 ) {
		return cffjavacast();
	}

	if ( strcmp( input, "jsstringformat" ) == 0 ) {
		return cffjsstringformat();
	}

	if ( strcmp( input, "lcase" ) == 0 ) {
		return cfflcase();
	}

	if ( strcmp( input, "left" ) == 0 ) {
		return cffleft();
	}

	if ( strcmp( input, "len" ) == 0 ) {
		return cfflen();
	}

	if ( strcmp( input, "listappend" ) == 0 ) {
		return cfflistappend();
	}

	if ( strcmp( input, "listchangedelims" ) == 0 ) {
		return cfflistchangedelims();
	}

	if ( strcmp( input, "listcontains" ) == 0 ) {
		return cfflistcontains();
	}

	if ( strcmp( input, "listcontainsnocase" ) == 0 ) {
		return cfflistcontainsnocase();
	}

	if ( strcmp( input, "listdeleteat" ) == 0 ) {
		return cfflistdeleteat();
	}

	if ( strcmp( input, "listfind" ) == 0 ) {
		return cfflistfind();
	}

	if ( strcmp( input, "listfindnocase" ) == 0 ) {
		return cfflistfindnocase();
	}

	if ( strcmp( input, "listfirst" ) == 0 ) {
		return cfflistfirst();
	}

	if ( strcmp( input, "listgetat" ) == 0 ) {
		return cfflistgetat();
	}

	if ( strcmp( input, "listinsertat" ) == 0 ) {
		return cfflistinsertat();
	}

	if ( strcmp( input, "listlast" ) == 0 ) {
		return cfflistlast();
	}

	if ( strcmp( input, "listlen" ) == 0 ) {
		return cfflistlen();
	}

	if ( strcmp( input, "listprepend" ) == 0 ) {
		return cfflistprepend();
	}

	if ( strcmp( input, "listqualify" ) == 0 ) {
		return cfflistqualify();
	}

	if ( strcmp( input, "listrest" ) == 0 ) {
		return cfflistrest();
	}

	if ( strcmp( input, "listsetat" ) == 0 ) {
		return cfflistsetat();
	}

	if ( strcmp( input, "listsort" ) == 0 ) {
		return cfflistsort();
	}

	if ( strcmp( input, "listtoarray" ) == 0 ) {
		return cfflisttoarray();
	}

	if ( strcmp( input, "listvaluecount" ) == 0 ) {
		return cfflistvaluecount();
	}

	if ( strcmp( input, "listvaluecountnocase" ) == 0 ) {
		return cfflistvaluecountnocase();
	}

	if ( strcmp( input, "ljustify" ) == 0 ) {
		return cffljustify();
	}

	if ( strcmp( input, "location" ) == 0 ) {
		return cfflocation();
	}

	if ( strcmp( input, "log" ) == 0 ) {
		return cfflog();
	}

	if ( strcmp( input, "log10" ) == 0 ) {
		return cfflog10();
	}

	if ( strcmp( input, "lscurrencyformat" ) == 0 ) {
		return cfflscurrencyformat();
	}

	if ( strcmp( input, "lsdateformat" ) == 0 ) {
		return cfflsdateformat();
	}

	if ( strcmp( input, "lseurocurrencyformat" ) == 0 ) {
		return cfflseurocurrencyformat();
	}

	if ( strcmp( input, "lsiscurrency" ) == 0 ) {
		return cfflsiscurrency();
	}

	if ( strcmp( input, "lsisdate" ) == 0 ) {
		return cfflsisdate();
	}

	if ( strcmp( input, "lsisnumeric" ) == 0 ) {
		return cfflsisnumeric();
	}

	if ( strcmp( input, "lsnumberformat" ) == 0 ) {
		return cfflsnumberformat();
	}

	if ( strcmp( input, "lsparsecurrency" ) == 0 ) {
		return cfflsparsecurrency();
	}

	if ( strcmp( input, "lsparsedatetime" ) == 0 ) {
		return cfflsparsedatetime();
	}

	if ( strcmp( input, "lsparseeurocurrency" ) == 0 ) {
		return cfflsparseeurocurrency();
	}

	if ( strcmp( input, "lsparsenumber" ) == 0 ) {
		return cfflsparsenumber();
	}

	if ( strcmp( input, "lstimeformat" ) == 0 ) {
		return cfflstimeformat();
	}

	if ( strcmp( input, "ltrim" ) == 0 ) {
		return cffltrim();
	}

	if ( strcmp( input, "max" ) == 0 ) {
		return cffmax();
	}

	if ( strcmp( input, "mid" ) == 0 ) {
		return cffmid();
	}

	if ( strcmp( input, "min" ) == 0 ) {
		return cffmin();
	}

	if ( strcmp( input, "minute" ) == 0 ) {
		return cffminute();
	}

	if ( strcmp( input, "month" ) == 0 ) {
		return cffmonth();
	}

	if ( strcmp( input, "monthasstring" ) == 0 ) {
		return cffmonthasstring();
	}

	if ( strcmp( input, "now" ) == 0 ) {
		return cffnow();
	}

	if ( strcmp( input, "numberformat" ) == 0 ) {
		return cffnumberformat();
	}

	if ( strcmp( input, "objectequals" ) == 0 ) {
		return cffobjectequals();
	}

	if ( strcmp( input, "objectload" ) == 0 ) {
		return cffobjectload();
	}

	if ( strcmp( input, "objectload" ) == 0 ) {
		return cffobjectload();
	}

	if ( strcmp( input, "objectsave" ) == 0 ) {
		return cffobjectsave();
	}

	if ( strcmp( input, "ormclearsession" ) == 0 ) {
		return cfformclearsession();
	}

	if ( strcmp( input, "ormclosesession" ) == 0 ) {
		return cfformclosesession();
	}

	if ( strcmp( input, "ormevictcollection" ) == 0 ) {
		return cfformevictcollection();
	}

	if ( strcmp( input, "ormevictentity" ) == 0 ) {
		return cfformevictentity();
	}

	if ( strcmp( input, "ormevictqueries" ) == 0 ) {
		return cfformevictqueries();
	}

	if ( strcmp( input, "ormexecutequery" ) == 0 ) {
		return cfformexecutequery();
	}

	if ( strcmp( input, "ormflush" ) == 0 ) {
		return cfformflush();
	}

	if ( strcmp( input, "ormgetsession" ) == 0 ) {
		return cfformgetsession();
	}

	if ( strcmp( input, "ormgetsessionfactory" ) == 0 ) {
		return cfformgetsessionfactory();
	}

	if ( strcmp( input, "ormreload" ) == 0 ) {
		return cfformreload();
	}

	if ( strcmp( input, "paragraphformat" ) == 0 ) {
		return cffparagraphformat();
	}

	if ( strcmp( input, "parsedatetime" ) == 0 ) {
		return cffparsedatetime();
	}

	if ( strcmp( input, "pi" ) == 0 ) {
		return cffpi();
	}

	if ( strcmp( input, "precisionevaluate" ) == 0 ) {
		return cffprecisionevaluate();
	}

	if ( strcmp( input, "preservesinglequotes" ) == 0 ) {
		return cffpreservesinglequotes();
	}

	if ( strcmp( input, "quarter" ) == 0 ) {
		return cffquarter();
	}

	if ( strcmp( input, "queryaddcolumn" ) == 0 ) {
		return cffqueryaddcolumn();
	}

	if ( strcmp( input, "queryaddrow" ) == 0 ) {
		return cffqueryaddrow();
	}

	if ( strcmp( input, "queryconvertforgrid" ) == 0 ) {
		return cffqueryconvertforgrid();
	}

	if ( strcmp( input, "querynew" ) == 0 ) {
		return cffquerynew();
	}

	if ( strcmp( input, "querysetcell" ) == 0 ) {
		return cffquerysetcell();
	}

	if ( strcmp( input, "quotedvaluelist" ) == 0 ) {
		return cffquotedvaluelist();
	}

	if ( strcmp( input, "rand" ) == 0 ) {
		return cffrand();
	}

	if ( strcmp( input, "randomize" ) == 0 ) {
		return cffrandomize();
	}

	if ( strcmp( input, "randrange" ) == 0 ) {
		return cffrandrange();
	}

	if ( strcmp( input, "refind" ) == 0 ) {
		return cffrefind();
	}

	if ( strcmp( input, "refindnocase" ) == 0 ) {
		return cffrefindnocase();
	}

	if ( strcmp( input, "releasecomobject" ) == 0 ) {
		return cffreleasecomobject();
	}

	if ( strcmp( input, "rematch" ) == 0 ) {
		return cffrematch();
	}

	if ( strcmp( input, "rematchnocase" ) == 0 ) {
		return cffrematchnocase();
	}

	if ( strcmp( input, "removechars" ) == 0 ) {
		return cffremovechars();
	}

	if ( strcmp( input, "repeatstring" ) == 0 ) {
		return cffrepeatstring();
	}

	if ( strcmp( input, "replace" ) == 0 ) {
		return cffreplace();
	}

	if ( strcmp( input, "replacelist" ) == 0 ) {
		return cffreplacelist();
	}

	if ( strcmp( input, "replacenocase" ) == 0 ) {
		return cffreplacenocase();
	}

	if ( strcmp( input, "rereplace" ) == 0 ) {
		return cffrereplace();
	}

	if ( strcmp( input, "rereplacenocase" ) == 0 ) {
		return cffrereplacenocase();
	}

	if ( strcmp( input, "reverse" ) == 0 ) {
		return cffreverse();
	}

	if ( strcmp( input, "right" ) == 0 ) {
		return cffright();
	}

	if ( strcmp( input, "rjustify" ) == 0 ) {
		return cffrjustify();
	}

	if ( strcmp( input, "round" ) == 0 ) {
		return cffround();
	}

	if ( strcmp( input, "rtrim" ) == 0 ) {
		return cffrtrim();
	}

	if ( strcmp( input, "second" ) == 0 ) {
		return cffsecond();
	}

	if ( strcmp( input, "sendgatewaymessage" ) == 0 ) {
		return cffsendgatewaymessage();
	}

	if ( strcmp( input, "serializejson" ) == 0 ) {
		return cffserializejson();
	}

	if ( strcmp( input, "setencoding" ) == 0 ) {
		return cffsetencoding();
	}

	if ( strcmp( input, "setlocale" ) == 0 ) {
		return cffsetlocale();
	}

	if ( strcmp( input, "setprofilestring" ) == 0 ) {
		return cffsetprofilestring();
	}

	if ( strcmp( input, "setvariable" ) == 0 ) {
		return cffsetvariable();
	}

	if ( strcmp( input, "sgn" ) == 0 ) {
		return cffsgn();
	}

	if ( strcmp( input, "sin" ) == 0 ) {
		return cffsin();
	}

	if ( strcmp( input, "sleep" ) == 0 ) {
		return cffsleep();
	}

	if ( strcmp( input, "spanexcluding" ) == 0 ) {
		return cffspanexcluding();
	}

	if ( strcmp( input, "spanincluding" ) == 0 ) {
		return cffspanincluding();
	}

	if ( strcmp( input, "spreadsheetaddcolumn" ) == 0 ) {
		return cffspreadsheetaddcolumn();
	}

	if ( strcmp( input, "spreadsheetaddfreezepane" ) == 0 ) {
		return cffspreadsheetaddfreezepane();
	}

	if ( strcmp( input, "spreadsheetaddimage" ) == 0 ) {
		return cffspreadsheetaddimage();
	}

	if ( strcmp( input, "spreadsheetaddimage" ) == 0 ) {
		return cffspreadsheetaddimage();
	}

	if ( strcmp( input, "spreadsheetaddinfo" ) == 0 ) {
		return cffspreadsheetaddinfo();
	}

	if ( strcmp( input, "spreadsheetaddrow" ) == 0 ) {
		return cffspreadsheetaddrow();
	}

	if ( strcmp( input, "spreadsheetaddrows" ) == 0 ) {
		return cffspreadsheetaddrows();
	}

	if ( strcmp( input, "spreadsheetaddsplitpane" ) == 0 ) {
		return cffspreadsheetaddsplitpane();
	}

	if ( strcmp( input, "spreadsheetcreatesheet" ) == 0 ) {
		return cffspreadsheetcreatesheet();
	}

	if ( strcmp( input, "spreadsheetdeletecolumn" ) == 0 ) {
		return cffspreadsheetdeletecolumn();
	}

	if ( strcmp( input, "spreadsheetdeletecolumns" ) == 0 ) {
		return cffspreadsheetdeletecolumns();
	}

	if ( strcmp( input, "spreadsheetdeleterow" ) == 0 ) {
		return cffspreadsheetdeleterow();
	}

	if ( strcmp( input, "spreadsheetdeleterows" ) == 0 ) {
		return cffspreadsheetdeleterows();
	}

	if ( strcmp( input, "spreadsheetformatcell" ) == 0 ) {
		return cffspreadsheetformatcell();
	}

	if ( strcmp( input, "spreadsheetformatcolumn" ) == 0 ) {
		return cffspreadsheetformatcolumn();
	}

	if ( strcmp( input, "spreadsheetformatcolumns" ) == 0 ) {
		return cffspreadsheetformatcolumns();
	}

	if ( strcmp( input, "spreadsheetformatrow" ) == 0 ) {
		return cffspreadsheetformatrow();
	}

	if ( strcmp( input, "spreadsheetformatrows" ) == 0 ) {
		return cffspreadsheetformatrows();
	}

	if ( strcmp( input, "spreadsheetgetcellcomment" ) == 0 ) {
		return cffspreadsheetgetcellcomment();
	}

	if ( strcmp( input, "spreadsheetgetcellformula" ) == 0 ) {
		return cffspreadsheetgetcellformula();
	}

	if ( strcmp( input, "spreadsheetgetcellvalue" ) == 0 ) {
		return cffspreadsheetgetcellvalue();
	}

	if ( strcmp( input, "spreadsheetinfo" ) == 0 ) {
		return cffspreadsheetinfo();
	}

	if ( strcmp( input, "spreadsheetmergecells" ) == 0 ) {
		return cffspreadsheetmergecells();
	}

	if ( strcmp( input, "spreadsheetnew" ) == 0 ) {
		return cffspreadsheetnew();
	}

	if ( strcmp( input, "spreadsheetread" ) == 0 ) {
		return cffspreadsheetread();
	}

	if ( strcmp( input, "spreadsheetreadbinary" ) == 0 ) {
		return cffspreadsheetreadbinary();
	}

	if ( strcmp( input, "spreadsheetsetactivesheet" ) == 0 ) {
		return cffspreadsheetsetactivesheet();
	}

	if ( strcmp( input, "spreadsheetsetactivesheetnumber" ) == 0 ) {
		return cffspreadsheetsetactivesheetnumber();
	}

	if ( strcmp( input, "spreadsheetsetcellcomment" ) == 0 ) {
		return cffspreadsheetsetcellcomment();
	}

	if ( strcmp( input, "spreadsheetsetcellformula" ) == 0 ) {
		return cffspreadsheetsetcellformula();
	}

	if ( strcmp( input, "spreadsheetsetcellvalue" ) == 0 ) {
		return cffspreadsheetsetcellvalue();
	}

	if ( strcmp( input, "spreadsheetsetcolumnwidth" ) == 0 ) {
		return cffspreadsheetsetcolumnwidth();
	}

	if ( strcmp( input, "spreadsheetsetfooter" ) == 0 ) {
		return cffspreadsheetsetfooter();
	}

	if ( strcmp( input, "spreadsheetsetheader" ) == 0 ) {
		return cffspreadsheetsetheader();
	}

	if ( strcmp( input, "spreadsheetsetrowheight" ) == 0 ) {
		return cffspreadsheetsetrowheight();
	}

	if ( strcmp( input, "spreadsheetshiftcolumns" ) == 0 ) {
		return cffspreadsheetshiftcolumns();
	}

	if ( strcmp( input, "spreadsheetshiftrows" ) == 0 ) {
		return cffspreadsheetshiftrows();
	}

	if ( strcmp( input, "spreadsheetwrite" ) == 0 ) {
		return cffspreadsheetwrite();
	}

	if ( strcmp( input, "sqr" ) == 0 ) {
		return cffsqr();
	}

	if ( strcmp( input, "stripcr" ) == 0 ) {
		return cffstripcr();
	}

	if ( strcmp( input, "structappend" ) == 0 ) {
		return cffstructappend();
	}

	if ( strcmp( input, "structclear" ) == 0 ) {
		return cffstructclear();
	}

	if ( strcmp( input, "structcopy" ) == 0 ) {
		return cffstructcopy();
	}

	if ( strcmp( input, "structcount" ) == 0 ) {
		return cffstructcount();
	}

	if ( strcmp( input, "structdelete" ) == 0 ) {
		return cffstructdelete();
	}

	if ( strcmp( input, "structfind" ) == 0 ) {
		return cffstructfind();
	}

	if ( strcmp( input, "structfindkey" ) == 0 ) {
		return cffstructfindkey();
	}

	if ( strcmp( input, "structfindvalue" ) == 0 ) {
		return cffstructfindvalue();
	}

	if ( strcmp( input, "structget" ) == 0 ) {
		return cffstructget();
	}

	if ( strcmp( input, "structinsert" ) == 0 ) {
		return cffstructinsert();
	}

	if ( strcmp( input, "structisempty" ) == 0 ) {
		return cffstructisempty();
	}

	if ( strcmp( input, "structkeyarray" ) == 0 ) {
		return cffstructkeyarray();
	}

	if ( strcmp( input, "structkeyexists" ) == 0 ) {
		return cffstructkeyexists();
	}

	if ( strcmp( input, "structkeylist" ) == 0 ) {
		return cffstructkeylist();
	}

	if ( strcmp( input, "structnew" ) == 0 ) {
		return cffstructnew();
	}

	if ( strcmp( input, "structsort" ) == 0 ) {
		return cffstructsort();
	}

	if ( strcmp( input, "structupdate" ) == 0 ) {
		return cffstructupdate();
	}

	if ( strcmp( input, "tan" ) == 0 ) {
		return cfftan();
	}

	if ( strcmp( input, "threadjoin" ) == 0 ) {
		return cffthreadjoin();
	}

	if ( strcmp( input, "threadterminate" ) == 0 ) {
		return cffthreadterminate();
	}

	if ( strcmp( input, "throw" ) == 0 ) {
		return cffthrow();
	}

	if ( strcmp( input, "timeformat" ) == 0 ) {
		return cfftimeformat();
	}

	if ( strcmp( input, "tobase64" ) == 0 ) {
		return cfftobase64();
	}

	if ( strcmp( input, "tobinary" ) == 0 ) {
		return cfftobinary();
	}

	if ( strcmp( input, "toscript" ) == 0 ) {
		return cfftoscript();
	}

	if ( strcmp( input, "tostring" ) == 0 ) {
		return cfftostring();
	}

	if ( strcmp( input, "trace" ) == 0 ) {
		return cfftrace();
	}

	if ( strcmp( input, "transactioncommit" ) == 0 ) {
		return cfftransactioncommit();
	}

	if ( strcmp( input, "transactionrollback" ) == 0 ) {
		return cfftransactionrollback();
	}

	if ( strcmp( input, "transactionsetsavepoint" ) == 0 ) {
		return cfftransactionsetsavepoint();
	}

	if ( strcmp( input, "trim" ) == 0 ) {
		return cfftrim();
	}

	if ( strcmp( input, "ucase" ) == 0 ) {
		return cffucase();
	}

	if ( strcmp( input, "urldecode" ) == 0 ) {
		return cffurldecode();
	}

	if ( strcmp( input, "urlencodedformat" ) == 0 ) {
		return cffurlencodedformat();
	}

	if ( strcmp( input, "urlsessionformat" ) == 0 ) {
		return cffurlsessionformat();
	}

	if ( strcmp( input, "val" ) == 0 ) {
		return cffval();
	}

	if ( strcmp( input, "valuelist" ) == 0 ) {
		return cffvaluelist();
	}

	if ( strcmp( input, "verifyclient" ) == 0 ) {
		return cffverifyclient();
	}

	if ( strcmp( input, "week" ) == 0 ) {
		return cffweek();
	}

	if ( strcmp( input, "wrap" ) == 0 ) {
		return cffwrap();
	}

	if ( strcmp( input, "writedump" ) == 0 ) {
		return cffwritedump();
	}

	if ( strcmp( input, "writelog" ) == 0 ) {
		return cffwritelog();
	}

	if ( strcmp( input, "writeoutput" ) == 0 ) {
		return cffwriteoutput();
	}

	if ( strcmp( input, "xmlchildpos" ) == 0 ) {
		return cffxmlchildpos();
	}

	if ( strcmp( input, "xmlelemnew" ) == 0 ) {
		return cffxmlelemnew();
	}

	if ( strcmp( input, "xmlformat" ) == 0 ) {
		return cffxmlformat();
	}

	if ( strcmp( input, "xmlgetnodetype" ) == 0 ) {
		return cffxmlgetnodetype();
	}

	if ( strcmp( input, "xmlnew" ) == 0 ) {
		return cffxmlnew();
	}

	if ( strcmp( input, "xmlparse" ) == 0 ) {
		return cffxmlparse();
	}

	if ( strcmp( input, "xmlsearch" ) == 0 ) {
		return cffxmlsearch();
	}

	if ( strcmp( input, "xmltransform" ) == 0 ) {
		return cffxmltransform();
	}

	if ( strcmp( input, "xmlvalidate" ) == 0 ) {
		return cffxmlvalidate();
	}

	if ( strcmp( input, "year" ) == 0 ) {
		return cffyear();
	}

	if ( strcmp( input, "yesnoformat" ) == 0 ) {
		return cffyesnoformat();
	}


#ifdef NPP_CFWHEELS

	if ( strcmp( input, "adderror" ) == 0 ) {
		return cfwfadderror();
	}


	if ( strcmp( input, "adderrortobase" ) == 0 ) {
		return cfwfadderrortobase();
	}


	if ( strcmp( input, "addroute" ) == 0 ) {
		return cfwfaddroute();
	}


	if ( strcmp( input, "aftercreate" ) == 0 ) {
		return cfwfaftercreate();
	}


	if ( strcmp( input, "afterdelete" ) == 0 ) {
		return cfwfafterdelete();
	}


	if ( strcmp( input, "afterfind" ) == 0 ) {
		return cfwfafterfind();
	}


	if ( strcmp( input, "afterinitialization" ) == 0 ) {
		return cfwfafterinitialization();
	}


	if ( strcmp( input, "afternew" ) == 0 ) {
		return cfwfafternew();
	}


	if ( strcmp( input, "aftersave" ) == 0 ) {
		return cfwfaftersave();
	}


	if ( strcmp( input, "afterupdate" ) == 0 ) {
		return cfwfafterupdate();
	}


	if ( strcmp( input, "aftervalidation" ) == 0 ) {
		return cfwfaftervalidation();
	}


	if ( strcmp( input, "aftervalidationoncreate" ) == 0 ) {
		return cfwfaftervalidationoncreate();
	}


	if ( strcmp( input, "aftervalidationonupdate" ) == 0 ) {
		return cfwfaftervalidationonupdate();
	}


	if ( strcmp( input, "allchanges" ) == 0 ) {
		return cfwfallchanges();
	}


	if ( strcmp( input, "allerrors" ) == 0 ) {
		return cfwfallerrors();
	}


	if ( strcmp( input, "average" ) == 0 ) {
		return cfwfaverage();
	}


	if ( strcmp( input, "beforecreate" ) == 0 ) {
		return cfwfbeforecreate();
	}


	if ( strcmp( input, "beforedelete" ) == 0 ) {
		return cfwfbeforedelete();
	}


	if ( strcmp( input, "beforesave" ) == 0 ) {
		return cfwfbeforesave();
	}


	if ( strcmp( input, "beforeupdate" ) == 0 ) {
		return cfwfbeforeupdate();
	}


	if ( strcmp( input, "beforevalidation" ) == 0 ) {
		return cfwfbeforevalidation();
	}


	if ( strcmp( input, "beforevalidationoncreate" ) == 0 ) {
		return cfwfbeforevalidationoncreate();
	}


	if ( strcmp( input, "beforevalidationonupdate" ) == 0 ) {
		return cfwfbeforevalidationonupdate();
	}


	if ( strcmp( input, "belongsto" ) == 0 ) {
		return cfwfbelongsto();
	}


	if ( strcmp( input, "buttonto" ) == 0 ) {
		return cfwfbuttonto();
	}


	if ( strcmp( input, "caches" ) == 0 ) {
		return cfwfcaches();
	}


	if ( strcmp( input, "capitalize" ) == 0 ) {
		return cfwfcapitalize();
	}


	if ( strcmp( input, "changedfrom" ) == 0 ) {
		return cfwfchangedfrom();
	}


	if ( strcmp( input, "changedproperties" ) == 0 ) {
		return cfwfchangedproperties();
	}


	if ( strcmp( input, "checkbox" ) == 0 ) {
		return cfwfcheckbox();
	}


	if ( strcmp( input, "checkboxtag" ) == 0 ) {
		return cfwfcheckboxtag();
	}


	if ( strcmp( input, "clearerrors" ) == 0 ) {
		return cfwfclearerrors();
	}


	if ( strcmp( input, "columnnames" ) == 0 ) {
		return cfwfcolumnnames();
	}


	if ( strcmp( input, "contentforlayout" ) == 0 ) {
		return cfwfcontentforlayout();
	}


	if ( strcmp( input, "count" ) == 0 ) {
		return cfwfcount();
	}


	if ( strcmp( input, "create" ) == 0 ) {
		return cfwfcreate();
	}


	if ( strcmp( input, "cycle" ) == 0 ) {
		return cfwfcycle();
	}


	if ( strcmp( input, "datasource" ) == 0 ) {
		return cfwfdatasource();
	}


	if ( strcmp( input, "dateselect" ) == 0 ) {
		return cfwfdateselect();
	}


	if ( strcmp( input, "dateselecttags" ) == 0 ) {
		return cfwfdateselecttags();
	}


	if ( strcmp( input, "datetimeselect" ) == 0 ) {
		return cfwfdatetimeselect();
	}


	if ( strcmp( input, "datetimeselecttags" ) == 0 ) {
		return cfwfdatetimeselecttags();
	}


	if ( strcmp( input, "dayselecttag" ) == 0 ) {
		return cfwfdayselecttag();
	}


	if ( strcmp( input, "delete" ) == 0 ) {
		return cfwfdelete();
	}


	if ( strcmp( input, "deleteall" ) == 0 ) {
		return cfwfdeleteall();
	}


	if ( strcmp( input, "deletebykey" ) == 0 ) {
		return cfwfdeletebykey();
	}


	if ( strcmp( input, "deleteone" ) == 0 ) {
		return cfwfdeleteone();
	}


	if ( strcmp( input, "deobfuscateparam" ) == 0 ) {
		return cfwfdeobfuscateparam();
	}


	if ( strcmp( input, "distanceoftimeinwords" ) == 0 ) {
		return cfwfdistanceoftimeinwords();
	}


	if ( strcmp( input, "endformtag" ) == 0 ) {
		return cfwfendformtag();
	}


	if ( strcmp( input, "errorcount" ) == 0 ) {
		return cfwferrorcount();
	}


	if ( strcmp( input, "errormessageon" ) == 0 ) {
		return cfwferrormessageon();
	}


	if ( strcmp( input, "errorson" ) == 0 ) {
		return cfwferrorson();
	}


	if ( strcmp( input, "errorsonbase" ) == 0 ) {
		return cfwferrorsonbase();
	}


	if ( strcmp( input, "exists" ) == 0 ) {
		return cfwfexists();
	}


	if ( strcmp( input, "filefield" ) == 0 ) {
		return cfwffilefield();
	}


	if ( strcmp( input, "filefieldtag" ) == 0 ) {
		return cfwffilefieldtag();
	}


	if ( strcmp( input, "filters" ) == 0 ) {
		return cfwffilters();
	}


	if ( strcmp( input, "findall" ) == 0 ) {
		return cfwffindall();
	}


	if ( strcmp( input, "findbykey" ) == 0 ) {
		return cfwffindbykey();
	}


	if ( strcmp( input, "findone" ) == 0 ) {
		return cfwffindone();
	}


	if ( strcmp( input, "flash" ) == 0 ) {
		return cfwfflash();
	}


	if ( strcmp( input, "flashclear" ) == 0 ) {
		return cfwfflashclear();
	}


	if ( strcmp( input, "flashcount" ) == 0 ) {
		return cfwfflashcount();
	}


	if ( strcmp( input, "flashdelete" ) == 0 ) {
		return cfwfflashdelete();
	}


	if ( strcmp( input, "flashinsert" ) == 0 ) {
		return cfwfflashinsert();
	}


	if ( strcmp( input, "flashisempty" ) == 0 ) {
		return cfwfflashisempty();
	}


	if ( strcmp( input, "flashkeyexists" ) == 0 ) {
		return cfwfflashkeyexists();
	}


	if ( strcmp( input, "get" ) == 0 ) {
		return cfwfget();
	}


	if ( strcmp( input, "haschanged" ) == 0 ) {
		return cfwfhaschanged();
	}


	if ( strcmp( input, "haserrors" ) == 0 ) {
		return cfwfhaserrors();
	}


	if ( strcmp( input, "hasmany" ) == 0 ) {
		return cfwfhasmany();
	}


	if ( strcmp( input, "hasone" ) == 0 ) {
		return cfwfhasone();
	}


	if ( strcmp( input, "hiddenfield" ) == 0 ) {
		return cfwfhiddenfield();
	}


	if ( strcmp( input, "hiddenfieldtag" ) == 0 ) {
		return cfwfhiddenfieldtag();
	}


	if ( strcmp( input, "hourselecttag" ) == 0 ) {
		return cfwfhourselecttag();
	}


	if ( strcmp( input, "humanize" ) == 0 ) {
		return cfwfhumanize();
	}


	if ( strcmp( input, "imagetag" ) == 0 ) {
		return cfwfimagetag();
	}


	if ( strcmp( input, "isajax" ) == 0 ) {
		return cfwfisajax();
	}


	if ( strcmp( input, "isget" ) == 0 ) {
		return cfwfisget();
	}


	if ( strcmp( input, "isnew" ) == 0 ) {
		return cfwfisnew();
	}


	if ( strcmp( input, "ispost" ) == 0 ) {
		return cfwfispost();
	}


	if ( strcmp( input, "javascriptincludetag" ) == 0 ) {
		return cfwfjavascriptincludetag();
	}


	if ( strcmp( input, "key" ) == 0 ) {
		return cfwfkey();
	}


	if ( strcmp( input, "maximum" ) == 0 ) {
		return cfwfmaximum();
	}


	if ( strcmp( input, "minimum" ) == 0 ) {
		return cfwfminimum();
	}


	if ( strcmp( input, "minuteselecttag" ) == 0 ) {
		return cfwfminuteselecttag();
	}


	if ( strcmp( input, "model" ) == 0 ) {
		return cfwfmodel();
	}


	if ( strcmp( input, "monthselecttag" ) == 0 ) {
		return cfwfmonthselecttag();
	}


	if ( strcmp( input, "new" ) == 0 ) {
		return cfwfnew();
	}


	if ( strcmp( input, "obfuscateparam" ) == 0 ) {
		return cfwfobfuscateparam();
	}


	if ( strcmp( input, "passwordfield" ) == 0 ) {
		return cfwfpasswordfield();
	}


	if ( strcmp( input, "pluginnames" ) == 0 ) {
		return cfwfpluginnames();
	}


	if ( strcmp( input, "pluralize" ) == 0 ) {
		return cfwfpluralize();
	}


	if ( strcmp( input, "primarykey" ) == 0 ) {
		return cfwfprimarykey();
	}


	if ( strcmp( input, "property" ) == 0 ) {
		return cfwfproperty();
	}


	if ( strcmp( input, "propertynames" ) == 0 ) {
		return cfwfpropertynames();
	}


	if ( strcmp( input, "radiobutton" ) == 0 ) {
		return cfwfradiobutton();
	}


	if ( strcmp( input, "radiobuttontag" ) == 0 ) {
		return cfwfradiobuttontag();
	}


	if ( strcmp( input, "redirectto" ) == 0 ) {
		return cfwfredirectto();
	}


	if ( strcmp( input, "reload" ) == 0 ) {
		return cfwfreload();
	}


	if ( strcmp( input, "rendernothing" ) == 0 ) {
		return cfwfrendernothing();
	}


	if ( strcmp( input, "renderpage" ) == 0 ) {
		return cfwfrenderpage();
	}


	if ( strcmp( input, "renderpartial" ) == 0 ) {
		return cfwfrenderpartial();
	}


	if ( strcmp( input, "rendertext" ) == 0 ) {
		return cfwfrendertext();
	}


	if ( strcmp( input, "save" ) == 0 ) {
		return cfwfsave();
	}


	if ( strcmp( input, "secondselecttag" ) == 0 ) {
		return cfwfsecondselecttag();
	}


	if ( strcmp( input, "select" ) == 0 ) {
		return cfwfselect();
	}


	if ( strcmp( input, "selecttag" ) == 0 ) {
		return cfwfselecttag();
	}


	if ( strcmp( input, "sendemail" ) == 0 ) {
		return cfwfsendemail();
	}


	if ( strcmp( input, "sendfile" ) == 0 ) {
		return cfwfsendfile();
	}


	if ( strcmp( input, "set" ) == 0 ) {
		return cfwfset();
	}


	if ( strcmp( input, "setproperties" ) == 0 ) {
		return cfwfsetproperties();
	}


	if ( strcmp( input, "singularize" ) == 0 ) {
		return cfwfsingularize();
	}


	if ( strcmp( input, "startformtag" ) == 0 ) {
		return cfwfstartformtag();
	}


	if ( strcmp( input, "stylesheetlinktag" ) == 0 ) {
		return cfwfstylesheetlinktag();
	}


	if ( strcmp( input, "submittag" ) == 0 ) {
		return cfwfsubmittag();
	}


	if ( strcmp( input, "sum" ) == 0 ) {
		return cfwfsum();
	}


	if ( strcmp( input, "table" ) == 0 ) {
		return cfwftable();
	}


	if ( strcmp( input, "tablename" ) == 0 ) {
		return cfwftablename();
	}


	if ( strcmp( input, "textarea" ) == 0 ) {
		return cfwftextarea();
	}


	if ( strcmp( input, "textareatag" ) == 0 ) {
		return cfwftextareatag();
	}


	if ( strcmp( input, "textfield" ) == 0 ) {
		return cfwftextfield();
	}


	if ( strcmp( input, "textfieldtag" ) == 0 ) {
		return cfwftextfieldtag();
	}


	if ( strcmp( input, "timeselect" ) == 0 ) {
		return cfwftimeselect();
	}


	if ( strcmp( input, "timeselecttags" ) == 0 ) {
		return cfwftimeselecttags();
	}


	if ( strcmp( input, "update" ) == 0 ) {
		return cfwfupdate();
	}


	if ( strcmp( input, "updateall" ) == 0 ) {
		return cfwfupdateall();
	}


	if ( strcmp( input, "updatebykey" ) == 0 ) {
		return cfwfupdatebykey();
	}


	if ( strcmp( input, "updateone" ) == 0 ) {
		return cfwfupdateone();
	}


	if ( strcmp( input, "urlfor" ) == 0 ) {
		return cfwfurlfor();
	}


	if ( strcmp( input, "valid" ) == 0 ) {
		return cfwfvalid();
	}


	if ( strcmp( input, "validate" ) == 0 ) {
		return cfwfvalidate();
	}


	if ( strcmp( input, "validateoncreate" ) == 0 ) {
		return cfwfvalidateoncreate();
	}


	if ( strcmp( input, "validateonupdate" ) == 0 ) {
		return cfwfvalidateonupdate();
	}


	if ( strcmp( input, "validatesconfirmationof" ) == 0 ) {
		return cfwfvalidatesconfirmationof();
	}


	if ( strcmp( input, "validatesexclusionof" ) == 0 ) {
		return cfwfvalidatesexclusionof();
	}


	if ( strcmp( input, "validatesformatof" ) == 0 ) {
		return cfwfvalidatesformatof();
	}


	if ( strcmp( input, "validatesinclusionof" ) == 0 ) {
		return cfwfvalidatesinclusionof();
	}


	if ( strcmp( input, "validateslengthof" ) == 0 ) {
		return cfwfvalidateslengthof();
	}


	if ( strcmp( input, "validatesnumericalityof" ) == 0 ) {
		return cfwfvalidatesnumericalityof();
	}


	if ( strcmp( input, "validatespresenceof" ) == 0 ) {
		return cfwfvalidatespresenceof();
	}


	if ( strcmp( input, "validatesuniquenessof" ) == 0 ) {
		return cfwfvalidatesuniquenessof();
	}


	if ( strcmp( input, "verifies" ) == 0 ) {
		return cfwfverifies();
	}


	if ( strcmp( input, "yearselecttag" ) == 0 ) {
		return cfwfyearselecttag();
	}


#endif

	return cffunction();

}
char * getTypeAsString( cftypes type )
{
	switch ( type ) {
	case T_ANY:
		return "Any ";
		break;
	case T_ARRAY:
		return "Array ";
		break;
	case T_BINARY:
		return "Binary ";
		break;
	case T_BOOLEAN:
		return "Boolean ";
		break;
	case T_DATETIME:
		return "DateTime ";
		break;
	case T_NODE:
		return "Node ";
		break;
	case T_NUMERIC:
		return "Numeric ";
		break;
	case T_OBJECT:
		return "Object ";
		break;
	case T_QUERY:
		return "Query ";
		break;
	case T_QUERYCOLUMN:
		return "QueryColumn ";
		break;
	case T_REGEX:
		return "RegEx ";
		break;
	case T_STRING:
		return "String ";
		break;
	case T_STRUCT:
		return "Struct ";
		break;
	case T_VARIABLENAME:
		return "VaraibleName ";
		break;
	case T_ODBCDATETIME:
		return "ODBCDateTime ";
		break;
	case T_ODBCDATE:
		return "ODBCDate ";
		break;
	case T_ODBCTIME:
		return "ODBCTime ";
		break;
	case T_IMAGE:
		return "Image ";
		break;
	case T_VOID:
		return "Void ";
		break;
	default:
		return"";
		break;
	}
}
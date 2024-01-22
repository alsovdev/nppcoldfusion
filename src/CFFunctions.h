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


//#define NPP_CFWHEELS
#ifndef NPP_CFFUNCTIONS
#define NPP_CFFUNCTIONS

#include <string.h>
enum cftypes {
	T_ANY, T_ARRAY, T_BINARY, T_BOOLEAN, T_DATETIME, T_NODE,
	T_NUMERIC, T_OBJECT, T_QUERY, T_QUERYCOLUMN, T_REGEX, T_STRING,
	T_STRUCT, T_VARIABLENAME, T_ODBCDATETIME, T_ODBCDATE,
	T_ODBCTIME, T_IMAGE, T_VOID
};


class cfparameter
{
public:
	const char* name;
	cftypes type;

	cfparameter();
	~cfparameter();
};
/*
class cfvalue
{
public:
	char * value;
	cfvalue();
	~cfvalue();

};

class cfattribute
{
public:
	char * name;
	cftypes type;

	cfattribute();
	~cfattribute();
};


class cftag
{
public:
	cftag();
	~cftag();
public:
	char * name;
	cfattribute attributes[10];
	//bool parameterrequired[10];
	//cftypes returntype;
};
*/
class cffunction
{
public:
	cffunction();
	~cffunction();
public:
	const char* name;
	cfparameter parameters[10];
	bool parameterrequired[10];
	cftypes returntype;
};
class cfpnumber_numeric : public cfparameter
{
public:
	cfpnumber_numeric();

	~cfpnumber_numeric();

};


class cfpwebservice_string : public cfparameter
{
public:
	cfpwebservice_string();

	~cfpwebservice_string();

};


class cfpnamespace_string : public cfparameter
{
public:
	cfpnamespace_string();

	~cfpnamespace_string();

};


class cfpname_string : public cfparameter
{
public:
	cfpname_string();

	~cfpname_string();

};


class cfpvalue_string : public cfparameter
{
public:
	cfpvalue_string();

	~cfpvalue_string();

};


class cfpmustunderstand_boolean : public cfparameter
{
public:
	cfpmustunderstand_boolean();

	~cfpmustunderstand_boolean();

};


class cfpurl_string : public cfparameter
{
public:
	cfpurl_string();

	~cfpurl_string();

};


class cfpfunctionname_string : public cfparameter
{
public:
	cfpfunctionname_string();

	~cfpfunctionname_string();

};


class cfparray_array : public cfparameter
{
public:
	cfparray_array();

	~cfparray_array();

};


class cfpvalue_any : public cfparameter
{
public:
	cfpvalue_any();

	~cfpvalue_any();

};


class cfpobject_any : public cfparameter
{
public:
	cfpobject_any();

	~cfpobject_any();

};


class cfpposition_numeric : public cfparameter
{
public:
	cfpposition_numeric();

	~cfpposition_numeric();

};


class cfpobject_variablename : public cfparameter
{
public:
	cfpobject_variablename();

	~cfpobject_variablename();

};


class cfparray_string : public cfparameter
{
public:
	cfparray_string();

	~cfparray_string();

};


class cfpelementindex_numeric : public cfparameter
{
public:
	cfpelementindex_numeric();

	~cfpelementindex_numeric();

};


class cfpdimension_numeric : public cfparameter
{
public:
	cfpdimension_numeric();

	~cfpdimension_numeric();

};


class cfpvalue_object : public cfparameter
{
public:
	cfpvalue_object();

	~cfpvalue_object();

};


class cfpsize_numeric : public cfparameter
{
public:
	cfpsize_numeric();

	~cfpsize_numeric();

};


class cfpstart_pos_numeric : public cfparameter
{
public:
	cfpstart_pos_numeric();

	~cfpstart_pos_numeric();

};


class cfpend_pos_numeric : public cfparameter
{
public:
	cfpend_pos_numeric();

	~cfpend_pos_numeric();

};


class cfpsort_type_string : public cfparameter
{
public:
	cfpsort_type_string();

	~cfpsort_type_string();

};


class cfpsort_order_string : public cfparameter
{
public:
	cfpsort_order_string();

	~cfpsort_order_string();

};


class cfpposition1_numeric : public cfparameter
{
public:
	cfpposition1_numeric();

	~cfpposition1_numeric();

};


class cfpposition2_numeric : public cfparameter
{
public:
	cfpposition2_numeric();

	~cfpposition2_numeric();

};


class cfpdelimiter_string : public cfparameter
{
public:
	cfpdelimiter_string();

	~cfpdelimiter_string();

};


class cfpstring_string : public cfparameter
{
public:
	cfpstring_string();

	~cfpstring_string();

};


class cfpbinaryencoding_string : public cfparameter
{
public:
	cfpbinaryencoding_string();

	~cfpbinaryencoding_string();

};


class cfpbinarydata_binary : public cfparameter
{
public:
	cfpbinarydata_binary();

	~cfpbinarydata_binary();

};


class cfpencoding_string : public cfparameter
{
public:
	cfpencoding_string();

	~cfpencoding_string();

};


class cfpnumber1_numeric : public cfparameter
{
public:
	cfpnumber1_numeric();

	~cfpnumber1_numeric();

};


class cfpnumber2_numeric : public cfparameter
{
public:
	cfpnumber2_numeric();

	~cfpnumber2_numeric();

};


class cfpstart_numeric : public cfparameter
{
public:
	cfpstart_numeric();

	~cfpstart_numeric();

};


class cfplength_numeric : public cfparameter
{
public:
	cfplength_numeric();

	~cfplength_numeric();

};


class cfpmask_numeric : public cfparameter
{
public:
	cfpmask_numeric();

	~cfpmask_numeric();

};


class cfpcount_numeric : public cfparameter
{
public:
	cfpcount_numeric();

	~cfpcount_numeric();

};


class cfpid_string : public cfparameter
{
public:
	cfpid_string();

	~cfpid_string();

};


class cfptype_string : public cfparameter
{
public:
	cfptype_string();

	~cfptype_string();

};


class cfptimespan_datetime : public cfparameter
{
public:
	cfptimespan_datetime();

	~cfptimespan_datetime();

};


class cfpideltime_datetime : public cfparameter
{
public:
	cfpideltime_datetime();

	~cfpideltime_datetime();

};


class cfpids_string : public cfparameter
{
public:
	cfpids_string();

	~cfpids_string();

};


class cfpthrowonerror_boolean : public cfparameter
{
public:
	cfpthrowonerror_boolean();

	~cfpthrowonerror_boolean();

};


class cfppropstruct_struct : public cfparameter
{
public:
	cfppropstruct_struct();

	~cfppropstruct_struct();

};


class cfpbinaryobject_binary : public cfparameter
{
public:
	cfpbinaryobject_binary();

	~cfpbinaryobject_binary();

};


class cfpstring1_string : public cfparameter
{
public:
	cfpstring1_string();

	~cfpstring1_string();

};


class cfpstring2_string : public cfparameter
{
public:
	cfpstring2_string();

	~cfpstring2_string();

};


class cfpyear_numeric : public cfparameter
{
public:
	cfpyear_numeric();

	~cfpyear_numeric();

};


class cfpmonth_numeric : public cfparameter
{
public:
	cfpmonth_numeric();

	~cfpmonth_numeric();

};


class cfpday_numeric : public cfparameter
{
public:
	cfpday_numeric();

	~cfpday_numeric();

};


class cfphour_numeric : public cfparameter
{
public:
	cfphour_numeric();

	~cfphour_numeric();

};


class cfpminute_numeric : public cfparameter
{
public:
	cfpminute_numeric();

	~cfpminute_numeric();

};


class cfpsecond_numeric : public cfparameter
{
public:
	cfpsecond_numeric();

	~cfpsecond_numeric();

};


class cfpcontext_string : public cfparameter
{
public:
	cfpcontext_string();

	~cfpcontext_string();

};


class cfpclass_string : public cfparameter
{
public:
	cfpclass_string();

	~cfpclass_string();

};


class cfplocale_string : public cfparameter
{
public:
	cfplocale_string();

	~cfplocale_string();

};


class cfpservername_string : public cfparameter
{
public:
	cfpservername_string();

	~cfpservername_string();

};


class cfpcomponent_name_string : public cfparameter
{
public:
	cfpcomponent_name_string();

	~cfpcomponent_name_string();

};


class cfpurltowsdl_string : public cfparameter
{
public:
	cfpurltowsdl_string();

	~cfpurltowsdl_string();

};


class cfpportname_string : public cfparameter
{
public:
	cfpportname_string();

	~cfpportname_string();

};


class cfpdate_datetime : public cfparameter
{
public:
	cfpdate_datetime();

	~cfpdate_datetime();

};


class cfpdays_numeric : public cfparameter
{
public:
	cfpdays_numeric();

	~cfpdays_numeric();

};


class cfphours_numeric : public cfparameter
{
public:
	cfphours_numeric();

	~cfphours_numeric();

};


class cfpminutes_numeric : public cfparameter
{
public:
	cfpminutes_numeric();

	~cfpminutes_numeric();

};


class cfpseconds_numeric : public cfparameter
{
public:
	cfpseconds_numeric();

	~cfpseconds_numeric();

};


class cfpdatepart_string : public cfparameter
{
public:
	cfpdatepart_string();

	~cfpdatepart_string();

};


class cfpdate1_datetime : public cfparameter
{
public:
	cfpdate1_datetime();

	~cfpdate1_datetime();

};


class cfpdate2_datetime : public cfparameter
{
public:
	cfpdate2_datetime();

	~cfpdate2_datetime();

};


class cfpmask_string : public cfparameter
{
public:
	cfpmask_string();

	~cfpmask_string();

};


class cfpday_of_week_numeric : public cfparameter
{
public:
	cfpday_of_week_numeric();

	~cfpday_of_week_numeric();

};


class cfpencrypted_string_string : public cfparameter
{
public:
	cfpencrypted_string_string();

	~cfpencrypted_string_string();

};


class cfpkey_string : public cfparameter
{
public:
	cfpkey_string();

	~cfpkey_string();

};


class cfpalgorithm_string : public cfparameter
{
public:
	cfpalgorithm_string();

	~cfpalgorithm_string();

};


class cfpivorsalt_binary : public cfparameter
{
public:
	cfpivorsalt_binary();

	~cfpivorsalt_binary();

};


class cfpiterations_numeric : public cfparameter
{
public:
	cfpiterations_numeric();

	~cfpiterations_numeric();

};


class cfpbytes_string : public cfparameter
{
public:
	cfpbytes_string();

	~cfpbytes_string();

};


class cfpjsonvar_string : public cfparameter
{
public:
	cfpjsonvar_string();

	~cfpjsonvar_string();

};


class cfpstrictmapping_boolean : public cfparameter
{
public:
	cfpstrictmapping_boolean();

	~cfpstrictmapping_boolean();

};


class cfppath_string : public cfparameter
{
public:
	cfppath_string();

	~cfppath_string();

};


class cfprecurse_boolean : public cfparameter
{
public:
	cfprecurse_boolean();

	~cfprecurse_boolean();

};


class cfpabsolute_path_string : public cfparameter
{
public:
	cfpabsolute_path_string();

	~cfpabsolute_path_string();

};


class cfpreturntype_string : public cfparameter
{
public:
	cfpreturntype_string();

	~cfpreturntype_string();

};


class cfpfilter_string : public cfparameter
{
public:
	cfpfilter_string();

	~cfpfilter_string();

};


class cfpsort_string : public cfparameter
{
public:
	cfpsort_string();

	~cfpsort_string();

};


class cfpnewpath_string : public cfparameter
{
public:
	cfpnewpath_string();

	~cfpnewpath_string();

};


class cfpvariable_name_variablename : public cfparameter
{
public:
	cfpvariable_name_variablename();

	~cfpvariable_name_variablename();

};


class cfpvariable_object : public cfparameter
{
public:
	cfpvariable_object();

	~cfpvariable_object();

};


class cfpentity_variablename : public cfparameter
{
public:
	cfpentity_variablename();

	~cfpentity_variablename();

};


class cfpentityname_string : public cfparameter
{
public:
	cfpentityname_string();

	~cfpentityname_string();

};


class cfpfiltercriteria_string : public cfparameter
{
public:
	cfpfiltercriteria_string();

	~cfpfiltercriteria_string();

};


class cfpunique_string : public cfparameter
{
public:
	cfpunique_string();

	~cfpunique_string();

};


class cfpsortorder_string : public cfparameter
{
public:
	cfpsortorder_string();

	~cfpsortorder_string();

};


class cfpoptions_string : public cfparameter
{
public:
	cfpoptions_string();

	~cfpoptions_string();

};


class cfpsampleentity_string : public cfparameter
{
public:
	cfpsampleentity_string();

	~cfpsampleentity_string();

};


class cfpunique_boolean : public cfparameter
{
public:
	cfpunique_boolean();

	~cfpunique_boolean();

};


class cfpid_object : public cfparameter
{
public:
	cfpid_object();

	~cfpid_object();

};


class cfpforceinsert_boolean : public cfparameter
{
public:
	cfpforceinsert_boolean();

	~cfpforceinsert_boolean();

};


class cfporm_object_variablename : public cfparameter
{
public:
	cfporm_object_variablename();

	~cfporm_object_variablename();

};


class cfpentity_name_string : public cfparameter
{
public:
	cfpentity_name_string();

	~cfpentity_name_string();

};


class cfpexpression1_string : public cfparameter
{
public:
	cfpexpression1_string();

	~cfpexpression1_string();

};


class cfpexpression2_string : public cfparameter
{
public:
	cfpexpression2_string();

	~cfpexpression2_string();

};


class cfpexpressionn_string : public cfparameter
{
public:
	cfpexpressionn_string();

	~cfpexpressionn_string();

};


class cfprelative_path_string : public cfparameter
{
public:
	cfprelative_path_string();

	~cfprelative_path_string();

};


class cfpfileobj_variablename : public cfparameter
{
public:
	cfpfileobj_variablename();

	~cfpfileobj_variablename();

};


class cfpsource_string : public cfparameter
{
public:
	cfpsource_string();

	~cfpsource_string();

};


class cfpdestination_string : public cfparameter
{
public:
	cfpdestination_string();

	~cfpdestination_string();

};


class cfpfilepath_string : public cfparameter
{
public:
	cfpfilepath_string();

	~cfpfilepath_string();

};


class cfpfileobject_object : public cfparameter
{
public:
	cfpfileobject_object();

	~cfpfileobject_object();

};


class cfpmode_string : public cfparameter
{
public:
	cfpmode_string();

	~cfpmode_string();

};


class cfpcharset_string : public cfparameter
{
public:
	cfpcharset_string();

	~cfpcharset_string();

};


class cfpfileobj_object : public cfparameter
{
public:
	cfpfileobj_object();

	~cfpfileobj_object();

};


class cfpfile_variablename : public cfparameter
{
public:
	cfpfile_variablename();

	~cfpfile_variablename();

};


class cfpattribute_string : public cfparameter
{
public:
	cfpattribute_string();

	~cfpattribute_string();

};


class cfpbytes_numeric : public cfparameter
{
public:
	cfpbytes_numeric();

	~cfpbytes_numeric();

};


class cfpdata_string : public cfparameter
{
public:
	cfpdata_string();

	~cfpdata_string();

};


class cfpfile_object : public cfparameter
{
public:
	cfpfile_object();

	~cfpfile_object();

};


class cfptext_string : public cfparameter
{
public:
	cfptext_string();

	~cfptext_string();

};


class cfpsubstring_string : public cfparameter
{
public:
	cfpsubstring_string();

	~cfpsubstring_string();

};


class cfpset_string : public cfparameter
{
public:
	cfpset_string();

	~cfpset_string();

};


class cfpradix_numeric : public cfparameter
{
public:
	cfpradix_numeric();

	~cfpradix_numeric();

};


class cfptagname_string : public cfparameter
{
public:
	cfptagname_string();

	~cfptagname_string();

};


class cfpinstancenumber_numeric : public cfparameter
{
public:
	cfpinstancenumber_numeric();

	~cfpinstancenumber_numeric();

};


class cfpscope_name_string : public cfparameter
{
public:
	cfpscope_name_string();

	~cfpscope_name_string();

};


class cfpjavaobject_object : public cfparameter
{
public:
	cfpjavaobject_object();

	~cfpjavaobject_object();

};


class cfpgatewayid_string : public cfparameter
{
public:
	cfpgatewayid_string();

	~cfpgatewayid_string();

};


class cfpdatetime_datetime : public cfparameter
{
public:
	cfpdatetime_datetime();

	~cfpdatetime_datetime();

};


class cfpobject_object : public cfparameter
{
public:
	cfpobject_object();

	~cfpobject_object();

};


class cfpprinter_string : public cfparameter
{
public:
	cfpprinter_string();

	~cfpprinter_string();

};


class cfpinifile_string : public cfparameter
{
public:
	cfpinifile_string();

	~cfpinifile_string();

};


class cfpinipath_string : public cfparameter
{
public:
	cfpinipath_string();

	~cfpinipath_string();

};


class cfpsection_string : public cfparameter
{
public:
	cfpsection_string();

	~cfpsection_string();

};


class cfpentry_string : public cfparameter
{
public:
	cfpentry_string();

	~cfpentry_string();

};


class cfpasxml_boolean : public cfparameter
{
public:
	cfpasxml_boolean();

	~cfpasxml_boolean();

};


class cfpwebservice_object : public cfparameter
{
public:
	cfpwebservice_object();

	~cfpwebservice_object();

};


class cfpdir_string : public cfparameter
{
public:
	cfpdir_string();

	~cfpdir_string();

};


class cfpprefix_string : public cfparameter
{
public:
	cfpprefix_string();

	~cfpprefix_string();

};


class cfpindex_numeric : public cfparameter
{
public:
	cfpindex_numeric();

	~cfpindex_numeric();

};


class cfpdelimiters_string : public cfparameter
{
public:
	cfpdelimiters_string();

	~cfpdelimiters_string();

};


class cfpfilesystemtype_string : public cfparameter
{
public:
	cfpfilesystemtype_string();

	~cfpfilesystemtype_string();

};


class cfpversion_numeric : public cfparameter
{
public:
	cfpversion_numeric();

	~cfpversion_numeric();

};


class cfpcondition_boolean : public cfparameter
{
public:
	cfpcondition_boolean();

	~cfpcondition_boolean();

};


class cfpthickness_string : public cfparameter
{
public:
	cfpthickness_string();

	~cfpthickness_string();

};


class cfpcolor_string : public cfparameter
{
public:
	cfpcolor_string();

	~cfpcolor_string();

};


class cfpbordertype_string : public cfparameter
{
public:
	cfpbordertype_string();

	~cfpbordertype_string();

};


class cfpblurradius_numeric : public cfparameter
{
public:
	cfpblurradius_numeric();

	~cfpblurradius_numeric();

};


class cfpx_numeric : public cfparameter
{
public:
	cfpx_numeric();

	~cfpx_numeric();

};


class cfpy_numeric : public cfparameter
{
public:
	cfpy_numeric();

	~cfpy_numeric();

};


class cfpwidth_numeric : public cfparameter
{
public:
	cfpwidth_numeric();

	~cfpwidth_numeric();

};


class cfpheight_numeric : public cfparameter
{
public:
	cfpheight_numeric();

	~cfpheight_numeric();

};


class cfpdx_numeric : public cfparameter
{
public:
	cfpdx_numeric();

	~cfpdx_numeric();

};


class cfpdy_numeric : public cfparameter
{
public:
	cfpdy_numeric();

	~cfpdy_numeric();

};


class cfpstartangle_numeric : public cfparameter
{
public:
	cfpstartangle_numeric();

	~cfpstartangle_numeric();

};


class cfparchangle_numeric : public cfparameter
{
public:
	cfparchangle_numeric();

	~cfparchangle_numeric();

};


class cfpfilled_boolean : public cfparameter
{
public:
	cfpfilled_boolean();

	~cfpfilled_boolean();

};


class cfpraised_boolean : public cfparameter
{
public:
	cfpraised_boolean();

	~cfpraised_boolean();

};


class cfpname_object : public cfparameter
{
public:
	cfpname_object();

	~cfpname_object();

};


class cfpctrlx1_string : public cfparameter
{
public:
	cfpctrlx1_string();

	~cfpctrlx1_string();

};


class cfpctrly1_numeric : public cfparameter
{
public:
	cfpctrly1_numeric();

	~cfpctrly1_numeric();

};


class cfpctrlx2_numeric : public cfparameter
{
public:
	cfpctrlx2_numeric();

	~cfpctrlx2_numeric();

};


class cfpctrly2_numeric : public cfparameter
{
public:
	cfpctrly2_numeric();

	~cfpctrly2_numeric();

};


class cfpx1_numeric : public cfparameter
{
public:
	cfpx1_numeric();

	~cfpx1_numeric();

};


class cfpy1_numeric : public cfparameter
{
public:
	cfpy1_numeric();

	~cfpy1_numeric();

};


class cfpx2_numeric : public cfparameter
{
public:
	cfpx2_numeric();

	~cfpx2_numeric();

};


class cfpy2_numeric : public cfparameter
{
public:
	cfpy2_numeric();

	~cfpy2_numeric();

};


class cfpxcords_numeric : public cfparameter
{
public:
	cfpxcords_numeric();

	~cfpxcords_numeric();

};


class cfpycords_numeric : public cfparameter
{
public:
	cfpycords_numeric();

	~cfpycords_numeric();

};


class cfpispolygon_boolean : public cfparameter
{
public:
	cfpispolygon_boolean();

	~cfpispolygon_boolean();

};


class cfparcwidth_numeric : public cfparameter
{
public:
	cfparcwidth_numeric();

	~cfparcwidth_numeric();

};


class cfparcheight_numeric : public cfparameter
{
public:
	cfparcheight_numeric();

	~cfparcheight_numeric();

};


class cfpstr_string : public cfparameter
{
public:
	cfpstr_string();

	~cfpstr_string();

};


class cfpattributecollection_struct : public cfparameter
{
public:
	cfpattributecollection_struct();

	~cfpattributecollection_struct();

};


class cfptranspose_string : public cfparameter
{
public:
	cfptranspose_string();

	~cfptranspose_string();

};


class cfpimagetype_string : public cfparameter
{
public:
	cfpimagetype_string();

	~cfpimagetype_string();

};


class cfpcanvascolor_string : public cfparameter
{
public:
	cfpcanvascolor_string();

	~cfpcanvascolor_string();

};


class cfpsource1_string : public cfparameter
{
public:
	cfpsource1_string();

	~cfpsource1_string();

};


class cfpsource2_string : public cfparameter
{
public:
	cfpsource2_string();

	~cfpsource2_string();

};


class cfpimage1_string : public cfparameter
{
public:
	cfpimage1_string();

	~cfpimage1_string();

};


class cfpimage2_string : public cfparameter
{
public:
	cfpimage2_string();

	~cfpimage2_string();

};


class cfpinterpolation_string : public cfparameter
{
public:
	cfpinterpolation_string();

	~cfpinterpolation_string();

};


class cfpblurfactor_boolean : public cfparameter
{
public:
	cfpblurfactor_boolean();

	~cfpblurfactor_boolean();

};


class cfpangle_numeric : public cfparameter
{
public:
	cfpangle_numeric();

	~cfpangle_numeric();

};


class cfpfitwidth_numeric : public cfparameter
{
public:
	cfpfitwidth_numeric();

	~cfpfitwidth_numeric();

};


class cfpfitheight_numeric : public cfparameter
{
public:
	cfpfitheight_numeric();

	~cfpfitheight_numeric();

};


class cfpblurfactor_numeric : public cfparameter
{
public:
	cfpblurfactor_numeric();

	~cfpblurfactor_numeric();

};


class cfpantialias_boolean : public cfparameter
{
public:
	cfpantialias_boolean();

	~cfpantialias_boolean();

};


class cfppercent_numeric : public cfparameter
{
public:
	cfppercent_numeric();

	~cfppercent_numeric();

};


class cfpgain_numeric : public cfparameter
{
public:
	cfpgain_numeric();

	~cfpgain_numeric();

};


class cfpshear_numeric : public cfparameter
{
public:
	cfpshear_numeric();

	~cfpshear_numeric();

};


class cfpdirection_string : public cfparameter
{
public:
	cfpdirection_string();

	~cfpdirection_string();

};


class cfpshrx_numeric : public cfparameter
{
public:
	cfpshrx_numeric();

	~cfpshrx_numeric();

};


class cfpshry_numeric : public cfparameter
{
public:
	cfpshry_numeric();

	~cfpshry_numeric();

};


class cfpxtrans_numeric : public cfparameter
{
public:
	cfpxtrans_numeric();

	~cfpxtrans_numeric();

};


class cfpytrans_numeric : public cfparameter
{
public:
	cfpytrans_numeric();

	~cfpytrans_numeric();

};


class cfpquality_string : public cfparameter
{
public:
	cfpquality_string();

	~cfpquality_string();

};


class cfpoverwrite_boolean : public cfparameter
{
public:
	cfpoverwrite_boolean();

	~cfpoverwrite_boolean();

};


class cfpformat_string : public cfparameter
{
public:
	cfpformat_string();

	~cfpformat_string();

};


class cfpinhtmlformat_boolean : public cfparameter
{
public:
	cfpinhtmlformat_boolean();

	~cfpinhtmlformat_boolean();

};


class cfpc1_string : public cfparameter
{
public:
	cfpc1_string();

	~cfpc1_string();

};


class cfpradix_string : public cfparameter
{
public:
	cfpradix_string();

	~cfpradix_string();

};


class cfpvariable_name_string : public cfparameter
{
public:
	cfpvariable_name_string();

	~cfpvariable_name_string();

};


class cfptypename_string : public cfparameter
{
public:
	cfptypename_string();

	~cfptypename_string();

};


class cfpip_string : public cfparameter
{
public:
	cfpip_string();

	~cfpip_string();

};


class cfpvar_string : public cfparameter
{
public:
	cfpvar_string();

	~cfpvar_string();

};


class cfpipaddress_string : public cfparameter
{
public:
	cfpipaddress_string();

	~cfpipaddress_string();

};


class cfpvalue_variablename : public cfparameter
{
public:
	cfpvalue_variablename();

	~cfpvalue_variablename();

};


class cfpfile_string : public cfparameter
{
public:
	cfpfile_string();

	~cfpfile_string();

};


class cfprolelist_string : public cfparameter
{
public:
	cfprolelist_string();

	~cfprolelist_string();

};


class cfprole_name_string : public cfparameter
{
public:
	cfprole_name_string();

	~cfprole_name_string();

};


class cfpmin_numeric : public cfparameter
{
public:
	cfpmin_numeric();

	~cfpmin_numeric();

};


class cfpmax_numeric : public cfparameter
{
public:
	cfpmax_numeric();

	~cfpmax_numeric();

};


class cfppattern_string : public cfparameter
{
public:
	cfppattern_string();

	~cfppattern_string();

};


class cfpvariable_string : public cfparameter
{
public:
	cfpvariable_string();

	~cfpvariable_string();

};


class cfplist_string : public cfparameter
{
public:
	cfplist_string();

	~cfplist_string();

};


class cfpnew_delimiter_string : public cfparameter
{
public:
	cfpnew_delimiter_string();

	~cfpnew_delimiter_string();

};


class cfpqualifier_string : public cfparameter
{
public:
	cfpqualifier_string();

	~cfpqualifier_string();

};


class cfpelements_string : public cfparameter
{
public:
	cfpelements_string();

	~cfpelements_string();

};


class cfpincludeemptyfields_boolean : public cfparameter
{
public:
	cfpincludeemptyfields_boolean();

	~cfpincludeemptyfields_boolean();

};


class cfpmulticharacterdelimiter_boolean : public cfparameter
{
public:
	cfpmulticharacterdelimiter_boolean();

	~cfpmulticharacterdelimiter_boolean();

};


class cfpaddtoken_boolean : public cfparameter
{
public:
	cfpaddtoken_boolean();

	~cfpaddtoken_boolean();

};


class cfpstatuscode_numeric : public cfparameter
{
public:
	cfpstatuscode_numeric();

	~cfpstatuscode_numeric();

};


class cfpcurrency_string : public cfparameter
{
public:
	cfpcurrency_string();

	~cfpcurrency_string();

};


class cfpdt_string_string : public cfparameter
{
public:
	cfpdt_string_string();

	~cfpdt_string_string();

};


class cfpcurrency_string_string : public cfparameter
{
public:
	cfpcurrency_string_string();

	~cfpcurrency_string_string();

};


class cfptime_datetime : public cfparameter
{
public:
	cfptime_datetime();

	~cfptime_datetime();

};


class cfpmonth_number_numeric : public cfparameter
{
public:
	cfpmonth_number_numeric();

	~cfpmonth_number_numeric();

};


class cfpparam1_object : public cfparameter
{
public:
	cfpparam1_object();

	~cfpparam1_object();

};


class cfpparam2_object : public cfparameter
{
public:
	cfpparam2_object();

	~cfpparam2_object();

};


class cfpbinaryobject_object : public cfparameter
{
public:
	cfpbinaryobject_object();

	~cfpbinaryobject_object();

};


class cfpcomponentname_string : public cfparameter
{
public:
	cfpcomponentname_string();

	~cfpcomponentname_string();

};


class cfprelationname_string : public cfparameter
{
public:
	cfprelationname_string();

	~cfprelationname_string();

};


class cfpcachename_string : public cfparameter
{
public:
	cfpcachename_string();

	~cfpcachename_string();

};


class cfphql_string : public cfparameter
{
public:
	cfphql_string();

	~cfphql_string();

};


class cfpqueryoptions_string : public cfparameter
{
public:
	cfpqueryoptions_string();

	~cfpqueryoptions_string();

};


class cfppop_conversion_string : public cfparameter
{
public:
	cfppop_conversion_string();

	~cfppop_conversion_string();

};


class cfpexpressions_string : public cfparameter
{
public:
	cfpexpressions_string();

	~cfpexpressions_string();

};


class cfpquery_query : public cfparameter
{
public:
	cfpquery_query();

	~cfpquery_query();

};


class cfpcolumn_name_string : public cfparameter
{
public:
	cfpcolumn_name_string();

	~cfpcolumn_name_string();

};


class cfpdatatype_string : public cfparameter
{
public:
	cfpdatatype_string();

	~cfpdatatype_string();

};


class cfparray_name_array : public cfparameter
{
public:
	cfparray_name_array();

	~cfparray_name_array();

};


class cfpquery_string : public cfparameter
{
public:
	cfpquery_string();

	~cfpquery_string();

};


class cfppage_numeric : public cfparameter
{
public:
	cfppage_numeric();

	~cfppage_numeric();

};


class cfppagesize_numeric : public cfparameter
{
public:
	cfppagesize_numeric();

	~cfppagesize_numeric();

};


class cfpcolumnlist_string : public cfparameter
{
public:
	cfpcolumnlist_string();

	~cfpcolumnlist_string();

};


class cfpcolumntypelist_string : public cfparameter
{
public:
	cfpcolumntypelist_string();

	~cfpcolumntypelist_string();

};


class cfpcolumn_string : public cfparameter
{
public:
	cfpcolumn_string();

	~cfpcolumn_string();

};


class cfprow_numeric : public cfparameter
{
public:
	cfprow_numeric();

	~cfprow_numeric();

};


class cfpcolumn_querycolumn : public cfparameter
{
public:
	cfpcolumn_querycolumn();

	~cfpcolumn_querycolumn();

};


class cfpreg_expression_regex : public cfparameter
{
public:
	cfpreg_expression_regex();

	~cfpreg_expression_regex();

};


class cfpreturnsubexpressions_boolean : public cfparameter
{
public:
	cfpreturnsubexpressions_boolean();

	~cfpreturnsubexpressions_boolean();

};


class cfpobjectname_object : public cfparameter
{
public:
	cfpobjectname_object();

	~cfpobjectname_object();

};


class cfpreg_expression_string : public cfparameter
{
public:
	cfpreg_expression_string();

	~cfpreg_expression_string();

};


class cfpsubstring1_string : public cfparameter
{
public:
	cfpsubstring1_string();

	~cfpsubstring1_string();

};


class cfpsubstring2_string : public cfparameter
{
public:
	cfpsubstring2_string();

	~cfpsubstring2_string();

};


class cfpscope_string : public cfparameter
{
public:
	cfpscope_string();

	~cfpscope_string();

};


class cfplist1_string : public cfparameter
{
public:
	cfplist1_string();

	~cfplist1_string();

};


class cfplist2_string : public cfparameter
{
public:
	cfplist2_string();

	~cfplist2_string();

};


class cfpdata_struct : public cfparameter
{
public:
	cfpdata_struct();

	~cfpdata_struct();

};


class cfpvar_variablename : public cfparameter
{
public:
	cfpvar_variablename();

	~cfpvar_variablename();

};


class cfpserializequerybycolumns_boolean : public cfparameter
{
public:
	cfpserializequerybycolumns_boolean();

	~cfpserializequerybycolumns_boolean();

};


class cfpnew_locale_string : public cfparameter
{
public:
	cfpnew_locale_string();

	~cfpnew_locale_string();

};


class cfpduration_numeric : public cfparameter
{
public:
	cfpduration_numeric();

	~cfpduration_numeric();

};


class cfpspreadsheetobj_variablename : public cfparameter
{
public:
	cfpspreadsheetobj_variablename();

	~cfpspreadsheetobj_variablename();

};


class cfpstartrow_numeric : public cfparameter
{
public:
	cfpstartrow_numeric();

	~cfpstartrow_numeric();

};


class cfpstartcolumn_numeric : public cfparameter
{
public:
	cfpstartcolumn_numeric();

	~cfpstartcolumn_numeric();

};


class cfpinsert_boolean : public cfparameter
{
public:
	cfpinsert_boolean();

	~cfpinsert_boolean();

};


class cfpcolumn_numeric : public cfparameter
{
public:
	cfpcolumn_numeric();

	~cfpcolumn_numeric();

};


class cfpendcolumn_numeric : public cfparameter
{
public:
	cfpendcolumn_numeric();

	~cfpendcolumn_numeric();

};


class cfpendrow_numeric : public cfparameter
{
public:
	cfpendrow_numeric();

	~cfpendrow_numeric();

};


class cfpimagefilepath_string : public cfparameter
{
public:
	cfpimagefilepath_string();

	~cfpimagefilepath_string();

};


class cfpanchor_string : public cfparameter
{
public:
	cfpanchor_string();

	~cfpanchor_string();

};


class cfpimagedata_string : public cfparameter
{
public:
	cfpimagedata_string();

	~cfpimagedata_string();

};


class cfpinfo_struct : public cfparameter
{
public:
	cfpinfo_struct();

	~cfpinfo_struct();

};


class cfpsplitcolumn_numeric : public cfparameter
{
public:
	cfpsplitcolumn_numeric();

	~cfpsplitcolumn_numeric();

};


class cfpsplitrow_numeric : public cfparameter
{
public:
	cfpsplitrow_numeric();

	~cfpsplitrow_numeric();

};


class cfpposition_string : public cfparameter
{
public:
	cfpposition_string();

	~cfpposition_string();

};


class cfprange_numeric : public cfparameter
{
public:
	cfprange_numeric();

	~cfprange_numeric();

};


class cfpcolumns_string : public cfparameter
{
public:
	cfpcolumns_string();

	~cfpcolumns_string();

};


class cfpauthor_string : public cfparameter
{
public:
	cfpauthor_string();

	~cfpauthor_string();

};


class cfpcomment_string : public cfparameter
{
public:
	cfpcomment_string();

	~cfpcomment_string();

};


class cfprow_string : public cfparameter
{
public:
	cfprow_string();

	~cfprow_string();

};


class cfpsheetname_string : public cfparameter
{
public:
	cfpsheetname_string();

	~cfpsheetname_string();

};


class cfpxmlformat_boolean : public cfparameter
{
public:
	cfpxmlformat_boolean();

	~cfpxmlformat_boolean();

};


class cfpfilename_string : public cfparameter
{
public:
	cfpfilename_string();

	~cfpfilename_string();

};


class cfpformula_string : public cfparameter
{
public:
	cfpformula_string();

	~cfpformula_string();

};


class cfpcolumnnumber_numeric : public cfparameter
{
public:
	cfpcolumnnumber_numeric();

	~cfpcolumnnumber_numeric();

};


class cfpleftfooter_string : public cfparameter
{
public:
	cfpleftfooter_string();

	~cfpleftfooter_string();

};


class cfpcenterfooter_string : public cfparameter
{
public:
	cfpcenterfooter_string();

	~cfpcenterfooter_string();

};


class cfprightfooter_string : public cfparameter
{
public:
	cfprightfooter_string();

	~cfprightfooter_string();

};


class cfpleftheader_string : public cfparameter
{
public:
	cfpleftheader_string();

	~cfpleftheader_string();

};


class cfpcenterheader_string : public cfparameter
{
public:
	cfpcenterheader_string();

	~cfpcenterheader_string();

};


class cfprightheader_string : public cfparameter
{
public:
	cfprightheader_string();

	~cfprightheader_string();

};


class cfprownumber_numeric : public cfparameter
{
public:
	cfprownumber_numeric();

	~cfprownumber_numeric();

};


class cfpend_numeric : public cfparameter
{
public:
	cfpend_numeric();

	~cfpend_numeric();

};


class cfprows_numeric : public cfparameter
{
public:
	cfprows_numeric();

	~cfprows_numeric();

};


class cfppassword_string : public cfparameter
{
public:
	cfppassword_string();

	~cfppassword_string();

};


class cfpstruct1_struct : public cfparameter
{
public:
	cfpstruct1_struct();

	~cfpstruct1_struct();

};


class cfpstruct2_struct : public cfparameter
{
public:
	cfpstruct2_struct();

	~cfpstruct2_struct();

};


class cfpoverwriteflag_boolean : public cfparameter
{
public:
	cfpoverwriteflag_boolean();

	~cfpoverwriteflag_boolean();

};


class cfpstructure_struct : public cfparameter
{
public:
	cfpstructure_struct();

	~cfpstructure_struct();

};


class cfpstructure_string : public cfparameter
{
public:
	cfpstructure_string();

	~cfpstructure_string();

};


class cfpindicatenotexisting_boolean : public cfparameter
{
public:
	cfpindicatenotexisting_boolean();

	~cfpindicatenotexisting_boolean();

};


class cfptop_object : public cfparameter
{
public:
	cfptop_object();

	~cfptop_object();

};


class cfppathdesired_string : public cfparameter
{
public:
	cfppathdesired_string();

	~cfppathdesired_string();

};


class cfpallowoverwrite_boolean : public cfparameter
{
public:
	cfpallowoverwrite_boolean();

	~cfpallowoverwrite_boolean();

};


class cfpbase_struct : public cfparameter
{
public:
	cfpbase_struct();

	~cfpbase_struct();

};


class cfpsorttype_string : public cfparameter
{
public:
	cfpsorttype_string();

	~cfpsorttype_string();

};


class cfppathtosubelement_string : public cfparameter
{
public:
	cfppathtosubelement_string();

	~cfppathtosubelement_string();

};


class cfpthreadname_string : public cfparameter
{
public:
	cfpthreadname_string();

	~cfpthreadname_string();

};


class cfptimeout_numeric : public cfparameter
{
public:
	cfptimeout_numeric();

	~cfptimeout_numeric();

};


class cfpmessage_string : public cfparameter
{
public:
	cfpmessage_string();

	~cfpmessage_string();

};


class cfpdetail_string : public cfparameter
{
public:
	cfpdetail_string();

	~cfpdetail_string();

};


class cfperrorcode_string : public cfparameter
{
public:
	cfperrorcode_string();

	~cfperrorcode_string();

};


class cfpextendedinfo_string : public cfparameter
{
public:
	cfpextendedinfo_string();

	~cfpextendedinfo_string();

};


class cfpstring_or_object_object : public cfparameter
{
public:
	cfpstring_or_object_object();

	~cfpstring_or_object_object();

};


class cfpbase64_or_object_object : public cfparameter
{
public:
	cfpbase64_or_object_object();

	~cfpbase64_or_object_object();

};


class cfpcfvar_object : public cfparameter
{
public:
	cfpcfvar_object();

	~cfpcfvar_object();

};


class cfpjavascriptvar_string : public cfparameter
{
public:
	cfpjavascriptvar_string();

	~cfpjavascriptvar_string();

};


class cfpoutputformat_boolean : public cfparameter
{
public:
	cfpoutputformat_boolean();

	~cfpoutputformat_boolean();

};


class cfpasformat_boolean : public cfparameter
{
public:
	cfpasformat_boolean();

	~cfpasformat_boolean();

};


class cfpany_value_object : public cfparameter
{
public:
	cfpany_value_object();

	~cfpany_value_object();

};


class cfpabort_boolean : public cfparameter
{
public:
	cfpabort_boolean();

	~cfpabort_boolean();

};


class cfpcategory_string : public cfparameter
{
public:
	cfpcategory_string();

	~cfpcategory_string();

};


class cfpinline_boolean : public cfparameter
{
public:
	cfpinline_boolean();

	~cfpinline_boolean();

};


class cfplabel_string : public cfparameter
{
public:
	cfplabel_string();
	~cfplabel_string();

};


class cfpsavepoint_string : public cfparameter
{
public:
	cfpsavepoint_string();

	~cfpsavepoint_string();

};


class cfpurlencodedstring_string : public cfparameter
{
public:
	cfpurlencodedstring_string();

	~cfpurlencodedstring_string();

};


class cfprequesturl_string : public cfparameter
{
public:
	cfprequesturl_string();

	~cfprequesturl_string();

};


class cfplimit_numeric : public cfparameter
{
public:
	cfplimit_numeric();

	~cfplimit_numeric();

};


class cfpstrip_boolean : public cfparameter
{
public:
	cfpstrip_boolean();

	~cfpstrip_boolean();

};


class cfpexpand_boolean : public cfparameter
{
public:
	cfpexpand_boolean();

	~cfpexpand_boolean();

};


class cfphide_string : public cfparameter
{
public:
	cfphide_string();

	~cfphide_string();

};


class cfpkeys_numeric : public cfparameter
{
public:
	cfpkeys_numeric();

	~cfpkeys_numeric();

};



class cfpmetainfo_boolean : public cfparameter
{
public:
	cfpmetainfo_boolean();

	~cfpmetainfo_boolean();

};


class cfpoutput_string : public cfparameter
{
public:
	cfpoutput_string();

	~cfpoutput_string();

};


class cfpshow_string : public cfparameter
{
public:
	cfpshow_string();

	~cfpshow_string();

};


class cfpshowudfs_boolean : public cfparameter
{
public:
	cfpshowudfs_boolean();

	~cfpshowudfs_boolean();

};


class cfptop_numeric : public cfparameter
{
public:
	cfptop_numeric();

	~cfptop_numeric();

};


class cfplog_string : public cfparameter
{
public:
	cfplog_string();

	~cfplog_string();

};


class cfpapplication_boolean : public cfparameter
{
public:
	cfpapplication_boolean();

	~cfpapplication_boolean();

};


class cfpelem_node : public cfparameter
{
public:
	cfpelem_node();

	~cfpelem_node();

};


class cfpchildname_string : public cfparameter
{
public:
	cfpchildname_string();

	~cfpchildname_string();

};


class cfpn_numeric : public cfparameter
{
public:
	cfpn_numeric();

	~cfpn_numeric();

};


class cfpxmlobj_object : public cfparameter
{
public:
	cfpxmlobj_object();

	~cfpxmlobj_object();

};


class cfpescapenewset_boolean : public cfparameter
{
public:
	cfpescapenewset_boolean();

	~cfpescapenewset_boolean();

};


class cfpxmlnode_object : public cfparameter
{
public:
	cfpxmlnode_object();

	~cfpxmlnode_object();

};


class cfpcasesensitive_boolean : public cfparameter
{
public:
	cfpcasesensitive_boolean();

	~cfpcasesensitive_boolean();

};


class cfpxmlstring_string : public cfparameter
{
public:
	cfpxmlstring_string();

	~cfpxmlstring_string();

};


class cfpvalidator_string : public cfparameter
{
public:
	cfpvalidator_string();

	~cfpvalidator_string();

};


class cfpxmldoc_object : public cfparameter
{
public:
	cfpxmldoc_object();

	~cfpxmldoc_object();

};


class cfpxpathstring_string : public cfparameter
{
public:
	cfpxpathstring_string();

	~cfpxpathstring_string();

};


class cfpxml_string : public cfparameter
{
public:
	cfpxml_string();

	~cfpxml_string();

};


class cfpxsl_string : public cfparameter
{
public:
	cfpxsl_string();

	~cfpxsl_string();

};


class cfpparameters_struct : public cfparameter
{
public:
	cfpparameters_struct();

	~cfpparameters_struct();

};


class cfpvalue_boolean : public cfparameter
{
public:
	cfpvalue_boolean();

	~cfpvalue_boolean();

};


#ifdef NPP_CFWHEELS

class cfpproperty_string : public cfparameter
{
public:
	cfpproperty_string();
	~cfpproperty_string();

};

class cfpcontroller_string : public cfparameter
{
public:
	cfpcontroller_string();
	~cfpcontroller_string();

};

class cfpaction_string : public cfparameter
{
public:
	cfpaction_string();
	~cfpaction_string();

};

class cfpmethods_string : public cfparameter
{
public:
	cfpmethods_string();
	~cfpmethods_string();

};

class cfpwhere_string : public cfparameter
{
public:
	cfpwhere_string();
	~cfpwhere_string();

};

class cfpinclude_string : public cfparameter
{
public:
	cfpinclude_string();
	~cfpinclude_string();

};

class cfpdistinct_boolean : public cfparameter
{
public:
	cfpdistinct_boolean();
	~cfpdistinct_boolean();

};

class cfpforeignkey_string : public cfparameter
{
public:
	cfpforeignkey_string();
	~cfpforeignkey_string();

};

class cfpjointype_string : public cfparameter
{
public:
	cfpjointype_string();
	~cfpjointype_string();

};

class cfpwindowsize_numeric : public cfparameter
{
public:
	cfpwindowsize_numeric();
	~cfpwindowsize_numeric();

};

class cfpalwaysshowanchors_boolean : public cfparameter
{
public:
	cfpalwaysshowanchors_boolean();
	~cfpalwaysshowanchors_boolean();

};

class cfpanchordivider_string : public cfparameter
{
public:
	cfpanchordivider_string();
	~cfpanchordivider_string();

};

class cfplinktocurrentpage_boolean : public cfparameter
{
public:
	cfplinktocurrentpage_boolean();
	~cfplinktocurrentpage_boolean();

};

class cfpprepend_string : public cfparameter
{
public:
	cfpprepend_string();
	~cfpprepend_string();

};

class cfpappend_string : public cfparameter
{
public:
	cfpappend_string();
	~cfpappend_string();

};

class cfpprependtopage_string : public cfparameter
{
public:
	cfpprependtopage_string();
	~cfpprependtopage_string();

};

class cfpprependonfirst_boolean : public cfparameter
{
public:
	cfpprependonfirst_boolean();
	~cfpprependonfirst_boolean();

};

class cfpappendtopage_string : public cfparameter
{
public:
	cfpappendtopage_string();
	~cfpappendtopage_string();

};

class cfpappendonlast_boolean : public cfparameter
{
public:
	cfpappendonlast_boolean();
	~cfpappendonlast_boolean();

};

class cfpclassforcurrent_string : public cfparameter
{
public:
	cfpclassforcurrent_string();
	~cfpclassforcurrent_string();

};

class cfphandle_string : public cfparameter
{
public:
	cfphandle_string();
	~cfphandle_string();

};

class cfpshowsinglepage_boolean : public cfparameter
{
public:
	cfpshowsinglepage_boolean();
	~cfpshowsinglepage_boolean();

};

class cfpactions_string : public cfparameter
{
public:
	cfpactions_string();
	~cfpactions_string();

};

class cfptime_numeric : public cfparameter
{
public:
	cfptime_numeric();
	~cfptime_numeric();

};

class cfpobjectname_any : public cfparameter
{
public:
	cfpobjectname_any();
	~cfpobjectname_any();

};

class cfpcheckedvalue_string : public cfparameter
{
public:
	cfpcheckedvalue_string();
	~cfpcheckedvalue_string();

};

class cfpuncheckedvalue_string : public cfparameter
{
public:
	cfpuncheckedvalue_string();
	~cfpuncheckedvalue_string();

};

class cfplabelplacement_string : public cfparameter
{
public:
	cfplabelplacement_string();
	~cfplabelplacement_string();

};

class cfpprependtolabel_string : public cfparameter
{
public:
	cfpprependtolabel_string();
	~cfpprependtolabel_string();

};

class cfpappendtolabel_string : public cfparameter
{
public:
	cfpappendtolabel_string();
	~cfpappendtolabel_string();

};

class cfperrorelement_string : public cfparameter
{
public:
	cfperrorelement_string();
	~cfperrorelement_string();

};

class cfpchecked_boolean : public cfparameter
{
public:
	cfpchecked_boolean();
	~cfpchecked_boolean();

};

class cfppartial_any : public cfparameter
{
public:
	cfppartial_any();
	~cfppartial_any();

};

class cfpgroup_string : public cfparameter
{
public:
	cfpgroup_string();
	~cfpgroup_string();

};

class cfpcache_any : public cfparameter
{
public:
	cfpcache_any();
	~cfpcache_any();

};

class cfplayout_string : public cfparameter
{
public:
	cfplayout_string();
	~cfplayout_string();

};

class cfpspacer_string : public cfparameter
{
public:
	cfpspacer_string();
	~cfpspacer_string();

};

class cfpproperties_struct : public cfparameter
{
public:
	cfpproperties_struct();
	~cfpproperties_struct();

};

class cfpdefaults_boolean : public cfparameter
{
public:
	cfpdefaults_boolean();
	~cfpdefaults_boolean();

};

class cfpparameterize_any : public cfparameter
{
public:
	cfpparameterize_any();
	~cfpparameterize_any();

};

class cfpconfirm_string : public cfparameter
{
public:
	cfpconfirm_string();
	~cfpconfirm_string();

};

class cfproute_string : public cfparameter
{
public:
	cfproute_string();
	~cfproute_string();

};

class cfpkey_any : public cfparameter
{
public:
	cfpkey_any();
	~cfpkey_any();

};

class cfpparams_string : public cfparameter
{
public:
	cfpparams_string();
	~cfpparams_string();

};

class cfponlypath_boolean : public cfparameter
{
public:
	cfponlypath_boolean();
	~cfponlypath_boolean();

};

class cfphost_string : public cfparameter
{
public:
	cfphost_string();
	~cfphost_string();

};

class cfpprotocol_string : public cfparameter
{
public:
	cfpprotocol_string();
	~cfpprotocol_string();

};

class cfpport_numeric : public cfparameter
{
public:
	cfpport_numeric();
	~cfpport_numeric();

};

class cfpdatasource_string : public cfparameter
{
public:
	cfpdatasource_string();
	~cfpdatasource_string();

};

class cfpusername_string : public cfparameter
{
public:
	cfpusername_string();
	~cfpusername_string();

};

class cfporder_string : public cfparameter
{
public:
	cfporder_string();
	~cfporder_string();

};

class cfpseparator_string : public cfparameter
{
public:
	cfpseparator_string();
	~cfpseparator_string();

};


class cfpendyear_numeric : public cfparameter
{
public:
	cfpendyear_numeric();
	~cfpendyear_numeric();

};

class cfpmonthdisplay_string : public cfparameter
{
public:
	cfpmonthdisplay_string();
	~cfpmonthdisplay_string();

};

class cfpincludeblank_any : public cfparameter
{
public:
	cfpincludeblank_any();
	~cfpincludeblank_any();

};

class cfpselected_string : public cfparameter
{
public:
	cfpselected_string();
	~cfpselected_string();

};

class cfpobjectname_string : public cfparameter
{
public:
	cfpobjectname_string();
	~cfpobjectname_string();

};

class cfpstartyear_numeric : public cfparameter
{
public:
	cfpstartyear_numeric();
	~cfpstartyear_numeric();

};

class cfptimeorder_string : public cfparameter
{
public:
	cfptimeorder_string();
	~cfptimeorder_string();

};

class cfpminutestep_numeric : public cfparameter
{
public:
	cfpminutestep_numeric();
	~cfpminutestep_numeric();

};

class cfpdateorder_string : public cfparameter
{
public:
	cfpdateorder_string();
	~cfpdateorder_string();

};

class cfpdateseparator_string : public cfparameter
{
public:
	cfpdateseparator_string();
	~cfpdateseparator_string();

};

class cfptimeseparator_string : public cfparameter
{
public:
	cfptimeseparator_string();
	~cfptimeseparator_string();

};

class cfpinstantiate_boolean : public cfparameter
{
public:
	cfpinstantiate_boolean();
	~cfpinstantiate_boolean();

};

class cfp$softdeletecheck_boolean : public cfparameter
{
public:
	cfp$softdeletecheck_boolean();
	~cfp$softdeletecheck_boolean();

};

class cfpparam_string : public cfparameter
{
public:
	cfpparam_string();
	~cfpparam_string();

};

class cfpshowduplicates_boolean : public cfparameter
{
public:
	cfpshowduplicates_boolean();
	~cfpshowduplicates_boolean();

};

class cfpprependtext_string : public cfparameter
{
public:
	cfpprependtext_string();
	~cfpprependtext_string();

};

class cfpappendtext_string : public cfparameter
{
public:
	cfpappendtext_string();
	~cfpappendtext_string();

};

class cfpwrapperelement_string : public cfparameter
{
public:
	cfpwrapperelement_string();
	~cfpwrapperelement_string();

};

class cfpreload_boolean : public cfparameter
{
public:
	cfpreload_boolean();
	~cfpreload_boolean();

};

class cfpthrough_string : public cfparameter
{
public:
	cfpthrough_string();
	~cfpthrough_string();

};

class cfponly_string : public cfparameter
{
public:
	cfponly_string();
	~cfponly_string();

};

class cfpexcept_string : public cfparameter
{
public:
	cfpexcept_string();
	~cfpexcept_string();

};

class cfpselect_string : public cfparameter
{
public:
	cfpselect_string();
	~cfpselect_string();

};

class cfpmaxrows_numeric : public cfparameter
{
public:
	cfpmaxrows_numeric();
	~cfpmaxrows_numeric();

};

class cfpreturnas_string : public cfparameter
{
public:
	cfpreturnas_string();
	~cfpreturnas_string();

};

class cfpshortcut_string : public cfparameter
{
public:
	cfpshortcut_string();
	~cfpshortcut_string();

};

class cfpsources_string : public cfparameter
{
public:
	cfpsources_string();
	~cfpsources_string();

};

class cfp$persisted_boolean : public cfparameter
{
public:
	cfp$persisted_boolean();
	~cfp$persisted_boolean();

};

class cfpparam_any : public cfparameter
{
public:
	cfpparam_any();
	~cfpparam_any();

};

class cfpword_string : public cfparameter
{
public:
	cfpword_string();
	~cfpword_string();

};

class cfpreturncount_boolean : public cfparameter
{
public:
	cfpreturncount_boolean();
	~cfpreturncount_boolean();

};

class cfpsql_string : public cfparameter
{
public:
	cfpsql_string();
	~cfpsql_string();

};

class cfptagvalue_string : public cfparameter
{
public:
	cfptagvalue_string();
	~cfptagvalue_string();

};

class cfpback_boolean : public cfparameter
{
public:
	cfpback_boolean();
	~cfpback_boolean();

};

class cfptemplate_string : public cfparameter
{
public:
	cfptemplate_string();
	~cfptemplate_string();

};

class cfplayout_any : public cfparameter
{
public:
	cfplayout_any();
	~cfplayout_any();

};

class cfp$showdebuginformation_any : public cfparameter
{
public:
	cfp$showdebuginformation_any();
	~cfp$showdebuginformation_any();

};

class cfppartial_string : public cfparameter
{
public:
	cfppartial_string();
	~cfppartial_string();

};

class cfptext_any : public cfparameter
{
public:
	cfptext_any();
	~cfptext_any();

};

class cfpoptions_any : public cfparameter
{
public:
	cfpoptions_any();
	~cfpoptions_any();

};

class cfpvaluefield_string : public cfparameter
{
public:
	cfpvaluefield_string();
	~cfpvaluefield_string();

};

class cfptextfield_string : public cfparameter
{
public:
	cfptextfield_string();
	~cfptextfield_string();

};

class cfpmultiple_boolean : public cfparameter
{
public:
	cfpmultiple_boolean();
	~cfpmultiple_boolean();

};

class cfptemplates_string : public cfparameter
{
public:
	cfptemplates_string();
	~cfptemplates_string();

};

class cfpfrom_string : public cfparameter
{
public:
	cfpfrom_string();
	~cfpfrom_string();

};

class cfpto_string : public cfparameter
{
public:
	cfpto_string();
	~cfpto_string();

};

class cfpsubject_string : public cfparameter
{
public:
	cfpsubject_string();
	~cfpsubject_string();

};

class cfplayouts_any : public cfparameter
{
public:
	cfplayouts_any();
	~cfplayouts_any();

};

class cfpdetectmultipart_boolean : public cfparameter
{
public:
	cfpdetectmultipart_boolean();
	~cfpdetectmultipart_boolean();

};

class cfpdisposition_string : public cfparameter
{
public:
	cfpdisposition_string();
	~cfpdisposition_string();

};

class cfpmethod_string : public cfparameter
{
public:
	cfpmethod_string();
	~cfpmethod_string();

};

class cfpmultipart_boolean : public cfparameter
{
public:
	cfpmultipart_boolean();
	~cfpmultipart_boolean();

};

class cfpspamprotection_boolean : public cfparameter
{
public:
	cfpspamprotection_boolean();
	~cfpspamprotection_boolean();

};

class cfpmedia_string : public cfparameter
{
public:
	cfpmedia_string();
	~cfpmedia_string();

};

class cfpimage_string : public cfparameter
{
public:
	cfpimage_string();
	~cfpimage_string();

};

class cfpdisable_any : public cfparameter
{
public:
	cfpdisable_any();
	~cfpdisable_any();

};

class cfpcontent_string : public cfparameter
{
public:
	cfpcontent_string();
	~cfpcontent_string();

};

class cfpif_string : public cfparameter
{
public:
	cfpif_string();
	~cfpif_string();

};

class cfpunless_string : public cfparameter
{
public:
	cfpunless_string();
	~cfpunless_string();

};

class cfpproperties_string : public cfparameter
{
public:
	cfpproperties_string();
	~cfpproperties_string();

};

class cfpwhen_string : public cfparameter
{
public:
	cfpwhen_string();
	~cfpwhen_string();

};

class cfpallowblank_boolean : public cfparameter
{
public:
	cfpallowblank_boolean();
	~cfpallowblank_boolean();

};

class cfpregex_string : public cfparameter
{
public:
	cfpregex_string();
	~cfpregex_string();

};

class cfpexactly_numeric : public cfparameter
{
public:
	cfpexactly_numeric();
	~cfpexactly_numeric();

};

class cfpmaximum_numeric : public cfparameter
{
public:
	cfpmaximum_numeric();
	~cfpmaximum_numeric();

};

class cfpminimum_numeric : public cfparameter
{
public:
	cfpminimum_numeric();
	~cfpminimum_numeric();

};

class cfpwithin_string : public cfparameter
{
public:
	cfpwithin_string();
	~cfpwithin_string();

};

class cfponlyinteger_boolean : public cfparameter
{
public:
	cfponlyinteger_boolean();
	~cfponlyinteger_boolean();

};

class cfppost_any : public cfparameter
{
public:
	cfppost_any();
	~cfppost_any();

};

class cfpget_any : public cfparameter
{
public:
	cfpget_any();
	~cfpget_any();

};

class cfpajax_any : public cfparameter
{
public:
	cfpajax_any();
	~cfpajax_any();

};

class cfpcookie_string : public cfparameter
{
public:
	cfpcookie_string();
	~cfpcookie_string();

};

class cfpsession_string : public cfparameter
{
public:
	cfpsession_string();
	~cfpsession_string();

};

class cfphandler_string : public cfparameter
{
public:
	cfphandler_string();
	~cfphandler_string();

};


#endif



class cffabs : public cffunction
{
public:
	cffabs() {
		name = "Abs";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
	}

};


class cffacos : public cffunction
{
public:
	cffacos() {
		name = "ACos";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
	}

};


class cffaddsoaprequestheader : public cffunction
{
public:
	cffaddsoaprequestheader() {
		name = "AddSOAPRequestHeader";
		returntype = T_BOOLEAN;

		parameters[0] = cfpwebservice_string();
		parameterrequired[0] = true;
		parameters[1] = cfpnamespace_string();
		parameterrequired[1] = true;
		parameters[2] = cfpname_string();
		parameterrequired[2] = true;
		parameters[3] = cfpvalue_string();
		parameterrequired[3] = true;
		parameters[4] = cfpmustunderstand_boolean();
		parameterrequired[4] = true;
	}

};


class cffaddsoapresponseheader : public cffunction
{
public:
	cffaddsoapresponseheader() {
		name = "AddSOAPResponseHeader";
		returntype = T_BOOLEAN;

		parameters[0] = cfpnamespace_string();
		parameterrequired[0] = true;
		parameters[1] = cfpname_string();
		parameterrequired[1] = true;
		parameters[2] = cfpvalue_string();
		parameterrequired[2] = true;
		parameters[3] = cfpmustunderstand_boolean();
		parameterrequired[3] = false;
	}

};


class cffajaxlink : public cffunction
{
public:
	cffajaxlink() {
		name = "AjaxLink";
		returntype = T_VOID;

		parameters[0] = cfpurl_string();
		parameterrequired[0] = true;
	}

};


class cffajaxonload : public cffunction
{
public:
	cffajaxonload() {
		name = "AjaxOnLoad";
		returntype = T_VOID;

		parameters[0] = cfpfunctionname_string();
		parameterrequired[0] = true;
	}

};


class cffapplicationstop : public cffunction
{
public:
	cffapplicationstop() {
		name = "ApplicationStop";
		returntype = T_VOID;

		parameters[0] = cfpfunctionname_string();
		parameterrequired[0] = true;
	}

};


class cffarrayappend : public cffunction
{
public:
	cffarrayappend() {
		name = "ArrayAppend";
		returntype = T_BOOLEAN;

		parameters[0] = cfparray_array();
		parameterrequired[0] = true;
		parameters[1] = cfpvalue_any();
		parameterrequired[1] = true;
	}

};


class cffarrayavg : public cffunction
{
public:
	cffarrayavg() {
		name = "ArrayAvg";
		returntype = T_NUMERIC;

		parameters[0] = cfparray_array();
		parameterrequired[0] = true;
	}

};


class cffarrayclear : public cffunction
{
public:
	cffarrayclear() {
		name = "ArrayClear";
		returntype = T_BOOLEAN;

		parameters[0] = cfparray_array();
		parameterrequired[0] = true;
	}

};


class cffarraycontains : public cffunction
{
public:
	cffarraycontains() {
		name = "ArrayContains";
		returntype = T_BOOLEAN;

		parameters[0] = cfparray_array();
		parameterrequired[0] = true;
		parameters[1] = cfpobject_any();
		parameterrequired[1] = true;
	}

};


class cffarraydelete : public cffunction
{
public:
	cffarraydelete() {
		name = "ArrayDelete";
		returntype = T_BOOLEAN;

		parameters[0] = cfparray_array();
		parameterrequired[0] = true;
		parameters[1] = cfpobject_any();
		parameterrequired[1] = true;
	}

};


class cffarraydeleteat : public cffunction
{
public:
	cffarraydeleteat() {
		name = "ArrayDeleteAt";
		returntype = T_BOOLEAN;

		parameters[0] = cfparray_array();
		parameterrequired[0] = true;
		parameters[1] = cfpposition_numeric();
		parameterrequired[1] = true;
	}

};


class cffarrayfind : public cffunction
{
public:
	cffarrayfind() {
		name = "ArrayFind";
		returntype = T_NUMERIC;

		parameters[0] = cfparray_array();
		parameterrequired[0] = true;
		parameters[1] = cfpobject_variablename();
		parameterrequired[1] = true;
	}

};


class cffarrayfindnocase : public cffunction
{
public:
	cffarrayfindnocase() {
		name = "ArrayFindNoCase";
		returntype = T_NUMERIC;

		parameters[0] = cfparray_array();
		parameterrequired[0] = true;
		parameters[1] = cfpobject_variablename();
		parameterrequired[1] = true;
	}

};


class cffarrayinsertat : public cffunction
{
public:
	cffarrayinsertat() {
		name = "ArrayInsertAt";
		returntype = T_BOOLEAN;

		parameters[0] = cfparray_array();
		parameterrequired[0] = true;
		parameters[1] = cfpposition_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpvalue_any();
		parameterrequired[2] = true;
	}

};


class cffarrayisdefined : public cffunction
{
public:
	cffarrayisdefined() {
		name = "ArrayIsDefined";
		returntype = T_BOOLEAN;

		parameters[0] = cfparray_string();
		parameterrequired[0] = true;
		parameters[1] = cfpelementindex_numeric();
		parameterrequired[1] = true;
	}

};


class cffarrayisempty : public cffunction
{
public:
	cffarrayisempty() {
		name = "ArrayIsEmpty";
		returntype = T_BOOLEAN;

		parameters[0] = cfparray_array();
		parameterrequired[0] = true;
	}

};


class cffarraylen : public cffunction
{
public:
	cffarraylen() {
		name = "ArrayLen";
		returntype = T_NUMERIC;

		parameters[0] = cfparray_array();
		parameterrequired[0] = true;
	}

};


class cffarraymax : public cffunction
{
public:
	cffarraymax() {
		name = "ArrayMax";
		returntype = T_NUMERIC;

		parameters[0] = cfparray_array();
		parameterrequired[0] = true;
	}

};


class cffarraymin : public cffunction
{
public:
	cffarraymin() {
		name = "ArrayMin";
		returntype = T_NUMERIC;

		parameters[0] = cfparray_array();
		parameterrequired[0] = true;
	}

};


class cffarraynew : public cffunction
{
public:
	cffarraynew() {
		name = "ArrayNew";
		returntype = T_ARRAY;

		parameters[0] = cfpdimension_numeric();
		parameterrequired[0] = true;
	}

};


class cffarrayprepend : public cffunction
{
public:
	cffarrayprepend() {
		name = "ArrayPrepend";
		returntype = T_BOOLEAN;

		parameters[0] = cfparray_array();
		parameterrequired[0] = true;
		parameters[1] = cfpvalue_object();
		parameterrequired[1] = true;
	}

};


class cffarrayresize : public cffunction
{
public:
	cffarrayresize() {
		name = "ArrayResize";
		returntype = T_BOOLEAN;

		parameters[0] = cfparray_array();
		parameterrequired[0] = true;
		parameters[1] = cfpsize_numeric();
		parameterrequired[1] = true;
	}

};


class cffarrayset : public cffunction
{
public:
	cffarrayset() {
		name = "ArraySet";
		returntype = T_BOOLEAN;

		parameters[0] = cfparray_array();
		parameterrequired[0] = true;
		parameters[1] = cfpstart_pos_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpend_pos_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpvalue_object();
		parameterrequired[3] = true;
	}

};


class cffarraysort : public cffunction
{
public:
	cffarraysort() {
		name = "ArraySort";
		returntype = T_BOOLEAN;

		parameters[0] = cfparray_array();
		parameterrequired[0] = true;
		parameters[1] = cfpsort_type_string();
		parameterrequired[1] = true;
		parameters[2] = cfpsort_order_string();
		parameterrequired[2] = false;
	}

};


class cffarraysum : public cffunction
{
public:
	cffarraysum() {
		name = "ArraySum";
		returntype = T_NUMERIC;

		parameters[0] = cfparray_array();
		parameterrequired[0] = true;
	}

};


class cffarrayswap : public cffunction
{
public:
	cffarrayswap() {
		name = "ArraySwap";
		returntype = T_BOOLEAN;

		parameters[0] = cfparray_array();
		parameterrequired[0] = true;
		parameters[1] = cfpposition1_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpposition2_numeric();
		parameterrequired[2] = true;
	}

};


class cffarraytolist : public cffunction
{
public:
	cffarraytolist() {
		name = "ArrayToList";
		returntype = T_STRING;

		parameters[0] = cfparray_array();
		parameterrequired[0] = true;
		parameters[1] = cfpdelimiter_string();
		parameterrequired[1] = false;
	}

};


class cffasc : public cffunction
{
public:
	cffasc() {
		name = "Asc";
		returntype = T_NUMERIC;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
	}

};


class cffasin : public cffunction
{
public:
	cffasin() {
		name = "ASin";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
	}

};


class cffatn : public cffunction
{
public:
	cffatn() {
		name = "Atn";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
	}

};


class cffbinarydecode : public cffunction
{
public:
	cffbinarydecode() {
		name = "BinaryDecode";
		returntype = T_BINARY;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpbinaryencoding_string();
		parameterrequired[1] = true;
	}

};


class cffbinaryencode : public cffunction
{
public:
	cffbinaryencode() {
		name = "BinaryEncode";
		returntype = T_STRING;

		parameters[0] = cfpbinarydata_binary();
		parameterrequired[0] = true;
		parameters[1] = cfpencoding_string();
		parameterrequired[1] = true;
	}

};


class cffbitand : public cffunction
{
public:
	cffbitand() {
		name = "BitAnd";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber1_numeric();
		parameterrequired[0] = true;
		parameters[1] = cfpnumber2_numeric();
		parameterrequired[1] = true;
	}

};


class cffbitmaskclear : public cffunction
{
public:
	cffbitmaskclear() {
		name = "BitMaskClear";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
		parameters[1] = cfpstart_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfplength_numeric();
		parameterrequired[2] = true;
	}

};


class cffbitmaskread : public cffunction
{
public:
	cffbitmaskread() {
		name = "BitMaskRead";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
		parameters[1] = cfpstart_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfplength_numeric();
		parameterrequired[2] = true;
	}

};


class cffbitmaskset : public cffunction
{
public:
	cffbitmaskset() {
		name = "BitMaskSet";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
		parameters[1] = cfpmask_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpstart_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfplength_numeric();
		parameterrequired[3] = true;
	}

};


class cffbitnot : public cffunction
{
public:
	cffbitnot() {
		name = "BitNot";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
	}

};


class cffbitor : public cffunction
{
public:
	cffbitor() {
		name = "BitOr";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber1_numeric();
		parameterrequired[0] = true;
		parameters[1] = cfpnumber2_numeric();
		parameterrequired[1] = true;
	}

};


class cffbitshln : public cffunction
{
public:
	cffbitshln() {
		name = "BitSHLN";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
		parameters[1] = cfpcount_numeric();
		parameterrequired[1] = true;
	}

};


class cffbitshrn : public cffunction
{
public:
	cffbitshrn() {
		name = "BitSHRN";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
		parameters[1] = cfpcount_numeric();
		parameterrequired[1] = true;
	}

};


class cffbitxor : public cffunction
{
public:
	cffbitxor() {
		name = "BitXor";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber1_numeric();
		parameterrequired[0] = true;
		parameters[1] = cfpnumber2_numeric();
		parameterrequired[1] = true;
	}

};


class cffcacheget : public cffunction
{
public:
	cffcacheget() {
		name = "CacheGet";
		returntype = T_VOID;

		parameters[0] = cfpid_string();
		parameterrequired[0] = true;
	}

};


class cffcachegetallids : public cffunction
{
public:
	cffcachegetallids() {
		name = "CacheGetAllIds";
		returntype = T_VOID;

		parameters[0] = cfpid_string();
		parameterrequired[0] = true;
	}

};


class cffcachegetmetadata : public cffunction
{
public:
	cffcachegetmetadata() {
		name = "CacheGetMetadata";
		returntype = T_STRUCT;

		parameters[0] = cfpid_string();
		parameterrequired[0] = true;
	}

};


class cffcachegetproperties : public cffunction
{
public:
	cffcachegetproperties() {
		name = "CacheGetProperties";
		returntype = T_STRUCT;

		parameters[0] = cfptype_string();
		parameterrequired[0] = true;
	}

};


class cffcacheput : public cffunction
{
public:
	cffcacheput() {
		name = "CachePut";
		returntype = T_VOID;

		parameters[0] = cfpid_string();
		parameterrequired[0] = true;
		parameters[1] = cfpvalue_string();
		parameterrequired[1] = true;
		parameters[2] = cfptimespan_datetime();
		parameterrequired[2] = false;
		parameters[3] = cfpideltime_datetime();
		parameterrequired[3] = false;
	}

};


class cffcacheremove : public cffunction
{
public:
	cffcacheremove() {
		name = "CacheRemove";
		returntype = T_VOID;

		parameters[0] = cfpids_string();
		parameterrequired[0] = true;
		parameters[1] = cfpthrowonerror_boolean();
		parameterrequired[1] = false;
	}

};


class cffcachesetproperties : public cffunction
{
public:
	cffcachesetproperties() {
		name = "CacheSetProperties";
		returntype = T_VOID;

		parameters[0] = cfppropstruct_struct();
		parameterrequired[0] = true;
	}

};


class cffceiling : public cffunction
{
public:
	cffceiling() {
		name = "Ceiling";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
	}

};


class cffcharsetdecode : public cffunction
{
public:
	cffcharsetdecode() {
		name = "CharsetDecode";
		returntype = T_BINARY;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpencoding_string();
		parameterrequired[1] = true;
	}

};


class cffcharsetencode : public cffunction
{
public:
	cffcharsetencode() {
		name = "CharsetEncode";
		returntype = T_BINARY;

		parameters[0] = cfpbinaryobject_binary();
		parameterrequired[0] = true;
		parameters[1] = cfpencoding_string();
		parameterrequired[1] = true;
	}

};


class cffchr : public cffunction
{
public:
	cffchr() {
		name = "Chr";
		returntype = T_STRING;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
	}

};


class cffcjustify : public cffunction
{
public:
	cffcjustify() {
		name = "CJustify";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfplength_numeric();
		parameterrequired[1] = true;
	}

};


class cffcompare : public cffunction
{
public:
	cffcompare() {
		name = "Compare";
		returntype = T_NUMERIC;

		parameters[0] = cfpstring1_string();
		parameterrequired[0] = true;
		parameters[1] = cfpstring2_string();
		parameterrequired[1] = true;
	}

};


class cffcomparenocase : public cffunction
{
public:
	cffcomparenocase() {
		name = "CompareNoCase";
		returntype = T_NUMERIC;

		parameters[0] = cfpstring1_string();
		parameterrequired[0] = true;
		parameters[1] = cfpstring2_string();
		parameterrequired[1] = true;
	}

};


class cffcos : public cffunction
{
public:
	cffcos() {
		name = "Cos";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
	}

};


class cffcreatedate : public cffunction
{
public:
	cffcreatedate() {
		name = "CreateDate";
		returntype = T_DATETIME;

		parameters[0] = cfpyear_numeric();
		parameterrequired[0] = true;
		parameters[1] = cfpmonth_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpday_numeric();
		parameterrequired[2] = true;
	}

};


class cffcreatedatetime : public cffunction
{
public:
	cffcreatedatetime() {
		name = "CreateDateTime";
		returntype = T_DATETIME;

		parameters[0] = cfpyear_numeric();
		parameterrequired[0] = true;
		parameters[1] = cfpmonth_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpday_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfphour_numeric();
		parameterrequired[3] = true;
		parameters[4] = cfpminute_numeric();
		parameterrequired[4] = true;
		parameters[5] = cfpsecond_numeric();
		parameterrequired[5] = true;
	}

};


class cffcreateobject : public cffunction
{
public:
	cffcreateobject() {
		name = "CreateObject";
		returntype = T_OBJECT;

		parameters[0] = cfptype_string();
		parameterrequired[0] = true;
		parameters[1] = cfpcontext_string();
		parameterrequired[1] = true;
		parameters[2] = cfpclass_string();
		parameterrequired[2] = true;
		parameters[3] = cfplocale_string();
		parameterrequired[3] = true;
		parameters[4] = cfpservername_string();
		parameterrequired[4] = true;
		parameters[5] = cfpcomponent_name_string();
		parameterrequired[5] = true;
		parameters[6] = cfpurltowsdl_string();
		parameterrequired[6] = true;
		parameters[7] = cfpportname_string();
		parameterrequired[7] = false;
	}

};


class cffcreateodbcdate : public cffunction
{
public:
	cffcreateodbcdate() {
		name = "CreateODBCDate";
		returntype = T_ODBCDATE;

		parameters[0] = cfpdate_datetime();
		parameterrequired[0] = true;
	}

};


class cffcreateodbcdatetime : public cffunction
{
public:
	cffcreateodbcdatetime() {
		name = "CreateODBCDateTime";
		returntype = T_ODBCDATETIME;

		parameters[0] = cfpdate_datetime();
		parameterrequired[0] = true;
	}

};


class cffcreateodbctime : public cffunction
{
public:
	cffcreateodbctime() {
		name = "CreateODBCTime";
		returntype = T_ODBCTIME;

		parameters[0] = cfpdate_datetime();
		parameterrequired[0] = true;
	}

};


class cffcreatetime : public cffunction
{
public:
	cffcreatetime() {
		name = "CreateTime";
		returntype = T_DATETIME;

		parameters[0] = cfphour_numeric();
		parameterrequired[0] = true;
		parameters[1] = cfpminute_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpsecond_numeric();
		parameterrequired[2] = true;
	}

};


class cffcreatetimespan : public cffunction
{
public:
	cffcreatetimespan() {
		name = "CreateTimeSpan";
		returntype = T_DATETIME;

		parameters[0] = cfpdays_numeric();
		parameterrequired[0] = true;
		parameters[1] = cfphours_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpminutes_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpseconds_numeric();
		parameterrequired[3] = true;
	}

};


class cffcreateuuid : public cffunction
{
public:
	cffcreateuuid() {
		name = "CreateUUID";
		returntype = T_STRING;

		parameters[0] = cfpdays_numeric();
		parameterrequired[0] = true;
		parameters[1] = cfphours_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpminutes_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpseconds_numeric();
		parameterrequired[3] = true;
	}

};


class cffdateadd : public cffunction
{
public:
	cffdateadd() {
		name = "DateAdd";
		returntype = T_DATETIME;

		parameters[0] = cfpdatepart_string();
		parameterrequired[0] = true;
		parameters[1] = cfpnumber_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpdate_datetime();
		parameterrequired[2] = true;
	}

};


class cffdatecompare : public cffunction
{
public:
	cffdatecompare() {
		name = "DateCompare";
		returntype = T_NUMERIC;

		parameters[0] = cfpdate1_datetime();
		parameterrequired[0] = true;
		parameters[1] = cfpdate2_datetime();
		parameterrequired[1] = true;
		parameters[2] = cfpdatepart_string();
		parameterrequired[2] = false;
	}

};


class cffdateconvert : public cffunction
{
public:
	cffdateconvert() {
		name = "DateConvert";
		returntype = T_DATETIME;

		parameters[0] = cfptype_string();
		parameterrequired[0] = true;
		parameters[1] = cfpdate_datetime();
		parameterrequired[1] = true;
	}

};


class cffdatediff : public cffunction
{
public:
	cffdatediff() {
		name = "DateDiff";
		returntype = T_NUMERIC;

		parameters[0] = cfpdatepart_string();
		parameterrequired[0] = true;
		parameters[1] = cfpdate1_datetime();
		parameterrequired[1] = true;
		parameters[2] = cfpdate2_datetime();
		parameterrequired[2] = true;
	}

};


class cffdateformat : public cffunction
{
public:
	cffdateformat() {
		name = "DateFormat";
		returntype = T_STRING;

		parameters[0] = cfpdate_datetime();
		parameterrequired[0] = true;
		parameters[1] = cfpmask_string();
		parameterrequired[1] = false;
	}

};


class cffdatepart : public cffunction
{
public:
	cffdatepart() {
		name = "DatePart";
		returntype = T_NUMERIC;

		parameters[0] = cfpdatepart_string();
		parameterrequired[0] = true;
		parameters[1] = cfpdate_datetime();
		parameterrequired[1] = true;
	}

};


class cffday : public cffunction
{
public:
	cffday() {
		name = "Day";
		returntype = T_NUMERIC;

		parameters[0] = cfpdate_datetime();
		parameterrequired[0] = true;
	}

};


class cffdayofweek : public cffunction
{
public:
	cffdayofweek() {
		name = "DayOfWeek";
		returntype = T_NUMERIC;

		parameters[0] = cfpdate_datetime();
		parameterrequired[0] = true;
	}

};


class cffdayofweekasstring : public cffunction
{
public:
	cffdayofweekasstring() {
		name = "DayOfWeekAsString";
		returntype = T_STRING;

		parameters[0] = cfpday_of_week_numeric();
		parameterrequired[0] = true;
	}

};


class cffdayofyear : public cffunction
{
public:
	cffdayofyear() {
		name = "DayOfYear";
		returntype = T_NUMERIC;

		parameters[0] = cfpdate_datetime();
		parameterrequired[0] = true;
	}

};


class cffdaysinmonth : public cffunction
{
public:
	cffdaysinmonth() {
		name = "DaysInMonth";
		returntype = T_NUMERIC;

		parameters[0] = cfpdate_datetime();
		parameterrequired[0] = true;
	}

};


class cffdaysinyear : public cffunction
{
public:
	cffdaysinyear() {
		name = "DaysInYear";
		returntype = T_NUMERIC;

		parameters[0] = cfpdate_datetime();
		parameterrequired[0] = true;
	}

};


class cffde : public cffunction
{
public:
	cffde() {
		name = "DE";
		returntype = T_OBJECT;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
	}

};


class cffdecimalformat : public cffunction
{
public:
	cffdecimalformat() {
		name = "DecimalFormat";
		returntype = T_STRING;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
	}

};


class cffdecrementvalue : public cffunction
{
public:
	cffdecrementvalue() {
		name = "DecrementValue";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
	}

};


class cffdecrypt : public cffunction
{
public:
	cffdecrypt() {
		name = "Decrypt";
		returntype = T_STRING;

		parameters[0] = cfpencrypted_string_string();
		parameterrequired[0] = true;
		parameters[1] = cfpkey_string();
		parameterrequired[1] = true;
		parameters[2] = cfpalgorithm_string();
		parameterrequired[2] = false;
		parameters[3] = cfpencoding_string();
		parameterrequired[3] = false;
		parameters[4] = cfpivorsalt_binary();
		parameterrequired[4] = false;
		parameters[5] = cfpiterations_numeric();
		parameterrequired[5] = false;
	}

};


class cffdecryptbinary : public cffunction
{
public:
	cffdecryptbinary() {
		name = "DecryptBinary";
		returntype = T_STRING;

		parameters[0] = cfpbytes_string();
		parameterrequired[0] = true;
		parameters[1] = cfpkey_string();
		parameterrequired[1] = true;
		parameters[2] = cfpalgorithm_string();
		parameterrequired[2] = false;
		parameters[3] = cfpivorsalt_binary();
		parameterrequired[3] = false;
		parameters[4] = cfpiterations_numeric();
		parameterrequired[4] = false;
	}

};


class cffdeleteclientvariable : public cffunction
{
public:
	cffdeleteclientvariable() {
		name = "DeleteClientVariable";
		returntype = T_BOOLEAN;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
	}

};


class cffdeserializejson : public cffunction
{
public:
	cffdeserializejson() {
		name = "DeserializeJSON";
		returntype = T_ANY;

		parameters[0] = cfpjsonvar_string();
		parameterrequired[0] = true;
		parameters[1] = cfpstrictmapping_boolean();
		parameterrequired[1] = false;
	}

};


class cffdirectorycreate : public cffunction
{
public:
	cffdirectorycreate() {
		name = "DirectoryCreate";
		returntype = T_VOID;

		parameters[0] = cfppath_string();
		parameterrequired[0] = true;
	}

};


class cffdirectorydelete : public cffunction
{
public:
	cffdirectorydelete() {
		name = "DirectoryDelete";
		returntype = T_VOID;

		parameters[0] = cfppath_string();
		parameterrequired[0] = true;
		parameters[1] = cfprecurse_boolean();
		parameterrequired[1] = true;
	}

};


class cffdirectoryexists : public cffunction
{
public:
	cffdirectoryexists() {
		name = "DirectoryExists";
		returntype = T_BOOLEAN;

		parameters[0] = cfpabsolute_path_string();
		parameterrequired[0] = true;
	}

};


class cffdirectorylist : public cffunction
{
public:
	cffdirectorylist() {
		name = "DirectoryList";
		returntype = T_OBJECT;

		parameters[0] = cfppath_string();
		parameterrequired[0] = true;
		parameters[1] = cfprecurse_boolean();
		parameterrequired[1] = false;
		parameters[2] = cfpreturntype_string();
		parameterrequired[2] = false;
		parameters[3] = cfpfilter_string();
		parameterrequired[3] = false;
		parameters[4] = cfpsort_string();
		parameterrequired[4] = false;
	}

};


class cffdirectoryrename : public cffunction
{
public:
	cffdirectoryrename() {
		name = "DirectoryRename";
		returntype = T_VOID;

		parameters[0] = cfppath_string();
		parameterrequired[0] = true;
		parameters[1] = cfpnewpath_string();
		parameterrequired[1] = true;
	}

};


class cffdollarformat : public cffunction
{
public:
	cffdollarformat() {
		name = "DollarFormat";
		returntype = T_STRING;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
	}

};


class cffdotnettocftype : public cffunction
{
public:
	cffdotnettocftype() {
		name = "DotNetToCFType";
		returntype = T_ANY;

		parameters[0] = cfpvariable_name_variablename();
		parameterrequired[0] = true;
	}

};


class cffduplicate : public cffunction
{
public:
	cffduplicate() {
		name = "Duplicate";
		returntype = T_OBJECT;

		parameters[0] = cfpvariable_object();
		parameterrequired[0] = true;
	}

};


class cffencrypt : public cffunction
{
public:
	cffencrypt() {
		name = "Encrypt";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpkey_string();
		parameterrequired[1] = true;
		parameters[2] = cfpalgorithm_string();
		parameterrequired[2] = false;
		parameters[3] = cfpencoding_string();
		parameterrequired[3] = false;
		parameters[4] = cfpivorsalt_binary();
		parameterrequired[4] = false;
		parameters[5] = cfpiterations_numeric();
		parameterrequired[5] = false;
	}

};


class cffencryptbinary : public cffunction
{
public:
	cffencryptbinary() {
		name = "EncryptBinary";
		returntype = T_STRING;

		parameters[0] = cfpbytes_string();
		parameterrequired[0] = true;
		parameters[1] = cfpkey_string();
		parameterrequired[1] = true;
		parameters[2] = cfpalgorithm_string();
		parameterrequired[2] = false;
		parameters[3] = cfpivorsalt_binary();
		parameterrequired[3] = false;
		parameters[4] = cfpiterations_numeric();
		parameterrequired[4] = false;
	}

};


class cffentitydelete : public cffunction
{
public:
	cffentitydelete() {
		name = "EntityDelete";
		returntype = T_VOID;

		parameters[0] = cfpentity_variablename();
		parameterrequired[0] = true;
	}

};


class cffentityload : public cffunction
{
public:
	cffentityload() {
		name = "EntityLoad";
		returntype = T_VOID;

		parameters[0] = cfpentityname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpfiltercriteria_string();
		parameterrequired[1] = true;
		parameters[2] = cfpunique_string();
		parameterrequired[2] = false;
		parameters[3] = cfpsortorder_string();
		parameterrequired[3] = false;
		parameters[4] = cfpoptions_string();
		parameterrequired[4] = false;
	}

};
/*

class cffentityload : public cffunction
{
public:
cffentityload()
{
name = "EntityLoad";
returntype = T_VOID;

parameters[0] = cfpentityname_string();
parameterrequired[0] = true;
parameters[1] = cfpid_string();
parameterrequired[1] = true;
parameters[2] = cfpunique_string();
parameterrequired[2] = false;
}

};
*/

class cffentityloadbyexample : public cffunction
{
public:
	cffentityloadbyexample() {
		name = "EntityLoadByExample";
		returntype = T_OBJECT;

		parameters[0] = cfpsampleentity_string();
		parameterrequired[0] = true;
		parameters[1] = cfpunique_boolean();
		parameterrequired[1] = false;
	}

};


class cffentityloadbypk : public cffunction
{
public:
	cffentityloadbypk() {
		name = "EntityLoadByPK";
		returntype = T_OBJECT;

		parameters[0] = cfpentityname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpid_object();
		parameterrequired[1] = true;
	}

};


class cffentitymerge : public cffunction
{
public:
	cffentitymerge() {
		name = "EntityMerge";
		returntype = T_OBJECT;

		parameters[0] = cfpentity_variablename();
		parameterrequired[0] = true;
	}

};


class cffentitynew : public cffunction
{
public:
	cffentitynew() {
		name = "EntityNew";
		returntype = T_OBJECT;

		parameters[0] = cfpentityname_string();
		parameterrequired[0] = true;
	}

};


class cffentityreload : public cffunction
{
public:
	cffentityreload() {
		name = "EntityReload";
		returntype = T_VOID;

		parameters[0] = cfpentity_variablename();
		parameterrequired[0] = true;
	}

};


class cffentitysave : public cffunction
{
public:
	cffentitysave() {
		name = "EntitySave";
		returntype = T_VOID;

		parameters[0] = cfpentity_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpforceinsert_boolean();
		parameterrequired[1] = false;
	}

};


class cffentitytoquery : public cffunction
{
public:
	cffentitytoquery() {
		name = "EntitytoQuery";
		returntype = T_QUERY;

		parameters[0] = cfporm_object_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpentity_name_string();
		parameterrequired[1] = false;
	}

};


class cffevaluate : public cffunction
{
public:
	cffevaluate() {
		name = "Evaluate";
		returntype = T_OBJECT;

		parameters[0] = cfpexpression1_string();
		parameterrequired[0] = true;
		parameters[1] = cfpexpression2_string();
		parameterrequired[1] = false;
		parameters[2] = cfpexpressionn_string();
		parameterrequired[2] = false;
	}

};


class cffexp : public cffunction
{
public:
	cffexp() {
		name = "Exp";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
	}

};


class cffexpandpath : public cffunction
{
public:
	cffexpandpath() {
		name = "ExpandPath";
		returntype = T_STRING;

		parameters[0] = cfprelative_path_string();
		parameterrequired[0] = true;
	}

};


class cfffileclose : public cffunction
{
public:
	cfffileclose() {
		name = "FileClose";
		returntype = T_VOID;

		parameters[0] = cfpfileobj_variablename();
		parameterrequired[0] = true;
	}

};


class cfffilecopy : public cffunction
{
public:
	cfffilecopy() {
		name = "FileCopy";
		returntype = T_VOID;

		parameters[0] = cfpsource_string();
		parameterrequired[0] = true;
		parameters[1] = cfpdestination_string();
		parameterrequired[1] = true;
	}

};


class cfffiledelete : public cffunction
{
public:
	cfffiledelete() {
		name = "FileDelete";
		returntype = T_VOID;

		parameters[0] = cfpfilepath_string();
		parameterrequired[0] = true;
	}

};


class cfffileexists : public cffunction
{
public:
	cfffileexists() {
		name = "FileExists";
		returntype = T_BOOLEAN;

		parameters[0] = cfppath_string();
		parameterrequired[0] = true;
	}

};


class cfffileiseof : public cffunction
{
public:
	cfffileiseof() {
		name = "FileIsEOF";
		returntype = T_BOOLEAN;

		parameters[0] = cfpfileobject_object();
		parameterrequired[0] = true;
	}

};


class cfffilemove : public cffunction
{
public:
	cfffilemove() {
		name = "FileMove";
		returntype = T_VOID;

		parameters[0] = cfpsource_string();
		parameterrequired[0] = true;
		parameters[1] = cfpdestination_string();
		parameterrequired[1] = true;
	}

};


class cfffileopen : public cffunction
{
public:
	cfffileopen() {
		name = "FileOpen";
		returntype = T_OBJECT;

		parameters[0] = cfpfilepath_string();
		parameterrequired[0] = true;
		parameters[1] = cfpmode_string();
		parameterrequired[1] = false;
		parameters[2] = cfpcharset_string();
		parameterrequired[2] = false;
	}

};


class cfffileread : public cffunction
{
public:
	cfffileread() {
		name = "FileRead";
		returntype = T_STRING;

		parameters[0] = cfpfilepath_string();
		parameterrequired[0] = true;
		parameters[1] = cfpcharset_string();
		parameterrequired[1] = false;
	}

};


class cfffilereadbinary : public cffunction
{
public:
	cfffilereadbinary() {
		name = "FileReadBinary";
		returntype = T_VOID;

		parameters[0] = cfpfilepath_string();
		parameterrequired[0] = true;
	}

};


class cfffilereadline : public cffunction
{
public:
	cfffilereadline() {
		name = "FileReadLine";
		returntype = T_STRING;

		parameters[0] = cfpfileobj_object();
		parameterrequired[0] = true;
	}

};


class cfffileseek : public cffunction
{
public:
	cfffileseek() {
		name = "FileSeek";
		returntype = T_VOID;

		parameters[0] = cfpfile_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpposition_numeric();
		parameterrequired[1] = true;
	}

};


class cfffilesetaccessmode : public cffunction
{
public:
	cfffilesetaccessmode() {
		name = "FileSetAccessMode";
		returntype = T_VOID;

		parameters[0] = cfpfilepath_string();
		parameterrequired[0] = true;
		parameters[1] = cfpmode_string();
		parameterrequired[1] = true;
	}

};


class cfffilesetattribute : public cffunction
{
public:
	cfffilesetattribute() {
		name = "FileSetAttribute";
		returntype = T_VOID;

		parameters[0] = cfpfilepath_string();
		parameterrequired[0] = true;
		parameters[1] = cfpattribute_string();
		parameterrequired[1] = true;
	}

};


class cfffilesetlastmodified : public cffunction
{
public:
	cfffilesetlastmodified() {
		name = "FileSetLastModified";
		returntype = T_VOID;

		parameters[0] = cfpfilepath_string();
		parameterrequired[0] = true;
		parameters[1] = cfpdate_datetime();
		parameterrequired[1] = true;
	}

};


class cfffileskipbytes : public cffunction
{
public:
	cfffileskipbytes() {
		name = "FileSkipBytes";
		returntype = T_VOID;

		parameters[0] = cfpfile_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpbytes_numeric();
		parameterrequired[1] = true;
	}

};


class cfffilewrite : public cffunction
{
public:
	cfffilewrite() {
		name = "FileWrite";
		returntype = T_VOID;

		parameters[0] = cfpfilepath_string();
		parameterrequired[0] = true;
		parameters[1] = cfpdata_string();
		parameterrequired[1] = true;
		parameters[2] = cfpcharset_string();
		parameterrequired[2] = false;
	}

};


class cfffilewriteline : public cffunction
{
public:
	cfffilewriteline() {
		name = "FileWriteLine";
		returntype = T_VOID;

		parameters[0] = cfpfile_object();
		parameterrequired[0] = true;
		parameters[1] = cfptext_string();
		parameterrequired[1] = true;
	}

};


class cfffind : public cffunction
{
public:
	cfffind() {
		name = "Find";
		returntype = T_NUMERIC;

		parameters[0] = cfpsubstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpstring_string();
		parameterrequired[1] = true;
		parameters[2] = cfpstart_numeric();
		parameterrequired[2] = false;
	}

};


class cfffindnocase : public cffunction
{
public:
	cfffindnocase() {
		name = "FindNoCase";
		returntype = T_NUMERIC;

		parameters[0] = cfpsubstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpstring_string();
		parameterrequired[1] = true;
		parameters[2] = cfpstart_numeric();
		parameterrequired[2] = false;
	}

};


class cfffindoneof : public cffunction
{
public:
	cfffindoneof() {
		name = "FindOneOf";
		returntype = T_NUMERIC;

		parameters[0] = cfpset_string();
		parameterrequired[0] = true;
		parameters[1] = cfpstring_string();
		parameterrequired[1] = true;
		parameters[2] = cfpstart_numeric();
		parameterrequired[2] = false;
	}

};


class cfffirstdayofmonth : public cffunction
{
public:
	cfffirstdayofmonth() {
		name = "FirstDayOfMonth";
		returntype = T_NUMERIC;

		parameters[0] = cfpdate_datetime();
		parameterrequired[0] = true;
	}

};


class cfffix : public cffunction
{
public:
	cfffix() {
		name = "Fix";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
	}

};


class cffformatbasen : public cffunction
{
public:
	cffformatbasen() {
		name = "FormatBaseN";
		returntype = T_STRING;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
		parameters[1] = cfpradix_numeric();
		parameterrequired[1] = true;
	}

};


class cffgeneratesecretkey : public cffunction
{
public:
	cffgeneratesecretkey() {
		name = "GenerateSecretKey";
		returntype = T_STRING;

		parameters[0] = cfpalgorithm_string();
		parameterrequired[0] = false;
	}

};


class cffgetauthuser : public cffunction
{
public:
	cffgetauthuser() {
		name = "GetAuthUser";
		returntype = T_STRING;

		parameters[0] = cfpalgorithm_string();
		parameterrequired[0] = false;
	}

};


class cffgetbasetagdata : public cffunction
{
public:
	cffgetbasetagdata() {
		name = "GetBaseTagData";
		returntype = T_OBJECT;

		parameters[0] = cfptagname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpinstancenumber_numeric();
		parameterrequired[1] = false;
	}

};


class cffgetbasetaglist : public cffunction
{
public:
	cffgetbasetaglist() {
		name = "GetBaseTagList";
		returntype = T_STRING;

		parameters[0] = cfptagname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpinstancenumber_numeric();
		parameterrequired[1] = false;
	}

};


class cffgetbasetemplatepath : public cffunction
{
public:
	cffgetbasetemplatepath() {
		name = "GetBaseTemplatePath";
		returntype = T_STRING;

		parameters[0] = cfptagname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpinstancenumber_numeric();
		parameterrequired[1] = false;
	}

};


class cffgetclientvariableslist : public cffunction
{
public:
	cffgetclientvariableslist() {
		name = "GetClientVariablesList";
		returntype = T_STRING;

		parameters[0] = cfptagname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpinstancenumber_numeric();
		parameterrequired[1] = false;
	}

};


class cffgetcomponentmetadata : public cffunction
{
public:
	cffgetcomponentmetadata() {
		name = "GetComponentMetaData";
		returntype = T_STRUCT;

		parameters[0] = cfppath_string();
		parameterrequired[0] = true;
	}

};


class cffgetcontextroot : public cffunction
{
public:
	cffgetcontextroot() {
		name = "GetContextRoot";
		returntype = T_STRING;

		parameters[0] = cfppath_string();
		parameterrequired[0] = true;
	}

};


class cffgetcurrenttemplatepath : public cffunction
{
public:
	cffgetcurrenttemplatepath() {
		name = "GetCurrentTemplatePath";
		returntype = T_STRING;

		parameters[0] = cfppath_string();
		parameterrequired[0] = true;
	}

};


class cffgetdirectoryfrompath : public cffunction
{
public:
	cffgetdirectoryfrompath() {
		name = "GetDirectoryFromPath";
		returntype = T_STRING;

		parameters[0] = cfppath_string();
		parameterrequired[0] = true;
	}

};


class cffgetencoding : public cffunction
{
public:
	cffgetencoding() {
		name = "GetEncoding";
		returntype = T_STRING;

		parameters[0] = cfpscope_name_string();
		parameterrequired[0] = true;
	}

};


class cffgetexception : public cffunction
{
public:
	cffgetexception() {
		name = "GetException";
		returntype = T_OBJECT;

		parameters[0] = cfpjavaobject_object();
		parameterrequired[0] = true;
	}

};


class cffgetfilefrompath : public cffunction
{
public:
	cffgetfilefrompath() {
		name = "GetFileFromPath";
		returntype = T_STRING;

		parameters[0] = cfppath_string();
		parameterrequired[0] = true;
	}

};


class cffgetfileinfo : public cffunction
{
public:
	cffgetfileinfo() {
		name = "GetFileInfo";
		returntype = T_STRUCT;

		parameters[0] = cfppath_string();
		parameterrequired[0] = true;
	}

};


class cffgetfunctionlist : public cffunction
{
public:
	cffgetfunctionlist() {
		name = "GetFunctionList";
		returntype = T_STRUCT;

		parameters[0] = cfppath_string();
		parameterrequired[0] = true;
	}

};


class cffgetgatewayhelper : public cffunction
{
public:
	cffgetgatewayhelper() {
		name = "GetGatewayHelper";
		returntype = T_OBJECT;

		parameters[0] = cfpgatewayid_string();
		parameterrequired[0] = true;
	}

};


class cffgethttprequestdata : public cffunction
{
public:
	cffgethttprequestdata() {
		name = "GetHttpRequestData";
		returntype = T_STRUCT;

		parameters[0] = cfpgatewayid_string();
		parameterrequired[0] = true;
	}

};


class cffgethttptimestring : public cffunction
{
public:
	cffgethttptimestring() {
		name = "GetHttpTimeString";
		returntype = T_STRING;

		parameters[0] = cfpdatetime_datetime();
		parameterrequired[0] = true;
	}

};


class cffgetlocale : public cffunction
{
public:
	cffgetlocale() {
		name = "GetLocale";
		returntype = T_STRING;

		parameters[0] = cfpdatetime_datetime();
		parameterrequired[0] = true;
	}

};


class cffgetlocaledisplayname : public cffunction
{
public:
	cffgetlocaledisplayname() {
		name = "GetLocaleDisplayName";
		returntype = T_STRING;

		parameters[0] = cfpdatetime_datetime();
		parameterrequired[0] = true;
	}

};


class cffgetlocalhostip : public cffunction
{
public:
	cffgetlocalhostip() {
		name = "GetLocalHostIP";
		returntype = T_STRING;

		parameters[0] = cfpdatetime_datetime();
		parameterrequired[0] = true;
	}

};


class cffgetmetadata : public cffunction
{
public:
	cffgetmetadata() {
		name = "GetMetaData";
		returntype = T_OBJECT;

		parameters[0] = cfpobject_object();
		parameterrequired[0] = true;
	}

};


class cffgetmetricdata : public cffunction
{
public:
	cffgetmetricdata() {
		name = "GetMetricData";
		returntype = T_OBJECT;

		parameters[0] = cfpmode_string();
		parameterrequired[0] = true;
	}

};


class cffgetpagecontext : public cffunction
{
public:
	cffgetpagecontext() {
		name = "GetPageContext";
		returntype = T_OBJECT;

		parameters[0] = cfpmode_string();
		parameterrequired[0] = true;
	}

};


class cffgetprinterinfo : public cffunction
{
public:
	cffgetprinterinfo() {
		name = "GetPrinterInfo";
		returntype = T_STRUCT;

		parameters[0] = cfpprinter_string();
		parameterrequired[0] = true;
	}

};


class cffgetprinterlist : public cffunction
{
public:
	cffgetprinterlist() {
		name = "GetPrinterList";
		returntype = T_STRING;

		parameters[0] = cfpprinter_string();
		parameterrequired[0] = true;
	}

};


class cffgetprofilesections : public cffunction
{
public:
	cffgetprofilesections() {
		name = "GetProfileSections";
		returntype = T_STRUCT;

		parameters[0] = cfpinifile_string();
		parameterrequired[0] = true;
	}

};


class cffgetprofilestring : public cffunction
{
public:
	cffgetprofilestring() {
		name = "GetProfileString";
		returntype = T_STRING;

		parameters[0] = cfpinipath_string();
		parameterrequired[0] = true;
		parameters[1] = cfpsection_string();
		parameterrequired[1] = true;
		parameters[2] = cfpentry_string();
		parameterrequired[2] = true;
	}

};


class cffgetreadableimageformats : public cffunction
{
public:
	cffgetreadableimageformats() {
		name = "GetReadableImageFormats";
		returntype = T_STRING;

		parameters[0] = cfpinipath_string();
		parameterrequired[0] = true;
		parameters[1] = cfpsection_string();
		parameterrequired[1] = true;
		parameters[2] = cfpentry_string();
		parameterrequired[2] = true;
	}

};


class cffgetsoaprequest : public cffunction
{
public:
	cffgetsoaprequest() {
		name = "GetSOAPRequest";
		returntype = T_OBJECT;

		parameters[0] = cfpinipath_string();
		parameterrequired[0] = true;
		parameters[1] = cfpsection_string();
		parameterrequired[1] = true;
		parameters[2] = cfpentry_string();
		parameterrequired[2] = true;
	}

};


class cffgetsoaprequestheader : public cffunction
{
public:
	cffgetsoaprequestheader() {
		name = "GetSOAPRequestHeader";
		returntype = T_OBJECT;

		parameters[0] = cfpnamespace_string();
		parameterrequired[0] = true;
		parameters[1] = cfpname_string();
		parameterrequired[1] = true;
		parameters[2] = cfpasxml_boolean();
		parameterrequired[2] = false;
	}

};


class cffgetsoapresponse : public cffunction
{
public:
	cffgetsoapresponse() {
		name = "GetSOAPResponse";
		returntype = T_OBJECT;

		parameters[0] = cfpwebservice_string();
		parameterrequired[0] = true;
	}

};


class cffgetsoapresponseheader : public cffunction
{
public:
	cffgetsoapresponseheader() {
		name = "GetSOAPResponseHeader";
		returntype = T_OBJECT;

		parameters[0] = cfpwebservice_object();
		parameterrequired[0] = true;
		parameters[1] = cfpnamespace_string();
		parameterrequired[1] = true;
		parameters[2] = cfpname_string();
		parameterrequired[2] = true;
		parameters[3] = cfpasxml_boolean();
		parameterrequired[3] = false;
	}

};


class cffgettempdirectory : public cffunction
{
public:
	cffgettempdirectory() {
		name = "GetTempDirectory";
		returntype = T_STRING;

		parameters[0] = cfpwebservice_object();
		parameterrequired[0] = true;
		parameters[1] = cfpnamespace_string();
		parameterrequired[1] = true;
		parameters[2] = cfpname_string();
		parameterrequired[2] = true;
		parameters[3] = cfpasxml_boolean();
		parameterrequired[3] = false;
	}

};


class cffgettempfile : public cffunction
{
public:
	cffgettempfile() {
		name = "GetTempFile";
		returntype = T_STRING;

		parameters[0] = cfpdir_string();
		parameterrequired[0] = true;
		parameters[1] = cfpprefix_string();
		parameterrequired[1] = true;
	}

};


class cffgettickcount : public cffunction
{
public:
	cffgettickcount() {
		name = "GetTickCount";
		returntype = T_NUMERIC;

		parameters[0] = cfpdir_string();
		parameterrequired[0] = true;
		parameters[1] = cfpprefix_string();
		parameterrequired[1] = true;
	}

};


class cffgettimezoneinfo : public cffunction
{
public:
	cffgettimezoneinfo() {
		name = "GetTimeZoneInfo";
		returntype = T_OBJECT;

		parameters[0] = cfptext_string();
		parameterrequired[0] = true;
	}

};


class cffgettoken : public cffunction
{
public:
	cffgettoken() {
		name = "GetToken";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpindex_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpdelimiters_string();
		parameterrequired[2] = false;
	}

};


class cffgetuserroles : public cffunction
{
public:
	cffgetuserroles() {
		name = "GetUserRoles";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpindex_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpdelimiters_string();
		parameterrequired[2] = false;
	}

};


class cffgetvfsmetadata : public cffunction
{
public:
	cffgetvfsmetadata() {
		name = "GetVFSMetaData";
		returntype = T_STRUCT;

		parameters[0] = cfpfilesystemtype_string();
		parameterrequired[0] = true;
	}

};


class cffgetwriteableimageformats : public cffunction
{
public:
	cffgetwriteableimageformats() {
		name = "GetWriteableImageFormats";
		returntype = T_STRING;

		parameters[0] = cfpfilesystemtype_string();
		parameterrequired[0] = true;
	}

};


class cffhash : public cffunction
{
public:
	cffhash() {
		name = "Hash";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpalgorithm_string();
		parameterrequired[1] = false;
		parameters[2] = cfpencoding_string();
		parameterrequired[2] = false;
	}

};


class cffhour : public cffunction
{
public:
	cffhour() {
		name = "Hour";
		returntype = T_NUMERIC;

		parameters[0] = cfpdate_datetime();
		parameterrequired[0] = true;
	}

};


class cffhtmlcodeformat : public cffunction
{
public:
	cffhtmlcodeformat() {
		name = "HTMLCodeFormat";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpversion_numeric();
		parameterrequired[1] = false;
	}

};


class cffhtmleditformat : public cffunction
{
public:
	cffhtmleditformat() {
		name = "HTMLEditFormat";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpversion_numeric();
		parameterrequired[1] = false;
	}

};


class cffiif : public cffunction
{
public:
	cffiif() {
		name = "IIf";
		returntype = T_STRING;

		parameters[0] = cfpcondition_boolean();
		parameterrequired[0] = true;
		parameters[1] = cfpexpression1_string();
		parameterrequired[1] = true;
		parameters[2] = cfpexpression2_string();
		parameterrequired[2] = true;
	}

};


class cffimageaddborder : public cffunction
{
public:
	cffimageaddborder() {
		name = "ImageAddBorder";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpthickness_string();
		parameterrequired[1] = true;
		parameters[2] = cfpcolor_string();
		parameterrequired[2] = false;
		parameters[3] = cfpbordertype_string();
		parameterrequired[3] = false;
	}

};


class cffimageblur : public cffunction
{
public:
	cffimageblur() {
		name = "ImageBlur";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpblurradius_numeric();
		parameterrequired[1] = false;
	}

};


class cffimageclearrect : public cffunction
{
public:
	cffimageclearrect() {
		name = "ImageClearRect";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpx_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpy_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpwidth_numeric();
		parameterrequired[3] = true;
		parameters[4] = cfpheight_numeric();
		parameterrequired[4] = true;
	}

};


class cffimagecopy : public cffunction
{
public:
	cffimagecopy() {
		name = "ImageCopy";
		returntype = T_IMAGE;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpx_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpy_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpwidth_numeric();
		parameterrequired[3] = true;
		parameters[4] = cfpheight_numeric();
		parameterrequired[4] = true;
		parameters[5] = cfpdx_numeric();
		parameterrequired[5] = false;
		parameters[6] = cfpdy_numeric();
		parameterrequired[6] = false;
	}

};


class cffimagecrop : public cffunction
{
public:
	cffimagecrop() {
		name = "ImageCrop";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpx_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpy_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpwidth_numeric();
		parameterrequired[3] = true;
		parameters[4] = cfpheight_numeric();
		parameterrequired[4] = true;
	}

};


class cffimagedrawarc : public cffunction
{
public:
	cffimagedrawarc() {
		name = "ImageDrawArc";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpx_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpy_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpwidth_numeric();
		parameterrequired[3] = true;
		parameters[4] = cfpheight_numeric();
		parameterrequired[4] = true;
		parameters[5] = cfpstartangle_numeric();
		parameterrequired[5] = true;
		parameters[6] = cfparchangle_numeric();
		parameterrequired[6] = true;
		parameters[7] = cfpfilled_boolean();
		parameterrequired[7] = false;
	}

};


class cffimagedrawbeveledrect : public cffunction
{
public:
	cffimagedrawbeveledrect() {
		name = "ImageDrawBeveledRect";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpx_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpy_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpwidth_numeric();
		parameterrequired[3] = true;
		parameters[4] = cfpheight_numeric();
		parameterrequired[4] = true;
		parameters[5] = cfpraised_boolean();
		parameterrequired[5] = true;
		parameters[6] = cfpfilled_boolean();
		parameterrequired[6] = false;
	}

};


class cffimagedrawcubiccurve : public cffunction
{
public:
	cffimagedrawcubiccurve() {
		name = "ImageDrawCubicCurve";
		returntype = T_VOID;

		parameters[0] = cfpname_object();
		parameterrequired[0] = true;
		parameters[1] = cfpctrlx1_string();
		parameterrequired[1] = true;
		parameters[2] = cfpctrly1_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpctrlx2_numeric();
		parameterrequired[3] = true;
		parameters[4] = cfpctrly2_numeric();
		parameterrequired[4] = true;
		parameters[5] = cfpx1_numeric();
		parameterrequired[5] = true;
		parameters[6] = cfpy1_numeric();
		parameterrequired[6] = true;
		parameters[7] = cfpx2_numeric();
		parameterrequired[7] = true;
		parameters[8] = cfpy2_numeric();
		parameterrequired[8] = true;
	}

};


class cffimagedrawline : public cffunction
{
public:
	cffimagedrawline() {
		name = "ImageDrawLine";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpx1_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpy1_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpx2_numeric();
		parameterrequired[3] = true;
		parameters[4] = cfpy2_numeric();
		parameterrequired[4] = true;
	}

};


class cffimagedrawlines : public cffunction
{
public:
	cffimagedrawlines() {
		name = "ImageDrawLines";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpxcords_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpycords_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpispolygon_boolean();
		parameterrequired[3] = false;
		parameters[4] = cfpfilled_boolean();
		parameterrequired[4] = false;
	}

};


class cffimagedrawoval : public cffunction
{
public:
	cffimagedrawoval() {
		name = "ImageDrawOval";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpx_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpy_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpwidth_numeric();
		parameterrequired[3] = true;
		parameters[4] = cfpheight_numeric();
		parameterrequired[4] = true;
		parameters[5] = cfpfilled_boolean();
		parameterrequired[5] = false;
	}

};


class cffimagedrawpoint : public cffunction
{
public:
	cffimagedrawpoint() {
		name = "ImageDrawPoint";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpx_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpy_numeric();
		parameterrequired[2] = true;
	}

};


class cffimagedrawquadraticcurve : public cffunction
{
public:
	cffimagedrawquadraticcurve() {
		name = "ImageDrawQuadraticCurve";
		returntype = T_VOID;

		parameters[0] = cfpname_object();
		parameterrequired[0] = true;
		parameters[1] = cfpctrlx1_string();
		parameterrequired[1] = true;
		parameters[2] = cfpctrly1_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpctrlx2_numeric();
		parameterrequired[3] = true;
		parameters[4] = cfpctrly2_numeric();
		parameterrequired[4] = true;
		parameters[5] = cfpx1_numeric();
		parameterrequired[5] = true;
		parameters[6] = cfpy1_numeric();
		parameterrequired[6] = true;
		parameters[7] = cfpx2_numeric();
		parameterrequired[7] = true;
		parameters[8] = cfpy2_numeric();
		parameterrequired[8] = true;
	}

};


class cffimagedrawrect : public cffunction
{
public:
	cffimagedrawrect() {
		name = "ImageDrawRect";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpx_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpy_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpwidth_numeric();
		parameterrequired[3] = true;
		parameters[4] = cfpheight_numeric();
		parameterrequired[4] = true;
		parameters[5] = cfpfilled_boolean();
		parameterrequired[5] = false;
	}

};


class cffimagedrawroundrect : public cffunction
{
public:
	cffimagedrawroundrect() {
		name = "ImageDrawRoundRect";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpx_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpy_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpwidth_numeric();
		parameterrequired[3] = true;
		parameters[4] = cfpheight_numeric();
		parameterrequired[4] = true;
		parameters[5] = cfparcwidth_numeric();
		parameterrequired[5] = true;
		parameters[6] = cfparcheight_numeric();
		parameterrequired[6] = true;
		parameters[7] = cfpfilled_boolean();
		parameterrequired[7] = false;
	}

};


class cffimagedrawtext : public cffunction
{
public:
	cffimagedrawtext() {
		name = "ImageDrawText";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpstr_string();
		parameterrequired[1] = true;
		parameters[2] = cfpx_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpy_numeric();
		parameterrequired[3] = true;
		parameters[4] = cfpattributecollection_struct();
		parameterrequired[4] = true;
	}

};


class cffimageflip : public cffunction
{
public:
	cffimageflip() {
		name = "ImageFlip";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfptranspose_string();
		parameterrequired[1] = true;
	}

};


class cffimagegetblob : public cffunction
{
public:
	cffimagegetblob() {
		name = "ImageGetBlob";
		returntype = T_VOID;

		parameters[0] = cfpsource_string();
		parameterrequired[0] = true;
	}

};


class cffimagegetbufferedimage : public cffunction
{
public:
	cffimagegetbufferedimage() {
		name = "ImageGetBufferedImage";
		returntype = T_IMAGE;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
	}

};


class cffimagegetexifmetadata : public cffunction
{
public:
	cffimagegetexifmetadata() {
		name = "ImageGetEXIFMetadata";
		returntype = T_STRUCT;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
	}

};


class cffimagegetexiftag : public cffunction
{
public:
	cffimagegetexiftag() {
		name = "ImageGetEXIFTag";
		returntype = T_STRING;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfptagname_string();
		parameterrequired[1] = true;
	}

};


class cffimagegetheight : public cffunction
{
public:
	cffimagegetheight() {
		name = "ImageGetHeight";
		returntype = T_NUMERIC;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
	}

};


class cffimagegetiptcmetadata : public cffunction
{
public:
	cffimagegetiptcmetadata() {
		name = "ImageGetIPTCMetadata";
		returntype = T_STRUCT;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
	}

};


class cffimagegetiptctag : public cffunction
{
public:
	cffimagegetiptctag() {
		name = "ImageGetIPTCTag";
		returntype = T_STRING;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfptagname_string();
		parameterrequired[1] = true;
	}

};


class cffimagegetwidth : public cffunction
{
public:
	cffimagegetwidth() {
		name = "ImageGetWidth";
		returntype = T_NUMERIC;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
	}

};


class cffimagegrayscale : public cffunction
{
public:
	cffimagegrayscale() {
		name = "ImageGrayscale";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
	}

};


class cffimageinfo : public cffunction
{
public:
	cffimageinfo() {
		name = "ImageInfo";
		returntype = T_STRUCT;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
	}

};


class cffimagenegative : public cffunction
{
public:
	cffimagenegative() {
		name = "ImageNegative";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
	}

};


class cffimagenew : public cffunction
{
public:
	cffimagenew() {
		name = "ImageNew";
		returntype = T_IMAGE;

		parameters[0] = cfpsource_string();
		parameterrequired[0] = false;
		parameters[1] = cfpwidth_numeric();
		parameterrequired[1] = false;
		parameters[2] = cfpheight_numeric();
		parameterrequired[2] = false;
		parameters[3] = cfpimagetype_string();
		parameterrequired[3] = false;
		parameters[4] = cfpcanvascolor_string();
		parameterrequired[4] = false;
	}

};


class cffimageoverlay : public cffunction
{
public:
	cffimageoverlay() {
		name = "ImageOverlay";
		returntype = T_VOID;

		parameters[0] = cfpsource1_string();
		parameterrequired[0] = true;
		parameters[1] = cfpsource2_string();
		parameterrequired[1] = true;
	}

};


class cffimagepaste : public cffunction
{
public:
	cffimagepaste() {
		name = "ImagePaste";
		returntype = T_VOID;

		parameters[0] = cfpimage1_string();
		parameterrequired[0] = true;
		parameters[1] = cfpimage2_string();
		parameterrequired[1] = true;
		parameters[2] = cfpx_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpy_numeric();
		parameterrequired[3] = true;
	}

};


class cffimageread : public cffunction
{
public:
	cffimageread() {
		name = "ImageRead";
		returntype = T_IMAGE;

		parameters[0] = cfppath_string();
		parameterrequired[0] = true;
	}

};


class cffimagereadbase64 : public cffunction
{
public:
	cffimagereadbase64() {
		name = "ImageReadBase64";
		returntype = T_IMAGE;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
	}

};


class cffimageresize : public cffunction
{
public:
	cffimageresize() {
		name = "ImageResize";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpwidth_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpheight_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpinterpolation_string();
		parameterrequired[3] = true;
		parameters[4] = cfpblurfactor_boolean();
		parameterrequired[4] = true;
	}

};


class cffimagerotate : public cffunction
{
public:
	cffimagerotate() {
		name = "ImageRotate";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpangle_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpx_numeric();
		parameterrequired[2] = false;
		parameters[3] = cfpy_numeric();
		parameterrequired[3] = false;
		parameters[4] = cfpinterpolation_string();
		parameterrequired[4] = false;
	}

};


class cffimagerotatedrawingaxis : public cffunction
{
public:
	cffimagerotatedrawingaxis() {
		name = "ImageRotateDrawingAxis";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpangle_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpx_numeric();
		parameterrequired[2] = false;
		parameters[3] = cfpy_numeric();
		parameterrequired[3] = false;
	}

};


class cffimagescaletofit : public cffunction
{
public:
	cffimagescaletofit() {
		name = "ImageScaleToFit";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpfitwidth_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpfitheight_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpinterpolation_string();
		parameterrequired[3] = false;
		parameters[4] = cfpblurfactor_numeric();
		parameterrequired[4] = false;
	}

};


class cffimagesetantialiasing : public cffunction
{
public:
	cffimagesetantialiasing() {
		name = "ImageSetAntialiasing";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpantialias_boolean();
		parameterrequired[1] = false;
	}

};


class cffimagesetbackgroundcolor : public cffunction
{
public:
	cffimagesetbackgroundcolor() {
		name = "ImageSetBackgroundColor";
		returntype = T_VOID;

		parameters[0] = cfpname_object();
		parameterrequired[0] = true;
		parameters[1] = cfpcolor_string();
		parameterrequired[1] = true;
	}

};


class cffimagesetdrawingcolor : public cffunction
{
public:
	cffimagesetdrawingcolor() {
		name = "ImageSetDrawingColor";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpcolor_string();
		parameterrequired[1] = true;
	}

};


class cffimagesetdrawingstroke : public cffunction
{
public:
	cffimagesetdrawingstroke() {
		name = "ImageSetDrawingStroke";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpattributecollection_struct();
		parameterrequired[1] = false;
	}

};


class cffimagesetdrawingtransparency : public cffunction
{
public:
	cffimagesetdrawingtransparency() {
		name = "ImageSetDrawingTransparency";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfppercent_numeric();
		parameterrequired[1] = true;
	}

};


class cffimagesharpen : public cffunction
{
public:
	cffimagesharpen() {
		name = "ImageSharpen";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpgain_numeric();
		parameterrequired[1] = false;
	}

};


class cffimageshear : public cffunction
{
public:
	cffimageshear() {
		name = "ImageShear";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpshear_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpdirection_string();
		parameterrequired[2] = false;
		parameters[3] = cfpinterpolation_string();
		parameterrequired[3] = false;
	}

};


class cffimagesheardrawingaxis : public cffunction
{
public:
	cffimagesheardrawingaxis() {
		name = "ImageShearDrawingAxis";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpshrx_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpshry_numeric();
		parameterrequired[2] = true;
	}

};


class cffimagetranslate : public cffunction
{
public:
	cffimagetranslate() {
		name = "ImageTranslate";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpxtrans_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpytrans_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpinterpolation_string();
		parameterrequired[3] = false;
	}

};


class cffimagetranslatedrawingaxis : public cffunction
{
public:
	cffimagetranslatedrawingaxis() {
		name = "ImageTranslateDrawingAxis";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpx_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpy_numeric();
		parameterrequired[2] = true;
	}

};


class cffimagewrite : public cffunction
{
public:
	cffimagewrite() {
		name = "ImageWrite";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpdestination_string();
		parameterrequired[1] = false;
		parameters[2] = cfpquality_string();
		parameterrequired[2] = false;
		parameters[3] = cfpoverwrite_boolean();
		parameterrequired[3] = false;
	}

};


class cffimagewritebase64 : public cffunction
{
public:
	cffimagewritebase64() {
		name = "ImageWriteBase64";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpdestination_string();
		parameterrequired[1] = true;
		parameters[2] = cfpformat_string();
		parameterrequired[2] = true;
		parameters[3] = cfpinhtmlformat_boolean();
		parameterrequired[3] = false;
		parameters[4] = cfpoverwrite_boolean();
		parameterrequired[4] = false;
	}

};


class cffimagexordrawingmode : public cffunction
{
public:
	cffimagexordrawingmode() {
		name = "ImageXORDrawingMode";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpc1_string();
		parameterrequired[1] = true;
	}

};


class cffincrementvalue : public cffunction
{
public:
	cffincrementvalue() {
		name = "IncrementValue";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
	}

};


class cffinputbasen : public cffunction
{
public:
	cffinputbasen() {
		name = "InputBaseN";
		returntype = T_NUMERIC;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpradix_string();
		parameterrequired[1] = true;
	}

};


class cffinsert : public cffunction
{
public:
	cffinsert() {
		name = "Insert";
		returntype = T_STRING;

		parameters[0] = cfpsubstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpstring_string();
		parameterrequired[1] = true;
		parameters[2] = cfpposition_numeric();
		parameterrequired[2] = true;
	}

};


class cffint : public cffunction
{
public:
	cffint() {
		name = "Int";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
	}

};


class cffisarray : public cffunction
{
public:
	cffisarray() {
		name = "IsArray";
		returntype = T_BOOLEAN;

		parameters[0] = cfpvalue_object();
		parameterrequired[0] = true;
		parameters[1] = cfpnumber_numeric();
		parameterrequired[1] = false;
	}

};


class cffisbinary : public cffunction
{
public:
	cffisbinary() {
		name = "IsBinary";
		returntype = T_BOOLEAN;

		parameters[0] = cfpvalue_object();
		parameterrequired[0] = true;
	}

};


class cffisboolean : public cffunction
{
public:
	cffisboolean() {
		name = "IsBoolean";
		returntype = T_BOOLEAN;

		parameters[0] = cfpvalue_object();
		parameterrequired[0] = true;
	}

};


class cffiscustomfunction : public cffunction
{
public:
	cffiscustomfunction() {
		name = "IsCustomFunction";
		returntype = T_BOOLEAN;

		parameters[0] = cfpobject_object();
		parameterrequired[0] = true;
	}

};


class cffisdate : public cffunction
{
public:
	cffisdate() {
		name = "IsDate";
		returntype = T_BOOLEAN;

		parameters[0] = cfpobject_object();
		parameterrequired[0] = true;
	}

};


class cffisddx : public cffunction
{
public:
	cffisddx() {
		name = "IsDDX";
		returntype = T_BOOLEAN;

		parameters[0] = cfppath_string();
		parameterrequired[0] = true;
	}

};


class cffisdebugmode : public cffunction
{
public:
	cffisdebugmode() {
		name = "IsDebugMode";
		returntype = T_BOOLEAN;

		parameters[0] = cfppath_string();
		parameterrequired[0] = true;
	}

};


class cffisdefined : public cffunction
{
public:
	cffisdefined() {
		name = "IsDefined";
		returntype = T_BOOLEAN;

		parameters[0] = cfpvariable_name_string();
		parameterrequired[0] = true;
	}

};


class cffisimage : public cffunction
{
public:
	cffisimage() {
		name = "IsImage";
		returntype = T_BOOLEAN;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
	}

};


class cffisimagefile : public cffunction
{
public:
	cffisimagefile() {
		name = "IsImageFile";
		returntype = T_BOOLEAN;

		parameters[0] = cfppath_string();
		parameterrequired[0] = true;
	}

};


class cffisinstanceof : public cffunction
{
public:
	cffisinstanceof() {
		name = "IsInstanceOf";
		returntype = T_BOOLEAN;

		parameters[0] = cfpobject_object();
		parameterrequired[0] = true;
		parameters[1] = cfptypename_string();
		parameterrequired[1] = true;
	}

};


class cffisipv6 : public cffunction
{
public:
	cffisipv6() {
		name = "IsIPv6";
		returntype = T_BOOLEAN;

		parameters[0] = cfpip_string();
		parameterrequired[0] = true;
	}

};


class cffisjson : public cffunction
{
public:
	cffisjson() {
		name = "IsJSON";
		returntype = T_BOOLEAN;

		parameters[0] = cfpvar_string();
		parameterrequired[0] = true;
	}

};


class cffisleapyear : public cffunction
{
public:
	cffisleapyear() {
		name = "IsLeapYear";
		returntype = T_BOOLEAN;

		parameters[0] = cfpyear_numeric();
		parameterrequired[0] = true;
	}

};


class cffislocalhost : public cffunction
{
public:
	cffislocalhost() {
		name = "IsLocalHost";
		returntype = T_BOOLEAN;

		parameters[0] = cfpipaddress_string();
		parameterrequired[0] = true;
	}

};


class cffisnull : public cffunction
{
public:
	cffisnull() {
		name = "IsNull";
		returntype = T_BOOLEAN;

		parameters[0] = cfpobject_variablename();
		parameterrequired[0] = true;
	}

};


class cffisnumeric : public cffunction
{
public:
	cffisnumeric() {
		name = "IsNumeric";
		returntype = T_BOOLEAN;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
	}

};


class cffisnumericdate : public cffunction
{
public:
	cffisnumericdate() {
		name = "IsNumericDate";
		returntype = T_BOOLEAN;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
	}

};


class cffisobject : public cffunction
{
public:
	cffisobject() {
		name = "IsObject";
		returntype = T_BOOLEAN;

		parameters[0] = cfpvalue_object();
		parameterrequired[0] = true;
	}

};


class cffispdffile : public cffunction
{
public:
	cffispdffile() {
		name = "IsPDFFile";
		returntype = T_BOOLEAN;

		parameters[0] = cfppath_string();
		parameterrequired[0] = true;
	}

};


class cffispdfobject : public cffunction
{
public:
	cffispdfobject() {
		name = "IsPDFObject";
		returntype = T_BOOLEAN;

		parameters[0] = cfpvalue_variablename();
		parameterrequired[0] = true;
	}

};


class cffisquery : public cffunction
{
public:
	cffisquery() {
		name = "IsQuery";
		returntype = T_BOOLEAN;

		parameters[0] = cfpvalue_string();
		parameterrequired[0] = true;
	}

};


class cffissimplevalue : public cffunction
{
public:
	cffissimplevalue() {
		name = "IsSimpleValue";
		returntype = T_BOOLEAN;

		parameters[0] = cfpvalue_object();
		parameterrequired[0] = true;
	}

};


class cffissoaprequest : public cffunction
{
public:
	cffissoaprequest() {
		name = "IsSOAPRequest";
		returntype = T_BOOLEAN;

		parameters[0] = cfpvalue_object();
		parameterrequired[0] = true;
	}

};


class cffisspreadsheetfile : public cffunction
{
public:
	cffisspreadsheetfile() {
		name = "IsSpreadsheetFile";
		returntype = T_BOOLEAN;

		parameters[0] = cfpfile_string();
		parameterrequired[0] = true;
	}

};


class cffisspreadsheetobject : public cffunction
{
public:
	cffisspreadsheetobject() {
		name = "IsSpreadsheetObject";
		returntype = T_BOOLEAN;

		parameters[0] = cfpobject_variablename();
		parameterrequired[0] = true;
	}

};


class cffisstruct : public cffunction
{
public:
	cffisstruct() {
		name = "IsStruct";
		returntype = T_BOOLEAN;

		parameters[0] = cfpvariable_object();
		parameterrequired[0] = true;
	}

};


class cffisuserinanyrole : public cffunction
{
public:
	cffisuserinanyrole() {
		name = "IsUserInAnyRole";
		returntype = T_BOOLEAN;

		parameters[0] = cfprolelist_string();
		parameterrequired[0] = true;
	}

};


class cffisuserinrole : public cffunction
{
public:
	cffisuserinrole() {
		name = "IsUserInRole";
		returntype = T_STRING;

		parameters[0] = cfprole_name_string();
		parameterrequired[0] = true;
	}

};


class cffisuserloggedin : public cffunction
{
public:
	cffisuserloggedin() {
		name = "IsUserLoggedIn";
		returntype = T_BOOLEAN;

		parameters[0] = cfprole_name_string();
		parameterrequired[0] = true;
	}

};


class cffisvalid : public cffunction
{
public:
	cffisvalid() {
		name = "IsValid";
		returntype = T_BOOLEAN;

		parameters[0] = cfptype_string();
		parameterrequired[0] = true;
		parameters[1] = cfpvalue_object();
		parameterrequired[1] = true;
		parameters[2] = cfpmin_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpmax_numeric();
		parameterrequired[3] = true;
		parameters[4] = cfppattern_string();
		parameterrequired[4] = true;
	}

};


class cffiswddx : public cffunction
{
public:
	cffiswddx() {
		name = "IsWDDX";
		returntype = T_BOOLEAN;

		parameters[0] = cfpvalue_object();
		parameterrequired[0] = true;
	}

};


class cffisxml : public cffunction
{
public:
	cffisxml() {
		name = "IsXML";
		returntype = T_BOOLEAN;

		parameters[0] = cfpvalue_string();
		parameterrequired[0] = true;
	}

};


class cffisxmlattribute : public cffunction
{
public:
	cffisxmlattribute() {
		name = "IsXmlAttribute";
		returntype = T_BOOLEAN;

		parameters[0] = cfpvalue_object();
		parameterrequired[0] = true;
	}

};


class cffisxmldoc : public cffunction
{
public:
	cffisxmldoc() {
		name = "IsXmlDoc";
		returntype = T_BOOLEAN;

		parameters[0] = cfpvalue_object();
		parameterrequired[0] = true;
	}

};


class cffisxmlelem : public cffunction
{
public:
	cffisxmlelem() {
		name = "IsXmlElem";
		returntype = T_BOOLEAN;

		parameters[0] = cfpvalue_object();
		parameterrequired[0] = true;
	}

};


class cffisxmlnode : public cffunction
{
public:
	cffisxmlnode() {
		name = "IsXmlNode";
		returntype = T_BOOLEAN;

		parameters[0] = cfpvalue_object();
		parameterrequired[0] = true;
	}

};


class cffisxmlroot : public cffunction
{
public:
	cffisxmlroot() {
		name = "IsXmlRoot";
		returntype = T_BOOLEAN;

		parameters[0] = cfpvalue_object();
		parameterrequired[0] = true;
	}

};


class cffjavacast : public cffunction
{
public:
	cffjavacast() {
		name = "JavaCast";
		returntype = T_OBJECT;

		parameters[0] = cfptype_string();
		parameterrequired[0] = true;
		parameters[1] = cfpvariable_string();
		parameterrequired[1] = true;
	}

};


class cffjsstringformat : public cffunction
{
public:
	cffjsstringformat() {
		name = "JSStringFormat";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
	}

};


class cfflcase : public cffunction
{
public:
	cfflcase() {
		name = "LCase";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
	}

};


class cffleft : public cffunction
{
public:
	cffleft() {
		name = "Left";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpcount_numeric();
		parameterrequired[1] = true;
	}

};


class cfflen : public cffunction
{
public:
	cfflen() {
		name = "Len";
		returntype = T_NUMERIC;

		parameters[0] = cfpobject_object();
		parameterrequired[0] = true;
	}

};


class cfflistappend : public cffunction
{
public:
	cfflistappend() {
		name = "ListAppend";
		returntype = T_STRING;

		parameters[0] = cfplist_string();
		parameterrequired[0] = true;
		parameters[1] = cfpvalue_string();
		parameterrequired[1] = true;
		parameters[2] = cfpdelimiters_string();
		parameterrequired[2] = false;
	}

};


class cfflistchangedelims : public cffunction
{
public:
	cfflistchangedelims() {
		name = "ListChangeDelims";
		returntype = T_STRING;

		parameters[0] = cfplist_string();
		parameterrequired[0] = true;
		parameters[1] = cfpnew_delimiter_string();
		parameterrequired[1] = true;
		parameters[2] = cfpdelimiters_string();
		parameterrequired[2] = false;
	}

};


class cfflistcontains : public cffunction
{
public:
	cfflistcontains() {
		name = "ListContains";
		returntype = T_NUMERIC;

		parameters[0] = cfplist_string();
		parameterrequired[0] = true;
		parameters[1] = cfpsubstring_string();
		parameterrequired[1] = true;
		parameters[2] = cfpdelimiters_string();
		parameterrequired[2] = false;
	}

};


class cfflistcontainsnocase : public cffunction
{
public:
	cfflistcontainsnocase() {
		name = "ListContainsNoCase";
		returntype = T_NUMERIC;

		parameters[0] = cfplist_string();
		parameterrequired[0] = true;
		parameters[1] = cfpsubstring_string();
		parameterrequired[1] = true;
		parameters[2] = cfpdelimiters_string();
		parameterrequired[2] = false;
	}

};


class cfflistdeleteat : public cffunction
{
public:
	cfflistdeleteat() {
		name = "ListDeleteAt";
		returntype = T_STRING;

		parameters[0] = cfplist_string();
		parameterrequired[0] = true;
		parameters[1] = cfpposition_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpdelimiters_string();
		parameterrequired[2] = false;
	}

};


class cfflistfind : public cffunction
{
public:
	cfflistfind() {
		name = "ListFind";
		returntype = T_NUMERIC;

		parameters[0] = cfplist_string();
		parameterrequired[0] = true;
		parameters[1] = cfpvalue_string();
		parameterrequired[1] = true;
		parameters[2] = cfpdelimiters_string();
		parameterrequired[2] = false;
	}

};


class cfflistfindnocase : public cffunction
{
public:
	cfflistfindnocase() {
		name = "ListFindNoCase";
		returntype = T_NUMERIC;

		parameters[0] = cfplist_string();
		parameterrequired[0] = true;
		parameters[1] = cfpvalue_string();
		parameterrequired[1] = true;
		parameters[2] = cfpdelimiters_string();
		parameterrequired[2] = false;
	}

};


class cfflistfirst : public cffunction
{
public:
	cfflistfirst() {
		name = "ListFirst";
		returntype = T_STRING;

		parameters[0] = cfplist_string();
		parameterrequired[0] = true;
		parameters[1] = cfpdelimiters_string();
		parameterrequired[1] = false;
	}

};


class cfflistgetat : public cffunction
{
public:
	cfflistgetat() {
		name = "ListGetAt";
		returntype = T_STRING;

		parameters[0] = cfplist_string();
		parameterrequired[0] = true;
		parameters[1] = cfpposition_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpdelimiters_string();
		parameterrequired[2] = false;
	}

};


class cfflistinsertat : public cffunction
{
public:
	cfflistinsertat() {
		name = "ListInsertAt";
		returntype = T_STRING;

		parameters[0] = cfplist_string();
		parameterrequired[0] = true;
		parameters[1] = cfpposition_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpvalue_string();
		parameterrequired[2] = true;
		parameters[3] = cfpdelimiters_string();
		parameterrequired[3] = false;
	}

};


class cfflistlast : public cffunction
{
public:
	cfflistlast() {
		name = "ListLast";
		returntype = T_STRING;

		parameters[0] = cfplist_string();
		parameterrequired[0] = true;
		parameters[1] = cfpdelimiters_string();
		parameterrequired[1] = false;
	}

};


class cfflistlen : public cffunction
{
public:
	cfflistlen() {
		name = "ListLen";
		returntype = T_NUMERIC;

		parameters[0] = cfplist_string();
		parameterrequired[0] = true;
		parameters[1] = cfpdelimiters_string();
		parameterrequired[1] = false;
	}

};


class cfflistprepend : public cffunction
{
public:
	cfflistprepend() {
		name = "ListPrepend";
		returntype = T_STRING;

		parameters[0] = cfplist_string();
		parameterrequired[0] = true;
		parameters[1] = cfpvalue_string();
		parameterrequired[1] = true;
		parameters[2] = cfpdelimiters_string();
		parameterrequired[2] = false;
	}

};


class cfflistqualify : public cffunction
{
public:
	cfflistqualify() {
		name = "ListQualify";
		returntype = T_STRING;

		parameters[0] = cfplist_string();
		parameterrequired[0] = true;
		parameters[1] = cfpqualifier_string();
		parameterrequired[1] = true;
		parameters[2] = cfpdelimiters_string();
		parameterrequired[2] = false;
		parameters[3] = cfpelements_string();
		parameterrequired[3] = false;
	}

};


class cfflistrest : public cffunction
{
public:
	cfflistrest() {
		name = "ListRest";
		returntype = T_STRING;

		parameters[0] = cfplist_string();
		parameterrequired[0] = true;
		parameters[1] = cfpdelimiters_string();
		parameterrequired[1] = false;
	}

};


class cfflistsetat : public cffunction
{
public:
	cfflistsetat() {
		name = "ListSetAt";
		returntype = T_STRING;

		parameters[0] = cfplist_string();
		parameterrequired[0] = true;
		parameters[1] = cfpposition_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpvalue_string();
		parameterrequired[2] = true;
		parameters[3] = cfpdelimiters_string();
		parameterrequired[3] = false;
	}

};


class cfflistsort : public cffunction
{
public:
	cfflistsort() {
		name = "ListSort";
		returntype = T_STRING;

		parameters[0] = cfplist_string();
		parameterrequired[0] = true;
		parameters[1] = cfpsort_type_string();
		parameterrequired[1] = true;
		parameters[2] = cfpsort_order_string();
		parameterrequired[2] = false;
		parameters[3] = cfpdelimiters_string();
		parameterrequired[3] = false;
	}

};


class cfflisttoarray : public cffunction
{
public:
	cfflisttoarray() {
		name = "ListToArray";
		returntype = T_ARRAY;

		parameters[0] = cfplist_string();
		parameterrequired[0] = true;
		parameters[1] = cfpdelimiters_string();
		parameterrequired[1] = false;
		parameters[2] = cfpincludeemptyfields_boolean();
		parameterrequired[2] = false;
		parameters[3] = cfpmulticharacterdelimiter_boolean();
		parameterrequired[3] = false;
	}

};


class cfflistvaluecount : public cffunction
{
public:
	cfflistvaluecount() {
		name = "ListValueCount";
		returntype = T_NUMERIC;

		parameters[0] = cfplist_string();
		parameterrequired[0] = true;
		parameters[1] = cfpvalue_string();
		parameterrequired[1] = true;
		parameters[2] = cfpdelimiters_string();
		parameterrequired[2] = false;
	}

};


class cfflistvaluecountnocase : public cffunction
{
public:
	cfflistvaluecountnocase() {
		name = "ListValueCountNoCase";
		returntype = T_NUMERIC;

		parameters[0] = cfplist_string();
		parameterrequired[0] = true;
		parameters[1] = cfpvalue_string();
		parameterrequired[1] = true;
		parameters[2] = cfpdelimiters_string();
		parameterrequired[2] = false;
	}

};


class cffljustify : public cffunction
{
public:
	cffljustify() {
		name = "LJustify";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfplength_numeric();
		parameterrequired[1] = true;
	}

};


class cfflocation : public cffunction
{
public:
	cfflocation() {
		name = "Location";
		returntype = T_VOID;

		parameters[0] = cfpurl_string();
		parameterrequired[0] = true;
		parameters[1] = cfpaddtoken_boolean();
		parameterrequired[1] = false;
		parameters[2] = cfpstatuscode_numeric();
		parameterrequired[2] = false;
	}

};


class cfflog : public cffunction
{
public:
	cfflog() {
		name = "Log";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
	}

};


class cfflog10 : public cffunction
{
public:
	cfflog10() {
		name = "Log10";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
	}

};


class cfflscurrencyformat : public cffunction
{
public:
	cfflscurrencyformat() {
		name = "LSCurrencyFormat";
		returntype = T_STRING;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
		parameters[1] = cfptype_string();
		parameterrequired[1] = false;
	}

};


class cfflsdateformat : public cffunction
{
public:
	cfflsdateformat() {
		name = "LSDateFormat";
		returntype = T_STRING;

		parameters[0] = cfpdate_datetime();
		parameterrequired[0] = true;
		parameters[1] = cfpmask_string();
		parameterrequired[1] = false;
	}

};


class cfflseurocurrencyformat : public cffunction
{
public:
	cfflseurocurrencyformat() {
		name = "LSEuroCurrencyFormat";
		returntype = T_STRING;

		parameters[0] = cfpcurrency_string();
		parameterrequired[0] = true;
		parameters[1] = cfptype_string();
		parameterrequired[1] = true;
	}

};


class cfflsiscurrency : public cffunction
{
public:
	cfflsiscurrency() {
		name = "LSIsCurrency";
		returntype = T_BOOLEAN;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
	}

};


class cfflsisdate : public cffunction
{
public:
	cfflsisdate() {
		name = "LSIsDate";
		returntype = T_BOOLEAN;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
	}

};


class cfflsisnumeric : public cffunction
{
public:
	cfflsisnumeric() {
		name = "LSIsNumeric";
		returntype = T_BOOLEAN;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
	}

};


class cfflsnumberformat : public cffunction
{
public:
	cfflsnumberformat() {
		name = "LSNumberFormat";
		returntype = T_STRING;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
		parameters[1] = cfpmask_string();
		parameterrequired[1] = false;
	}

};


class cfflsparsecurrency : public cffunction
{
public:
	cfflsparsecurrency() {
		name = "LSParseCurrency";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
	}

};


class cfflsparsedatetime : public cffunction
{
public:
	cfflsparsedatetime() {
		name = "LSParseDateTime";
		returntype = T_DATETIME;

		parameters[0] = cfpdt_string_string();
		parameterrequired[0] = true;
	}

};


class cfflsparseeurocurrency : public cffunction
{
public:
	cfflsparseeurocurrency() {
		name = "LSParseEuroCurrency";
		returntype = T_NUMERIC;

		parameters[0] = cfpcurrency_string_string();
		parameterrequired[0] = true;
	}

};


class cfflsparsenumber : public cffunction
{
public:
	cfflsparsenumber() {
		name = "LSParseNumber";
		returntype = T_NUMERIC;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
	}

};


class cfflstimeformat : public cffunction
{
public:
	cfflstimeformat() {
		name = "LSTimeFormat";
		returntype = T_STRING;

		parameters[0] = cfptime_datetime();
		parameterrequired[0] = true;
		parameters[1] = cfpmask_string();
		parameterrequired[1] = false;
	}

};


class cffltrim : public cffunction
{
public:
	cffltrim() {
		name = "LTrim";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
	}

};


class cffmax : public cffunction
{
public:
	cffmax() {
		name = "Max";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber1_numeric();
		parameterrequired[0] = true;
		parameters[1] = cfpnumber2_numeric();
		parameterrequired[1] = true;
	}

};


class cffmid : public cffunction
{
public:
	cffmid() {
		name = "Mid";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpstart_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpcount_numeric();
		parameterrequired[2] = true;
	}

};


class cffmin : public cffunction
{
public:
	cffmin() {
		name = "Min";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber1_numeric();
		parameterrequired[0] = true;
		parameters[1] = cfpnumber2_numeric();
		parameterrequired[1] = true;
	}

};


class cffminute : public cffunction
{
public:
	cffminute() {
		name = "Minute";
		returntype = T_NUMERIC;

		parameters[0] = cfpdate_datetime();
		parameterrequired[0] = true;
	}

};


class cffmonth : public cffunction
{
public:
	cffmonth() {
		name = "Month";
		returntype = T_NUMERIC;

		parameters[0] = cfpdate_datetime();
		parameterrequired[0] = true;
	}

};


class cffmonthasstring : public cffunction
{
public:
	cffmonthasstring() {
		name = "MonthAsString";
		returntype = T_STRING;

		parameters[0] = cfpmonth_number_numeric();
		parameterrequired[0] = true;
	}

};


class cffnow : public cffunction
{
public:
	cffnow() {
		name = "Now";
		returntype = T_DATETIME;

		parameters[0] = cfpmonth_number_numeric();
		parameterrequired[0] = true;
	}

};


class cffnumberformat : public cffunction
{
public:
	cffnumberformat() {
		name = "NumberFormat";
		returntype = T_STRING;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
		parameters[1] = cfpmask_string();
		parameterrequired[1] = false;
	}

};


class cffobjectequals : public cffunction
{
public:
	cffobjectequals() {
		name = "ObjectEquals";
		returntype = T_BOOLEAN;

		parameters[0] = cfpparam1_object();
		parameterrequired[0] = true;
		parameters[1] = cfpparam2_object();
		parameterrequired[1] = true;
	}

};


class cffobjectload : public cffunction
{
public:
	cffobjectload() {
		name = "ObjectLoad";
		returntype = T_VOID;

		parameters[0] = cfpbinaryobject_object();
		parameterrequired[0] = true;
	}

};
/*

class cffobjectload : public cffunction
{
public:
cffobjectload()
{
name = "ObjectLoad";
returntype = T_VOID;

parameters[0] = cfpfilepath_string();
parameterrequired[0] = true;
}

};*/


class cffobjectsave : public cffunction
{
public:
	cffobjectsave() {
		name = "ObjectSave";
		returntype = T_BINARY;

		parameters[0] = cfpobject_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpfile_string();
		parameterrequired[1] = false;
	}

};


class cfformclearsession : public cffunction
{
public:
	cfformclearsession() {
		name = "ORMClearSession";
		returntype = T_VOID;

		parameters[0] = cfpobject_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpfile_string();
		parameterrequired[1] = false;
	}

};


class cfformclosesession : public cffunction
{
public:
	cfformclosesession() {
		name = "ORMCloseSession";
		returntype = T_VOID;

		parameters[0] = cfpobject_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpfile_string();
		parameterrequired[1] = false;
	}

};


class cfformevictcollection : public cffunction
{
public:
	cfformevictcollection() {
		name = "ORMEvictCollection";
		returntype = T_VOID;

		parameters[0] = cfpcomponentname_string();
		parameterrequired[0] = true;
		parameters[1] = cfprelationname_string();
		parameterrequired[1] = true;
		parameters[2] = cfpid_string();
		parameterrequired[2] = false;
	}

};


class cfformevictentity : public cffunction
{
public:
	cfformevictentity() {
		name = "ORMEvictEntity";
		returntype = T_VOID;

		parameters[0] = cfpcomponentname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpid_string();
		parameterrequired[1] = false;
	}

};


class cfformevictqueries : public cffunction
{
public:
	cfformevictqueries() {
		name = "ORMEvictQueries";
		returntype = T_VOID;

		parameters[0] = cfpcachename_string();
		parameterrequired[0] = false;
	}

};


class cfformexecutequery : public cffunction
{
public:
	cfformexecutequery() {
		name = "ORMExecuteQuery";
		returntype = T_VOID;

		parameters[0] = cfphql_string();
		parameterrequired[0] = true;
		parameters[1] = cfpunique_boolean();
		parameterrequired[1] = false;
		parameters[2] = cfpqueryoptions_string();
		parameterrequired[2] = false;
	}

};


class cfformflush : public cffunction
{
public:
	cfformflush() {
		name = "ORMFlush";
		returntype = T_VOID;

		parameters[0] = cfphql_string();
		parameterrequired[0] = true;
		parameters[1] = cfpunique_boolean();
		parameterrequired[1] = false;
		parameters[2] = cfpqueryoptions_string();
		parameterrequired[2] = false;
	}

};


class cfformgetsession : public cffunction
{
public:
	cfformgetsession() {
		name = "ORMGetSession";
		returntype = T_VOID;

		parameters[0] = cfphql_string();
		parameterrequired[0] = true;
		parameters[1] = cfpunique_boolean();
		parameterrequired[1] = false;
		parameters[2] = cfpqueryoptions_string();
		parameterrequired[2] = false;
	}

};


class cfformgetsessionfactory : public cffunction
{
public:
	cfformgetsessionfactory() {
		name = "ORMGetSessionFactory";
		returntype = T_OBJECT;

		parameters[0] = cfphql_string();
		parameterrequired[0] = true;
		parameters[1] = cfpunique_boolean();
		parameterrequired[1] = false;
		parameters[2] = cfpqueryoptions_string();
		parameterrequired[2] = false;
	}

};


class cfformreload : public cffunction
{
public:
	cfformreload() {
		name = "ORMReload";
		returntype = T_VOID;

		parameters[0] = cfphql_string();
		parameterrequired[0] = true;
		parameters[1] = cfpunique_boolean();
		parameterrequired[1] = false;
		parameters[2] = cfpqueryoptions_string();
		parameterrequired[2] = false;
	}

};


class cffparagraphformat : public cffunction
{
public:
	cffparagraphformat() {
		name = "ParagraphFormat";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
	}

};


class cffparsedatetime : public cffunction
{
public:
	cffparsedatetime() {
		name = "ParseDateTime";
		returntype = T_DATETIME;

		parameters[0] = cfpdt_string_string();
		parameterrequired[0] = true;
		parameters[1] = cfppop_conversion_string();
		parameterrequired[1] = false;
	}

};


class cffpi : public cffunction
{
public:
	cffpi() {
		name = "Pi";
		returntype = T_NUMERIC;

		parameters[0] = cfpdt_string_string();
		parameterrequired[0] = true;
		parameters[1] = cfppop_conversion_string();
		parameterrequired[1] = false;
	}

};


class cffprecisionevaluate : public cffunction
{
public:
	cffprecisionevaluate() {
		name = "PrecisionEvaluate";
		returntype = T_NUMERIC;

		parameters[0] = cfpexpressions_string();
		parameterrequired[0] = true;
	}

};


class cffpreservesinglequotes : public cffunction
{
public:
	cffpreservesinglequotes() {
		name = "PreserveSingleQuotes";
		returntype = T_VOID;

		parameters[0] = cfpvariable_string();
		parameterrequired[0] = true;
	}

};


class cffquarter : public cffunction
{
public:
	cffquarter() {
		name = "Quarter";
		returntype = T_NUMERIC;

		parameters[0] = cfpdate_datetime();
		parameterrequired[0] = true;
	}

};


class cffqueryaddcolumn : public cffunction
{
public:
	cffqueryaddcolumn() {
		name = "QueryAddColumn";
		returntype = T_NUMERIC;

		parameters[0] = cfpquery_query();
		parameterrequired[0] = true;
		parameters[1] = cfpcolumn_name_string();
		parameterrequired[1] = true;
		parameters[2] = cfpdatatype_string();
		parameterrequired[2] = false;
		parameters[3] = cfparray_name_array();
		parameterrequired[3] = true;
	}

};


class cffqueryaddrow : public cffunction
{
public:
	cffqueryaddrow() {
		name = "QueryAddRow";
		returntype = T_NUMERIC;

		parameters[0] = cfpquery_query();
		parameterrequired[0] = true;
		parameters[1] = cfpnumber_numeric();
		parameterrequired[1] = false;
	}

};


class cffqueryconvertforgrid : public cffunction
{
public:
	cffqueryconvertforgrid() {
		name = "QueryConvertForGrid";
		returntype = T_STRUCT;

		parameters[0] = cfpquery_string();
		parameterrequired[0] = true;
		parameters[1] = cfppage_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfppagesize_numeric();
		parameterrequired[2] = true;
	}

};


class cffquerynew : public cffunction
{
public:
	cffquerynew() {
		name = "QueryNew";
		returntype = T_QUERY;

		parameters[0] = cfpcolumnlist_string();
		parameterrequired[0] = true;
		parameters[1] = cfpcolumntypelist_string();
		parameterrequired[1] = false;
	}

};


class cffquerysetcell : public cffunction
{
public:
	cffquerysetcell() {
		name = "QuerySetCell";
		returntype = T_BOOLEAN;

		parameters[0] = cfpquery_query();
		parameterrequired[0] = true;
		parameters[1] = cfpcolumn_string();
		parameterrequired[1] = true;
		parameters[2] = cfpvalue_object();
		parameterrequired[2] = true;
		parameters[3] = cfprow_numeric();
		parameterrequired[3] = false;
	}

};


class cffquotedvaluelist : public cffunction
{
public:
	cffquotedvaluelist() {
		name = "QuotedValueList";
		returntype = T_STRING;

		parameters[0] = cfpcolumn_querycolumn();
		parameterrequired[0] = true;
		parameters[1] = cfpdelimiter_string();
		parameterrequired[1] = false;
	}

};


class cffrand : public cffunction
{
public:
	cffrand() {
		name = "Rand";
		returntype = T_NUMERIC;

		parameters[0] = cfpalgorithm_string();
		parameterrequired[0] = false;
	}

};


class cffrandomize : public cffunction
{
public:
	cffrandomize() {
		name = "Randomize";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
		parameters[1] = cfpalgorithm_string();
		parameterrequired[1] = false;
	}

};


class cffrandrange : public cffunction
{
public:
	cffrandrange() {
		name = "RandRange";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber1_numeric();
		parameterrequired[0] = true;
		parameters[1] = cfpnumber2_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpalgorithm_string();
		parameterrequired[2] = false;
	}

};


class cffrefind : public cffunction
{
public:
	cffrefind() {
		name = "REFind";
		returntype = T_OBJECT;

		parameters[0] = cfpreg_expression_regex();
		parameterrequired[0] = true;
		parameters[1] = cfpstring_string();
		parameterrequired[1] = true;
		parameters[2] = cfpstart_numeric();
		parameterrequired[2] = false;
		parameters[3] = cfpreturnsubexpressions_boolean();
		parameterrequired[3] = false;
	}

};


class cffrefindnocase : public cffunction
{
public:
	cffrefindnocase() {
		name = "REFindNoCase";
		returntype = T_OBJECT;

		parameters[0] = cfpreg_expression_regex();
		parameterrequired[0] = true;
		parameters[1] = cfpstring_string();
		parameterrequired[1] = true;
		parameters[2] = cfpstart_numeric();
		parameterrequired[2] = false;
		parameters[3] = cfpreturnsubexpressions_boolean();
		parameterrequired[3] = false;
	}

};


class cffreleasecomobject : public cffunction
{
public:
	cffreleasecomobject() {
		name = "ReleaseComObject";
		returntype = T_VOID;

		parameters[0] = cfpobjectname_object();
		parameterrequired[0] = true;
	}

};


class cffrematch : public cffunction
{
public:
	cffrematch() {
		name = "REMatch";
		returntype = T_ARRAY;

		parameters[0] = cfpreg_expression_string();
		parameterrequired[0] = true;
		parameters[1] = cfpstring_string();
		parameterrequired[1] = true;
	}

};


class cffrematchnocase : public cffunction
{
public:
	cffrematchnocase() {
		name = "REMatchNoCase";
		returntype = T_ARRAY;

		parameters[0] = cfpreg_expression_string();
		parameterrequired[0] = true;
		parameters[1] = cfpstring_string();
		parameterrequired[1] = true;
	}

};


class cffremovechars : public cffunction
{
public:
	cffremovechars() {
		name = "RemoveChars";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpstart_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpcount_numeric();
		parameterrequired[2] = true;
	}

};


class cffrepeatstring : public cffunction
{
public:
	cffrepeatstring() {
		name = "RepeatString";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpcount_numeric();
		parameterrequired[1] = true;
	}

};


class cffreplace : public cffunction
{
public:
	cffreplace() {
		name = "Replace";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpsubstring1_string();
		parameterrequired[1] = true;
		parameters[2] = cfpsubstring2_string();
		parameterrequired[2] = true;
		parameters[3] = cfpscope_string();
		parameterrequired[3] = false;
	}

};


class cffreplacelist : public cffunction
{
public:
	cffreplacelist() {
		name = "ReplaceList";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfplist1_string();
		parameterrequired[1] = true;
		parameters[2] = cfplist2_string();
		parameterrequired[2] = true;
	}

};


class cffreplacenocase : public cffunction
{
public:
	cffreplacenocase() {
		name = "ReplaceNoCase";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpsubstring1_string();
		parameterrequired[1] = true;
		parameters[2] = cfpsubstring2_string();
		parameterrequired[2] = true;
		parameters[3] = cfpscope_string();
		parameterrequired[3] = false;
	}

};


class cffrereplace : public cffunction
{
public:
	cffrereplace() {
		name = "REReplace";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpreg_expression_regex();
		parameterrequired[1] = true;
		parameters[2] = cfpsubstring_string();
		parameterrequired[2] = true;
		parameters[3] = cfpscope_string();
		parameterrequired[3] = false;
	}

};


class cffrereplacenocase : public cffunction
{
public:
	cffrereplacenocase() {
		name = "REReplaceNoCase";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpreg_expression_regex();
		parameterrequired[1] = true;
		parameters[2] = cfpsubstring_string();
		parameterrequired[2] = true;
		parameters[3] = cfpscope_string();
		parameterrequired[3] = false;
	}

};


class cffreverse : public cffunction
{
public:
	cffreverse() {
		name = "Reverse";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
	}

};


class cffright : public cffunction
{
public:
	cffright() {
		name = "Right";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpcount_numeric();
		parameterrequired[1] = true;
	}

};


class cffrjustify : public cffunction
{
public:
	cffrjustify() {
		name = "RJustify";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfplength_numeric();
		parameterrequired[1] = true;
	}

};


class cffround : public cffunction
{
public:
	cffround() {
		name = "Round";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
	}

};


class cffrtrim : public cffunction
{
public:
	cffrtrim() {
		name = "RTrim";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
	}

};


class cffsecond : public cffunction
{
public:
	cffsecond() {
		name = "Second";
		returntype = T_NUMERIC;

		parameters[0] = cfpdate_datetime();
		parameterrequired[0] = true;
	}

};


class cffsendgatewaymessage : public cffunction
{
public:
	cffsendgatewaymessage() {
		name = "SendGatewayMessage";
		returntype = T_STRING;

		parameters[0] = cfpgatewayid_string();
		parameterrequired[0] = true;
		parameters[1] = cfpdata_struct();
		parameterrequired[1] = true;
	}

};


class cffserializejson : public cffunction
{
public:
	cffserializejson() {
		name = "SerializeJSON";
		returntype = T_STRING;

		parameters[0] = cfpvar_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpserializequerybycolumns_boolean();
		parameterrequired[1] = false;
	}

};


class cffsetencoding : public cffunction
{
public:
	cffsetencoding() {
		name = "SetEncoding";
		returntype = T_VOID;

		parameters[0] = cfpscope_name_string();
		parameterrequired[0] = true;
		parameters[1] = cfpcharset_string();
		parameterrequired[1] = true;
	}

};


class cffsetlocale : public cffunction
{
public:
	cffsetlocale() {
		name = "SetLocale";
		returntype = T_STRING;

		parameters[0] = cfpnew_locale_string();
		parameterrequired[0] = true;
	}

};


class cffsetprofilestring : public cffunction
{
public:
	cffsetprofilestring() {
		name = "SetProfileString";
		returntype = T_STRING;

		parameters[0] = cfpinipath_string();
		parameterrequired[0] = true;
		parameters[1] = cfpsection_string();
		parameterrequired[1] = true;
		parameters[2] = cfpentry_string();
		parameterrequired[2] = true;
		parameters[3] = cfpvalue_string();
		parameterrequired[3] = true;
	}

};


class cffsetvariable : public cffunction
{
public:
	cffsetvariable() {
		name = "SetVariable";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpvalue_string();
		parameterrequired[1] = true;
	}

};


class cffsgn : public cffunction
{
public:
	cffsgn() {
		name = "Sgn";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
	}

};


class cffsin : public cffunction
{
public:
	cffsin() {
		name = "Sin";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
	}

};


class cffsleep : public cffunction
{
public:
	cffsleep() {
		name = "Sleep";
		returntype = T_VOID;

		parameters[0] = cfpduration_numeric();
		parameterrequired[0] = true;
	}

};


class cffspanexcluding : public cffunction
{
public:
	cffspanexcluding() {
		name = "SpanExcluding";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpset_string();
		parameterrequired[1] = true;
	}

};


class cffspanincluding : public cffunction
{
public:
	cffspanincluding() {
		name = "SpanIncluding";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpset_string();
		parameterrequired[1] = true;
	}

};


class cffspreadsheetaddcolumn : public cffunction
{
public:
	cffspreadsheetaddcolumn() {
		name = "SpreadsheetAddColumn";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpdata_string();
		parameterrequired[1] = true;
		parameters[2] = cfpstartrow_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpstartcolumn_numeric();
		parameterrequired[3] = true;
		parameters[4] = cfpinsert_boolean();
		parameterrequired[4] = true;
		parameters[5] = cfpinsert_boolean();
		parameterrequired[5] = false;
	}

};


class cffspreadsheetaddfreezepane : public cffunction
{
public:
	cffspreadsheetaddfreezepane() {
		name = "SpreadsheetAddFreezePane";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpcolumn_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfprow_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpendcolumn_numeric();
		parameterrequired[3] = false;
		parameters[4] = cfpendrow_numeric();
		parameterrequired[4] = false;
	}

};

/*
class cffspreadsheetaddimage : public cffunction
{
public:
cffspreadsheetaddimage()
{
name = "SpreadsheetAddImage";
returntype = T_VOID;

parameters[0] = cfpspreadsheetobj_variablename();
parameterrequired[0] = true;
parameters[1] = cfpimagefilepath_string();
parameterrequired[1] = true;
parameters[2] = cfpanchor_string();
parameterrequired[2] = true;
}

};*/


class cffspreadsheetaddimage : public cffunction
{
public:
	cffspreadsheetaddimage() {
		name = "SpreadsheetAddImage";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpimagedata_string();
		parameterrequired[1] = true;
		parameters[2] = cfpimagetype_string();
		parameterrequired[2] = true;
		parameters[3] = cfpanchor_string();
		parameterrequired[3] = true;
	}

};


class cffspreadsheetaddinfo : public cffunction
{
public:
	cffspreadsheetaddinfo() {
		name = "SpreadsheetAddInfo";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpinfo_struct();
		parameterrequired[1] = true;
	}

};


class cffspreadsheetaddrow : public cffunction
{
public:
	cffspreadsheetaddrow() {
		name = "SpreadsheetAddRow";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpdata_string();
		parameterrequired[1] = true;
		parameters[2] = cfprow_numeric();
		parameterrequired[2] = false;
		parameters[3] = cfpcolumn_numeric();
		parameterrequired[3] = false;
		parameters[4] = cfpinsert_boolean();
		parameterrequired[4] = false;
	}

};


class cffspreadsheetaddrows : public cffunction
{
public:
	cffspreadsheetaddrows() {
		name = "SpreadsheetAddRows";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpdata_string();
		parameterrequired[1] = true;
		parameters[2] = cfprow_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpinsert_boolean();
		parameterrequired[3] = false;
	}

};


class cffspreadsheetaddsplitpane : public cffunction
{
public:
	cffspreadsheetaddsplitpane() {
		name = "SpreadsheetAddSplitPane";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpx_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpy_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpsplitcolumn_numeric();
		parameterrequired[3] = true;
		parameters[4] = cfpsplitrow_numeric();
		parameterrequired[4] = true;
		parameters[5] = cfpposition_string();
		parameterrequired[5] = false;
	}

};


class cffspreadsheetcreatesheet : public cffunction
{
public:
	cffspreadsheetcreatesheet() {
		name = "SpreadsheetCreateSheet";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpname_string();
		parameterrequired[1] = true;
	}

};


class cffspreadsheetdeletecolumn : public cffunction
{
public:
	cffspreadsheetdeletecolumn() {
		name = "SpreadsheetDeleteColumn";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpcolumn_numeric();
		parameterrequired[1] = true;
	}

};


class cffspreadsheetdeletecolumns : public cffunction
{
public:
	cffspreadsheetdeletecolumns() {
		name = "SpreadsheetDeleteColumns";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfprange_numeric();
		parameterrequired[1] = true;
	}

};


class cffspreadsheetdeleterow : public cffunction
{
public:
	cffspreadsheetdeleterow() {
		name = "SpreadsheetDeleteRow";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfprow_numeric();
		parameterrequired[1] = true;
	}

};


class cffspreadsheetdeleterows : public cffunction
{
public:
	cffspreadsheetdeleterows() {
		name = "SpreadsheetDeleteRows";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfprange_numeric();
		parameterrequired[1] = true;
	}

};


class cffspreadsheetformatcell : public cffunction
{
public:
	cffspreadsheetformatcell() {
		name = "SpreadsheetFormatCell";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpformat_string();
		parameterrequired[1] = true;
		parameters[2] = cfprow_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpcolumn_numeric();
		parameterrequired[3] = true;
	}

};


class cffspreadsheetformatcolumn : public cffunction
{
public:
	cffspreadsheetformatcolumn() {
		name = "SpreadsheetFormatColumn";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpformat_string();
		parameterrequired[1] = true;
		parameters[2] = cfpcolumn_numeric();
		parameterrequired[2] = true;
	}

};


class cffspreadsheetformatcolumns : public cffunction
{
public:
	cffspreadsheetformatcolumns() {
		name = "SpreadsheetFormatColumns";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpformat_string();
		parameterrequired[1] = true;
		parameters[2] = cfpcolumns_string();
		parameterrequired[2] = true;
	}

};


class cffspreadsheetformatrow : public cffunction
{
public:
	cffspreadsheetformatrow() {
		name = "SpreadsheetFormatRow";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpformat_string();
		parameterrequired[1] = true;
		parameters[2] = cfprow_numeric();
		parameterrequired[2] = true;
	}

};


class cffspreadsheetformatrows : public cffunction
{
public:
	cffspreadsheetformatrows() {
		name = "SpreadsheetFormatRows";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpformat_string();
		parameterrequired[1] = true;
		parameters[2] = cfprow_numeric();
		parameterrequired[2] = true;
	}

};


class cffspreadsheetgetcellcomment : public cffunction
{
public:
	cffspreadsheetgetcellcomment() {
		name = "SpreadsheetGetCellComment";
		returntype = T_ARRAY;

		parameters[0] = cfpauthor_string();
		parameterrequired[0] = true;
		parameters[1] = cfpcolumn_numeric();
		parameterrequired[1] = false;
		parameters[2] = cfpcomment_string();
		parameterrequired[2] = false;
		parameters[3] = cfprow_string();
		parameterrequired[3] = false;
	}

};


class cffspreadsheetgetcellformula : public cffunction
{
public:
	cffspreadsheetgetcellformula() {
		name = "SpreadsheetGetCellFormula";
		returntype = T_STRING;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfprow_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpcolumn_numeric();
		parameterrequired[2] = true;
	}

};


class cffspreadsheetgetcellvalue : public cffunction
{
public:
	cffspreadsheetgetcellvalue() {
		name = "SpreadsheetGetCellValue";
		returntype = T_STRING;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfprow_string();
		parameterrequired[1] = true;
		parameters[2] = cfpcolumn_string();
		parameterrequired[2] = true;
	}

};


class cffspreadsheetinfo : public cffunction
{
public:
	cffspreadsheetinfo() {
		name = "SpreadsheetInfo";
		returntype = T_STRUCT;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
	}

};


class cffspreadsheetmergecells : public cffunction
{
public:
	cffspreadsheetmergecells() {
		name = "SpreadsheetMergeCells";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpstartrow_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpendrow_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpstartcolumn_numeric();
		parameterrequired[3] = true;
		parameters[4] = cfpendcolumn_numeric();
		parameterrequired[4] = true;
	}

};


class cffspreadsheetnew : public cffunction
{
public:
	cffspreadsheetnew() {
		name = "SpreadsheetNew";
		returntype = T_VOID;

		parameters[0] = cfpsheetname_string();
		parameterrequired[0] = false;
		parameters[1] = cfpxmlformat_boolean();
		parameterrequired[1] = false;
	}

};


class cffspreadsheetread : public cffunction
{
public:
	cffspreadsheetread() {
		name = "SpreadsheetRead";
		returntype = T_VOID;

		parameters[0] = cfpfilename_string();
		parameterrequired[0] = true;
		parameters[1] = cfpspreadsheetobj_variablename();
		parameterrequired[1] = true;
	}

};


class cffspreadsheetreadbinary : public cffunction
{
public:
	cffspreadsheetreadbinary() {
		name = "SpreadsheetReadBinary";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
	}

};


class cffspreadsheetsetactivesheet : public cffunction
{
public:
	cffspreadsheetsetactivesheet() {
		name = "SpreadsheetSetActiveSheet";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpname_string();
		parameterrequired[1] = false;
	}

};


class cffspreadsheetsetactivesheetnumber : public cffunction
{
public:
	cffspreadsheetsetactivesheetnumber() {
		name = "SpreadsheetSetActiveSheetNumber";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpnumber_numeric();
		parameterrequired[1] = false;
	}

};


class cffspreadsheetsetcellcomment : public cffunction
{
public:
	cffspreadsheetsetcellcomment() {
		name = "SpreadsheetSetCellComment";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpcomment_string();
		parameterrequired[1] = true;
		parameters[2] = cfprow_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpcolumn_numeric();
		parameterrequired[3] = true;
	}

};


class cffspreadsheetsetcellformula : public cffunction
{
public:
	cffspreadsheetsetcellformula() {
		name = "SpreadsheetSetCellFormula";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpformula_string();
		parameterrequired[1] = true;
		parameters[2] = cfprow_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpcolumn_numeric();
		parameterrequired[3] = true;
	}

};


class cffspreadsheetsetcellvalue : public cffunction
{
public:
	cffspreadsheetsetcellvalue() {
		name = "SpreadsheetSetCellValue";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpvalue_string();
		parameterrequired[1] = true;
		parameters[2] = cfprow_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfpcolumn_numeric();
		parameterrequired[3] = true;
	}

};


class cffspreadsheetsetcolumnwidth : public cffunction
{
public:
	cffspreadsheetsetcolumnwidth() {
		name = "SpreadsheetSetColumnWidth";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpcolumnnumber_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpwidth_numeric();
		parameterrequired[2] = true;
	}

};


class cffspreadsheetsetfooter : public cffunction
{
public:
	cffspreadsheetsetfooter() {
		name = "SpreadsheetSetFooter";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpleftfooter_string();
		parameterrequired[1] = true;
		parameters[2] = cfpcenterfooter_string();
		parameterrequired[2] = true;
		parameters[3] = cfprightfooter_string();
		parameterrequired[3] = true;
	}

};


class cffspreadsheetsetheader : public cffunction
{
public:
	cffspreadsheetsetheader() {
		name = "SpreadsheetSetHeader";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpleftheader_string();
		parameterrequired[1] = true;
		parameters[2] = cfpcenterheader_string();
		parameterrequired[2] = true;
		parameters[3] = cfprightheader_string();
		parameterrequired[3] = true;
	}

};


class cffspreadsheetsetrowheight : public cffunction
{
public:
	cffspreadsheetsetrowheight() {
		name = "SpreadsheetSetRowHeight";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfprownumber_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpheight_numeric();
		parameterrequired[2] = true;
	}

};


class cffspreadsheetshiftcolumns : public cffunction
{
public:
	cffspreadsheetshiftcolumns() {
		name = "SpreadsheetShiftColumns";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpstart_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpend_numeric();
		parameterrequired[2] = false;
		parameters[3] = cfpstart_numeric();
		parameterrequired[3] = false;
	}

};


class cffspreadsheetshiftrows : public cffunction
{
public:
	cffspreadsheetshiftrows() {
		name = "SpreadsheetShiftRows";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpstart_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpend_numeric();
		parameterrequired[2] = true;
		parameters[3] = cfprows_numeric();
		parameterrequired[3] = false;
	}

};


class cffspreadsheetwrite : public cffunction
{
public:
	cffspreadsheetwrite() {
		name = "SpreadsheetWrite";
		returntype = T_VOID;

		parameters[0] = cfpspreadsheetobj_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpfilename_string();
		parameterrequired[1] = true;
		parameters[2] = cfppassword_string();
		parameterrequired[2] = false;
		parameters[3] = cfpoverwrite_boolean();
		parameterrequired[3] = false;
	}

};


class cffsqr : public cffunction
{
public:
	cffsqr() {
		name = "Sqr";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
	}

};


class cffstripcr : public cffunction
{
public:
	cffstripcr() {
		name = "StripCR";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
	}

};


class cffstructappend : public cffunction
{
public:
	cffstructappend() {
		name = "StructAppend";
		returntype = T_BOOLEAN;

		parameters[0] = cfpstruct1_struct();
		parameterrequired[0] = true;
		parameters[1] = cfpstruct2_struct();
		parameterrequired[1] = true;
		parameters[2] = cfpoverwriteflag_boolean();
		parameterrequired[2] = false;
	}

};


class cffstructclear : public cffunction
{
public:
	cffstructclear() {
		name = "StructClear";
		returntype = T_BOOLEAN;

		parameters[0] = cfpstructure_struct();
		parameterrequired[0] = true;
	}

};


class cffstructcopy : public cffunction
{
public:
	cffstructcopy() {
		name = "StructCopy";
		returntype = T_STRUCT;

		parameters[0] = cfpstructure_struct();
		parameterrequired[0] = true;
	}

};


class cffstructcount : public cffunction
{
public:
	cffstructcount() {
		name = "StructCount";
		returntype = T_NUMERIC;

		parameters[0] = cfpstructure_struct();
		parameterrequired[0] = true;
	}

};


class cffstructdelete : public cffunction
{
public:
	cffstructdelete() {
		name = "StructDelete";
		returntype = T_BOOLEAN;

		parameters[0] = cfpstructure_struct();
		parameterrequired[0] = true;
		parameters[1] = cfpkey_string();
		parameterrequired[1] = true;
		parameters[2] = cfpindicatenotexisting_boolean();
		parameterrequired[2] = false;
	}

};


class cffstructfind : public cffunction
{
public:
	cffstructfind() {
		name = "StructFind";
		returntype = T_OBJECT;

		parameters[0] = cfpstructure_struct();
		parameterrequired[0] = true;
		parameters[1] = cfpkey_string();
		parameterrequired[1] = true;
	}

};


class cffstructfindkey : public cffunction
{
public:
	cffstructfindkey() {
		name = "StructFindKey";
		returntype = T_ARRAY;

		parameters[0] = cfptop_object();
		parameterrequired[0] = true;
		parameters[1] = cfpvalue_string();
		parameterrequired[1] = true;
		parameters[2] = cfpscope_string();
		parameterrequired[2] = true;
	}

};


class cffstructfindvalue : public cffunction
{
public:
	cffstructfindvalue() {
		name = "StructFindValue";
		returntype = T_ARRAY;

		parameters[0] = cfptop_object();
		parameterrequired[0] = true;
		parameters[1] = cfpvalue_string();
		parameterrequired[1] = true;
		parameters[2] = cfpscope_string();
		parameterrequired[2] = false;
	}

};


class cffstructget : public cffunction
{
public:
	cffstructget() {
		name = "StructGet";
		returntype = T_STRUCT;

		parameters[0] = cfppathdesired_string();
		parameterrequired[0] = true;
	}

};


class cffstructinsert : public cffunction
{
public:
	cffstructinsert() {
		name = "StructInsert";
		returntype = T_BOOLEAN;

		parameters[0] = cfpstructure_struct();
		parameterrequired[0] = true;
		parameters[1] = cfpkey_string();
		parameterrequired[1] = true;
		parameters[2] = cfpvalue_object();
		parameterrequired[2] = true;
		parameters[3] = cfpallowoverwrite_boolean();
		parameterrequired[3] = false;
	}

};


class cffstructisempty : public cffunction
{
public:
	cffstructisempty() {
		name = "StructIsEmpty";
		returntype = T_BOOLEAN;

		parameters[0] = cfpstructure_struct();
		parameterrequired[0] = true;
	}

};


class cffstructkeyarray : public cffunction
{
public:
	cffstructkeyarray() {
		name = "StructKeyArray";
		returntype = T_ARRAY;

		parameters[0] = cfpstructure_struct();
		parameterrequired[0] = true;
	}

};


class cffstructkeyexists : public cffunction
{
public:
	cffstructkeyexists() {
		name = "StructKeyExists";
		returntype = T_BOOLEAN;

		parameters[0] = cfpstructure_struct();
		parameterrequired[0] = true;
		parameters[1] = cfpkey_string();
		parameterrequired[1] = true;
	}

};


class cffstructkeylist : public cffunction
{
public:
	cffstructkeylist() {
		name = "StructKeyList";
		returntype = T_STRING;

		parameters[0] = cfpstructure_struct();
		parameterrequired[0] = true;
		parameters[1] = cfpdelimiter_string();
		parameterrequired[1] = false;
	}

};


class cffstructnew : public cffunction
{
public:
	cffstructnew() {
		name = "StructNew";
		returntype = T_STRUCT;

		parameters[0] = cfpstructure_struct();
		parameterrequired[0] = true;
		parameters[1] = cfpdelimiter_string();
		parameterrequired[1] = false;
	}

};


class cffstructsort : public cffunction
{
public:
	cffstructsort() {
		name = "StructSort";
		returntype = T_ARRAY;

		parameters[0] = cfpbase_struct();
		parameterrequired[0] = true;
		parameters[1] = cfpsorttype_string();
		parameterrequired[1] = true;
		parameters[2] = cfpsortorder_string();
		parameterrequired[2] = true;
		parameters[3] = cfppathtosubelement_string();
		parameterrequired[3] = true;
	}

};


class cffstructupdate : public cffunction
{
public:
	cffstructupdate() {
		name = "StructUpdate";
		returntype = T_BOOLEAN;

		parameters[0] = cfpstructure_struct();
		parameterrequired[0] = true;
		parameters[1] = cfpkey_string();
		parameterrequired[1] = true;
		parameters[2] = cfpvalue_object();
		parameterrequired[2] = true;
	}

};


class cfftan : public cffunction
{
public:
	cfftan() {
		name = "Tan";
		returntype = T_NUMERIC;

		parameters[0] = cfpnumber_numeric();
		parameterrequired[0] = true;
	}

};


class cffthreadjoin : public cffunction
{
public:
	cffthreadjoin() {
		name = "ThreadJoin";
		returntype = T_VOID;

		parameters[0] = cfpthreadname_string();
		parameterrequired[0] = false;
		parameters[1] = cfptimeout_numeric();
		parameterrequired[1] = false;
	}

};


class cffthreadterminate : public cffunction
{
public:
	cffthreadterminate() {
		name = "ThreadTerminate";
		returntype = T_VOID;

		parameters[0] = cfpthreadname_string();
		parameterrequired[0] = true;
	}

};


class cffthrow : public cffunction
{
public:
	cffthrow() {
		name = "Throw";
		returntype = T_NUMERIC;

		parameters[0] = cfptype_string();
		parameterrequired[0] = false;
		parameters[1] = cfpmessage_string();
		parameterrequired[1] = false;
		parameters[2] = cfpdetail_string();
		parameterrequired[2] = false;
		parameters[3] = cfperrorcode_string();
		parameterrequired[3] = false;
		parameters[4] = cfpextendedinfo_string();
		parameterrequired[4] = false;
		parameters[5] = cfpobject_object();
		parameterrequired[5] = false;
	}

};


class cfftimeformat : public cffunction
{
public:
	cfftimeformat() {
		name = "TimeFormat";
		returntype = T_STRING;

		parameters[0] = cfptime_datetime();
		parameterrequired[0] = true;
		parameters[1] = cfpmask_string();
		parameterrequired[1] = false;
	}

};


class cfftobase64 : public cffunction
{
public:
	cfftobase64() {
		name = "ToBase64";
		returntype = T_STRING;

		parameters[0] = cfpstring_or_object_object();
		parameterrequired[0] = true;
		parameters[1] = cfpencoding_string();
		parameterrequired[1] = false;
	}

};


class cfftobinary : public cffunction
{
public:
	cfftobinary() {
		name = "ToBinary";
		returntype = T_BINARY;

		parameters[0] = cfpbase64_or_object_object();
		parameterrequired[0] = true;
	}

};


class cfftoscript : public cffunction
{
public:
	cfftoscript() {
		name = "ToScript";
		returntype = T_STRING;

		parameters[0] = cfpcfvar_object();
		parameterrequired[0] = true;
		parameters[1] = cfpjavascriptvar_string();
		parameterrequired[1] = true;
		parameters[2] = cfpoutputformat_boolean();
		parameterrequired[2] = false;
		parameters[3] = cfpasformat_boolean();
		parameterrequired[3] = false;
	}

};


class cfftostring : public cffunction
{
public:
	cfftostring() {
		name = "ToString";
		returntype = T_STRING;

		parameters[0] = cfpany_value_object();
		parameterrequired[0] = true;
		parameters[1] = cfpencoding_string();
		parameterrequired[1] = false;
	}

};


class cfftrace : public cffunction
{
public:
	cfftrace() {
		name = "Trace";
		returntype = T_VOID;

		parameters[0] = cfpabort_boolean();
		parameterrequired[0] = false;
		parameters[1] = cfpcategory_string();
		parameterrequired[1] = false;
		parameters[2] = cfpinline_boolean();
		parameterrequired[2] = false;
		parameters[3] = cfptext_string();
		parameterrequired[3] = false;
		parameters[4] = cfptype_string();
		parameterrequired[4] = false;
		parameters[5] = cfpvar_string();
		parameterrequired[5] = false;
	}

};


class cfftransactioncommit : public cffunction
{
public:
	cfftransactioncommit() {
		name = "TransactionCommit";
		returntype = T_VOID;

		parameters[0] = cfpabort_boolean();
		parameterrequired[0] = false;
		parameters[1] = cfpcategory_string();
		parameterrequired[1] = false;
		parameters[2] = cfpinline_boolean();
		parameterrequired[2] = false;
		parameters[3] = cfptext_string();
		parameterrequired[3] = false;
		parameters[4] = cfptype_string();
		parameterrequired[4] = false;
		parameters[5] = cfpvar_string();
		parameterrequired[5] = false;
	}

};


class cfftransactionrollback : public cffunction
{
public:
	cfftransactionrollback() {
		name = "TransactionRollback";
		returntype = T_VOID;

		parameters[0] = cfpsavepoint_string();
		parameterrequired[0] = false;
	}

};


class cfftransactionsetsavepoint : public cffunction
{
public:
	cfftransactionsetsavepoint() {
		name = "TransactionSetSavePoint";
		returntype = T_VOID;

		parameters[0] = cfpsavepoint_string();
		parameterrequired[0] = true;
	}

};


class cfftrim : public cffunction
{
public:
	cfftrim() {
		name = "Trim";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
	}

};


class cffucase : public cffunction
{
public:
	cffucase() {
		name = "UCase";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
	}

};


class cffurldecode : public cffunction
{
public:
	cffurldecode() {
		name = "URLDecode";
		returntype = T_STRING;

		parameters[0] = cfpurlencodedstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpcharset_string();
		parameterrequired[1] = false;
	}

};


class cffurlencodedformat : public cffunction
{
public:
	cffurlencodedformat() {
		name = "URLEncodedFormat";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpcharset_string();
		parameterrequired[1] = false;
	}

};


class cffurlsessionformat : public cffunction
{
public:
	cffurlsessionformat() {
		name = "URLSessionFormat";
		returntype = T_STRING;

		parameters[0] = cfprequesturl_string();
		parameterrequired[0] = true;
	}

};


class cffval : public cffunction
{
public:
	cffval() {
		name = "Val";
		returntype = T_NUMERIC;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
	}

};


class cffvaluelist : public cffunction
{
public:
	cffvaluelist() {
		name = "ValueList";
		returntype = T_STRING;

		parameters[0] = cfpcolumn_querycolumn();
		parameterrequired[0] = true;
		parameters[1] = cfpdelimiter_string();
		parameterrequired[1] = false;
	}

};


class cffverifyclient : public cffunction
{
public:
	cffverifyclient() {
		name = "VerifyClient";
		returntype = T_VOID;

		parameters[0] = cfpcolumn_querycolumn();
		parameterrequired[0] = true;
		parameters[1] = cfpdelimiter_string();
		parameterrequired[1] = false;
	}

};


class cffweek : public cffunction
{
public:
	cffweek() {
		name = "Week";
		returntype = T_NUMERIC;

		parameters[0] = cfpdate_datetime();
		parameterrequired[0] = true;
	}

};


class cffwrap : public cffunction
{
public:
	cffwrap() {
		name = "Wrap";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfplimit_numeric();
		parameterrequired[1] = true;
		parameters[2] = cfpstrip_boolean();
		parameterrequired[2] = false;
	}

};


class cffwritedump : public cffunction
{
public:
	cffwritedump() {
		name = "WriteDump";
		returntype = T_VOID;

		parameters[0] = cfpvar_variablename();
		parameterrequired[0] = true;
		parameters[1] = cfpexpand_boolean();
		parameterrequired[1] = false;
		parameters[2] = cfpformat_string();
		parameterrequired[2] = false;
		parameters[3] = cfphide_string();
		parameterrequired[3] = false;
		parameters[4] = cfpkeys_numeric();
		parameterrequired[4] = false;
		parameters[5] = cfplabel_string();
		parameterrequired[5] = false;
		parameters[6] = cfpmetainfo_boolean();
		parameterrequired[6] = false;
		parameters[7] = cfpoutput_string();
		parameterrequired[7] = false;
		parameters[8] = cfpshow_string();
		parameterrequired[8] = false;
		parameters[9] = cfpshowudfs_boolean();
		parameterrequired[9] = false;
		parameters[10] = cfptop_numeric();
		parameterrequired[10] = false;
	}

};


class cffwritelog : public cffunction
{
public:
	cffwritelog() {
		name = "WriteLog";
		returntype = T_VOID;

		parameters[0] = cfptext_string();
		parameterrequired[0] = true;
		parameters[1] = cfplog_string();
		parameterrequired[1] = false;
		parameters[2] = cfpfile_string();
		parameterrequired[2] = false;
		parameters[3] = cfptype_string();
		parameterrequired[3] = false;
		parameters[4] = cfpapplication_boolean();
		parameterrequired[4] = false;
	}

};


class cffwriteoutput : public cffunction
{
public:
	cffwriteoutput() {
		name = "WriteOutput";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
	}

};


class cffxmlchildpos : public cffunction
{
public:
	cffxmlchildpos() {
		name = "XmlChildPos";
		returntype = T_NUMERIC;

		parameters[0] = cfpelem_node();
		parameterrequired[0] = true;
		parameters[1] = cfpchildname_string();
		parameterrequired[1] = true;
		parameters[2] = cfpn_numeric();
		parameterrequired[2] = true;
	}

};


class cffxmlelemnew : public cffunction
{
public:
	cffxmlelemnew() {
		name = "XmlElemNew";
		returntype = T_OBJECT;

		parameters[0] = cfpxmlobj_object();
		parameterrequired[0] = true;
		parameters[1] = cfpnamespace_string();
		parameterrequired[1] = false;
		parameters[2] = cfpchildname_string();
		parameterrequired[2] = true;
	}

};


class cffxmlformat : public cffunction
{
public:
	cffxmlformat() {
		name = "XmlFormat";
		returntype = T_STRING;

		parameters[0] = cfpstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpescapenewset_boolean();
		parameterrequired[1] = false;
	}

};


class cffxmlgetnodetype : public cffunction
{
public:
	cffxmlgetnodetype() {
		name = "XmlGetNodeType";
		returntype = T_STRING;

		parameters[0] = cfpxmlnode_object();
		parameterrequired[0] = true;
	}

};


class cffxmlnew : public cffunction
{
public:
	cffxmlnew() {
		name = "XmlNew";
		returntype = T_OBJECT;

		parameters[0] = cfpcasesensitive_boolean();
		parameterrequired[0] = false;
	}

};


class cffxmlparse : public cffunction
{
public:
	cffxmlparse() {
		name = "XmlParse";
		returntype = T_OBJECT;

		parameters[0] = cfpxmlstring_string();
		parameterrequired[0] = true;
		parameters[1] = cfpcasesensitive_boolean();
		parameterrequired[1] = false;
		parameters[2] = cfpvalidator_string();
		parameterrequired[2] = false;
	}

};


class cffxmlsearch : public cffunction
{
public:
	cffxmlsearch() {
		name = "XmlSearch";
		returntype = T_ARRAY;

		parameters[0] = cfpxmldoc_object();
		parameterrequired[0] = true;
		parameters[1] = cfpxpathstring_string();
		parameterrequired[1] = true;
	}

};


class cffxmltransform : public cffunction
{
public:
	cffxmltransform() {
		name = "XmlTransform";
		returntype = T_STRING;

		parameters[0] = cfpxml_string();
		parameterrequired[0] = true;
		parameters[1] = cfpxsl_string();
		parameterrequired[1] = true;
		parameters[2] = cfpparameters_struct();
		parameterrequired[2] = false;
	}

};


class cffxmlvalidate : public cffunction
{
public:
	cffxmlvalidate() {
		name = "XmlValidate";
		returntype = T_STRUCT;

		parameters[0] = cfpxmldoc_object();
		parameterrequired[0] = true;
		parameters[1] = cfpvalidator_string();
		parameterrequired[1] = false;
	}

};


class cffyear : public cffunction
{
public:
	cffyear() {
		name = "Year";
		returntype = T_NUMERIC;

		parameters[0] = cfpdate_datetime();
		parameterrequired[0] = true;
	}

};


class cffyesnoformat : public cffunction
{
public:
	cffyesnoformat() {
		name = "YesNoFormat";
		returntype = T_STRING;

		parameters[0] = cfpvalue_boolean();
		parameterrequired[0] = true;
	}

};
cffunction getfunction(const char* input);
const char* getTypeAsString(cftypes type);



#ifdef NPP_CFWHEELS


class cfwfadderror : public cffunction
{
public:
	cfwfadderror() {
		name = "addError";
		returntype = T_VOID;

		parameters[0] = cfpproperty_string();
		parameterrequired[0] = true;
		parameters[1] = cfpmessage_string();
		parameterrequired[1] = true;
		parameters[2] = cfpname_string();
		parameterrequired[2] = false;
	}

};


class cfwfadderrortobase : public cffunction
{
public:
	cfwfadderrortobase() {
		name = "addErrorToBase";
		returntype = T_VOID;

		parameters[0] = cfpmessage_string();
		parameterrequired[0] = true;
		parameters[1] = cfpname_string();
		parameterrequired[1] = false;
	}

};


class cfwfaddroute : public cffunction
{
public:
	cfwfaddroute() {
		name = "addRoute";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfppattern_string();
		parameterrequired[1] = true;
		parameters[2] = cfpcontroller_string();
		parameterrequired[2] = false;
		parameters[3] = cfpaction_string();
		parameterrequired[3] = false;
	}

};


class cfwfaftercreate : public cffunction
{
public:
	cfwfaftercreate() {
		name = "afterCreate";
		returntype = T_VOID;

		parameters[0] = cfpmethods_string();
		parameterrequired[0] = false;
	}

};


class cfwfafterdelete : public cffunction
{
public:
	cfwfafterdelete() {
		name = "afterDelete";
		returntype = T_VOID;

		parameters[0] = cfpmethods_string();
		parameterrequired[0] = false;
	}

};


class cfwfafterfind : public cffunction
{
public:
	cfwfafterfind() {
		name = "afterFind";
		returntype = T_VOID;

		parameters[0] = cfpmethods_string();
		parameterrequired[0] = false;
	}

};


class cfwfafterinitialization : public cffunction
{
public:
	cfwfafterinitialization() {
		name = "afterInitialization";
		returntype = T_VOID;

		parameters[0] = cfpmethods_string();
		parameterrequired[0] = false;
	}

};


class cfwfafternew : public cffunction
{
public:
	cfwfafternew() {
		name = "afterNew";
		returntype = T_VOID;

		parameters[0] = cfpmethods_string();
		parameterrequired[0] = false;
	}

};


class cfwfaftersave : public cffunction
{
public:
	cfwfaftersave() {
		name = "afterSave";
		returntype = T_VOID;

		parameters[0] = cfpmethods_string();
		parameterrequired[0] = false;
	}

};


class cfwfafterupdate : public cffunction
{
public:
	cfwfafterupdate() {
		name = "afterUpdate";
		returntype = T_VOID;

		parameters[0] = cfpmethods_string();
		parameterrequired[0] = false;
	}

};


class cfwfaftervalidation : public cffunction
{
public:
	cfwfaftervalidation() {
		name = "afterValidation";
		returntype = T_VOID;

		parameters[0] = cfpmethods_string();
		parameterrequired[0] = false;
	}

};


class cfwfaftervalidationoncreate : public cffunction
{
public:
	cfwfaftervalidationoncreate() {
		name = "afterValidationOnCreate";
		returntype = T_VOID;

		parameters[0] = cfpmethods_string();
		parameterrequired[0] = false;
	}

};


class cfwfaftervalidationonupdate : public cffunction
{
public:
	cfwfaftervalidationonupdate() {
		name = "afterValidationOnUpdate";
		returntype = T_VOID;

		parameters[0] = cfpmethods_string();
		parameterrequired[0] = false;
	}

};


class cfwfallchanges : public cffunction
{
public:
	cfwfallchanges() {
		name = "allChanges";
		returntype = T_STRUCT;

		parameters[0] = cfpmethods_string();
		parameterrequired[0] = false;
	}

};


class cfwfallerrors : public cffunction
{
public:
	cfwfallerrors() {
		name = "allErrors";
		returntype = T_ARRAY;

		parameters[0] = cfpmethods_string();
		parameterrequired[0] = false;
	}

};


class cfwfaverage : public cffunction
{
public:
	cfwfaverage() {
		name = "average";
		returntype = T_ANY;

		parameters[0] = cfpproperty_string();
		parameterrequired[0] = true;
		parameters[1] = cfpwhere_string();
		parameterrequired[1] = false;
		parameters[2] = cfpinclude_string();
		parameterrequired[2] = false;
		parameters[3] = cfpdistinct_boolean();
		parameterrequired[3] = false;
	}

};


class cfwfbeforecreate : public cffunction
{
public:
	cfwfbeforecreate() {
		name = "beforeCreate";
		returntype = T_VOID;

		parameters[0] = cfpmethods_string();
		parameterrequired[0] = false;
	}

};


class cfwfbeforedelete : public cffunction
{
public:
	cfwfbeforedelete() {
		name = "beforeDelete";
		returntype = T_VOID;

		parameters[0] = cfpmethods_string();
		parameterrequired[0] = false;
	}

};


class cfwfbeforesave : public cffunction
{
public:
	cfwfbeforesave() {
		name = "beforeSave";
		returntype = T_VOID;

		parameters[0] = cfpmethods_string();
		parameterrequired[0] = false;
	}

};


class cfwfbeforeupdate : public cffunction
{
public:
	cfwfbeforeupdate() {
		name = "beforeUpdate";
		returntype = T_VOID;

		parameters[0] = cfpmethods_string();
		parameterrequired[0] = false;
	}

};


class cfwfbeforevalidation : public cffunction
{
public:
	cfwfbeforevalidation() {
		name = "beforeValidation";
		returntype = T_VOID;

		parameters[0] = cfpmethods_string();
		parameterrequired[0] = false;
	}

};


class cfwfbeforevalidationoncreate : public cffunction
{
public:
	cfwfbeforevalidationoncreate() {
		name = "beforeValidationOnCreate";
		returntype = T_VOID;

		parameters[0] = cfpmethods_string();
		parameterrequired[0] = false;
	}

};


class cfwfbeforevalidationonupdate : public cffunction
{
public:
	cfwfbeforevalidationonupdate() {
		name = "beforeValidationOnUpdate";
		returntype = T_VOID;

		parameters[0] = cfpmethods_string();
		parameterrequired[0] = false;
	}

};


class cfwfbelongsto : public cffunction
{
public:
	cfwfbelongsto() {
		name = "belongsTo";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpclass_string();
		parameterrequired[1] = false;
		parameters[2] = cfpforeignkey_string();
		parameterrequired[2] = false;
		parameters[3] = cfpjointype_string();
		parameterrequired[3] = false;
	}

};


class cfwfbuttonto : public cffunction
{
public:
	cfwfbuttonto() {
		name = "buttonTo";
		returntype = T_STRING;

		parameters[0] = cfpwindowsize_numeric();
		parameterrequired[0] = false;
		parameters[1] = cfpalwaysshowanchors_boolean();
		parameterrequired[1] = false;
		parameters[2] = cfpanchordivider_string();
		parameterrequired[2] = false;
		parameters[3] = cfplinktocurrentpage_boolean();
		parameterrequired[3] = false;
		parameters[4] = cfpprepend_string();
		parameterrequired[4] = false;
		parameters[5] = cfpappend_string();
		parameterrequired[5] = false;
		parameters[6] = cfpprependtopage_string();
		parameterrequired[6] = false;
		parameters[7] = cfpprependonfirst_boolean();
		parameterrequired[7] = false;
		parameters[8] = cfpappendtopage_string();
		parameterrequired[8] = false;
		parameters[9] = cfpappendonlast_boolean();
		parameterrequired[9] = false;
		parameters[10] = cfpclassforcurrent_string();
		parameterrequired[10] = false;
		parameters[11] = cfphandle_string();
		parameterrequired[11] = false;
		parameters[12] = cfpname_string();
		parameterrequired[12] = false;
		parameters[13] = cfpshowsinglepage_boolean();
		parameterrequired[13] = false;
	}

};


class cfwfcaches : public cffunction
{
public:
	cfwfcaches() {
		name = "caches";
		returntype = T_VOID;

		parameters[0] = cfpactions_string();
		parameterrequired[0] = false;
		parameters[1] = cfptime_numeric();
		parameterrequired[1] = false;
	}

};


class cfwfcapitalize : public cffunction
{
public:
	cfwfcapitalize() {
		name = "capitalize";
		returntype = T_STRING;

		parameters[0] = cfptext_string();
		parameterrequired[0] = true;
	}

};


class cfwfchangedfrom : public cffunction
{
public:
	cfwfchangedfrom() {
		name = "changedFrom";
		returntype = T_STRING;

		parameters[0] = cfpproperty_string();
		parameterrequired[0] = true;
	}

};


class cfwfchangedproperties : public cffunction
{
public:
	cfwfchangedproperties() {
		name = "changedProperties";
		returntype = T_STRING;

		parameters[0] = cfpproperty_string();
		parameterrequired[0] = true;
	}

};


class cfwfcheckbox : public cffunction
{
public:
	cfwfcheckbox() {
		name = "checkBox";
		returntype = T_STRING;

		parameters[0] = cfpobjectname_any();
		parameterrequired[0] = true;
		parameters[1] = cfpproperty_string();
		parameterrequired[1] = true;
		parameters[2] = cfpcheckedvalue_string();
		parameterrequired[2] = false;
		parameters[3] = cfpuncheckedvalue_string();
		parameterrequired[3] = false;
		parameters[4] = cfplabel_string();
		parameterrequired[4] = false;
		parameters[5] = cfplabelplacement_string();
		parameterrequired[5] = false;
		parameters[6] = cfpprepend_string();
		parameterrequired[6] = false;
		parameters[7] = cfpappend_string();
		parameterrequired[7] = false;
		parameters[8] = cfpprependtolabel_string();
		parameterrequired[8] = false;
		parameters[9] = cfpappendtolabel_string();
		parameterrequired[9] = false;
		parameters[10] = cfperrorelement_string();
		parameterrequired[10] = false;
	}

};


class cfwfcheckboxtag : public cffunction
{
public:
	cfwfcheckboxtag() {
		name = "checkBoxTag";
		returntype = T_STRING;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpchecked_boolean();
		parameterrequired[1] = false;
		parameters[2] = cfpvalue_string();
		parameterrequired[2] = false;
		parameters[3] = cfplabel_string();
		parameterrequired[3] = false;
		parameters[4] = cfplabelplacement_string();
		parameterrequired[4] = false;
		parameters[5] = cfpprepend_string();
		parameterrequired[5] = false;
		parameters[6] = cfpappend_string();
		parameterrequired[6] = false;
		parameters[7] = cfpprependtolabel_string();
		parameterrequired[7] = false;
		parameters[8] = cfpappendtolabel_string();
		parameterrequired[8] = false;
	}

};


class cfwfclearerrors : public cffunction
{
public:
	cfwfclearerrors() {
		name = "clearErrors";
		returntype = T_VOID;

		parameters[0] = cfpproperty_string();
		parameterrequired[0] = false;
		parameters[1] = cfpname_string();
		parameterrequired[1] = false;
	}

};


class cfwfcolumnnames : public cffunction
{
public:
	cfwfcolumnnames() {
		name = "columnNames";
		returntype = T_STRING;

		parameters[0] = cfpproperty_string();
		parameterrequired[0] = false;
		parameters[1] = cfpname_string();
		parameterrequired[1] = false;
	}

};


class cfwfcontentforlayout : public cffunction
{
public:
	cfwfcontentforlayout() {
		name = "contentForLayout";
		returntype = T_STRING;

		parameters[0] = cfppartial_any();
		parameterrequired[0] = true;
		parameters[1] = cfpgroup_string();
		parameterrequired[1] = false;
		parameters[2] = cfpcache_any();
		parameterrequired[2] = false;
		parameters[3] = cfplayout_string();
		parameterrequired[3] = false;
		parameters[4] = cfpspacer_string();
		parameterrequired[4] = false;
	}

};


class cfwfcount : public cffunction
{
public:
	cfwfcount() {
		name = "count";
		returntype = T_NUMERIC;

		parameters[0] = cfpwhere_string();
		parameterrequired[0] = false;
		parameters[1] = cfpinclude_string();
		parameterrequired[1] = false;
	}

};


class cfwfcreate : public cffunction
{
public:
	cfwfcreate() {
		name = "create";
		returntype = T_ANY;

		parameters[0] = cfpproperties_struct();
		parameterrequired[0] = false;
		parameters[1] = cfpdefaults_boolean();
		parameterrequired[1] = false;
		parameters[2] = cfpparameterize_any();
		parameterrequired[2] = false;
	}

};


class cfwfcycle : public cffunction
{
public:
	cfwfcycle() {
		name = "cycle";
		returntype = T_STRING;

		parameters[0] = cfptext_string();
		parameterrequired[0] = false;
		parameters[1] = cfpconfirm_string();
		parameterrequired[1] = false;
		parameters[2] = cfproute_string();
		parameterrequired[2] = false;
		parameters[3] = cfpcontroller_string();
		parameterrequired[3] = false;
		parameters[4] = cfpaction_string();
		parameterrequired[4] = false;
		parameters[5] = cfpkey_any();
		parameterrequired[5] = false;
		parameters[6] = cfpparams_string();
		parameterrequired[6] = false;
		parameters[7] = cfpanchor_string();
		parameterrequired[7] = false;
		parameters[8] = cfponlypath_boolean();
		parameterrequired[8] = false;
		parameters[9] = cfphost_string();
		parameterrequired[9] = false;
		parameters[10] = cfpprotocol_string();
		parameterrequired[10] = false;
		parameters[11] = cfpport_numeric();
		parameterrequired[11] = false;
	}

};


class cfwfdatasource : public cffunction
{
public:
	cfwfdatasource() {
		name = "dataSource";
		returntype = T_VOID;

		parameters[0] = cfpdatasource_string();
		parameterrequired[0] = true;
		parameters[1] = cfpusername_string();
		parameterrequired[1] = false;
		parameters[2] = cfppassword_string();
		parameterrequired[2] = false;
	}

};


class cfwfdateselect : public cffunction
{
public:
	cfwfdateselect() {
		name = "dateSelect";
		returntype = T_STRING;

		parameters[0] = cfpobjectname_any();
		parameterrequired[0] = false;
		parameters[1] = cfpproperty_string();
		parameterrequired[1] = false;
		parameters[2] = cfporder_string();
		parameterrequired[2] = false;
		parameters[3] = cfpseparator_string();
		parameterrequired[3] = false;
		parameters[4] = cfpstartyear_numeric();
		parameterrequired[4] = false;
		parameters[5] = cfpendyear_numeric();
		parameterrequired[5] = false;
		parameters[6] = cfpmonthdisplay_string();
		parameterrequired[6] = false;
		parameters[7] = cfpincludeblank_any();
		parameterrequired[7] = false;
		parameters[8] = cfplabel_string();
		parameterrequired[8] = false;
		parameters[9] = cfplabelplacement_string();
		parameterrequired[9] = false;
		parameters[10] = cfpprepend_string();
		parameterrequired[10] = false;
		parameters[11] = cfpappend_string();
		parameterrequired[11] = false;
		parameters[12] = cfpprependtolabel_string();
		parameterrequired[12] = false;
		parameters[13] = cfpappendtolabel_string();
		parameterrequired[13] = false;
		parameters[14] = cfperrorelement_string();
		parameterrequired[14] = false;
	}

};


class cfwfdateselecttags : public cffunction
{
public:
	cfwfdateselecttags() {
		name = "dateSelectTags";
		returntype = T_STRING;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpselected_string();
		parameterrequired[1] = false;
		parameters[2] = cfporder_string();
		parameterrequired[2] = false;
		parameters[3] = cfpseparator_string();
		parameterrequired[3] = false;
		parameters[4] = cfpstartyear_numeric();
		parameterrequired[4] = false;
		parameters[5] = cfpendyear_numeric();
		parameterrequired[5] = false;
		parameters[6] = cfpmonthdisplay_string();
		parameterrequired[6] = false;
		parameters[7] = cfpincludeblank_any();
		parameterrequired[7] = false;
		parameters[8] = cfplabel_string();
		parameterrequired[8] = false;
		parameters[9] = cfplabelplacement_string();
		parameterrequired[9] = false;
		parameters[10] = cfpprepend_string();
		parameterrequired[10] = false;
		parameters[11] = cfpappend_string();
		parameterrequired[11] = false;
		parameters[12] = cfpprependtolabel_string();
		parameterrequired[12] = false;
		parameters[13] = cfpappendtolabel_string();
		parameterrequired[13] = false;
	}

};


class cfwfdatetimeselect : public cffunction
{
public:
	cfwfdatetimeselect() {
		name = "dateTimeSelect";
		returntype = T_STRING;

		parameters[0] = cfpobjectname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpdateorder_string();
		parameterrequired[1] = false;
		parameters[2] = cfpstartyear_numeric();
		parameterrequired[2] = false;
		parameters[3] = cfpmonthdisplay_string();
		parameterrequired[3] = false;
		parameters[4] = cfptimeorder_string();
		parameterrequired[4] = false;
		parameters[5] = cfpminutestep_numeric();
		parameterrequired[5] = false;
		parameters[6] = cfpseparator_string();
		parameterrequired[6] = false;
		parameters[7] = cfpincludeblank_any();
		parameterrequired[7] = false;
		parameters[8] = cfplabel_string();
		parameterrequired[8] = false;
		parameters[9] = cfpprepend_string();
		parameterrequired[9] = false;
		parameters[10] = cfpappend_string();
		parameterrequired[10] = false;
		parameters[11] = cfpprependtolabel_string();
		parameterrequired[11] = false;
		parameters[12] = cfpappendtolabel_string();
		parameterrequired[12] = false;
		parameters[13] = cfperrorelement_string();
		parameterrequired[13] = false;
	}

};


class cfwfdatetimeselecttags : public cffunction
{
public:
	cfwfdatetimeselecttags() {
		name = "dateTimeSelectTags";
		returntype = T_STRING;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpselected_string();
		parameterrequired[1] = false;
		parameters[2] = cfpdateorder_string();
		parameterrequired[2] = false;
		parameters[3] = cfpdateseparator_string();
		parameterrequired[3] = false;
		parameters[4] = cfpstartyear_numeric();
		parameterrequired[4] = false;
		parameters[5] = cfpendyear_numeric();
		parameterrequired[5] = false;
		parameters[6] = cfpmonthdisplay_string();
		parameterrequired[6] = false;
		parameters[7] = cfptimeorder_string();
		parameterrequired[7] = false;
		parameters[8] = cfptimeseparator_string();
		parameterrequired[8] = false;
		parameters[9] = cfpminutestep_numeric();
		parameterrequired[9] = false;
		parameters[10] = cfpseparator_string();
		parameterrequired[10] = false;
		parameters[11] = cfpincludeblank_any();
		parameterrequired[11] = false;
		parameters[12] = cfplabel_string();
		parameterrequired[12] = false;
		parameters[13] = cfplabelplacement_string();
		parameterrequired[13] = false;
		parameters[14] = cfpprepend_string();
		parameterrequired[14] = false;
		parameters[15] = cfpappend_string();
		parameterrequired[15] = false;
		parameters[16] = cfpprependtolabel_string();
		parameterrequired[16] = false;
		parameters[17] = cfpappendtolabel_string();
		parameterrequired[17] = false;
	}

};


class cfwfdayselecttag : public cffunction
{
public:
	cfwfdayselecttag() {
		name = "daySelectTag";
		returntype = T_STRING;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpselected_string();
		parameterrequired[1] = false;
		parameters[2] = cfpincludeblank_any();
		parameterrequired[2] = false;
		parameters[3] = cfplabel_string();
		parameterrequired[3] = false;
		parameters[4] = cfplabelplacement_string();
		parameterrequired[4] = false;
		parameters[5] = cfpprepend_string();
		parameterrequired[5] = false;
		parameters[6] = cfpappend_string();
		parameterrequired[6] = false;
		parameters[7] = cfpprependtolabel_string();
		parameterrequired[7] = false;
		parameters[8] = cfpappendtolabel_string();
		parameterrequired[8] = false;
	}

};


class cfwfdelete : public cffunction
{
public:
	cfwfdelete() {
		name = "delete";
		returntype = T_BOOLEAN;

		parameters[0] = cfpparameterize_any();
		parameterrequired[0] = false;
	}

};


class cfwfdeleteall : public cffunction
{
public:
	cfwfdeleteall() {
		name = "deleteAll";
		returntype = T_NUMERIC;

		parameters[0] = cfpwhere_string();
		parameterrequired[0] = false;
		parameters[1] = cfpinclude_string();
		parameterrequired[1] = false;
		parameters[2] = cfpparameterize_any();
		parameterrequired[2] = false;
		parameters[3] = cfpinstantiate_boolean();
		parameterrequired[3] = false;
		parameters[4] = cfp$softdeletecheck_boolean();
		parameterrequired[4] = false;
	}

};


class cfwfdeletebykey : public cffunction
{
public:
	cfwfdeletebykey() {
		name = "deleteByKey";
		returntype = T_BOOLEAN;

		parameters[0] = cfpkey_any();
		parameterrequired[0] = true;
	}

};


class cfwfdeleteone : public cffunction
{
public:
	cfwfdeleteone() {
		name = "deleteOne";
		returntype = T_BOOLEAN;

		parameters[0] = cfpwhere_string();
		parameterrequired[0] = false;
		parameters[1] = cfporder_string();
		parameterrequired[1] = false;
	}

};


class cfwfdeobfuscateparam : public cffunction
{
public:
	cfwfdeobfuscateparam() {
		name = "deobfuscateParam";
		returntype = T_STRING;

		parameters[0] = cfpparam_string();
		parameterrequired[0] = true;
	}

};


class cfwfdistanceoftimeinwords : public cffunction
{
public:
	cfwfdistanceoftimeinwords() {
		name = "distanceOfTimeInWords";
		returntype = T_STRING;

		parameters[0] = cfpobjectname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpclass_string();
		parameterrequired[1] = false;
		parameters[2] = cfpshowduplicates_boolean();
		parameterrequired[2] = false;
	}

};


class cfwfendformtag : public cffunction
{
public:
	cfwfendformtag() {
		name = "endFormTag";
		returntype = T_STRING;

		parameters[0] = cfpobjectname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpclass_string();
		parameterrequired[1] = false;
		parameters[2] = cfpshowduplicates_boolean();
		parameterrequired[2] = false;
	}

};


class cfwferrorcount : public cffunction
{
public:
	cfwferrorcount() {
		name = "errorCount";
		returntype = T_NUMERIC;

		parameters[0] = cfpproperty_string();
		parameterrequired[0] = false;
		parameters[1] = cfpname_string();
		parameterrequired[1] = false;
	}

};


class cfwferrormessageon : public cffunction
{
public:
	cfwferrormessageon() {
		name = "errorMessageOn";
		returntype = T_STRING;

		parameters[0] = cfpobjectname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpproperty_string();
		parameterrequired[1] = true;
		parameters[2] = cfpprependtext_string();
		parameterrequired[2] = false;
		parameters[3] = cfpappendtext_string();
		parameterrequired[3] = false;
		parameters[4] = cfpwrapperelement_string();
		parameterrequired[4] = false;
		parameters[5] = cfpclass_string();
		parameterrequired[5] = false;
	}

};


class cfwferrorson : public cffunction
{
public:
	cfwferrorson() {
		name = "errorsOn";
		returntype = T_ARRAY;

		parameters[0] = cfpproperty_string();
		parameterrequired[0] = true;
		parameters[1] = cfpname_string();
		parameterrequired[1] = false;
	}

};


class cfwferrorsonbase : public cffunction
{
public:
	cfwferrorsonbase() {
		name = "errorsOnBase";
		returntype = T_ARRAY;

		parameters[0] = cfpname_string();
		parameterrequired[0] = false;
	}

};


class cfwfexists : public cffunction
{
public:
	cfwfexists() {
		name = "exists";
		returntype = T_BOOLEAN;

		parameters[0] = cfpkey_any();
		parameterrequired[0] = false;
		parameters[1] = cfpwhere_string();
		parameterrequired[1] = false;
		parameters[2] = cfpreload_boolean();
		parameterrequired[2] = false;
		parameters[3] = cfpparameterize_any();
		parameterrequired[3] = false;
	}

};


class cfwffilefield : public cffunction
{
public:
	cfwffilefield() {
		name = "fileField";
		returntype = T_STRING;

		parameters[0] = cfpobjectname_any();
		parameterrequired[0] = true;
		parameters[1] = cfpproperty_string();
		parameterrequired[1] = true;
		parameters[2] = cfplabel_string();
		parameterrequired[2] = false;
		parameters[3] = cfplabelplacement_string();
		parameterrequired[3] = false;
		parameters[4] = cfpprepend_string();
		parameterrequired[4] = false;
		parameters[5] = cfpappend_string();
		parameterrequired[5] = false;
		parameters[6] = cfpprependtolabel_string();
		parameterrequired[6] = false;
		parameters[7] = cfpappendtolabel_string();
		parameterrequired[7] = false;
		parameters[8] = cfperrorelement_string();
		parameterrequired[8] = false;
	}

};


class cfwffilefieldtag : public cffunction
{
public:
	cfwffilefieldtag() {
		name = "fileFieldTag";
		returntype = T_STRING;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfplabel_string();
		parameterrequired[1] = false;
		parameters[2] = cfplabelplacement_string();
		parameterrequired[2] = false;
		parameters[3] = cfpprepend_string();
		parameterrequired[3] = false;
		parameters[4] = cfpappend_string();
		parameterrequired[4] = false;
		parameters[5] = cfpprependtolabel_string();
		parameterrequired[5] = false;
		parameters[6] = cfpappendtolabel_string();
		parameterrequired[6] = false;
	}

};


class cfwffilters : public cffunction
{
public:
	cfwffilters() {
		name = "filters";
		returntype = T_VOID;

		parameters[0] = cfpthrough_string();
		parameterrequired[0] = true;
		parameters[1] = cfptype_string();
		parameterrequired[1] = false;
		parameters[2] = cfponly_string();
		parameterrequired[2] = false;
		parameters[3] = cfpexcept_string();
		parameterrequired[3] = false;
	}

};


class cfwffindall : public cffunction
{
public:
	cfwffindall() {
		name = "findAll";
		returntype = T_ANY;

		parameters[0] = cfpwhere_string();
		parameterrequired[0] = false;
		parameters[1] = cfporder_string();
		parameterrequired[1] = false;
		parameters[2] = cfpselect_string();
		parameterrequired[2] = false;
		parameters[3] = cfpdistinct_boolean();
		parameterrequired[3] = false;
		parameters[4] = cfpinclude_string();
		parameterrequired[4] = false;
		parameters[5] = cfpmaxrows_numeric();
		parameterrequired[5] = false;
	}

};


class cfwffindbykey : public cffunction
{
public:
	cfwffindbykey() {
		name = "findByKey";
		returntype = T_ANY;

		parameters[0] = cfpkey_any();
		parameterrequired[0] = true;
		parameters[1] = cfpselect_string();
		parameterrequired[1] = false;
		parameters[2] = cfpinclude_string();
		parameterrequired[2] = false;
		parameters[3] = cfpcache_any();
		parameterrequired[3] = false;
		parameters[4] = cfpreload_boolean();
		parameterrequired[4] = false;
		parameters[5] = cfpparameterize_any();
		parameterrequired[5] = false;
		parameters[6] = cfpreturnas_string();
		parameterrequired[6] = false;
		parameters[7] = cfp$softdeletecheck_boolean();
		parameterrequired[7] = false;
	}

};


class cfwffindone : public cffunction
{
public:
	cfwffindone() {
		name = "findOne";
		returntype = T_ANY;

		parameters[0] = cfpwhere_string();
		parameterrequired[0] = false;
		parameters[1] = cfporder_string();
		parameterrequired[1] = false;
		parameters[2] = cfpselect_string();
		parameterrequired[2] = false;
		parameters[3] = cfpinclude_string();
		parameterrequired[3] = false;
		parameters[4] = cfpcache_any();
		parameterrequired[4] = false;
		parameters[5] = cfpreload_boolean();
		parameterrequired[5] = false;
		parameters[6] = cfpparameterize_any();
		parameterrequired[6] = false;
		parameters[7] = cfpreturnas_string();
		parameterrequired[7] = false;
		parameters[8] = cfp$softdeletecheck_boolean();
		parameterrequired[8] = false;
	}

};


class cfwfflash : public cffunction
{
public:
	cfwfflash() {
		name = "flash";
		returntype = T_ANY;

		parameters[0] = cfpkey_string();
		parameterrequired[0] = false;
	}

};


class cfwfflashclear : public cffunction
{
public:
	cfwfflashclear() {
		name = "flashClear";
		returntype = T_VOID;

		parameters[0] = cfpkey_string();
		parameterrequired[0] = false;
	}

};


class cfwfflashcount : public cffunction
{
public:
	cfwfflashcount() {
		name = "flashCount";
		returntype = T_NUMERIC;

		parameters[0] = cfpkey_string();
		parameterrequired[0] = false;
	}

};


class cfwfflashdelete : public cffunction
{
public:
	cfwfflashdelete() {
		name = "flashDelete";
		returntype = T_BOOLEAN;

		parameters[0] = cfpkey_string();
		parameterrequired[0] = true;
	}

};


class cfwfflashinsert : public cffunction
{
public:
	cfwfflashinsert() {
		name = "flashInsert";
		returntype = T_VOID;

		parameters[0] = cfpkey_string();
		parameterrequired[0] = true;
	}

};


class cfwfflashisempty : public cffunction
{
public:
	cfwfflashisempty() {
		name = "flashIsEmpty";
		returntype = T_BOOLEAN;

		parameters[0] = cfpkey_string();
		parameterrequired[0] = true;
	}

};


class cfwfflashkeyexists : public cffunction
{
public:
	cfwfflashkeyexists() {
		name = "flashKeyExists";
		returntype = T_BOOLEAN;

		parameters[0] = cfpkey_string();
		parameterrequired[0] = true;
	}

};


class cfwfget : public cffunction
{
public:
	cfwfget() {
		name = "get";
		returntype = T_ANY;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpfunctionname_string();
		parameterrequired[1] = false;
	}

};


class cfwfhaschanged : public cffunction
{
public:
	cfwfhaschanged() {
		name = "hasChanged";
		returntype = T_BOOLEAN;

		parameters[0] = cfpproperty_string();
		parameterrequired[0] = false;
	}

};


class cfwfhaserrors : public cffunction
{
public:
	cfwfhaserrors() {
		name = "hasErrors";
		returntype = T_BOOLEAN;

		parameters[0] = cfpproperty_string();
		parameterrequired[0] = false;
		parameters[1] = cfpname_string();
		parameterrequired[1] = false;
	}

};


class cfwfhasmany : public cffunction
{
public:
	cfwfhasmany() {
		name = "hasMany";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpclass_string();
		parameterrequired[1] = false;
		parameters[2] = cfpforeignkey_string();
		parameterrequired[2] = false;
		parameters[3] = cfpjointype_string();
		parameterrequired[3] = false;
		parameters[4] = cfpshortcut_string();
		parameterrequired[4] = false;
		parameters[5] = cfpthrough_string();
		parameterrequired[5] = false;
	}

};


class cfwfhasone : public cffunction
{
public:
	cfwfhasone() {
		name = "hasOne";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpclass_string();
		parameterrequired[1] = false;
		parameters[2] = cfpforeignkey_string();
		parameterrequired[2] = false;
		parameters[3] = cfpjointype_string();
		parameterrequired[3] = false;
	}

};


class cfwfhiddenfield : public cffunction
{
public:
	cfwfhiddenfield() {
		name = "hiddenField";
		returntype = T_STRING;

		parameters[0] = cfpobjectname_any();
		parameterrequired[0] = true;
		parameters[1] = cfpproperty_string();
		parameterrequired[1] = true;
	}

};


class cfwfhiddenfieldtag : public cffunction
{
public:
	cfwfhiddenfieldtag() {
		name = "hiddenFieldTag";
		returntype = T_STRING;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpvalue_string();
		parameterrequired[1] = false;
	}

};


class cfwfhourselecttag : public cffunction
{
public:
	cfwfhourselecttag() {
		name = "hourSelectTag";
		returntype = T_STRING;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpselected_string();
		parameterrequired[1] = false;
		parameters[2] = cfpincludeblank_any();
		parameterrequired[2] = false;
		parameters[3] = cfplabel_string();
		parameterrequired[3] = false;
		parameters[4] = cfplabelplacement_string();
		parameterrequired[4] = false;
		parameters[5] = cfpprepend_string();
		parameterrequired[5] = false;
		parameters[6] = cfpappend_string();
		parameterrequired[6] = false;
		parameters[7] = cfpprependtolabel_string();
		parameterrequired[7] = false;
		parameters[8] = cfpappendtolabel_string();
		parameterrequired[8] = false;
	}

};


class cfwfhumanize : public cffunction
{
public:
	cfwfhumanize() {
		name = "humanize";
		returntype = T_STRING;

		parameters[0] = cfptext_string();
		parameterrequired[0] = true;
	}

};


class cfwfimagetag : public cffunction
{
public:
	cfwfimagetag() {
		name = "imageTag";
		returntype = T_STRING;

		parameters[0] = cfpsource_string();
		parameterrequired[0] = true;
	}

};


class cfwfisajax : public cffunction
{
public:
	cfwfisajax() {
		name = "isAjax";
		returntype = T_BOOLEAN;

		parameters[0] = cfpsource_string();
		parameterrequired[0] = true;
	}

};


class cfwfisget : public cffunction
{
public:
	cfwfisget() {
		name = "isGet";
		returntype = T_BOOLEAN;

		parameters[0] = cfpsource_string();
		parameterrequired[0] = true;
	}

};


class cfwfisnew : public cffunction
{
public:
	cfwfisnew() {
		name = "isNew";
		returntype = T_BOOLEAN;

		parameters[0] = cfpsource_string();
		parameterrequired[0] = true;
	}

};


class cfwfispost : public cffunction
{
public:
	cfwfispost() {
		name = "isPost";
		returntype = T_BOOLEAN;

		parameters[0] = cfpsource_string();
		parameterrequired[0] = true;
	}

};


class cfwfjavascriptincludetag : public cffunction
{
public:
	cfwfjavascriptincludetag() {
		name = "javaScriptIncludeTag";
		returntype = T_STRING;

		parameters[0] = cfpsources_string();
		parameterrequired[0] = false;
		parameters[1] = cfptype_string();
		parameterrequired[1] = false;
	}

};


class cfwfkey : public cffunction
{
public:
	cfwfkey() {
		name = "key";
		returntype = T_STRING;

		parameters[0] = cfp$persisted_boolean();
		parameterrequired[0] = false;
	}

};


class cfwfmaximum : public cffunction
{
public:
	cfwfmaximum() {
		name = "maximum";
		returntype = T_ANY;

		parameters[0] = cfpproperty_string();
		parameterrequired[0] = true;
		parameters[1] = cfpwhere_string();
		parameterrequired[1] = false;
		parameters[2] = cfpinclude_string();
		parameterrequired[2] = false;
	}

};


class cfwfminimum : public cffunction
{
public:
	cfwfminimum() {
		name = "minimum";
		returntype = T_ANY;

		parameters[0] = cfpproperty_string();
		parameterrequired[0] = true;
		parameters[1] = cfpwhere_string();
		parameterrequired[1] = false;
		parameters[2] = cfpinclude_string();
		parameterrequired[2] = false;
	}

};


class cfwfminuteselecttag : public cffunction
{
public:
	cfwfminuteselecttag() {
		name = "minuteSelectTag";
		returntype = T_STRING;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpselected_string();
		parameterrequired[1] = false;
		parameters[2] = cfpminutestep_numeric();
		parameterrequired[2] = false;
		parameters[3] = cfpincludeblank_any();
		parameterrequired[3] = false;
		parameters[4] = cfplabel_string();
		parameterrequired[4] = false;
		parameters[5] = cfplabelplacement_string();
		parameterrequired[5] = false;
		parameters[6] = cfpprepend_string();
		parameterrequired[6] = false;
		parameters[7] = cfpappend_string();
		parameterrequired[7] = false;
		parameters[8] = cfpprependtolabel_string();
		parameterrequired[8] = false;
		parameters[9] = cfpappendtolabel_string();
		parameterrequired[9] = false;
	}

};


class cfwfmodel : public cffunction
{
public:
	cfwfmodel() {
		name = "model";
		returntype = T_ANY;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
	}

};


class cfwfmonthselecttag : public cffunction
{
public:
	cfwfmonthselecttag() {
		name = "monthSelectTag";
		returntype = T_STRING;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpselected_string();
		parameterrequired[1] = false;
		parameters[2] = cfpmonthdisplay_string();
		parameterrequired[2] = false;
		parameters[3] = cfpincludeblank_any();
		parameterrequired[3] = false;
		parameters[4] = cfplabel_string();
		parameterrequired[4] = false;
		parameters[5] = cfplabelplacement_string();
		parameterrequired[5] = false;
		parameters[6] = cfpprepend_string();
		parameterrequired[6] = false;
		parameters[7] = cfpappend_string();
		parameterrequired[7] = false;
		parameters[8] = cfpprependtolabel_string();
		parameterrequired[8] = false;
		parameters[9] = cfpappendtolabel_string();
		parameterrequired[9] = false;
	}

};


class cfwfnew : public cffunction
{
public:
	cfwfnew() {
		name = "new";
		returntype = T_ANY;

		parameters[0] = cfpproperties_struct();
		parameterrequired[0] = false;
		parameters[1] = cfpdefaults_boolean();
		parameterrequired[1] = false;
	}

};


class cfwfobfuscateparam : public cffunction
{
public:
	cfwfobfuscateparam() {
		name = "obfuscateParam";
		returntype = T_STRING;

		parameters[0] = cfpparam_any();
		parameterrequired[0] = true;
	}

};


class cfwfpasswordfield : public cffunction
{
public:
	cfwfpasswordfield() {
		name = "passwordField";
		returntype = T_STRING;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpvalue_string();
		parameterrequired[1] = false;
		parameters[2] = cfplabel_string();
		parameterrequired[2] = false;
		parameters[3] = cfplabelplacement_string();
		parameterrequired[3] = false;
		parameters[4] = cfpprepend_string();
		parameterrequired[4] = false;
		parameters[5] = cfpappend_string();
		parameterrequired[5] = false;
		parameters[6] = cfpprependtolabel_string();
		parameterrequired[6] = false;
		parameters[7] = cfpappendtolabel_string();
		parameterrequired[7] = false;
	}

};


class cfwfpluginnames : public cffunction
{
public:
	cfwfpluginnames() {
		name = "pluginNames";
		returntype = T_STRING;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpvalue_string();
		parameterrequired[1] = false;
		parameters[2] = cfplabel_string();
		parameterrequired[2] = false;
		parameters[3] = cfplabelplacement_string();
		parameterrequired[3] = false;
		parameters[4] = cfpprepend_string();
		parameterrequired[4] = false;
		parameters[5] = cfpappend_string();
		parameterrequired[5] = false;
		parameters[6] = cfpprependtolabel_string();
		parameterrequired[6] = false;
		parameters[7] = cfpappendtolabel_string();
		parameterrequired[7] = false;
	}

};


class cfwfpluralize : public cffunction
{
public:
	cfwfpluralize() {
		name = "pluralize";
		returntype = T_STRING;

		parameters[0] = cfpword_string();
		parameterrequired[0] = true;
		parameters[1] = cfpcount_numeric();
		parameterrequired[1] = false;
		parameters[2] = cfpreturncount_boolean();
		parameterrequired[2] = false;
	}

};


class cfwfprimarykey : public cffunction
{
public:
	cfwfprimarykey() {
		name = "primaryKey";
		returntype = T_STRING;

		parameters[0] = cfpword_string();
		parameterrequired[0] = true;
		parameters[1] = cfpcount_numeric();
		parameterrequired[1] = false;
		parameters[2] = cfpreturncount_boolean();
		parameterrequired[2] = false;
	}

};


class cfwfproperty : public cffunction
{
public:
	cfwfproperty() {
		name = "property";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpcolumn_string();
		parameterrequired[1] = false;
		parameters[2] = cfpsql_string();
		parameterrequired[2] = false;
	}

};


class cfwfpropertynames : public cffunction
{
public:
	cfwfpropertynames() {
		name = "propertyNames";
		returntype = T_STRING;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpcolumn_string();
		parameterrequired[1] = false;
		parameters[2] = cfpsql_string();
		parameterrequired[2] = false;
	}

};


class cfwfradiobutton : public cffunction
{
public:
	cfwfradiobutton() {
		name = "radioButton";
		returntype = T_STRING;

		parameters[0] = cfpobjectname_any();
		parameterrequired[0] = true;
		parameters[1] = cfpproperty_string();
		parameterrequired[1] = true;
		parameters[2] = cfptagvalue_string();
		parameterrequired[2] = true;
		parameters[3] = cfplabel_string();
		parameterrequired[3] = false;
		parameters[4] = cfplabelplacement_string();
		parameterrequired[4] = false;
		parameters[5] = cfpprepend_string();
		parameterrequired[5] = false;
		parameters[6] = cfpappend_string();
		parameterrequired[6] = false;
		parameters[7] = cfpprependtolabel_string();
		parameterrequired[7] = false;
		parameters[8] = cfpappendtolabel_string();
		parameterrequired[8] = false;
		parameters[9] = cfperrorelement_string();
		parameterrequired[9] = false;
	}

};


class cfwfradiobuttontag : public cffunction
{
public:
	cfwfradiobuttontag() {
		name = "radioButtonTag";
		returntype = T_STRING;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpvalue_string();
		parameterrequired[1] = true;
		parameters[2] = cfpchecked_boolean();
		parameterrequired[2] = false;
		parameters[3] = cfplabel_string();
		parameterrequired[3] = false;
		parameters[4] = cfplabelplacement_string();
		parameterrequired[4] = false;
		parameters[5] = cfpprepend_string();
		parameterrequired[5] = false;
		parameters[6] = cfpappend_string();
		parameterrequired[6] = false;
		parameters[7] = cfpprependtolabel_string();
		parameterrequired[7] = false;
		parameters[8] = cfpappendtolabel_string();
		parameterrequired[8] = false;
	}

};


class cfwfredirectto : public cffunction
{
public:
	cfwfredirectto() {
		name = "redirectTo";
		returntype = T_VOID;

		parameters[0] = cfpback_boolean();
		parameterrequired[0] = false;
		parameters[1] = cfpaddtoken_boolean();
		parameterrequired[1] = false;
		parameters[2] = cfpstatuscode_numeric();
		parameterrequired[2] = false;
		parameters[3] = cfproute_string();
		parameterrequired[3] = false;
		parameters[4] = cfpcontroller_string();
		parameterrequired[4] = false;
		parameters[5] = cfpaction_string();
		parameterrequired[5] = false;
		parameters[6] = cfpkey_any();
		parameterrequired[6] = false;
		parameters[7] = cfpparams_string();
		parameterrequired[7] = false;
		parameters[8] = cfpanchor_string();
		parameterrequired[8] = false;
		parameters[9] = cfponlypath_boolean();
		parameterrequired[9] = false;
		parameters[10] = cfphost_string();
		parameterrequired[10] = false;
		parameters[11] = cfpprotocol_string();
		parameterrequired[11] = false;
		parameters[12] = cfpport_numeric();
		parameterrequired[12] = false;
	}

};


class cfwfreload : public cffunction
{
public:
	cfwfreload() {
		name = "reload";
		returntype = T_VOID;

		parameters[0] = cfpback_boolean();
		parameterrequired[0] = false;
		parameters[1] = cfpaddtoken_boolean();
		parameterrequired[1] = false;
		parameters[2] = cfpstatuscode_numeric();
		parameterrequired[2] = false;
		parameters[3] = cfproute_string();
		parameterrequired[3] = false;
		parameters[4] = cfpcontroller_string();
		parameterrequired[4] = false;
		parameters[5] = cfpaction_string();
		parameterrequired[5] = false;
		parameters[6] = cfpkey_any();
		parameterrequired[6] = false;
		parameters[7] = cfpparams_string();
		parameterrequired[7] = false;
		parameters[8] = cfpanchor_string();
		parameterrequired[8] = false;
		parameters[9] = cfponlypath_boolean();
		parameterrequired[9] = false;
		parameters[10] = cfphost_string();
		parameterrequired[10] = false;
		parameters[11] = cfpprotocol_string();
		parameterrequired[11] = false;
		parameters[12] = cfpport_numeric();
		parameterrequired[12] = false;
	}

};


class cfwfrendernothing : public cffunction
{
public:
	cfwfrendernothing() {
		name = "renderNothing";
		returntype = T_VOID;

		parameters[0] = cfpback_boolean();
		parameterrequired[0] = false;
		parameters[1] = cfpaddtoken_boolean();
		parameterrequired[1] = false;
		parameters[2] = cfpstatuscode_numeric();
		parameterrequired[2] = false;
		parameters[3] = cfproute_string();
		parameterrequired[3] = false;
		parameters[4] = cfpcontroller_string();
		parameterrequired[4] = false;
		parameters[5] = cfpaction_string();
		parameterrequired[5] = false;
		parameters[6] = cfpkey_any();
		parameterrequired[6] = false;
		parameters[7] = cfpparams_string();
		parameterrequired[7] = false;
		parameters[8] = cfpanchor_string();
		parameterrequired[8] = false;
		parameters[9] = cfponlypath_boolean();
		parameterrequired[9] = false;
		parameters[10] = cfphost_string();
		parameterrequired[10] = false;
		parameters[11] = cfpprotocol_string();
		parameterrequired[11] = false;
		parameters[12] = cfpport_numeric();
		parameterrequired[12] = false;
	}

};


class cfwfrenderpage : public cffunction
{
public:
	cfwfrenderpage() {
		name = "renderPage";
		returntype = T_ANY;

		parameters[0] = cfpcontroller_string();
		parameterrequired[0] = false;
		parameters[1] = cfpaction_string();
		parameterrequired[1] = false;
		parameters[2] = cfptemplate_string();
		parameterrequired[2] = false;
		parameters[3] = cfplayout_any();
		parameterrequired[3] = false;
		parameters[4] = cfpcache_any();
		parameterrequired[4] = false;
		parameters[5] = cfpreturnas_string();
		parameterrequired[5] = false;
		parameters[6] = cfp$showdebuginformation_any();
		parameterrequired[6] = false;
	}

};


class cfwfrenderpartial : public cffunction
{
public:
	cfwfrenderpartial() {
		name = "renderPartial";
		returntype = T_ANY;

		parameters[0] = cfppartial_string();
		parameterrequired[0] = true;
		parameters[1] = cfpcache_any();
		parameterrequired[1] = false;
		parameters[2] = cfplayout_string();
		parameterrequired[2] = false;
		parameters[3] = cfpreturnas_string();
		parameterrequired[3] = false;
	}

};


class cfwfrendertext : public cffunction
{
public:
	cfwfrendertext() {
		name = "renderText";
		returntype = T_VOID;

		parameters[0] = cfptext_any();
		parameterrequired[0] = true;
	}

};


class cfwfsave : public cffunction
{
public:
	cfwfsave() {
		name = "save";
		returntype = T_BOOLEAN;

		parameters[0] = cfpparameterize_any();
		parameterrequired[0] = false;
		parameters[1] = cfpdefaults_boolean();
		parameterrequired[1] = false;
	}

};


class cfwfsecondselecttag : public cffunction
{
public:
	cfwfsecondselecttag() {
		name = "secondSelectTag";
		returntype = T_STRING;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpselected_string();
		parameterrequired[1] = false;
		parameters[2] = cfpincludeblank_any();
		parameterrequired[2] = false;
		parameters[3] = cfplabel_string();
		parameterrequired[3] = false;
		parameters[4] = cfplabelplacement_string();
		parameterrequired[4] = false;
		parameters[5] = cfpprepend_string();
		parameterrequired[5] = false;
		parameters[6] = cfpappend_string();
		parameterrequired[6] = false;
		parameters[7] = cfpprependtolabel_string();
		parameterrequired[7] = false;
		parameters[8] = cfpappendtolabel_string();
		parameterrequired[8] = false;
	}

};


class cfwfselect : public cffunction
{
public:
	cfwfselect() {
		name = "select";
		returntype = T_STRING;

		parameters[0] = cfpobjectname_any();
		parameterrequired[0] = true;
		parameters[1] = cfpproperty_string();
		parameterrequired[1] = true;
		parameters[2] = cfpoptions_any();
		parameterrequired[2] = true;
		parameters[3] = cfpincludeblank_any();
		parameterrequired[3] = false;
		parameters[4] = cfpvaluefield_string();
		parameterrequired[4] = false;
		parameters[5] = cfptextfield_string();
		parameterrequired[5] = false;
		parameters[6] = cfplabel_string();
		parameterrequired[6] = false;
		parameters[7] = cfplabelplacement_string();
		parameterrequired[7] = false;
		parameters[8] = cfpprepend_string();
		parameterrequired[8] = false;
		parameters[9] = cfpappend_string();
		parameterrequired[9] = false;
		parameters[10] = cfpprependtolabel_string();
		parameterrequired[10] = false;
		parameters[11] = cfpappendtolabel_string();
		parameterrequired[11] = false;
		parameters[12] = cfperrorelement_string();
		parameterrequired[12] = false;
	}

};


class cfwfselecttag : public cffunction
{
public:
	cfwfselecttag() {
		name = "selectTag";
		returntype = T_STRING;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpoptions_any();
		parameterrequired[1] = true;
		parameters[2] = cfpselected_string();
		parameterrequired[2] = false;
		parameters[3] = cfpincludeblank_any();
		parameterrequired[3] = false;
		parameters[4] = cfpmultiple_boolean();
		parameterrequired[4] = false;
		parameters[5] = cfpvaluefield_string();
		parameterrequired[5] = false;
		parameters[6] = cfptextfield_string();
		parameterrequired[6] = false;
		parameters[7] = cfplabel_string();
		parameterrequired[7] = false;
		parameters[8] = cfplabelplacement_string();
		parameterrequired[8] = false;
		parameters[9] = cfpprepend_string();
		parameterrequired[9] = false;
		parameters[10] = cfpappend_string();
		parameterrequired[10] = false;
		parameters[11] = cfpprependtolabel_string();
		parameterrequired[11] = false;
		parameters[12] = cfpappendtolabel_string();
		parameterrequired[12] = false;
	}

};


class cfwfsendemail : public cffunction
{
public:
	cfwfsendemail() {
		name = "sendEmail";
		returntype = T_VOID;

		parameters[0] = cfptemplates_string();
		parameterrequired[0] = false;
		parameters[1] = cfpfrom_string();
		parameterrequired[1] = true;
		parameters[2] = cfpto_string();
		parameterrequired[2] = true;
		parameters[3] = cfpsubject_string();
		parameterrequired[3] = true;
		parameters[4] = cfplayouts_any();
		parameterrequired[4] = false;
		parameters[5] = cfpdetectmultipart_boolean();
		parameterrequired[5] = false;
	}

};


class cfwfsendfile : public cffunction
{
public:
	cfwfsendfile() {
		name = "sendFile";
		returntype = T_VOID;

		parameters[0] = cfpfile_string();
		parameterrequired[0] = true;
		parameters[1] = cfpname_string();
		parameterrequired[1] = false;
		parameters[2] = cfptype_string();
		parameterrequired[2] = false;
		parameters[3] = cfpdisposition_string();
		parameterrequired[3] = false;
	}
};


class cfwfset : public cffunction
{
public:
	cfwfset() {
		name = "set";
		returntype = T_VOID;

		parameters[0] = cfpfile_string();
		parameterrequired[0] = true;
		parameters[1] = cfpname_string();
		parameterrequired[1] = false;
		parameters[2] = cfptype_string();
		parameterrequired[2] = false;
		parameters[3] = cfpdisposition_string();
		parameterrequired[3] = false;
	}

};


class cfwfsetproperties : public cffunction
{
public:
	cfwfsetproperties() {
		name = "setProperties";
		returntype = T_VOID;

		parameters[0] = cfpproperties_struct();
		parameterrequired[0] = false;
	}

};


class cfwfsingularize : public cffunction
{
public:
	cfwfsingularize() {
		name = "singularize";
		returntype = T_STRING;

		parameters[0] = cfpword_string();
		parameterrequired[0] = true;
	}

};


class cfwfstartformtag : public cffunction
{
public:
	cfwfstartformtag() {
		name = "startFormTag";
		returntype = T_STRING;

		parameters[0] = cfpmethod_string();
		parameterrequired[0] = false;
		parameters[1] = cfpmultipart_boolean();
		parameterrequired[1] = false;
		parameters[2] = cfpspamprotection_boolean();
		parameterrequired[2] = false;
		parameters[3] = cfproute_string();
		parameterrequired[3] = false;
		parameters[4] = cfpcontroller_string();
		parameterrequired[4] = false;
		parameters[5] = cfpaction_string();
		parameterrequired[5] = false;
		parameters[6] = cfpkey_any();
		parameterrequired[6] = false;
		parameters[7] = cfpparams_string();
		parameterrequired[7] = false;
		parameters[8] = cfpanchor_string();
		parameterrequired[8] = false;
		parameters[9] = cfponlypath_boolean();
		parameterrequired[9] = false;
		parameters[10] = cfphost_string();
		parameterrequired[10] = false;
		parameters[11] = cfpprotocol_string();
		parameterrequired[11] = false;
		parameters[12] = cfpport_numeric();
		parameterrequired[12] = false;
	}

};


class cfwfstylesheetlinktag : public cffunction
{
public:
	cfwfstylesheetlinktag() {
		name = "styleSheetLinkTag";
		returntype = T_STRING;

		parameters[0] = cfpsources_string();
		parameterrequired[0] = false;
		parameters[1] = cfptype_string();
		parameterrequired[1] = false;
		parameters[2] = cfpmedia_string();
		parameterrequired[2] = false;
	}

};


class cfwfsubmittag : public cffunction
{
public:
	cfwfsubmittag() {
		name = "submitTag";
		returntype = T_STRING;

		parameters[0] = cfpvalue_string();
		parameterrequired[0] = false;
		parameters[1] = cfpimage_string();
		parameterrequired[1] = false;
		parameters[2] = cfpdisable_any();
		parameterrequired[2] = false;
	}

};


class cfwfsum : public cffunction
{
public:
	cfwfsum() {
		name = "sum";
		returntype = T_ANY;

		parameters[0] = cfpproperty_string();
		parameterrequired[0] = true;
		parameters[1] = cfpwhere_string();
		parameterrequired[1] = false;
		parameters[2] = cfpinclude_string();
		parameterrequired[2] = false;
		parameters[3] = cfpdistinct_boolean();
		parameterrequired[3] = false;
	}

};


class cfwftable : public cffunction
{
public:
	cfwftable() {
		name = "table";
		returntype = T_VOID;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
	}

};


class cfwftablename : public cffunction
{
public:
	cfwftablename() {
		name = "tableName";
		returntype = T_STRING;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
	}

};


class cfwftextarea : public cffunction
{
public:
	cfwftextarea() {
		name = "textArea";
		returntype = T_STRING;

		parameters[0] = cfpobjectname_any();
		parameterrequired[0] = true;
		parameters[1] = cfpproperty_string();
		parameterrequired[1] = true;
		parameters[2] = cfplabel_string();
		parameterrequired[2] = false;
		parameters[3] = cfplabelplacement_string();
		parameterrequired[3] = false;
		parameters[4] = cfpprepend_string();
		parameterrequired[4] = false;
		parameters[5] = cfpappend_string();
		parameterrequired[5] = false;
		parameters[6] = cfpprependtolabel_string();
		parameterrequired[6] = false;
		parameters[7] = cfpappendtolabel_string();
		parameterrequired[7] = false;
		parameters[8] = cfperrorelement_string();
		parameterrequired[8] = false;
	}

};


class cfwftextareatag : public cffunction
{
public:
	cfwftextareatag() {
		name = "textAreaTag";
		returntype = T_STRING;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpcontent_string();
		parameterrequired[1] = false;
		parameters[2] = cfplabel_string();
		parameterrequired[2] = false;
		parameters[3] = cfplabelplacement_string();
		parameterrequired[3] = false;
		parameters[4] = cfpprepend_string();
		parameterrequired[4] = false;
		parameters[5] = cfpappend_string();
		parameterrequired[5] = false;
		parameters[6] = cfpprependtolabel_string();
		parameterrequired[6] = false;
		parameters[7] = cfpappendtolabel_string();
		parameterrequired[7] = false;
	}

};


class cfwftextfield : public cffunction
{
public:
	cfwftextfield() {
		name = "textField";
		returntype = T_STRING;

		parameters[0] = cfpobjectname_any();
		parameterrequired[0] = true;
		parameters[1] = cfpproperty_string();
		parameterrequired[1] = true;
		parameters[2] = cfplabel_string();
		parameterrequired[2] = false;
		parameters[3] = cfplabelplacement_string();
		parameterrequired[3] = false;
		parameters[4] = cfpprepend_string();
		parameterrequired[4] = false;
		parameters[5] = cfpappend_string();
		parameterrequired[5] = false;
		parameters[6] = cfpprependtolabel_string();
		parameterrequired[6] = false;
		parameters[7] = cfpappendtolabel_string();
		parameterrequired[7] = false;
		parameters[8] = cfperrorelement_string();
		parameterrequired[8] = false;
	}

};


class cfwftextfieldtag : public cffunction
{
public:
	cfwftextfieldtag() {
		name = "textFieldTag";
		returntype = T_STRING;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpvalue_string();
		parameterrequired[1] = false;
		parameters[2] = cfplabel_string();
		parameterrequired[2] = false;
		parameters[3] = cfplabelplacement_string();
		parameterrequired[3] = false;
		parameters[4] = cfpprepend_string();
		parameterrequired[4] = false;
		parameters[5] = cfpappend_string();
		parameterrequired[5] = false;
		parameters[6] = cfpprependtolabel_string();
		parameterrequired[6] = false;
		parameters[7] = cfpappendtolabel_string();
		parameterrequired[7] = false;
	}

};


class cfwftimeselect : public cffunction
{
public:
	cfwftimeselect() {
		name = "timeSelect";
		returntype = T_STRING;

		parameters[0] = cfpobjectname_any();
		parameterrequired[0] = false;
		parameters[1] = cfpproperty_string();
		parameterrequired[1] = false;
		parameters[2] = cfporder_string();
		parameterrequired[2] = false;
		parameters[3] = cfpseparator_string();
		parameterrequired[3] = false;
		parameters[4] = cfpminutestep_numeric();
		parameterrequired[4] = false;
		parameters[5] = cfpincludeblank_any();
		parameterrequired[5] = false;
		parameters[6] = cfplabel_string();
		parameterrequired[6] = false;
		parameters[7] = cfplabelplacement_string();
		parameterrequired[7] = false;
		parameters[8] = cfpprepend_string();
		parameterrequired[8] = false;
		parameters[9] = cfpappend_string();
		parameterrequired[9] = false;
		parameters[10] = cfpprependtolabel_string();
		parameterrequired[10] = false;
		parameters[11] = cfpappendtolabel_string();
		parameterrequired[11] = false;
		parameters[12] = cfperrorelement_string();
		parameterrequired[12] = false;
	}

};


class cfwftimeselecttags : public cffunction
{
public:
	cfwftimeselecttags() {
		name = "timeSelectTags";
		returntype = T_STRING;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpselected_string();
		parameterrequired[1] = false;
		parameters[2] = cfporder_string();
		parameterrequired[2] = false;
		parameters[3] = cfpseparator_string();
		parameterrequired[3] = false;
		parameters[4] = cfpminutestep_numeric();
		parameterrequired[4] = false;
		parameters[5] = cfpincludeblank_any();
		parameterrequired[5] = false;
		parameters[6] = cfplabel_string();
		parameterrequired[6] = false;
		parameters[7] = cfplabelplacement_string();
		parameterrequired[7] = false;
		parameters[8] = cfpprepend_string();
		parameterrequired[8] = false;
		parameters[9] = cfpappend_string();
		parameterrequired[9] = false;
		parameters[10] = cfpprependtolabel_string();
		parameterrequired[10] = false;
		parameters[11] = cfpappendtolabel_string();
		parameterrequired[11] = false;
	}

};


class cfwfupdate : public cffunction
{
public:
	cfwfupdate() {
		name = "update";
		returntype = T_BOOLEAN;

		parameters[0] = cfpproperties_struct();
		parameterrequired[0] = false;
		parameters[1] = cfpparameterize_any();
		parameterrequired[1] = false;
	}

};


class cfwfupdateall : public cffunction
{
public:
	cfwfupdateall() {
		name = "updateAll";
		returntype = T_NUMERIC;

		parameters[0] = cfpwhere_string();
		parameterrequired[0] = false;
		parameters[1] = cfpinclude_string();
		parameterrequired[1] = false;
		parameters[2] = cfpproperties_struct();
		parameterrequired[2] = false;
		parameters[3] = cfpparameterize_any();
		parameterrequired[3] = false;
		parameters[4] = cfpinstantiate_boolean();
		parameterrequired[4] = false;
		parameters[5] = cfp$softdeletecheck_boolean();
		parameterrequired[5] = false;
	}

};


class cfwfupdatebykey : public cffunction
{
public:
	cfwfupdatebykey() {
		name = "updateByKey";
		returntype = T_BOOLEAN;

		parameters[0] = cfpkey_any();
		parameterrequired[0] = true;
		parameters[1] = cfpproperties_struct();
		parameterrequired[1] = false;
	}

};


class cfwfupdateone : public cffunction
{
public:
	cfwfupdateone() {
		name = "updateOne";
		returntype = T_BOOLEAN;

		parameters[0] = cfpwhere_string();
		parameterrequired[0] = false;
		parameters[1] = cfporder_string();
		parameterrequired[1] = false;
		parameters[2] = cfpproperties_struct();
		parameterrequired[2] = false;
	}

};


class cfwfurlfor : public cffunction
{
public:
	cfwfurlfor() {
		name = "urlFor";
		returntype = T_STRING;

		parameters[0] = cfproute_string();
		parameterrequired[0] = false;
		parameters[1] = cfpcontroller_string();
		parameterrequired[1] = false;
		parameters[2] = cfpaction_string();
		parameterrequired[2] = false;
		parameters[3] = cfpkey_any();
		parameterrequired[3] = false;
		parameters[4] = cfpparams_string();
		parameterrequired[4] = false;
		parameters[5] = cfpanchor_string();
		parameterrequired[5] = false;
		parameters[6] = cfponlypath_boolean();
		parameterrequired[6] = false;
		parameters[7] = cfphost_string();
		parameterrequired[7] = false;
		parameters[8] = cfpprotocol_string();
		parameterrequired[8] = false;
		parameters[9] = cfpport_numeric();
		parameterrequired[9] = false;
	}

};


class cfwfvalid : public cffunction
{
public:
	cfwfvalid() {
		name = "valid";
		returntype = T_BOOLEAN;

		parameters[0] = cfproute_string();
		parameterrequired[0] = false;
		parameters[1] = cfpcontroller_string();
		parameterrequired[1] = false;
		parameters[2] = cfpaction_string();
		parameterrequired[2] = false;
		parameters[3] = cfpkey_any();
		parameterrequired[3] = false;
		parameters[4] = cfpparams_string();
		parameterrequired[4] = false;
		parameters[5] = cfpanchor_string();
		parameterrequired[5] = false;
		parameters[6] = cfponlypath_boolean();
		parameterrequired[6] = false;
		parameters[7] = cfphost_string();
		parameterrequired[7] = false;
		parameters[8] = cfpprotocol_string();
		parameterrequired[8] = false;
		parameters[9] = cfpport_numeric();
		parameterrequired[9] = false;
	}

};


class cfwfvalidate : public cffunction
{
public:
	cfwfvalidate() {
		name = "validate";
		returntype = T_VOID;

		parameters[0] = cfpmethods_string();
		parameterrequired[0] = false;
		parameters[1] = cfpif_string();
		parameterrequired[1] = false;
		parameters[2] = cfpunless_string();
		parameterrequired[2] = false;
	}

};


class cfwfvalidateoncreate : public cffunction
{
public:
	cfwfvalidateoncreate() {
		name = "validateOnCreate";
		returntype = T_VOID;

		parameters[0] = cfpmethods_string();
		parameterrequired[0] = false;
		parameters[1] = cfpif_string();
		parameterrequired[1] = false;
		parameters[2] = cfpunless_string();
		parameterrequired[2] = false;
	}

};


class cfwfvalidateonupdate : public cffunction
{
public:
	cfwfvalidateonupdate() {
		name = "validateOnUpdate";
		returntype = T_VOID;

		parameters[0] = cfpmethods_string();
		parameterrequired[0] = false;
		parameters[1] = cfpif_string();
		parameterrequired[1] = false;
		parameters[2] = cfpunless_string();
		parameterrequired[2] = false;
	}

};


class cfwfvalidatesconfirmationof : public cffunction
{
public:
	cfwfvalidatesconfirmationof() {
		name = "validatesConfirmationOf";
		returntype = T_VOID;

		parameters[0] = cfpproperties_string();
		parameterrequired[0] = false;
		parameters[1] = cfpmessage_string();
		parameterrequired[1] = false;
		parameters[2] = cfpwhen_string();
		parameterrequired[2] = false;
		parameters[3] = cfpif_string();
		parameterrequired[3] = false;
		parameters[4] = cfpunless_string();
		parameterrequired[4] = false;
	}

};


class cfwfvalidatesexclusionof : public cffunction
{
public:
	cfwfvalidatesexclusionof() {
		name = "validatesExclusionOf";
		returntype = T_VOID;

		parameters[0] = cfpproperties_string();
		parameterrequired[0] = false;
		parameters[1] = cfplist_string();
		parameterrequired[1] = true;
		parameters[2] = cfpmessage_string();
		parameterrequired[2] = false;
		parameters[3] = cfpwhen_string();
		parameterrequired[3] = false;
		parameters[4] = cfpallowblank_boolean();
		parameterrequired[4] = false;
		parameters[5] = cfpif_string();
		parameterrequired[5] = false;
		parameters[6] = cfpunless_string();
		parameterrequired[6] = false;
	}

};


class cfwfvalidatesformatof : public cffunction
{
public:
	cfwfvalidatesformatof() {
		name = "validatesFormatOf";
		returntype = T_VOID;

		parameters[0] = cfpproperties_string();
		parameterrequired[0] = false;
		parameters[1] = cfpregex_string();
		parameterrequired[1] = false;
		parameters[2] = cfptype_string();
		parameterrequired[2] = false;
		parameters[3] = cfpmessage_string();
		parameterrequired[3] = false;
		parameters[4] = cfpwhen_string();
		parameterrequired[4] = false;
		parameters[5] = cfpallowblank_boolean();
		parameterrequired[5] = false;
		parameters[6] = cfpif_string();
		parameterrequired[6] = false;
		parameters[7] = cfpunless_string();
		parameterrequired[7] = false;
	}

};


class cfwfvalidatesinclusionof : public cffunction
{
public:
	cfwfvalidatesinclusionof() {
		name = "validatesInclusionOf";
		returntype = T_VOID;

		parameters[0] = cfpproperties_string();
		parameterrequired[0] = false;
		parameters[1] = cfplist_string();
		parameterrequired[1] = true;
		parameters[2] = cfpmessage_string();
		parameterrequired[2] = false;
		parameters[3] = cfpwhen_string();
		parameterrequired[3] = false;
		parameters[4] = cfpallowblank_boolean();
		parameterrequired[4] = false;
		parameters[5] = cfpif_string();
		parameterrequired[5] = false;
		parameters[6] = cfpunless_string();
		parameterrequired[6] = false;
	}

};


class cfwfvalidateslengthof : public cffunction
{
public:
	cfwfvalidateslengthof() {
		name = "validatesLengthOf";
		returntype = T_VOID;

		parameters[0] = cfpproperties_string();
		parameterrequired[0] = false;
		parameters[1] = cfpmessage_string();
		parameterrequired[1] = false;
		parameters[2] = cfpwhen_string();
		parameterrequired[2] = false;
		parameters[3] = cfpallowblank_boolean();
		parameterrequired[3] = false;
		parameters[4] = cfpexactly_numeric();
		parameterrequired[4] = false;
		parameters[5] = cfpmaximum_numeric();
		parameterrequired[5] = false;
		parameters[6] = cfpminimum_numeric();
		parameterrequired[6] = false;
		parameters[7] = cfpwithin_string();
		parameterrequired[7] = false;
		parameters[8] = cfpif_string();
		parameterrequired[8] = false;
		parameters[9] = cfpunless_string();
		parameterrequired[9] = false;
	}

};


class cfwfvalidatesnumericalityof : public cffunction
{
public:
	cfwfvalidatesnumericalityof() {
		name = "validatesNumericalityOf";
		returntype = T_VOID;

		parameters[0] = cfpproperties_string();
		parameterrequired[0] = false;
		parameters[1] = cfpmessage_string();
		parameterrequired[1] = false;
		parameters[2] = cfpwhen_string();
		parameterrequired[2] = false;
		parameters[3] = cfpallowblank_boolean();
		parameterrequired[3] = false;
		parameters[4] = cfponlyinteger_boolean();
		parameterrequired[4] = false;
		parameters[5] = cfpif_string();
		parameterrequired[5] = false;
		parameters[6] = cfpunless_string();
		parameterrequired[6] = false;
	}

};


class cfwfvalidatespresenceof : public cffunction
{
public:
	cfwfvalidatespresenceof() {
		name = "validatesPresenceOf";
		returntype = T_VOID;

		parameters[0] = cfpproperties_string();
		parameterrequired[0] = false;
		parameters[1] = cfpmessage_string();
		parameterrequired[1] = false;
		parameters[2] = cfpwhen_string();
		parameterrequired[2] = false;
		parameters[3] = cfpif_string();
		parameterrequired[3] = false;
		parameters[4] = cfpunless_string();
		parameterrequired[4] = false;
	}

};


class cfwfvalidatesuniquenessof : public cffunction
{
public:
	cfwfvalidatesuniquenessof() {
		name = "validatesUniquenessOf";
		returntype = T_VOID;

		parameters[0] = cfpproperties_string();
		parameterrequired[0] = false;
		parameters[1] = cfpmessage_string();
		parameterrequired[1] = false;
		parameters[2] = cfpwhen_string();
		parameterrequired[2] = false;
		parameters[3] = cfpallowblank_boolean();
		parameterrequired[3] = false;
		parameters[4] = cfpscope_string();
		parameterrequired[4] = false;
		parameters[5] = cfpif_string();
		parameterrequired[5] = false;
		parameters[6] = cfpunless_string();
		parameterrequired[6] = false;
	}

};


class cfwfverifies : public cffunction
{
public:
	cfwfverifies() {
		name = "verifies";
		returntype = T_VOID;

		parameters[0] = cfponly_string();
		parameterrequired[0] = false;
		parameters[1] = cfpexcept_string();
		parameterrequired[1] = false;
		parameters[2] = cfppost_any();
		parameterrequired[2] = false;
		parameters[3] = cfpget_any();
		parameterrequired[3] = false;
		parameters[4] = cfpajax_any();
		parameterrequired[4] = false;
		parameters[5] = cfpcookie_string();
		parameterrequired[5] = false;
		parameters[6] = cfpsession_string();
		parameterrequired[6] = false;
		parameters[7] = cfpparams_string();
		parameterrequired[7] = false;
		parameters[8] = cfphandler_string();
		parameterrequired[8] = false;
	}

};


class cfwfyearselecttag : public cffunction
{
public:
	cfwfyearselecttag() {
		name = "yearSelectTag";
		returntype = T_STRING;

		parameters[0] = cfpname_string();
		parameterrequired[0] = true;
		parameters[1] = cfpselected_string();
		parameterrequired[1] = false;
		parameters[2] = cfpstartyear_numeric();
		parameterrequired[2] = false;
		parameters[3] = cfpendyear_numeric();
		parameterrequired[3] = false;
		parameters[4] = cfpincludeblank_any();
		parameterrequired[4] = false;
		parameters[5] = cfplabel_string();
		parameterrequired[5] = false;
		parameters[6] = cfplabelplacement_string();
		parameterrequired[6] = false;
		parameters[7] = cfpprepend_string();
		parameterrequired[7] = false;
		parameters[8] = cfpappend_string();
		parameterrequired[8] = false;
		parameters[9] = cfpprependtolabel_string();
		parameterrequired[9] = false;
		parameters[10] = cfpappendtolabel_string();
		parameterrequired[10] = false;
	}

};

#endif


#endif

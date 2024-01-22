#ifndef _nppcf_npp_plugin_menu_h_
#define _nppcf_npp_plugin_menu_h_
//---------------------------------------------------------------------------
#include "core/NppPluginMenu.h"

#include "CFMLPlugin.h"
class nppCFMenu : public CNppPluginMenu
{
public:
	enum NMenuItems {
	    N_WRAPCFOUTPUT = 0,
	    N_WRAPCFCOMMENT,
	    N_WRAPCFDUMP,
	    N_SEPARATOR1,
	    N_AUTOCREQ,
	    N_AUTOCCFSQL,
	    N_FINGERTEXTINT,
	    N_SEPARATOR2,
	    N_ABOUT,

	    N_NBFUNCITEMS
	};
	static FuncItem arrFuncItems[N_NBFUNCITEMS];

public:
	static void		aboutDlg();
	static void		updateMenu();
	static void		wrapCFComment();
	static void		wrapCFOutput();
	static void		wrapCFDump();
	static void		toggleAutocReq();
	static void		toggleAutocCFSQL();
	static void		toggleIntegrateFT();


};

//---------------------------------------------------------------------------
#endif

#include "nppCFMenu.h"

extern CFMLPlugin        cfmlPlugin;
using namespace nppColdFusionNS;
FuncItem nppCFMenu::arrFuncItems[N_NBFUNCITEMS] = {
	{ _T( "Wrap in CFOutput Tags" ), wrapCFOutput, 0, false, NULL },
	{ _T( "Wrap in CFComment" ), wrapCFComment, 0, false, NULL },
	{ _T( "Wrap in CFDump" ), wrapCFDump, 0, false, NULL },
	{ _T( "" ), NULL, 0, false, NULL }, // separator
	{ _T( "Autocomplete Required Attributes By Default" ), toggleAutocReq, 0, false, NULL },
	{ _T( "Autocomplete cf_sql_ for cfsqltype" ), toggleAutocCFSQL, 0, false, NULL },
	{ _T( "Integrate with FingerText" ), toggleIntegrateFT, 0, false, NULL },
	{ _T( "" ), NULL, 0, false, NULL }, // separator
	{ _T( "About" ), aboutDlg, 0, false, NULL }
};

void nppCFMenu::toggleAutocReq()
{
	nppCFShared &cfs = *nppCFShared::Instance();
	cfs.alwaysCompleteReqAttributes = !cfs.alwaysCompleteReqAttributes;
	updateMenu();

}

void nppCFMenu::toggleAutocCFSQL()
{
	nppCFShared &cfs = *nppCFShared::Instance();
	cfs.completeCFsqltype = !cfs.completeCFsqltype;
	updateMenu();
}

void nppCFMenu::toggleIntegrateFT()
{
	nppCFShared &cfs = *nppCFShared::Instance();
	cfs.integrateWithFingerText = !cfs.integrateWithFingerText;
	updateMenu();
}

void nppCFMenu::updateMenu()
{
	nppCFShared &cfs = *nppCFShared::Instance();
	cfs.m_nppMsgr.SendNppMsg( NPPM_SETMENUITEMCHECK, arrFuncItems[N_AUTOCREQ]._cmdID, cfs.alwaysCompleteReqAttributes );
	cfs.m_nppMsgr.SendNppMsg( NPPM_SETMENUITEMCHECK, arrFuncItems[N_AUTOCCFSQL]._cmdID, cfs.completeCFsqltype );
	cfs.m_nppMsgr.SendNppMsg( NPPM_SETMENUITEMCHECK, arrFuncItems[N_FINGERTEXTINT]._cmdID, cfs.integrateWithFingerText );
}

void nppCFMenu::aboutDlg()
{
	cfmlPlugin.aboutDlg();
}


void nppCFMenu::wrapCFComment()
{
	cfmlPlugin.wrapCFComment();
}

void nppCFMenu::wrapCFOutput()
{
	cfmlPlugin.wrapCFOutput();
}

void nppCFMenu::wrapCFDump()
{
	cfmlPlugin.wrapCFDump();
}


/*INT_PTR nppCFMenu::PluginDialogBox(WORD idDlg, DLGPROC lpDlgFunc)
{
    // static function uses static (global) variable 'thePlugin'
    return ::DialogBox( (HINSTANCE) thePlugin.getDllModule(),
               MAKEINTRESOURCE(idDlg), m_nppMsgr.getNppWnd(), lpDlgFunc );
}*/
/*
void nppCFMenu::UpdateMenuState()
{
    HMENU hMenu = ::GetMenu( m_nppMsgr.getNppWnd() );
    ::CheckMenuItem(hMenu, arrFuncItems[N_AUTOCOMPLETE]._cmdID,
        MF_BYCOMMAND | (g_opt.m_bBracketsAutoComplete ? MF_CHECKED : MF_UNCHECKED));

    if ( g_opt.m_bBracketsAutoComplete )
    {
        cfmlPlugin.OnNppBufferActivated();
    }
}

void nppCFMenu::AllowAutocomplete(bool bAllow)
{
    HMENU hMenu = ::GetMenu( m_nppMsgr.getNppWnd() );
    ::EnableMenuItem(hMenu, arrFuncItems[N_AUTOCOMPLETE]._cmdID,
        MF_BYCOMMAND | (bAllow ? MF_ENABLED : MF_GRAYED));
    ::EnableMenuItem(hMenu, arrFuncItems[N_SETTINGS]._cmdID,
        MF_BYCOMMAND | (bAllow ? MF_ENABLED : MF_GRAYED));
}
*/
#define INCLUDE_DEPRECATED_FEATURES /// *** troubles here can occur yet
#include "SciMessager.h"

CSciMessager::CSciMessager( HWND hSciWnd )
{
	m_hSciWnd = hSciWnd;
	pSciMsg = (SciFnDirect)SendMessage(m_hSciWnd,SCI_GETDIRECTFUNCTION, 0, 0);

	pSciWndData = (sptr_t)SendMessage(m_hSciWnd,SCI_GETDIRECTPOINTER, 0, 0); 
}

CSciMessager::~CSciMessager()
{
}

LRESULT CSciMessager::SendSciMsg( UINT uMsg, WPARAM wParam , LPARAM lParam )
{
	//return ::SendMessage( m_hSciWnd, uMsg, wParam, lParam );
	return pSciMsg(pSciWndData, uMsg, wParam, lParam);
}

LRESULT CSciMessager::SendSciMsg( UINT uMsg, WPARAM wParam , LPARAM lParam ) const
{
	//return ::SendMessage( m_hSciWnd, uMsg, wParam, lParam );
	return pSciMsg(pSciWndData, uMsg, wParam, lParam);
}

void CSciMessager::beginUndoAction()
{
	SendSciMsg( SCI_BEGINUNDOACTION );
}

void CSciMessager::endUndoAction()
{
	SendSciMsg( SCI_ENDUNDOACTION );
}

unsigned char CSciMessager::getCharAt( int pos ) const
{
	return ( unsigned char ) SendSciMsg( SCI_GETCHARAT, ( WPARAM ) pos );
}

unsigned int CSciMessager::getCodePage() const
{
	return ( unsigned int ) SendSciMsg( SCI_GETCODEPAGE );
}

int CSciMessager::getCurrentPos() const
{
	return ( int ) SendSciMsg( SCI_GETCURRENTPOS );
}

int CSciMessager::getLineFromPos( int pos ) const
{
	return ( int ) SendSciMsg( SCI_LINEFROMPOSITION, ( WPARAM ) pos );
}

int CSciMessager::getLineState( int line ) const
{
	return ( int ) SendSciMsg( SCI_GETLINESTATE, ( WPARAM ) line );
}

int CSciMessager::getCaretInLine() const
{
	int curpos = SendSciMsg( SCI_GETCURRENTPOS );
	int line = SendSciMsg( SCI_LINEFROMPOSITION,( WPARAM ) curpos );
	int startofline = SendSciMsg( SCI_POSITIONFROMLINE, ( WPARAM ) line );
	return curpos - startofline;
}


LRESULT CSciMessager::getDocPointer() const
{
	return SendSciMsg( SCI_GETDOCPOINTER );
}

int CSciMessager::getSelectionMode() const
{
	return ( int ) SendSciMsg( SCI_GETSELECTIONMODE );
}

int CSciMessager::getSelectionEnd() const
{
	return ( int ) SendSciMsg( SCI_GETSELECTIONEND );
}

int CSciMessager::getSelectionStart() const
{
	return ( int ) SendSciMsg( SCI_GETSELECTIONSTART );
}

int CSciMessager::getSelText( char* pText ) const
{
	return ( int ) SendSciMsg( SCI_GETSELTEXT, 0, ( LPARAM ) pText );
}

int CSciMessager::getText( int len, char* pText ) const
{
	return ( int ) SendSciMsg( SCI_GETTEXT, ( WPARAM ) len, ( LPARAM ) pText );
}

int CSciMessager::getTextLength() const
{
	return ( int ) SendSciMsg( SCI_GETTEXTLENGTH );
}

int CSciMessager::getTextRange( int pos1, int pos2, char* pText ) const
{
	TextRange tr;
	tr.chrg.cpMin = pos1;
	tr.chrg.cpMax = pos2;
	tr.lpstrText = pText;
	return ( int ) SendSciMsg( SCI_GETTEXTRANGE, 0, ( LPARAM ) &tr );
}

int CSciMessager::getStyleAt( int pos ) const
{
	return ( int ) SendSciMsg( SCI_GETSTYLEAT, ( WPARAM ) pos );
}

void CSciMessager::goToPos( int pos )
{
	SendSciMsg( SCI_GOTOPOS, ( WPARAM ) pos );
}

bool CSciMessager::isModified() const
{
	return SendSciMsg( SCI_GETMODIFY ) ? true : false;
}

bool CSciMessager::isSelectionRectangle() const
{
	return SendSciMsg( SCI_SELECTIONISRECTANGLE ) ? true : false;
}

bool CSciMessager::isAutoCActive() const
{

	return SendSciMsg( SCI_AUTOCACTIVE ) ? true : false;
}

void CSciMessager::setCodePage( unsigned int codePage )
{
	SendSciMsg( SCI_SETCODEPAGE, ( WPARAM ) codePage );
}

void CSciMessager::setSel( int anchorPos, int currentPos )
{
	SendSciMsg( SCI_SETSEL, ( WPARAM ) anchorPos, ( LPARAM ) currentPos );
}

void CSciMessager::setSelectionMode( int mode )
{
	SendSciMsg( SCI_SETSELECTIONMODE, ( WPARAM ) mode );
}

void CSciMessager::setSelectionEnd( int pos )
{
	SendSciMsg( SCI_SETSELECTIONEND, ( WPARAM ) pos );
}

void CSciMessager::setSelectionStart( int pos )
{
	SendSciMsg( SCI_SETSELECTIONSTART, ( WPARAM ) pos );
}

void CSciMessager::setSelText( const char* pText )
{
	SendSciMsg( SCI_REPLACESEL, 0, ( LPARAM ) pText );
}

void CSciMessager::setText( const char* pText )
{
	SendSciMsg( SCI_SETTEXT, 0, ( LPARAM ) pText );
}

void CSciMessager::autoCShow( int len, const char* list )
{
	SendSciMsg( SCI_AUTOCSHOW, ( WPARAM ) len, ( LPARAM ) list );
}

void CSciMessager::autoCSetSeparator( char separator )
{
	SendSciMsg( SCI_AUTOCSETSEPARATOR, ( WPARAM ) separator );
}

void CSciMessager::autoCSetIgnoreCase( bool ignoreCase ) const
{
	SendSciMsg( SCI_AUTOCSETIGNORECASE, ( WPARAM ) ignoreCase );
}
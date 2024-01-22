#ifndef _sci_messager_h_
#define _sci_messager_h_
//---------------------------------------------------------------------------
#include "base.h"
#include "Scintilla.h"

class CSciMessager
{
protected:
	HWND m_hSciWnd;
	SciFnDirect pSciMsg;
	sptr_t pSciWndData; 

public:
	CSciMessager( HWND hSciWnd = NULL );
	virtual ~CSciMessager();

	LRESULT SendSciMsg( UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0 );
	LRESULT SendSciMsg( UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0 ) const;

	/* Text retrieval and modification */
	int           getText( int len, char* pText ) const;
	void          setText( const char* pText );
	void          beginUndoAction();
	void          endUndoAction();
	unsigned char getCharAt( int pos ) const;
	unsigned int  getCodePage() const; // 0 (non-Unicode), SC_CP_UTF8, DBCS etc.
	int           getCurrentPos() const;
	int				getCaretInLine() const;
	LRESULT       getDocPointer() const; // identifies the document
	int				getLineFromPos( int pos ) const;
	int				getLineState( int line ) const;
	HWND          getSciWnd() const  {
		return m_hSciWnd;
	}

	int           getSelectionMode() const; // SC_SEL_STREAM, SC_SEL_RECTANGLE, SC_SEL_LINES
	int           getSelectionEnd() const;
	int           getSelectionStart() const;
	int				getStyleAt( int pos ) const;
	int           getSelText( char* pText ) const;
	int           getTextLength() const;
	int           getTextRange( int pos1, int pos2, char* pText ) const;
	void          goToPos( int pos );
	bool          isModified() const;
	bool          isSelectionRectangle() const;
	bool		isAutoCActive() const;
	void          setCodePage( unsigned int codePage );
	void          setSciWnd( HWND hSciWnd )  {
		m_hSciWnd = hSciWnd;
	}
	void          setSel( int anchorPos, int currentPos );
	void          setSelectionMode( int mode ); // SC_SEL_STREAM, SC_SEL_RECTANGLE, SC_SEL_LINES
	void          setSelectionEnd( int pos );
	void          setSelectionStart( int pos );
	void          setSelText( const char* pText );
	void		  autoCShow( int len, const char *list );
	void		  autoCSetSeparator( char separator );
	void		  autoCSetIgnoreCase( bool ignoreCase ) const;
};

//---------------------------------------------------------------------------
#endif

// Not implemented yet

// void			setSavePoint();
// void			getLine(int line, char* text) const;
/*SCI_GETLINE(int line, char *text)
SCI_REPLACESEL(<unused>, const char *text)
SCI_SETREADONLY(bool readOnly)
SCI_GETREADONLY
SCI_GETTEXTRANGE(<unused>, Sci_TextRange *tr)
SCI_ALLOCATE(int bytes, <unused>)
SCI_ADDTEXT(int length, const char *s)
SCI_ADDSTYLEDTEXT(int length, cell *s)
SCI_APPENDTEXT(int length, const char *s)
SCI_INSERTTEXT(int pos, const char *text)
SCI_CLEARALL
SCI_CLEARDOCUMENTSTYLE
SCI_GETCHARAT(int position)
SCI_GETSTYLEAT(int position)
SCI_GETSTYLEDTEXT(<unused>, Sci_TextRange *tr)
SCI_SETSTYLEBITS(int bits)
SCI_GETSTYLEBITS		*/

/* Searching */

/*
SCI_FINDTEXT(int flags, Sci_TextToFind *ttf)
SCI_SEARCHANCHOR
SCI_SEARCHNEXT(int searchFlags, const char *text)
SCI_SEARCHPREV(int searchFlags, const char *text)
SCI_SETTARGETSTART(int pos)
SCI_GETTARGETSTART
SCI_SETTARGETEND(int pos)
SCI_GETTARGETEND
SCI_TARGETFROMSELECTION
SCI_SETSEARCHFLAGS(int searchFlags)
SCI_GETSEARCHFLAGS
SCI_SEARCHINTARGET(int length, const char *text)
SCI_REPLACETARGET(int length, const char *text)
SCI_REPLACETARGETRE(int length, const char *text)
SCI_GETTAG(int tagNumber, char *tagValue)
*/

/* Cut, copy & paste */

/*
SCI_CUT
SCI_COPY
SCI_PASTE
SCI_CLEAR
SCI_CANPASTE
SCI_COPYRANGE(int start, int end)
SCI_COPYTEXT(int length, const char *text)
SCI_COPYALLOWLINE
SCI_SETPASTECONVERTENDINGS(bool convert)
SCI_GETPASTECONVERTENDINGS
*/

/* Error handling */

/*

SCI_SETSTATUS(int status)
SCI_GETSTATUS
*/

/* Undo & Redo */

/*

SCI_UNDO
SCI_CANUNDO
SCI_EMPTYUNDOBUFFER
SCI_REDO
SCI_CANREDO
SCI_SETUNDOCOLLECTION(bool collectUndo)
SCI_GETUNDOCOLLECTION
SCI_BEGINUNDOACTION
SCI_ENDUNDOACTION
SCI_ADDUNDOACTION(int token, int flags)

*/
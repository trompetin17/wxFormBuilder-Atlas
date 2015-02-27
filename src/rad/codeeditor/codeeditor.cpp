///////////////////////////////////////////////////////////////////////////////
//
// wxFormBuilder - A Visual Dialog Editor for wxWidgets.
// Copyright (C) 2005 José Antonio Hurtado
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
// Written by
//   José Antonio Hurtado - joseantonio.hurtado@gmail.com
//   Juan Antonio Ortega  - jortegalalmolda@gmail.com
//
///////////////////////////////////////////////////////////////////////////////

#include "codeeditor.h"

#include <wx/fdrepdlg.h>
#include <wx/msgdlg.h>
#include <wx/sizer.h>

#if wxVERSION_NUMBER < 2900
    #include <wx/wxScintilla/wxscintilla.h>
#else
    #include <wx/stc/stc.h>
#endif

BEGIN_EVENT_TABLE ( CodeEditor,  wxPanel )
#if wxVERSION_NUMBER < 2900
	EVT_SCI_MARGINCLICK( wxID_ANY, CodeEditor::OnMarginClick )
#else
    EVT_STC_MARGINCLICK( wxID_ANY, CodeEditor::OnMarginClick )
#endif
	EVT_FIND( wxID_ANY, CodeEditor::OnFind )
	EVT_FIND_NEXT( wxID_ANY, CodeEditor::OnFind )
END_EVENT_TABLE()

CodeEditor::CodeEditor( wxWindow *parent, int id )
:
wxPanel( parent, id )
{
	wxBoxSizer *sizer = new wxBoxSizer( wxVERTICAL );

#if wxVERSION_NUMBER < 2900
	m_code = new wxScintilla( this, -1 );

	// Line Numbers
	m_code->SetMarginType( 0, wxSCI_MARGIN_NUMBER );
	m_code->SetMarginWidth( 0, m_code->TextWidth ( wxSCI_STYLE_LINENUMBER, wxT( "_99999" ) )  );

	// markers
	m_code->MarkerDefine ( wxSCI_MARKNUM_FOLDER, wxSCI_MARK_BOXPLUS );
	m_code->MarkerSetBackground ( wxSCI_MARKNUM_FOLDER, wxColour ( wxT( "BLACK" ) ) );
	m_code->MarkerSetForeground ( wxSCI_MARKNUM_FOLDER, wxColour ( wxT( "WHITE" ) ) );
	m_code->MarkerDefine ( wxSCI_MARKNUM_FOLDEROPEN, wxSCI_MARK_BOXMINUS );
	m_code->MarkerSetBackground ( wxSCI_MARKNUM_FOLDEROPEN, wxColour ( wxT( "BLACK" ) ) );
	m_code->MarkerSetForeground ( wxSCI_MARKNUM_FOLDEROPEN, wxColour ( wxT( "WHITE" ) ) );
	m_code->MarkerDefine ( wxSCI_MARKNUM_FOLDERSUB, wxSCI_MARK_EMPTY );
	m_code->MarkerDefine ( wxSCI_MARKNUM_FOLDEREND, wxSCI_MARK_BOXPLUS );
	m_code->MarkerSetBackground ( wxSCI_MARKNUM_FOLDEREND, wxColour ( wxT( "BLACK" ) ) );
	m_code->MarkerSetForeground ( wxSCI_MARKNUM_FOLDEREND, wxColour ( wxT( "WHITE" ) ) );
	m_code->MarkerDefine ( wxSCI_MARKNUM_FOLDEROPENMID, wxSCI_MARK_BOXMINUS );
	m_code->MarkerSetBackground ( wxSCI_MARKNUM_FOLDEROPENMID, wxColour ( wxT( "BLACK" ) ) );
	m_code->MarkerSetForeground ( wxSCI_MARKNUM_FOLDEROPENMID, wxColour ( wxT( "WHITE" ) ) );
	m_code->MarkerDefine ( wxSCI_MARKNUM_FOLDERMIDTAIL, wxSCI_MARK_EMPTY );
	m_code->MarkerDefine ( wxSCI_MARKNUM_FOLDERTAIL, wxSCI_MARK_EMPTY );

	// folding
	m_code->SetMarginType ( 1, wxSCI_MARGIN_SYMBOL );
	m_code->SetMarginMask ( 1, wxSCI_MASK_FOLDERS );
#else
    m_code = new wxStyledTextCtrl( this );

    // Line Numbers
    m_code->SetMarginType( 0, wxSTC_MARGIN_NUMBER );
    m_code->SetMarginWidth( 0, m_code->TextWidth ( wxSTC_STYLE_LINENUMBER, wxT( "_99999" ) )  );

    // markers
    m_code->MarkerDefine ( wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS );
    m_code->MarkerSetBackground ( wxSTC_MARKNUM_FOLDER, wxColour ( wxT( "BLACK" ) ) );
    m_code->MarkerSetForeground ( wxSTC_MARKNUM_FOLDER, wxColour ( wxT( "WHITE" ) ) );
    m_code->MarkerDefine ( wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS );
    m_code->MarkerSetBackground ( wxSTC_MARKNUM_FOLDEROPEN, wxColour ( wxT( "BLACK" ) ) );
    m_code->MarkerSetForeground ( wxSTC_MARKNUM_FOLDEROPEN, wxColour ( wxT( "WHITE" ) ) );
    m_code->MarkerDefine ( wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY );
    m_code->MarkerDefine ( wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUS );
    m_code->MarkerSetBackground ( wxSTC_MARKNUM_FOLDEREND, wxColour ( wxT( "BLACK" ) ) );
    m_code->MarkerSetForeground ( wxSTC_MARKNUM_FOLDEREND, wxColour ( wxT( "WHITE" ) ) );
    m_code->MarkerDefine ( wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS );
    m_code->MarkerSetBackground ( wxSTC_MARKNUM_FOLDEROPENMID, wxColour ( wxT( "BLACK" ) ) );
    m_code->MarkerSetForeground ( wxSTC_MARKNUM_FOLDEROPENMID, wxColour ( wxT( "WHITE" ) ) );
    m_code->MarkerDefine ( wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY );
    m_code->MarkerDefine ( wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY );

    // folding
    m_code->SetMarginType ( 1, wxSTC_MARGIN_SYMBOL );
    m_code->SetMarginMask ( 1, wxSTC_MASK_FOLDERS );
#endif
	m_code->SetMarginWidth ( 1, 16 );
	m_code->SetMarginSensitive ( 1, true );

	m_code->SetProperty( wxT( "fold" ),					wxT( "1" ) );
	m_code->SetProperty( wxT( "fold.comment" ),			wxT( "1" ) );
	m_code->SetProperty( wxT( "fold.compact" ),			wxT( "1" ) );
	m_code->SetProperty( wxT( "fold.preprocessor" ),		wxT( "1" ) );
	m_code->SetProperty( wxT( "fold.html" ),				wxT( "1" ) );
	m_code->SetProperty( wxT( "fold.html.preprocessor" ),	wxT( "1" ) );

#if wxVERSION_NUMBER < 2900
	m_code->SetFoldFlags( wxSCI_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSCI_FOLDFLAG_LINEAFTER_CONTRACTED );
#else
    m_code->SetFoldFlags( wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED );
#endif
	m_code->SetIndentationGuides( true );

	m_code->SetMarginWidth( 2, 0 );
	sizer->Add( m_code, 1, wxEXPAND | wxALL );
	SetSizer( sizer );
}

#if wxVERSION_NUMBER < 2900
void CodeEditor::OnMarginClick ( wxScintillaEvent &event )
#else
void CodeEditor::OnMarginClick ( wxStyledTextEvent &event )
#endif
{
	if ( event.GetMargin() == 1 )
	{
		int lineClick = m_code->LineFromPosition ( event.GetPosition() );
		int levelClick = m_code->GetFoldLevel ( lineClick );

#if wxVERSION_NUMBER < 2900
		if ( ( levelClick & wxSCI_FOLDLEVELHEADERFLAG ) > 0 )
#else
        if ( ( levelClick & wxSTC_FOLDLEVELHEADERFLAG ) > 0 )
#endif
		{
			m_code->ToggleFold ( lineClick );
		}
	}
}

#if wxVERSION_NUMBER < 2900
wxScintilla* CodeEditor::GetTextCtrl()
#else
wxStyledTextCtrl* CodeEditor::GetTextCtrl()
#endif
{
	return m_code;
}

void CodeEditor::OnFind( wxFindDialogEvent& event )
{
	int wxflags = event.GetFlags();
	int sciflags = 0;
	if ( (wxflags & wxFR_WHOLEWORD) != 0 )
	{
#if wxVERSION_NUMBER < 2900
		sciflags |= wxSCI_FIND_WHOLEWORD;
#else
        sciflags |= wxSTC_FIND_WHOLEWORD;
#endif
	}
	if ( (wxflags & wxFR_MATCHCASE) != 0 )
	{
#if wxVERSION_NUMBER < 2900
		sciflags |= wxSCI_FIND_MATCHCASE;
#else
        sciflags |= wxSTC_FIND_MATCHCASE;
#endif
	}
	int result;
	if ( (wxflags & wxFR_DOWN) != 0 )
	{
		m_code->SetSelectionStart( m_code->GetSelectionEnd() );
		m_code->SearchAnchor();
		result = m_code->SearchNext( sciflags, event.GetFindString() );
	}
	else
	{
		m_code->SetSelectionEnd( m_code->GetSelectionStart() );
		m_code->SearchAnchor();
		result = m_code->SearchPrev( sciflags, event.GetFindString() );
	}
#if wxVERSION_NUMBER < 2900
	if ( wxSCI_INVALID_POSITION == result )
#else
    if ( wxSTC_INVALID_POSITION == result )
#endif
	{
		wxMessageBox( wxString::Format( _("\"%s\" not found!"), event.GetFindString().c_str() ), _("Not Found!"), wxICON_ERROR, (wxWindow*)event.GetClientData() );
	}
	else
	{
		m_code->EnsureCaretVisible();
	}
}

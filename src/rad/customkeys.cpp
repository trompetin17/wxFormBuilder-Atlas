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

#include "customkeys.h"
#include "utils/debug.h"
#include "codegen/cppcg.h"
#include "model/objectbase.h"

#include <rad/appdata.h>

BEGIN_EVENT_TABLE(CustomKeysEvtHandler,wxEvtHandler)
  EVT_CHAR(CustomKeysEvtHandler::OnKeyPress)
END_EVENT_TABLE()

void CustomKeysEvtHandler::OnKeyPress(wxKeyEvent &event)
{
  LogDebug( wxT("%d"),event.GetKeyCode());

  if (event.GetKeyCode() == WXK_DELETE)
    AppData()->RemoveObject(AppData()->GetSelectedObject());
  else if (event.GetKeyCode() == 'P')
  {
    /////
    // prueba del parser
    /////

    LogDebug( wxT("#### Prueba del parser ####") );

    PObjectBase obj = AppData()->GetSelectedObject();
    PCodeInfo code_info = obj->GetObjectInfo()->GetCodeInfo( wxT("C++") );

    LogDebug( wxT("#### Plantillas ####") );

#if wxVERSION_NUMBER < 2900
    LogDebug((wxChar *)(code_info->GetTemplate( wxT("construction") ).c_str()));
    LogDebug((wxChar *)(code_info->GetTemplate( wxT("declaration") ).c_str()));
#else
    LogDebug( code_info->GetTemplate( wxT("construction") ) );
    LogDebug( code_info->GetTemplate( wxT("declaration") ) );
#endif
    LogDebug( wxT("#### Código ####") );
    {
      CppTemplateParser parser(obj,code_info->GetTemplate( wxT("construction") ), false, false, wxEmptyString );

#if wxVERSION_NUMBER < 2900
      LogDebug((wxChar *)parser.ParseTemplate().c_str());
#else
      LogDebug( parser.ParseTemplate() );
#endif
    }
    {
      CppTemplateParser parser(obj,code_info->GetTemplate( wxT("declaration") ), false, false, wxEmptyString );

#if wxVERSION_NUMBER < 2900
      LogDebug((wxChar *)parser.ParseTemplate().c_str());
#else
      LogDebug( parser.ParseTemplate() );
#endif
    }
  }
  else if (event.GetKeyCode() == 'C')
  {
    AppData()->GenerateCode();
  }
  else
    event.Skip();
}


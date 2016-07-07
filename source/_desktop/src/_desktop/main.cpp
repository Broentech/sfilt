//h+//////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2016 Broentech Solutions AS
// Contact: https://broentech.no/#!/contact
//
//
// GNU Lesser General Public License Usage
// This file may be used under the terms of the GNU Lesser
// General Public License version 3 as published by the Free Software
// Foundation and appearing in the file LICENSE.LGPL3 included in the
// packaging of this file. Please review the following information to
// ensure the GNU Lesser General Public License version 3 requirements
// will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
//
//
//////////////////////////////////////////////////////////////////////////////
//
//  \file      main.cpp
//
//  \brief     Application entry point
//
//  \author    Stian Broen
//
//  \date      28.06.2015
//
//
//
//
//  \par       Revision History
//
//
//             
//
//
//h-//////////////////////////////////////////////////////////////////////////

// Qt includes
#include <QApplication>

// local includes
#include "appwindow.h"

using namespace guiSpace;

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   app.setOrganizationName("Broentech Solutions AS");
   app.setOrganizationDomain("broentech.no");
   app.setApplicationName("SFilt");
   app.setApplicationVersion("0.0.1");
   AppWindow window;
   window.setWindowTitle("SFilt");
   window.show();
   return app.exec();
}
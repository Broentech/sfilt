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
//  \file      appwindow.h
//
//  \brief     Main window for rustbuster Desktop
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
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QString>

// solution includes
#include <imageViewWindow/imageViewWindow.h>

namespace guiSpace {
	class AppWindow : public QMainWindow
	{
		Q_OBJECT
		
	public:
		explicit AppWindow(QWidget *parent = 0);
		~AppWindow();

   signals:
      void loadImage(const QString &path);

   private slots:
      void openImageActionTriggered();
      void setUserMessage(const QString &message);

   private:
      void initActions();
      void initGUI();
      void initMenu();
      void initToolbar();
      void openImage(const QString &path);

   private:
      ImageViewWindow *m_imageView;
      QAction *m_openImageAction;
      QMenu *m_fileMenu;
      QToolBar *m_fileToolbar;
	};
}
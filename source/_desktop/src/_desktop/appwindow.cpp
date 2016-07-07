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
//  \file      appwindow.cpp
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
#include <QMenuBar>
#include <QFileDialog>
#include <QSettings>
#include <QFileInfo>
#include <QStandardPaths>
#include <QStatusBar>
#include <QScrollArea>

// local includes
#include "appwindow.h"

using namespace guiSpace;

AppWindow::AppWindow(QWidget *parent)
:QMainWindow(parent),
m_imageView(0),
m_fileMenu(0),
m_fileToolbar(0)
{
   initGUI();
   setAcceptDrops(true);
}

AppWindow::~AppWindow()
{

}

void AppWindow::initGUI()
{
   initActions();
   initMenu();
   initToolbar();

   m_imageView = new ImageViewWindow(this);

   connect(m_imageView, SIGNAL(setUserMessage(const QString &)),
      this, SLOT(setUserMessage(const QString &)));

   connect(this, SIGNAL(loadImage(const QString &)),
      m_imageView, SLOT(addImage(const QString &)));

   this->setCentralWidget(m_imageView);
   this->statusBar()->showMessage(tr("Ready"), 5000);
}

void AppWindow::initMenu()
{
   m_fileMenu = this->menuBar()->addMenu(tr("&File"));
   m_fileMenu->addAction(m_openImageAction);
}

void AppWindow::initToolbar()
{
   m_fileToolbar = this->addToolBar(tr("&File"));
   m_fileToolbar->addAction(m_openImageAction);
}

void AppWindow::initActions()
{
   m_openImageAction = new QAction(this);
   m_openImageAction->setIcon(QIcon(":/images/open.png"));
   m_openImageAction->setText("Load Image");

   connect(m_openImageAction, SIGNAL(triggered()),
      this, SLOT(openImageActionTriggered()));
}

void AppWindow::openImageActionTriggered()
{
   QSettings settings;
   QString folder = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
   settings.beginGroup("ocrtest");
   if (settings.contains("folderwithfiles"))
   {
      folder = settings.value("folderwithfiles").toString();
   }
   QString chosenFile = QFileDialog::getOpenFileName(this, "Image to analyze", folder, tr("Image Files (*.png *.jpg *.bmp *.jpeg)"));
   if (chosenFile == "")
   {
      // user cancelled
      this->statusBar()->showMessage("Cancelled", 5000);
      return;
   }
   QFileInfo fInfo(chosenFile);
   if (!fInfo.exists())
   {
      // user cancelled (or there was a mistake)
      this->statusBar()->showMessage("Cancelled", 5000);
      return;
   }
   QString imagedir = fInfo.dir().path();
   settings.setValue("folderwithfiles", imagedir);
   settings.endGroup();
   openImage(chosenFile);
}

void AppWindow::openImage(const QString &path)
{
   this->statusBar()->showMessage("Opening image " + path, 5000);
   emit loadImage(path);
}

void AppWindow::setUserMessage(const QString &message)
{
   this->statusBar()->showMessage(message, 5000);
}

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
//  \file      imageViewWindow.cpp
//
//  \brief     Window windget for displaying image items
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
#include <QVBoxLayout>
#include <QPainter>
#include <QPixmap>

// local includes
#include "imageViewWindow.h"
#include "singleImageData.h"

using namespace guiSpace;

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	ImageViewWindow ctor
//
//
//  \param  QWidget *parent -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  28.06.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
ImageViewWindow::ImageViewWindow(QWidget *parent)
:QWidget(parent),
m_imagesView(0),
m_leftButton(0),
m_rightButton(0),
m_currentIndex(0),
m_thumbGroup(0)
{
   initGui();
   this->setMinimumSize(QSize(400, 300));
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	ImageViewWindow ctor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  28.06.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
ImageViewWindow::~ImageViewWindow()
{

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	initGui
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  28.06.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
void ImageViewWindow::initGui()
{
   m_imagesView = new QStackedWidget(this);

   m_leftButton = new QToolButton(this);
   m_leftButton->setIcon(QIcon(":/images/left.png"));
   m_leftButton->setToolTip("Previous image");
   m_leftButton->setIconSize(QSize(32, 32));
   m_leftButton->setEnabled(false);

   connect(m_leftButton, SIGNAL(clicked()),
      this, SLOT(leftClicked()));

   m_rightButton = new QToolButton(this);
   m_rightButton->setIcon(QIcon(":/images/right.png"));
   m_rightButton->setToolTip("Next image");
   m_rightButton->setIconSize(QSize(32, 32));
   m_rightButton->setEnabled(false);

   connect(m_rightButton, SIGNAL(clicked()),
      this, SLOT(rightClicked()));

   m_imageThumbs = new QHBoxLayout;
   m_thumbGroup = new QButtonGroup(this);
   m_thumbGroup->setExclusive(true);

   QHBoxLayout *buttonLay = new QHBoxLayout;
   buttonLay->addWidget(m_leftButton);
   buttonLay->addStretch();
   buttonLay->addLayout(m_imageThumbs);
   buttonLay->addStretch();
   buttonLay->addWidget(m_rightButton);

   QVBoxLayout *lay = new QVBoxLayout;
   lay->addWidget(m_imagesView);
   lay->addLayout(buttonLay);
   this->setLayout(lay);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	leftClicked
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  28.06.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
void ImageViewWindow::leftClicked()
{
   --m_currentIndex;
   if (m_currentIndex < 0)
   {
      m_currentIndex = m_thumbnails.lastKey();
   }
   emit setUserMessage("Current image is " + m_thumbnails[m_currentIndex]->toolTip());
   m_thumbnails[m_currentIndex]->setChecked(true);
   m_imagesView->setCurrentIndex(m_currentIndex);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	rightClicked
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  28.06.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
void ImageViewWindow::rightClicked()
{
   ++m_currentIndex;
   if (m_currentIndex >= m_imagesView->count())
   {
      m_currentIndex = m_thumbnails.firstKey();
   }
   emit setUserMessage("Current image is " + m_thumbnails[m_currentIndex]->toolTip());
   m_thumbnails[m_currentIndex]->setChecked(true);
   m_imagesView->setCurrentIndex(m_currentIndex);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	addImage
//
//
//  \param  const QString &path -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  28.06.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
void ImageViewWindow::addImage(const QString &path)
{
   SingleImageData *newimage = new SingleImageData(this);
   newimage->setImage(path);
   m_currentIndex = m_imagesView->addWidget(newimage);
   QToolButton *thumb = new QToolButton(this);
   thumb->setIcon(QIcon(newimage->thumbnail()));
   thumb->setIconSize(QSize(64, 64));
   thumb->setChecked(true);
   thumb->setToolTip(path);

   connect(thumb, SIGNAL(clicked()),
      this, SLOT(thumbClicked()));

   m_thumbGroup->addButton(thumb);
   m_thumbnails[m_currentIndex] = thumb;
   resetThumbLay();
   m_imagesView->setCurrentIndex(m_currentIndex);
   m_leftButton->setEnabled(true);
   m_rightButton->setEnabled(true);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	resetThumbLay
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  28.06.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
void ImageViewWindow::resetThumbLay()
{
   for (int i = 0; i < m_imageThumbs->count(); i++)
   {
      m_imageThumbs->takeAt(i);
   }
   QMapIterator<int, QToolButton *> i(m_thumbnails);
   while (i.hasNext())
   {
      i.next();
      m_imageThumbs->addWidget(i.value());
      if (i.hasNext())
      {
         m_imageThumbs->addStretch();
      }
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	thumbClicked
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  28.06.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
void ImageViewWindow::thumbClicked()
{
   QToolButton *thumb = qobject_cast<QToolButton *>(this->sender());
   if (0 == thumb)
   {
      return;
   }
   QMapIterator<int, QToolButton *> i(m_thumbnails);
   while (i.hasNext())
   {
      i.next();
      if (i.value() == thumb)
      {
         emit setUserMessage("Current image is " + thumb->toolTip());
         return m_imagesView->setCurrentIndex(i.key());
      }
   }
}

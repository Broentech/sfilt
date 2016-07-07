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
//  \file      singleImageData.cpp
//
//  \brief     Window widget for displaying a single item image and data
//
//  \author    Stian Broen
//
//  \date      01.07.2015
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
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>

// local includes
#include "singleImageData.h"

using namespace guiSpace;
using namespace imageProcessingSpace;

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	SingleImageData ctor
//
//
//  \param  QWidget *parent -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  01.07.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
SingleImageData::SingleImageData(QWidget *parent)
:QWidget(parent),
m_original(0),
m_rgbView(0),
m_hsvView(0)
{
   initGUI();
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	SingleImageData ctor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  01.07.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
SingleImageData::~SingleImageData()
{

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	initGUI
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  01.07.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
void SingleImageData::initGUI()
{
   QTabWidget *alltab = new QTabWidget(this);
   alltab->addTab(initOrigTab(), "Original");
   alltab->addTab(initRGBTab(), "RGB");
   alltab->addTab(initHSVTab(), "HSV");

   QGridLayout *lay = new QGridLayout;
   lay->addWidget(alltab, 0, 0);

   this->setLayout(lay);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	initOrigTab
//
//
//  \param  N/A
//
//  \return QWidget*
//    
//  \author Stian Broen 
//
//  \date  02.07.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
QWidget* SingleImageData::initOrigTab()
{
   m_original = new SingleImageView(this);
   return m_original;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	initRGBTab
//
//
//  \param  N/A
//
//  \return QWidget*
//    
//  \author Stian Broen 
//
//  \date  02.07.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
QWidget* SingleImageData::initRGBTab()
{
   m_rgbView = new ChannelView(this);
   return m_rgbView;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	initHSVTab
//
//
//  \param  N/A
//
//  \return QWidget*
//    
//  \author Stian Broen 
//
//  \date  02.07.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
QWidget* SingleImageData::initHSVTab()
{
   m_hsvView = new ChannelView(this);
   return m_hsvView;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	setImage
//
//
//  \param  const QString &path -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  01.07.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
void SingleImageData::setImage(const QString &path)
{
   cv::Mat orig = loadMat(path);
   m_original->setImage(Mat2QImage(orig), "Original");
   std::vector<cv::Mat> chans = splitChannels_RGB_std(orig);
   QStringList names;
   names << "Red" << "Green" << "Blue";
   QList<QColor> rgbColors;
   rgbColors << QColor(Qt::red) << QColor(Qt::green) << QColor(Qt::blue);
   m_rgbView->setChannels(chans, RgbCmt, names, rgbColors);
   chans = splitChannels_HSV_std(orig);
   names.clear();
   names << "Hue" << "Saturation" << "Value";
   m_hsvView->setChannels(chans, HvsCmt, names);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	thumbnail
//
//
//  \param  N/A
//
//  \return QImage
//    
//  \author Stian Broen 
//
//  \date  01.07.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
QPixmap SingleImageData::thumbnail() const
{
   return m_original->thumbnail();
}

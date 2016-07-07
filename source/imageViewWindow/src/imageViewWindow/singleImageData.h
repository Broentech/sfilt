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
//  \file      singleImageData.h
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

#ifndef _RUSTBUST_SINGLE_IMAGE_DATA_H_
#define _RUSTBUST_SINGLE_IMAGE_DATA_H_

// Qt includes
#include <QWidget>
#include <QTabWidget>

// solution includes
#include <processImage/commonFunctions.h>

// local includes
#include "singleImage.h"
#include "singleChannelHistogram.h"
#include "channelView.h"

namespace guiSpace {
	class SingleImageData : public QWidget
	{
		Q_OBJECT
		
	public:
		explicit SingleImageData(QWidget *parent = 0);
		~SingleImageData();
      void setImage(const QString &path);
      QPixmap thumbnail() const;

   private:
      void initGUI();
      QWidget *initOrigTab();
      QWidget *initRGBTab();
      QWidget *initHSVTab();

   private:
      SingleImageView *m_original;
      ChannelView *m_rgbView;
      ChannelView *m_hsvView;
	};
}

#endif
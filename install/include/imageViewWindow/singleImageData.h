//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      singleImageData.h
//
//  \brief     Window widget for displaying a single item image and data
//
//  \author    Stian Broen
//
//  \date      01.07.2015
//
//  \par       Copyright: BroenTech Solutions AS
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
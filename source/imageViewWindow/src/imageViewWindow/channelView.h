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
//  \file      channelView.h
//
//  \brief     Window to manage an image that has been separated into channels
//
//  \author    Stian Broen
//
//  \date      02.07.2015
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

#ifndef _RUSTBUST_CHANNEL_VIEW_H_
#define _RUSTBUST_CHANNEL_VIEW_H_

// Qt includes
#include <QWidget>
#include <QTabWidget>
#include <QPair>
#include <QMap>
#include <QStringList>
#include <QToolBar>
#include <QAction>

// solution includes
#include <processImage/commonFunctions.h>

// local includes
#include "singleImage.h"
#include "singleChannelHistogram.h"

namespace guiSpace {

   typedef QPair<SingleImageView *, SingleChannelHistogram *> ChannelViewWidgets;
   typedef QMap<int, QPair<QString, ChannelViewWidgets> > ChannelViewMap;
   typedef QMapIterator<int, QPair<QString, ChannelViewWidgets> > ChannelViewMap_i;
   SingleChannelHistogram* findCorrespondingHistogram(SingleImageView *view, const ChannelViewMap &map);
   SingleImageView* findCorrespondingImageView(SingleChannelHistogram *hist, const ChannelViewMap &map);
   std::vector<cv::Mat> extractImagesFromViews_cv(const ChannelViewMap &map);
   cv::Mat extractImageFromHist_cv(const ChannelViewMap &map, SingleChannelHistogram *hist);
   cv::Mat lookupToMat(const QList<int> &lookup);

   typedef enum ChannelMapType
   {
      UnknownCMT,
      RgbCmt,
      HvsCmt,
   } ChannelMapType;

	class ChannelView : public QWidget
	{
		Q_OBJECT
		
	public:
      explicit ChannelView(QWidget *parent = 0);
      ~ChannelView();
      void setChannels(const std::vector<cv::Mat> &channels, ChannelMapType type, const QStringList &names = QStringList(), const QList<QColor> &colors = QList<QColor>());
      inline std::vector<cv::Mat> channels() const { return m_channels; }

   private:
      void initGUI();
      void clear();

   private slots:
      void channelHasProcessedImage(bool itstrue);
      void mergeTriggered();
      void histResetTriggered();
      void histApplyTriggered();
      void histSquashTriggered();
      void histDragTriggered();
      void histInverseTriggered();

   private:
      std::vector<cv::Mat> m_channels;
      QTabWidget *m_channelTab;
      ChannelViewMap m_widgets;
      QAction *m_mergeButton;
      QToolBar *m_channelTools;
      SingleImageView *m_merged;
      ChannelMapType m_type;
	};
}

#endif

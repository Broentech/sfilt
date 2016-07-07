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
//  \file      channelView.cpp
//
//  \brief     Window to manage an image that has been separated into channels
//
//  \author    Stian Broen
//
//  \date      02.07.2015
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

// Qt includes
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QToolButton>
#include <QMessageBox>
#include <QtMath>

// local includes
#include "channelView.h"

using namespace guiSpace;
using namespace imageProcessingSpace;

SingleChannelHistogram* guiSpace::findCorrespondingHistogram(SingleImageView *view, const ChannelViewMap &map)
{
   if (0 == view || map.size() == 0)
   {
      return 0;
   }
   ChannelViewMap_i i(map);
   while (i.hasNext())
   {
      i.next();
      if (i.value().second.first == view)
      {
         return i.value().second.second;
      }
   }
   return 0;
}

SingleImageView* guiSpace::findCorrespondingImageView(SingleChannelHistogram *hist, const ChannelViewMap &map)
{
   if (0 == hist || map.size() == 0)
   {
      return 0;
   }
   ChannelViewMap_i i(map);
   while (i.hasNext())
   {
      i.next();
      if (i.value().second.second == hist)
      {
         return i.value().second.first;
      }
   }
   return 0;
}

std::vector<cv::Mat> guiSpace::extractImagesFromViews_cv(const ChannelViewMap &map)
{
   std::vector<cv::Mat> ret;
   ChannelViewMap_i i(map);
   while (i.hasNext())
   {
      i.next();
      ret.push_back(QImage2Mat(i.value().second.first->currentImage()));
   }
   return ret;
}

cv::Mat guiSpace::extractImageFromHist_cv(const ChannelViewMap &map, SingleChannelHistogram *hist)
{
   ChannelViewMap_i i(map);
   while (i.hasNext())
   {
      i.next();
      if (i.value().second.second == hist)
      {
         return QImage2Mat(i.value().second.first->currentImage());
      }
   }
   return cv::Mat();
}

cv::Mat guiSpace::lookupToMat(const QList<int> &lookup)
{
   cv::Mat lut(1, lookup.size(), CV_8U);
   for (int i = 0; i < lookup.size(); i++)
   {
      lut.at<uchar>(i) = lookup[i];
   }
   return lut;
}

ChannelView::ChannelView(QWidget *parent)
   :QWidget(parent),
   m_channelTab(0),
   m_mergeButton(0),
   m_channelTools(0),
   m_merged(0),
   m_type(UnknownCMT)
{
   initGUI();
}

ChannelView::~ChannelView()
{

}

void ChannelView::initGUI()
{
   m_mergeButton = new QAction(this);
   m_mergeButton->setIcon(QIcon(":/images/merge.png"));
   m_mergeButton->setToolTip(tr("Merge channels"));

   connect(m_mergeButton, SIGNAL(triggered()),
      this, SLOT(mergeTriggered()));

   m_channelTools = new QToolBar(this);
   m_channelTools->addAction(m_mergeButton);

   QVBoxLayout *llay = new QVBoxLayout;
   llay->addWidget(m_channelTools);
   llay->addStretch();

   m_channelTab = new QTabWidget(this);

   QHBoxLayout *lay = new QHBoxLayout;

   lay->addLayout(llay);
   lay->addWidget(m_channelTab);

   this->setLayout(lay);
}

void ChannelView::setChannels(const std::vector<cv::Mat> &channels, ChannelMapType type, const QStringList &names, const QList<QColor> &colors)
{
   m_type = type;
   m_channelTab->clear();
   QList <QPair <QString, QImage> > _chans = splittedChannelsToQt(channels, names);
   for (int i = 0; i < _chans.size(); i++)
   {
      QPair <QString, QImage> p = _chans.at(i);
      QString text = p.first;
      QImage image = p.second;
      QColor color;
      if (i < colors.size())
      {
         color = colors.at(i);
      }
      else
      {
         color = QColor(Qt::darkGray);
      }
      SingleImageView *imgview = new SingleImageView(this);

      connect(imgview, SIGNAL(iHaveProcessedImage(bool)),
         this, SLOT(channelHasProcessedImage(bool)));

      imgview->setImage(image, text);
      SingleChannelHistogram *chart = new SingleChannelHistogram(this);

      connect(chart, SIGNAL(resetTriggered()),
         this, SLOT(histResetTriggered()));

      connect(chart, SIGNAL(applyTriggered()),
         this, SLOT(histApplyTriggered()));

      connect(chart, SIGNAL(squashTriggered()),
         this, SLOT(histSquashTriggered()));

      connect(chart, SIGNAL(dragTriggered()),
         this, SLOT(histDragTriggered()));

      connect(chart, SIGNAL(inverseTriggered()),
         this, SLOT(histInverseTriggered()));

      QMap<int, float> hist = calcHistogram(channels.at(i));
      chart->setData(hist, text, color);
      ChannelViewWidgets cvw;
      cvw.first = imgview;
      cvw.second = chart;
      m_widgets[i] = qMakePair(text, cvw);
      QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
      splitter->addWidget(imgview);
      splitter->addWidget(chart);
      m_channelTab->addTab(splitter, text);
   }
}

void ChannelView::clear()
{
   for (int i = 0; i < m_channelTab->count(); i++)
   {
      m_channelTab->widget(i)->deleteLater();
   }
   m_channels.clear();
   m_widgets.clear();
}

void ChannelView::channelHasProcessedImage(bool itstrue)
{
   SingleImageView *view = qobject_cast<SingleImageView *>(this->sender());
   SingleChannelHistogram *hist = findCorrespondingHistogram(view, m_widgets);
   if (0 == hist)
   {
      return;
   }
   QMap<int, float> data = calcHistogram(QImage2Mat(view->currentImage()));
   hist->updateData(data);
   if (0 != m_merged)
   {
      mergeTriggered();
   }
}

void ChannelView::mergeTriggered()
{
   cv::Mat result, tmp;
   std::vector<cv::Mat> chans;
   switch (m_type)
   {
   case(RgbCmt) :
      chans = flipChans(extractImagesFromViews_cv(m_widgets));
      cv::merge(chans, result);
      break;
   case(HvsCmt) :
      chans = extractImagesFromViews_cv(m_widgets);
      cv::merge(chans, tmp);
      cvtColor(tmp, result, CV_HSV2BGR);
      break;
   case(UnknownCMT) :
   default:
      chans = flipChans(extractImagesFromViews_cv(m_widgets));
      break;
   }

   if (0 == m_merged)
   {
      m_merged = new SingleImageView(this);
      m_channelTab->addTab(m_merged, tr("Merged"));
   }
   m_merged->setImage(result);
}

void ChannelView::histResetTriggered()
{
   qInfo() << "histResetTriggered - NOT IMPLEMENTED";
}

void ChannelView::histApplyTriggered()
{
   qInfo() << "histApplyTriggered - NOT IMPLEMENTED";
}

void ChannelView::histSquashTriggered()
{
   SingleChannelHistogram *hist = qobject_cast<SingleChannelHistogram *>(this->sender());
   if (0 == hist)
   {
      return;
   }
   qreal stepSize = 180.0 / 256.0;
   qreal amplitude = 0.5;
   QList<qreal> multis;
   for (qreal degrees = 0.0; degrees < 180.0; degrees += stepSize)
   {
      qreal radians = ((degrees * 3.14) / 180.0);
      qreal sinval = qSin(radians);
      qreal y = ((sinval * (amplitude / 2)) + (amplitude) / 2) - (amplitude / 2.0);
      multis << y;
   }

   QList<int> lookup;
   for (int i = 0; i < multis.size(); i++)
   {
      lookup << qRound(static_cast<qreal>(i)+static_cast<qreal>(i % 128) * multis[i]);
   }

   cv::Mat image = extractImageFromHist_cv(m_widgets, hist);
   cv::Mat lut = lookupToMat(lookup);
   cv::Mat result;
   cv::LUT(image, lut, result);

   SingleImageView *view = findCorrespondingImageView(hist, m_widgets);
   if (0 != view)
   {
      view->setImage_Processed(result);
   }
}

void ChannelView::histDragTriggered()
{
   SingleChannelHistogram *hist = qobject_cast<SingleChannelHistogram *>(this->sender());
   if (0 == hist)
   {
      return;
   }
   qreal stepSize = 180.0 / 256.0;
   qreal amplitude = 0.5;
   QList<qreal> multis;
   for (qreal degrees = 0.0; degrees < 180.0; degrees += stepSize)
   {
      qreal radians = ((degrees * 3.14) / 180.0);
      qreal sinval = -qSin(radians);
      qreal y = ((sinval * (amplitude / 2)) + (amplitude) / 2) - (amplitude / 2.0);
      multis << y;
   }

   QList<int> lookup;
   for (int i = 0; i < multis.size(); i++)
   {
      lookup << qRound(static_cast<qreal>(i) + static_cast<qreal>(i % 128) * multis[i]);
   }

   cv::Mat image = extractImageFromHist_cv(m_widgets, hist);
   cv::Mat lut = lookupToMat(lookup);
   cv::Mat result;
   cv::LUT(image, lut, result); 

   SingleImageView *view = findCorrespondingImageView(hist, m_widgets);
   if (0 != view)
   {
      view->setImage_Processed(result);
   }
}

void ChannelView::histInverseTriggered()
{

}
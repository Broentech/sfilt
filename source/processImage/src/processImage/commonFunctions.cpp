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
//  \file      commonFunctions.cpp
//
//  \brief     
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

// Qt includes
#include <QtDebug>

// local includes
#include "processImage.h"

using namespace imageProcessingSpace;

std::vector<cv::Mat> imageProcessingSpace::flipChans(const std::vector<cv::Mat> &chans)
{
   std::vector<cv::Mat> flip;
   for (int i = chans.size() - 1; i >= 0; i--)
   {
      flip.push_back(chans.at(i));
   }
   return flip;
}

cv::Mat imageProcessingSpace::loadMat(const QString &path)
{
   return cv::imread(path.toLatin1().data());
}

QImage imageProcessingSpace::Mat2QImage(const cv::Mat &src)
{
   try
   {
      switch (src.type())
      {
         // 8-bit, 4 channel
      case CV_8UC4:
      {
         QImage image(src.data, src.cols, src.rows, src.step, QImage::Format_ARGB32);
         return image;
      }

      // 8-bit, 3 channel
      case CV_8UC3:
      {
         QImage image(src.data, src.cols, src.rows, src.step, QImage::Format_RGB888);
         return image.rgbSwapped();
      }

      // 8-bit, 1 channel
      case CV_8UC1:
      {
         static QVector<QRgb>  sColorTable;
         // only create our color table once
         if (sColorTable.isEmpty())
         {
            for (int i = 0; i < 256; ++i)
            {
               sColorTable.push_back(qRgb(i, i, i));
            }
         }
         QImage image(src.data, src.cols, src.rows, src.step, QImage::Format_Indexed8);
         image.setColorTable(sColorTable);
         return image;
      }

      default:
         qWarning() << "imageProcessingSpace::Mat2QImage() - cv::Mat image type not handled in switch:" << src.type();
         break;
      }
   }
   catch (cv::Exception ex)
   {
      qCritical() << "imageProcessingSpace::Mat2QImage() - cv::Exception thrown : " << ex.msg.c_str();
   }

   return QImage();
}

cv::Mat imageProcessingSpace::QImage2Mat(const QImage &src, bool inCloneImageData)
{
   try
   {
      switch (src.format())
      {
         // 8-bit, 4 channel
      case QImage::Format_RGB32:
      {
         cv::Mat  mat(src.height(), src.width(), CV_8UC4, const_cast<uchar*>(src.bits()), src.bytesPerLine());
         return (inCloneImageData ? mat.clone() : mat);
      }

      // 8-bit, 3 channel
      case QImage::Format_RGB888:
      {
         if (!inCloneImageData)
         {
            qWarning() << "imageProcessingSpace::QImage2Mat() - Conversion requires cloning since we use a temporary QImage";
         }
         QImage   swapped = src.rgbSwapped();

         return cv::Mat(swapped.height(), swapped.width(), CV_8UC3, const_cast<uchar*>(swapped.bits()), swapped.bytesPerLine()).clone();
      }

      // 8-bit, 1 channel
      case QImage::Format_Indexed8:
      {
         cv::Mat  mat(src.height(), src.width(), CV_8UC1, const_cast<uchar*>(src.bits()), src.bytesPerLine());
         return (inCloneImageData ? mat.clone() : mat);
      }

      default:
         qWarning() << "imageProcessingSpace::QImage2Mat() - QImage format not handled in switch:" << src.format();
         break;
      }
   }
   catch (cv::Exception ex)
   {
      qCritical() << "imageProcessingSpace::QImage2Mat() - cv::Exception thrown : " << ex.msg.c_str();
   }
   return cv::Mat();
}

std::vector<cv::Mat> imageProcessingSpace::splitChannels_RGB_std(const cv::Mat &orig)
{
   std::vector<cv::Mat> planes;
   cv::split(orig, planes);
   return flipChans(planes);
}

QMap<QString, QImage> imageProcessingSpace::splitChannels_RGB(QImage image)
{
   cv::Mat orig = QImage2Mat(image);
   std::vector<cv::Mat> planes = splitChannels_RGB_std(orig);
   return splittedRGBChannelsToQt(planes);
}

std::vector<cv::Mat> imageProcessingSpace::splitChannels_HSV_std(const cv::Mat &orig)
{
   cv::Mat converted(orig.size(), orig.type());
   cv::cvtColor(orig, converted, CV_BGR2HSV);
   std::vector<cv::Mat> planes;
   cv::split(converted, planes);
   return planes;
}

QMap<QString, QImage> imageProcessingSpace::splitChannels_HSV(QImage image)
{
   cv::Mat orig = QImage2Mat(image);
   std::vector<cv::Mat> planes = splitChannels_HSV_std(orig);
   return splittedHSVChannelsToQt(planes);
}

QMap<QString, QImage> imageProcessingSpace::splittedRGBChannelsToQt(const std::vector<cv::Mat> &rgb)
{
   QMap<QString, QImage> rgbSplit;
   if (rgb.size() == 1)
   {
      rgbSplit["Gray"] = Mat2QImage(rgb.at(0)).copy();
   }
   else if (rgb.size() == 3)
   {
      rgbSplit["Blue"] = Mat2QImage(rgb.at(0)).copy();
      rgbSplit["Green"] = Mat2QImage(rgb.at(1)).copy();
      rgbSplit["Red"] = Mat2QImage(rgb.at(2)).copy();
   }
   else if (rgb.size() == 4)
   {
      rgbSplit["Blue"] = Mat2QImage(rgb.at(0)).copy();
      rgbSplit["Green"] = Mat2QImage(rgb.at(1)).copy();
      rgbSplit["Red"] = Mat2QImage(rgb.at(2)).copy();
      rgbSplit["Alpha"] = Mat2QImage(rgb.at(3)).copy();
   }
   return rgbSplit;
}

QList <QPair <QString, QImage> > imageProcessingSpace::splittedChannelsToQt(const std::vector<cv::Mat> &chans, const QStringList &names)
{
   QList <QPair <QString, QImage> > ret;
   for (int i = 0; i < chans.size(); i++)
   {
      if (i < names.size())
      {
         ret << qMakePair(names.at(i), Mat2QImage(chans.at(i)).copy());
      }
      else
      {
         ret << qMakePair(QString::number(i), Mat2QImage(chans.at(i)).copy());
      }
   }
   return ret;
}

QMap<QString, QImage> imageProcessingSpace::splittedHSVChannelsToQt(const std::vector<cv::Mat> &hsv)
{
   QMap<QString, QImage> hsvSplit;
   if (hsv.size() == 1)
   {
      hsvSplit["Gray"] = Mat2QImage(hsv.at(0)).copy();
   }
   else if (hsv.size() == 3)
   {
      hsvSplit["Value"] = Mat2QImage(hsv.at(0)).copy();
      hsvSplit["Saturation"] = Mat2QImage(hsv.at(1)).copy();
      hsvSplit["Hue"] = Mat2QImage(hsv.at(2)).copy();
   }
   else if (hsv.size() == 4)
   {
      hsvSplit["Value"] = Mat2QImage(hsv.at(0)).copy();
      hsvSplit["Saturation"] = Mat2QImage(hsv.at(1)).copy();
      hsvSplit["Hue"] = Mat2QImage(hsv.at(2)).copy();
      hsvSplit["Alpha"] = Mat2QImage(hsv.at(3)).copy();
   }
   return hsvSplit;
}

QMap<int, float> imageProcessingSpace::calcHistogram(const cv::Mat &orig)
{
   QMap<int, float> hist;
   int histSize[1];
   histSize[0] = 256;
   float hranges[2];
   hranges[0] = 0.0;
   hranges[1] = 255.0;
   const float* ranges[1];
   ranges[0] = hranges;
   int channels[1];
   channels[0] = 0;

   cv::MatND _hist;
   cv::calcHist(
      &orig,
      1,
      channels,
      cv::Mat(),
      _hist,
      1,
      histSize,
      ranges
      );

   for (int i = 0; i < 256; i++)
   {
      hist[i] = _hist.at<float>(i);
   }

   return hist;
}
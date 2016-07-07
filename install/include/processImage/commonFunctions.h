//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      commonFunctions.h
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

#ifndef _PROCESS_IMAGE_COMMONFUNCS_H_
#define _PROCESS_IMAGE_COMMONFUNCS_H_

// Qt includes
#include <QImage>
#include <QMap>

// opencv includes
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace imageProcessingSpace {
   
   cv::Mat loadMat(const QString &path);

   std::vector<cv::Mat> flipChans(const std::vector<cv::Mat> &chans);
   std::vector<cv::Mat> splitChannels_RGB_std(const cv::Mat &orig);
   QMap<QString, QImage> splitChannels_RGB(QImage image);
   QMap<QString, QImage> splittedRGBChannelsToQt(const std::vector<cv::Mat> &rgb);

   std::vector<cv::Mat> splitChannels_HSV_std(const cv::Mat &orig);
   QMap<QString, QImage> splitChannels_HSV(QImage image);
   QMap<QString, QImage> splittedHSVChannelsToQt(const std::vector<cv::Mat> &hsv);

   QList <QPair <QString, QImage> > splittedChannelsToQt(const std::vector<cv::Mat> &chans, const QStringList &names);

   QMap<int, float> calcHistogram(const cv::Mat &orig);
   QImage Mat2QImage(const cv::Mat &src);
   cv::Mat QImage2Mat(const QImage &src, bool inCloneImageData = true);
}

#endif
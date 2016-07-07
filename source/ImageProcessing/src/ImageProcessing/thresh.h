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
//  \file      thresh.h
//
//  \brief     Class containing threshold processing parameters for image processing
//
//  \author    Stian Broen
//
//  \date      11.10.2013
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

#ifndef _IMGPROC_THRESHOLD_H_
#define _IMGPROC_THRESHOLD_H_

// Qt includes
#include <QString>
#include <QMap>
#include <QJsonObject>

// local includes
#include "base.h"

namespace imageProcessingSpace {
   class CProcTask_Thresh : public CProcTaskBase
   {
   private:
      ThresholdChannel m_channel;
      ThresholdMethod m_method;
      ThresholdType m_type;
      ThresholdAdaptiveMethod m_adaptiveMethod;
      double m_thresholdValue;
      double m_maxValue;
      double m_C;
      int m_blockSize;
      QMap<ThresholdChannel, QString> m_childrenChannels;

   public:
      CProcTask_Thresh();
      CProcTask_Thresh(
         ThresholdChannel chan,
         ThresholdMethod method = THRESH_METHOD_REGULAR,
         ThresholdType type = THRESH_BINARY,
         ThresholdAdaptiveMethod admeth = THRESH_ADMETH_UNKNOWN,
         double value = 128,
         double max = 255,
         double c = 5,
         int blocksize = 3);
      ~CProcTask_Thresh();
      CProcTask_Thresh(const CProcTask_Thresh &other);
      CProcTask_Thresh(const QString &json);
      CProcTask_Thresh& operator=(const CProcTask_Thresh &other);
      bool operator==(const CProcTask_Thresh &other) const;
      bool operator!=(const CProcTask_Thresh &other) const;
      void clear();
      bool isValid() const;
      QString id() const;
      QString json() const;

      ThresholdChannel channel() const;
      ThresholdMethod method() const;
      ThresholdType type() const;
      ThresholdAdaptiveMethod adaptiveMethod() const;
      double thresholdValue() const;
      double maxValue() const;
      double ad_c() const;
      int blockSize() const;
      QMap<ThresholdChannel, QString> children() const;
      QString child(ThresholdChannel channel) const;
      void setChannel(ThresholdChannel val);
      void setMethod(ThresholdMethod val);
      void setType(ThresholdType val);
      void setAdaptiveMethod(ThresholdAdaptiveMethod val);
      void setThresholdValue(double val);
      void setMaxValue(double val);
      void setC(double val);
      void setBlockSize(int val);
      void setChildren(QMap<ThresholdChannel, QString> children);
      void setChild(ThresholdChannel channel, const QString &summary);
   };

   //CProcTask_Thresh thresholdModelFromSummary(const QString &summary, int i = 0);
   //QString thresholdModelToSummary(const CProcTask_Thresh &model);
   //bool setThresholdModelEntry(CProcTask_Thresh &model, const QString &variableName, const QString &value);

   QJsonObject CProcTask_Thresh_to_JSONOBJECT(const CProcTask_Thresh &prc);
   QString CProcTask_Thresh_to_JSON(const CProcTask_Thresh &prc);
   CProcTask_Thresh CProcTask_Thresh_from_JSON(const QString &json);
   CProcTask_Thresh CProcTask_Thresh_from_JSONOBJECT(const QJsonObject &obj);

   cv::Mat doThresholding(CProcTask_Thresh *spec, cv::Mat source);
}

#endif
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
//  \file      smooth.h
//
//  \brief     Class containing smoothing parameters for image processing
//
//  \author    Stian Broen
//
//  \date      13.09.2013
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

#ifndef _IMGPROC_SMOOTH_H_
#define _IMGPROC_SMOOTH_H_

// Qt includes
#include <QString>
#include <QJsonObject>

// local includes
#include "base.h"

namespace imageProcessingSpace {
   class CProcTask_Smooth : public CProcTaskBase
   {
   private:
      SmoothType m_type;
      int m_size1;
      int m_size2;
      double m_sigma1;
      double m_sigma2;

   public:
      CProcTask_Smooth();
      CProcTask_Smooth(SmoothType type, int size1, int size2, double sigma1 = 0.0, double sigma2 = 0.0);
      ~CProcTask_Smooth();
      CProcTask_Smooth(const CProcTask_Smooth &other);
      CProcTask_Smooth(const QString &json);
      CProcTask_Smooth& operator=(const CProcTask_Smooth &other);
      bool operator==(const CProcTask_Smooth &other) const;
      bool operator!=(const CProcTask_Smooth &other) const;
      void clear();
      bool isValid() const;
      QString id() const;
      QString json() const;

      inline SmoothType type() const { return m_type; }
      inline int size1() const { return m_size1; }
      inline int size2() const { return m_size2; }
      inline double sigma1() const { return m_sigma1; }
      inline double sigma2() const { return m_sigma2; }

      inline void setType(SmoothType type) { m_type = type; }
      inline void setSize1(int val) { m_size1 = val; }
      inline void setSize2(int val) { m_size2 = val; }
      inline void setSigma1(double val) { m_sigma1 = val; }
      inline void setSigma2(double val) { m_sigma2 = val; }
   };

   QJsonObject CProcTask_Smooth_to_JSONOBJECT(const CProcTask_Smooth &prc);
   QString CProcTask_Smooth_to_JSON(const CProcTask_Smooth &prc);
   CProcTask_Smooth CProcTask_Smooth_from_JSON(const QString &json);
   CProcTask_Smooth CProcTask_Smooth_from_JSONOBJECT(const QJsonObject &obj);

   //CProcTask_Smooth smoothModelFromSummary(const QString &summary);
   //QString smoothModelToSummary(const CProcTask_Smooth &model);
   //bool setSmoothModelEntry(CProcTask_Smooth &model, const QString &variableName, const QString &value);

   bool doSmoothing(CProcTask_Smooth *spec, cv::Mat source, cv::Mat &target);
   cv::Mat doSmoothing(CProcTask_Smooth *spec, cv::Mat source);
}

#endif
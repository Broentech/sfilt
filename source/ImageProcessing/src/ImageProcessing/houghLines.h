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
//  \file      houghLines.h
//
//  \brief     Class containing Hough lines transform (progressive probabilistic) parameters for image processing
//
//  \author    Stian Broen
//
//  \date      28.10.2013
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

#ifndef _IMGPROC_HOUGHLINES_H_
#define _IMGPROC_HOUGHLINES_H_

// Qt includes
#include <QString>
#include <QList>
#include <QLine>
#include <QJsonObject>

// local includes
#include "base.h"

namespace imageProcessingSpace {
   class CProcTask_HoughLines : public CProcTaskBase
   {
   private:
      double m_rho;
      double m_theta;
      int m_threshold;
      double m_param1;
      double m_param2;

   public:
      CProcTask_HoughLines();
      CProcTask_HoughLines(double rho, double theta, int threshold, double param1 = 0.0, double param2 = 0.0);
      ~CProcTask_HoughLines();
      CProcTask_HoughLines(const CProcTask_HoughLines &other);
      CProcTask_HoughLines(const QString &json);
      CProcTask_HoughLines& operator=(const CProcTask_HoughLines &other);
      bool operator==(const CProcTask_HoughLines &other) const;
      bool operator!=(const CProcTask_HoughLines &other) const;
      void clear();
      bool isValid() const;
      QString id() const;
      QString json() const;

      inline double rho() const { return m_rho; }
      inline double theta() const { return m_theta; }
      inline int threshold() const { return m_threshold; }
      inline double param1() const { return m_param1; }
      inline double param2() const { return m_param2; }

      inline void setRho(double val) { m_rho = val; }
      inline void setTheta(double val) { m_theta = val; }
      inline void setThreshold(int val) { m_threshold = val; }
      inline void setParam1(double val) { m_param1 = val; }
      inline void setParam2(double val) { m_param2 = val; }

   };

   //CProcTask_HoughLines houghLinesModelFromSummary(const QString &summary);
   //QString houghLinesToSummary(const CProcTask_HoughLines &model);
   //bool sethoughLinesModelEntry(CProcTask_HoughLines &model, const QString &variableName, const QString &value);

   QJsonObject CProcTask_HoughLines_to_JSONOBJECT(const CProcTask_HoughLines &prc);
   QString CProcTask_HoughLines_to_JSON(const CProcTask_HoughLines &prc);
   CProcTask_HoughLines CProcTask_HoughLines_from_JSON(const QString &json);
   CProcTask_HoughLines CProcTask_HoughLines_from_JSONOBJECT(const QJsonObject &obj);

   QList<QLine> doHoughLines(CProcTask_HoughLines *spec, cv::Mat source);
}

#endif
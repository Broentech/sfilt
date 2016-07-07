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
//  \file      houghLines.cpp
//
//  \brief     Class containing Hough lines transform parameters for image processing
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

// Qt includes
#include <QStringList>
#include <QPoint>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>

// local includes
#include "houghLines.h"

using namespace imageProcessingSpace;

CProcTask_HoughLines::CProcTask_HoughLines()
   :m_rho(-1.0),
   m_theta(-1.0),
   m_threshold(-1),
   m_param1(-1.0),
   m_param2(-1.0)
{

}

CProcTask_HoughLines::CProcTask_HoughLines(double rho, double theta, int threshold, double param1, double param2)
   :m_rho(rho),
   m_theta(theta),
   m_threshold(threshold),
   m_param1(param1),
   m_param2(param2)
{

}

CProcTask_HoughLines::~CProcTask_HoughLines()
{

}

CProcTask_HoughLines::CProcTask_HoughLines(const CProcTask_HoughLines &other)
   :m_rho(other.rho()),
   m_theta(other.theta()),
   m_threshold(other.threshold()),
   m_param1(other.param1()),
   m_param2(other.param2())
{

}

CProcTask_HoughLines::CProcTask_HoughLines(const QString &json)
{
   *this = CProcTask_HoughLines_from_JSON(json);
}

CProcTask_HoughLines& CProcTask_HoughLines::operator=(const CProcTask_HoughLines &other)
{
   m_rho = other.rho();
   m_theta = other.theta();
   m_threshold = other.threshold();
   m_param1 = other.param1();
   m_param2 = other.param2();
   return *this;
}

bool CProcTask_HoughLines::operator==(const CProcTask_HoughLines &other) const
{
   return (m_rho == other.rho() &&
      m_theta == other.theta() &&
      m_threshold == other.threshold() &&
      m_param1 == other.param1() &&
      m_param2 == other.param2());
}

bool CProcTask_HoughLines::operator!=(const CProcTask_HoughLines &other) const
{
   return !(*this == other);
}

void CProcTask_HoughLines::clear()
{
   m_rho = -1.0;
   m_theta = -1.0;
   m_threshold = -1;
   m_param1 = -1.0;
   m_param2 = -1.0;
}

bool CProcTask_HoughLines::isValid() const
{
   if (m_rho < 0.0 ||
      m_theta < 0.0 ||
      m_threshold < 0 ||
      m_param1 < 0.0 ||
      m_param2 < 0.0)
   {
      return false;
   }
   return true;
}

QString CProcTask_HoughLines::id() const
{
   return imgProcTaskToString(IMGPROC_HOUGHLINES);
}

QString CProcTask_HoughLines::json() const
{
   return CProcTask_HoughLines_to_JSON(*this);
}

QJsonObject imageProcessingSpace::CProcTask_HoughLines_to_JSONOBJECT(const CProcTask_HoughLines &prc)
{
   QJsonObject obj;
   obj[houghLineTag_rho] = prc.rho();
   obj[houghLineTag_theta] = prc.theta();
   obj[houghLineTag_threshold] = prc.threshold();
   obj[houghLineTag_param_1] = prc.param1();
   obj[houghLineTag_param_2] = prc.param2();
   return obj;
}

QString imageProcessingSpace::CProcTask_HoughLines_to_JSON(const CProcTask_HoughLines &prc)
{
   return QJsonDocument(CProcTask_HoughLines_to_JSONOBJECT(prc)).toJson();
}

CProcTask_HoughLines imageProcessingSpace::CProcTask_HoughLines_from_JSON(const QString &json)
{
   QJsonDocument doc = QJsonDocument::fromJson(json.toLatin1());
   if (doc.isNull())
   {
      return CProcTask_HoughLines();
   }
   QJsonObject obj = doc.object();
   return CProcTask_HoughLines_from_JSONOBJECT(obj);
}

CProcTask_HoughLines imageProcessingSpace::CProcTask_HoughLines_from_JSONOBJECT(const QJsonObject &obj)
{
   CProcTask_HoughLines prc;
   if (obj.isEmpty() ||
      obj[houghLineTag_rho].type() != QJsonValue::Double ||
      obj[houghLineTag_theta].type() != QJsonValue::Double ||
      obj[houghLineTag_threshold].type() != QJsonValue::Double ||
      obj[houghLineTag_param_1].type() != QJsonValue::Double ||
      obj[houghLineTag_param_2].type() != QJsonValue::Double
      )
   {
      return prc;
   }
   prc.setRho(obj[houghLineTag_rho].toDouble());
   prc.setRho(obj[houghLineTag_theta].toDouble());
   prc.setRho(obj[houghLineTag_threshold].toInt());
   prc.setRho(obj[houghLineTag_param_1].toDouble());
   prc.setRho(obj[houghLineTag_param_2].toDouble());
   return prc;
}

//CProcTask_HoughLines imageProcessingSpace::houghLinesModelFromSummary(const QString &summary)
//{
//   CProcTask_HoughLines ret;
//   QStringList splt = summary.split(',');
//   for (int i = 0; i < splt.size(); i++)
//   {
//      const QString spltAt = splt.at(i);
//      if (!spltAt.contains(':'))
//      {
//         continue;
//      }
//      const QString var = spltAt.split(':').at(0);
//      const QString val = spltAt.split(':').at(1);
//      sethoughLinesModelEntry(ret, var, val);
//   }
//   return ret;
//}
//
//QString imageProcessingSpace::houghLinesToSummary(const CProcTask_HoughLines &model)
//{
//   QString ret;
//   ret.append(houghLineTag_rho + ':' + QString::number(model.rho()) + ',' +
//      houghLineTag_theta + ':' + QString::number(model.theta()) + ',' +
//      houghLineTag_threshold + ':' + QString::number(model.threshold()) + ',' +
//      houghLineTag_param_1 + ':' + QString::number(model.param1()) + ',' +
//      houghLineTag_param_2 + ':' + QString::number(model.param2()) + ';');
//   return ret;
//}
//
//bool imageProcessingSpace::sethoughLinesModelEntry(CProcTask_HoughLines &model, const QString &variableName, const QString &value)
//{
//   if (variableName == houghLineTag_rho)
//   {
//      model.setRho(value.toDouble());
//   }
//   else if (variableName == houghLineTag_theta)
//   {
//      model.setTheta(value.toDouble());
//   }
//   else if (variableName == houghLineTag_threshold)
//   {
//      model.setThreshold(value.toInt());
//   }
//   else if (variableName == houghLineTag_param_1)
//   {
//      model.setParam1(value.toDouble());
//   }
//   else if (variableName == houghLineTag_param_2)
//   {
//      QString _val = value;
//      if (_val.contains(';'))
//      {
//         _val.remove(';');
//      }
//      model.setParam2(_val.toDouble());
//   }
//   else
//   {
//      return false;
//   }
//   return true;
//}

QList<QLine> imageProcessingSpace::doHoughLines(CProcTask_HoughLines *spec, cv::Mat source)
{
   QList<QLine> ret;
   if (0 == spec ||
      !spec->isValid())
   {
      return ret;
   }

   //std::vector<cv::Vec4i> lines;
   std::vector<cv::Vec2f> lines;
   try
   {
      cv::Mat dst, cdst;
      Canny(source, dst, 50, 200, 3);
      cvtColor(dst, cdst, CV_GRAY2BGR);

      //HoughLinesP(dst, lines, 1          , CV_PI / 180  , 50               , 50            , 10);
      HoughLines  (dst, lines, spec->rho(), spec->theta(), spec->threshold(), spec->param1(), spec->param2());
   }
   catch (cv::Exception e)
   {
      qDebug() << "imageProcessingSpace::doHoughLines - cvHoughLines2 Exception : " << e.msg.c_str();
      return ret;
   }

   for (int i = 0; i < lines.size(); i++)
   {
      float rho = lines[i][0];
      float theta = lines[i][1];
      double a = cos(theta), b = sin(theta);
      double x0 = a*rho, y0 = b*rho;

      QPoint pt1(
         cvRound(x0 + 1000 * (-b)),
         cvRound(y0 + 1000 * (a)));

      QPoint pt2(
         cvRound(x0 - 1000 * (-b)),
         cvRound(y0 - 1000 * (a)));

      QLine line(pt1, pt2);
      ret << line;
   }
   return ret;
}
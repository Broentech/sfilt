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
//  \file      smooth.cpp
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

// Qt includes
#include <QStringList>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>

// local includes
#include "smooth.h"

using namespace imageProcessingSpace;
Q_DECLARE_METATYPE(SmoothType)

CProcTask_Smooth::CProcTask_Smooth()
:m_type(UNKNOWN_SMOOTH),
m_size1(0),
m_size2(0),
m_sigma1(0.0),
m_sigma2(0.0)
{

}

CProcTask_Smooth::CProcTask_Smooth(SmoothType type, int size1, int size2, double sigma1, double sigma2)
   :m_type(type),
   m_size1(size1),
   m_size2(size2),
   m_sigma1(sigma1),
   m_sigma2(sigma2)
{

}

CProcTask_Smooth::~CProcTask_Smooth()
{

}

CProcTask_Smooth::CProcTask_Smooth(const CProcTask_Smooth &other)
   :m_type(other.type()),
   m_size1(other.size1()),
   m_size2(other.size2()),
   m_sigma1(other.sigma1()),
   m_sigma2(other.sigma2())
{

}

CProcTask_Smooth::CProcTask_Smooth(const QString &json)
{
   *this = CProcTask_Smooth_from_JSON(json);
}

CProcTask_Smooth& CProcTask_Smooth::operator=(const CProcTask_Smooth &other)
{
   m_type = other.type();
   m_size1 = other.size1();
   m_size2 = other.size2();
   m_sigma1 = other.sigma1();
   m_sigma2 = other.sigma2();
   return *this;
}

bool CProcTask_Smooth::operator==(const CProcTask_Smooth &other) const
{
   return(m_type == other.type() &&
      m_size1 == other.size1() &&
      m_size2 == other.size2() &&
      m_sigma1 == other.sigma1() &&
      m_sigma2 == other.sigma2());
}

bool CProcTask_Smooth::operator!=(const CProcTask_Smooth &other) const
{
   return !(*this == other);
}

void CProcTask_Smooth::clear()
{
   m_type = UNKNOWN_SMOOTH;
   m_size1 = 0;
   m_size2 = 0;
   m_sigma1 = 0.0;
   m_sigma2 = 0.0;
}

bool CProcTask_Smooth::isValid() const
{
   if (m_type == UNKNOWN_SMOOTH || (m_size1 == 0 && m_size2 == 0))
   {
      return false;
   }
   return true;
}

QString CProcTask_Smooth::id() const
{
   return smoothTypeToString(m_type);
}

QString CProcTask_Smooth::json() const
{
   return CProcTask_Smooth_to_JSON(*this);
}


QJsonObject imageProcessingSpace::CProcTask_Smooth_to_JSONOBJECT(const CProcTask_Smooth &prc)
{
   QJsonObject obj;
   obj[smoothTag_TYPE] = smoothTypeToString(prc.type());
   obj[smoothTag_SIZE1] = prc.size1();
   obj[smoothTag_SIZE2] = prc.size2();
   obj[smoothTag_SIGMA1] = prc.sigma1();
   obj[smoothTag_SIGMA2] = prc.sigma2();
   return obj;
}

QString imageProcessingSpace::CProcTask_Smooth_to_JSON(const CProcTask_Smooth &prc)
{
   return QJsonDocument(CProcTask_Smooth_to_JSONOBJECT(prc)).toJson();
}

CProcTask_Smooth imageProcessingSpace::CProcTask_Smooth_from_JSON(const QString &json)
{
   QJsonDocument doc = QJsonDocument::fromJson(json.toLatin1());
   if (doc.isNull())
   {
      return CProcTask_Smooth();
   }
   QJsonObject obj = doc.object();
   return CProcTask_Smooth_from_JSONOBJECT(obj);
}

CProcTask_Smooth imageProcessingSpace::CProcTask_Smooth_from_JSONOBJECT(const QJsonObject &obj)
{
   CProcTask_Smooth prc;
   if (obj.isEmpty() ||
      obj[smoothTag_TYPE].type() != QJsonValue::String ||
      obj[smoothTag_SIZE1].type() != QJsonValue::Double ||
      obj[smoothTag_SIZE2].type() != QJsonValue::Double ||
      obj[smoothTag_SIGMA1].type() != QJsonValue::Double ||
      obj[smoothTag_SIGMA2].type() != QJsonValue::Double)
   {
      return prc;
   }
   prc.setType(smoothTypeFromString(obj[smoothTag_TYPE].toString()));
   prc.setSize1(obj[smoothTag_SIZE1].toInt());
   prc.setSize2(obj[smoothTag_SIZE2].toInt());
   prc.setSigma1(obj[smoothTag_SIGMA1].toInt());
   prc.setSigma2(obj[smoothTag_SIGMA2].toInt());
   return prc;
}

//CProcTask_Smooth imageProcessingSpace::smoothModelFromSummary(const QString &summary)
//{
//   CProcTask_Smooth ret;
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
//      if (!setSmoothModelEntry(ret, var, val))
//      {
//         qDebug() << "Invalid variable/value pair";
//      }
//   }
//   return ret;
//}
//QString imageProcessingSpace::smoothModelToSummary(const CProcTask_Smooth &model)
//{
//   return smoothTag_TYPE + ':' + smoothTypeToString(model.type()) + ',' +
//      smoothTag_SIZE1 + ':' + QString("%1").arg(model.size1()) + ',' +
//      smoothTag_SIZE2 + ':' + QString("%1").arg(model.size2()) + ',' +
//      smoothTag_SIGMA1 + ':' + QString("%1").arg(model.sigma1()) + ',' +
//      smoothTag_SIGMA2 + ':' + QString("%1").arg(model.sigma2()) + ',';
//}
//bool imageProcessingSpace::setSmoothModelEntry(CProcTask_Smooth &model, const QString &variableName, const QString &value)
//{
//   if (variableName == smoothTag_TYPE)
//   {
//      model.setType(smoothTypeFromString(value));
//   }
//   else if (variableName == smoothTag_SIZE1)
//   {
//      model.setSize1(value.toInt());
//   }
//   else if (variableName == smoothTag_SIZE2)
//   {
//      model.setSize2(value.toInt());
//   }
//   else if (variableName == smoothTag_SIGMA1)
//   {
//      model.setSigma1(value.toDouble());
//   }
//   else if (variableName == smoothTag_SIGMA2)
//   {
//      model.setSigma2(value.toDouble());
//   }
//   else
//   {
//      return false;
//   }
//   return true;
//}

bool imageProcessingSpace::doSmoothing(CProcTask_Smooth *spec, cv::Mat source, cv::Mat &target)
{
   if (0 == spec || 0 == source.data || 0 == target.data || !spec->isValid())
   {
      return false;
   }

   cv::Size _size;
   _size.height = spec->size1();
   _size.width = spec->size2();

   try
   {
      blur(source, target, _size);
   }
   catch (cv::Exception e)
   {
      qDebug() << "imageProcessingSpace::doSmoothing - cvSmooth Exception : " << e.msg.c_str();
      return false;
   }
   return true;
}

cv::Mat imageProcessingSpace::doSmoothing(CProcTask_Smooth *spec, cv::Mat source)
{
   cv::Mat out(source.size(), source.depth(), source.channels());
   if (0 == spec || 0 == source.data)
   {
      return out;
   }

   cv::Size _size;
   _size.height = spec->size1();
   _size.width = spec->size2();

   try
   {
      switch (spec->type())
      {
      case(BLUR) :
         blur(source, out, _size);
         break;
      case(GAUSSIAN) :
         GaussianBlur(source, out, _size, spec->sigma1(), spec->sigma2());
         break;
      case(MEDIAN) :
         medianBlur(source, out, _size.height);
         break;
      case(BILATERAL) :
         bilateralFilter(source, out, _size.height, spec->sigma1(), spec->sigma2());
         break;
      default:
         break;
      }
   }
   catch (cv::Exception e)
   {
      qDebug() << "imageProcessingSpace::doSmoothing - cvSmooth Exception : " << e.msg.c_str();
   }


   return out;
}
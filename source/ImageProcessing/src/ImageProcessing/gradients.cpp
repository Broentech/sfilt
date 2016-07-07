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
//  \file      gradients.h
//
//  \brief     Class containing gradients parameters for image transforms
//
//  \author    Stian Broen
//
//  \date      13.10.2013
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
#include "gradients.h"

using namespace imageProcessingSpace;
Q_DECLARE_METATYPE(GradientType)

CProcTask_Gradients::CProcTask_Gradients()
:m_type(GRADIENT_TYPE_UNKNOWN),
m_order_x(-1),
m_order_y(-1),
m_apertureSize(0),
m_lowThreshold(-1.0),
m_highThreshold(-1.0)
{

}

CProcTask_Gradients::CProcTask_Gradients(GradientType type, int order_x, int order_y, int apertureSize, double lowThreshold, double highThreshold)
   :m_type(type),
   m_order_x(order_x),
   m_order_y(order_y),
   m_apertureSize(apertureSize),
   m_lowThreshold(lowThreshold),
   m_highThreshold(highThreshold)
{

}

CProcTask_Gradients::~CProcTask_Gradients()
{

}

CProcTask_Gradients::CProcTask_Gradients(const CProcTask_Gradients &other)
   :m_type(other.type()),
   m_order_x(other.order_x()),
   m_order_y(other.order_y()),
   m_apertureSize(other.apertureSize()),
   m_lowThreshold(other.lowThreshold()),
   m_highThreshold(other.highThreshold())
{

}

CProcTask_Gradients::CProcTask_Gradients(const QString &json)
{
   *this = CProcTask_Gradients_from_JSON(json);
}

CProcTask_Gradients& CProcTask_Gradients::operator=(const CProcTask_Gradients &other)
{
   m_type = other.type();
   m_order_x = other.order_x();
   m_order_y = other.order_y();
   m_apertureSize = other.apertureSize();
   m_lowThreshold = other.lowThreshold();
   m_highThreshold = other.highThreshold();
   return *this;
}

bool CProcTask_Gradients::operator==(const CProcTask_Gradients &other) const
{
   return (m_type == other.type() &&
      m_order_x == other.order_x() &&
      m_order_y == other.order_y() &&
      m_apertureSize == other.apertureSize() &&
      m_lowThreshold == other.lowThreshold() &&
      m_highThreshold == other.highThreshold());
}

bool CProcTask_Gradients::operator!=(const CProcTask_Gradients &other) const
{
   return !(*this == other);
}

void CProcTask_Gradients::clear()
{
   m_type = GRADIENT_TYPE_UNKNOWN;
   m_order_x = -1;
   m_order_y = -1;
   m_apertureSize = 0;
   m_lowThreshold = -1.0;
   m_highThreshold = -1.0;
}

bool CProcTask_Gradients::isValid() const
{
   if (m_type != CV_SCHARR &&
      m_apertureSize != 1 &&
      m_apertureSize != 3 &&
      m_apertureSize != 5 &&
      m_apertureSize != 7)
   {
      return false;
   }
   if ((m_type == GRADIENT_TYPE_SOBEL || GRADIENT_TYPE_SCHARR) &&
      (m_order_x != 0 && m_order_x != 1 && m_order_x != 2) &&
      (m_order_y != 0 && m_order_y != 1 && m_order_y != 2))
   {
      return false;
   }
   return true;
}

QString CProcTask_Gradients::id() const
{
   return gradientTypeToString(m_type);
}

QString CProcTask_Gradients::json() const
{
   return CProcTask_Gradients_to_JSON(*this);
}

//CProcTask_Gradients imageProcessingSpace::gradientsModelFromSummary(const QString &summary)
//{
//   CProcTask_Gradients ret;
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
//      setGradientsModelEntry(ret, var, val);
//   }
//   return ret;
//}

QJsonObject imageProcessingSpace::CProcTask_Gradients_to_JSONOBJECT(const CProcTask_Gradients &prc)
{
   QJsonObject obj;
   obj[gradsTag_type] = gradientTypeToString(prc.type());
   obj[gradsTag_order_x] = prc.order_x();
   obj[gradsTag_order_y] = prc.order_y();
   obj[gradsTag_apSize] = prc.apertureSize();
   obj[gradsTag_lowThreshold] = prc.lowThreshold();
   obj[gradsTag_highThreshold] = prc.highThreshold();
   return obj;
}

QString imageProcessingSpace::CProcTask_Gradients_to_JSON(const CProcTask_Gradients &prc)
{
   return QJsonDocument(CProcTask_Gradients_to_JSONOBJECT(prc)).toJson();
}

CProcTask_Gradients imageProcessingSpace::CProcTask_Gradients_from_JSON(const QString &json)
{
   QJsonDocument doc = QJsonDocument::fromJson(json.toLatin1());
   if (doc.isNull())
   {
      return CProcTask_Gradients();
   }
   QJsonObject obj = doc.object();
   return CProcTask_Gradients_from_JSONOBJECT(obj);
}

CProcTask_Gradients imageProcessingSpace::CProcTask_Gradients_from_JSONOBJECT(const QJsonObject &obj)
{
   CProcTask_Gradients prc;
   if (obj.isEmpty() ||
      obj[gradsTag_type].type() != QJsonValue::String ||
      obj[gradsTag_order_x].type() != QJsonValue::Double ||
      obj[gradsTag_order_y].type() != QJsonValue::Double ||
      obj[gradsTag_apSize].type() != QJsonValue::Double ||
      obj[gradsTag_lowThreshold].type() != QJsonValue::Double ||
      obj[gradsTag_highThreshold].type() != QJsonValue::Double
      )
   {
      return prc;
   }
   prc.setType(gradientTypeFromString(obj[gradsTag_type].toString()));
   prc.setOrder_x(obj[gradsTag_order_x].toDouble());
   prc.setOrder_y(obj[gradsTag_order_y].toDouble());
   prc.setApertureSize(obj[gradsTag_apSize].toDouble());
   prc.setLowThreshold(obj[gradsTag_lowThreshold].toDouble());
   prc.setHighThreshold(obj[gradsTag_highThreshold].toDouble());
   return prc;
}

//QString imageProcessingSpace::gradientsModelToSummary(const CProcTask_Gradients &model)
//{
//   return gradsTag_type + ':' + gradientTypeToString(model.type()) + ',' +
//      gradsTag_order_x + ':' + QString("%1").arg(model.order_x()) + ',' +
//      gradsTag_order_y + ':' + QString("%1").arg(model.order_y()) + ',' +
//      gradsTag_apSize + ':' + QString("%1").arg(model.apertureSize()) + ',' +
//      gradsTag_lowThreshold + ':' + QString("%1").arg(model.lowThreshold()) + ',' +
//      gradsTag_highThreshold + ':' + QString("%1").arg(model.highThreshold()) + ',';
//}
//
//bool imageProcessingSpace::setGradientsModelEntry(CProcTask_Gradients &model, const QString &variableName, const QString &value)
//{
//   if (variableName == gradsTag_type)
//   {
//      model.setType(gradientTypeFromString(value));
//   }
//   else if (variableName == gradsTag_order_x)
//   {
//      model.setOrder_x(value.toInt());
//   }
//   else if (variableName == gradsTag_order_y)
//   {
//      model.setOrder_y(value.toInt());
//   }
//   else if (variableName == gradsTag_apSize)
//   {
//      model.setApertureSize(value.toInt());
//   }
//   else if (variableName == gradsTag_lowThreshold)
//   {
//      model.setLowThreshold(value.toDouble());
//   }
//   else if (variableName == gradsTag_highThreshold)
//   {
//      model.setHighThreshold(value.toDouble());
//   }
//   else
//   {
//      return false;
//   }
//   return true;
//}

cv::Mat imageProcessingSpace::doGradient(CProcTask_Gradients *spec, cv::Mat source)
{
   cv::Mat out;
   if (0 == spec || !spec->isValid())
   {
      return out;
   }

   int dep = source.depth();
   int ddepth = -1;
   switch (dep)
   {
   case(CV_8U) :
      ddepth = CV_32F;
      break;
   case(CV_16U) :
   case(CV_16S) :
      ddepth = CV_32F;
      break;
   case(CV_32F) :
      ddepth = CV_64F;
      break;
   case(CV_64F) :
      ddepth = CV_64F;
      break;
   default:
      break;
   }

   if (spec->type() == GRADIENT_TYPE_SOBEL || spec->type() == GRADIENT_TYPE_SCHARR)
   {
      if (spec->type() == GRADIENT_TYPE_SOBEL)
      {
         cv::Mat sobelx;
         cv::Mat draw;
         cv::Mat gray;
         if (source.channels() > 1)
         {
            try
            {
               cvtColor(source, gray, CV_RGB2GRAY);
            }
            catch (cv::Exception e)
            {
               qCritical() << "Failed at cvCvtColor : " << e.msg.c_str();
               return out;
            }
         }
         else
         {
            gray = source;
         }

         try
         {
            Sobel(gray, sobelx, ddepth, spec->order_x(), spec->order_y(), spec->apertureSize());
            double minVal, maxVal;
            minMaxLoc(sobelx, &minVal, &maxVal); //find minimum and maximum intensities
            sobelx.convertTo(draw, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
         }
         catch (cv::Exception e)
         {
            qDebug() << "imageProcessingSpace::doGradient - cvSobel Exception : " << e.msg.c_str();
            return out;
         }
         return draw;
      }
      else
      {
         cv::Mat sobelx;
         cv::Mat draw;
         cv::Mat gray;
         if (source.channels() > 1)
         {
            try
            {
               cvtColor(source, gray, CV_RGB2GRAY);
            }
            catch (cv::Exception e)
            {
               qCritical() << "Failed at cvCvtColor : " << e.msg.c_str();
               return out;
            }
         }
         else
         {
            gray = source;
         }
         try
         {
            Sobel(gray, sobelx, ddepth, spec->order_x(), spec->order_y(), CV_SCHARR);
            double minVal, maxVal;
            minMaxLoc(sobelx, &minVal, &maxVal); //find minimum and maximum intensities
            sobelx.convertTo(draw, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
         }
         catch (cv::Exception e)
         {
            qDebug() << "imageProcessingSpace::doGradient - cvSobel Exception : " << e.msg.c_str();
            return out;
         }
         return draw;
      }
   }
   else if (spec->type() == GRADIENT_TYPE_LAPLACE)
   {
      cv::Mat gray, dst, abs_dst;
      if (source.channels() > 1)
      {
         try
         {
            cvtColor(source, gray, CV_RGB2GRAY);
         }
         catch (cv::Exception e)
         {
            qCritical() << "Failed at cvCvtColor : " << e.msg.c_str();
            return out;
         }
      }
      else
      {
         gray = source;
      }
      try
      {
         Laplacian(gray, dst, ddepth, spec->apertureSize(), spec->order_x(), spec->order_y(), cv::BORDER_DEFAULT);
         convertScaleAbs(dst, abs_dst);
      }
      catch (cv::Exception e)
      {
         qDebug() << "imageProcessingSpace::doGradient - cvLaplace Exception : " << e.msg.c_str();
      }
      return abs_dst;
   }
   else if (spec->type() == GRADIENT_TYPE_CANNY)
   {
      cv::Mat gray;
      if (source.channels() > 1)
      {
         try
         {
            cvtColor(source, gray, CV_RGB2GRAY);
         }
         catch (cv::Exception e)
         {
            qCritical() << "Failed at cvCvtColor : " << e.msg.c_str();
            return out;
         }
      }
      else
      {
         gray = source;
      }
      out = cv::Mat(gray.size(), source.depth(), 1);
      try
      {
         Canny(gray, out, spec->lowThreshold(), spec->highThreshold(), spec->apertureSize());
      }
      catch (cv::Exception e)
      {
         qDebug() << "imageProcessingSpace::doGradient - cvCanny Exception : " << e.msg.c_str();
      }
      return out;
   }
   else
   {
      return out;
   }
}
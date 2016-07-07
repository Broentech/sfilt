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
//  \file      kernels.cpp
//
//  \brief     Class containing kernels for image processing
//
//  \author    Stian Broen
//
//  \date      01.01.2014
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
#include <QtDebug>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>

// local includes
#include "kernels.h"

using namespace imageProcessingSpace;

CProcTask_Kernels::CProcTask_Kernels()
:m_type(KERNEL_UNKNOWN),
m_valueType(QVariant::Invalid)
{

}

CProcTask_Kernels::CProcTask_Kernels(KernelType type, QVariant::Type valueType, QList< kernelvalue > kernel)
:m_type(type),
m_valueType(valueType),
m_kernel(kernel)
{

}

CProcTask_Kernels::~CProcTask_Kernels()
{

}

CProcTask_Kernels::CProcTask_Kernels(const CProcTask_Kernels &other)
:m_type(other.type()),
m_valueType(other.valueType()),
m_kernel(other.kernel())
{

}

CProcTask_Kernels::CProcTask_Kernels(const QString &json)
{
   *this = CProcTask_Kernels_from_JSON(json);
}

CProcTask_Kernels& CProcTask_Kernels::operator=(const CProcTask_Kernels &other)
{
   setType(other.type());
   setValueType(other.valueType());
   setKernel(other.kernel());
   return *this;
}

bool CProcTask_Kernels::operator==(const CProcTask_Kernels &other) const
{
   QList< kernelvalue > otherKernel = other.kernel();
   int kernelSize = m_kernel.size();
   if (m_type != other.type() ||
      m_valueType != other.valueType() ||
      kernelSize != otherKernel.size())
   {
      return false;
   }

   int foundCount = 0;
   for(int i=0; i<kernelSize; i++)
   {
      kernelvalue myval = m_kernel.at(i);
      for(int j=0; j<kernelSize; j++)
      {
         kernelvalue otherval = otherKernel.at(j);
         if (first(otherval) == first(myval) &&
            second(otherval) == second(myval) &&
            third(otherval) == third(myval))
         {
            foundCount++;
         }
      }
   }
   if (foundCount != kernelSize)
   {
      return false;
   }
   return true;
}

bool CProcTask_Kernels::operator!=(const CProcTask_Kernels &other) const
{
   return !(*this==other);
}

void CProcTask_Kernels::clear()
{
   m_type = KERNEL_UNKNOWN;
   m_valueType = QVariant::Invalid;
   m_kernel.clear();
}

bool CProcTask_Kernels::isValid() const
{
   return(m_type != KERNEL_UNKNOWN &&
      m_valueType != QMetaType::UnknownType &&
      m_kernel.size() >= 2);
}

QString CProcTask_Kernels::id() const
{
   return imgProcTaskToString(IMGPROC_CONVOLVE);
}

QString CProcTask_Kernels::json() const
{
   return CProcTask_Kernels_to_JSON(*this);
}

QJsonObject imageProcessingSpace::CProcTask_Kernels_to_JSONOBJECT(const CProcTask_Kernels &prc)
{
   QJsonObject obj;
   obj[kernelTag_type] = kernelTypeToString(prc.type());
   obj[kernelTag_valueType] = variantTypeToString(prc.valueType());
   QJsonArray jarray;
   QList< kernelvalue > kernel = prc.kernel();
   for (int i = 0; i < kernel.size(); i++)
   {
      kernelvalue tup = kernel.at(i);
      QJsonObject tupobj;
      tupobj[kernelTag_coordX] = first(tup);
      tupobj[kernelTag_coordY] = second(tup);
      tupobj[kernelTag_value] = third(tup).toDouble();
      jarray << tupobj;
   }
   obj[kernelTag_kernel] = jarray;
   return obj;
}

QString imageProcessingSpace::CProcTask_Kernels_to_JSON(const CProcTask_Kernels &prc)
{
   return QJsonDocument(CProcTask_Kernels_to_JSONOBJECT(prc)).toJson();
}

CProcTask_Kernels imageProcessingSpace::CProcTask_Kernels_from_JSON(const QString &json)
{
   QJsonDocument doc = QJsonDocument::fromJson(json.toLatin1());
   if (doc.isNull())
   {
      return CProcTask_Kernels();
   }
   QJsonObject obj = doc.object();
   return CProcTask_Kernels_from_JSONOBJECT(obj);
}

CProcTask_Kernels imageProcessingSpace::CProcTask_Kernels_from_JSONOBJECT(const QJsonObject &obj)
{
   CProcTask_Kernels prc;
   if (obj.isEmpty() ||
      obj[kernelTag_type].type() != QJsonValue::String ||
      obj[kernelTag_valueType].type() != QJsonValue::String ||
      obj[kernelTag_kernel].type() != QJsonValue::Array
      )
   {
      return prc;
   }
   prc.setType(kernelTypeFromString(obj[kernelTag_type].toString()));
   prc.setValueType(variantTypeFromString(obj[kernelTag_valueType].toString()));
   QJsonArray jarray = obj[kernelTag_kernel].toArray();
   QList< kernelvalue > kernel;
   for (int i = 0; i < jarray.size(); i++)
   {
      QJsonObject kernat = jarray.at(i).toObject();
      if (kernat.isEmpty() ||
         kernat[kernelTag_coordX].type() != QJsonValue::Double ||
         kernat[kernelTag_coordY].type() != QJsonValue::Double ||
         kernat[kernelTag_value].type() != QJsonValue::Double)
      {
         continue;
      }
      kernelvalue tup;
      setFirst(tup, kernat[kernelTag_coordX].toInt());
      setSecond(tup, kernat[kernelTag_coordY].toInt());
      setThird(tup, QVariant(kernat[kernelTag_value].toDouble()));
      kernel << tup;
   }
   prc.setKernel(kernel);
   return prc;
}

//CProcTask_Kernels imageProcessingSpace::kernelModelFromSummary(const QString &summary)
//{
//   CProcTask_Kernels ret;
//   QStringList splt = summary.split(',');
//   for(int i=0; i<splt.size(); i++)
//   {
//      const QString spltAt = splt.at(i);
//      if (!spltAt.contains(':'))
//      {
//         continue;
//      }
//      const QString var = spltAt.split(':').at(0);
//      const QString val = spltAt.split(':').at(1);
//      if (!setKernelModelEntry(ret, var, val))
//      {
//         qWarning() << "Invalid parameter for class CProcTask_Kernels : " << var << " = " << val;
//      }
//   }
//   return ret;
//}
//
//QString imageProcessingSpace::kernelModelToSummary(const CProcTask_Kernels &model)
//{
//   QString ret;
//   QList< kernelvalue > kernel = model.kernel();
//   ret.append(kernelTag_type      + ':' + kernelTypeToString (model.type     ()) + ',' +
//              kernelTag_valueType + ':' + variantTypeToString(model.valueType()) + ',' );
//   for(int i=0; i<kernel.size(); i++)
//   {
//      kernelvalue tup = kernel.at(i);
//      ret.append(kernelTag_entry  + ':' + 
//                 kernelTag_coordX + '=' + QString::number(first(tup)) + '*' +
//                 kernelTag_coordY + '=' + QString::number(second(tup)) + '*' +
//                 kernelTag_value  + '=' +                 third(tup).toString() + ',');
//   }
//   return ret;
//}
//
//bool imageProcessingSpace::setKernelModelEntry(CProcTask_Kernels &model, const QString &variableName, const QString &value)
//{
//   if (variableName == kernelTag_type)
//   {
//      model.setType(kernelTypeFromString(value));
//   }
//   else if (variableName == kernelTag_valueType)
//   {
//      model.setValueType(variantTypeFromString(value));
//   }
//   else if(variableName == kernelTag_entry)
//   {
//      kernelvalue tup;
//      QStringList splt = value.split('*');
//      for(int i=0; i<splt.size(); i++)
//      {
//         QString spltAt = splt.at(i);
//         if (!spltAt.contains('='))
//         {
//            continue;
//         }
//         QString var = spltAt.split('=').at(0);
//         QString val = spltAt.split('=').at(1);
//         if (var == kernelTag_coordX)
//         {
//            setFirst(tup, val.toInt());
//         }
//         else if (var == kernelTag_coordY)
//         {
//            setSecond(tup, val.toInt());
//         }
//         else if (var == kernelTag_value)
//         {
//            setThird(tup, composeVariantFromString(model.valueType(), val));
//         }
//      }
//      model.addKernelValue(tup);
//   }
//   else
//   {
//      return false;
//   }
//   return true;
//}

cv::Mat imageProcessingSpace::doConvolution(CProcTask_Kernels *spec, cv::Mat _source)
{
   cv::Mat matOut;
   if (0 == spec || !spec->isValid())
   {
      return matOut;
   }
   cv::Mat matSource = _source;
   matOut.create(matSource.size(), matSource.type());
   QList< kernelvalue > specKernel = spec->kernel();
   if(spec->valueType() == QVariant::Double)
   {
      cv::Mat kernel(spec->type(), spec->type(), CV_32F, cv::Scalar(0));
      for(int i=0; i<specKernel.size(); i++)
      {
         kernelvalue tup = specKernel.at(i);
         int x = first(tup);
         int y = second(tup);
         if (!(x < spec->type() || y < spec->type()))
         {
            continue;
         }
         QVariant variant = third(tup);
         bool ok;
         double dval = variant.toDouble(&ok);
         if (!ok)
         {
            continue;
         }
         float fval = static_cast<double>(dval);
         try
         {
            kernel.at<float>(x, y) = fval;
         }
         catch(cv::Exception e)
         {
            qCritical() << "Failed at at<float> : " << e.msg.c_str();
            return matOut;
         }
      }
      try
      {
         cv::filter2D(matSource, matOut, matSource.depth(), kernel);
      }
      catch (cv::Exception e)
      {
         qCritical() << "Failed at filter2D : " << e.msg.c_str();
         return matOut;
      }
   }
   /*else if(spec->valueType() == QVariant::Int)
   {
      cv::Mat kernel(spec->type(), spec->type(), CV_16SC2, cv::Scalar(0));
      for(int i=0; i<specKernel.size(); i++)
      {
         kernelvalue tup = specKernel.at(i);
         int x = first(tup);
         int y = second(tup);
         if (!(x < spec->type() || y < spec->type()))
         {
            continue;
         }
         QVariant variant = third(tup);
         bool ok;
         int ival = variant.toInt(&ok);
         if (!ok)
         {
            continue;
         }
         try
         {
            kernel.at<int>(x, y) = ival;
         }
         catch(cv::Exception e)
         {
            qCritical() << "Failed at at<int> : " << e.msg.c_str();
            return matOut;
         }
         try
         {
            cv::filter2D(matSource, matOut, matSource.depth(), kernel);
         }
         catch(cv::Exception e)
         {
            qCritical() << "Failed at filter2D : " << e.msg.c_str();
            return matOut;
         }
      }
   }*/
   else
   {
      return matOut;
   }

   return matOut;
}

int imageProcessingSpace::first(const kernelvalue &val)
{
   return val.first.first;
}

int imageProcessingSpace::second(const kernelvalue &val)
{
   return val.first.second;
}

QVariant imageProcessingSpace::third(const kernelvalue &val)
{
   return val.second;
}

kernelvalue& imageProcessingSpace::setFirst(kernelvalue &val, int _first)
{
   val.first.first = _first;
   return val;
}

kernelvalue& imageProcessingSpace::setSecond(kernelvalue &val, int _second)
{
   val.first.second = _second;
   return val;
}

kernelvalue& imageProcessingSpace::setThird(kernelvalue &val, const QVariant &_third)
{
   val.second = _third;
   return val;
}

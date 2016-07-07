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
//  \file      morph.cpp
//
//  \brief     Class containing morphology processing parameters for image processing
//
//  \author    Stian Broen
//
//  \date      01.10.2013
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
#include "morph.h"

using namespace imageProcessingSpace;
Q_DECLARE_METATYPE(MorphType)
Q_DECLARE_METATYPE(MorphKernelShape)

CProcTask_Morph::CProcTask_Morph()
:m_type(UNKNOWN_MORPH),
m_kernelType(SHAPE_UNKNOWN),
m_kernelCols(0),
m_kernelRows(0),
m_kernelAnchor_X(0),
m_kernelAnchor_Y(0),
m_iterations(0)
{

}

CProcTask_Morph::CProcTask_Morph(
   MorphType type,
   MorphKernelShape kernelType,
   int kernelCols,
   int kernelRows,
   int anchor_x,
   int anchor_y,
   int iterations)
:m_type(type),
m_kernelType(kernelType),
m_kernelCols(kernelCols),
m_kernelRows(kernelRows),
m_kernelAnchor_X(anchor_x),
m_kernelAnchor_Y(anchor_y),
m_iterations(iterations)
{

}

CProcTask_Morph::~CProcTask_Morph()
{

}

CProcTask_Morph::CProcTask_Morph(const CProcTask_Morph &other)
:m_type(other.type()),
m_kernelType(other.kernelType()),
m_kernelCols(other.columns()),
m_kernelRows(other.rows()),
m_kernelAnchor_X(other.anchor_x()),
m_kernelAnchor_Y(other.anchor_y()),
m_iterations(other.iterations())
{

}

CProcTask_Morph::CProcTask_Morph(const QString &json)
{
   *this = CProcTask_Morph_from_JSON(json);
}

CProcTask_Morph& CProcTask_Morph::operator=(const CProcTask_Morph &other)
{
   m_type = other.type();
   m_kernelType = other.kernelType();
   m_kernelCols = other.columns();
   m_kernelRows = other.rows();
   m_kernelAnchor_X = other.anchor_x();
   m_kernelAnchor_Y = other.anchor_y();
   m_iterations = other.iterations();
   return *this;
}

bool CProcTask_Morph::operator==(const CProcTask_Morph &other) const
{
   return(m_type == other.type() &&
      m_kernelType == other.kernelType() &&
      m_kernelCols == other.columns() &&
      m_kernelRows == other.rows() &&
      m_kernelAnchor_X == other.anchor_x() &&
      m_kernelAnchor_Y == other.anchor_y() &&
      m_iterations == other.iterations());
}

bool CProcTask_Morph::operator!=(const CProcTask_Morph &other) const
{
   return !(*this==other);
}

void CProcTask_Morph::clear()
{
   m_type = UNKNOWN_MORPH;
   m_kernelType = SHAPE_UNKNOWN;
   m_kernelCols = 0;
   m_kernelRows = 0;
   m_kernelAnchor_X = 0;
   m_kernelAnchor_Y = 0;
   m_iterations = 0;
}

bool CProcTask_Morph::isValid() const
{
   if (m_type == UNKNOWN_MORPH ||
      m_kernelType == SHAPE_UNKNOWN ||
      m_iterations <= 0)
   {
      return false;
   }
   if (m_kernelType == SHAPE_DEFAULT)
   {
      return true;
   }
   if (m_kernelCols <= 0 ||
      m_kernelRows <= 0 ||
      m_kernelAnchor_X < 0 ||
      m_kernelAnchor_Y < 0)
   {
      return false;
   }
   if (m_kernelAnchor_X >= m_kernelCols ||
      m_kernelAnchor_Y >= m_kernelRows)
   {
      return false;
   }
   return true;
}

QString CProcTask_Morph::id() const
{
   return morphTypeToString(m_type);
}

QString CProcTask_Morph::json() const
{
   return CProcTask_Morph_to_JSON(*this);
}

QJsonObject imageProcessingSpace::CProcTask_Morph_to_JSONOBJECT(const CProcTask_Morph &prc)
{
   QJsonObject obj;
   obj[morphTag_type] = morphTypeToString(prc.type());
   obj[morphTag_shape] = morphKernelShapeToString(prc.kernelType());
   obj[morphTag_cols] = prc.columns();
   obj[morphTag_rows] = prc.rows();
   obj[morphTag_anchorX] = prc.anchor_x();
   obj[morphTag_anchorY] = prc.anchor_y();
   obj[morphTag_iter] = prc.iterations();
   return obj;
}

QString imageProcessingSpace::CProcTask_Morph_to_JSON(const CProcTask_Morph &prc)
{
   return QJsonDocument(CProcTask_Morph_to_JSONOBJECT(prc)).toJson();
}

CProcTask_Morph imageProcessingSpace::CProcTask_Morph_from_JSON(const QString &json)
{
   QJsonDocument doc = QJsonDocument::fromJson(json.toLatin1());
   if (doc.isNull())
   {
      return CProcTask_Morph();
   }
   QJsonObject obj = doc.object();
   return CProcTask_Morph_from_JSONOBJECT(obj);
}

CProcTask_Morph imageProcessingSpace::CProcTask_Morph_from_JSONOBJECT(const QJsonObject &obj)
{
   CProcTask_Morph prc;
   if (obj.isEmpty() ||
      obj[morphTag_type].type() != QJsonValue::String ||
      obj[morphTag_shape].type() != QJsonValue::String ||
      obj[morphTag_cols].type() != QJsonValue::Double ||
      obj[morphTag_rows].type() != QJsonValue::Double ||
      obj[morphTag_anchorX].type() != QJsonValue::Double ||
      obj[morphTag_anchorY].type() != QJsonValue::Double ||
      obj[morphTag_iter].type() != QJsonValue::Double
      )
   {
      return prc;
   }
   prc.setType(morphTypeFromString(obj[morphTag_type].toString()));
   prc.setKernelType(morphKernelShapeFromString(obj[morphTag_shape].toString()));
   prc.setColumns(obj[morphTag_cols].toInt());
   prc.setRows(obj[morphTag_rows].toInt());
   prc.setAnchor_x(obj[morphTag_anchorX].toInt());
   prc.setAnchor_y(obj[morphTag_anchorY].toInt());
   prc.setIterations(obj[morphTag_iter].toInt());
   return prc;
}

//CProcTask_Morph imageProcessingSpace::morphModelFromSummary(const QString &summary)
//{
//   CProcTask_Morph ret;
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
//      setMorphModelEntry(ret, var, val);
//   }
//   return ret;
//}
//QString imageProcessingSpace::morphModelToSummary(const CProcTask_Morph &model)
//{
//   return morphTag_type    + ':' + morphTypeToString        (model.type       ()) + ',' +
//          morphTag_shape   + ':' + morphKernelShapeToString (model.kernelType ()) + ',' +
//          morphTag_cols    + ':' + QString::number          (model.columns    ()) + ',' +
//          morphTag_rows    + ':' + QString::number          (model.rows       ()) + ',' +
//          morphTag_anchorX + ':' + QString::number          (model.anchor_x   ()) + ',' +
//          morphTag_anchorY + ':' + QString::number          (model.anchor_y   ()) + ',' +
//          morphTag_iter    + ':' + QString::number          (model.iterations ());
//}
//bool imageProcessingSpace::setMorphModelEntry(CProcTask_Morph &model, const QString &variableName, const QString &value)
//{
//   if (variableName == morphTag_type)
//   {
//      model.setType(morphTypeFromString(value));
//   }
//   else if (variableName == morphTag_shape)
//   {
//      model.setKernelType(morphKernelShapeFromString(value));
//   }
//   else if (variableName == morphTag_cols)
//   {
//      model.setColumns(value.toInt());
//   }
//   else if (variableName == morphTag_rows)
//   {
//      model.setRows(value.toInt());
//   }
//   else if (variableName == morphTag_anchorX)
//   {
//      model.setAnchor_x(value.toInt());
//   }
//   else if (variableName == morphTag_anchorY)
//   {
//      model.setAnchor_y(value.toInt());
//   }
//   else if (variableName == morphTag_iter)
//   {
//      model.setIterations(value.toInt());
//   }
//   else
//   {
//      return false;
//   }
//   return true;
//}

cv::Mat imageProcessingSpace::doMorphology(CProcTask_Morph *spec, cv::Mat source)
{
   if (0 == spec || !spec->isValid())
   {
      return cv::Mat();
   }

   switch(spec->type())
   {
   case(MORPH_ERODE):
      return doErode(spec, source);
   case(MORPH_DILATE):
      return doDilate(spec, source);
   case(MORPH_OPEN):
   case(MORPH_CLOSE):
   case(MORPH_GRADIENT):
   case(MORPH_TOPHAT):
   case(MORPH_BLACKHAT):
      return doGeneralMorph(spec, source);
   case(UNKNOWN_MORPH):
   default:
      return cv::Mat();
   }
}

cv::Mat imageProcessingSpace::doErode(CProcTask_Morph *spec, cv::Mat source)
{
   cv::Mat out(source.size(), source.depth(), source.channels());
   if (0 == spec || 0 == source.data || !spec->isValid())
   {
      return out;
   }
   try
   {
      erode(source, out, cv::Mat(), cv::Point(-1,-1), spec->iterations());
   }
   catch(cv::Exception e)
   {
      qDebug() << "imageProcessingSpace::doErode - cvErode Exception : " << e.msg.c_str();
   }
   return out;
}

cv::Mat imageProcessingSpace::doDilate(CProcTask_Morph *spec, cv::Mat source)
{
   cv::Mat out(source.size(), source.depth(), source.channels());
   if (0 == spec || 0 == source.data || !spec->isValid())
   {
      return out;
   }

   try
   {
      dilate(source, out, cv::Mat(), cv::Point(-1, -1), spec->iterations());
   }
   catch(cv::Exception e)
   {
      qDebug() << "imageProcessingSpace::doDilate - cvDilate Exception : " << e.msg.c_str();
   }
   return out;
}

cv::Mat imageProcessingSpace::doGeneralMorph(CProcTask_Morph *spec, cv::Mat source)
{
   cv::Mat out(source.size(), source.depth(), source.channels());
   if (0 == spec || 0 == source.data || !spec->isValid())
   {
      return out;
   }
   try
   {
      morphologyEx(source, out, spec->type(), cv::Mat(), cv::Point(-1,-1), spec->iterations());
   }
   catch(cv::Exception e)
   {
      qDebug() << "imageProcessingSpace::doGeneralMorph - cvMorphologyEx Exception : " << e.msg.c_str();
   }
   return out;
}
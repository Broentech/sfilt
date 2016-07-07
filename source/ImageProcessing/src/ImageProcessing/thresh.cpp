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
//  \file      thresh.cpp
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

// Qt includes
#include <QStringList>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>

// local includes
#include "thresh.h"

using namespace imageProcessingSpace;
Q_DECLARE_METATYPE(ThresholdMethod)
Q_DECLARE_METATYPE(ThresholdType)
Q_DECLARE_METATYPE(ThresholdAdaptiveMethod)
Q_DECLARE_METATYPE(ThresholdChannel)

CProcTask_Thresh::CProcTask_Thresh()
:m_channel(THRESH_CHANNEL_UNKNOWN),
m_method(THRESH_METHOD_UNKNOWN),
m_type(THRESH_UNKNOWN),
m_adaptiveMethod(THRESH_ADMETH_UNKNOWN),
m_thresholdValue(0.0),
m_maxValue(0.0),
m_C(0.0),
m_blockSize(0)
{

}

CProcTask_Thresh::CProcTask_Thresh(ThresholdChannel chan,
   ThresholdMethod method,
   ThresholdType type,
   ThresholdAdaptiveMethod admeth,
   double value,
   double max,
   double c,
   int blocksize)
:m_channel(chan),
m_method(method),
m_type(type),
m_adaptiveMethod(admeth),
m_thresholdValue(value),
m_maxValue(max),
m_C(c),
m_blockSize(blocksize)
{

}

CProcTask_Thresh::~CProcTask_Thresh()
{

}

CProcTask_Thresh::CProcTask_Thresh(const CProcTask_Thresh &other)
:m_channel(other.channel()),
m_method(other.method()),
m_type(other.type()),
m_adaptiveMethod(other.adaptiveMethod()),
m_thresholdValue(other.thresholdValue()),
m_maxValue(other.maxValue()),
m_C(other.ad_c()),
m_blockSize(other.blockSize()),
m_childrenChannels(other.children())
{

}

CProcTask_Thresh::CProcTask_Thresh(const QString &json)
{
   *this = CProcTask_Thresh_from_JSON(json);
}

CProcTask_Thresh& CProcTask_Thresh::operator=(const CProcTask_Thresh &other)
{
   m_channel = other.channel();
   m_method = other.method();
   m_type = other.type();
   m_adaptiveMethod = other.adaptiveMethod() ;
   m_thresholdValue = other.thresholdValue() ;
   m_maxValue = other.maxValue();
   m_C = other.ad_c();
   m_blockSize = other.blockSize();
   m_childrenChannels = other.children();
   return *this;
}

bool CProcTask_Thresh::operator==(const CProcTask_Thresh &other) const
{
   if (m_channel != other.channel() ||
      m_method != other.method() ||
      m_type != other.type() ||
      m_adaptiveMethod != other.adaptiveMethod() ||
      m_thresholdValue != other.thresholdValue() ||
      m_maxValue != other.maxValue() ||
      m_C != other.ad_c() ||
      m_blockSize != other.blockSize() ||
      m_childrenChannels.size() != other.children().size())
   {
      return false;
   }
   if (m_childrenChannels.size() == 0)
   {
      return true;
   }
   QMap<ThresholdChannel, QString> otherChildren(other.children());
   QMapIterator<ThresholdChannel, QString> i(m_childrenChannels);
   while(i.hasNext())
   {
      i.next();
      if (!otherChildren.contains(i.key()))
      {
         return false;
      }
      if (otherChildren.value(i.key()) != i.value())
      {
         return false;
      }
   }
   return true;
}

bool CProcTask_Thresh::operator!=(const CProcTask_Thresh &other) const
{
   return !(*this==other);
}

void CProcTask_Thresh::clear()
{
   m_channel = THRESH_CHANNEL_UNKNOWN;
   m_method = THRESH_METHOD_UNKNOWN;
   m_type = THRESH_UNKNOWN;
   m_adaptiveMethod = THRESH_ADMETH_UNKNOWN;
   m_thresholdValue = 0.0;
   m_maxValue = 0.0;
   m_C = 0.0 ;
   m_blockSize = 0;
   m_childrenChannels.clear();
}

bool CProcTask_Thresh::isValid() const
{
   if (m_channel != THRESH_CHANNEL_RGB &&
      (m_channel == UNKNOWN_GRAYSCALE ||
      m_method == THRESH_METHOD_UNKNOWN ||
      m_type == THRESH_UNKNOWN))
   {
      return false;
   }
   if(m_channel == THRESH_CHANNEL_RGB)
   {
      if (m_childrenChannels.size() != 3)
      {
         return false;
      }
      QMapIterator<ThresholdChannel, QString> i(m_childrenChannels);
      while(i.hasNext())
      {
         i.next();
         if (!CProcTask_Thresh_from_JSON(i.value()).isValid())
         {
            return false;
         }
      }
   }
   if (m_method == THRESH_METHOD_REGULAR &&
      m_thresholdValue > m_maxValue)
   {
      return false;
   }
   if(m_method == THRESH_METHOD_ADAPTIVE)
   {
      if (m_type != THRESH_BINARY &&
         m_type != THRESH_BINARY_INV)
      {
         return false;
      }
      if (m_blockSize <= 2)
      {
         return false;
      }
   }
   return true;
}

QString CProcTask_Thresh::id() const
{
   return thresholdTypeToString(m_type);
}

QString CProcTask_Thresh::json() const
{
   return CProcTask_Thresh_to_JSON(*this);
}

ThresholdChannel CProcTask_Thresh::channel() const 
{ 
   return m_channel; 
}

ThresholdMethod CProcTask_Thresh::method() const 
{ 
   return m_method; 
}

ThresholdType CProcTask_Thresh::type() const 
{ 
   return m_type; 
}

ThresholdAdaptiveMethod CProcTask_Thresh::adaptiveMethod() const 
{ 
   return m_adaptiveMethod; 
}

double CProcTask_Thresh::thresholdValue() const 
{ 
   return m_thresholdValue; 
}

double CProcTask_Thresh::maxValue() const 
{ 
   return m_maxValue; 
}

double CProcTask_Thresh::ad_c() const 
{ 
   return m_C; 
}

int CProcTask_Thresh::blockSize() const 
{ 
   return m_blockSize; 
}

QMap<ThresholdChannel, QString> CProcTask_Thresh::children() const 
{ 
   return m_childrenChannels; 
}

QString CProcTask_Thresh::child(ThresholdChannel channel) const
{
   if (m_childrenChannels.contains(channel))
   {
      return m_childrenChannels.value(channel);
   }
   return "";
}

void CProcTask_Thresh::setChannel(ThresholdChannel val) 
{ 
   m_channel = val; 
}

void CProcTask_Thresh::setMethod(ThresholdMethod val) 
{ 
   m_method = val; 
}

void CProcTask_Thresh::setType(ThresholdType val) 
{ 
   m_type = val; 
}

void CProcTask_Thresh::setAdaptiveMethod(ThresholdAdaptiveMethod val) 
{ 
   m_adaptiveMethod = val; 
}

void CProcTask_Thresh::setThresholdValue(double val)
{
   if (val > m_maxValue)
   {
      m_thresholdValue = m_maxValue;
   }
   else
   {
      m_thresholdValue = val;
   }
}

void CProcTask_Thresh::setMaxValue(double val)
{
   m_maxValue = val;
   if (m_thresholdValue > m_maxValue)
   {
      m_thresholdValue = m_maxValue;
   }
}

void CProcTask_Thresh::setC(double val) 
{ 
   m_C = val; 
}

void CProcTask_Thresh::setBlockSize(int val)
{
   if (val <= 0)
   {
      m_blockSize = 2;
   }
   else
   {
      m_blockSize = val;
   }
}

void CProcTask_Thresh::setChildren(QMap<ThresholdChannel, QString> children) 
{ 
   m_childrenChannels = children; 
}

void CProcTask_Thresh::setChild(ThresholdChannel channel, const QString &summary) 
{ 
   m_childrenChannels.insert(channel, summary); 
}

QJsonObject imageProcessingSpace::CProcTask_Thresh_to_JSONOBJECT(const CProcTask_Thresh &prc)
{
   QJsonObject obj;
   obj[threshTag_doSplitChannels] = thresholdChannelToString(prc.channel());
   if (prc.channel() == THRESH_CHANNEL_RGB)
   {
      QMapIterator<ThresholdChannel, QString> i(prc.children());
      QJsonArray jarray;
      while (i.hasNext())
      {
         i.next();
         CProcTask_Thresh child = CProcTask_Thresh_to_JSON(i.value());
         if (child.isValid())
         {
            jarray << CProcTask_Thresh_to_JSONOBJECT(child);
         }
      }
      if (jarray.size() > 0)
      {
         obj[threshTag_list] = jarray;
      }
   }
   else
   {
      obj[threshTag_method] = thresholdMethodToString(prc.method());
      obj[threshTag_adaptiveMethod] = thresholdAdmethToString(prc.adaptiveMethod());
      obj[threshTag_max] = prc.maxValue();
      obj[threshTag_value] = prc.thresholdValue();
      obj[threshTag_C] = prc.ad_c();
      obj[threshTag_blockSize] = prc.blockSize();
   }

   return obj;
}

QString imageProcessingSpace::CProcTask_Thresh_to_JSON(const CProcTask_Thresh &prc)
{
   return QJsonDocument(CProcTask_Thresh_to_JSONOBJECT(prc)).toJson();
}

CProcTask_Thresh imageProcessingSpace::CProcTask_Thresh_from_JSON(const QString &json)
{
   QJsonDocument doc = QJsonDocument::fromJson(json.toLatin1());
   if (doc.isNull())
   {
      return CProcTask_Thresh();
   }
   QJsonObject obj = doc.object();
   return CProcTask_Thresh_from_JSONOBJECT(obj);
}

CProcTask_Thresh imageProcessingSpace::CProcTask_Thresh_from_JSONOBJECT(const QJsonObject &obj)
{
   CProcTask_Thresh prc;
   if (obj.isEmpty() ||
      obj[threshTag_doSplitChannels].type() != QJsonValue::String)
   {
      return prc;
   }
   prc.setChannel(thresholdChannelFromString(obj[threshTag_doSplitChannels].toString()));
   if (obj.contains(threshTag_list) &&
      obj[threshTag_list].type() == QJsonValue::Array)
   {
      QMap<ThresholdChannel, QString> children;
      QJsonArray jarray = obj[threshTag_list].toArray();
      for (int i = 0; i < jarray.size(); i++)
      {
         CProcTask_Thresh child = CProcTask_Thresh_from_JSONOBJECT(jarray.at(i).toObject());
         if (child.isValid())
         {
            children.insert(child.channel(), CProcTask_Thresh_to_JSON(child));
         }
      }
      if (children.size() > 0)
      {
         prc.setChildren(children);
      }
   }

   if (obj.contains(threshTag_method))
   {
      prc.setMethod(thresholdMethodFromString(obj[threshTag_method].toString()));
   }
   if (obj.contains(threshTag_adaptiveMethod))
   {
      prc.setAdaptiveMethod(thresholdAdmethFromString(obj[threshTag_adaptiveMethod].toString()));
   }
   if (obj.contains(threshTag_max))
   {
      prc.setMaxValue(obj[threshTag_max].toDouble());
   }
   if (obj.contains(threshTag_value))
   {
      prc.setThresholdValue(obj[threshTag_value].toDouble());
   }
   if (obj.contains(threshTag_C))
   {
      prc.setC(obj[threshTag_C].toDouble());
   }
   if (obj.contains(threshTag_blockSize))
   {
      prc.setBlockSize(obj[threshTag_blockSize].toInt());
   }
   return prc;
}

//CProcTask_Thresh imageProcessingSpace::thresholdModelFromSummary(const QString &summary, int i)
//{
//   CProcTask_Thresh ret;
//   QStringList splt = summary.split(',');
//   for(; i<splt.size(); i++)
//   {
//      const QString spltAt = splt.at(i);
//      if (!spltAt.contains(':'))
//      {
//         continue;
//      }
//      const QString var = spltAt.split(':').at(0);
//      const QString val = spltAt.split(':').at(1);
//      if(ret.channel() == THRESH_CHANNEL_RGB)
//      {
//         CProcTask_Thresh child = thresholdModelFromSummary(summary, i);
//         ret.setChild(child.channel(), child.summary());
//         continue;
//      }
//      setThresholdModelEntry(ret, var, val);
//   }
//   return ret;
//}
//QString imageProcessingSpace::thresholdModelToSummary(const CProcTask_Thresh &model)
//{
//   QString ret;
//   ret.append(threshTag_doSplitChannels + ':' + thresholdChannelToString(model.channel()) + ',');
//   if(model.channel() == THRESH_CHANNEL_RGB)
//   {
//      QMapIterator<ThresholdChannel, QString> i(model.children());
//      while(i.hasNext())
//      {
//         i.next();
//         ret.append(thresholdModelToSummary(i.value()));
//      }
//      return ret;
//   }
//   ret.append(threshTag_method         + ':' + thresholdMethodToString(model.method         ()) + ',' +
//              threshTag_type           + ':' + thresholdTypeToString  (model.type           ()) + ',' +
//              threshTag_adaptiveMethod + ':' + thresholdAdmethToString(model.adaptiveMethod ()) + ',' +
//              threshTag_max            + ':' + QString::number        (model.maxValue       ()) + ',' +
//              threshTag_value          + ':' + QString::number        (model.thresholdValue ()) + ',' +
//              threshTag_C              + ':' + QString::number        (model.ad_c           ()) + ',' +
//              threshTag_blockSize      + ':' + QString::number        (model.blockSize      ()) + ';' );
//
//   return ret;
//}
//bool imageProcessingSpace::setThresholdModelEntry(CProcTask_Thresh &model, const QString &variableName, const QString &value)
//{
//   if (variableName == threshTag_doSplitChannels)
//   {
//      model.setChannel(thresholdChannelFromString(value));
//   }
//   else if (variableName == threshTag_method)
//   {
//      model.setMethod(thresholdMethodFromString(value));
//   }
//   else if (variableName == threshTag_type)
//   {
//      model.setType(thresholdTypeFromString(value));
//   }
//   else if (variableName == threshTag_adaptiveMethod)
//   {
//      model.setAdaptiveMethod(thresholdAdmethFromString(value));
//   }
//   else if (variableName == threshTag_value)
//   {
//      model.setThresholdValue(value.toDouble());
//   }
//   else if (variableName == threshTag_max)
//   {
//      model.setMaxValue(value.toDouble());
//   }
//   else if (variableName == threshTag_C)
//   {
//      model.setC(value.toDouble());
//   }
//   else if (variableName == threshTag_blockSize)
//   {
//      model.setBlockSize(value.toInt());
//   }
//   else
//   {
//      return false;
//   }
//   return true;
//}

cv::Mat imageProcessingSpace::doThresholding(CProcTask_Thresh *spec, cv::Mat source)
{
   cv::Mat out(source.size(), source.depth(), source.channels());
   if (0 == spec || 0 == source.data || !spec->isValid())
   {
      return out;
   }

   if(spec->channel() == THRESH_CHANNEL_GREY)
   {
      cv::Mat gray;
      out = cv::Mat(source.size(), source.depth(), 1);
      if (source.channels() == 1)
      {
         gray = source;
      }
      else
      {
         gray = cv::Mat(source.size(), source.depth(), 1);
         try
         {
            cvtColor(source, gray, CV_RGB2GRAY);
         }
         catch (cv::Exception e)
         {
            qDebug() << "imageProcessingSpace::doThresholding - cvThreshold Exception : " << e.msg.c_str();
         }
      }
      
      if(spec->method() == THRESH_METHOD_REGULAR)
      {
         try
         {
            threshold(gray, out, spec->thresholdValue(), spec->maxValue(), spec->type());
         }
         catch(cv::Exception e)
         {
            qDebug() << "imageProcessingSpace::doThresholding - cvThreshold Exception : " << e.msg.c_str();
         }
      }
      else if(spec->method() == THRESH_METHOD_ADAPTIVE)
      {
         try
         {
            adaptiveThreshold(gray, out, spec->maxValue(), spec->adaptiveMethod(), spec->type(), spec->blockSize(), spec->ad_c());
         }
         catch(cv::Exception e)
         {
            qDebug() << "imageProcessingSpace::doThresholding - cvAdaptiveThreshold Exception : " << e.msg.c_str();
         }
      }
      return out;
   }
   else if(spec->channel() == THRESH_CHANNEL_RGB)
   {
      return out;
   }

   return out;
}

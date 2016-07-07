//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      gray.cpp
//
//  \brief     Class containing grayscale processing parameters for image processing
//
//  \author    Stian Broen
//
//  \date      22.09.2013
//
//  \par       Copyright: BroenTech AS
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

// local includes
#include "gray.h"

using namespace imageProcessingSpace;
Q_DECLARE_METATYPE(GrayScaleType)

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CProcTask_Gray ctor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  22.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_Gray::CProcTask_Gray()
:m_type(UNKNOWN_GRAYSCALE),
m_lowThreshold(0.0),
m_highThreshold(0.0),
m_aperture(0.0)
{

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CProcTask_Gray ctor
//
//
//  \param  GrayScaleType type   -
//          double lowThreshold  -
//          double highThreshold -
//          double aperture      -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  22.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_Gray::CProcTask_Gray(GrayScaleType type, double lowThreshold, double highThreshold, double aperture)
:m_type(type),
m_lowThreshold(lowThreshold),
m_highThreshold(highThreshold),
m_aperture(aperture)
{

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CProcTask_Gray dtor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  22.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_Gray::~CProcTask_Gray()
{

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CProcTask_Gray ctor
//
//
//  \param  const CProcTask_Gray &other -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  13.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_Gray::CProcTask_Gray(const CProcTask_Gray &other)
:m_type(other.type()),
m_lowThreshold(other.lowThreshold()),
m_highThreshold(other.highThreshold()),
m_aperture(other.aperture())
{

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CProcTask_Gray ctor
//
//
//  \param  const QString &summary -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  22.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_Gray::CProcTask_Gray(const QString &summary)
{
   *this = grayModelFromSummary(summary);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	operator=
//
//
//  \param  const CProcTask_Gray &other -
//
//  \return CProcTask_Gray&
//    
//  \author Stian Broen 
//
//  \date  22.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_Gray& CProcTask_Gray::operator=(const CProcTask_Gray &other)
{
   m_type = other.type();
   m_lowThreshold = other.lowThreshold();
   m_highThreshold = other.highThreshold();
   m_aperture = other.aperture();
   return *this;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	operator==
//
//
//  \param  const CProcTask_Gray &other -
//
//  \return bool
//    
//  \author Stian Broen 
//
//  \date  22.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
bool CProcTask_Gray::operator==(const CProcTask_Gray &other) const
{
   return(m_type == other.type() &&
      m_lowThreshold == other.lowThreshold() &&
      m_highThreshold == other.highThreshold() &&
      m_aperture == other.aperture());
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	operator!=
//
//
//  \param  const CProcTask_Gray &other -
//
//  \return bool
//    
//  \author Stian Broen 
//
//  \date  13.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
bool CProcTask_Gray::operator!=(const CProcTask_Gray &other) const
{
   return !(*this==other);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	clear
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  13.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CProcTask_Gray::clear()
{
   m_type = UNKNOWN_GRAYSCALE;
   m_lowThreshold = 0.0;
   m_highThreshold = 0.0;
   m_aperture = 0.0;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	isValid
//
//
//  \param  N/A
//
//  \return bool
//    
//  \author Stian Broen 
//
//  \date  13.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
bool CProcTask_Gray::isValid() const
{
   return (m_type != UNKNOWN_GRAYSCALE);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	id
//
//
//  \param  N/A
//
//  \return QString
//    
//  \author Stian Broen 
//
//  \date  22.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
QString CProcTask_Gray::id() const
{
   return grayScaleTypeToString(m_type);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	summary
//
//
//  \param  N/A
//
//  \return QString
//    
//  \author Stian Broen 
//
//  \date  03.01.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
QString CProcTask_Gray::summary() const
{
   return grayModelToSummary(*this);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	grayModelFromSummary
//
//
//  \param  const QString &summary -
//
//  \return CProcTask_Gray
//    
//  \author Stian Broen 
//
//  \date  22.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_Gray imageProcessingSpace::grayModelFromSummary(const QString &summary)
{
   CProcTask_Gray ret;
   QStringList splt = summary.split(',');
   for(int i=0; i<splt.size(); i++)
   {
      const QString spltAt = splt.at(i);
      if (!spltAt.contains(':'))
      {
         continue;
      }
      const QString var = spltAt.split(':').at(0);
      const QString val = spltAt.split(':').at(1);
      setGrayModelEntry(ret, var, val);
   }
   return ret;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	grayModelToSummary
//
//
//  \param  const CProcTask_Gray &model -
//
//  \return QString
//    
//  \author Stian Broen 
//
//  \date  22.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
QString imageProcessingSpace::grayModelToSummary(const CProcTask_Gray &model)
{
   return grayscaleTag_type           + ':' + grayScaleTypeToString(model.type          ()) + ',' +
          grayscaleTag_lowThreshold   + ':' + QString("%1").arg    (model.lowThreshold  ()) + ',' +
          grayscaleTag_highThreshold  + ':' + QString("%1").arg    (model.highThreshold ()) + ',' +
          grayscaleTag_aperture       + ':' + QString("%1").arg    (model.aperture      ()) + ',';
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	setGrayModelEntry
//
//
//  \param  CProcTask_Gray &model     -
//          const QString &variableName -
//          const QString &value        -
//
//  \return bool
//    
//  \author Stian Broen 
//
//  \date  22.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
bool imageProcessingSpace::setGrayModelEntry(CProcTask_Gray &model, const QString &variableName, const QString &value)
{
   if (variableName == grayscaleTag_type)
   {
      model.setType(grayscaleTypeFromString(value));
   }
   else if (variableName == grayscaleTag_lowThreshold)
   {
      model.setLowThreshold(value.toDouble());
   }
   else if (variableName == grayscaleTag_highThreshold)
   {
      model.setHighThreshold(value.toDouble());
   }
   else if (variableName == grayscaleTag_aperture)
   {
      model.setAperture(value.toDouble());
   }
   else
   {
      return false;
   }
   return true;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	doGraying
//
//
//  \param  CProcTask_Gray *spec -
//          IplImage *source     -
//
//  \return IplImage*
//    
//  \author Stian Broen 
//
//  \date  22.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
cv::Mat imageProcessingSpace::doGraying(CProcTask_Gray *spec, cv::Mat source)
{
   if (0 == spec)
   {
      return cv::Mat();
   }
   switch(spec->type())
   {
   case(CONVERT_TO_GRAYSCALE):
      return convertToGrayscale(source);
   case(CONVERT_TO_BINARY):
      return doThreshold(source, spec->lowThreshold());
   case(CONVERT_TO_CANNY):
      return doCanny(source, spec->lowThreshold(), spec->highThreshold(), spec->aperture());
   case(UNKNOWN_GRAYSCALE):
   default:
      return source;
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	convertToGrayscale
//
//
//  \param  IplImage *source -
//
//  \return IplImage*
//    
//  \author Stian Broen 
//
//  \date  22.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
cv::Mat imageProcessingSpace::convertToGrayscale(cv::Mat source)
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
         return source;
      }
   }
   else
   {
      gray = source;
   }
   return gray;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	doThreshold
//
//
//  \param  IplImage *source -
//          double threshold -
//          int type         -
//
//  \return IplImage*
//    
//  \author Stian Broen 
//
//  \date  22.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
cv::Mat imageProcessingSpace::doThreshold(cv::Mat source, double thresholdval, int type)
{
   cv::Mat gray = convertToGrayscale(source);
   cv::Mat out(gray.size(), source.depth(), 1);
   try
   {
      threshold(gray, out, thresholdval, 255, type);
   }
   catch(cv::Exception e)
   {
      qDebug() << "imageProcessingSpace::doThreshold - cvThreshold Exception : " << e.msg.c_str();
   }
   return out;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	doCanny
//
//
//  \param  IplImage *source -
//          double low       -
//          double high      -
//          double aperture  -
//
//  \return IplImage*
//    
//  \author Stian Broen 
//
//  \date  22.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
cv::Mat imageProcessingSpace::doCanny(cv::Mat source, double low, double high, double aperture)
{
   cv::Mat gray = convertToGrayscale(source);
   cv::Mat out(gray.size(), source.depth(), 1);
   try
   {
      Canny(gray, out, low, high, aperture);
   }
   catch(cv::Exception e)
   {
      qDebug() << "imageProcessingSpace::doCanny - cvCanny Exception : " << e.msg.c_str();
   }
   return out;
}
//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      distanceTransform.cpp
//
//  \brief     Class containing distance transform parameters for image processing
//
//  \author    Stian Broen
//
//  \date      27.12.2013
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
#include <QtDebug>

// local includes
#include "distanceTransform.h"

using namespace imageProcessingSpace;

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CProcTask_DistTrans ctor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  27.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_DistTrans::CProcTask_DistTrans()
:m_type(DIST_UNKNOWN),
m_mask(DIST_MASK_UNKNOWN)
{

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CProcTask_DistTrans ctor
//
//
//  \param  const QPoint &center -
//          qreal m              -
//          int flags            -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  27.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_DistTrans::CProcTask_DistTrans(DistanceTransformType type, DistanceTransformMask mask)
:m_type(type),
m_mask(mask)
{

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CProcTask_DistTrans dtor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  27.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_DistTrans::~CProcTask_DistTrans()
{

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CProcTask_DistTrans ctor
//
//
//  \param  const CProcTask_DistTrans &other -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  27.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_DistTrans::CProcTask_DistTrans(const CProcTask_DistTrans &other)
:m_type(other.type()),
m_mask(other.mask())
{

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CProcTask_DistTrans ctor
//
//
//  \param  const QString &summary -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  27.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_DistTrans::CProcTask_DistTrans(const QString &summary)
{
   *this = distTransModelFromSummary(summary);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	operator=
//
//
//  \param  const CProcTask_DistTrans &other -
//
//  \return CProcTask_DistTrans&
//    
//  \author Stian Broen 
//
//  \date  27.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_DistTrans& CProcTask_DistTrans::operator=(const CProcTask_DistTrans &other)
{
   setType(other.type());
   setMask(other.mask());
   return *this;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	operator==
//
//
//  \param  const CProcTask_DistTrans &other -
//
//  \return bool
//    
//  \author Stian Broen 
//
//  \date  27.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
bool CProcTask_DistTrans::operator==(const CProcTask_DistTrans &other) const
{
   return (m_type == other.type() && m_mask == other.mask());
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	operator!=
//
//
//  \param  const CProcTask_DistTrans &other -
//
//  \return bool
//    
//  \author Stian Broen 
//
//  \date  27.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
bool CProcTask_DistTrans::operator!=(const CProcTask_DistTrans &other) const
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
//  \date  27.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CProcTask_DistTrans::clear()
{
   m_type = DIST_UNKNOWN;
   m_mask = DIST_MASK_UNKNOWN;
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
//  \date  27.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
bool CProcTask_DistTrans::isValid() const
{
   return(m_type != DIST_UNKNOWN && m_mask != DIST_MASK_UNKNOWN);
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
//  \date  27.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
QString CProcTask_DistTrans::id() const
{
   return imgProcTaskToString(IMGPROC_DISTTRANS);
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
//  \date  27.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
QString CProcTask_DistTrans::summary() const
{
   return distTransToSummary(*this);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	distTransModelFromSummary
//
//
//  \param  const QString &summary -
//
//  \return CProcTask_LogPolar
//    
//  \author Stian Broen 
//
//  \date  27.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_DistTrans imageProcessingSpace::distTransModelFromSummary(const QString &summary)
{
   CProcTask_DistTrans ret;
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
      if (!setDistTransModelEntry(ret, var, val))
      {
         qWarning() << "Invalid parameter for class CProcTask_DistTrans : " << var << " = " << val;
      }
   }
   return ret;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	distTransToSummary
//
//
//  \param  const CProcTask_DistTrans &model -
//
//  \return QString
//    
//  \author Stian Broen 
//
//  \date  27.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
QString imageProcessingSpace::distTransToSummary(const CProcTask_DistTrans &model)
{
   QString ret;
   ret.append(distTrans_type     + ':' + distTransTypeToString(model.type()) + ',' +
              distTrans_maskSize + ':' + distTransMaskToString(model.mask()) + ';' );
   return ret;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	setDistTransModelEntry
//
//
//  \param  CProcTask_DistTrans &model  -
//          const QString &variableName -
//          const QString &value        -
//
//  \return bool
//    
//  \author Stian Broen 
//
//  \date  27.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
bool imageProcessingSpace::setDistTransModelEntry(CProcTask_DistTrans &model, const QString &variableName, const QString &value)
{
   if (variableName == distTrans_type)
   {
      model.setType(distTransTypeFromString(value));
   }
   else if (variableName == distTrans_maskSize)
   {
      model.setMask(distTransMaskFromString(value));
   }
   else
   {
      return false;
   }
   return true;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	doDistanceTransform
//
//
//  \param  CProcTask_DistTrans *spec -
//          cv::Mat source          -
//
//  \return cv::Mat
//    
//  \author Stian Broen 
//
//  \date  27.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
cv::Mat imageProcessingSpace::doDistanceTransform(CProcTask_DistTrans *spec, cv::Mat source)
{
   cv::Mat out;
   if (0 == spec || !spec->isValid())
   {
      return out;
   }
   
   try
   {
      out = cv::Mat(source.size(), IPL_DEPTH_32F, source.channels());
   }
   catch(cv::Exception e)
   {
      qCritical() << "Failed at cvCreateImage : " << e.msg.c_str();
      return out;
   }

   try
   {
      distanceTransform(source, out, spec->type(), spec->mask());
   }
   catch(cv::Exception e)
   {
      qCritical() << "Failed at cvDistTransform : " << e.msg.c_str();
      return out;
   }
   return out;
}

//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      logPolar.cpp
//
//  \brief     Class containing log polar transform parameters for image processing
//
//  \author    Stian Broen
//
//  \date      20.12.2013
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
#include "logPolar.h"

using namespace imageProcessingSpace;

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CProcTask_LogPolar ctor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_LogPolar::CProcTask_LogPolar()
:m_center(-1,-1),
m_M(-1.0 ),
m_flags(-1)
{

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CProcTask_LogPolar ctor
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
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_LogPolar::CProcTask_LogPolar(const QPoint &center, qreal m, int flags)
:m_center(center),
m_M(m),
m_flags(flags)
{

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CProcTask_LogPolar dtor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_LogPolar::~CProcTask_LogPolar()
{

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CProcTask_LogPolar ctor
//
//
//  \param  const CProcTask_LogPolar &other -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_LogPolar::CProcTask_LogPolar(const CProcTask_LogPolar &other)
:m_center(other.center()),
m_M(other.m()),
m_flags(other.flags())
{

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CProcTask_LogPolar ctor
//
//
//  \param  const QString &summary -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_LogPolar::CProcTask_LogPolar(const QString &summary)
{
   *this = logPolarModelFromSummary(summary);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	operator=
//
//
//  \param  const CProcTask_LogPolar &other -
//
//  \return CProcTask_LogPolar&
//    
//  \author Stian Broen 
//
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_LogPolar& CProcTask_LogPolar::operator=(const CProcTask_LogPolar &other)
{
   setCenter(other.center());
   setM(other.m());
   setFlags(other.flags());
   return *this;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	operator==
//
//
//  \param  const CProcTask_LogPolar &other -
//
//  \return bool
//    
//  \author Stian Broen 
//
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
bool CProcTask_LogPolar::operator==(const CProcTask_LogPolar &other) const
{
   return (m_center == other.center() &&
      m_M == other.m() &&
      m_flags == other.flags());
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	operator!=
//
//
//  \param  const CProcTask_LogPolar &other -
//
//  \return bool
//    
//  \author Stian Broen 
//
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
bool CProcTask_LogPolar::operator!=(const CProcTask_LogPolar &other) const
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
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CProcTask_LogPolar::clear()
{
   m_center = QPoint(-1,-1);
   m_M = -1.0 ;
   m_flags = -1;
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
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
bool CProcTask_LogPolar::isValid() const
{
   if (m_center.y() < 0 ||
      m_center.x() < 0 ||
      m_M < 0.0 ||
      m_flags < 0)
   {
      return false;
   }
   return true;
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
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
QString CProcTask_LogPolar::id() const
{
   return imgProcTaskToString(IMGPROC_LOGPOLAR);
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
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
QString CProcTask_LogPolar::summary() const
{
   return logPolarToSummary(*this);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	logPolarModelFromSummary
//
//
//  \param  const QString &summary -
//
//  \return CProcTask_LogPolar
//    
//  \author Stian Broen 
//
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_LogPolar imageProcessingSpace::logPolarModelFromSummary(const QString &summary)
{
   CProcTask_LogPolar ret;
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
      setlogPolarModelEntry(ret, var, val);
   }
   return ret;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	logPolarToSummary
//
//
//  \param  const CProcTask_LogPolar &model -
//
//  \return QString
//    
//  \author Stian Broen 
//
//  \date  28.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
QString imageProcessingSpace::logPolarToSummary(const CProcTask_LogPolar &model)
{
   QString ret;
   ret.append(logPolar_center_X + ':' + QString::number (model.center().x()) + ',' +
              logPolar_center_Y + ':' + QString::number (model.center().y()) + ',' +
              logPolar_mval     + ':' + QString::number (model.m())          + ',' +
              logPolar_flags    + ':' + QString::number (model.flags())      + ';' );
   return ret;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	setlogPolarModelEntry
//
//
//  \param  CProcTask_HoughLines &model     -
//          const QString &variableName -
//          const QString &value        -
//
//  \return bool
//    
//  \author Stian Broen 
//
//  \date  28.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
bool imageProcessingSpace::setlogPolarModelEntry(CProcTask_LogPolar &model, const QString &variableName, const QString &value)
{
   if (variableName == logPolar_center_X)
   {
      model.setCenterX(value.toInt());
   }
   else if (variableName == logPolar_center_Y)
   {
      model.setCenterY(value.toInt());
   }
   else if (variableName == logPolar_mval)
   {
      model.setM(value.toDouble());
   }
   else if(variableName == logPolar_flags)
   {
      QString valcpy = value;
      if (valcpy.contains(';'))
      {
         valcpy.remove(";");
      }
      model.setFlags(valcpy.toInt());
   }
   else
   {
      return false;
   }
   return true;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	doLogPolar
//
//
//  \param  CProcTask_LogPolar *spec -
//          IplImage *source         -
//
//  \return bool
//    
//  \author Stian Broen 
//
//  \date  28.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
cv::Mat imageProcessingSpace::doLogPolar(CProcTask_LogPolar *spec, cv::Mat source)
{
   cv::Mat out(source.size(), source.depth(), source.channels());
   if (0 == spec || !spec->isValid())
   {
      return out;
   }

   //try
   //{
   //   cvLogPolar(source, out, cvPoint2D32f(spec->center().x(), spec->center().y()), spec->m(), spec->flags());
   //}
   //catch(cv::Exception e)
   //{
   //   qCritical() << "Failed at cvLogPolar : " << e.msg.c_str();
   //}
   return out;
}
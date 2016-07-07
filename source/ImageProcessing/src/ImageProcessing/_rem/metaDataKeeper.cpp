//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      metaDataKeeper.cpp
//
//  \brief     This is a singleton class that contains and handles metadata for image processing
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

// local includes
#include "metaDataKeeper.h"

using namespace imageProcessingSpace;
bool CMetaDataKeeper::m_instanceFlag = false;
CMetaDataKeeper* CMetaDataKeeper::m_instance = 0;

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CImgProc ctor
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
CMetaDataKeeper::CMetaDataKeeper()
:m_isMouseTracking(false),
m_showMetaPoints(false),
m_isEditMode(false),
m_isPointTracking(false),
m_metaFreeze(false)
{
   m_redDotPen.setColor(Qt::red);
   m_redDotPen.setWidth(5);

   m_redThinPen.setColor(Qt::red);
   m_redThinPen.setWidth(1);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CImgProc dtor
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
CMetaDataKeeper::~CMetaDataKeeper()
{

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	getInstance
//
//
//  \param  N/A
//
//  \return CMetaDataKeeper* -
//    
//  \author Stian Broen 
//
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CMetaDataKeeper* CMetaDataKeeper::getInstance()
{
   if(m_instanceFlag == false || 0 == m_instance)
   {
      m_instance = new CMetaDataKeeper();
      m_instanceFlag = true;
      return m_instance;
   }
   else
   {
      return m_instance;
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	setMetadata_lines
//
//
//  \param  QList<QLine> lines -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  28.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CMetaDataKeeper::setMetadata_lines(QList<QLine> lines)
{
   if (m_metaFreeze)
   {
      return;
   }
   m_metaLines = lines;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	hasMetadata
//
//
//  \param  N/A
//
//  \return bool
//    
//  \author Stian Broen 
//
//  \date  28.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
bool CMetaDataKeeper::hasMetadata() const
{
   if (m_metaLines.size() == 0 && m_metaPoints.size() == 0)
   {
      return false;
   }
   return true;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	drawMetadata
//
//
//  \param  QPainter *painter -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  28.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CMetaDataKeeper::drawMetadata(QPainter *painter)
{
   if (0 == painter)
   {
      return;
   }

   // draw lines
   if(m_metaLines.size() > 0)
   {
      painter->setPen(m_redThinPen);
      for (int i = 0; i<m_metaLines.size(); i++)
      {
         painter->drawLine(m_metaLines.at(i));
      }
   }

   // draw points
   if(m_showMetaPoints && m_metaPoints.size() > 0)
   {
      painter->setPen(m_redDotPen);
      QHashIterator<QString, QPoint> i(m_metaPoints);
      while(i.hasNext())
      {
         i.next();
         const QString text = i.key();
         const QPoint pt = i.value();
         painter->setPen(m_redDotPen);
         painter->drawPoint(pt);
         painter->setPen(m_redThinPen);
         painter->drawText(QPoint(pt.x() + 10, pt.y()), text);
      }
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	metaFreeze
//
//
//  \param  bool val -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  06.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CMetaDataKeeper::metaFreeze(bool val)
{
   m_metaFreeze = val;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	metaClear
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  06.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CMetaDataKeeper::metaClear()
{
   m_metaLines.clear();
   m_metaPoints.clear();
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	metaStore
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  06.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CMetaDataKeeper::metaStore()
{

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	metaPoints
//
//
//  \param  QHash<QString, QPoint> m_points -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CMetaDataKeeper::metaPoints(QHash<QString, QPoint> m_points)
{
   m_metaPoints = m_points;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	currPoint
//
//
//  \param  N/A
//
//  \return QPoint
//    
//  \author Stian Broen 
//
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
QPoint CMetaDataKeeper::currPoint() const
{
   return m_currPoint;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	setCurrPoint
//
//
//  \param  const QPoint &point
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CMetaDataKeeper::setCurrPoint(const QPoint &point)
{
   if(m_isPointTracking && m_trackPointName != "" && m_metaPoints.contains(m_trackPointName))
   {
      m_metaPoints.insert(m_trackPointName, point);
      emit pointTracking(m_trackPointName, point);
   }
   else
   {
      m_currPoint = point;
      emit updateCurrPoint(m_currPoint);
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	setMouseTracking
//
//
//  \param  bool val -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CMetaDataKeeper::setMouseTracking(bool val)
{
   m_isMouseTracking = val;
   emit metaSetMouseTracking(m_isMouseTracking);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	addMetaPoint
//
//
//  \param  const QString &name -
//          const QPoint &pt    -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CMetaDataKeeper::addMetaPoint(const QString &name, const QPoint &pt)
{
   if(!containsPoint(name, pt))
   {
      m_metaPoints.insert(name, pt);
      emit pointListUpdated();
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	containsPoint
//
//
//  \param  const QString &name -
//          const QPoint &pt    -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  19.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
bool CMetaDataKeeper::containsPoint(const QString &name, const QPoint &pt) const
{
   if (m_metaPoints.size() == 0 || !m_metaPoints.contains(name))
   {
      return false;
   }
   QHashIterator<QString, QPoint> i(m_metaPoints);
   while(i.hasNext())
   {
      i.next();
      const QString _name = i.key();
      if (_name != name)
      {
         continue;
      }
      const QPoint _pt = i.value();
      if (_pt == pt)
      {
         return true;
      }
   }
   return false;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	setMetaPoints
//
//
//  \param  QHash<QString, QPoint> points -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CMetaDataKeeper::setMetaPoints(QHash<QString, QPoint> points) 
{ 
   m_metaPoints = points; 
   emit pointListUpdated();
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	trackPoint
//
//
//  \param  const QPoint &pt -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CMetaDataKeeper::trackPoint(const QPoint &pt, bool &found)
{
   QMutableHashIterator<QString, QPoint> i(m_metaPoints);
   while(i.hasNext())
   {
      i.next();
      const QString name = i.key();
      const QPoint storedPt = i.value();
      QRect rect(QPoint(storedPt.x() - 5, storedPt.y() - 5) ,
                 QPoint(storedPt.x() + 5, storedPt.y() + 5));
      if(rect.contains(pt))
      {
         m_trackPointName = name;
         m_isPointTracking = true;
         found = true;
         i.setValue(pt);
         return;
      }
   }
   m_isPointTracking = false;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	endPointTracking
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
void CMetaDataKeeper::endPointTracking()
{
   m_isPointTracking = false;
   m_trackPointName = "";
}

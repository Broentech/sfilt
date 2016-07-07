//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      logPolar.h
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

#ifndef _IMGPROC_LOGPOLAR_H_
#define _IMGPROC_LOGPOLAR_H_

// Qt includes
#include <QPoint>

// local includes
#include "base.h"

namespace imageProcessingSpace {
   class CProcTask_LogPolar : public CProcTaskBase
   {
   private:
      QPoint m_center;
      qreal m_M;
      int m_flags;

   public:
      CProcTask_LogPolar();
      CProcTask_LogPolar(const QPoint &center, qreal m, int flags);
      ~CProcTask_LogPolar();
      CProcTask_LogPolar(const CProcTask_LogPolar &other);
      CProcTask_LogPolar(const QString &summary);
      CProcTask_LogPolar& operator=(const CProcTask_LogPolar &other);
      bool operator==(const CProcTask_LogPolar &other) const;
      bool operator!=(const CProcTask_LogPolar &other) const;
      void clear();
      bool isValid() const;
      QString id() const;
      QString summary() const;

      inline QPoint center() const { return m_center; }
      inline qreal m() const { return m_M; }
      inline int flags() const { return m_flags; }

      inline void setCenterX(int val){ m_center.setX(val); }
      inline void setCenterY(int val){ m_center.setY(val); }
      inline void setCenter(const QPoint &pt) { m_center = pt; }
      inline void setM(qreal val) { m_M = val; }
      inline void setFlags(int val) { m_flags = val; }

   };

   CProcTask_LogPolar logPolarModelFromSummary(const QString &summary);
   QString logPolarToSummary(const CProcTask_LogPolar &model);
   bool setlogPolarModelEntry(CProcTask_LogPolar &model, const QString &variableName, const QString &value);
   cv::Mat doLogPolar(CProcTask_LogPolar *spec, cv::Mat source);
}

#endif
//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      metaDataKeeper.h
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

#ifndef _IMGPROC_METADATA_KEEPER_H_
#define _IMGPROC_METADATA_KEEPER_H_

// Qt includes
#include <QObject>
#include <QLine>
#include <QHash>
#include <QPoint>
#include <QStringList>
#include <QPen>
#include <QPainter>

namespace imageProcessingSpace {
   class CMetaDataKeeper : public QObject
   {
      Q_OBJECT

   public:
      static CMetaDataKeeper* getInstance();
      ~CMetaDataKeeper();
      bool hasMetadata() const;
      void drawMetadata(QPainter *painter);
      void setMetadata_lines(QList<QLine> lines);
      QPoint currPoint() const;
      void setCurrPoint(const QPoint &point);
      inline QPen redThinPen() const { return m_redThinPen; }
      inline QPen redThickPen() const { return m_redDotPen; }
      bool containsPoint(const QString &name, const QPoint &pt) const;
      inline QHash<QString, QPoint> metaPoints() const { return m_metaPoints; }
      void setMetaPoints(QHash<QString, QPoint> points);
      inline void setShowMetaPoints(bool val) { m_showMetaPoints = val; }
      inline bool showMetaPoints() const { return m_showMetaPoints; }
      inline void setIsEditMode(bool val) { m_isEditMode = val; }
      inline bool isEditMode() const { return m_isEditMode; }
      void trackPoint(const QPoint &pt, bool &found);
      void endPointTracking();

   public slots:
      void metaFreeze(bool val);
      void metaClear();
      void metaStore();
      void metaPoints(QHash<QString, QPoint> m_points);
      void setMouseTracking(bool val);
      void addMetaPoint(const QString &name, const QPoint &pt);

   signals:
      void metaSetMouseTracking(bool val);
      void updateCurrPoint(const QPoint &pt);
      void pointListUpdated();
      void pointTracking(const QString &name, const QPoint &pt);

   private:
      explicit CMetaDataKeeper();
      explicit CMetaDataKeeper(const CMetaDataKeeper &rhs); //< force linker error if someone tries to use it
      const CMetaDataKeeper& operator=(const CMetaDataKeeper &rhs); //< force linker error if someone tries to use it
      
      bool m_isMouseTracking;
      bool m_showMetaPoints;
      bool m_isEditMode;
      bool m_isPointTracking;
      static bool m_instanceFlag;
      static CMetaDataKeeper* m_instance;

      QList<QLine> m_metaLines;
      QHash<QString, QPoint> m_metaPoints;
      QPoint m_currPoint;
      bool m_metaFreeze;
      QPen m_redDotPen;
      QPen m_redThinPen;
      QString m_trackPointName;
   };
}

#endif
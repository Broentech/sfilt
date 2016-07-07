//h+//////////////////////////////////////////////////////////////////////////
/*!
//  \file      metadataPoints.h
//
//  \brief     GUI to define points
//
//  \author    Stian Broen
//
//  \date      19.12.2013
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
*/
//h-//////////////////////////////////////////////////////////////////////////

#ifndef _IMGPROC_METADATA_POINTS_H_
#define _IMGPROC_METADATA_POINTS_H_

#include <QWidget>
#include <QPoint>
#include <QMultiHash>
#include <QString>

class QLabel;
class QLineEdit;
class QToolButton;
class QCheckBox;
class QListWidget;

namespace guiSpace {
   class CImgProcMetaPoints : public QWidget
   {
      Q_OBJECT

   public:
      explicit CImgProcMetaPoints(QWidget *parent = 0);
      ~CImgProcMetaPoints();

   public slots:
      void currPoint(const QPoint &pt);
      void clickPoint(bool val);

   private:
      void initGUI();

   private slots:
      void addClicked();
      void removeClicked();
      void showPointsChecked(bool checked);
      void updateList();

   signals:
      void addMetaPoint(const QString &name, const QPoint &pt);

   private:
      QCheckBox *m_doTrack;
      QCheckBox *m_doShow;
      QLineEdit *m_nameLine;
      QLabel *m_x;
      QLabel *m_y;
      QToolButton *m_addPoint;
      QToolButton *m_removePoints;
      QListWidget *m_pointList;
   };
}

#endif
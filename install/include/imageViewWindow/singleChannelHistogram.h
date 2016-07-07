//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      singleChannelHistogram.h
//
//  \brief     Window widget for displaying a single channel histogram
//
//  \author    Stian Broen
//
//  \date      01.07.2015
//
//  \par       Copyright: BroenTech Solutions AS
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

#ifndef _SINGLE_CHANNEL_HISTOGRAM_H_
#define _SINGLE_CHANNEL_HISTOGRAM_H_

// Qt includes
#include <QWidget>
#include <QMap>
#include <QString>
#include <QColor>
#include <QAction>
#include <QToolBar>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>

QT_CHARTS_USE_NAMESPACE

namespace guiSpace {
   class SingleChannelHistogram : public QWidget
   {
      Q_OBJECT

   public:
      explicit SingleChannelHistogram(QWidget *parent = 0);
      ~SingleChannelHistogram();
      inline QMap<int, float> data() const { return m_data; }
      void setData(const QMap<int, float> &data, const QString &text, const QColor &color);
      void updateData(const QMap<int, float> &data);

   signals:
      void resetTriggered();
      void applyTriggered();
      void squashTriggered();
      void dragTriggered();
      void inverseTriggered();

   private:
      void initGui();

   private:
      QMap<int, float> m_data;
      QString m_text;
      QColor m_color;
      QChartView *m_chartView;
      QAction *m_resetAction;
      QAction *m_applyAction;
      QAction *m_squashAction;
      QAction *m_dragAction;
      QAction *m_inverseAction;
      QToolBar *m_toolbar;
   };
}

#endif
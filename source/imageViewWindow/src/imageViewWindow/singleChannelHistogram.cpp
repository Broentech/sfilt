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
//  \file      singleChannelHistogram.cpp
//
//  \brief     Window widget for displaying a single channel histogram
//
//  \author    Stian Broen
//
//  \date      01.07.2015
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
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

// local includes
#include "singleChannelHistogram.h"

using namespace guiSpace;

SingleChannelHistogram::SingleChannelHistogram(QWidget *parent)
:QWidget(parent),
m_chartView(0),
m_resetAction(0),
//m_applyAction(0),
m_squashAction(0),
m_dragAction(0),
//m_inverseAction(0),
m_toolbar(0)
{
   initGui();
}

SingleChannelHistogram::~SingleChannelHistogram()
{

}

void SingleChannelHistogram::initGui()
{
   m_resetAction = new QAction(this);
   m_resetAction->setIcon(QIcon(":/images/reset.png"));
   m_resetAction->setToolTip(tr("Reset histogram"));

   connect(m_resetAction, SIGNAL(triggered()),
      this, SIGNAL(resetTriggered()));

   //m_applyAction = new QAction(this);
   //m_applyAction->setIcon(QIcon(":/images/OK.png"));
   //m_applyAction->setToolTip(tr("Apply"));

   //connect(m_applyAction, SIGNAL(triggered()),
   //   this, SIGNAL(applyTriggered()));

   m_squashAction = new QAction(this);
   m_squashAction->setIcon(QIcon(":/images/smaller.png"));
   m_squashAction->setToolTip(tr("Squeeze histogram"));

   connect(m_squashAction, SIGNAL(triggered()),
      this, SIGNAL(squashTriggered()));

   m_dragAction = new QAction(this);
   m_dragAction->setIcon(QIcon(":/images/larger.png"));
   m_dragAction->setToolTip(tr("Drag histogram"));

   connect(m_dragAction, SIGNAL(triggered()),
      this, SIGNAL(dragTriggered()));

   //m_inverseAction = new QAction(this);
   //m_inverseAction->setIcon(QIcon(":/images/sort.png"));
   //m_inverseAction->setToolTip(tr("Inverse intensities"));

   //connect(m_inverseAction, SIGNAL(triggered()),
   //   this, SIGNAL(inverseTriggered()));

   m_toolbar = new QToolBar(this);
   m_toolbar->setOrientation(Qt::Vertical);
   m_toolbar->addAction(m_squashAction);
   m_toolbar->addAction(m_dragAction);
   //m_toolbar->addAction(m_inverseAction);
   m_toolbar->addAction(m_resetAction);
   //m_toolbar->addAction(m_applyAction);

   m_chartView = new QChartView(this);
   QHBoxLayout *lay = new QHBoxLayout;
   lay->addWidget(m_chartView);
   lay->addWidget(m_toolbar);
   this->setLayout(lay);
}

void SingleChannelHistogram::setData(const QMap<int, float> &data, const QString &text, const QColor &color)
{
   if (data.size() == 0)
   {
      return;
   }
   m_data = data;
   m_text = text;
   m_color = color;
   if (m_chartView->chart() != 0)
   {
      m_chartView->chart()->removeAllSeries();
   }
   else
   {
      QChart *chart = new QChart();
      m_chartView->setChart(chart);
   }
   QChart *chart = m_chartView->chart();
   if (text != "")
   {
      chart->setTitle(text);
   }
   QLineSeries *series = new QLineSeries(chart);
   QMapIterator<int, float> i(m_data);
   while (i.hasNext())
   {
      i.next();
      series->append(QPointF(i.key(), i.value()));
   }
   QAreaSeries *area = new QAreaSeries(series);
   area->setColor(color);
   chart->addSeries(area);
   chart->createDefaultAxes();
   m_chartView->setChart(chart);
}

void SingleChannelHistogram::updateData(const QMap<int, float> &data)
{
   setData(data, m_text, m_color);
}

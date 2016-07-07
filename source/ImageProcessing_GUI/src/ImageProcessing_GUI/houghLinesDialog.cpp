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
//  \file      houghLinesDialog.h
//
//  \brief     GUI to define Hough Lines related parameters
//
//  \author    Stian Broen
//
//  \date      28.10.2013
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
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>

// local includes
#include "houghLinesDialog.h"

using namespace guiSpace;

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CHoughLinesDialog ctor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  28.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CHoughLinesDialog::CHoughLinesDialog(QWidget *parent)
:CImgProcDialogBase(parent),
m_rhoSpin(0),
m_thetaSpin(0),
m_thresholdSpin(0),
m_param1Spin(0),
m_param2Spin(0)
{
   initGUI();
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CHoughLinesDialog dtor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  28.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CHoughLinesDialog::~CHoughLinesDialog()
{

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	initGUI
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  28.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CHoughLinesDialog::initGUI()
{
   QLabel *rhoLabel = new QLabel("Rho", this);
   QLabel *thetaLabel = new QLabel("Theta", this);
   QLabel *thresholdLabel = new QLabel("Threshold / Minimum Votes", this);
   QLabel *param1Label = new QLabel("Minimum Length", this);
   QLabel *param2Label = new QLabel("Maximum Gap", this);

   m_rhoSpin = new QDoubleSpinBox(this);
   m_rhoSpin->setRange(1.0, 200.0);
   m_rhoSpin->setSingleStep(1.0);
   m_rhoSpin->setValue(1.0);

   m_thetaSpin = new QDoubleSpinBox(this);
   m_thetaSpin->setRange(0.0, 2*3.14);
   m_thetaSpin->setSingleStep(3.14 / 360.0);
   m_thetaSpin->setValue(3.14 / 180.0);
   
   m_thresholdSpin = new QSpinBox(this);
   m_thresholdSpin->setRange(1, 200);
   m_thresholdSpin->setSingleStep(1);
   m_thresholdSpin->setValue(80);
   
   m_param1Spin = new QDoubleSpinBox(this);
   m_param1Spin->setRange(0.0, 200.0);
   m_param1Spin->setSingleStep(1.0);
   m_param1Spin->setValue(100.0);

   m_param2Spin = new QDoubleSpinBox(this);
   m_param2Spin->setRange(0.0, 200.0);
   m_param2Spin->setSingleStep(1.0);
   m_param2Spin->setValue(20.0);

   QGridLayout *wlay = new QGridLayout;
   wlay->addWidget(rhoLabel, 0, 0);
   wlay->addWidget(thetaLabel, 1, 0);
   wlay->addWidget(thresholdLabel, 2, 0);
   wlay->addWidget(param1Label, 3, 0);
   wlay->addWidget(param2Label, 4, 0);

   wlay->addWidget(m_rhoSpin, 0, 1);
   wlay->addWidget(m_thetaSpin, 1, 1);
   wlay->addWidget(m_thresholdSpin, 2, 1);
   wlay->addWidget(m_param1Spin, 3, 1);
   wlay->addWidget(m_param2Spin, 4, 1);

   QVBoxLayout *lay = new QVBoxLayout;
   lay->addLayout(wlay);
   lay->addStretch();

   this->setLayout(lay);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	getData
//
//
//  \param  N/A
//
//  \return CProcTask_HoughLines*
//    
//  \author Stian Broen 
//
//  \date  28.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_HoughLines* CHoughLinesDialog::getData() const
{
   return new CProcTask_HoughLines(
      m_rhoSpin->value(),
      m_thetaSpin->value(),
      m_thresholdSpin->value(),
      m_param1Spin->value(),
      m_param2Spin->value());
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	setData
//
//
//  \param  const QString &summary -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  28.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CHoughLinesDialog::setData(const QString &summary)
{
   CProcTask_HoughLines data(summary);
   if (!data.isValid())
   {
      return;
   }

   m_rhoSpin->setValue(data.rho());
   m_thetaSpin->setValue(data.theta());
   m_thresholdSpin->setValue(data.threshold());
   m_param1Spin->setValue(data.param1());
   m_param2Spin->setValue(data.param2());
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	setEditMode
//
//
//  \param  bool val -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  28.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CHoughLinesDialog::setEditMode(bool val)
{
   m_editMode = val;
   if(m_editMode)
   {
      connect(m_rhoSpin, SIGNAL(valueChanged(double)), 
         this, SLOT(valueChanged(double)));

      connect(m_thetaSpin, SIGNAL(valueChanged(double)), 
         this, SLOT(valueChanged(double)));

      connect(m_thresholdSpin, SIGNAL(valueChanged(int)), 
         this, SLOT(valueChanged(int)));

      connect(m_param1Spin, SIGNAL(valueChanged(double)), 
         this, SLOT(valueChanged(double)));

      connect(m_param2Spin, SIGNAL(valueChanged(double)), 
         this, SLOT(valueChanged(double)));
   }
   else
   {
      disconnect(m_rhoSpin, SIGNAL(valueChanged(double)), 
         this, SLOT(valueChanged(double)));

      disconnect(m_thetaSpin, SIGNAL(valueChanged(double)), 
         this, SLOT(valueChanged(double)));

      disconnect(m_thresholdSpin, SIGNAL(valueChanged(int)), 
         this, SLOT(valueChanged(int)));

      disconnect(m_param1Spin, SIGNAL(valueChanged(double)), 
         this, SLOT(valueChanged(double)));

      disconnect(m_param2Spin, SIGNAL(valueChanged(double)), 
         this, SLOT(valueChanged(double)));
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	valueChanged
//
//
//  \param  int
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  28.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CHoughLinesDialog::valueChanged(int)
{
   if (m_editMode)
   {
      emit edited();
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	valueChanged
//
//
//  \param  double
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  28.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CHoughLinesDialog::valueChanged(double)
{
   if (m_editMode)
   {
      emit edited();
   }
}
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
//  \file      gradientDialog.h
//
//  \brief     GUI to define gradient parameters
//
//  \author    Stian Broen
//
//  \date      13.10.2013
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
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

// local includes
#include "gradientDialog.h"

using namespace guiSpace;
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CGradientDialog ctor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  13.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CGradientDialog::CGradientDialog(QWidget *parent)
:CImgProcDialogBase(parent),
m_types(0),
m_order_XSpin(0),
m_order_YSpin(0),
m_apertureSpin(0),
m_highThresholdSpin(0),
m_lowThresholdSpin(0)
{
   initGUI();
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CGradientDialog dtor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  13.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CGradientDialog::~CGradientDialog()
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
//  \date  13.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CGradientDialog::initGUI()
{
   QLabel *typeLabel = new QLabel("Gradient type", this);
   QLabel *xLabel = new QLabel("Order x", this);
   QLabel *yLabel = new QLabel("Order y", this);
   QLabel *aperLabel = new QLabel("Aperture size", this);
   QLabel *lowLabel = new QLabel("Low threshold", this);
   QLabel *highLabel = new QLabel("High threshold", this);

   m_types = new QComboBox(this);
   m_types->addItem(gradientTypeToString(GRADIENT_TYPE_SOBEL) ,QVariant(GRADIENT_TYPE_SOBEL));
   m_types->addItem(gradientTypeToString(GRADIENT_TYPE_SCHARR) ,QVariant(GRADIENT_TYPE_SCHARR));
   m_types->addItem(gradientTypeToString(GRADIENT_TYPE_LAPLACE) ,QVariant(GRADIENT_TYPE_LAPLACE));
   m_types->addItem(gradientTypeToString(GRADIENT_TYPE_CANNY) ,QVariant(GRADIENT_TYPE_CANNY));
   m_types->setCurrentIndex(m_types->findText(gradientTypeToString(GRADIENT_TYPE_SOBEL)));

   m_order_XSpin = new QSpinBox(this);
   m_order_XSpin->setRange(0, 2);
   m_order_XSpin->setValue(1);
   m_order_XSpin->setSingleStep(1);

   m_order_YSpin = new QSpinBox(this);
   m_order_YSpin->setRange(0, 2);
   m_order_YSpin->setValue(1);
   m_order_YSpin->setSingleStep(1);

   m_apertureSpin = new QSpinBox(this);
   m_apertureSpin->setRange(1, 7);
   m_apertureSpin->setValue(3);
   m_apertureSpin->setSingleStep(2);

   m_highThresholdSpin = new QDoubleSpinBox(this);
   m_highThresholdSpin->setRange(0.0 , 256.0);
   m_highThresholdSpin->setValue(100.0);
   m_highThresholdSpin->setSingleStep(1.0);

   m_lowThresholdSpin = new QDoubleSpinBox(this);
   m_lowThresholdSpin->setRange(0.0 , 256.0);
   m_lowThresholdSpin->setValue(100.0);
   m_lowThresholdSpin->setSingleStep(1.0);

   QGridLayout *lay = new QGridLayout;
   lay->addWidget(typeLabel, 0, 0);
   lay->addWidget(xLabel, 1, 0);
   lay->addWidget(yLabel, 2, 0);
   lay->addWidget(aperLabel, 3, 0);
   lay->addWidget(lowLabel, 4, 0);
   lay->addWidget(highLabel, 5, 0);
   lay->addWidget(m_types, 0, 1);
   lay->addWidget(m_order_XSpin, 1, 1);
   lay->addWidget(m_order_YSpin, 2, 1);
   lay->addWidget(m_apertureSpin, 3, 1);
   lay->addWidget(m_highThresholdSpin, 4, 1);
   lay->addWidget(m_lowThresholdSpin, 5, 1);

   QVBoxLayout *str = new QVBoxLayout;
   str->addLayout(lay);
   str->addStretch();

   this->setLayout(str);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	getData
//
//
//  \param  N/A
//
//  \return CProcTask_Gradients
//    
//  \author Stian Broen 
//
//  \date  13.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_Gradients* CGradientDialog::getData() const
{
   return new CProcTask_Gradients(
      static_cast<GradientType>(m_types->itemData(m_types->currentIndex()).toInt()),
      m_order_XSpin->value(),
      m_order_YSpin->value(),
      m_apertureSpin->value(),
      m_lowThresholdSpin->value(),
      m_highThresholdSpin->value());
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
//  \date  13.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CGradientDialog::setData(const QString &summary)
{
   CProcTask_Gradients data(summary);
   if (!data.isValid())
   {
      return;
   }

   m_types->setCurrentIndex(m_types->findData(data.type()));
   m_order_XSpin->setValue(data.order_x());
   m_order_YSpin->setValue(data.order_y());
   m_apertureSpin->setValue(data.apertureSize());
   m_highThresholdSpin->setValue(data.highThreshold());
   m_lowThresholdSpin->setValue(data.lowThreshold());
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
//  \date  13.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CGradientDialog::setEditMode(bool val)
{
   m_editMode = val;
   if(m_editMode)
   {
      connect(m_types, SIGNAL(currentIndexChanged(int)), 
         this, SLOT(valueChanged(int)));

      connect(m_order_XSpin, SIGNAL(valueChanged(int)), 
         this, SLOT(valueChanged(int)));

      connect(m_order_YSpin, SIGNAL(valueChanged(int)), 
         this, SLOT(valueChanged(int)));

      connect(m_apertureSpin, SIGNAL(valueChanged(int)), 
         this, SLOT(valueChanged(int)));

      connect(m_highThresholdSpin, SIGNAL(valueChanged(double)), 
         this, SLOT(valueChanged(double)));

      connect(m_lowThresholdSpin, SIGNAL(valueChanged(double)), 
         this, SLOT(valueChanged(double)));
   }
   else
   {
      disconnect(m_types, SIGNAL(currentIndexChanged(int)), 
         this, SLOT(valueChanged(int)));

      disconnect(m_order_XSpin, SIGNAL(valueChanged(int)), 
         this, SLOT(valueChanged(int)));

      disconnect(m_order_YSpin, SIGNAL(valueChanged(int)), 
         this, SLOT(valueChanged(int)));

      disconnect(m_apertureSpin, SIGNAL(valueChanged(int)), 
         this, SLOT(valueChanged(int)));

      disconnect(m_highThresholdSpin, SIGNAL(valueChanged(double)), 
         this, SLOT(valueChanged(double)));

      disconnect(m_lowThresholdSpin, SIGNAL(valueChanged(double)), 
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
//  \date  13.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CGradientDialog::valueChanged(int)
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
//  \date  13.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CGradientDialog::valueChanged(double)
{
   if (m_editMode)
   {
      emit edited();
   }
}

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
//  \file      smoothDialog.cpp
//
//  \brief     GUI to define smoothing parameters
//
//  \author    Stian Broen
//
//  \date      13.09.2013
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
#include <QtCore/qmath.h>

// local includes
#include "smoothDialog.h"

using namespace guiSpace;
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CSmoothDialog ctor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  13.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CSmoothDialog::CSmoothDialog(QWidget *parent)
:CImgProcDialogBase(parent),
m_types(0),
m_size1(0),
m_size2(0),
m_sigma1(0),
m_sigma2(0)
{
   initGUI();
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CSmoothDialog dtor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  13.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CSmoothDialog::~CSmoothDialog()
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
//  \date  13.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CSmoothDialog::initGUI()
{
   QLabel *typeLabel = new QLabel("Processing type", this);
   QLabel *size1Label = new QLabel("Mask size X", this);
   QLabel *size2Label = new QLabel("Mask size Y", this);
   QLabel *sigma1Label = new QLabel("Sigma 1", this);
   QLabel *sigma2Label = new QLabel("Sigma 2", this);

   m_types = new QComboBox(this);
   //m_types->addItem(smoothTag_BLUR_NO_SCALE, QVariant(BLUR_NO_SCALE));
   m_types->addItem(smoothTag_BLUR, QVariant(BLUR));
   m_types->addItem(smoothTag_GAUSSIAN, QVariant(GAUSSIAN));
   m_types->addItem(smoothTag_MEDIAN, QVariant(MEDIAN));
   //m_types->addItem(smoothTag_BILATERAL, QVariant(BILATERAL));
   m_types->setCurrentIndex(m_types->findText(smoothTag_GAUSSIAN));

   m_size1 = new QSpinBox(this);
   m_size1->setRange(1, 21);
   m_size1->setValue(3);
   m_size1->setSingleStep(2);

   connect(m_size1, SIGNAL(valueChanged(int)), 
      this, SLOT(size1changed(int)));

   m_size2 = new QSpinBox(this);
   m_size2->setRange(0, 21);
   m_size2->setValue(3);
   m_size2->setSingleStep(2);

   connect(m_size2, SIGNAL(valueChanged(int)), 
      this, SLOT(size2changed(int)));

   m_sigma1 = new QDoubleSpinBox(this);
   m_sigma1->setRange(0.0 , 10.0);
   m_sigma1->setValue(0.0);
   m_sigma1->setSingleStep(0.1);

   m_sigma2 = new QDoubleSpinBox(this);
   m_sigma2->setRange(0.0 , 10.0);
   m_sigma2->setValue(0.0);
   m_sigma2->setSingleStep(0.1);

   QGridLayout *lay = new QGridLayout;
   lay->addWidget(typeLabel, 0, 0);
   lay->addWidget(size1Label, 1, 0);
   lay->addWidget(size2Label, 2, 0);
   lay->addWidget(sigma1Label, 3, 0);
   lay->addWidget(sigma2Label, 4, 0);
   lay->addWidget(m_types, 0, 1);
   lay->addWidget(m_size1, 1, 1);
   lay->addWidget(m_size2, 2, 1);
   lay->addWidget(m_sigma1, 3, 1);
   lay->addWidget(m_sigma2, 4, 1);

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
//  \return CProcTask_Smooth
//    
//  \author Stian Broen 
//
//  \date  13.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_Smooth* CSmoothDialog::getData() const
{
   return new CProcTask_Smooth(
      smoothTypeFromString(m_types->currentText()),
      m_size1->value(),
      m_size2->value(),
      m_sigma1->value(),
      m_sigma2->value());
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	size1changed
//
//
//  \param  int i -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  17.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CSmoothDialog::size1changed(int i)
{
   double di = i;
   double di_2 = di / 2.0;
   double fdi = qFloor(di_2);
   if (fdi - di_2 == 0)
   {
      m_size1->setValue(i + 1);
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	size2changed
//
//
//  \param  int i -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  17.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CSmoothDialog::size2changed(int i)
{
   if (0 == i)
   {
      return;
   }
   double di = i;
   double di_2 = di / 2.0;
   double fdi = qFloor(di_2);
   if (fdi - di_2 == 0)
   {
      m_size2->setValue(i + 1);
   }
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
//  \date  09.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CSmoothDialog::setData(const QString &summary)
{
   CProcTask_Smooth data(summary);
   if (!data.isValid())
   {
      return;
   }

   m_types ->setCurrentIndex(m_types->findData(data.type()));
   m_size1 ->setValue(data.size1 ());
   m_size2 ->setValue(data.size2 ());
   m_sigma1->setValue(data.sigma1());
   m_sigma2->setValue(data.sigma2());
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
//  \date  09.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CSmoothDialog::setEditMode(bool val)
{
   m_editMode = val;
   if(m_editMode)
   {
      connect(m_types, SIGNAL(currentIndexChanged(int)), 
         this, SLOT(typeEdited(int)));

      connect(m_size1, SIGNAL(valueChanged(int)),
         this, SLOT(valueChanged(int)));

      connect(m_size2, SIGNAL(valueChanged(int)), 
         this, SLOT(valueChanged(int)));

      connect(m_sigma1, SIGNAL(valueChanged(double)), 
         this, SLOT(valueChanged(double)));

      connect(m_sigma2, SIGNAL(valueChanged(double)), 
         this, SLOT(valueChanged(double)));
   }
   else
   {
      disconnect(m_types, SIGNAL(currentIndexChanged(int)), 
         this, SLOT(typeEdited(int)));

      disconnect(m_size1, SIGNAL(valueChanged(int)), 
         this, SLOT(valueChanged(int)));

      disconnect(m_size2, SIGNAL(valueChanged(int)), 
         this, SLOT(valueChanged(int)));

      disconnect(m_sigma1, SIGNAL(valueChanged(double)), 
         this, SLOT(valueChanged(double)));

      disconnect(m_sigma2, SIGNAL(valueChanged(double)), 
         this, SLOT(valueChanged(double)));
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	typeEdited
//
//
//  \param  int
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  09.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CSmoothDialog::typeEdited(int)
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
//  \param  int
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  09.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CSmoothDialog::valueChanged(int)
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
//  \date  09.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CSmoothDialog::valueChanged(double)
{
   if (m_editMode)
   {
      emit edited();
   }
}

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
//  \file      morphDialog.cpp
//
//  \brief     GUI to define morphology related parameters
//
//  \author    Stian Broen
//
//  \date      01.10.2013
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
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>

// local includes
#include "morphDialog.h"

using namespace guiSpace;

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CMorphDialog ctor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  01.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CMorphDialog::CMorphDialog(QWidget *parent)
:CImgProcDialogBase(parent),
m_typeCombo(0),
m_shapeCombo(0),
m_useCustomKernel(0),
m_columnsSpin(0),
m_rowsSpin(0),
m_anchorXSpin(0),
m_anchorYSpin(0),
m_iterationsSpin(0)
{
   initGUI();
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CMorphDialog dtor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  01.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CMorphDialog::~CMorphDialog()
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
//  \date  01.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CMorphDialog::initGUI()
{
   QLabel *typeLabel = new QLabel("Morphology type", this);
   QLabel *iterLabel = new QLabel("Iterations", this);
   QLabel *shapeLabel = new QLabel("Kernel shape", this);
   QLabel *colLabel = new QLabel("Columns", this);
   QLabel *rowsLabel = new QLabel("Rows", this);
   QLabel *anchorXLabel = new QLabel("X Anchor", this);
   QLabel *anchorYLabel = new QLabel("Y Anchor", this);
   
   m_typeCombo = new QComboBox(this);
   m_typeCombo->addItem(morphTypeToString(MORPH_ERODE), QVariant(MORPH_ERODE));
   m_typeCombo->addItem(morphTypeToString(MORPH_DILATE), QVariant(MORPH_DILATE));
   m_typeCombo->addItem(morphTypeToString(MORPH_OPEN), QVariant(MORPH_OPEN));
   m_typeCombo->addItem(morphTypeToString(MORPH_CLOSE), QVariant(MORPH_CLOSE));
   //m_typeCombo->addItem(morphTypeToString(MORPH_GRADIENT), QVariant(MORPH_GRADIENT));
   //m_typeCombo->addItem(morphTypeToString(MORPH_TOPHAT), QVariant(MORPH_TOPHAT));
   //m_typeCombo->addItem(morphTypeToString(MORPH_BLACKHAT), QVariant(MORPH_BLACKHAT));

   m_iterationsSpin = new QSpinBox(this);
   m_iterationsSpin->setRange(1, 200);
   m_iterationsSpin->setSingleStep(1);
   m_iterationsSpin->setValue(1);

   m_useCustomKernel = new QCheckBox(this);
   m_useCustomKernel->setChecked(false);
   m_useCustomKernel->setText("Use custom kernel");
   connect(m_useCustomKernel, SIGNAL(stateChanged(int)), this, SLOT(useCustomKernelChanged(int)));
   m_useCustomKernel->setEnabled(false);

   m_shapeCombo = new QComboBox(this);
   m_shapeCombo->addItem(morphKernelShapeToString(SHAPE_DEFAULT), QVariant(SHAPE_DEFAULT));
   m_shapeCombo->addItem(morphKernelShapeToString(SHAPE_RECT), QVariant(SHAPE_RECT));
   m_shapeCombo->addItem(morphKernelShapeToString(SHAPE_CROSS), QVariant(SHAPE_CROSS));
   m_shapeCombo->addItem(morphKernelShapeToString(SHAPE_ELLIPSE), QVariant(SHAPE_ELLIPSE));
   m_shapeCombo->setCurrentIndex(m_shapeCombo->findText(morphKernelShapeToString(SHAPE_DEFAULT)));
   m_shapeCombo->setEnabled(false);
   
   m_columnsSpin = new QSpinBox(this);
   m_columnsSpin->setRange(1, 50);
   m_columnsSpin->setSingleStep(1);
   m_columnsSpin->setValue(3);
   m_columnsSpin->setEnabled(false);

   m_rowsSpin = new QSpinBox(this);
   m_rowsSpin->setRange(1, 50);
   m_rowsSpin->setSingleStep(1);
   m_rowsSpin->setValue(3);
   m_rowsSpin->setEnabled(false);

   connect(m_columnsSpin , SIGNAL(valueChanged(int)), 
      this, SLOT(checkAnchors(int)));

   connect(m_rowsSpin, SIGNAL(valueChanged(int)), 
      this, SLOT(checkAnchors(int)));

   m_anchorXSpin = new QSpinBox(this);
   m_anchorXSpin->setSingleStep(1);
   m_anchorXSpin->setValue(2);
   m_anchorXSpin->setEnabled(false);

   m_anchorYSpin = new QSpinBox(this);
   m_anchorYSpin->setSingleStep(1);
   m_anchorYSpin->setValue(2);
   m_anchorYSpin->setEnabled(false);

   m_anchorXSpin->setRange(0, m_columnsSpin->value() - 1);
   m_anchorYSpin->setRange(0, m_rowsSpin->value() - 1);

   QGridLayout *wlay = new QGridLayout;
   wlay->addWidget(typeLabel, 0, 0);
   wlay->addWidget(iterLabel, 1, 0);
   wlay->addWidget(m_useCustomKernel, 2, 0, 1, 2);
   wlay->addWidget(shapeLabel, 3, 0);
   wlay->addWidget(colLabel, 4, 0);
   wlay->addWidget(rowsLabel, 5, 0);
   wlay->addWidget(anchorXLabel, 6, 0);
   wlay->addWidget(anchorYLabel, 7, 0);

   wlay->addWidget(m_typeCombo, 0, 1);
   wlay->addWidget(m_iterationsSpin, 1, 1);
   wlay->addWidget(m_shapeCombo, 3, 1);
   wlay->addWidget(m_columnsSpin, 4, 1);
   wlay->addWidget(m_rowsSpin, 5, 1);
   wlay->addWidget(m_anchorXSpin, 6, 1);
   wlay->addWidget(m_anchorYSpin, 7, 1);

   this->setLayout(wlay);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	getData
//
//
//  \param  N/A
//
//  \return CProcTask_Morph*
//    
//  \author Stian Broen 
//
//  \date  01.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_Morph* CMorphDialog::getData() const
{
   return new CProcTask_Morph(
      static_cast<MorphType>(m_typeCombo->itemData(m_typeCombo->currentIndex()).toInt()),
      static_cast<MorphKernelShape>(m_shapeCombo->itemData(m_shapeCombo->currentIndex()).toInt()),
      m_columnsSpin->value(),
      m_rowsSpin->value(),
      m_anchorXSpin->value(),
      m_anchorYSpin->value(),
      m_iterationsSpin->value());
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	useCustomKernelChanged
//
//
//  \param  int val -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  01.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CMorphDialog::useCustomKernelChanged(int)
{
   if(m_useCustomKernel->isChecked())
   {
      m_shapeCombo->setCurrentIndex(m_shapeCombo->findText(morphKernelShapeToString(SHAPE_RECT)));
      m_shapeCombo->setEnabled(true);
      m_columnsSpin->setEnabled(true);
      m_rowsSpin->setEnabled(true);
      m_anchorXSpin->setEnabled(true);
      m_anchorYSpin->setEnabled(true);
   }
   else
   {
      m_shapeCombo->setCurrentIndex(m_shapeCombo->findText(morphKernelShapeToString(SHAPE_DEFAULT)));
      m_shapeCombo->setEnabled(false);
      m_columnsSpin->setEnabled(false);
      m_rowsSpin->setEnabled(false);
      m_anchorXSpin->setEnabled(false);
      m_anchorYSpin->setEnabled(false);
   }
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
void CMorphDialog::setEditMode(bool val)
{
   m_editMode = val;
   if(m_editMode)
   {
      connect(m_useCustomKernel, SIGNAL(stateChanged(int)), 
         this, SLOT(valueChanged(int)));

      connect(m_typeCombo, SIGNAL(currentIndexChanged(int)), 
         this, SLOT(typeEdited  (int)));

      connect(m_shapeCombo, SIGNAL(currentIndexChanged(int)), 
         this, SLOT(typeEdited  (int)));

      connect(m_columnsSpin, SIGNAL(valueChanged(int)), 
         this, SLOT(valueChanged(int)));

      connect(m_rowsSpin, SIGNAL(valueChanged(int)), 
         this, SLOT(valueChanged(int)));

      connect(m_anchorXSpin, SIGNAL(valueChanged(int)), 
         this, SLOT(valueChanged(int)));

      connect(m_anchorYSpin, SIGNAL(valueChanged(int)), 
         this, SLOT(valueChanged(int)));

      connect(m_iterationsSpin, SIGNAL(valueChanged(int)), 
         this, SLOT(valueChanged(int)));
   }
   else
   {
      disconnect(m_useCustomKernel, SIGNAL(stateChanged(int)), 
         this, SLOT(valueChanged(int)));

      disconnect(m_typeCombo, SIGNAL(currentIndexChanged(int)), 
         this, SLOT(typeEdited(int)));

      disconnect(m_shapeCombo, SIGNAL(currentIndexChanged(int)), 
         this, SLOT(typeEdited(int)));

      disconnect(m_columnsSpin, SIGNAL(valueChanged(int)), 
         this, SLOT(valueChanged(int)));

      disconnect(m_rowsSpin, SIGNAL(valueChanged(int)), 
         this, SLOT(valueChanged(int)));

      disconnect(m_anchorXSpin, SIGNAL(valueChanged(int)), 
         this, SLOT(valueChanged(int)));

      disconnect(m_anchorYSpin, SIGNAL(valueChanged(int)), 
         this, SLOT(valueChanged(int)));

      disconnect(m_iterationsSpin , SIGNAL(valueChanged(int)), 
         this, SLOT(valueChanged(int)));
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
void CMorphDialog::setData(const QString &summary)
{
   CProcTask_Morph data(summary);
   if (!data.isValid())
   {
      return;
   }
   m_typeCombo ->setCurrentIndex(m_typeCombo ->findData(data.type      ()));
   m_shapeCombo->setCurrentIndex(m_shapeCombo->findData(data.kernelType()));
   if (data.kernelType() == SHAPE_DEFAULT)
   {
      m_useCustomKernel->setChecked(false);
   }
   else
   {
      m_useCustomKernel->setChecked(true);
   }
   m_columnsSpin->setValue(data.columns());
   m_rowsSpin->setValue(data.rows());
   m_anchorXSpin->setValue(data.anchor_x());
   m_anchorYSpin->setValue(data.anchor_y());
   m_iterationsSpin->setValue(data.iterations());
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
void CMorphDialog::typeEdited(int)
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
void CMorphDialog::valueChanged(int)
{
   if (m_editMode)
   {
      emit edited();
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	checkAnchors
//
//
//  \param  int
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  11.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CMorphDialog::checkAnchors(int)
{
   if (m_anchorXSpin->value() >= m_columnsSpin->value())
   {
      m_anchorXSpin->setValue(m_columnsSpin->value() - 1);
   }
   if (m_anchorYSpin->value() >= m_rowsSpin->value())
   {
      m_anchorYSpin->setValue(m_rowsSpin->value() - 1);
   }
   m_anchorXSpin->setRange(0, m_columnsSpin->value() - 1);
   m_anchorYSpin->setRange(0, m_rowsSpin->value() - 1);
}

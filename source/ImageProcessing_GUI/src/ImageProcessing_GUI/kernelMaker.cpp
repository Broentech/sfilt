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
//  \file      kernelMaker.cpp
//
//  \brief     GUI to define kernels
//
//  \author    Stian Broen
//
//  \date      01.01.2014
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
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QFrame>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QHeaderView>

// solution includes

// local includes
#include "kernelMaker.h"

using namespace guiSpace;

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CKernelDialog ctor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  01.01.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////
CKernelDialog::CKernelDialog(QWidget *parent)
:CImgProcDialogBase(parent),
m_typeCombo(0),
//m_valueCombo(0),
m_kernel(0),
m_lastType(KERNEL_3X3),
m_lastVarType(QVariant::Double)
{
   initGUI();
   updateKernel();
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CKernelDialog dtor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  01.01.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////
CKernelDialog::~CKernelDialog()
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
//  \date  01.01.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CKernelDialog::initGUI()
{
   QLabel *typeLabel = new QLabel("Type", this);
   //QLabel *valueLabel = new QLabel("Value Type", this);
   QLabel *kernelLabel = new QLabel("Kernel", this);

   m_typeCombo = new QComboBox(this);
   m_typeCombo->addItem(kernelTypeToString(KERNEL_3X3), KERNEL_3X3);
   m_typeCombo->addItem(kernelTypeToString(KERNEL_5X5), KERNEL_5X5);
   m_typeCombo->addItem(kernelTypeToString(KERNEL_7X7), KERNEL_7X7);
   //m_typeCombo->addItem(kernelTypeToString(KERNEL_CUSTOM) , KERNEL_CUSTOM ); // XXX TODO
   m_typeCombo->setCurrentIndex(m_typeCombo->findText(kernelTypeToString(KERNEL_3X3)));

   connect(m_typeCombo, SIGNAL(currentIndexChanged(int)), 
      this, SLOT(typeComboChanged(int)));

   //m_valueCombo = new QComboBox(this);

   //connect(m_valueCombo, SIGNAL(currentIndexChanged(int)), 
   //   this, SLOT(valueTypeComboChanged(int)));

   //QList<QVariant::Type> kernelVals = allowedKernelValueTypes();
   //for(int i=0; i<kernelVals.size(); i++)
   //{
   //   QVariant::Type type = kernelVals.at(i);
   //   m_valueCombo->addItem(variantTypeToString(type), static_cast<int>(type));
   //}
   //m_valueCombo->setCurrentIndex(0);

   m_kernel = new QTableWidget(this);
   QSizePolicy kernelSize;
   kernelSize.setVerticalPolicy(QSizePolicy::Maximum);
   kernelSize.setHorizontalPolicy(QSizePolicy::Maximum);
   m_kernel->setSizePolicy(kernelSize);
   QHBoxLayout *kernelHL = new QHBoxLayout;
   kernelHL->addStretch();
   kernelHL->addWidget(m_kernel);
   kernelHL->addStretch();

   QGridLayout *lay = new QGridLayout;
   lay->addWidget(typeLabel, 0 , 0);
   //lay->addWidget(valueLabel, 1 , 0);
   lay->addWidget(m_typeCombo, 0 , 1);
   //lay->addWidget(m_valueCombo, 1 , 1);

   QFrame* line = new QFrame();
   line->setFrameShape(QFrame::HLine);
   line->setFrameShadow(QFrame::Sunken);

   QVBoxLayout *_lay = new QVBoxLayout;
   _lay->addLayout(lay);
   _lay->addWidget(line);
   _lay->addWidget(kernelLabel);
   _lay->addLayout(kernelHL);
   _lay->addStretch();
   this->setLayout(_lay);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	getData
//
//
//  \param  KernelType type        -
//          QVariant::Type vartype -
//
//  \return CProcTask_Kernels*
//    
//  \author Stian Broen 
//
//  \date  01.01.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_Kernels* CKernelDialog::getData(KernelType type, QVariant::Type vartype) const
{
   if (m_kernel == 0 ||
      //m_valueCombo == 0 ||
      m_typeCombo == 0)
   {
      return 0;
   }

   QVariant::Type valType = QVariant::Double;
   //if (vartype == QVariant::Invalid)
   //{
   //   valType = static_cast<QVariant::Type>(m_valueCombo->itemData(m_valueCombo->currentIndex()).toInt());
   //}
   //else
   //{
   //   valType = vartype;
   //}
   KernelType kernelType;
   if (type == KERNEL_UNKNOWN)
   {
      kernelType = static_cast<KernelType>(m_typeCombo->itemData(m_typeCombo->currentIndex()).toInt());
   }
   else
   {
      kernelType = type;
   }

   CProcTask_Kernels *data = new CProcTask_Kernels;
   data->setType(kernelType);
   data->setValueType(valType);
   for(int x=0; x<m_kernel->columnCount(); x++)
   {
      for(int y=0; y<m_kernel->rowCount(); y++)
      {
         QWidget *widget = m_kernel->cellWidget(y, x);
         if (0 == widget)
         {
            continue;
         }
         switch(valType)
         {
         case(QVariant::Int):
            {
               QSpinBox *item = qobject_cast<QSpinBox *>(widget);
               if (0 == item)
               {
                  continue;
               }
               int value = item->value();
               kernelvalue tup;
               setFirst(tup, x);
               setSecond(tup, y);
               setThird(tup, QVariant(value));
               data->addKernelValue(tup);
            }
            break;
         case(QVariant::Double):
            {
               QDoubleSpinBox *item = qobject_cast<QDoubleSpinBox *>(widget);
               if (0 == item)
               {
                  continue;
               }
               double value = item->value();
               kernelvalue tup;
               setFirst(tup, x);
               setSecond(tup, y);
               setThird(tup, QVariant(value));
               data->addKernelValue(tup);
            }
            break;
         default:
            continue;
         }
      }
   }
   return data;
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
//  \date  01.01.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CKernelDialog::setData(const QString &summary)
{
   CProcTask_Kernels tempData(summary);
   int index = m_typeCombo->findData(tempData.type());
   if (index >= 0)
   {
      m_typeCombo->setCurrentIndex(index);
   }
   //int vartype = static_cast<int>(tempData.valueType());
   //index = m_valueCombo->findData(vartype);
   //if (index >= 0)
   //{
   //   m_valueCombo->setCurrentIndex(index);
   //}
   QList< kernelvalue > kernel = tempData.kernel();
   for(int i=0; i<kernel.size(); i++)
   {
      kernelvalue tup = kernel.at(i);
      int x = first(tup);
      int y = second(tup);
      QVariant val = third(tup);
      if(m_kernel->columnCount() > x &&
        m_kernel->rowCount() > y)
      {
         switch(tempData.valueType())
         {
         case(QVariant::Int):
            {
               QSpinBox *item = qobject_cast<QSpinBox *>(m_kernel->cellWidget(x, y));
               if (0 == item)
               {
                  continue;
               }
               item->setValue(val.toInt());
            }
            break;
         case(QVariant::Double):
            {
               QDoubleSpinBox *item = qobject_cast<QDoubleSpinBox *>(m_kernel->cellWidget(x, y));
               if (0 == item)
               {
                  continue;
               }
               item->setValue(val.toDouble());
            }
            break;
         default:
            continue;
         }
      }
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
//  \date  01.01.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CKernelDialog::valueChanged(int)
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
//  \date  02.01.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CKernelDialog::valueChanged(double)
{
   if (m_editMode)
   {
      emit edited();
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
//  \date  01.01.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CKernelDialog::setEditMode(bool val)
{
   m_editMode = val;
   if(m_editMode)
   {
      connect(m_typeCombo, SIGNAL(currentIndexChanged(int)), 
         this, SLOT(valueChanged(int)));

      //connect(m_valueCombo, SIGNAL(currentIndexChanged(int)), 
      //   this, SLOT(valueChanged(int)));

      for(int x=0; x<m_kernel->columnCount(); x++)
      {
         for(int y=0; y<m_kernel->rowCount(); y++)
         {
            QWidget *widget = m_kernel->cellWidget(y, x);
            if (0 == widget)
            {
               continue;
            }
            switch(m_lastVarType)
            {
            case(QVariant::Int):
               {
                  QSpinBox *item = qobject_cast<QSpinBox *>(widget);
                  if (0 == item)
                  {
                     continue;
                  }

                  connect(item, SIGNAL(valueChanged(int)), 
                     this, SLOT(valueChanged(int)));
               }
               break;
            case(QVariant::Double):
               {
                  QDoubleSpinBox *item = qobject_cast<QDoubleSpinBox *>(widget);
                  if (0 == item)
                  {
                     continue;
                  }

                  connect(item, SIGNAL(valueChanged(double)), 
                     this, SLOT(valueChanged(double)));
               }
               break;
            default:
               continue;
            }
         }
      }
   }
   else
   {
      disconnect(m_typeCombo, SIGNAL(currentIndexChanged(int)), 
         this, SLOT(valueChanged(int)));

      //disconnect(m_valueCombo, SIGNAL(currentIndexChanged(int)), 
      //   this, SLOT(valueChanged(int)));

      for(int x=0; x<m_kernel->columnCount(); x++)
      {
         for(int y=0; y<m_kernel->rowCount(); y++)
         {
            QWidget *widget = m_kernel->cellWidget(y, x);
            if (0 == widget)
            {
               continue;
            }
            switch(m_lastVarType)
            {
            case(QVariant::Int):
               {
                  QSpinBox *item = qobject_cast<QSpinBox *>(widget);
                  if (0 == item)
                  {
                     continue;
                  }

                  disconnect(item, SIGNAL(valueChanged(int)), 
                     this, SLOT(valueChanged(int)));
               }
               break;
            case(QVariant::Double):
               {
                  QDoubleSpinBox *item = qobject_cast<QDoubleSpinBox *>(widget);
                  if (0 == item)
                  {
                     continue;
                  }

                  disconnect(item, SIGNAL(valueChanged(double)), 
                     this, SLOT(valueChanged(double)));
               }
               break;
            default:
               continue;
            }
         }
      }
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	updateKernel
//
//
//  \param  N/A -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  01.01.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CKernelDialog::updateKernel()
{
   if (m_kernel == 0 ||
      //m_valueCombo == 0 ||
      m_typeCombo == 0)
   {
      return;
   }

   m_kernel->clear();
   int typeIndex = m_typeCombo->itemData(m_typeCombo->currentIndex()).toInt();
   if (typeIndex <= 0)
   {
      // TODO create custom kernel size
      return;
   }

   QVariant::Type type = QVariant::Double; // static_cast<QVariant::Type>(m_valueCombo->itemData(m_valueCombo->currentIndex()).toInt());
   int w = 0;
   int row_index = 0;
   m_kernel->setColumnCount(typeIndex);
   m_kernel->setRowCount(typeIndex);
   m_kernel->horizontalHeader()->setDefaultSectionSize(42);
   m_kernel->horizontalHeader()->hide();
   m_kernel->verticalHeader()->setDefaultSectionSize(42);
   m_kernel->verticalHeader()->hide();
   double mid = static_cast<double>(typeIndex - 1) / 2.0;
   for(int i=0; i<typeIndex; i++)
   {
      for(int j=0; j<typeIndex; j++)
      {
         QWidget *cell = makeKernelCell(type);
         if (0 == cell)
         {
            continue;
         }
         if (static_cast<double>(i) == mid && static_cast<double>(j) == mid)
         {
            cell->setFont(QFont("", 14));
         }
         m_kernel->setCellWidget(i, j, cell);
      }
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	typeComboChanged
//
//
//  \param  int val -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  02.01.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CKernelDialog::typeComboChanged(int val)
{
   CProcTask_Kernels *tempData = getData(m_lastType);
   updateKernel();
   m_lastType = static_cast<KernelType>(m_typeCombo->itemData(m_typeCombo->currentIndex()).toInt());
   if(0 != tempData)
   {
      disconnect(m_typeCombo, SIGNAL(currentIndexChanged(int)), 
         this, SLOT(typeComboChanged(int)));

      //disconnect(m_valueCombo, SIGNAL(currentIndexChanged(int)), 
      //   this, SLOT(valueTypeComboChanged(int)));

      setData(tempData->json());

      connect(m_typeCombo, SIGNAL(currentIndexChanged(int)), 
         this, SLOT(typeComboChanged(int)));

      //connect(m_valueCombo, SIGNAL(currentIndexChanged(int)), 
      //   this, SLOT(valueTypeComboChanged(int)));

      delete tempData;
   }
   m_typeCombo->setCurrentIndex(val);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	valueTypeComboChanged
//
//
//  \param  int val -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  02.01.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CKernelDialog::valueTypeComboChanged(int val)
{
   CProcTask_Kernels *tempData = getData(KERNEL_UNKNOWN, m_lastVarType);
   updateKernel();
   m_lastVarType = QVariant::Double; // static_cast<QVariant::Type>(m_valueCombo->itemData(m_valueCombo->currentIndex()).toInt());
   if(0 != tempData)
   {
      disconnect(m_typeCombo, SIGNAL(currentIndexChanged(int)), 
         this, SLOT(typeComboChanged(int)));

      //disconnect(m_valueCombo, SIGNAL(currentIndexChanged(int)), 
      //   this, SLOT(valueTypeComboChanged(int)));

      tempData->setValueType(m_lastVarType);
      setData(tempData->json());

      connect(m_typeCombo, SIGNAL(currentIndexChanged(int)), 
         this, SLOT(typeComboChanged(int)));

      //connect(m_valueCombo, SIGNAL(currentIndexChanged(int)), 
      //   this, SLOT(valueTypeComboChanged(int)));

      delete tempData;
   }
   //m_valueCombo->setCurrentIndex(val);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	makeKernelCell
//
//
//  \param  QVariant::Type type -
//
//  \return QWidget*
//    
//  \author Stian Broen 
//
//  \date  01.01.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////
QWidget* guiSpace::makeKernelCell(QVariant::Type type)
{
   if(type == QVariant::Int)
   {
      QSpinBox *item = new QSpinBox;
      item->setValue(0);
      item->setRange(-255, 255);
      item->setMaximumSize(QSize(42, 42));
      item->setMinimumSize(QSize(42, 42));
      item->setButtonSymbols(QAbstractSpinBox::NoButtons);
      item->setAlignment(Qt::AlignCenter);
      return item;
   }
   else if(type == QVariant::Double)
   {
      QDoubleSpinBox *item = new QDoubleSpinBox;
      item->setValue(0.0);
      item->setRange(-255.0, 255.0);
      item->setMaximumSize(QSize(42, 42));
      item->setMinimumSize(QSize(42, 42));
      item->setButtonSymbols(QAbstractSpinBox::NoButtons);
      item->setAlignment(Qt::AlignCenter);
      return item;
   }
   else
   {
      return 0;
   }
}

//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      grayDialog.cpp
//
//  \brief     GUI to define grayscale related parameters
//
//  \author    Stian Broen
//
//  \date      22.09.2013
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

// Qt includes
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>

// local includes
#include "grayDialog.h"

using namespace guiSpace;

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CGrayDialog ctor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  22.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CGrayDialog::CGrayDialog(QWidget *parent)
:CImgProcDialogBase(parent),
m_typeCombo(0),
m_lowThreshSpin(0),
m_highThreshSpin(0),
m_apertureSpin(0)
{
   initGUI();
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CGrayDialog dtor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  22.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CGrayDialog::~CGrayDialog()
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
//  \date  22.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CGrayDialog::initGUI()
{
   QLabel *typeLabel = new QLabel("Processing type", this);
   QLabel *lowLabel = new QLabel("Low threshold", this);
   QLabel *highLabel = new QLabel("High threshold", this);
   QLabel *apertureLabel = new QLabel("Aperture", this);

   m_typeCombo = new QComboBox(this);
   m_typeCombo->addItem(grayScaleTypeToString(CONVERT_TO_GRAYSCALE), QVariant(CONVERT_TO_GRAYSCALE));
   m_typeCombo->addItem(grayScaleTypeToString(CONVERT_TO_BINARY), QVariant(CONVERT_TO_BINARY));
   m_typeCombo->addItem(grayScaleTypeToString(CONVERT_TO_CANNY), QVariant(CONVERT_TO_CANNY));

   connect(m_typeCombo, SIGNAL(currentIndexChanged(const QString &)),
      this, SLOT(typeChanged(const QString &)));

   m_lowThreshSpin = new QDoubleSpinBox(this);
   m_lowThreshSpin->setRange(0.0, 255.0);
   m_lowThreshSpin->setSingleStep(1.0);
   m_lowThreshSpin->setValue(10.0);
   m_lowThreshSpin->setEnabled(false);

   m_highThreshSpin = new QDoubleSpinBox(this);
   m_highThreshSpin->setRange(0.0, 255.0);
   m_highThreshSpin->setSingleStep(1.0);
   m_highThreshSpin->setValue(100.0);
   m_highThreshSpin->setEnabled(false);

   m_apertureSpin  = new QDoubleSpinBox(this);
   m_apertureSpin->setRange(0.0, 255.0);
   m_apertureSpin->setSingleStep(1.0);
   m_apertureSpin->setValue(3);
   m_apertureSpin->setEnabled(false);

   QGridLayout *wlay = new QGridLayout;
   wlay->addWidget(typeLabel, 0, 0);
   wlay->addWidget(lowLabel, 1, 0);
   wlay->addWidget(highLabel, 2, 0);
   wlay->addWidget(apertureLabel, 3, 0);
   wlay->addWidget(m_typeCombo, 0, 1);
   wlay->addWidget(m_lowThreshSpin, 1, 1);
   wlay->addWidget(m_highThreshSpin, 2, 1);
   wlay->addWidget(m_apertureSpin, 3, 1);

   this->setLayout(wlay);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	typeChanged
//
//
//  \param  const QString & -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  22.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CGrayDialog::typeChanged(const QString &)
{
   switch(m_typeCombo->itemData(m_typeCombo->currentIndex()).toInt())
   {
   case(CONVERT_TO_GRAYSCALE):
      m_lowThreshSpin->setEnabled(false);
      m_highThreshSpin->setEnabled(false);
      m_apertureSpin->setEnabled(false);
      break;
   case(CONVERT_TO_BINARY):
      m_lowThreshSpin->setEnabled(true);
      m_highThreshSpin->setEnabled(false);
      m_apertureSpin->setEnabled(false);
      break;
   case(CONVERT_TO_CANNY):
      m_lowThreshSpin->setEnabled(true);
      m_highThreshSpin->setEnabled(true);
      m_apertureSpin->setEnabled(true);
      break;
   case(UNKNOWN_GRAYSCALE):
   default:
      break;
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	getData
//
//
//  \param  N/A
//
//  \return CProcTask_Gray*
//    
//  \author Stian Broen 
//
//  \date  22.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_Gray* CGrayDialog::getData() const
{
   return new CProcTask_Gray(
      static_cast<GrayScaleType>(m_typeCombo->itemData(m_typeCombo->currentIndex()).toInt()),
      m_lowThreshSpin->value(),
      m_highThreshSpin->value(),
      m_apertureSpin->value());
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
//  \date  22.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CGrayDialog::setData(const QString &summary)
{
   CProcTask_Gray data(summary);
   if (!data.isValid())
   {
      return;
   }
   m_lowThreshSpin->setValue(data.lowThreshold());
   m_highThreshSpin->setValue(data.highThreshold());
   m_apertureSpin->setValue(data.aperture());
   m_typeCombo->setCurrentIndex(m_typeCombo->findData(data.type()));
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
//  \date  08.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CGrayDialog::setEditMode(bool val)
{
   m_editMode = val;
   if(m_editMode)
   {
      connect(m_typeCombo, SIGNAL(currentIndexChanged(int)), 
         this, SLOT(typeEdited(int)));

      connect(m_lowThreshSpin, SIGNAL(valueChanged(double)), 
         this, SLOT(valueChanged(double)));

      connect(m_highThreshSpin, SIGNAL(valueChanged(double)), 
         this, SLOT(valueChanged(double)));

      connect(m_apertureSpin, SIGNAL(valueChanged(double)), 
         this, SLOT(valueChanged(double)));
   }
   else
   {
      disconnect(m_typeCombo, SIGNAL(currentIndexChanged(int)), 
         this, SLOT(typeEdited(int)));

      disconnect(m_lowThreshSpin, SIGNAL(valueChanged(double)), 
         this, SLOT(valueChanged(double)));

      disconnect(m_highThreshSpin, SIGNAL(valueChanged(double)), 
         this, SLOT(valueChanged(double)));

      disconnect(m_apertureSpin, SIGNAL(valueChanged(double)), 
         this, SLOT(valueChanged(double)));
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	typeEdited
//
//
//  \param  int -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  08.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CGrayDialog::typeEdited(int)
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
//  \param  double -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  08.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CGrayDialog::valueChanged(double)
{
   if (m_editMode)
   {
      emit edited();
   }
}


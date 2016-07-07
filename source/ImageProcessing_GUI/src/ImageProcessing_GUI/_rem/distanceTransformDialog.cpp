//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      distanceTransformDialog.cpp
//
//  \brief     GUI to define distance transform related parameters
//
//  \author    Stian Broen
//
//  \date      27.12.2013
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
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

// solution includes

// local includes
#include "distanceTransformDialog.h"

using namespace guiSpace;

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CDistTransDialog ctor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  27.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CDistTransDialog::CDistTransDialog(QWidget *parent)
:CImgProcDialogBase(parent),
m_typeCombo(0),
m_maskCombo(0)
{
   initGUI();
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CDistTransDialog dtor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  27.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CDistTransDialog::~CDistTransDialog()
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
//  \date  27.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CDistTransDialog::initGUI()
{
   QLabel *typeLabel = new QLabel("Type", this);
   QLabel *maskLabel = new QLabel("Mask", this);

   m_typeCombo = new QComboBox(this);
   m_typeCombo->addItem(distTransTypeToString(DIST_L2), DIST_L2);
   m_typeCombo->addItem(distTransTypeToString(DIST_L1), DIST_L1);
   m_typeCombo->addItem(distTransTypeToString(DIST_L12), DIST_L12);
   m_typeCombo->addItem(distTransTypeToString(DIST_FAIR), DIST_FAIR);
   m_typeCombo->addItem(distTransTypeToString(DIST_WELSCH), DIST_WELSCH);
   m_typeCombo->setCurrentIndex(m_typeCombo->findText(distTransTypeToString(DIST_L2)));

   m_maskCombo = new QComboBox(this);
   m_maskCombo->addItem("3 X 3", DIST_MASK_3);
   m_maskCombo->addItem("5 X 5", DIST_MASK_5);
   m_maskCombo->addItem("PRECISE", DIST_MASK_PRECISE);
   m_maskCombo->setCurrentIndex(m_maskCombo->findText("3 X 3"));

   QGridLayout *lay = new QGridLayout;
   lay->addWidget(typeLabel, 0, 0);
   lay->addWidget(maskLabel, 1, 0);
   lay->addWidget(m_typeCombo, 0, 1);
   lay->addWidget(m_maskCombo, 1, 1);

   QVBoxLayout *_lay = new QVBoxLayout;
   _lay->addLayout(lay);
   _lay->addStretch();
   this->setLayout(_lay);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	getData
//
//
//  \param  N/A
//
//  \return CProcTask_DistTrans*
//    
//  \author Stian Broen 
//
//  \date  27.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_DistTrans* CDistTransDialog::getData() const
{
   DistanceTransformType type = static_cast<DistanceTransformType>(m_typeCombo->itemData(m_typeCombo->currentIndex()).toInt());
   DistanceTransformMask mask = static_cast<DistanceTransformMask>(m_maskCombo->itemData(m_maskCombo->currentIndex()).toInt());
   return new CProcTask_DistTrans(type, mask);
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
//  \date  27.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CDistTransDialog::setData(const QString &summary)
{
   CProcTask_DistTrans data(summary);
   int index = m_typeCombo->findData(data.type());
   if (index >= 0)
   {
      m_typeCombo->setCurrentIndex(index);
   }
   index = m_maskCombo->findData(data.mask());
   if (index >= 0)
   {
      m_maskCombo->setCurrentIndex(index);
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
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CDistTransDialog::valueChanged(int)
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
//  \date  27.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CDistTransDialog::setEditMode(bool val)
{
   m_editMode = val;
   if(m_editMode)
   {
      connect(m_typeCombo, SIGNAL(currentIndexChanged (int)), 
         this, SLOT(valueChanged(int)));

      connect(m_maskCombo, SIGNAL(currentIndexChanged (int)), 
         this, SLOT(valueChanged(int)));
   }
   else
   {
      disconnect(m_typeCombo, SIGNAL(currentIndexChanged(int)), 
         this, SLOT(valueChanged(int)));

      disconnect(m_maskCombo, SIGNAL(currentIndexChanged(int)), 
         this, SLOT(valueChanged(int)));
   }
}

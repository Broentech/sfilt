//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      logPolarDialog.cpp
//
//  \brief     GUI to define LogPolar related parameters
//
//  \author    Stian Broen
//
//  \date      20.12.2013
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
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGroupBox>

// solution includes
#include <ImageProcessing/metaDataKeeper.h>

// local includes
#include "logPolarDialog.h"

using namespace guiSpace;

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CLogPolarDialog ctor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CLogPolarDialog::CLogPolarDialog(QWidget *parent)
:CImgProcDialogBase(parent),
m_selectPointCombo(0),
m_mValSpint(0),
m_doWarpFillCheck(0),
m_doInverseCheck(0),
m_useInterGroup(0),
m_useInter_NN(0),
m_useInter_LINEAR(0),
m_useInter_CUBIC(0),
m_useInter_AREA(0),
m_useInter_LANCOZ(0)
{
   initGUI();

   connect(CMetaDataKeeper::getInstance(), SIGNAL(pointListUpdated()), 
      this, SLOT(updateList()));

   connect(CMetaDataKeeper::getInstance(), SIGNAL(pointTracking(const QString &, const QPoint &)), 
      this, SLOT(pointTracking(const QString &, const QPoint &)));

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CLogPolarDialog dtor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CLogPolarDialog::~CLogPolarDialog()
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
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CLogPolarDialog::initGUI()
{
   QLabel *pointLabel = new QLabel("Center Point", this);
   QLabel *mLabel = new QLabel("M - Value", this);

   m_selectPointCombo = new QComboBox(this);
   m_mValSpint = new QDoubleSpinBox(this);
   m_mValSpint->setRange(0.1, 512.0);
   m_mValSpint->setValue(100.0);

   QGridLayout *toplay = new QGridLayout;
   toplay->addWidget(pointLabel, 0, 0);
   toplay->addWidget(mLabel, 1, 0);
   toplay->addWidget(m_selectPointCombo, 0, 1);
   toplay->addWidget(m_mValSpint, 1, 1);


   QLabel *interNNLabel = new QLabel("NN", this);
   QLabel *interLINEARLabel = new QLabel("LINEAR", this);
   QLabel *interCUBUCLabel = new QLabel("CUBIC", this);
   QLabel *interAREALabel = new QLabel("AREA", this);
   QLabel *interLANCOZLabel = new QLabel("LANCZOS4", this);

   m_useInter_NN = new QRadioButton(this);
   m_useInter_NN->setChecked(false);

   m_useInter_LINEAR = new QRadioButton(this);
   m_useInter_LINEAR->setChecked(true);

   m_useInter_CUBIC = new QRadioButton(this);
   m_useInter_CUBIC->setChecked(false);

   m_useInter_AREA = new QRadioButton(this);
   m_useInter_AREA->setChecked(false);

   m_useInter_LANCOZ = new QRadioButton(this);
   m_useInter_LANCOZ->setChecked(false);

   m_useInterGroup = new QButtonGroup(this);
   m_useInterGroup->setExclusive(true);
   m_useInterGroup->addButton(m_useInter_NN, CV_INTER_NN);
   m_useInterGroup->addButton(m_useInter_LINEAR, CV_INTER_LINEAR);
   m_useInterGroup->addButton(m_useInter_CUBIC, CV_INTER_CUBIC);
   m_useInterGroup->addButton(m_useInter_AREA, CV_INTER_AREA);
   m_useInterGroup->addButton(m_useInter_LANCOZ, CV_INTER_LANCZOS4);

   QGridLayout *interlay = new QGridLayout;
   interlay->addWidget(interNNLabel, 0, 0);
   interlay->addWidget(interLINEARLabel, 1, 0);
   interlay->addWidget(interCUBUCLabel, 2, 0);
   interlay->addWidget(interAREALabel, 3, 0);
   interlay->addWidget(interLANCOZLabel, 4, 0);
   interlay->addWidget(m_useInter_NN, 0, 1);
   interlay->addWidget(m_useInter_LINEAR, 1, 1);
   interlay->addWidget(m_useInter_CUBIC, 2, 1);
   interlay->addWidget(m_useInter_AREA, 3, 1);
   interlay->addWidget(m_useInter_LANCOZ, 4, 1);

   QGroupBox *interbox = new QGroupBox(this);
   interbox->setTitle("Interpolation");
   interbox->setLayout(interlay);


   QLabel *m_useFillLabel = new QLabel("Fill Outliers", this);
   QLabel *m_useInversLabel = new QLabel("Inverse Map" , this);

   m_doWarpFillCheck = new QCheckBox(this);
   m_doInverseCheck = new QCheckBox(this);

   QGridLayout *botlay = new QGridLayout;
   botlay->addWidget(m_useFillLabel, 0, 0);
   botlay->addWidget(m_useInversLabel, 1, 0);
   botlay->addWidget(m_doWarpFillCheck, 0, 1);
   botlay->addWidget(m_doInverseCheck, 1, 1);

   QGroupBox *warpBox = new QGroupBox(this);
   warpBox->setTitle("Warping");
   warpBox->setLayout(botlay);

   QHBoxLayout *flaglay = new QHBoxLayout;
   flaglay->addWidget(interbox);
   flaglay->addWidget(warpBox);

   QVBoxLayout *_lay = new QVBoxLayout;
   _lay->addLayout(toplay);
   _lay->addLayout(flaglay);
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
//  \return CProcTask_LogPolar*
//    
//  \author Stian Broen 
//
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_LogPolar* CLogPolarDialog::getData() const
{
   QString pointName = m_selectPointCombo->currentText();
   if (pointName == "")
   {
      return 0;
   }
   int pointIndex = m_selectPointCombo->findText(pointName);
   if (pointIndex < 0)
   {
      return 0;
   }
   QPoint pt = m_selectPointCombo->itemData(pointIndex).toPoint();
   qreal m = m_mValSpint->value();
   if (m < 0.1)
   {
      return 0;
   }
   bool useFill = m_doWarpFillCheck->isChecked();
   bool useInv  = m_doInverseCheck->isChecked();
   int interpoaltion = m_useInterGroup->id(m_useInterGroup->checkedButton());
   int flags;
   if (useFill && !useInv)
   {
      flags = interpoaltion + CV_WARP_FILL_OUTLIERS;
   }
   else if (!useFill && useInv)
   {
      flags = interpoaltion + CV_WARP_INVERSE_MAP;
   }
   else if (useFill && useInv)
   {
      flags = interpoaltion + CV_WARP_FILL_OUTLIERS + CV_WARP_INVERSE_MAP;
   }
   else
   {
      flags = interpoaltion;
   }

   return new CProcTask_LogPolar(pt, m, flags);
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
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CLogPolarDialog::setData(const QString &summary)
{
   CProcTask_LogPolar data(summary);
   m_mValSpint->setValue(data.m());
   for(int i=0; i<m_selectPointCombo->count(); i++)
   {
      if(m_selectPointCombo->itemData(i).toPoint() == data.center())
      {
         m_selectPointCombo->setCurrentIndex(i);
         break;
      }
   }

   // kinda clunky, but here goes
   switch(data.flags())
   {
   case(0):
      m_useInter_NN ->setChecked(true);
      m_doWarpFillCheck->setChecked(false);
      m_doInverseCheck->setChecked(false);
      break;
   case(1):
      m_useInter_LINEAR->setChecked(true);
      m_doWarpFillCheck->setChecked(false);
      m_doInverseCheck->setChecked(false);
      break;
   case(2):
      m_useInter_CUBIC->setChecked(true);
      m_doWarpFillCheck->setChecked(false);
      m_doInverseCheck->setChecked(false);
      break;
   case(3):
      m_useInter_AREA->setChecked(true);
      m_doWarpFillCheck->setChecked(false);
      m_doInverseCheck->setChecked(false);
      break;
   case(4):
      m_useInter_LANCOZ->setChecked(true);
      m_doWarpFillCheck->setChecked(false);
      m_doInverseCheck->setChecked(false);
      break;

   case(8):
      m_useInter_NN->setChecked(true);
      m_doWarpFillCheck->setChecked(true);
      m_doInverseCheck->setChecked(false);
      break;
   case(9):
      m_useInter_LINEAR->setChecked(true);
      m_doWarpFillCheck->setChecked(true);
      m_doInverseCheck->setChecked(false);
      break;
   case(10):
      m_useInter_CUBIC->setChecked(true);
      m_doWarpFillCheck->setChecked(true);
      m_doInverseCheck->setChecked(false);
      break;
   case(11):
      m_useInter_AREA->setChecked(true);
      m_doWarpFillCheck->setChecked(true);
      m_doInverseCheck->setChecked(false);
      break;
   case(12):
      m_useInter_LANCOZ->setChecked(true);
      m_doWarpFillCheck->setChecked(true);
      m_doInverseCheck->setChecked(false);
      break;

   case(16):
      m_useInter_NN->setChecked(true);
      m_doWarpFillCheck->setChecked(false);
      m_doInverseCheck->setChecked(true);
      break;
   case(17):
      m_useInter_LINEAR->setChecked(true);
      m_doWarpFillCheck->setChecked(false);
      m_doInverseCheck->setChecked(true);
      break;
   case(18):
      m_useInter_CUBIC->setChecked(true);
      m_doWarpFillCheck->setChecked(false);
      m_doInverseCheck->setChecked(true);
      break;
   case(19):
      m_useInter_AREA->setChecked(true);
      m_doWarpFillCheck->setChecked(false);
      m_doInverseCheck->setChecked(true);
      break;
   case(20):
      m_useInter_LANCOZ->setChecked(true);
      m_doWarpFillCheck->setChecked(false);
      m_doInverseCheck->setChecked(true);
      break;

   case(24):
      m_useInter_NN->setChecked(true);
      m_doWarpFillCheck->setChecked(true);
      m_doInverseCheck->setChecked(true);
      break;
   case(25):
      m_useInter_LINEAR->setChecked(true);
      m_doWarpFillCheck->setChecked(true);
      m_doInverseCheck->setChecked(true);
      break;
   case(26):
      m_useInter_CUBIC->setChecked(true);
      m_doWarpFillCheck->setChecked(true);
      m_doInverseCheck->setChecked(true);
      break;
   case(27):
      m_useInter_AREA->setChecked(true);
      m_doWarpFillCheck->setChecked(true);
      m_doInverseCheck->setChecked(true);
      break;
   case(28):
      m_useInter_LANCOZ->setChecked(true);
      m_doWarpFillCheck->setChecked(true);
      m_doInverseCheck->setChecked(true);
      break;
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
void CLogPolarDialog::valueChanged(int)
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
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CLogPolarDialog::valueChanged(double)
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
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CLogPolarDialog::setEditMode(bool val)
{
   m_editMode = val;
   if(m_editMode)
   {
      connect(m_mValSpint, SIGNAL(valueChanged(double)), 
         this, SLOT(valueChanged(double)));

      connect(m_selectPointCombo, SIGNAL(currentIndexChanged(int)), 
         this, SLOT(valueChanged(int)));

      connect(m_doWarpFillCheck, SIGNAL(stateChanged(int)), 
         this, SLOT(valueChanged(int)));

      connect(m_doInverseCheck, SIGNAL(stateChanged(int)), 
         this, SLOT(valueChanged(int)));

      connect(m_useInterGroup, SIGNAL(buttonClicked(int)), 
         this, SLOT(valueChanged(int)));
   }
   else
   {
      disconnect(m_mValSpint, SIGNAL(valueChanged(double)), 
         this, SLOT(valueChanged(double)));

      disconnect(m_selectPointCombo, SIGNAL(currentIndexChanged(int)), 
         this, SLOT(valueChanged(int)));

      disconnect(m_doWarpFillCheck, SIGNAL(stateChanged(int)), 
         this, SLOT(valueChanged(int)));

      disconnect(m_doInverseCheck, SIGNAL(stateChanged(int)), 
         this, SLOT(valueChanged(int)));

      disconnect(m_useInterGroup, SIGNAL(buttonClicked(int)), 
         this, SLOT(valueChanged(int)));
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	updateList
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CLogPolarDialog::updateList()
{
   QMultiHash<QString, QPoint> points = CMetaDataKeeper::getInstance()->metaPoints();
   m_selectPointCombo->clear();
   QHashIterator<QString, QPoint> i(points);
   while(i.hasNext())
   {
      i.next();
      const QString key = i.key();
      const QPoint pt  = i.value();
      m_selectPointCombo->addItem(key, pt);
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	pointTracking
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  20.12.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CLogPolarDialog::pointTracking(const QString &name, const QPoint &pt)
{
   if (!m_editMode)
   {
      return;
   }
   int index = m_selectPointCombo->findText(name);
   if (index < 0)
   {
      return;
   }
   m_selectPointCombo->setItemData(index, pt);
   emit edited();
}
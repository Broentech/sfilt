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
//  \file      thresholdDialog.cpp
//
//  \brief     GUI to define threshold related parameters
//
//  \author    Stian Broen
//
//  \date      12.10.2013
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
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>

// local includes
#include "thresholdDialog.h"

using namespace guiSpace;

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CThreshChannelWidget ctor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  12.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CThreshChannelWidget::CThreshChannelWidget(ThresholdChannel channel, QWidget *parent)
:CImgProcDialogBase(parent),
m_channel(channel),
m_methodCombo(0),
m_typeCombo(0),
m_adaptiveMethodCombo(0),
m_valueSpin(0),
m_maxSpin(0),
m_cSpin(0),
m_blockSizeSpin(0)
{
   initGUI();
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CThresholdDialog dtor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  12.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CThreshChannelWidget::~CThreshChannelWidget()
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
//  \date  12.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CThreshChannelWidget::initGUI()
{
   QLabel *methodLabel = new QLabel("Method", this);
   QLabel *typeLabel = new QLabel("Type", this);
   QLabel *adaptiveTypeLabel = new QLabel("Adaptive Method" , this);
   QLabel *valueLabel = new QLabel("Threshold Value", this);
   QLabel *maxLabel = new QLabel("Max Value", this);
   QLabel *cLabel = new QLabel("C Variable", this);
   QLabel *blockSizeLabel = new QLabel("Block Size", this);

   m_methodCombo = new QComboBox(this);
   m_methodCombo->addItem(thresholdMethodToString(THRESH_METHOD_REGULAR ), QVariant(THRESH_METHOD_REGULAR ));
   m_methodCombo->addItem(thresholdMethodToString(THRESH_METHOD_ADAPTIVE), QVariant(THRESH_METHOD_ADAPTIVE));
   m_methodCombo->setCurrentIndex(m_methodCombo->findData(THRESH_METHOD_REGULAR));

   connect(m_methodCombo, SIGNAL(currentIndexChanged(const QString &)),
      this, SLOT(methodChanged(const QString &)));

   m_typeCombo = new QComboBox(this);
   m_typeCombo->addItem(thresholdTypeToString(THRESH_BINARY), QVariant(THRESH_BINARY));
   m_typeCombo->addItem(thresholdTypeToString(THRESH_BINARY_INV), QVariant(THRESH_BINARY_INV));
   m_typeCombo->addItem(thresholdTypeToString(THRESH_TRUNC), QVariant(THRESH_TRUNC));
   m_typeCombo->addItem(thresholdTypeToString(THRESH_TOZERO), QVariant(THRESH_TOZERO));
   m_typeCombo->addItem(thresholdTypeToString(THRESH_TOZERO_INV), QVariant(THRESH_TOZERO_INV));
   //m_typeCombo->addItem(thresholdTypeToString(THRESH_MASK), QVariant(THRESH_MASK));
   m_typeCombo->addItem(thresholdTypeToString(THRESH_OTSU), QVariant(THRESH_OTSU));
   m_typeCombo->setCurrentIndex(m_typeCombo->findData(THRESH_BINARY));

   connect(m_typeCombo, SIGNAL(currentIndexChanged(const QString &)),
      this, SLOT(typeChanged(const QString &)));

   m_adaptiveMethodCombo = new QComboBox(this);
   m_adaptiveMethodCombo->addItem(thresholdAdmethToString(ADAPTIVE_THRESH_MEAN_C), QVariant(ADAPTIVE_THRESH_MEAN_C));
   m_adaptiveMethodCombo->addItem(thresholdAdmethToString(ADAPTIVE_THRESH_GAUSSIAN_C), QVariant(ADAPTIVE_THRESH_GAUSSIAN_C));
   m_adaptiveMethodCombo->setCurrentIndex(m_adaptiveMethodCombo->findData(ADAPTIVE_THRESH_MEAN_C));
   m_adaptiveMethodCombo->setEnabled(false);

   m_valueSpin = new QDoubleSpinBox(this);
   m_valueSpin->setRange(0.0 , 256.0);
   m_valueSpin->setValue(100.0);

   m_maxSpin = new QDoubleSpinBox(this);
   m_maxSpin->setRange(0.0 , 256.0);
   m_maxSpin->setValue(256.0);

   connect(m_maxSpin, SIGNAL(valueChanged(double)), 
      this, SLOT(maxChanged(double)));

   m_cSpin = new QDoubleSpinBox(this);
   m_cSpin->setRange(-50.0 , 50.0);
   m_cSpin->setValue(5.0);
   m_cSpin->setEnabled(false);

   m_blockSizeSpin = new QSpinBox(this);
   m_blockSizeSpin->setRange(3 , 203);
   m_blockSizeSpin->setValue(3);
   m_blockSizeSpin->setSingleStep(2);
   m_blockSizeSpin->setEnabled(false);

   QGridLayout *wlay = new QGridLayout;
   wlay->addWidget(methodLabel, 0, 0);
   wlay->addWidget(typeLabel, 1, 0);
   wlay->addWidget(adaptiveTypeLabel, 2, 0);
   wlay->addWidget(valueLabel, 3, 0);
   wlay->addWidget(maxLabel, 4, 0);
   wlay->addWidget(cLabel, 5, 0);
   wlay->addWidget(blockSizeLabel, 7, 0);
   wlay->addWidget(m_methodCombo, 0, 1);
   wlay->addWidget(m_typeCombo, 1, 1);
   wlay->addWidget(m_adaptiveMethodCombo, 2, 1);
   wlay->addWidget(m_valueSpin, 3, 1);
   wlay->addWidget(m_maxSpin, 4, 1);
   wlay->addWidget(m_cSpin, 5, 1);
   wlay->addWidget(m_blockSizeSpin, 7, 1);

   this->setLayout(wlay);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	maxChanged
//
//
//  \param  double -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  12.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CThreshChannelWidget::maxChanged(double)
{
   if (0 == m_valueSpin || 0 == m_maxSpin)
   {
      return;
   }
   if (m_valueSpin->value() > m_maxSpin->value())
   {
      m_valueSpin->setValue(m_maxSpin->value());
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	methodChanged
//
//
//  \param  const QString & -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  12.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CThreshChannelWidget::methodChanged(const QString &)
{
   disconnect(m_methodCombo, SIGNAL(currentIndexChanged(const QString &)),
      this, SLOT(methodChanged(const QString &)));

   m_typeCombo->clear();
   m_typeCombo->addItem(thresholdTypeToString(THRESH_BINARY), QVariant(THRESH_BINARY));
   m_typeCombo->addItem(thresholdTypeToString(THRESH_BINARY_INV), QVariant(THRESH_BINARY_INV));
   if(static_cast<ThresholdMethod>(m_methodCombo->itemData(m_methodCombo->currentIndex()).toInt()) == THRESH_METHOD_REGULAR)
   {
      m_adaptiveMethodCombo->setEnabled(false);
      m_valueSpin->setEnabled(true );
      m_cSpin->setEnabled(false);
      m_blockSizeSpin->setEnabled(false);
      m_typeCombo->addItem(thresholdTypeToString(THRESH_TRUNC), QVariant(THRESH_TRUNC));
      m_typeCombo->addItem(thresholdTypeToString(THRESH_TOZERO), QVariant(THRESH_TOZERO));
      m_typeCombo->addItem(thresholdTypeToString(THRESH_TOZERO_INV), QVariant(THRESH_TOZERO_INV));
      //m_typeCombo->addItem(thresholdTypeToString(THRESH_MASK), QVariant(THRESH_MASK));
      m_typeCombo->addItem(thresholdTypeToString(THRESH_OTSU), QVariant(THRESH_OTSU));
   }
   else
   {
      m_adaptiveMethodCombo->setEnabled(true);
      m_valueSpin->setEnabled(false);
      m_cSpin->setEnabled(true);
      m_blockSizeSpin->setEnabled(true);
   }
   connect(m_methodCombo, SIGNAL(currentIndexChanged(const QString &)),
      this, SLOT(methodChanged(const QString &)));
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
//  \date  12.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CThreshChannelWidget::typeChanged(const QString &)
{
   if(static_cast<ThresholdType>(m_typeCombo->itemData(m_typeCombo->currentIndex()).toInt()) == THRESH_OTSU)
   {
      m_valueSpin->setEnabled(false);
   }
   else
   {
      m_valueSpin->setEnabled(true);
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	getData
//
//
//  \param  N/A
//
//  \return CProcTask_Thresh*
//    
//  \author Stian Broen 
//
//  \date  12.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_Thresh* CThreshChannelWidget::getData() const
{
   return new CProcTask_Thresh(
      m_channel,
      static_cast<ThresholdMethod>(m_methodCombo->itemData(m_methodCombo->currentIndex()).toInt()),
      static_cast<ThresholdType>(m_typeCombo->itemData(m_typeCombo->currentIndex()).toInt()),
      static_cast<ThresholdAdaptiveMethod>(m_adaptiveMethodCombo->itemData(m_adaptiveMethodCombo->currentIndex()).toInt()),
      m_valueSpin->value(),
      m_maxSpin->value(),
      m_cSpin->value(),
      m_blockSizeSpin->value());
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	setData
//
//
//  \param  const QString &summary
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  12.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CThreshChannelWidget::setData(const QString &summary)
{
   CProcTask_Thresh data(summary);
   m_methodCombo->setCurrentIndex(m_methodCombo->findData(data.method()));
   m_typeCombo->setCurrentIndex(m_typeCombo->findData(data.type()));
   m_adaptiveMethodCombo->setCurrentIndex(m_adaptiveMethodCombo->findData(data.adaptiveMethod()));
   m_valueSpin->setValue(data.thresholdValue());
   m_maxSpin->setValue(data.maxValue());
   m_cSpin->setValue(data.ad_c());
   m_blockSizeSpin->setValue(data.blockSize());
   methodChanged("");
   typeChanged("");
   maxChanged(0.0);
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
//  \date  12.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CThreshChannelWidget::setEditMode(bool val)
{
   m_editMode = val;
   if(m_editMode)
   {
      connect(m_methodCombo, SIGNAL(currentIndexChanged(const QString &)), 
         this, SLOT(wedited(const QString &)));

      connect(m_typeCombo, SIGNAL(currentIndexChanged(const QString &)), 
         this, SLOT(wedited(const QString &)));

      connect(m_adaptiveMethodCombo, SIGNAL(currentIndexChanged(const QString &)), 
         this, SLOT(wedited(const QString &)));

      connect(m_valueSpin, SIGNAL(valueChanged(double)), 
         this, SLOT(wedited(double)));

      connect(m_maxSpin, SIGNAL(valueChanged(double)), 
         this, SLOT(wedited(double)));

      connect(m_cSpin, SIGNAL(valueChanged(double)), 
         this, SLOT(wedited(double)));

      connect(m_blockSizeSpin, SIGNAL(valueChanged(int)), 
         this, SLOT(wedited(int)));
   }
   else
   {
      disconnect(m_methodCombo, SIGNAL(currentIndexChanged(const QString &)), 
         this, SLOT(wedited(const QString &)));

      disconnect(m_typeCombo, SIGNAL(currentIndexChanged(const QString &)), 
         this, SLOT(wedited(const QString &)));

      disconnect(m_adaptiveMethodCombo, SIGNAL(currentIndexChanged(const QString &)), 
         this, SLOT(wedited(const QString &)));

      disconnect(m_valueSpin, SIGNAL(valueChanged(double)), 
         this, SLOT(wedited(double)));

      disconnect(m_maxSpin, SIGNAL(valueChanged(double)), 
         this, SLOT(wedited(double)));

      disconnect(m_cSpin, SIGNAL(valueChanged(double)),
         this, SLOT(wedited(double)));

      disconnect(m_blockSizeSpin, SIGNAL(valueChanged(int)), 
         this, SLOT(wedited(int)));
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	wedited
//
//
//  \param  const QString & -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  12.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CThreshChannelWidget::wedited(const QString &)
{
   if (m_editMode)
   {
      emit edited();
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	wedited
//
//
//  \param  double -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  12.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CThreshChannelWidget::wedited(double)
{
   if (m_editMode)
   {
      emit edited();
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	wedited
//
//
//  \param  int -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  12.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CThreshChannelWidget::wedited(int)
{
   if (m_editMode)
   {
      emit edited();
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CThresholdDialog ctor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  12.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CThresholdDialog::CThresholdDialog(QWidget *parent)
:CImgProcDialogBase(parent) ,
//m_channelCombo(0),
m_grey(0)
//m_r(0),
//m_g(0),
//m_b(0),
//m_rgb(0)
{
   initGUI();
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CThresholdDialog dtor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  12.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CThresholdDialog::~CThresholdDialog()
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
//  \date  12.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CThresholdDialog::initGUI()
{
   //QLabel *chanLabel = new QLabel("Channel", this);
   //m_channelCombo = new QComboBox(this);
   //m_channelCombo->addItem(thresholdChannelToString(THRESH_CHANNEL_GREY), QVariant(THRESH_CHANNEL_GREY));
   //m_channelCombo->addItem(thresholdChannelToString(THRESH_CHANNEL_RGB ), QVariant(THRESH_CHANNEL_RGB ));
   //m_channelCombo->setCurrentIndex(m_channelCombo->findData(THRESH_CHANNEL_GREY));

   //connect(m_channelCombo, SIGNAL(currentIndexChanged(const QString &)),
   //   this, SLOT(channelChanged(const QString &)));

   //QHBoxLayout *tlay = new QHBoxLayout;
   //tlay->addWidget(chanLabel);
   //tlay->addWidget(m_channelCombo);

   //QFrame* line = new QFrame();
   //line->setFrameShape(QFrame::HLine);
   //line->setFrameShadow(QFrame::Sunken);

   m_grey = new CThreshChannelWidget(THRESH_CHANNEL_GREY, this);
   //m_r = new CThreshChannelWidget(THRESH_CHANNEL_RED, this);
   //m_g = new CThreshChannelWidget(THRESH_CHANNEL_GREEN, this);
   //m_b = new CThreshChannelWidget(THRESH_CHANNEL_BLUE, this);

   //m_rgb = new QTabWidget(this);
   //m_rgb->addTab(m_r, "RED");
   //m_rgb->addTab(m_g, "GREEN");
   //m_rgb->addTab(m_b, "BLUE");
   //m_rgb->setVisible(false);

   //QHBoxLayout *chanLay = new QHBoxLayout;
   //chanLay->addWidget(m_grey);
   //chanLay->addWidget(m_rgb);
   
   QVBoxLayout *lay = new QVBoxLayout;
   //lay->addLayout(tlay);
   //lay->addWidget(line);
   //lay->addLayout(chanLay);
   lay->addWidget(m_grey);
   this->setLayout(lay);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	channelChanged
//
//
//  \param  const QString &
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  12.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
//void CThresholdDialog::channelChanged(const QString &)
//{
//   if(static_cast<ThresholdChannel>(m_channelCombo->itemData(m_channelCombo->currentIndex()).toInt()) == THRESH_CHANNEL_RGB)
//   {
//      m_rgb->setVisible(true);
//      m_grey->setVisible(false);
//   }
//   else
//   {
//      m_rgb->setVisible(false);
//      m_grey->setVisible(true);
//   }
//}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	getData
//
//
//  \param  N/A
//
//  \return CProcTask_Thresh*
//    
//  \author Stian Broen 
//
//  \date  12.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CProcTask_Thresh* CThresholdDialog::getData() const
{
   //if(static_cast<ThresholdChannel>(m_channelCombo->itemData(m_channelCombo->currentIndex()).toInt()) == THRESH_CHANNEL_RGB)
   //{
   //   CProcTask_Thresh *ret = new CProcTask_Thresh;
   //   ret->setChannel(THRESH_CHANNEL_RGB);
   //   CProcTask_Thresh *_r = m_r->getData();
   //   CProcTask_Thresh *_g = m_g->getData();
   //   CProcTask_Thresh *_b = m_b->getData();
   //   ret->setChild(THRESH_CHANNEL_RED, _r->summary());
   //   ret->setChild(THRESH_CHANNEL_GREEN, _g->summary());
   //   ret->setChild(THRESH_CHANNEL_BLUE, _b->summary());
   //   delete _r;
   //   delete _g;
   //   delete _b;
   //   return ret;
   //}
   //else if (static_cast<ThresholdChannel>(m_channelCombo->itemData(m_channelCombo->currentIndex()).toInt()) == THRESH_CHANNEL_GREY)
   //{
      return m_grey->getData();
   //}
   //else
   //{
   //   return 0;
   //}
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
//  \date  12.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CThresholdDialog::setData(const QString &summary)
{
   //CProcTask_Thresh data(summary);
   //if(data.channel() == THRESH_CHANNEL_GREY)
   //{
   //   m_channelCombo->setCurrentIndex(m_channelCombo->findData(THRESH_CHANNEL_GREY));
      m_grey->setData(summary);
   /*}
   else if(data.channel() == THRESH_CHANNEL_RGB)
   {
      m_channelCombo->setCurrentIndex(m_channelCombo->findData(THRESH_CHANNEL_RGB));
      QMap<ThresholdChannel, QString> children = data.children();
      QMapIterator<ThresholdChannel, QString> i(children);
      while(i.hasNext())
      {
         i.next();
         const QString chanSum = i.value();
         CProcTask_Thresh chanData(chanSum);
         if (chanData.channel() == THRESH_CHANNEL_RED)
         {
            m_r->setData(chanSum);
         }
         else if (chanData.channel() == THRESH_CHANNEL_GREEN)
         {
            m_g->setData(chanSum);
         }
         else if (chanData.channel() == THRESH_CHANNEL_BLUE)
         {
            m_b->setData(chanSum);
         }
      }
   }*/
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
//  \date  12.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CThresholdDialog::setEditMode(bool val)
{
   m_editMode = val;
   m_grey->setEditMode(m_editMode);
   //m_r->setEditMode(m_editMode);
   //m_g->setEditMode(m_editMode);
   //m_b->setEditMode(m_editMode);
   if(m_editMode)
   {
      //connect(m_channelCombo, SIGNAL(currentIndexChanged(const QString &)), 
      //   this, SLOT(wedited(const QString &)));

      connect(m_grey, SIGNAL(edited()), 
         this, SIGNAL(edited()));

      //connect(m_r, SIGNAL(edited()), 
      //   this, SIGNAL(edited()));

      //connect(m_g, SIGNAL(edited()), 
      //   this, SIGNAL(edited()));

      //connect(m_b, SIGNAL(edited()), 
      //   this, SIGNAL(edited()));
   }
   else
   {
      //disconnect(m_channelCombo, SIGNAL(currentIndexChanged(const QString &)), 
      //   this, SLOT(wedited(const QString &)));

      disconnect(m_grey, SIGNAL(edited()), 
         this, SIGNAL(edited()));

      //disconnect(m_r, SIGNAL(edited()), 
      //   this, SIGNAL(edited()));

      //disconnect(m_g, SIGNAL(edited()), 
      //   this, SIGNAL(edited()));

      //disconnect(m_b, SIGNAL(edited()), 
      //   this, SIGNAL(edited()));
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	wedited
//
//
//  \param  const QString & -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  12.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
void CThresholdDialog::wedited(const QString &)
{
   if (m_editMode)
   {
      emit edited();
   }
}
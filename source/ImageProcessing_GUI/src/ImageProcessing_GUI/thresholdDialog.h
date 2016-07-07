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
//  \file      thresholdDialog.h
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

#ifndef _THRESHOLD_DIALOG_H_
#define _THRESHOLD_DIALOG_H_

// local includes
#include "dialogBase.h"

// solution includes
#include <ImageProcessing/thresh.h>

// Qt forwards
class QComboBox;
class QSpinBox;
class QDoubleSpinBox;
class QTabWidget;

using namespace imageProcessingSpace;
namespace guiSpace {
   
   class CThreshChannelWidget : public CImgProcDialogBase
   {
      Q_OBJECT

   public:
      explicit CThreshChannelWidget(ThresholdChannel channel, QWidget *parent = 0);
      ~CThreshChannelWidget();
      CProcTask_Thresh* getData() const;
      void setData(const QString &summary);
      void setEditMode(bool val);

   private slots:
      void methodChanged(const QString &);
      void typeChanged(const QString &);
      void maxChanged(double);

      void wedited(const QString &);
      void wedited(double);
      void wedited(int);

   private: // functions
      void initGUI();

   private: // members
      ThresholdChannel m_channel; 
      QComboBox *m_methodCombo;
      QComboBox *m_typeCombo;
      QComboBox *m_adaptiveMethodCombo;
      QDoubleSpinBox *m_valueSpin;
      QDoubleSpinBox *m_maxSpin;
      QDoubleSpinBox *m_cSpin;
      QSpinBox *m_blockSizeSpin;
   };
   
   class CThresholdDialog : public CImgProcDialogBase
   {
      Q_OBJECT

   public:
      explicit CThresholdDialog(QWidget *parent = 0);
      ~CThresholdDialog();
      CProcTask_Thresh* getData() const;
      void setData(const QString &summary);
      void setEditMode(bool val);

   private slots:
      //void channelChanged(const QString &);
      void wedited(const QString &);

   private: // functions
      void initGUI();

   private: // members
      //QComboBox *m_channelCombo;
      CThreshChannelWidget *m_grey;
      //CThreshChannelWidget *m_r;
      //CThreshChannelWidget *m_g;
      //CThreshChannelWidget *m_b;
      //QTabWidget *m_rgb;
   };
}

#endif
//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      thresholdDialog.h
//
//  \brief     GUI to define threshold related parameters
//
//  \author    Stian Broen
//
//  \date      12.10.2013
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
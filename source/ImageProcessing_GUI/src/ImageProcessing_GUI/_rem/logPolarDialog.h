//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      logPolarDialog.h
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

#ifndef _LOGPOLAR_DIALOG_H_
#define _LOGPOLAR_DIALOG_H_

// Qt includes
#include <QButtonGroup>
#include <QRadioButton>

// local includes
#include "dialogBase.h"

// solution includes
#include <ImageProcessing/logPolar.h>

// Qt forwards
class QDoubleSpinBox;
class QCheckBox;
class QComboBox;
class QRadioButton;

using namespace imageProcessingSpace;
namespace guiSpace {
   class CLogPolarDialog : public CImgProcDialogBase
   {
      Q_OBJECT

   public:
      explicit CLogPolarDialog(QWidget *parent);
      ~CLogPolarDialog();
      CProcTask_LogPolar* getData() const;
      void setData(const QString &summary);
      void setEditMode(bool val);

   private slots:
      void valueChanged(double);
      void valueChanged(int);
      void updateList();
      void pointTracking(const QString &name, const QPoint &pt);

   private: // functions
      void initGUI();

   private: // members
      QComboBox *m_selectPointCombo;
      QDoubleSpinBox *m_mValSpint;
      QCheckBox *m_doWarpFillCheck;
      QCheckBox *m_doInverseCheck;

      QButtonGroup *m_useInterGroup;
      QRadioButton *m_useInter_NN;
      QRadioButton *m_useInter_LINEAR;
      QRadioButton *m_useInter_CUBIC;
      QRadioButton *m_useInter_AREA;
      QRadioButton *m_useInter_LANCOZ;
   };
}

#endif
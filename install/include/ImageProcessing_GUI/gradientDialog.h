//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      gradientDialog.h
//
//  \brief     GUI to define gradient parameters
//
//  \author    Stian Broen
//
//  \date      13.10.2013
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

#ifndef _GRADIENT_DIALOG_H_
#define _GRADIENT_DIALOG_H_

// local includes
#include "dialogBase.h"

// solution includes
#include <ImageProcessing/gradients.h>

class QComboBox;
class QSpinBox;
class QDoubleSpinBox;

using namespace imageProcessingSpace;
namespace guiSpace {
   class CGradientDialog : public CImgProcDialogBase
   {
      Q_OBJECT

   public:
      explicit CGradientDialog(QWidget *parent = 0);
      ~CGradientDialog();
      CProcTask_Gradients* getData() const;
      void setData(const QString &summary);
      void setEditMode(bool val);

   private: // funcions
      void initGUI();

   private: // members
      QComboBox *m_types;
      QSpinBox *m_order_XSpin;
      QSpinBox *m_order_YSpin;
      QSpinBox *m_apertureSpin;
      QDoubleSpinBox *m_highThresholdSpin;
      QDoubleSpinBox *m_lowThresholdSpin;

   private slots:
      void valueChanged(int);
      void valueChanged(double);
   };
}

#endif
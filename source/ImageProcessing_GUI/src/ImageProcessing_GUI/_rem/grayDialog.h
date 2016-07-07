//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      grayDialog.h
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

#ifndef _GRAY_DIALOG_H_
#define _GRAY_DIALOG_H_

// local includes
#include "dialogBase.h"

// solution includes
#include <ImageProcessing/gray.h>

// Qt forwards
class QComboBox;
class QDoubleSpinBox;

using namespace imageProcessingSpace;
namespace guiSpace {
   class CGrayDialog : public CImgProcDialogBase
   {
      Q_OBJECT

   public:
      explicit CGrayDialog(QWidget *parent = 0);
      ~CGrayDialog();
      CProcTask_Gray* getData() const;
      void setData(const QString &summary);
      void setEditMode(bool val);

   private slots:
      void typeChanged(const QString &);
      void typeEdited(int);
      void valueChanged(double);

   private: // functions
      void initGUI();

   private: // members
      QComboBox *m_typeCombo;
      QDoubleSpinBox *m_lowThreshSpin;
      QDoubleSpinBox *m_highThreshSpin;
      QDoubleSpinBox *m_apertureSpin;
   };
}

#endif
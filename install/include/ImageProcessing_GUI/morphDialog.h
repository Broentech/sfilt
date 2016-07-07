//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      morphDialog.h
//
//  \brief     GUI to define morphology related parameters
//
//  \author    Stian Broen
//
//  \date      01.10.2013
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

#ifndef _MORPH_DIALOG_H_
#define _MORPH_DIALOG_H_

// local includes
#include "dialogBase.h"

// solution includes
#include <ImageProcessing/morph.h>

// Qt forwards
class QComboBox;
class QSpinBox;
class QCheckBox;

using namespace imageProcessingSpace;
namespace guiSpace {
   class CMorphDialog : public CImgProcDialogBase
   {
      Q_OBJECT

   public:
      explicit CMorphDialog(QWidget *parent);
      ~CMorphDialog();
      CProcTask_Morph* getData() const;
      void setData(const QString &summary);
      void setEditMode(bool val);

   private slots:
      void useCustomKernelChanged(int val);
      void typeEdited(int);
      void valueChanged(int);
      void checkAnchors(int);

   private: // functions
      void initGUI();

   private: // members
      QComboBox *m_typeCombo;
      QComboBox *m_shapeCombo;
      QCheckBox *m_useCustomKernel;
      QSpinBox *m_columnsSpin;
      QSpinBox *m_rowsSpin;
      QSpinBox *m_anchorXSpin;
      QSpinBox *m_anchorYSpin;
      QSpinBox *m_iterationsSpin;
   };
}

#endif
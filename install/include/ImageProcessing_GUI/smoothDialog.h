//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      smoothDialog.h
//
//  \brief     GUI to define smoothing parameters
//
//  \author    Stian Broen
//
//  \date      13.09.2013
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

#ifndef _SMOOTH_DIALOG_H_
#define _SMOOTH_DIALOG_H_

// local includes
#include "dialogBase.h"

// solution includes
#include <ImageProcessing/smooth.h>

class QComboBox;
class QSpinBox;
class QDoubleSpinBox;

using namespace imageProcessingSpace;
namespace guiSpace {
   class CSmoothDialog : public CImgProcDialogBase
   {
      Q_OBJECT

   public:
      explicit CSmoothDialog(QWidget *parent = 0);
      ~CSmoothDialog();
      CProcTask_Smooth* getData() const;
      void setData(const QString &summary);
      void setEditMode(bool val);

   private: // funcions
      void initGUI();

   private: // members
      QComboBox *m_types;
      QSpinBox *m_size1;
      QSpinBox *m_size2;
      QDoubleSpinBox *m_sigma1;
      QDoubleSpinBox *m_sigma2;

   private slots:
      void size1changed(int i);
      void size2changed(int i);
      void typeEdited(int);
      void valueChanged(int);
      void valueChanged(double);
   };
}

#endif
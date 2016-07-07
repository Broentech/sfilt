//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      kernelMaker.h
//
//  \brief     GUI to define kernels
//
//  \author    Stian Broen
//
//  \date      01.01.2014
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

#ifndef _KERNELMAKER_DIALOG_H_
#define _KERNELMAKER_DIALOG_H_

// Qt includes
#include <QMap>
#include <QPair>

// local includes
#include "dialogBase.h"

// solution includes
#include <ImageProcessing/kernels.h>

// Qt forwards
class QComboBox;
class QTableWidget;

using namespace imageProcessingSpace;
namespace guiSpace {
   class CKernelDialog : public CImgProcDialogBase
   {
      Q_OBJECT

   public:
      explicit CKernelDialog(QWidget *parent);
      ~CKernelDialog();
      CProcTask_Kernels* getData(KernelType type = KERNEL_UNKNOWN, QVariant::Type vartype = QVariant::Invalid) const;
      void setData(const QString &summary);
      void setEditMode(bool val);

   private slots:
      void valueChanged(int);
      void valueChanged(double);
      void typeComboChanged(int val);
      void valueTypeComboChanged(int val);

   private: // functions
      void initGUI();
      void updateKernel();

   private: // members
      QComboBox *m_typeCombo;
      //QComboBox *m_valueCombo;
      QTableWidget *m_kernel;
      KernelType m_lastType;
      QVariant::Type m_lastVarType;
   };

   QWidget* makeKernelCell(QVariant::Type type);
}

#endif
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
//  \file      kernelMaker.h
//
//  \brief     GUI to define kernels
//
//  \author    Stian Broen
//
//  \date      01.01.2014
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
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
//  \file      morphDialog.h
//
//  \brief     GUI to define morphology related parameters
//
//  \author    Stian Broen
//
//  \date      01.10.2013
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
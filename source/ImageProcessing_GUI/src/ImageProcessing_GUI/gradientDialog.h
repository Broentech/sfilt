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
//  \file      gradientDialog.h
//
//  \brief     GUI to define gradient parameters
//
//  \author    Stian Broen
//
//  \date      13.10.2013
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
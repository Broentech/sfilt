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
//  \file      smoothDialog.h
//
//  \brief     GUI to define smoothing parameters
//
//  \author    Stian Broen
//
//  \date      13.09.2013
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
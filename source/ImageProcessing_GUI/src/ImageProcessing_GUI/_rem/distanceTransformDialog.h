//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      distanceTransformDialog.h
//
//  \brief     GUI to define distance transform related parameters
//
//  \author    Stian Broen
//
//  \date      27.12.2013
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

#ifndef _DISTANCETRANSFORM_DIALOG_H_
#define _DISTANCETRANSFORM_DIALOG_H_

// Qt includes

// local includes
#include "dialogBase.h"

// solution includes
#include <ImageProcessing/distanceTransform.h>

// Qt forwards
class QComboBox;

using namespace imageProcessingSpace;
namespace guiSpace {
   class CDistTransDialog : public CImgProcDialogBase
   {
      Q_OBJECT

   public:
      explicit CDistTransDialog(QWidget *parent);
      ~CDistTransDialog();
      CProcTask_DistTrans* getData() const;
      void setData(const QString &summary);
      void setEditMode(bool val);

   private slots:
      void valueChanged(int);

   private: // functions
      void initGUI();

   private: // members
      QComboBox *m_typeCombo;
      QComboBox *m_maskCombo;
   };
}

#endif
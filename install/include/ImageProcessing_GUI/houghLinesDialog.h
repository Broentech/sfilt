//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      houghLinesDialog.h
//
//  \brief     GUI to define Hough Lines related parameters
//
//  \author    Stian Broen
//
//  \date      28.10.2013
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

#ifndef _HOUGHLINES_DIALOG_H_
#define _HOUGHLINES_DIALOG_H_

// local includes
#include "dialogBase.h"

// solution includes
#include <ImageProcessing/houghLines.h>

// Qt forwards
class QSpinBox;
class QDoubleSpinBox;

using namespace imageProcessingSpace;
namespace guiSpace {
   class CHoughLinesDialog : public CImgProcDialogBase
   {
      Q_OBJECT

   public:
      explicit CHoughLinesDialog(QWidget *parent);
      ~CHoughLinesDialog();
      CProcTask_HoughLines* getData() const;
      void setData(const QString &summary);
      void setEditMode(bool val);

   private slots:
      void valueChanged(double);
      void valueChanged(int);

   private: // functions
      void initGUI();

   private: // members
      QDoubleSpinBox *m_rhoSpin;
      QDoubleSpinBox *m_thetaSpin;
      QSpinBox *m_thresholdSpin;
      QDoubleSpinBox *m_param1Spin;
      QDoubleSpinBox *m_param2Spin;
   };
}

#endif
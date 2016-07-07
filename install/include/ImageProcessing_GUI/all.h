//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      all.h
//
//  \brief     GUI to define all image processing parameters
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

#ifndef _IMAGE_PROC_ALL_GUI_H_
#define _IMAGE_PROC_ALL_GUI_H_

// Qt includes
#include <QDialog>
#include <QMap>
#include <QPair>
#include <QListWidgetItem>
#include <QLabel>
#include <QShowEvent>
#include <QCheckBox>

// Solution includes
#include <ImageProcessing/imgProc.h>

// local includes
#include "smoothDialog.h"
#include "morphDialog.h"
#include "thresholdDialog.h"
#include "gradientDialog.h"
#include "houghLinesDialog.h"
#include "kernelMaker.h"

class QTabWidget;
class QTableWidget;
class QToolButton;
class QPushButton;
class QKeyEvent;

using namespace imageProcessingSpace;

namespace guiSpace {
   class CAllImgProcGUI : public QDialog
   {
      Q_OBJECT

   public:
      explicit CAllImgProcGUI(QWidget *parent = 0);
      ~CAllImgProcGUI();
      void setImage(QImage image);
      bool hasImage() const;
      inline QMap<int , QPair<ImgProcTask ,CProcTaskBase *> > data() const { return m_proctasks; }
      bool processImage(cv::Mat source, cv::Mat &target);
      inline bool hasLines_Hough() const { return (0 != m_imgproc && m_imgproc->hasLines_Hough()); }
      inline QList<QLine> lines_Hough() const { return m_imgproc->lines_Hough(); }

   private slots:
      void addClicked();
      void removeClicked();
      void showClicked();
      void hideClicked();
      void exitEditClicked();
      void cellClicked(int row, int column);
      void procTabChanged(int);
      void transTabChanged(int);
      void smoothEdited();
      void morphEdited();
      void threshEdited();
      void gradientEdited();
      void houghLinesEdited();
      void kernelsEdited(); 
      void okClicked();
      void cancelClicked();

   private: // functions
      void initGUI();
      QWidget* initGUI_processing();
      QWidget* initGUI_transforms();
      void updateTable();
      bool addSmoothing();
      bool addMorph();
      bool addThreshold();
      bool addGradient();
      bool addHoughLines();
      bool addKernels(); 
      void removeSmoothing(const QString &json);
      void removeMorph(const QString &json);
      void removeThreshold(const QString &json);
      void removeGradient(const QString &json);
      void removeHoughLines(const QString &json);
      void removeKernels(const QString &json);
      bool containsTask(const QString &name, const QString &json) const;
      void toggleTask(ImgProcTask task, const QString &json, bool val);
      void toggleTasks(bool val);
      void setEditMode(bool val);
      void redrawPreview();

   protected:
      void keyPressEvent(QKeyEvent *e);
      void showEvent(QShowEvent *e);

   signals:
      void updateProcessing();
      void ok();
      void cancel();
      void previewWasRedrawn();

   private: // members
      QTableWidget *m_table;
      QToolButton *m_add;
      QToolButton *m_remove;
      QToolButton *m_show;
      QToolButton *m_hide;
      QPushButton *m_exitEdit;
      QCheckBox *m_updateSource;
      QTabWidget *m_topTab;
      QTabWidget *m_procTab;
      QTabWidget *m_transTab;
      QTabWidget *m_metaTab;
      CSmoothDialog *m_smooth;
      CMorphDialog *m_morph;
      CThresholdDialog *m_threshold;
      CGradientDialog *m_gradient;
      CHoughLinesDialog *m_houghLines;
      CKernelDialog *m_kernels; 
      QMap<int , QPair<ImgProcTask ,CProcTaskBase *> > m_proctasks;
      QString m_currEditSummary;
      bool m_isEditMode;
      QLabel *m_previewLabel;
      QToolButton *m_ok;
      QToolButton *m_cancel;
      cv::Mat m_copyOfImage;
      CImgProc *m_imgproc;
   };
}

#endif
//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      dialogBase.h
//
//  \brief     Base class for image processing dialogs
//
//  \author    Stian Broen
//
//  \date      09.10.2013
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

#ifndef _IMGPROC_DIALOG_BASE_H_
#define _IMGPROC_DIALOG_BASE_H_

// Qt includes
#include <QWidget>
#include <QListWidgetItem>
#include <QTableWidgetItem>

namespace guiSpace {
   class CImgProcDialogBase : public QWidget
   {
      Q_OBJECT

   public:
      explicit CImgProcDialogBase(QWidget *parent = 0);
      virtual ~CImgProcDialogBase();
      virtual void setEditMode(bool val) = 0;
      virtual void setData(const QString &summary) = 0;

   signals:
      void edited();

   protected:
      bool m_editMode;
   };

   QListWidgetItem* makeListItem(const QString &text, bool isCheckable = false, QIcon *icon = 0, QVariant *val = 0, Qt::Alignment textallignment = Qt::AlignLeft);
   QTableWidgetItem* makeTableItem(const QString &text,
      int &width,
      bool isCheckable = false,
      QIcon *icon = 0,
      const QString &tooltip = "",
      const QVariant &data = QVariant(),
      bool isChecked = false);
}

#endif
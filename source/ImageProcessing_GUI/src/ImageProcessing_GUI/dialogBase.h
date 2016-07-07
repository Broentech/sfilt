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
//  \file      dialogBase.h
//
//  \brief     Base class for image processing dialogs
//
//  \author    Stian Broen
//
//  \date      09.10.2013
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
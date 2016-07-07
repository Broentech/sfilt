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
//  \file      dialogBase.cpp
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

// local includes
#include "dialogBase.h"

using namespace guiSpace;

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CImgProcDialogBase ctor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  09.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CImgProcDialogBase::CImgProcDialogBase(QWidget *parent)
:QWidget(parent),
m_editMode(false)
{

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	CImgProcDialogBase dtor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  09.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
CImgProcDialogBase::~CImgProcDialogBase()
{

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	makeTableItem
//
//
//  \param  const QString &text - The text in the item
//          int &width          - suggestion for a new column width to fit the text
//          bool isCheckable    -
//          QIcon *icon         -
//
//  \return QTableWidgetItem* -
//    
//  \author Stian Broen 
//
//  \date  17.02.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
QTableWidgetItem* guiSpace::makeTableItem(const QString &text,
   int &width,
   bool isCheckable,
   QIcon *icon,
   const QString &tooltip,
   const QVariant &data,
   bool isChecked)
{
   QTableWidgetItem *item = new QTableWidgetItem;
   QFont font("Times", 12, QFont::Light);
   QFontMetrics metr(font);
   width = metr.width(text);
   item->setText(text);
   if (isCheckable)
   {
      if (isChecked)
      {
         item->setCheckState(Qt::Checked);
      }
      else
      {
         item->setCheckState(Qt::Unchecked);
      }
      item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
      width += 35;
   }
   else
   {
      item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
   }

   if (tooltip != "")
   {
      item->setToolTip(tooltip);
   }

   if (!data.isNull())
   {
      item->setData(Qt::UserRole, data);
   }

   item->setTextAlignment(Qt::AlignCenter);
   if (0 != icon)
   {
      item->setIcon(*icon);
      int largestWidth = 0;
      QList<QSize> iconSizes = icon->availableSizes();
      for (int i = 0; i<iconSizes.count(); i++)
      {
         if (iconSizes.at(i).width() > largestWidth)
         {
            largestWidth = iconSizes.at(i).width();
         }
      }
      width += largestWidth;
   }

   if (width < 20)
   {
      width = 20;
   }

   return item;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	makeListItem
//
//
//  \param  const QString &text - The text in the item
//          bool isCheckable    -
//          QIcon *icon         -
//          QVariant *val       -
//
//  \return QListWidgetItem* -
//    
//  \author Stian Broen 
//
//  \date  13.03.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
QListWidgetItem* guiSpace::makeListItem(const QString &text, bool isCheckable, QIcon *icon, QVariant *val, Qt::Alignment textallignment)
{
   QListWidgetItem *item = new QListWidgetItem;
   item->setText(text);
   if (isCheckable)
   {
      item->setCheckState(Qt::Unchecked);
      item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
   }
   else
   {
      item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
   }

   if (0 != icon)
   {
      item->setIcon(*icon);
   }
   if (0 != val)
   {
      item->setData(Qt::UserRole, *val);
   }

   if (textallignment == Qt::AlignLeft || textallignment == Qt::AlignRight || textallignment == Qt::AlignHCenter || textallignment == Qt::AlignJustify)
   {
      item->setTextAlignment(textallignment);
   }
   return item;
}
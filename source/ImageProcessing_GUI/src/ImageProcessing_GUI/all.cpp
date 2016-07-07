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
//  \file      all.cpp
//
//  \brief     GUI to define all image processing parameters
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

// Qt includes
#include <QTabWidget>
#include <QTableWidget>
#include <QToolButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QKeyEvent>
#include <QLabel>
#include <QPainter>

// solution includes
#include <processImage/commonFunctions.h>

// local includes
#include "all.h"

using namespace guiSpace;

CAllImgProcGUI::CAllImgProcGUI(QWidget *parent)
   :QDialog(parent),
   m_table(0),
   m_add(0),
   m_remove(0),
   m_show(0),
   m_hide(0),
   m_exitEdit(0),
   m_updateSource(0),
   m_topTab(0),
   m_procTab(0),
   m_transTab(0),
   m_metaTab(0),
   m_smooth(0),
   m_morph(0),
   m_threshold(0),
   m_gradient(0),
   m_houghLines(0),
   m_kernels(0),
   m_isEditMode(false),
   m_previewLabel(0),
   m_ok(0),
   m_cancel(0),
   m_imgproc(0)
{
   initGUI();
}

CAllImgProcGUI::~CAllImgProcGUI()
{

}

void CAllImgProcGUI::initGUI()
{
   m_topTab = new QTabWidget(this);
   m_topTab->addTab(initGUI_processing(), "Processing");
   m_topTab->addTab(initGUI_transforms(), "Detection");

   m_add = new QToolButton(this);
   m_add->setIcon(QIcon(":/images/plus.png"));
   m_add->setToolTip("Add");
   connect(m_add, SIGNAL(clicked()), this, SLOT(addClicked()));

   m_remove = new QToolButton(this);
   m_remove->setIcon(QIcon(":/images/minus.png"));
   m_remove->setToolTip("Remove");
   connect(m_remove, SIGNAL(clicked()), this, SLOT(removeClicked()));

   m_show = new QToolButton(this);
   m_show->setIcon(QIcon(":/images/show.png"));
   m_show->setToolTip("Show");
   connect(m_show, SIGNAL(clicked()), this, SLOT(showClicked()));

   m_exitEdit = new QPushButton(this);
   m_exitEdit->setText("Exit Editmode");
   connect(m_exitEdit, SIGNAL(clicked()), this, SLOT(exitEditClicked()));
   m_exitEdit->setVisible(false);

   m_updateSource = new QCheckBox(this);
   m_updateSource->setText("Live Update");
   m_updateSource->setChecked(false);
   m_updateSource->setVisible(false);

   m_hide = new QToolButton(this);
   m_hide->setIcon(QIcon(":/images/hide.png"));
   m_hide->setToolTip("Hide");
   connect(m_hide, SIGNAL(clicked()), this, SLOT(hideClicked()));

   QHBoxLayout *buttonlay = new QHBoxLayout;
   buttonlay->addWidget(m_add);
   buttonlay->addWidget(m_remove);
   buttonlay->addWidget(m_show);
   buttonlay->addWidget(m_hide);
   buttonlay->addStretch();
   buttonlay->addWidget(m_exitEdit);
   buttonlay->addWidget(m_updateSource);

   QVBoxLayout *left = new QVBoxLayout;
   left->addWidget(m_topTab);
   left->addLayout(buttonlay);

   m_table = new QTableWidget(this);
   connect(m_table, SIGNAL(cellPressed(int, int)), 
      this, SLOT(cellClicked(int, int)));
   m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
   m_table->setSelectionMode(QAbstractItemView::SingleSelection);
   QVBoxLayout *right = new QVBoxLayout;
   right->addWidget(m_table);

   QVBoxLayout *lay = new QVBoxLayout;
   lay->addLayout(left);
   lay->addLayout(right);

   m_previewLabel = new QLabel(this);

   m_ok = new QToolButton(this);
   m_ok->setIcon(QIcon(":/images/OK.png"));
   m_ok->setIconSize(QSize(32, 32));

   connect(m_ok, SIGNAL(clicked()),
      this, SLOT(okClicked()));

   m_cancel = new QToolButton(this);
   m_cancel->setIcon(QIcon(":/images/NOT_OK.png"));
   m_cancel->setIconSize(QSize(32, 32));

   connect(m_cancel, SIGNAL(clicked()),
      this, SLOT(cancelClicked()));

   QHBoxLayout *exitlay = new QHBoxLayout;
   exitlay->addStretch();
   exitlay->addWidget(m_ok);
   exitlay->addWidget(m_cancel);

   QVBoxLayout *rightLay = new QVBoxLayout;
   rightLay->addWidget(m_previewLabel);
   rightLay->addLayout(exitlay);

   QHBoxLayout *totlay = new QHBoxLayout;
   totlay->addLayout(lay);
   totlay->addLayout(rightLay);
   this->setLayout(totlay);
}

QWidget* CAllImgProcGUI::initGUI_processing()
{
   m_smooth = new CSmoothDialog(this);
   m_morph = new CMorphDialog(this);
   m_threshold = new CThresholdDialog(this);
   m_kernels = new CKernelDialog(this);

   connect(m_smooth, SIGNAL(edited()), 
      this, SLOT(smoothEdited()));

   connect(m_morph, SIGNAL(edited()), 
      this, SLOT(morphEdited()));

   connect(m_threshold, SIGNAL(edited()), 
      this, SLOT(threshEdited()));

   connect(m_kernels, SIGNAL(edited()), 
      this, SLOT(kernelsEdited()));

   m_procTab = new QTabWidget(this);
   m_procTab->setUsesScrollButtons(false);
   connect(m_procTab, SIGNAL(currentChanged(int)), this, SLOT(procTabChanged(int)));
   m_procTab->addTab(m_smooth, imgProcTaskToString(IMGPROC_SMOOTH));
   m_procTab->addTab(m_morph, imgProcTaskToString(IMGPROC_MORPH));
   m_procTab->addTab(m_threshold, imgProcTaskToString(IMGPROC_THRESHOLD));
   m_procTab->addTab(m_kernels, imgProcTaskToString(IMGPROC_CONVOLVE));

   return m_procTab;
}

QWidget* CAllImgProcGUI::initGUI_transforms()
{
   m_gradient = new CGradientDialog(this);

   connect(m_gradient, SIGNAL(edited()), 
      this, SLOT(gradientEdited()));

   m_houghLines = new CHoughLinesDialog(this);

   connect(m_houghLines, SIGNAL(edited()), 
      this, SLOT(houghLinesEdited()));

   m_transTab = new QTabWidget(this);
   m_transTab->setUsesScrollButtons(false);
   m_transTab->addTab(m_gradient, imgProcTaskToString(IMGPROC_GRADIENT));
   m_transTab->addTab(m_houghLines, imgProcTaskToString(IMGPROC_HOUGHLINES));

   connect(m_transTab, SIGNAL(currentChanged(int)), 
      this, SLOT(transTabChanged(int)));

   return m_transTab;
}

void CAllImgProcGUI::addClicked()
{
   bool mustUpdate = false;
   if(m_topTab->tabText(m_topTab->currentIndex()) == "Processing")
   {
      switch(imgProcTaskFromString(m_procTab->tabText(m_procTab->currentIndex())))
      {
      case(IMGPROC_SMOOTH):
         if (addSmoothing())
         {
            mustUpdate = true;
         }
         break;
      case(IMGPROC_MORPH):
         if (addMorph())
         {
            mustUpdate = true;
         }
         break;
      case(IMGPROC_THRESHOLD):
         if (addThreshold())
         {
            mustUpdate = true;
         }
         break;
      case(IMGPROC_CONVOLVE):
         if (addKernels())
         {
            mustUpdate = true;
         }
         break;
      case(IMGPROC_UNKNOWN):
      default:
         return;
      }
   }
   else if(m_topTab->tabText(m_topTab->currentIndex()) == "Detection")
   {
      switch(imgProcTaskFromString(m_transTab->tabText(m_transTab->currentIndex())))
      {
      case(IMGPROC_GRADIENT):
         if (addGradient())
         {
            mustUpdate = true;
         }
         break;
      case(IMGPROC_HOUGHLINES):
         if (addHoughLines())
         {
            mustUpdate = true;
         }
         break;
      case(IMGPROC_UNKNOWN):
      default:
         return;
      }
   }
   if(mustUpdate)
   {
      updateTable();
      redrawPreview();
      emit updateProcessing();
   }
}

void CAllImgProcGUI::removeClicked()
{
   for(int i=0; i<m_table->rowCount(); i++)
   {
      QTableWidgetItem *nameitem = m_table->item(i, 0);
      if (0 == nameitem || nameitem->checkState() != Qt::Checked)
      {
         continue;
      }
      QTableWidgetItem *summitem = m_table->item(i, 1);
      if (0 == summitem)
      {
         continue;
      }
      ImgProcTask task = imgProcTaskFromString(nameitem->text());
      QString json = summitem->data(Qt::UserRole).toString();
      switch(task)
      {
      case(IMGPROC_SMOOTH):
         removeSmoothing(json);
         break;
      case(IMGPROC_MORPH):
         removeMorph(json);
         break;
      case(IMGPROC_THRESHOLD):
         removeThreshold(json);
         break;
      case(IMGPROC_GRADIENT):
         removeGradient(json);
         break;
      case(IMGPROC_HOUGHLINES):
         removeHoughLines(json);
         break;
      case(IMGPROC_CONVOLVE):
         removeKernels(json);
         break;
      case(IMGPROC_UNKNOWN):
      default:
         continue;
      }
   }
   emit updateProcessing();
   updateTable();
   redrawPreview();
}

void CAllImgProcGUI::updateTable()
{
   QHash<int, bool> checkCpy;
   for(int i=0; i<m_table->rowCount(); i++)
   {
      if (m_table->item(i, 0)->checkState() == Qt::Checked)
      {
         checkCpy.insert(i, true);
      }
      else
      {
         checkCpy.insert(i, false);
      }
   }

   m_table->clear();
   int w = 0;
   int row_index = 0;
   m_table->setColumnCount(3);
   m_table->setRowCount(m_proctasks.size());
   m_table->setHorizontalHeaderItem(0, makeTableItem("Effect", w));
   m_table->setHorizontalHeaderItem(1, makeTableItem("Type", w));
   m_table->setHorizontalHeaderItem(2, makeTableItem("", w));
   m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
   QMapIterator<int , QPair<ImgProcTask ,CProcTaskBase *> > i(m_proctasks);
   while(i.hasNext())
   {
      i.next();
      QPair<ImgProcTask ,CProcTaskBase *> val = i.value();
      QString name = imgProcTaskToString(val.first);
      QString json;
      QString id;
      bool isActive = false;
      CProcTaskBase *obj = 0;
      ImgProcTask task = val.first;
      switch(task)
      {
      case(IMGPROC_SMOOTH):
         obj = dynamic_cast<CProcTask_Smooth *>(val.second);
         if (0 == obj)
         {
            continue;
         }
         id = obj->id();
         isActive = obj->isActive();
         json = CProcTask_Smooth_to_JSON(*dynamic_cast<CProcTask_Smooth *>(obj));
         break;

      case(IMGPROC_MORPH):
         obj = dynamic_cast<CProcTask_Morph *>(val.second);
         if (0 == obj)
         {
            continue;
         }
         id = obj->id();
         isActive = obj->isActive();
         json = CProcTask_Morph_to_JSON(*dynamic_cast<CProcTask_Morph *>(obj));
         break;

      case(IMGPROC_THRESHOLD):
         obj = dynamic_cast<CProcTask_Thresh *>(val.second);
         if (0 == obj)
         {
            continue;
         }
         id = obj->id();
         isActive = obj->isActive();
         json = CProcTask_Thresh_to_JSON(*dynamic_cast<CProcTask_Thresh *>(obj));
         break;

      case(IMGPROC_GRADIENT):
         obj = dynamic_cast<CProcTask_Gradients *>(val.second);
         if (0 == obj)
         {
            continue;
         }
         id = obj->id();
         isActive = obj->isActive();
         json = CProcTask_Gradients_to_JSON(*dynamic_cast<CProcTask_Gradients *>(obj));
         break;

      case(IMGPROC_HOUGHLINES):
         obj = dynamic_cast<CProcTask_HoughLines *>(val.second);
         if (0 == obj)
         {
            continue;
         }
         id = obj->id();
         isActive = obj->isActive();
         json = CProcTask_HoughLines_to_JSON(*dynamic_cast<CProcTask_HoughLines *>(obj));
         break;

      case(IMGPROC_CONVOLVE):
         obj = dynamic_cast<CProcTask_Kernels *>(val.second);
         if (0 == obj)
         {
            continue;
         }
         id = obj->id();
         isActive = obj->isActive();
         json = CProcTask_Kernels_to_JSON(*dynamic_cast<CProcTask_Kernels *>(obj));
         break;

      case(IMGPROC_UNKNOWN):
      default:
         continue;
      }
      
      QTableWidgetItem *typeItem = makeTableItem
         (name,  // make a table item that has this text 
         w,  // return the width of the item
         true,  // make it checkable
         0,  // give it no icon
         "Effect",  // and this tooltip
         static_cast<int>(task),  // and this data
         checkCpy.value(row_index)); // and this checkstate

      m_table->setItem(row_index, 0, typeItem);
      
      QTableWidgetItem *summItem = makeTableItem(
         id,  // make a table item that has this text 
         w,  // return the width of the item
         false,  // make it uncheckable
         0,  // give it no icon
         json,  // and this tooltip
         json); // and this user data 
      m_table->setItem(row_index, 1, summItem);

      QTableWidgetItem *activityItem = 0;
      if (isActive)
      {
         activityItem = makeTableItem(
            "",  // make a table item that has this text 
            w,  // return the width of the item
            false,  // make it uncheckable
            &QIcon(":/images/show.png"),  // give it this icon
            "Active",  // and this tooltip
            true); // and this user data 
      }
      else
      {
         activityItem = makeTableItem("",  // make a table item that has this text 
            w,  // return the width of the item
            false,  // make it uncheckable
            &QIcon(":/images/hide.png"),  // give it this icon
            "Hidden",  // and this tooltip
            false); // and this user data 
      }

      m_table->setItem(row_index, 2, activityItem);

      ++row_index;
   }
}

bool CAllImgProcGUI::containsTask(const QString &name, const QString &json) const
{
   QMapIterator<int , QPair<ImgProcTask ,CProcTaskBase *> > i(m_proctasks);
   while(i.hasNext())
   {
      i.next();
      ImgProcTask task = i.value().first;
      if (imgProcTaskToString(task) != name)
      {
         continue;
      }
      CProcTaskBase *obj = i.value().second;
      if (0 == obj)
      {
         continue;
      }
      switch(task)
      {

      case(IMGPROC_SMOOTH):
         obj = dynamic_cast<CProcTask_Smooth *>(obj);
         if (0 == obj)
         {
            continue;
         }
         if (CProcTask_Smooth_to_JSON(*dynamic_cast<CProcTask_Smooth *>(obj)) == json)
         {
            return true;
         }
         break;

      case(IMGPROC_GRAYSCALE):
         // allow only 1 grayscale operation
         return true;
      case(IMGPROC_MORPH):
         obj = dynamic_cast<CProcTask_Morph *>(obj);
         if (0 == obj)
         {
            continue;
         }
         if (CProcTask_Morph_to_JSON(*dynamic_cast<CProcTask_Morph *>(obj)) == json)
         {
            return true;
         }
         break;
      
      case(IMGPROC_THRESHOLD):
         obj = dynamic_cast<CProcTask_Thresh *>(obj);
         if (0 == obj)
         {
            continue;
         }
         if (CProcTask_Thresh_to_JSON(*dynamic_cast<CProcTask_Thresh *>(obj)) == json)
         {
            return true;
         }
         break;

      case(IMGPROC_GRADIENT):
         obj = dynamic_cast<CProcTask_Gradients *>(obj);
         if (0 == obj)
         {
            continue;
         }
         if (CProcTask_Gradients_to_JSON(*dynamic_cast<CProcTask_Gradients *>(obj)) == json)
         {
            return true;
         }
         break;

      case(IMGPROC_HOUGHLINES):
         obj = dynamic_cast<CProcTask_HoughLines *>(obj);
         if (0 == obj)
         {
            continue;
         }
         if (CProcTask_HoughLines_to_JSON(*dynamic_cast<CProcTask_HoughLines *>(obj)) == json)
         {
            return true;
         }
         break;

      case(IMGPROC_CONVOLVE):
         obj = dynamic_cast<CProcTask_Kernels *>(obj);
         if (0 == obj)
         {
            continue;
         }
         if (CProcTask_Kernels_to_JSON(*dynamic_cast<CProcTask_Kernels *>(obj)) == json)
         {
            return true;
         }
         break;

      case(IMGPROC_UNKNOWN):
      default:
         return false;
      }
   }
   return false;
}

bool CAllImgProcGUI::addSmoothing()
{
   if (0 == m_smooth)
   {
      return false;
   }
   CProcTask_Smooth *data = m_smooth->getData();
   if (0 == data)
   {
      return false;
   }
   if (containsTask(imgProcTaskToString(IMGPROC_SMOOTH), CProcTask_Smooth_to_JSON(*data)))
   {
      return false;
   }
   m_proctasks.insert(m_proctasks.size(), QPair<ImgProcTask ,CProcTaskBase *>(IMGPROC_SMOOTH, data));
   return true;
}

void CAllImgProcGUI::removeSmoothing(const QString &json)
{
   QMutableMapIterator<int , QPair<ImgProcTask ,CProcTaskBase *> > i(m_proctasks);
   while(i.hasNext())
   {
      i.next();
      if (i.value().first != IMGPROC_SMOOTH)
      {
         continue;
      }
      CProcTask_Smooth *params = dynamic_cast<CProcTask_Smooth *>(i.value().second);
      if (0 == params)
      {
         continue;
      }
      if (CProcTask_Smooth_to_JSON(*params) == json)
      {
         i.remove();
      }
   }
}

bool CAllImgProcGUI::addMorph()
{
   if (0 == m_morph)
   {
      return false;
   }
   CProcTask_Morph *data = m_morph->getData();
   if (0 == data)
   {
      return false;
   }
   if (containsTask(imgProcTaskToString(IMGPROC_MORPH), CProcTask_Morph_to_JSON(*data)))
   {
      return false;
   }
   m_proctasks.insert(m_proctasks.size(), QPair<ImgProcTask ,CProcTaskBase *>(IMGPROC_MORPH, data));
   return true;
}

void CAllImgProcGUI::removeMorph(const QString &json)
{
   QMutableMapIterator<int , QPair<ImgProcTask ,CProcTaskBase *> > i(m_proctasks);
   while(i.hasNext())
   {
      i.next();
      if (i.value().first != IMGPROC_MORPH)
      {
         continue;
      }
      CProcTask_Morph *params = dynamic_cast<CProcTask_Morph *>(i.value().second);
      if (0 == params)
      {
         continue;
      }
      if (CProcTask_Morph_to_JSON(*params) == json)
      {
         i.remove();
      }
   }
}

bool CAllImgProcGUI::addThreshold()
{
   if (0 == m_threshold)
   {
      return false;
   }
   CProcTask_Thresh *data = m_threshold->getData();
   if (0 == data)
   {
      return false;
   }
   if (containsTask(imgProcTaskToString(IMGPROC_THRESHOLD), CProcTask_Thresh_to_JSON(*data)))
   {
      return false;
   }
   m_proctasks.insert(m_proctasks.size(), QPair<ImgProcTask ,CProcTaskBase *>(IMGPROC_THRESHOLD, data));
   return true;
}

void CAllImgProcGUI::removeThreshold(const QString &json)
{
   QMutableMapIterator<int , QPair<ImgProcTask ,CProcTaskBase *> > i(m_proctasks);
   while(i.hasNext())
   {
      i.next();
      if (i.value().first != IMGPROC_THRESHOLD)
      {
         continue;
      }
      CProcTask_Thresh *params = dynamic_cast<CProcTask_Thresh *>(i.value().second);
      if (0 == params)
      {
         continue;
      }
      if (CProcTask_Thresh_to_JSON(*params) == json)
      {
         i.remove();
      }
   }
}

bool CAllImgProcGUI::addGradient()
{
   if (0 == m_gradient)
   {
      return false;
   }
   CProcTask_Gradients *data = m_gradient->getData();
   if (0 == data)
   {
      return false;
   }
   if (containsTask(imgProcTaskToString(IMGPROC_GRADIENT), CProcTask_Gradients_to_JSON(*data)))
   {
      return false;
   }
   m_proctasks.insert(m_proctasks.size(), QPair<ImgProcTask ,CProcTaskBase *>(IMGPROC_GRADIENT, data));
   return true;
}

void CAllImgProcGUI::removeGradient(const QString &json)
{
   QMutableMapIterator<int , QPair<ImgProcTask ,CProcTaskBase *> > i(m_proctasks);
   while(i.hasNext())
   {
      i.next();
      if (i.value().first != IMGPROC_GRADIENT)
      {
         continue;
      }
      CProcTask_Gradients *params = dynamic_cast<CProcTask_Gradients *>(i.value().second);
      if (0 == params)
      {
         continue;
      }
      if (CProcTask_Gradients_to_JSON(*params) == json)
      {
         i.remove();
      }
   }
}

bool CAllImgProcGUI::addHoughLines()
{
   if (0 == m_houghLines)
   {
      return false;
   }
   CProcTask_HoughLines *data = m_houghLines->getData();
   if (0 == data)
   {
      return false;
   }
   if (containsTask(imgProcTaskToString(IMGPROC_HOUGHLINES), CProcTask_HoughLines_to_JSON(*data)))
   {
      return false;
   }
   m_proctasks.insert(m_proctasks.size(), QPair<ImgProcTask ,CProcTaskBase *>(IMGPROC_HOUGHLINES, data));
   return true;
}

void CAllImgProcGUI::removeHoughLines(const QString &json)
{
   QMutableMapIterator<int , QPair<ImgProcTask ,CProcTaskBase *> > i(m_proctasks);
   while(i.hasNext())
   {
      i.next();
      if (i.value().first != IMGPROC_HOUGHLINES)
      {
         continue;
      }
      CProcTask_HoughLines *params = dynamic_cast<CProcTask_HoughLines *>(i.value().second);
      if (0 == params)
      {
         continue;
      }
      if (CProcTask_HoughLines_to_JSON(*params) == json)
      {
         i.remove();
      }
   }
}

bool CAllImgProcGUI::addKernels()
{
   if (0 == m_kernels)
   {
      return false;
   }

   CProcTask_Kernels *data = m_kernels->getData();
   if (0 == data)
   {
      return false;
   }
   if (containsTask(imgProcTaskToString(IMGPROC_CONVOLVE), CProcTask_Kernels_to_JSON(*data)))
   {
      return false;
   }
   m_proctasks.insert(m_proctasks.size(), QPair<ImgProcTask ,CProcTaskBase *>(IMGPROC_CONVOLVE, data));
   return true;
}

void CAllImgProcGUI::removeKernels(const QString &json)
{
   QMutableMapIterator<int , QPair<ImgProcTask ,CProcTaskBase *> > i(m_proctasks);
   while(i.hasNext())
   {
      i.next();
      if (i.value().first != IMGPROC_CONVOLVE)
      {
         continue;
      }
      CProcTask_Kernels *params = dynamic_cast<CProcTask_Kernels *>(i.value().second);
      if (0 == params)
      {
         continue;
      }
      if (CProcTask_Kernels_to_JSON(*params) == json)
      {
         i.remove();
      }
   }
}

void CAllImgProcGUI::showClicked()
{
   toggleTasks(true);
}

void CAllImgProcGUI::hideClicked()
{
   toggleTasks(false);
}

void CAllImgProcGUI::toggleTasks(bool val)
{
   bool mustUpdate = false;
   for(int i=0; i<m_table->rowCount(); i++)
   {
      if(m_table->item(i, 0)->checkState() == Qt::Checked)
      {
         ImgProcTask task = static_cast<ImgProcTask>(m_table->item(i, 0)->data(Qt::UserRole).toInt());
         QString json =  m_table->item(i, 1)->data(Qt::UserRole).toString();
         toggleTask(task, json, val);
         mustUpdate = true;
      }
   }
   if (mustUpdate)
   {
      updateTable();
      redrawPreview();
   }
}

void CAllImgProcGUI::toggleTask(ImgProcTask task, const QString &json, bool val)
{
   QMapIterator<int , QPair<ImgProcTask ,CProcTaskBase *> > i(m_proctasks);
   while(i.hasNext())
   {
      i.next();
      QPair<ImgProcTask ,CProcTaskBase *> p = i.value();
      if (p.first != task || p.second->json() != json)
      {
         continue;
      }
      p.second->setActive(val);
   }
}

void CAllImgProcGUI::cellClicked(int row, int column)
{
   if (row >= m_table->rowCount() || column >= m_table->columnCount())
   {
      return;
   }
   ImgProcTask task = static_cast<ImgProcTask>(m_table->item(row, 0)->data(Qt::UserRole).toInt());
   m_currEditSummary =  m_table->item(row, 1)->data(Qt::UserRole).toString();
   switch(task)
   {
   case(IMGPROC_SMOOTH):
      m_topTab->setCurrentIndex(0);
      m_procTab->setCurrentIndex(0);
      m_smooth->setData(m_currEditSummary);
      m_smooth->setEditMode(true);
      break;
   case(IMGPROC_MORPH):
      m_topTab->setCurrentIndex(0);
      m_procTab->setCurrentIndex(1);
      m_morph->setData(m_currEditSummary);
      m_morph->setEditMode(true);
      break;
   case(IMGPROC_THRESHOLD):
      m_topTab->setCurrentIndex(0);
      m_procTab->setCurrentIndex(2);
      m_threshold->setData(m_currEditSummary);
      m_threshold->setEditMode(true);
      break;
   case(IMGPROC_CONVOLVE):
      m_topTab->setCurrentIndex(0);
      m_transTab->setCurrentIndex(3);
      m_kernels->setData(m_currEditSummary);
      m_kernels->setEditMode(true);
      break;
   case(IMGPROC_GRADIENT):
      m_topTab->setCurrentIndex(1);
      m_transTab->setCurrentIndex(0);
      m_gradient->setData(m_currEditSummary);
      m_gradient->setEditMode(true);
      break;
   case(IMGPROC_HOUGHLINES):
      m_topTab->setCurrentIndex(1);
      m_transTab->setCurrentIndex(1);
      m_houghLines->setData(m_currEditSummary);
      m_houghLines->setEditMode(true);
      break;

   default:
      return;
   }
   setEditMode(true);
}

void CAllImgProcGUI::smoothEdited()
{
   CProcTask_Smooth *data = m_smooth->getData();
   QMutableMapIterator<int , QPair<ImgProcTask ,CProcTaskBase *> > i(m_proctasks);
   while(i.hasNext())
   {
      i.next();
      QPair<ImgProcTask ,CProcTaskBase *> p = i.value();
      if (p.second->json() != m_currEditSummary)
      {
         continue;
      }
      delete p.second;
      p.second = data;
      i.setValue(p);
   }
   m_currEditSummary = data->json();
   emit updateProcessing();
   updateTable();
   redrawPreview();
}

void CAllImgProcGUI::morphEdited()
{
   CProcTask_Morph *data = m_morph->getData();
   QMutableMapIterator<int , QPair<ImgProcTask ,CProcTaskBase *> > i(m_proctasks);
   while(i.hasNext())
   {
      i.next();
      QPair<ImgProcTask ,CProcTaskBase *> p = i.value();
      if (p.second->json() != m_currEditSummary)
      {
         continue;
      }
      delete p.second;
      p.second = data;
      i.setValue(p);
   }
   m_currEditSummary = data->json();
   emit updateProcessing();
   updateTable();
   redrawPreview();
}

void CAllImgProcGUI::threshEdited()
{
   CProcTask_Thresh *data = m_threshold->getData();
   QMutableMapIterator<int , QPair<ImgProcTask ,CProcTaskBase *> > i(m_proctasks);
   while(i.hasNext())
   {
      i.next();
      QPair<ImgProcTask ,CProcTaskBase *> p = i.value();
      if (p.second->json() != m_currEditSummary)
      {
         continue;
      }
      delete p.second;
      p.second = data;
      i.setValue(p);
   }
   m_currEditSummary = data->json();
   emit updateProcessing();
   updateTable();
   redrawPreview();
}

void CAllImgProcGUI::gradientEdited()
{
   CProcTask_Gradients *data = m_gradient->getData();
   QMutableMapIterator<int , QPair<ImgProcTask ,CProcTaskBase *> > i(m_proctasks);
   while(i.hasNext())
   {
      i.next();
      QPair<ImgProcTask ,CProcTaskBase *> p = i.value();
      if (p.second->json() != m_currEditSummary)
      {
         continue;
      }
      delete p.second;
      p.second = data;
      i.setValue(p);
   }
   m_currEditSummary = data->json();
   emit updateProcessing();
   updateTable();
   redrawPreview();
}

void CAllImgProcGUI::houghLinesEdited()
{
   CProcTask_HoughLines *data = m_houghLines->getData();
   QMutableMapIterator<int , QPair<ImgProcTask ,CProcTaskBase *> > i(m_proctasks);
   while(i.hasNext())
   {
      i.next();
      QPair<ImgProcTask ,CProcTaskBase *> p = i.value();
      if (p.second->json() != m_currEditSummary)
      {
         continue;
      }
      delete p.second;
      p.second = data;
      i.setValue(p);
   }
   m_currEditSummary = data->json();
   emit updateProcessing();
   updateTable();
   redrawPreview();
}

void CAllImgProcGUI::kernelsEdited()
{
   CProcTask_Kernels *data = m_kernels->getData();
   QMutableMapIterator<int , QPair<ImgProcTask ,CProcTaskBase *> > i(m_proctasks);
   while(i.hasNext())
   {
      i.next();
      QPair<ImgProcTask ,CProcTaskBase *> p = i.value();
      if (p.second->json() != m_currEditSummary)
      {
         continue;
      }
      delete p.second;
      p.second = data;
      i.setValue(p);
   }
   m_currEditSummary = data->json();
   emit updateProcessing();
   updateTable();
   redrawPreview();
}

void CAllImgProcGUI::procTabChanged(int)
{
   setEditMode(false);
}

void CAllImgProcGUI::transTabChanged(int)
{
   setEditMode(false);
}

void CAllImgProcGUI::setEditMode(bool val)
{
   if (0 == m_smooth ||
      0 == m_morph ||
      0 == m_threshold ||
      0 == m_add ||
      0 == m_remove ||
      0 == m_show ||
      0 == m_hide ||
      0 == m_gradient ||
      0 == m_houghLines ||
      0 == m_kernels)
   {
      return;
   }
   m_isEditMode = val;
   if(!m_isEditMode)
   {
      m_exitEdit->setVisible(false);
      m_updateSource->setVisible(false);
      m_smooth->setEditMode(false);
      m_morph->setEditMode(false);
      m_threshold->setEditMode(false);
      m_gradient->setEditMode(false);
      m_houghLines->setEditMode(false);
      m_kernels->setEditMode(false);
      m_add->setEnabled(true);
      m_remove->setEnabled(true);
      m_show->setEnabled(true);
      m_hide->setEnabled(true);
   }
   else
   {
      m_updateSource->setVisible(true);
      m_exitEdit->setVisible(true);
      m_add->setEnabled(false);
      m_remove->setEnabled(false);
      m_show->setEnabled(false);
      m_hide->setEnabled(false);
   }
}

void CAllImgProcGUI::keyPressEvent(QKeyEvent *e)
{
   if(m_isEditMode)
   {
      if (e->key() == Qt::Key_Escape)
      {
         setEditMode(false);
      }
   }
   QDialog::keyPressEvent(e);
}

void CAllImgProcGUI::showEvent(QShowEvent *e)
{
   redrawPreview();
   QDialog::showEvent(e);
}

void CAllImgProcGUI::exitEditClicked()
{
   setEditMode(false);
}

void CAllImgProcGUI::setImage(QImage image)
{
   QPixmap tolabel(600, 400);
   QPainter p(&tolabel);

   QRect drawRect;
   drawRect.setWidth(tolabel.width());
   drawRect.setHeight(tolabel.width() * qRound(
      static_cast<qreal>(image.rect().height()) /
      static_cast<qreal>(image.rect().width())
      ));

   if (drawRect.height() > tolabel.height())
   {
      drawRect.setHeight(tolabel.height());
      drawRect.setWidth(tolabel.height() * qRound(
         static_cast<qreal>(image.rect().width()) /
         static_cast<qreal>(image.rect().height())
         ));
   }

   int dx = 0;
   int dy = 0;
   if (drawRect.height() < tolabel.height())
   {
      dy = qRound(static_cast<qreal>(tolabel.height() - drawRect.height()) / 2.0);
   }
   if (drawRect.width() < tolabel.width())
   {
      dx = qRound(static_cast<qreal>(tolabel.width() - drawRect.width()) / 2.0);
   }
   drawRect.moveTo(dx, dy);

   p.drawImage(drawRect, image, image.rect());
   m_copyOfImage = QImage2Mat(tolabel.toImage());
   m_previewLabel->setPixmap(tolabel);
}

bool CAllImgProcGUI::hasImage() const
{
   return (0 != m_copyOfImage.data);
}

void CAllImgProcGUI::okClicked()
{
   emit ok();
   this->hide();
}

void CAllImgProcGUI::cancelClicked()
{
   emit cancel();
   this->hide();
}

void CAllImgProcGUI::redrawPreview()
{
   if (!hasImage())
   {
      return;
   }
   if (0 == m_imgproc)
   {
      m_imgproc = new CImgProc;
   }

   if (m_proctasks.size() == 0)
   {
      QImage image = Mat2QImage(m_copyOfImage);
      QPixmap pixmap = QPixmap::fromImage(image);
      m_previewLabel->setPixmap(pixmap);
   }
   else
   {
      cv::Mat target;
      m_imgproc->setTasks(m_proctasks);
      if (m_imgproc->processImage(m_copyOfImage, target))
      {
         QImage image = Mat2QImage(target);
         if (!image.isNull())
         {
            QPixmap pixmap = QPixmap::fromImage(image);
            if (!pixmap.isNull() && 0 != m_previewLabel)
            {
               QPainter p(&pixmap);
               p.setRenderHint(QPainter::Antialiasing);
               p.setPen(Qt::red);
               if (m_imgproc->hasLines_Hough())
               {
                  QList<QLine> lines = m_imgproc->lines_Hough();
                  for (int i = 0; i < lines.size(); i++)
                  {
                     p.drawLine(lines[i]);
                  }
               }
               p.end();
               m_previewLabel->setPixmap(pixmap);
            }
         }
      }
   }
   if (m_updateSource->isChecked())
   {
      emit previewWasRedrawn();
   }
}

bool CAllImgProcGUI::processImage(cv::Mat source, cv::Mat &target)
{
   if (0 != m_imgproc && m_proctasks.size() > 0)
   {
      m_imgproc->setTasks(m_proctasks);
      return m_imgproc->processImage(source, target);
   }
   return false;
}


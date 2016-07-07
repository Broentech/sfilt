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
//  \file      singleImage.h
//
//  \brief     Window widget for displaying a single item
//
//  \author    Stian Broen
//
//  \date      28.06.2015
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
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>

// solution includes
#include <processImage/commonFunctions.h>

// local includes
#include "singleImage.h"

using namespace guiSpace;

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	SingleImageView ctor
//
//
//  \param  QWidget *parent -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  28.06.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
SingleImageView::SingleImageView(QWidget *parent)
:QWidget(parent),
m_thumbnail(64, 64),
m_imgprocDialog(0)
{
   initGUI();
   this->setMinimumSize(100,100);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	SingleImageView ctor
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  28.06.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
SingleImageView::~SingleImageView()
{

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	initGUI
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  28.06.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
void SingleImageView::initGUI()
{

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	setImage
//
//
//  \param  const QString &path -
//          const QString &text -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  28.06.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
void SingleImageView::setImage(const QString &path, const QString &text)
{
   m_imagePath = path;
   QImage img;
   if (img.load(m_imagePath))
   {
      setImage(img, text);
   }
   else
   {
      emit problem("Failed at loading image " + path);
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	setImage
//
//
//  \param  QImage image -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  01.07.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
void SingleImageView::setImage(QImage image, const QString &text)
{
   m_originalImage = image;
   m_text = text;
   QPainter p(&m_thumbnail);
   p.drawPixmap(m_thumbnail.rect(), QPixmap::fromImage(m_originalImage), m_originalImage.rect());
   this->update();
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	setImage
//
//
//  \param  cv::Mat image       -
//          const QString &text -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  03.07.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
void SingleImageView::setImage(cv::Mat image, const QString &text)
{
   setImage(Mat2QImage(image), text);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	paintEvent
//
//
//  \param  QPaintEvent *ev -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  28.06.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
void SingleImageView::paintEvent(QPaintEvent *ev)
{
   if (m_originalImage.isNull() &&
      m_processedImage.isNull())
   {
      return;
   }

   QImage drawme;
   if (!m_processedImage.isNull())
   {
      drawme = m_processedImage;
   }
   else
   {
      drawme = m_originalImage;
   }

   QPainter p(this);
   p.setRenderHint(QPainter::SmoothPixmapTransform, true);
   p.fillRect(this->rect(), QBrush(QColor(Qt::darkGray)));
   QRect drawRect;
   drawRect.setWidth(this->width());
   drawRect.setHeight(this->width() * qRound(
      static_cast<qreal>(drawme.rect().height()) /
      static_cast<qreal>(drawme.rect().width())
      ));

   if (drawRect.height() > this->height())
   {
      drawRect.setHeight(this->height());
      drawRect.setWidth(this->height() * qRound(
         static_cast<qreal>(drawme.rect().width()) /
         static_cast<qreal>(drawme.rect().height())
         ));
   }

   int dx = 0;
   int dy = 0;
   if (drawRect.height() < this->height())
   {
      dy = qRound(static_cast<qreal>(this->height() - drawRect.height()) / 2.0);
   }
   if (drawRect.width() < this->width())
   {
      dx = qRound(static_cast<qreal>(this->width() - drawRect.width()) / 2.0);
   }
   drawRect.moveTo(dx, dy);

   p.drawImage(drawRect, drawme, drawme.rect());

   if (m_imgprocDialog != 0 && m_imgprocDialog->hasLines_Hough())
   {
      QPixmap meta(drawme.size());
      meta.fill(QColor(255,255,255,0));
      QPainter metaPainter(&meta);
      QList<QLine> lines = m_imgprocDialog->lines_Hough();
      metaPainter.setPen(Qt::red);
      for (int i = 0; i < lines.size(); i++)
      {
         metaPainter.drawLine(lines[i]);
      }
      metaPainter.end();
      p.drawPixmap(drawRect, meta, meta.rect());
   }

   if (m_text != "")
   {
      p.drawText(QPoint(10, 10), m_text);
   }

   QWidget::paintEvent(ev);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	resizeEvent
//
//
//  \param  QPaintEvent *ev -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  28.06.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
void SingleImageView::resizeEvent(QResizeEvent *ev)
{
   this->update();
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	mousePressEvent
//
//
//  \param  QMouseEvent *ev -
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  01.07.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
void SingleImageView::mousePressEvent(QMouseEvent *ev)
{
   if (ev->button() == Qt::RightButton)
   {
      if (0 == m_imgprocDialog)
      {
         m_imgprocDialog = new CAllImgProcGUI(this);
         if (m_text != "")
         {
            m_imgprocDialog->setWindowTitle("Image Processing for - " + m_text);
         }
         else
         {
            m_imgprocDialog->setWindowTitle("Image Processing");
         }

         connect(m_imgprocDialog, SIGNAL(ok()),
            this, SLOT(procOk()));

         connect(m_imgprocDialog, SIGNAL(cancel()),
            this, SLOT(procCancel()));

         connect(m_imgprocDialog, SIGNAL(previewWasRedrawn()),
            this, SLOT(procOk()));

      }
      m_imgprocDialog->setImage(m_originalImage);
      m_imgprocDialog->show();
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	procOk
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  01.07.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
void SingleImageView::procOk()
{
   cv::Mat source = QImage2Mat(m_originalImage);
   cv::Mat target;
   if (m_imgprocDialog->processImage(source, target))
   {
      m_processedImage = Mat2QImage(target).copy();
      this->update();
      emit iHaveProcessedImage(true);
   }
   else
   {
      m_processedImage = QImage();
      emit iHaveProcessedImage(false);
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	setImage_Processed
//
//
//  \param  cv::Mat image
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  03.07.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
void SingleImageView::setImage_Processed(cv::Mat image)
{
   m_processedImage = Mat2QImage(image).copy();
   this->update();
   emit iHaveProcessedImage(true);
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	procCancel
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  01.07.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
void SingleImageView::procCancel()
{

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	currentImage
//
//
//  \param  N/A
//
//  \return N/A
//    
//  \author Stian Broen 
//
//  \date  03.07.2015
//
//
//f-//////////////////////////////////////////////////////////////////////////
QImage SingleImageView::currentImage() const
{
   if (m_processedImage.isNull())
   {
      return m_originalImage;
   }
   else
   {
      return m_processedImage;
   }
}



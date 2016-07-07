//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      singleImage.h
//
//  \brief     Window widget for displaying a single item
//
//  \author    Stian Broen
//
//  \date      28.06.2015
//
//  \par       Copyright: BroenTech Solutions AS
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

#ifndef _RUSTBUST_SINGLE_IMAGE_H_
#define _RUSTBUST_SINGLE_IMAGE_H_

// Qt includes
#include <QWidget>
#include <QString>
#include <QImage>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QMouseEvent>

// solution includes
#include <ImageProcessing_GUI/all.h>

using namespace imageProcessingSpace;

namespace guiSpace {
	class SingleImageView : public QWidget
	{
		Q_OBJECT
		
	public:
		explicit SingleImageView(QWidget *parent = 0);
		~SingleImageView();
      void setImage(const QString &path, const QString &text = "");
      void setImage(QImage image, const QString &text = "");
      void setImage(cv::Mat image, const QString &text = "");
      void setImage_Processed(cv::Mat image);
      inline QPixmap thumbnail() const { return m_thumbnail; }
      inline QImage image() const { return m_originalImage; }
      inline QImage processedImage() const { return m_processedImage; }
      QImage currentImage() const;

   signals:
      void problem(const QString &explanation);
      void iHaveProcessedImage(bool itstrue);

   private slots:
      void procOk();
      void procCancel();

   private:
      void initGUI();
      void reloadView();

   protected:
      void paintEvent(QPaintEvent *ev);
      void resizeEvent(QResizeEvent *ev);
      void mousePressEvent(QMouseEvent *ev);

   private:
      QString m_imagePath;
      QString m_text;
      QImage m_originalImage;
      QImage m_processedImage;
      QPixmap m_thumbnail;
      CAllImgProcGUI *m_imgprocDialog;
	};
}

#endif
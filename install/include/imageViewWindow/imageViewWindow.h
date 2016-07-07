//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      imageViewWindow.h
//
//  \brief     Window windget for displaying image items
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

#ifndef _RUSTBUST_IMAGE_VIEW_WINDOW_H_
#define _RUSTBUST_IMAGE_VIEW_WINDOW_H_

// Qt includes
#include <QWidget>
#include <QToolButton>
#include <QStackedWidget>
#include <QLabel>
#include <QResizeEvent>
#include <QHBoxLayout>
#include <QMap>
#include <QButtonGroup>

namespace guiSpace {
	class ImageViewWindow : public QWidget
	{
		Q_OBJECT
		
	public:
		explicit ImageViewWindow(QWidget *parent = 0);
		~ImageViewWindow();

   signals:
      void setUserMessage(const QString &message);

   public slots:
      void addImage(const QString &path);

   private slots:
      void leftClicked();
      void rightClicked();
      void thumbClicked();

   private:
      void initGui();
      void resetThumbLay();

   private:
      QStackedWidget *m_imagesView;
      QToolButton *m_leftButton;
      QToolButton *m_rightButton;
      QHBoxLayout *m_imageThumbs;
      QMap<int, QToolButton *> m_thumbnails;
      QButtonGroup *m_thumbGroup;
      int m_currentIndex;
	};
}

#endif
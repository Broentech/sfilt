//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      metadataGeneral.h
//
//  \brief     GUI to general metadata operations
//
//  \author    Stian Broen
//
//  \date      06.12.2013
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

#ifndef _IMGPROC_METADATA_GENERAL_H_
#define _IMGPROC_METADATA_GENERAL_H_

#include <QWidget>

class QPushButton;

namespace guiSpace {
   class CImgProcMetaGeneral : public QWidget
   {
      Q_OBJECT

   public:
      explicit CImgProcMetaGeneral(QWidget *parent = 0);
      ~CImgProcMetaGeneral();

   private:
      void initGUI();

   signals:
      void freeze(bool val);

   private slots:
      void freezeClicked();

   private:
      QPushButton *m_freezeMeta;
      QPushButton *m_clearMeta;
      QPushButton *m_storeMeta;
   };
}

#endif
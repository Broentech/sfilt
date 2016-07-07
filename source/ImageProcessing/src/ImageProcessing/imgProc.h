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
//  \file      imgProc.h
//
//  \brief     This is a class that performs processing on an opencv image
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

#ifndef _IMG_PROC_H_
#define _IMG_PROC_H_

// Qt includes
#include <QObject>
#include <QMap>

// local includes
#include "smooth.h"
#include "morph.h"
#include "thresh.h"
#include "gradients.h"
#include "houghLines.h"
#include "kernels.h"

using namespace cv;
namespace imageProcessingSpace {
   class CImgProc : public QObject
   {
      Q_OBJECT

   public:
      explicit CImgProc();
      ~CImgProc();
      bool processImage(cv::Mat source, cv::Mat &target);
      inline void setTasks(QMap<int , QPair<ImgProcTask ,CProcTaskBase *> > tasks) { m_proctasks = tasks; }
      inline QMap<int , QPair<ImgProcTask ,CProcTaskBase *> > tasks() const { return m_proctasks; }
      inline bool hasTasks() const { return m_proctasks.size() != 0; }
      inline bool hasLines_Hough() const { return (m_metaHoughLines.size() > 0); }
      inline QList<QLine> lines_Hough() const { return m_metaHoughLines; }

   public slots:
      void setActive(const QString &json, bool val);
      void addTask(ImgProcTask type, const QString &json);

   private: 
      QMap<int , QPair<ImgProcTask ,CProcTaskBase *> > m_proctasks;
      QList<QLine> m_metaHoughLines;

   private: 
      bool contains(const QString &json) const;
   };
}

#endif
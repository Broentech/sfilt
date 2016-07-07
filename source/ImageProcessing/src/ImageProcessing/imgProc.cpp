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
//  \file      imgProc.cpp
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

// local includes
#include "imgProc.h"

// opencv includes
#include <opencv/highgui.h>

using namespace imageProcessingSpace;
Q_DECLARE_METATYPE(ImgProcTask)

CImgProc::CImgProc()
{
   qRegisterMetaType<ImgProcTask>("ImgProcTask");
}

CImgProc::~CImgProc()
{

}

bool CImgProc::processImage(cv::Mat source, cv::Mat &target)
{
   QMapIterator<int , QPair<ImgProcTask ,CProcTaskBase *> > i(m_proctasks);
   cv::Mat tmp;
   while(i.hasNext())
   {
      i.next();
      ImgProcTask task = i.value().first;
      CProcTaskBase *spec = i.value().second;
      if (!spec->isActive())
      {
         continue;
      }
      cv::Mat _src;
      if (0 != tmp.data)
      {
         _src = tmp;
      }
      else
      {
         _src = source;
      }
      switch(task)
      {
      case(IMGPROC_SMOOTH):
         {
            CProcTask_Smooth *robj = 0;
            try
            {
               robj = dynamic_cast<CProcTask_Smooth *>(spec);
            }
            catch(std::__non_rtti_object e)
            {
               qCritical() << "RTTI exception, aborting";
               return false;
            }
            if(0 == robj)
            {
               qCritical() << "Invalid cast to CProcTask_Smooth";
               return false;
            }
            target = doSmoothing(robj, _src);
            break;
         }
      case(IMGPROC_MORPH):
         {
            CProcTask_Morph *robj = 0;
            try
            {
               robj = dynamic_cast<CProcTask_Morph *>(spec);
            }
            catch(std::__non_rtti_object e)
            {
               qCritical() << "RTTI exception, aborting";
               return false;
            }
            if(0 == robj)
            {
               qCritical() << "Invalid cast to CProcTask_Morph";
               return false;
            }
            target = doMorphology(robj, _src);
            break;
         }
      case(IMGPROC_THRESHOLD):
         {
            CProcTask_Thresh *robj = 0;
            try
            {
               robj = dynamic_cast<CProcTask_Thresh *>(spec);
            }
            catch(std::__non_rtti_object e)
            {
               qCritical() << "RTTI exception, aborting";
               return false;
            }
            if(0 == robj)
            {
               qCritical() << "Invalid cast to CProcTask_Thresh";
               return false;
            }
            target = doThresholding(robj, _src);
            break;
         }
      case(IMGPROC_GRADIENT):
         {
            CProcTask_Gradients *robj = 0;
            try
            {
               robj = dynamic_cast<CProcTask_Gradients *>(spec);
            }
            catch(std::__non_rtti_object e)
            {
               qCritical() << "RTTI exception, aborting";
               return false;
            }
            if(0 == robj)
            {
               qCritical() << "Invalid cast to CProcTask_Gradients";
               return false;
            }
            target = doGradient(robj, _src);
            break;
         }
      case(IMGPROC_HOUGHLINES):
         {
            CProcTask_HoughLines *robj = 0;
            try
            {
               robj = dynamic_cast<CProcTask_HoughLines *>(spec);
            }
            catch(std::__non_rtti_object e)
            {
               qCritical() << "RTTI exception, aborting";
               return false;
            }
            if(0 == robj)
            {
               qCritical() << "Invalid cast to CProcTask_HoughLines";
               return false;
            }
            m_metaHoughLines = doHoughLines(robj, _src);
            target = _src;
            continue;
         }
      case(IMGPROC_CONVOLVE):
         {
            CProcTask_Kernels *robj = 0;
            try
            {
               robj = dynamic_cast<CProcTask_Kernels *>(spec);
            }
            catch(std::__non_rtti_object e)
            {
               qCritical() << "RTTI exception, aborting";
               return false;
            }
            if(0 == robj)
            {
               qCritical() << "Invalid cast to CProcTask_Kernels";
               return false;
            }
            target = doConvolution(robj, _src);
            break;
         }

      case(IMGPROC_UNKNOWN):
      default:
         qCritical() << "Unknown processing object";
         return false;
      }

      if(i.hasNext())
      {
         i.next();
         CProcTaskBase *_spec = i.value().second;
         if(0 == _spec || !_spec->isActive())
         {
            _spec = 0;
            i.previous();
            continue;
         }
         i.previous();
         target.copyTo(tmp);
      }
   }

   return true;
}

void CImgProc::setActive(const QString &json, bool val)
{
   QMapIterator<int , QPair<ImgProcTask ,CProcTaskBase *> > i(m_proctasks);
   IplImage *tmp = 0;
   while(i.hasNext())
   {
      i.next();
      CProcTaskBase *spec = i.value().second;
      if (0 == spec || spec->json() != json)
      {
         continue;
      }
      spec->setActive(val);
      return;
   }
}

void CImgProc::addTask(ImgProcTask type, const QString &json)
{
   if (contains(json))
   {
      return;
   }
   switch(type)
   {
   case(IMGPROC_SMOOTH):
      break;
   case(IMGPROC_GRAYSCALE):
      break;
   case(IMGPROC_MORPH):
      break;
   case(IMGPROC_UNKNOWN):
   default:
      break;
   }
}

bool CImgProc::contains(const QString &json) const
{
   QMapIterator<int , QPair<ImgProcTask ,CProcTaskBase *>> i(m_proctasks);
   IplImage *tmp = 0;
   while(i.hasNext())
   {
      i.next();
      CProcTaskBase *spec = i.value().second;
      if (0 == spec)
      {
         continue;
      }
      if (spec->json() == json)
      {
         return true;
      }
   }
   return false;
}
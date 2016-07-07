//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      distanceTransform.h
//
//  \brief     Class containing distance transform parameters for image processing
//
//  \author    Stian Broen
//
//  \date      27.12.2013
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

#ifndef _IMGPROC_DISTANCETRANSFORM_H_
#define _IMGPROC_DISTANCETRANSFORM_H_

// Qt includes

// local includes
#include "base.h"

namespace imageProcessingSpace {
   class CProcTask_DistTrans : public CProcTaskBase
   {
   private:
      DistanceTransformType m_type;
      DistanceTransformMask m_mask;

   public:
      CProcTask_DistTrans();
      CProcTask_DistTrans(DistanceTransformType type, DistanceTransformMask mask);
      ~CProcTask_DistTrans();
      CProcTask_DistTrans(const CProcTask_DistTrans &other);
      CProcTask_DistTrans(const QString &summary);
      CProcTask_DistTrans& operator=(const CProcTask_DistTrans &other);
      bool operator==(const CProcTask_DistTrans &other) const;
      bool operator!=(const CProcTask_DistTrans &other) const;
      void clear();
      bool isValid() const;
      QString id() const;
      QString summary() const;

      inline void setType(DistanceTransformType type) { m_type = type; }
      inline void setMask(DistanceTransformMask mask) { m_mask = mask; }
      inline DistanceTransformType type() const { return m_type; }
      inline DistanceTransformMask mask() const { return m_mask; }

   };
   CProcTask_DistTrans distTransModelFromSummary(const QString &summary);
   QString distTransToSummary(const CProcTask_DistTrans &model);
   bool setDistTransModelEntry(CProcTask_DistTrans &model, const QString &variableName, const QString &value);

   cv::Mat doDistanceTransform(CProcTask_DistTrans *spec, cv::Mat source);
}

#endif
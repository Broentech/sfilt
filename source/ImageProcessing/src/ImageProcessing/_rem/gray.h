//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      gray.h
//
//  \brief     Class containing grayscale processing parameters for image processing
//
//  \author    Stian Broen
//
//  \date      22.09.2013
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

#ifndef _IMGPROC_GRAYSCALE_H_
#define _IMGPROC_GRAYSCALE_H_

// Qt includes
#include <QString>

// local includes
#include "base.h"

namespace imageProcessingSpace {
   class CProcTask_Gray : public CProcTaskBase
   {
   private:
      GrayScaleType m_type;
      double m_lowThreshold;
      double m_highThreshold;
      double m_aperture;

   public:
      CProcTask_Gray();
      CProcTask_Gray(GrayScaleType type, double lowThreshold, double highThreshold, double aperture);
      ~CProcTask_Gray();
      CProcTask_Gray(const CProcTask_Gray &other);
      CProcTask_Gray(const QString &summary);
      CProcTask_Gray& operator=(const CProcTask_Gray &other);
      bool operator==(const CProcTask_Gray &other) const;
      bool operator!=(const CProcTask_Gray &other) const;
      void clear();
      bool isValid() const;
      QString id() const;
      QString summary() const;

      inline GrayScaleType type() const { return m_type; }
      inline double lowThreshold() const { return m_lowThreshold; }
      inline double highThreshold() const { return m_highThreshold; }
      inline double aperture() const { return m_aperture; }

      inline void setType(GrayScaleType type) { m_type = type ; }
      inline void setLowThreshold(double val) { m_lowThreshold = val; }
      inline void setHighThreshold(double val) { m_highThreshold = val; }
      inline void setAperture(double val) { m_aperture = val; }
   };
   CProcTask_Gray grayModelFromSummary(const QString &summary);
   QString grayModelToSummary(const CProcTask_Gray &model);
   bool setGrayModelEntry(CProcTask_Gray &model, const QString &variableName, const QString &value);

   cv::Mat doGraying(CProcTask_Gray *spec, cv::Mat source);
   cv::Mat convertToGrayscale(cv::Mat source);
   cv::Mat doThreshold(cv::Mat source, double threshold, int type = CV_THRESH_BINARY);
   cv::Mat doCanny(cv::Mat source, double low, double high, double aperture);
}

#endif
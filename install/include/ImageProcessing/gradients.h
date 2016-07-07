//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      gradients.h
//
//  \brief     Class containing gradients parameters for image transforms
//
//  \author    Stian Broen
//
//  \date      13.10.2013
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

#ifndef _IMGTRANS_GRADIENTS_H_
#define _IMGTRANS_GRADIENTS_H_

// Qt includes
#include <QString>
#include <QJsonObject>

// local includes
#include "base.h"

namespace imageProcessingSpace {
   class CProcTask_Gradients : public CProcTaskBase
   {
   private:
      GradientType m_type;
      int m_order_x;
      int m_order_y;
      int m_apertureSize;
      double m_lowThreshold;
      double m_highThreshold;

   public:
      CProcTask_Gradients();
      CProcTask_Gradients(GradientType type, int order_x, int order_y, int apertureSize, double lowThreshold, double highThreshold);
      ~CProcTask_Gradients();
      CProcTask_Gradients(const CProcTask_Gradients &other);
      CProcTask_Gradients(const QString &json);
      CProcTask_Gradients& operator=(const CProcTask_Gradients &other);
      bool operator==(const CProcTask_Gradients &other) const;
      bool operator!=(const CProcTask_Gradients &other) const;
      void clear();
      bool isValid() const;
      QString id() const;
      QString json() const;

      inline GradientType type() const { return m_type; }
      inline int order_x() const { return m_order_x; }
      inline int order_y() const { return m_order_y; }
      inline int apertureSize() const { return m_apertureSize; }
      inline double lowThreshold() const { return m_lowThreshold; }
      inline double highThreshold() const { return m_highThreshold; }

      inline void setType(GradientType type) { m_type = type; }
      inline void setOrder_x(int val) { if(val == 0 || val == 1 || val == 2) m_order_x = val; }
      inline void setOrder_y(int val) { if(val == 0 || val == 1 || val == 2) m_order_y = val; }
      inline void setApertureSize(int val) { if(val == 1 || val == 3 || val == 5 || val == 7) m_apertureSize = val; }
      inline void setLowThreshold(double val) { m_lowThreshold  = val; }
      inline void setHighThreshold(double val) { m_highThreshold = val; }
   };

   QJsonObject CProcTask_Gradients_to_JSONOBJECT(const CProcTask_Gradients &prc);
   QString CProcTask_Gradients_to_JSON(const CProcTask_Gradients &prc);
   CProcTask_Gradients CProcTask_Gradients_from_JSON(const QString &json);
   CProcTask_Gradients CProcTask_Gradients_from_JSONOBJECT(const QJsonObject &obj);

   cv::Mat doGradient(CProcTask_Gradients *spec, cv::Mat source);
}

#endif
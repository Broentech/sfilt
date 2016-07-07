//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      kernels.h
//
//  \brief     Class containing kernels for image processing
//
//  \author    Stian Broen
//
//  \date      01.01.2014
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

#ifndef _IMGPROC_KERNELS_H_
#define _IMGPROC_KERNELS_H_

// Qt includes
#include <QVariant>
#include <QList>
#include <QJsonObject>

// local includes
#include "base.h"

namespace imageProcessingSpace {

   typedef QPair< QPair<int, int>, QVariant> kernelvalue;
   int first(const kernelvalue &val);
   int second(const kernelvalue &val);
   QVariant third(const kernelvalue &val);
   kernelvalue& setFirst(kernelvalue &val, int _first);
   kernelvalue& setSecond(kernelvalue &val, int _second);
   kernelvalue& setThird(kernelvalue &val, const QVariant &_third);

   class CProcTask_Kernels : public CProcTaskBase
   {
   private:
      KernelType m_type;
      QVariant::Type m_valueType;
      QList< kernelvalue > m_kernel; // X, Y, value

   public:

      inline KernelType type() const { return m_type; }
      inline QVariant::Type valueType() const { return m_valueType; }
      inline QList< kernelvalue > kernel() const { return m_kernel; }

      inline void setType(KernelType type) { m_type = type; }
      inline void setValueType(QVariant::Type valueType) { m_valueType = valueType; }
      inline void setKernel(QList< kernelvalue > kernel) { m_kernel = kernel; }
      inline void addKernelValue(kernelvalue val) { m_kernel << val; };

      CProcTask_Kernels();
      CProcTask_Kernels(KernelType type, QVariant::Type valueType, QList< kernelvalue > kernel);
      ~CProcTask_Kernels();
      CProcTask_Kernels(const CProcTask_Kernels &other);
      CProcTask_Kernels(const QString &json);
      CProcTask_Kernels& operator=(const CProcTask_Kernels &other);
      bool operator==(const CProcTask_Kernels &other) const;
      bool operator!=(const CProcTask_Kernels &other) const;
      void clear();
      bool isValid() const;
      QString id() const;
      QString json() const;
   };

   QJsonObject CProcTask_Kernels_to_JSONOBJECT(const CProcTask_Kernels &prc);
   QString CProcTask_Kernels_to_JSON(const CProcTask_Kernels &prc);
   CProcTask_Kernels CProcTask_Kernels_from_JSON(const QString &json);
   CProcTask_Kernels CProcTask_Kernels_from_JSONOBJECT(const QJsonObject &obj);

   //CProcTask_Kernels kernelModelFromSummary(const QString &summary);
   //QString kernelModelToSummary(const CProcTask_Kernels &model);
   //bool setKernelModelEntry(CProcTask_Kernels &model, const QString &variableName, const QString &value);

   cv::Mat doConvolution(CProcTask_Kernels *spec, cv::Mat source);
}

#endif
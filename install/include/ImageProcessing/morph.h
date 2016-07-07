//h+//////////////////////////////////////////////////////////////////////////
//
//  \file      morph.h
//
//  \brief     Class containing morphology processing parameters for image processing
//
//  \author    Stian Broen
//
//  \date      01.10.2013
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

#ifndef _IMGPROC_MORPH_H_
#define _IMGPROC_MORPH_H_

// Qt includes
#include <QString>
#include <QJsonObject>

// local includes
#include "base.h"

namespace imageProcessingSpace {
   class CProcTask_Morph : public CProcTaskBase
   {
   private:
      MorphType m_type;
      MorphKernelShape m_kernelType;
      int m_kernelCols;
      int m_kernelRows;
      int m_kernelAnchor_X;
      int m_kernelAnchor_Y;
      int m_iterations;

   public:
      CProcTask_Morph();
      CProcTask_Morph(
         MorphType type,
         MorphKernelShape kernelType,
         int kernelCols,
         int kernelRows,
         int anchor_x,
         int anchor_y,
         int iterations = 1);

      ~CProcTask_Morph();
      CProcTask_Morph(const CProcTask_Morph &other);
      CProcTask_Morph(const QString &json);
      CProcTask_Morph& operator=(const CProcTask_Morph &other);
      bool operator==(const CProcTask_Morph &other) const;
      bool operator!=(const CProcTask_Morph &other) const;
      void clear();
      bool isValid() const;
      QString id() const;
      QString json() const;

      inline MorphType type() const { return m_type; }
      inline MorphKernelShape kernelType() const { return m_kernelType; }
      inline int columns() const { return m_kernelCols; }
      inline int rows() const { return m_kernelRows; }
      inline int anchor_x() const { return m_kernelAnchor_X; }
      inline int anchor_y() const { return m_kernelAnchor_Y; }
      inline int iterations() const { return m_iterations; }

      inline void setType(MorphType type) { m_type = type; }
      inline void setKernelType(MorphKernelShape type) { m_kernelType = type; }
      inline void setColumns(int val) { m_kernelCols = val; }
      inline void setRows(int val) { m_kernelRows = val; }
      inline void setAnchor_x(int val) { m_kernelAnchor_X = val; }
      inline void setAnchor_y(int val) { m_kernelAnchor_Y = val; }
      inline void setIterations(int val) { m_iterations = val; }
   };

   QJsonObject CProcTask_Morph_to_JSONOBJECT(const CProcTask_Morph &prc);
   QString CProcTask_Morph_to_JSON(const CProcTask_Morph &prc);
   CProcTask_Morph CProcTask_Morph_from_JSON(const QString &json);
   CProcTask_Morph CProcTask_Morph_from_JSONOBJECT(const QJsonObject &obj);

   //CProcTask_Morph morphModelFromSummary(const QString &summary);
   //QString morphModelToSummary(const CProcTask_Morph &model);
   //bool setMorphModelEntry(CProcTask_Morph &model, const QString &variableName, const QString &value);

   cv::Mat doMorphology(CProcTask_Morph *spec, cv::Mat source);
   cv::Mat doErode(CProcTask_Morph *spec, cv::Mat source);
   cv::Mat doDilate(CProcTask_Morph *spec, cv::Mat source);
   cv::Mat doGeneralMorph(CProcTask_Morph *spec, cv::Mat source);
}

#endif
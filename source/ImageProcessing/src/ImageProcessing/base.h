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
//  \file      base.h
//
//  \brief     Common definitions for image processing
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

#ifndef _IMGPROC_BASE_H_
#define _IMGPROC_BASE_H_

// Qt includes
#include <QString>
#include <QtDebug>

// opencv includes
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace imageProcessingSpace {
   enum ImgProcTask
   {
      IMGPROC_UNKNOWN   ,
      IMGPROC_SMOOTH    ,
      IMGPROC_GRAYSCALE ,
      IMGPROC_MORPH     ,
      IMGPROC_THRESHOLD ,
      IMGPROC_GRADIENT  ,
      IMGPROC_HOUGHLINES,
      IMGPROC_CONVOLVE  ,
   }; 
   QString imgProcTaskToString(ImgProcTask task);
   ImgProcTask imgProcTaskFromString(const QString &task);

   // base class for processing task performers
   class CProcTaskBase
   {
   private:
      bool m_active;
      QString m_summary;
   public:
      CProcTaskBase() : m_active(true) {}
      virtual ~CProcTaskBase(){}
      virtual QString id() const = 0;
      virtual QString json() const = 0;
      inline bool isActive() const { return m_active; }
      inline void setActive(bool val) { m_active = val; }
   };

   // smoothing
   const QString smoothTag_TYPE          = "SMOOTH_TYPE";
   const QString smoothTag_SIZE1         = "SIZE1" ;
   const QString smoothTag_SIZE2         = "SIZE2" ;
   const QString smoothTag_SIGMA1        = "SIGMA1";
   const QString smoothTag_SIGMA2        = "SIGMA2";
   const QString smoothTag_UNKNOWN       = "UNKNOWN_SMOOTH";
   const QString smoothTag_BLUR_NO_SCALE = "BLUR_NO_SCALE" ;
   const QString smoothTag_BLUR          = "BLUR"          ;
   const QString smoothTag_GAUSSIAN      = "GAUSSIAN"      ;
   const QString smoothTag_MEDIAN        = "MEDIAN"        ;
   const QString smoothTag_BILATERAL     = "BILATERAL"     ;
   enum SmoothType
   {
      UNKNOWN_SMOOTH ,
      BLUR_NO_SCALE  ,
      BLUR           ,
      GAUSSIAN       ,
      MEDIAN         ,
      BILATERAL      ,
   }; 
   int smoothTypeToOpenCVval(SmoothType type);
   QString smoothTypeToString(SmoothType type);
   SmoothType smoothTypeFromString(const QString &type);

   // gray
   const QString grayscaleTag_type          = "GRAYSCALE_TYPE"    ;
   const QString grayscaleTag_lowThreshold  = "LOW_THRESHOLD"     ;
   const QString grayscaleTag_highThreshold = "HIGH_THRESHOLD"    ;
   const QString grayscaleTag_aperture      = "APERTURE"          ;
   enum GrayScaleType
   {
      UNKNOWN_GRAYSCALE    ,
      CONVERT_TO_GRAYSCALE ,
      CONVERT_TO_BINARY    ,
      CONVERT_TO_CANNY     ,
   }; 
   QString grayScaleTypeToString(GrayScaleType type);
   GrayScaleType grayscaleTypeFromString(const QString &type);

   // morphology
   const QString morphTag_type      = "MORPHOLOGY_TYPE"         ;
   const QString morphTag_shape     = "MORPHOLOGY_SHAPE"        ;
   const QString morphTag_cols      = "MORPHOLOGY_COLS"         ;
   const QString morphTag_rows      = "MORPHOLOGY_ROWS"         ;
   const QString morphTag_anchorX   = "MORPHOLOGY_ANCHOR_X"     ;
   const QString morphTag_anchorY   = "MORPHOLOGY_ANCHOR_Y"     ;
   const QString morphTag_iter      = "MORPHOLOGY_ITERATIONS"   ;

   enum MorphType
   {
      UNKNOWN_MORPH  = -1              ,
      MORPH_ERODE    = CV_MOP_ERODE    ,
      MORPH_DILATE   = CV_MOP_DILATE   ,
      MORPH_OPEN     = CV_MOP_OPEN     ,
      MORPH_CLOSE    = CV_MOP_CLOSE    ,
      MORPH_GRADIENT = CV_MOP_GRADIENT ,
      MORPH_TOPHAT   = CV_MOP_TOPHAT   ,
      MORPH_BLACKHAT = CV_MOP_BLACKHAT ,
   }; 
   QString morphTypeToString(MorphType type);
   MorphType morphTypeFromString(const QString &type);

   enum MorphKernelShape
   {
      SHAPE_UNKNOWN = -1               ,
      SHAPE_DEFAULT = 10               ,
      SHAPE_RECT    = CV_SHAPE_RECT    ,
      SHAPE_CROSS   = CV_SHAPE_CROSS   ,
      SHAPE_ELLIPSE = CV_SHAPE_ELLIPSE ,
   }; 
   QString morphKernelShapeToString(MorphKernelShape type);
   MorphKernelShape morphKernelShapeFromString(const QString &type);

   // thresholding
   const QString threshTag_list = "THRESHOLD_LIST";
   const QString threshTag_method          = "THRESHOLD_METHOD"             ;
   const QString threshTag_type            = "THRESHOLD_TYPE"               ;
   const QString threshTag_value           = "THRESHOLD_VALUE"              ;
   const QString threshTag_max             = "THRESHOLD_MAX"                ;
   const QString threshTag_adaptiveMethod  = "THRESHOLD_ADAPTIVE_METHOD"    ;
   const QString threshTag_blockSize       = "THRESHOLD_ADAPTIVE_BLOCKSIZE" ;
   const QString threshTag_C               = "THRESHOLD_ADAPTIVE_C"         ;
   const QString threshTag_doSplitChannels = "THRESHOLD_CHANNEL"            ;

   enum ThresholdMethod
   {
      THRESH_METHOD_UNKNOWN  = -1,
      THRESH_METHOD_REGULAR  =  0,
      THRESH_METHOD_ADAPTIVE =  1,
   }; 
   QString thresholdMethodToString(ThresholdMethod method);
   ThresholdMethod thresholdMethodFromString(const QString &method);

   enum ThresholdType
   {
      THRESH_UNKNOWN    = -1                   ,
      THRESH_BINARY     = CV_THRESH_BINARY     ,
      THRESH_BINARY_INV = CV_THRESH_BINARY_INV ,
      THRESH_TRUNC      = CV_THRESH_TRUNC      ,
      THRESH_TOZERO     = CV_THRESH_TOZERO     ,
      THRESH_TOZERO_INV = CV_THRESH_TOZERO_INV ,
      //THRESH_MASK       = CV_THRESH_MASK       ,
      THRESH_OTSU       = CV_THRESH_OTSU       ,
   }; 
   QString thresholdTypeToString(ThresholdType type);
   ThresholdType thresholdTypeFromString(const QString &type);

   enum ThresholdAdaptiveMethod
   {
      THRESH_ADMETH_UNKNOWN      = -1                            ,
      ADAPTIVE_THRESH_MEAN_C     = CV_ADAPTIVE_THRESH_MEAN_C     ,
      ADAPTIVE_THRESH_GAUSSIAN_C = CV_ADAPTIVE_THRESH_GAUSSIAN_C ,
   }; 
   QString thresholdAdmethToString(ThresholdAdaptiveMethod method);
   ThresholdAdaptiveMethod thresholdAdmethFromString(const QString &method);

   enum ThresholdChannel
   {
      THRESH_CHANNEL_UNKNOWN ,
      THRESH_CHANNEL_RGB     ,
      THRESH_CHANNEL_GREY    ,
      THRESH_CHANNEL_RED     ,
      THRESH_CHANNEL_GREEN   ,
      THRESH_CHANNEL_BLUE    ,
   }; 
   QString thresholdChannelToString(ThresholdChannel chan);
   ThresholdChannel thresholdChannelFromString(const QString &chan);

   // gradients transforms
   const QString gradsTag_type          = "TYPE"          ;
   const QString gradsTag_order_x       = "X_ORDER"       ;
   const QString gradsTag_order_y       = "Y_ORDER"       ;
   const QString gradsTag_apSize        = "APERTURE_SIZE" ;
   const QString gradsTag_lowThreshold  = "LOW_THRESHOLD" ;
   const QString gradsTag_highThreshold = "HIGH_THRESHOLD";

   enum GradientType
   {
      GRADIENT_TYPE_UNKNOWN ,
      GRADIENT_TYPE_SOBEL   ,
      GRADIENT_TYPE_SCHARR  ,
      GRADIENT_TYPE_LAPLACE ,
      GRADIENT_TYPE_CANNY   ,
   }; 
   QString gradientTypeToString(GradientType type);
   GradientType gradientTypeFromString(const QString &type);

   // hough lines
   const QString houghLineTag_rho       = "RHO"      ;
   const QString houghLineTag_theta     = "THETA"    ;
   const QString houghLineTag_threshold = "THRESHOLD";
   const QString houghLineTag_param_1   = "PARAM_1"  ;
   const QString houghLineTag_param_2   = "PARAM_2"  ;

   // convolution / kernels
   enum KernelType
   {
      KERNEL_UNKNOWN = -1,
      KERNEL_CUSTOM  =  0,
      KERNEL_3X3     =  3,
      KERNEL_5X5     =  5,
      KERNEL_7X7     =  7,
   };
   QString kernelTypeToString(KernelType kernel);
   KernelType kernelTypeFromString(const QString &kernel);

   const QString kernelTag_kernel = "KERNEL";
   const QString kernelTag_type      = "KERNEL_TYPE"     ;
   const QString kernelTag_valueType = "KERNEL_VALUETYPE";
   const QString kernelTag_entry     = "KERNEL_ENTRY"    ;
   const QString kernelTag_coordX    = "X"               ;
   const QString kernelTag_coordY    = "Y"               ;
   const QString kernelTag_value     = "VALUE"           ;

   QList<QVariant::Type> allowedKernelValueTypes();

   QString variantTypeToString(QVariant::Type type);
   QVariant::Type variantTypeFromString(const QString &type);
   QVariant composeVariantFromString(QVariant::Type type, const QString &value);
}

#endif
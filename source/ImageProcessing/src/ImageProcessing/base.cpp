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
//  \file      base.cpp
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

// Qt includes
#include <QMetaType>
#include <QDateTime>

// local includes
#include "base.h"

using namespace imageProcessingSpace;

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	imgProcTaskToString
//
//
//  \param  ImgProcTask task -
//
//  \return QString
//    
//  \author Stian Broen 
//
//  \date  17.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
QString imageProcessingSpace::imgProcTaskToString(ImgProcTask task)
{
   switch(task)
   {
   case(IMGPROC_SMOOTH):
      return "SMOOTHING";
   case(IMGPROC_GRAYSCALE):
      return "GRAYSCALE";
   case(IMGPROC_MORPH):
      return "MORPHOLOGY";
   case(IMGPROC_THRESHOLD):
      return "THRESHOLD";
   case(IMGPROC_GRADIENT):
      return "GRADIENT";
   case(IMGPROC_HOUGHLINES):
      return "HOUGH LINES";
   case(IMGPROC_CONVOLVE):
      return "CONVOLUTION";
   case(IMGPROC_UNKNOWN):
   default:
      return "UNKNOWN";
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	imgProcTaskFromString
//
//
//  \param  const QString &task -
//
//  \return ImgProcTask
//    
//  \author Stian Broen 
//
//  \date  17.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
ImgProcTask imageProcessingSpace::imgProcTaskFromString(const QString &task)
{
   if (task == "SMOOTHING")
   {
      return IMGPROC_SMOOTH;
   }
   else if (task == "GRAYSCALE")
   {
      return IMGPROC_GRAYSCALE;
   }
   else if (task == "MORPHOLOGY")
   {
      return IMGPROC_MORPH;
   }
   else if (task == "THRESHOLD")
   {
      return IMGPROC_THRESHOLD;
   }
   else if (task == "GRADIENT")
   {
      return IMGPROC_GRADIENT;
   }
   else if (task == "HOUGH LINES")
   {
      return IMGPROC_HOUGHLINES;
   }
   else if (task == "CONVOLUTION")
   {
      return IMGPROC_CONVOLVE;
   }
   else
   {
      return IMGPROC_UNKNOWN;
   }
}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	smoothTypeToString
//
//
//  \param  SmoothType type -
//
//  \return QString
//    
//  \author Stian Broen 
//
//  \date  13.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
QString imageProcessingSpace::smoothTypeToString(SmoothType type)
{
   switch(type)
   {
   case(BLUR_NO_SCALE):
      return smoothTag_BLUR_NO_SCALE;
   case(BLUR):
      return smoothTag_BLUR;
   case(GAUSSIAN):
      return smoothTag_GAUSSIAN;
   case(MEDIAN):
      return smoothTag_MEDIAN;
   case(BILATERAL):
      return smoothTag_BILATERAL;
   case(UNKNOWN_SMOOTH):
   default:
      return smoothTag_UNKNOWN;
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	smoothTypeFromString
//
//
//  \param  const QString &type -
//
//  \return SmoothType
//    
//  \author Stian Broen 
//
//  \date  13.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
SmoothType imageProcessingSpace::smoothTypeFromString(const QString &type)
{
   if (type == smoothTag_BLUR_NO_SCALE)
   {
      return BLUR_NO_SCALE;
   }
   else if (type == smoothTag_BLUR)
   {
      return BLUR;
   }
   else if (type == smoothTag_GAUSSIAN)
   {
      return GAUSSIAN;
   }
   else if (type == smoothTag_MEDIAN)
   {
      return MEDIAN;
   }
   else if (type == smoothTag_BILATERAL)
   {
      return BILATERAL;
   }
   else
   {
      return UNKNOWN_SMOOTH;
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	smoothTypeToOpenCVval
//
//
//  \param  SmoothType type -
//
//  \return int
//    
//  \author Stian Broen 
//
//  \date  13.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
int imageProcessingSpace::smoothTypeToOpenCVval(SmoothType type)
{
   switch(type)
   {
   case(BLUR_NO_SCALE):
      return CV_BLUR_NO_SCALE;
   case(BLUR):
      return CV_BLUR;
   case(GAUSSIAN):
      return CV_GAUSSIAN;
   case(MEDIAN):
      return CV_MEDIAN;
   case(BILATERAL):
      return CV_BILATERAL;
   case(UNKNOWN_SMOOTH):
   default:
      return -1;
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	grayScaleTypeToString
//
//
//  \param  GrayScaleType type -
//
//  \return QString
//    
//  \author Stian Broen 
//
//  \date  22.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
QString imageProcessingSpace::grayScaleTypeToString(GrayScaleType type)
{
   switch(type)
   {
   case(CONVERT_TO_GRAYSCALE):
      return "CONVERT_TO_GRAYSCALE";
   case(CONVERT_TO_BINARY):
      return "CONVERT_TO_BINARY";
   case(CONVERT_TO_CANNY):
      return "CONVERT_TO_CANNY";
   case(UNKNOWN_GRAYSCALE):
   default:
      return "UNKNOWN_GRAYSCALE";
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	grayscaleTypeFromString
//
//
//  \param  const QString &type -
//
//  \return GrayScaleType
//    
//  \author Stian Broen 
//
//  \date  22.09.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
GrayScaleType imageProcessingSpace::grayscaleTypeFromString(const QString &type)
{
   if (type == "CONVERT_TO_GRAYSCALE")
   {
      return CONVERT_TO_GRAYSCALE;
   }
   else if (type == "CONVERT_TO_BINARY")
   {
      return CONVERT_TO_BINARY;
   }
   else if (type == "CONVERT_TO_CANNY")
   {
      return CONVERT_TO_CANNY;
   }
   else
   {
      return UNKNOWN_GRAYSCALE;
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	morphTypeToString
//
//
//  \param  MorphType type -
//
//  \return QString
//    
//  \author Stian Broen 
//
//  \date  01.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
QString imageProcessingSpace::morphTypeToString(MorphType type)
{
   switch(type)
   {
   case(MORPH_ERODE):
      return "MORPH_ERODE";
   case(MORPH_DILATE):
      return "MORPH_DILATE";
   case(MORPH_OPEN):
      return "MORPH_OPEN";
   case(MORPH_CLOSE):
      return "MORPH_CLOSE";
   case(MORPH_GRADIENT):
      return "MORPH_GRADIENT";
   case(MORPH_TOPHAT):
      return "MORPH_TOPHAT";
   case(MORPH_BLACKHAT):
      return "MORPH_BLACKHAT";
   case(UNKNOWN_MORPH):
   default:
      return "UNKNOWN_MORPH";
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	morphTypeFromString
//
//
//  \param  const QString &type -
//
//  \return MorphType
//    
//  \author Stian Broen 
//
//  \date  01.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
MorphType imageProcessingSpace::morphTypeFromString(const QString &type)
{
   if (type == "MORPH_ERODE")
   {
      return MORPH_ERODE;
   }
   else if (type == "MORPH_DILATE")
   {
      return MORPH_DILATE;
   }
   else if (type == "MORPH_OPEN")
   {
      return MORPH_OPEN;
   }
   else if (type == "MORPH_CLOSE")
   {
      return MORPH_CLOSE;
   }
   else if (type == "MORPH_GRADIENT")
   {
      return MORPH_GRADIENT;
   }
   else if (type == "MORPH_TOPHAT")
   {
      return MORPH_TOPHAT;
   }
   else if (type == "MORPH_BLACKHAT")
   {
      return MORPH_BLACKHAT;
   }
   else
   {
      return UNKNOWN_MORPH;
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	morphKernelShapeToString
//
//
//  \param  MorphKernelShape type -
//
//  \return QString
//    
//  \author Stian Broen 
//
//  \date  01.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
QString imageProcessingSpace::morphKernelShapeToString(MorphKernelShape type)
{
   switch(type)
   {
   case(SHAPE_DEFAULT):
      return "SHAPE_DEFAULT";
   case(SHAPE_RECT):
      return "SHAPE_RECT";
   case(SHAPE_CROSS):
      return "SHAPE_CROSS";
   case(SHAPE_ELLIPSE):
      return "SHAPE_ELLIPSE";
   case(SHAPE_UNKNOWN):
   default:
      return "SHAPE_UNKNOWN";
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	morphKernelShapeFromString
//
//
//  \param  const QString &type -
//
//  \return MorphKernelShape
//    
//  \author Stian Broen 
//
//  \date  01.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
MorphKernelShape imageProcessingSpace::morphKernelShapeFromString(const QString &type)
{
   if (type == "SHAPE_DEFAULT")
   {
      return SHAPE_DEFAULT;
   }
   else if (type == "SHAPE_RECT")
   {
      return SHAPE_RECT;
   }
   else if (type == "SHAPE_CROSS")
   {
      return SHAPE_CROSS;
   }
   else if (type == "SHAPE_ELLIPSE")
   {
      return SHAPE_ELLIPSE;
   }
   else
   {
      return SHAPE_UNKNOWN;
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	thresholdMethodToString
//
//
//  \param  ThresholdMethod method -
//
//  \return QString
//    
//  \author Stian Broen 
//
//  \date  11.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
QString imageProcessingSpace::thresholdMethodToString(ThresholdMethod method)
{
   switch(method)
   {
   case(THRESH_METHOD_REGULAR):
      return "THRESH_METHOD_REGULAR";
   case(THRESH_METHOD_ADAPTIVE):
      return "THRESH_METHOD_ADAPTIVE";
   case(THRESH_METHOD_UNKNOWN):
   default:
      return "THRESH_METHOD_UNKNOWN";
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	thresholdMethodFromString
//
//
//  \param  const QString &method -
//
//  \return ThresholdMethod
//    
//  \author Stian Broen 
//
//  \date  11.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
ThresholdMethod imageProcessingSpace::thresholdMethodFromString(const QString &method)
{
   if (method == "THRESH_METHOD_REGULAR")
   {
      return THRESH_METHOD_REGULAR;
   }
   else if (method == "THRESH_METHOD_ADAPTIVE")
   {
      return THRESH_METHOD_ADAPTIVE;
   }
   else
   {
      return THRESH_METHOD_UNKNOWN;
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	thresholdTypeToString
//
//
//  \param  ThresholdType type -
//
//  \return QString
//    
//  \author Stian Broen 
//
//  \date  11.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
QString imageProcessingSpace::thresholdTypeToString(ThresholdType type)
{
   switch(type)
   {
   case(THRESH_BINARY):
      return "THRESH_BINARY";
   case(THRESH_BINARY_INV):
      return "THRESH_BINARY_INV";
   case(THRESH_TRUNC):
      return "THRESH_TRUNC";
   case(THRESH_TOZERO):
      return "THRESH_TOZERO";
   case(THRESH_TOZERO_INV):
      return "THRESH_TOZERO_INV";
   //case(THRESH_MASK):
   //   return "THRESH_MASK";
   case(THRESH_OTSU):
      return "THRESH_OTSU";
   case(THRESH_UNKNOWN):
   default:
      return "THRESH_UNKNOWN";
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	thresholdTypeFromString
//
//
//  \param  const QString &type -
//
//  \return ThresholdType
//    
//  \author Stian Broen 
//
//  \date  11.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
ThresholdType imageProcessingSpace::thresholdTypeFromString(const QString &type)
{
   if (type == "THRESH_BINARY")
   {
      return THRESH_BINARY;
   }
   else if (type == "THRESH_BINARY_INV")
   {
      return THRESH_BINARY_INV;
   }
   else if (type == "THRESH_TRUNC")
   {
      return THRESH_TRUNC;
   }
   else if (type == "THRESH_TOZERO")
   {
      return THRESH_TOZERO;
   }
   else if (type == "THRESH_TOZERO_INV")
   {
      return THRESH_TOZERO_INV;
   }
   //else if(type == "THRESH_MASK")
   //   return THRESH_MASK;
   else if (type == "THRESH_OTSU")
   {
      return THRESH_OTSU;
   }
   else
   {
      return THRESH_UNKNOWN;
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	thresholdAdmethToString
//
//
//  \param  ThresholdAdaptiveMethod method -
//
//  \return QString
//    
//  \author Stian Broen 
//
//  \date  11.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
QString imageProcessingSpace::thresholdAdmethToString(ThresholdAdaptiveMethod method)
{
   switch(method)
   {
   case(ADAPTIVE_THRESH_MEAN_C):
      return "ADAPTIVE_THRESH_MEAN_C";
   case(ADAPTIVE_THRESH_GAUSSIAN_C):
      return "ADAPTIVE_THRESH_GAUSSIAN_C";
   case(THRESH_ADMETH_UNKNOWN):
   default:
      return "THRESH_ADMETH_UNKNOWN";
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	thresholdAdmethFromString
//
//
//  \param  const QString &method -
//
//  \return ThresholdAdaptiveMethod
//    
//  \author Stian Broen 
//
//  \date  11.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
ThresholdAdaptiveMethod imageProcessingSpace::thresholdAdmethFromString(const QString &method)
{
   if (method == "ADAPTIVE_THRESH_MEAN_C")
   {
      return ADAPTIVE_THRESH_MEAN_C;
   }
   else if (method == "ADAPTIVE_THRESH_GAUSSIAN_C")
   {
      return ADAPTIVE_THRESH_GAUSSIAN_C;
   }
   else
   {
      return THRESH_ADMETH_UNKNOWN;
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	thresholdChannelToString
//
//
//  \param  ThresholdChannel chan -
//
//  \return QString
//    
//  \author Stian Broen 
//
//  \date  11.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
QString imageProcessingSpace::thresholdChannelToString(ThresholdChannel chan)
{
   switch(chan)
   {
   case(THRESH_CHANNEL_RGB):
      return "THRESH_CHANNEL_RGB";
   case(THRESH_CHANNEL_GREY):
      return "THRESH_CHANNEL_GREY";
   case(THRESH_CHANNEL_RED):
      return "THRESH_CHANNEL_RED";
   case(THRESH_CHANNEL_GREEN):
      return "THRESH_CHANNEL_GREEN";
   case(THRESH_CHANNEL_BLUE):
      return "THRESH_CHANNEL_BLUE";
   case(THRESH_CHANNEL_UNKNOWN):
   default:
      return "THRESH_CHANNEL_UNKNOWN";
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	thresholdChannelFromString
//
//
//  \param  const QString &chan) -
//
//  \return ThresholdChannel
//    
//  \author Stian Broen 
//
//  \date  11.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
ThresholdChannel imageProcessingSpace::thresholdChannelFromString(const QString &chan)
{
   if (chan == "THRESH_CHANNEL_RGB")
   {
      return THRESH_CHANNEL_RGB;
   }
   else if (chan == "THRESH_CHANNEL_GREY")
   {
      return THRESH_CHANNEL_GREY;
   }
   else if (chan == "THRESH_CHANNEL_RED")
   {
      return THRESH_CHANNEL_RED;
   }
   else if (chan == "THRESH_CHANNEL_GREEN")
   {
      return THRESH_CHANNEL_GREEN;
   }
   else if (chan == "THRESH_CHANNEL_BLUE")
   {
      return THRESH_CHANNEL_BLUE;
   }
   else
   {
      return THRESH_CHANNEL_UNKNOWN;
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	gradientTypeToString
//
//
//  \param  GradientType type -
//
//  \return QString
//    
//  \author Stian Broen 
//
//  \date  12.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
QString imageProcessingSpace::gradientTypeToString(GradientType type)
{
   switch(type)
   {
   case(GRADIENT_TYPE_SOBEL):
      return "GRADIENT_TYPE_SOBEL";
   case(GRADIENT_TYPE_SCHARR):
      return "GRADIENT_TYPE_SCHARR";
   case(GRADIENT_TYPE_LAPLACE):
      return "GRADIENT_TYPE_LAPLACE";
   case(GRADIENT_TYPE_CANNY):
      return "GRADIENT_TYPE_CANNY";
   case(GRADIENT_TYPE_UNKNOWN):
   default:
      return "GRADIENT_TYPE_UNKNOWN";
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	gradientTypeFromString
//
//
//  \param  const QString &type -
//
//  \return GradientType
//    
//  \author Stian Broen 
//
//  \date  12.10.2013
//
//
//f-//////////////////////////////////////////////////////////////////////////
GradientType imageProcessingSpace::gradientTypeFromString(const QString &type)
{
   if (type == "GRADIENT_TYPE_SOBEL")
   {
      return GRADIENT_TYPE_SOBEL;
   }
   else if (type == "GRADIENT_TYPE_SCHARR")
   {
      return GRADIENT_TYPE_SCHARR;
   }
   else if (type == "GRADIENT_TYPE_LAPLACE")
   {
      return GRADIENT_TYPE_LAPLACE;
   }
   else if (type == "GRADIENT_TYPE_CANNY")
   {
      return GRADIENT_TYPE_CANNY;
   }
   else
   {
      return GRADIENT_TYPE_UNKNOWN;
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	kernelTypeToString
//
//
//  \param  KernelType kernel -
//
//  \return QString
//    
//  \author Stian Broen 
//
//  \date  01.01.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////
QString imageProcessingSpace::kernelTypeToString(KernelType kernel)
{
   switch(kernel)
   {
   case(KERNEL_3X3):
      return "KERNEL_3X3";
   case(KERNEL_5X5):
      return "KERNEL_5X5";
   case(KERNEL_7X7):
      return "KERNEL_7X7";
   case(KERNEL_CUSTOM):
      return "KERNEL_CUSTOM";
   case(KERNEL_UNKNOWN):
   default:
      return "KERNEL_UNKNOWN";
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	kernelTypeFromString
//
//
//  \param  const QString &kernel -
//
//  \return KernelType
//    
//  \author Stian Broen 
//
//  \date  01.01.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////
KernelType imageProcessingSpace::kernelTypeFromString(const QString &kernel)
{
   if (kernel == "KERNEL_3X3")
   {
      return KERNEL_3X3;
   }
   else if (kernel == "KERNEL_5X5")
   {
      return KERNEL_5X5;
   }
   else if (kernel == "KERNEL_7X7")
   {
      return KERNEL_7X7;
   }
   else if (kernel == "KERNEL_CUSTOM")
   {
      return KERNEL_CUSTOM;
   }
   else
   {
      return KERNEL_UNKNOWN;
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	allowedKernelValueTypes
//
//
//  \param  N/A
//
//  \return QList<QVariant::Type>
//    
//  \author Stian Broen 
//
//  \date  01.01.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////
QList<QVariant::Type> imageProcessingSpace::allowedKernelValueTypes()
{
   static QList<QVariant::Type> allowedKernelVals;
   if(allowedKernelVals.size() == 0)
   {
      //allowedKernelVals << QVariant::Int;
      allowedKernelVals << QVariant::Double;
   }
   return allowedKernelVals;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	variantTypeToString
//
//
//  \param  QVariant::Type type -
//
//  \return QString
//    
//  \author Stian Broen 
//
//  \date  01.01.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////
QString imageProcessingSpace::variantTypeToString(QVariant::Type type)
{
   switch (type)
   {
   case(QVariant::BitArray) :
      return "BitArray";
   case(QVariant::Bitmap) :
      return "Bitmap";
   case(QVariant::Bool) :
      return "Bool";
   case(QVariant::Brush) :
      return "Brush";
   case(QVariant::ByteArray) :
      return "ByteArray";
   case(QVariant::Char) :
      return "Char";
   case(QVariant::Color) :
      return "Color";
   case(QVariant::Cursor) :
      return "Cursor";
   case(QVariant::Date) :
      return "Date";
   case(QVariant::DateTime) :
      return "DateTime";
   case(QVariant::Double) :
      return "Double";
   case(QVariant::EasingCurve) :
      return "EasingCurve";
   case(QVariant::Uuid) :
      return "Uuid";
   case(QVariant::ModelIndex) :
      return "ModelIndex";
   case(QVariant::Font) :
      return "Font";
   case(QVariant::Hash) :
      return "Hash";
   case(QVariant::Icon) :
      return "Icon";
   case(QVariant::Image) :
      return "Image";
   case(QVariant::Int) :
      return "Int";
   case(QVariant::KeySequence) :
      return "KeySequence";
   case(QVariant::Line) :
      return "Line";
   case(QVariant::LineF) :
      return "LineF";
   case(QVariant::List) :
      return "List";
   case(QVariant::Locale) :
      return "Locale";
   case(QVariant::LongLong) :
      return "LongLong";
   case(QVariant::Map) :
      return "Map";
   case(QVariant::Matrix) :
      return "Matrix";
   case(QVariant::Transform) :
      return "Transform";
   case(QVariant::Matrix4x4) :
      return "Matrix4x4";
   case(QVariant::Palette) :
      return "Palette";
   case(QVariant::Pen) :
      return "Pen";
   case(QVariant::Pixmap) :
      return "Pixmap";
   case(QVariant::Point) :
      return "Point";
   case(QVariant::PointF) :
      return "PointF";
   case(QVariant::Polygon) :
      return "Polygon";
   case(QVariant::PolygonF) :
      return "PolygonF";
   case(QVariant::Quaternion) :
      return "Quaternion";
   case(QVariant::Rect) :
      return "Rect";
   case(QVariant::RectF) :
      return "RectF";
   case(QVariant::RegExp) :
      return "RegExp";
   case(QVariant::RegularExpression) :
      return "RegularExpression";
   case(QVariant::Region) :
      return "Region";
   case(QVariant::Size) :
      return "Size";
   case(QVariant::SizeF) :
      return "SizeF";
   case(QVariant::SizePolicy) :
      return "SizePolicy";
   case(QVariant::String) :
      return "String";
   case(QVariant::StringList) :
      return "StringList";
   case(QVariant::TextFormat) :
      return "TextFormat";
   case(QVariant::TextLength) :
      return "TextLength";
   case(QVariant::Time) :
      return "Time";
   case(QVariant::UInt) :
      return "UInt";
   case(QVariant::ULongLong) :
      return "ULongLong";
   case(QVariant::Url) :
      return "Url";
   case(QVariant::Vector2D) :
      return "Vector2D";
   case(QVariant::Vector3D) :
      return "Vector3D";
   case(QVariant::Vector4D) :
      return "Vector4D";
   case(QVariant::UserType) :
      return "UserType";
   default:
      return "Invalid";
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	variantTypeFromString
//
//
//  \param  const QString &type -
//
//  \return QVariant::Type
//    
//  \author Stian Broen 
//
//  \date  01.01.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////
QVariant::Type imageProcessingSpace::variantTypeFromString(const QString &type)
{
   if (type == "BitArray")
      return QVariant::BitArray;
   if (type == "Bitmap")
      return QVariant::Bitmap;
   if (type == "Bool")
      return QVariant::Bool;
   if (type == "Brush")
      return QVariant::Brush;
   if (type == "ByteArray")
      return QVariant::ByteArray;
   if (type == "Char")
      return QVariant::Char;
   if (type == "Color")
      return QVariant::Color;
   if (type == "Cursor")
      return QVariant::Cursor;
   if (type == "Date")
      return QVariant::Date;
   if (type == "DateTime")
      return QVariant::DateTime;
   if (type == "Double")
      return QVariant::Double;
   if (type == "EasingCurve")
      return QVariant::EasingCurve;
   if (type == "Uuid")
      QVariant::Uuid;
   if (type == "ModelIndex")
      return QVariant::ModelIndex;
   if (type == "Font")
      return QVariant::Font;
   if (type == "Hash")
      return QVariant::Hash;
   if (type == "Icon")
      return QVariant::Icon;
   if (type == "Image")
      return QVariant::Image;
   if (type == "Int")
      return QVariant::Int;
   if (type == "KeySequence")
      return QVariant::KeySequence;
   if (type == "Line")
      return QVariant::Line;
   if (type == "LineF")
      return QVariant::LineF;
   if (type == "List")
      return QVariant::List;
   if (type == "Locale")
      return QVariant::Locale;
   if (type == "LongLong")
      return QVariant::LongLong;
   if (type == "Map")
      return QVariant::Map;
   if (type == "Matrix")
      return QVariant::Matrix;
   if (type == "Transform")
      return QVariant::Transform;
   if (type == "Matrix4x4")
      return QVariant::Matrix4x4;
   if (type == "Palette")
      return QVariant::Palette;
   if (type == "Pen")
      return QVariant::Pen;
   if (type == "Pixmap")
      return QVariant::Pixmap;
   if (type == "Point")
      return QVariant::Point;
   if (type == "PointF")
      return QVariant::PointF;
   if (type == "Polygon")
      return QVariant::Polygon;
   if (type == "PolygonF")
      return QVariant::PolygonF;
   if (type == "Quaternion")
      return QVariant::Quaternion;
   if (type == "Rect")
      return QVariant::Rect;
   if (type == "RectF")
      return QVariant::RectF;
   if (type == "RegExp")
      return QVariant::RegExp;
   if (type == "RegularExpression")
      return QVariant::RegularExpression;
   if (type == "Region")
      return QVariant::Region;
   if (type == "Size")
      return QVariant::Size;
   if (type == "SizeF")
      return QVariant::SizeF;
   if (type == "SizePolicy")
      return QVariant::SizePolicy;
   if (type == "String")
      return QVariant::String;
   if (type == "StringList")
      return QVariant::StringList;
   if (type == "TextFormat")
      return QVariant::TextFormat;
   if (type == "TextLength")
      return QVariant::TextLength;
   if (type == "Time")
      return QVariant::Time;
   if (type == "UInt")
      return QVariant::UInt;
   if (type == "ULongLong")
      return QVariant::ULongLong;
   if (type == "Url")
      return QVariant::Url;
   if (type == "Vector2D")
      return QVariant::Vector2D;
   if (type == "Vector3D")
      return QVariant::Vector3D;
   if (type == "Vector4D")
      return QVariant::Vector4D;
   if (type == "UserType")
      return QVariant::UserType;
   else
      return QVariant::Invalid;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	composeVariantFromString
//
//
//  \param  QVariant::Type type  -
//          const QString &value -
//
//  \return QVariant
//    
//  \author Stian Broen 
//
//  \date  01.01.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////
QVariant imageProcessingSpace::composeVariantFromString(QVariant::Type type, const QString &value)
{
   switch (type)
   {
   case(QVariant::BitArray) :
      return QVariant(value.toLatin1().constData());
   case(QVariant::Bool) :
      return QVariant(value.toInt());
   case(QVariant::ByteArray) :
      return QVariant(value.toLatin1());
   case(QVariant::Char) :
      if (value.size() > 0)
         return QVariant(value[0]);
   case(QVariant::Date) :
      return QVariant(QDate::fromString(value));
   case(QVariant::DateTime) :
      return QVariant(QDateTime::fromString(value));
   case(QVariant::Double) :
      return QVariant(value.toDouble());
   case(QVariant::Int) :
      return QVariant(value.toInt());
   case(QVariant::LongLong) :
      return QVariant(value.toLongLong());
   case(QVariant::String) :
      return QVariant(value);
   case(QVariant::Time) :
      return QVariant(QTime::fromString(value));
   case(QVariant::UInt) :
      return QVariant(value.toUInt());
   case(QVariant::ULongLong) :
      return QVariant(value.toULongLong());
   default:
      return QVariant(); // failed
   }
}

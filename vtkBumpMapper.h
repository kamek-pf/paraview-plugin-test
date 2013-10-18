/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkBumpMapper.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkBumpMapper - merge duplicate points, and/or remove unused points and/or remove degenerate cells
// .SECTION Description
// vtkBumpMapper is a filter that takes polygonal data as input and
// generates polygonal data as output. vtkBumpMapper can merge duplicate
// points (within specified ScaleFactor and if enabled), eliminate points
// that are not used, and if enabled, transform degenerate cells into
// appropriate forms (for example, a triangle is converted into a line
// if two points of triangle are merged).
//
// Conversion of degenerate cells is controlled by the flags
// ConvertLinesToPoints, ConvertPolysToLines, ConvertStripsToPolys which act
// cumulatively such that a degenerate strip may become a poly.
// The full set is
// Line with 1 points -> Vert (if ConvertLinesToPoints)
// Poly with 2 points -> Line (if ConvertPolysToLines)
// Poly with 1 points -> Vert (if ConvertPolysToLines && ConvertLinesToPoints)
// Strp with 3 points -> Poly (if ConvertStripsToPolys)
// Strp with 2 points -> Line (if ConvertStripsToPolys && ConvertPolysToLines)
// Strp with 1 points -> Vert (if ConvertStripsToPolys && ConvertPolysToLines
//   && ConvertLinesToPoints)
//
// If ScaleFactor is specified precisely=0.0, then vtkBumpMapper will use
// the vtkMergePoints object to merge points (which is faster). Otherwise the
// slower vtkIncrementalPointLocator is used.  Before inserting points into the point
// locator, this class calls a function OperateOnPoint which can be used (in
// subclasses) to further refine the cleaning process. See
// vtkQuantizePolyDataPoints.
//
// Note that merging of points can be disabled. In this case, a point locator
// will not be used, and points that are not used by any cells will be
// eliminated, but never merged.

// .SECTION Caveats
// Merging points can alter topology, including introducing non-manifold
// forms. The ScaleFactor should be chosen carefully to avoid these problems.
// Subclasses should handle OperateOnBounds as well as OperateOnPoint
// to ensure that the locator is correctly initialized (i.e. all modified
// points must lie inside modified bounds).
//
// .SECTION See Also
// vtkQuantizePolyDataPoints

#ifndef __vtkBumpMapper_h
#define __vtkBumpMapper_h

#include "vtkPolyDataAlgorithm.h"

class vtkIncrementalPointLocator;

class VTK_GRAPHICS_EXPORT vtkBumpMapper : public vtkPolyDataAlgorithm
{
public:
  static vtkBumpMapper *New();
  void PrintSelf(ostream& os, vtkIndent indent);
  vtkTypeMacro(vtkBumpMapper,vtkPolyDataAlgorithm);

  // Description:
  // Specify ScaleFactor in terms of fraction of bounding box length.
  // Default is 0.0.
  vtkSetClampMacro(ScaleFactor,double,0.0,1.0);
  vtkGetMacro(ScaleFactor,double);

  // Description:
  // Set/Get a spatial locator for speeding the search process. By
  // default an instance of vtkMergePoints is used.
  virtual void SetLocator(vtkIncrementalPointLocator *locator);
  vtkGetObjectMacro(Locator,vtkIncrementalPointLocator);

  // Description:
  // Create default locator. Used to create one when none is specified.
  void CreateDefaultLocator(vtkPolyData *input = 0);

  // Description:
  // Release locator
  void ReleaseLocator() { this->SetLocator(NULL); }




  // This filter is difficult to stream.
  // To get invariant results, the whole input must be processed at once.
  // This flag allows the user to select whether strict piece invariance
  // is required.  By default it is on.  When off, the filter can stream,
  // but results may change.
  //vtkSetMacro(PieceInvariant, int);
  //vtkGetMacro(PieceInvariant, int);
  //vtkBooleanMacro(PieceInvariant, int);

protected:
  vtkBumpMapper();
 ~vtkBumpMapper();

  // Usual data generation method
  virtual int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);



  double ScaleFactor;

  vtkIncrementalPointLocator *Locator;

  //int PieceInvariant;
private:
  vtkBumpMapper(const vtkBumpMapper&);  // Not implemented.
  void operator=(const vtkBumpMapper&);  // Not implemented.
};

#endif

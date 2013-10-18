/*=========================================================================

Program:   Visualization Toolkit
Module:    vtkBumpMapper.cxx

Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
All rights reserved.
See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkBumpMapper.h"

#include "vtkDoubleArray.h"
#include "vtkCellData.h"
#include "vtkMergePoints.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkPointData.h"
#include "vtkPolyData.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkIncrementalPointLocator.h"

vtkStandardNewMacro(vtkBumpMapper);

//---------------------------------------------------------------------------
// Specify a spatial locator for speeding the search process. By
// default an instance of vtkPointLocator is used.
vtkCxxSetObjectMacro(vtkBumpMapper,Locator,vtkIncrementalPointLocator);

//---------------------------------------------------------------------------
// Construct object with initial Tolerance of 0.0
vtkBumpMapper::vtkBumpMapper()
{
    this->scaleFactor = 1.0;
}

//--------------------------------------------------------------------------
vtkBumpMapper::~vtkBumpMapper()
{
}

//--------------------------------------------------------------------------
    int vtkBumpMapper::RequestData(
            vtkInformation *vtkNotUsed(request),
            vtkInformationVector **inputVector,
            vtkInformationVector *outputVector)
{
    // get the info objects
    vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
    vtkInformation *outInfo = outputVector->GetInformationObject(0);

    // get the input and output
    vtkPolyData *input = vtkPolyData::SafeDownCast(
            inInfo->Get(vtkDataObject::DATA_OBJECT()));
    vtkPolyData *output = vtkPolyData::SafeDownCast(
            outInfo->Get(vtkDataObject::DATA_OBJECT()));

    output->CopyStructure(input);
    //output->GetPointData()->PassData(input->GetPointData()); //copie tous les points de l'entree sur la sortie

    //vtkDataArray *normals = output->GetPointData()->GetNormals();
    vtkDataArray *normals = input->GetPointData()->GetNormals();
    vtkDoubleArray *newNormals = vtkDoubleArray::New();

    newNormals->SetName("New normals");
    newNormals->SetNumberOfComponents(normals->GetNumberOfComponents());
    newNormals->SetNumberOfTuples(normals->GetNumberOfTuples());

    for(vtkIdType i=0; i<normals->GetNumberOfTuples(); i++)
    {
        double normale[3];
        normals->GetTuple(i,normale);
        normale[0] *=this->scaleFactor;
        normale[1] *=this->scaleFactor;
        normale[2] *=this->scaleFactor;

        newNormals->SetTuple(i,normale);

    }

    output->GetPointData()->SetNormals(newNormals);
    newNormals->Delete();

    return 1;
}

//--------------------------------------------------------------------------
void vtkBumpMapper::PrintSelf(ostream& os, vtkIndent indent)
{
    this->Superclass::PrintSelf(os,indent);

    os << indent << "Scale Factor: "
        << this->scaleFactor;
}


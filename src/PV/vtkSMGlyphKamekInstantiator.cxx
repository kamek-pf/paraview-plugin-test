#include "vtkSMGlyphKamekInstantiator.h"
  
extern vtkObject* vtkInstantiatorvtkGlyphKamekNew();


  
void vtkSMGlyphKamekInstantiator::ClassInitialize()
{
  
  vtkInstantiator::RegisterInstantiator("vtkGlyphKamek", vtkInstantiatorvtkGlyphKamekNew);

  
}
          
void vtkSMGlyphKamekInstantiator::ClassFinalize()
{ 

  vtkInstantiator::UnRegisterInstantiator("vtkGlyphKamek", vtkInstantiatorvtkGlyphKamekNew);

  
}

vtkSMGlyphKamekInstantiator::vtkSMGlyphKamekInstantiator()
{
  if(++vtkSMGlyphKamekInstantiator::Count == 1)
    { 
    vtkSMGlyphKamekInstantiator::ClassInitialize(); 
    }
}

vtkSMGlyphKamekInstantiator::~vtkSMGlyphKamekInstantiator()
{
  if(--vtkSMGlyphKamekInstantiator::Count == 0)
    { 
    vtkSMGlyphKamekInstantiator::ClassFinalize(); 
    }
}

// Number of translation units that include this class's header.
// Purposely not initialized.  Default is static initialization to 0.
unsigned int vtkSMGlyphKamekInstantiator::Count;

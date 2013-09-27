#ifndef __vtkSMGlyphKamekInstantiator_h
#define __vtkSMGlyphKamekInstantiator_h

#include "vtkInstantiator.h"



class VTK_EXPORT vtkSMGlyphKamekInstantiator
{
  public:
  vtkSMGlyphKamekInstantiator();
  ~vtkSMGlyphKamekInstantiator();
  private:
  static void ClassInitialize();
  static void ClassFinalize();
  static unsigned int Count;
}; 

static vtkSMGlyphKamekInstantiator vtkSMGlyphKamekInstantiatorInitializer;

#endif

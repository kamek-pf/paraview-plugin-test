#include "vtkClientServerInterpreter.h"

#ifndef PARAVIEW_BUILD_SHARED_LIBS
#define PARAVIEW_BUILD_SHARED_LIBS
#endif
#if defined(PARAVIEW_BUILD_SHARED_LIBS) && defined(_WIN32)
# define VTK_WRAP_CS_EXPORT __declspec(dllexport)
#else
# define VTK_WRAP_CS_EXPORT
#endif

extern void vtkGlyphKamek_Init(vtkClientServerInterpreter* csi);


extern "C" void VTK_WRAP_CS_EXPORT GlyphKamek_Initialize(
  vtkClientServerInterpreter *csi)
{
  vtkGlyphKamek_Init(csi);

}

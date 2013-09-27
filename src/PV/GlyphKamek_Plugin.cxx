/*=========================================================================

   Program: ParaView
   Module:    pqParaViewPlugin.cxx.in

   Copyright (c) 2005,2006 Sandia Corporation, Kitware Inc.
   All rights reserved.

   ParaView is a free software; you can redistribute it and/or modify it
   under the terms of the ParaView license version 1.2. 

   See License_v1.2.txt for the full ParaView license.
   A copy of this license can be obtained by contacting
   Kitware Inc.
   28 Corporate Drive
   Clifton Park, NY 12065
   USA

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

========================================================================*/
#include "GlyphKamek_Plugin.h"

#include "vtkObjectFactory.h"

#include "/home/27/bbousque/Visualisation/TP2/src/PV/vtkSMXML_GlyphKamek.h"
#include "vtkSMGlyphKamekInstantiator.h"

#include "/home/27/bbousque/Visualisation/TP2/src/PV/GlyphKamek_doc.h"

//-----------------------------------------------------------------------------
// Used to push a string returns from a function to a vector.
template <class T, class F>
void PushBack(T& vector, F& fun)
{
  char* text = fun();
  vector.push_back(text);
  delete []text;
}

//-----------------------------------------------------------------------------
#ifdef plugin_type_servermanager
# ifdef INITIALIZE_WRAPPING
#  include "vtkClientServerInterpreterInitializer.h"
#  include "vtkClientServerInterpreter.h"

extern "C" void GlyphKamek_Initialize(vtkClientServerInterpreter *);

extern "C" void VTK_EXPORT GlyphKamek_CombinedInitialize(
  vtkClientServerInterpreter *interp)
{
  GlyphKamek_Initialize(interp);

  // Now initialize any extra kits as requested.
  
}
# endif
#endif

//-----------------------------------------------------------------------------
void GlyphKamek_Plugin::GetBinaryResources(
  std::vector<std::string>& resources)
{
  PushBack(resources, GlyphKamek_doc);

  (void)resources;
}

//-----------------------------------------------------------------------------
#ifdef plugin_type_gui


#endif

//-----------------------------------------------------------------------------
#ifdef plugin_type_servermanager
vtkClientServerInterpreterInitializer::InterpreterInitializationCallback
GlyphKamek_Plugin::GetInitializeInterpreterCallback()
{
# ifdef INITIALIZE_WRAPPING
  return GlyphKamek_CombinedInitialize;
# endif
  return NULL;
}

//-----------------------------------------------------------------------------
void GlyphKamek_Plugin::GetXMLs(std::vector<std::string> &xmls)
{
  PushBack(xmls, GlyphKamekGlyphKamekInterfaces);

  (void)xmls;
}
#endif

//-----------------------------------------------------------------------------
#ifdef plugin_type_gui
QObjectList GlyphKamek_Plugin::interfaces()
{
  QObjectList ifaces;
#ifdef PUSH_BACK_PV_INTERFACES
  PUSH_BACK_PV_INTERFACES(ifaces);
#endif
  return ifaces;
}
#endif

//-----------------------------------------------------------------------------
#ifdef plugin_type_python


void GlyphKamek_Plugin::GetPythonSourceList(std::vector<std::string>& modules,
  std::vector<std::string>& sources,
  std::vector<int> &package_flags)
{
  const char *moduleNames[] = {
    
  };
  char *moduleSources[] = {
    
  };
  const int packageFlags[] = {
    
  };

  int num_modules = sizeof(moduleNames)/sizeof(const char *);
  for (int cc=0; cc < num_modules; cc++)
    {
    modules.push_back(moduleNames[cc]);
    sources.push_back(moduleSources[cc]);
    package_flags.push_back(packageFlags[cc]);

    // free allocated memory.
    delete moduleSources[cc];
    moduleSources[cc] = NULL;
    }
}
#endif

//-----------------------------------------------------------------------------
// Mark this as a ParaView-ServerManager plugin.
PV_PLUGIN_EXPORT(GlyphKamek, GlyphKamek_Plugin)

//-----------------------------------------------------------------------------
#ifdef BUILD_SHARED_LIBS
#ifdef plugin_type_gui

// Required to mark this as a Qt plugin.
Q_EXPORT_PLUGIN2(GlyphKamek,  GlyphKamek_Plugin)
#endif
#endif

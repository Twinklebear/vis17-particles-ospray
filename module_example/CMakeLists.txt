set(CMAKE_CXX_STANDARD 11)

# Also see the pluggableGeometryExample which is included with OSPRay

ospray_create_library(ospray_module_colormapped_spheres
  ColormappedSpheres.cpp
  ColormappedSpheres.ispc
  moduleInit.cpp
  LINK
  ospray
)

ospray_create_application(colormapped_spheres_app
  colormapped_spheres_app.cpp
  LINK
  ospray)


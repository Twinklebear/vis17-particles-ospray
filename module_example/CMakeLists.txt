cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)

# Also see the pluggableGeometryExample which is included with OSPRay

# If we were passed -Dospray_DIR this module is being built outside
# of the OSPRay source. Otherwise we assume we're being built in the OSPRay
# build tree as a module under ospray/modules/
if (ospray_DIR)
  find_package(ospray REQUIRED)
  include(${OSPRAY_USE_FILE})

  include_directories(${OSPRAY_INCLUDE_DIRS})

  ospray_create_library(ospray_module_colormapped_spheres
    ColormappedSpheres.cpp
    ColormappedSpheres.ispc
    moduleInit.cpp
    LINK
    ${OSPRAY_LIBRARIES}
    )

  ospray_create_application(colormapped_spheres_app
    colormapped_spheres_app.cpp
    LINK
    ${OSPRAY_LIBRARIES})

else()

  ospray_create_library(ospray_module_colormapped_spheres
    ColormappedSpheres.cpp
    ColormappedSpheres.ispc
    moduleInit.cpp
    LINK
    ${OSPRAY_LIBRARIES}
    )

  ospray_create_application(colormapped_spheres_app
    colormapped_spheres_app.cpp
    LINK
    ${OSPRAY_LIBRARIES})
endif()


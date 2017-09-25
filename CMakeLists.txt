cmake_minimum_required(VERSION 3.1)
project(vis17_particles_ospray)

option(OSPRAY_MODULE_COLORMAPPED_SPHERES "Colormapped Spheres Module" ON)
if (OSPRAY_MODULE_COLORMAPPED_SPHERES)
  add_subdirectory(module_example)
endif()


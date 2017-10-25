#include <iostream>
#include "ColormappedSpheres.h"

extern "C" VIS17_COLORMAPPED_SPHERES_EXPORT void ospray_init_module_colormapped_spheres() {
  std::cout << "vis17: ColorMapped spheres module initializing" << std::endl;
}


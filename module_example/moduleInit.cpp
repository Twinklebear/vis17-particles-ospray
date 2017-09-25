#include <iostream>

extern "C" void ospray_init_module_colormapped_spheres() {
  std::cout << "vis17: ColorMapped spheres module initializing" << std::endl;
}


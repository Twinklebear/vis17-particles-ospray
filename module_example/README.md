# Sample OSPRay Module 

This module can be built in source with OSPRay from source, or against a distribution
of OSPRay.

## Building in Source with OSPRay

Get the [OSPRay](https://github.com/ospray/ospray) source code and clone the
repo into the modules subdirectory, then build OSPRay.

## Building Against a Distribution of OSPRay

Make a build directory in this subdirectory, then run CMake and point CMake
to the various dependencies. Besides OSPRay you'll need
[Embree](https://embree.github.io/), [TBB](https://www.threadingbuildingblocks.org/),
and [ISPC](http://ispc.github.io/).

```
cmake .. \
  -Dospray_DIR=<path to ospray install>/lib/cmake/ospray-<version>/ \
  -Dembree_DIR=<path to embree> \
  -DTBB_ROOT=<path to tbb> \
  -DISPC_EXECUTABLE=<path to ispc executable>
```


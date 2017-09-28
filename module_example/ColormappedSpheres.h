// ======================================================================== //
// Copyright 2009-2017 Intel Corporation                                    //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#pragma once

#include "geometry/Geometry.h"
#include "common/Model.h"
#include "common/Data.h"
#include "transferFunction/TransferFunction.h"

#if defined (_WIN32)
  #if defined(ospray_module_colormapped_spheres_EXPORTS)
    #define VIS17_COLORMAPPED_SPHERES_EXPORT __declspec(dllexport)
  #else
    #define VIS17_COLORMAPPED_SPHERES_EXPORT __declspec(dllimport)
  #endif
#else
  #define VIS17_COLORMAPPED_SPHERES_EXPORT
#endif


namespace vis17 {

  // A geometry for a set of colormapped spheres
  struct VIS17_COLORMAPPED_SPHERES_EXPORT ColormappedSpheres
    : public ospray::Geometry
  {
    ColormappedSpheres();

    virtual std::string toString() const override;
    virtual void finalize(ospray::Model *model) override;

    /*! default radius, if no per-sphere radius was specified. */
    float radius;
    int32_t materialID;

    size_t numSpheres;
    size_t bytesPerSphere;
    int64_t offset_center;
    int64_t offset_radius;
    int64_t offset_attribute;

    ospray::Ref<ospray::Data> sphereData;
    ospray::Ref<ospray::TransferFunction> transferFunction;

    float epsilon;
  };

}


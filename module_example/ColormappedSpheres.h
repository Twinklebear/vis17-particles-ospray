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

namespace vis17 {

  /*! \brief A geometry for a set of colormapped spheres

    Implements the \ref geometry_spheres geometry

  */
  struct OSPRAY_SDK_INTERFACE ColormappedSpheres : public ospray::Geometry
  {
    ColormappedSpheres();

    virtual std::string toString() const override;
    virtual void finalize(ospray::Model *model) override;

    // Data members //

    /*! default radius, if no per-sphere radius was specified. */
    float radius;
    int32_t materialID;

    size_t numSpheres;
    size_t bytesPerSphere; //!< num bytes per sphere
    int64_t offset_center;
    int64_t offset_radius;
    int64_t offset_attribute;

    ospray::Ref<ospray::Data> sphereData;
    ospray::Ref<ospray::TransferFunction> transferFunction;

    float epsilon;  //epsilon for intersections
  };
  /*! @} */

} // ::ospray


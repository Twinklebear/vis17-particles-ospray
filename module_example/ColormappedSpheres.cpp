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

// ospray
#include "ColormappedSpheres.h"
#include "common/Data.h"
#include "common/Model.h"
// ispc-generated files
#include "ColormappedSpheres_ispc.h"

namespace vis17 {

  using namespace ospray;

  ColormappedSpheres::ColormappedSpheres()
  {
    this->ispcEquivalent = ispc::ColormappedSpheres_create(this);
  }

  std::string ColormappedSpheres::toString() const
  {
    return "vis17::ColormappedSpheres";
  }

  void ColormappedSpheres::finalize(Model *model)
  {
    radius            = getParam1f("radius", 0.01f);
    materialID        = getParam1i("materialID", 0);
    bytesPerSphere    = getParam1i("bytes_per_sphere", 4*sizeof(float));
    offset_center     = getParam1i("offset_center", 0);
    offset_radius     = getParam1i("offset_radius", -1);
    offset_attribute  = getParam1i("offset_attribute", -1);
    sphereData        = getParamData("spheres");

    if (sphereData.ptr == nullptr) {
      throw std::runtime_error("#vis17:ColormappedSpheres: no 'spheres' data "
                               "specified");
    }

    numSpheres = sphereData->numBytes / bytesPerSphere;
    postStatusMsg(2) << "#vis17: creating 'colormapped_spheres' geometry, #spheres = "
                     << numSpheres;

    if (numSpheres >= (1ULL << 30)) {
      throw std::runtime_error("#ospray::ColormappedSpheres: too many spheres in this "
                               "sphere geometry. Consider splitting this "
                               "geometry in multiple geometries with fewer "
                               "spheres (you can still put all those "
                               "geometries into a single model, but you can't "
                               "put that many spheres into a single geometry "
                               "without causing address overflows)");
    }

    const char* spherePtr = (const char*)sphereData->data;
    bounds = empty;
    for (uint32_t i = 0; i < numSpheres; i++, spherePtr += bytesPerSphere) {
      const float r = offset_radius < 0 ? radius : *(float*)(spherePtr + offset_radius);
      const vec3f center = *(vec3f*)(spherePtr + offset_center);
      bounds.extend(box3f(center - r, center + r));
    }

    ispc::ColormappedSpheresGeometry_set(getIE(),
                                         model->getIE(),
                                         sphereData->data,
                                         numSpheres,
                                         bytesPerSphere,
                                         radius,
                                         materialID,
                                         offset_center,
                                         offset_radius,
                                         offset_attribute);
  }

  OSP_REGISTER_GEOMETRY(ColormappedSpheres,colormapped_spheres);

} // ::ospray

cmake_minimum_required(VERSION 3.5)
project(simple_particles)

set(CMAKE_CXX_STANDARD 14)

find_package(ospray REQUIRED)
include_directories(${OSPRAY_INCLUDE_DIRS})

add_executable(simple_particles simple_particles.cpp)
target_link_libraries(simple_particles ${OSPRAY_LIBRARIES})


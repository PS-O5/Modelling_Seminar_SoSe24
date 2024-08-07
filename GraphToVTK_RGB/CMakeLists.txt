cmake_minimum_required(VERSION 3.10)
project(PartitionedVTK)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(PartitionedVTK main.cxx)
target_link_libraries(PartitionedVTK ${VTK_LIBRARIES})

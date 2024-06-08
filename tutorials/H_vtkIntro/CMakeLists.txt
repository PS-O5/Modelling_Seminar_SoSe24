cmake_minimum_required(VERSION 3.8)
project(TestVTK)

set(VTK_DIR "/usr/include/vtk-9.1/")


# Find VTK package
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(test_vtk vtkCheck.cxx)

# Link VTK libraries
target_link_libraries(test_vtk ${VTK_LIBRARIES})

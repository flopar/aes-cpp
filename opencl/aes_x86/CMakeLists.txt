cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(aes_x86)

# for some reasons my OpenCL installed the necessary headers and libraries but these were recognized by CMake
# therefore I set the variables by hand

set(OpenCL_LIBRARY /usr/lib/x86_64-linux-gnu/libOpenCL.so.1.0.0)
set(OpenCL_INCLUDE /usr/include/CL/)
find_package(OpenCL REQUIRED)

add_subdirectory(src)

add_executable(main main.cpp)

target_link_libraries(main OpenCL::OpenCL)
target_include_directories(main PUBLIC OpenCL_INCLUDE)

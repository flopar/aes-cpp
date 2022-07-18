add_library(aes STATIC aes.cpp aes.hpp)
add_library(utility STATIC utility.cpp utility.hpp)
set_target_properties(utility PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
	CMAKE_CXX_STANDARD 20)
set_target_properties(aes PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
target_link_libraries(aes utility)

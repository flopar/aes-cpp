add_library(aes STATIC aes.cpp aes.hpp)
set_target_properties(aes PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(utility STATIC utility.hpp utility.cpp)
set_target_properties(utility PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

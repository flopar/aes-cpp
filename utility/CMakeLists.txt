add_library(utility STATIC utility.cpp utility.hpp)
set_target_properties(utility PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

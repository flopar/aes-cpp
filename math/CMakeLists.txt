add_library(math INTERFACE)

target_include_directories(math INTERFACE
	vector
	matrix)
target_sources(math INTERFACE
	vector/vector.cpp
	matrix/matrix.cpp)

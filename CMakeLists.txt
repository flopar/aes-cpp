cmake_minimum_required(VERSION 3.12...3.21)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
	cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

set(CMAKE_CXX_COMPILER /usr/bin/g++-8)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(AES	VERSION 1.0
		DESCRIPTION "AES implementation"
		LANGUAGES CXX)

add_subdirectory(math)
add_subdirectory(aes)
add_subdirectory(test)
add_subdirectory(utility)


target_include_directories(test PUBLIC aes)
target_include_directories(aes PUBLIC utility math)
target_link_libraries(aes math utility)
target_link_libraries(test aes)






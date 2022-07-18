cmake_minimum_required(VERSION 3.12...3.21)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
	cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}i)
endif()


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(AES	VERSION 1.0
		DESCRIPTION "AES implementation"
		LANGUAGES CXX)

add_subdirectory(aes)
add_subdirectory(test)

target_include_directories(test PUBLIC aes)

target_link_libraries(test aes)

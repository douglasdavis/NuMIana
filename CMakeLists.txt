cmake_minimum_required(VERSION 2.8)
project(NuMIana)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_CXX_FLAGS "-g -m64 -O3 -std=c++11")
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}")

find_package(ROOT REQUIRED)
include_directories("${ROOT_INC_DIR}")
link_directories("${ROOT_LIB_DIR}")

## -- prepare project include and lib dirs
include_directories("${CMAKE_SOURCE_DIR}/include")
link_directories("${CMAKE_SOURCE_DIR}/lib")

add_library(NuMIana SHARED WindowAna.cc LArAna.cc DAnaLibs.cc)
target_link_libraries(NuMIana ${ROOT_LIBS})

add_subdirectory(anas)
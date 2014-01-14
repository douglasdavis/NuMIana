include_directories(${CMAKE_SOURCE_DIR})
add_executable(ex ex.cpp)
target_link_libraries(ex ${ROOT_LIBS} NuMIana)

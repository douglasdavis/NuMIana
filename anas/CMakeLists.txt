include_directories(${CMAKE_SOURCE_DIR})

add_executable(windowex windowex.cpp)
target_link_libraries(windowex ${ROOT_LIBS} NuMIana)

add_executable(larex larex.cpp)
target_link_libraries(larex ${ROOT_LIBS} NuMIana)

add_executable(fluggex fluggex.cpp)
target_link_libraries(fluggex ${ROOT_LIBS})

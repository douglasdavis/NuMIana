include_directories(${CMAKE_SOURCE_DIR})

add_executable(gsimpex gsimpex.cpp)
target_link_libraries(gsimpex ${ROOT_LIBS} NuMIana)

add_executable(larex larex.cpp)
target_link_libraries(larex ${ROOT_LIBS} LArAna)

add_executable(fluggex fluggex.cpp)
target_link_libraries(fluggex ${ROOT_LIBS})

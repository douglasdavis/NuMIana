include_directories(${CMAKE_SOURCE_DIR})
add_executable(gsimpex gsimpex.cpp)
target_link_libraries(ex ${ROOT_LIBS} NuMIana)

add_executable(larex larex.cpp)
target_link_libraries(larex ${ROOT_LIBS} LArAna)

add_executable(fluggana FLUGG_ana.cpp)
target_link_libraries(fluggana ${ROOT_LIBS})

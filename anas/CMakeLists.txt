include_directories(${CMAKE_SOURCE_DIR})

add_executable(simpleex simpleex.cpp)
target_link_libraries(simpleex ${ROOT_LIBS} NuMIana)

add_executable(larex larex.cpp)
target_link_libraries(larex ${ROOT_LIBS} NuMIana)

add_executable(fluggex fluggex.cpp)
target_link_libraries(fluggex ${ROOT_LIBS} NuMIana)

add_executable(ppmediumAna ppmediumAna)
target_link_libraries(ppmediumAna ${ROOT_LIBS} NuMIana)
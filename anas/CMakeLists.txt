include_directories(${CMAKE_SOURCE_DIR})

#add_executable(simples_flux simples_flux.cpp)
#target_link_libraries(simples_flux ${ROOT_LIBS} NuMIana)

#add_executable(larex larex.cpp)
#target_link_libraries(larex ${ROOT_LIBS} NuMIana)

#add_executable(fluggex fluggex.cpp)
#target_link_libraries(fluggex ${ROOT_LIBS} NuMIana)

#add_executable(ppmediumAna ppmediumAna)
#target_link_libraries(ppmediumAna ${ROOT_LIBS} NuMIana)

add_executable(numiEvRate numiEvRate.cpp)
target_link_libraries(numiEvRate ${ROOT_LIBS} NuMIana)

#add_executable(simple2 simple2.cpp)
#target_link_libraries(simple2 ${ROOT_LIBS} NuMIana)

#add_executable(lartreeana lartreeana.cpp)
#target_link_libraries(lartreeana ${ROOT_LIBS} NuMIana)

#add_executable(lna lna.cpp)
#target_link_libraries(lna ${ROOT_LIBS} NuMIana)

add_executable(DEhist DEhist.cpp)
target_link_libraries(DEhist ${ROOT_LIBS} NuMIana)

add_executable(FullDEhist FullDEhist.cpp)
target_link_libraries(FullDEhist ${ROOT_LIBS} NuMIana)

add_executable(DEnue DEnue.cpp)
target_link_libraries(DEnue ${ROOT_LIBS} NuMIana)

add_executable(FullDEnue FullDEnue.cpp)
target_link_libraries(FullDEnue ${ROOT_LIBS} NuMIana)


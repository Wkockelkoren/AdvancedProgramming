project (PathPlanner)
cmake_minimum_required (VERSION 3.7)


set(SDL2_DIR "include/SDL2-2.0.9")
find_package(SDL2 REQUIRED)
include_directories(include ${SDL2_INCLUDE_DIRS})

if(MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Qpar /MP /O2 /DNDEBUG")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE}")
else(MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

	set(CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS_RELEASE}")
endif(MSVC)

SET(HEADERFILES
	include/Map.h
	include/PointOfInterest.h
	include/Vehicle.h
)
SOURCE_GROUP("Header Files" FILES ${HEADERFILES})

SET(SOURCEFILES
	main.cpp 
	include/Map.cpp
	include/PointOfInterest.cpp
	include/Vehicle.cpp
)
  
add_executable(PathPlanner
	${SOURCEFILES}
	${HEADERFILES}
)

target_link_libraries(PathPlanner ${SDL2_LIBRARIES})
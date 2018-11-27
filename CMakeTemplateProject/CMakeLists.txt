project (PathPlanner)
cmake_minimum_required (VERSION 3.0.2)

include_directories(include)

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

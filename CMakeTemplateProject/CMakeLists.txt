cmake_minimum_required (VERSION 3.7)

# Fix behavior of CMAKE_CXX_STANDARD when targeting macOS.
if (POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif ()

project (PathPlanner)

if(MSVC)
	set(SDL2_DIR "ext/SDL2-2.0.9")
endif(MSVC)

find_package(SDL2 REQUIRED)

include_directories(	
	include
	${SDL2_INCLUDE_DIRS}
)

if(MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Qpar /MP /O2 /DNDEBUG /EHsc")
	set (CMAKE_CXX_STANDARD 11)
    
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else(MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
	set (CMAKE_CXX_STANDARD 11)
    
    # lots of warnings
    add_compile_options(-Wall -Wextra -pedantic)
endif(MSVC)

SET(HEADERFILES
	include/Map.h
	include/TaskManager.h
	include/SampleAlgorithm.h
	include/VehicleManager.h
	include/PointOfInterest.h
	include/Vehicle.h
	include/Window.h
	include/Structures.h
    include/Menu.h
)
    
SOURCE_GROUP("Header Files" FILES ${HEADERFILES})

SET(SOURCEFILES
	main.cpp
	include/Map.cpp
	include/TaskManager.cpp
	include/SampleAlgorithm.cpp
	include/VehicleManager.cpp
	include/PointOfInterest.cpp
	include/Vehicle.cpp
	include/Window.cpp
    include/Menu.cpp
)

add_executable(PathPlanner
	${SOURCEFILES}
	${HEADERFILES}
)

target_link_libraries(
	PathPlanner
	${SDL2_LIBRARIES}
)


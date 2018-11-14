project (Unit-Test)
cmake_minimum_required (VERSION 3.0.2)

include_directories(include)

if(MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE}")
else(MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

	set(CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS_RELEASE}")
endif(MSVC)

SET(HEADERFILES
	include/EulerAngles.h
	include/MotionProfiles.h
	include/xxfuncs.h
	include/xxinverse.h
	include/xxmatrix.h
	include/xxtypes.h
)
SOURCE_GROUP("Header Files" FILES ${HEADERFILES})

SET(SOURCEFILES
	main.cpp 
	include/EulerAngles.cpp
	include/MotionProfiles.cpp
	include/xxfuncs.cpp
	include/xxinverse.cpp
	include/xxmatrix.cpp
)
  
add_executable(Unit-Test
	${SOURCEFILES}
	${HEADERFILES}
)

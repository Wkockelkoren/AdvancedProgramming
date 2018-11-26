project (PathPlanner)
cmake_minimum_required (VERSION 3.0.2)

include_directories(include)

add_subdirectory(include/wxWidgets-3.1.1)

if(MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Qpar /MP /O2 /DNDEBUG")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE}")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
else(MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

	set(CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS_RELEASE}")
endif(MSVC)

SET(HEADERFILES
)
SOURCE_GROUP("Header Files" FILES ${HEADERFILES})

SET(SOURCEFILES
	main.cpp
)
  
add_executable(${PROJECT_NAME}
	${SOURCEFILES}
	${HEADERFILES}
)

target_link_libraries(${PROJECT_NAME} net core base)
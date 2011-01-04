cmake_minimum_required(VERSION 2.6)


INCLUDE(FindPkgConfig)

pkg_check_modules(IO REQUIRED "iodrivers_base")
INCLUDE_DIRECTORIES(. /usr/include/eigen2 ${IO_INCLUDE_DIRS} .)
LINK_DIRECTORIES(${IO_LIBRARY_DIRS} )


add_executable(dsp3000_test
	dsp3000.cpp
	main.cpp
)

add_library(dsp3000 SHARED
	dsp3000.cpp
)

TARGET_LINK_LIBRARIES(dsp3000
	${IO_LIBRARIES}
)

TARGET_LINK_LIBRARIES(dsp3000_test 
	${IO_LIBRARIES}
)

INSTALL(TARGETS dsp3000 
	LIBRARY DESTINATION lib
)


INSTALL(FILES dsp3000.h DESTINATION include)
	
CONFIGURE_FILE(dsp3000.pc.in dsp3000.pc @ONLY)

INSTALL(FILES 
	${CMAKE_BINARY_DIR}/dsp3000.pc 
	DESTINATION lib/pkgconfig
)



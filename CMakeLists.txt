cmake_minimum_required(VERSION 2.6)
find_package(Rock)

rock_init(fog_kvh 0.1)
rock_doxygen()

rock_library(fog_kvh dsp3000.cpp
	HEADERS dsp3000.h
	DEPS_PKGCONFIG iodrivers_base)

rock_executable(fog_kvh_test main.cpp
	DEPS fog_kvh)


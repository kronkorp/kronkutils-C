cmake_minimum_required(VERSION 3.16)

project(kronkdynarray C)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(KRONKDYNARRAY_SOURCES
	src/dynarray_clear.c
	src/dynarray_free.c
	src/dynarray_getters.c
	src/dynarray_init.c
	src/dynarray_push.c
)

add_library(kronkdynarray_objects OBJECT ${KRONKDYNARRAY_SOURCES})

target_include_directories(kronkdynarray_objects PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

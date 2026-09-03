cmake_minimum_required(VERSION 3.16)

project(kronkutils C)

include(CTest)

add_subdirectory(dynarray)

add_library(kronkutils_static STATIC
	$<TARGET_OBJECTS:kronkdynarray_objects>
)

add_library(kronkutils_shared SHARED
	$<TARGET_OBJECTS:kronkdynarray_objects>
)

set_target_properties(kronkutils_static kronkutils_shared PROPERTIES
	OUTPUT_NAME kronkutils
)

target_include_directories(kronkutils_static PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/dynarray/include
)

target_include_directories(kronkutils_shared PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/dynarray/include
)

if(BUILD_TESTING)
	include(FetchContent)

	FetchContent_Declare(
		kronklab
		GIT_REPOSITORY https://github.com/kronkorp/kronklab.git
		GIT_TAG 5584149a3c9ccbb12baaf71cfd591db3b37541ad
	)
	FetchContent_MakeAvailable(kronklab)

	add_executable(kronkutils_tests
		tests/dynarray_test.c
	)
	target_link_libraries(kronkutils_tests PRIVATE
		kronkutils_static
		kronklab-static
	)
	target_compile_features(kronkutils_tests PRIVATE c_std_11)

	add_test(NAME dynarray COMMAND kronkutils_tests)
endif()
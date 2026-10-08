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

if(MSVC)
	# NOTE: The import library of the DLL is already kronkutils.lib (two rules making
	#       the same file: Ninja refuses to build)
	set_target_properties(kronkutils_static PROPERTIES OUTPUT_NAME kronkutils_static)
endif()

# NOTE: On Windows, a DLL only gives what it exports: nothing is marked for it, so
#       it exports all
set_target_properties(kronkutils_shared PROPERTIES
	WINDOWS_EXPORT_ALL_SYMBOLS ON
)

target_include_directories(kronkutils_static PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/dynarray/include
)

target_include_directories(kronkutils_shared PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/dynarray/include
)

# NOTE: kronklab runs each test in a fork(), which Windows does not have
if(BUILD_TESTING AND WIN32)
	message(STATUS "kronkutils: the tests need kronklab, which runs on POSIX only: not built")
elseif(BUILD_TESTING)
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
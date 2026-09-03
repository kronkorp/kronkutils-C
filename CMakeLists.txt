cmake_minimum_required(VERSION 3.16)

project(kronkutils C)

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

# target_sources(kronkutils_static PRIVATE
# 	$<TARGET_OBJECTS:kronkdynarray_objects>
# )

# target_sources(kronkutils_shared PRIVATE
# 	$<TARGET_OBJECTS:kronkdynarray_objects>
# )

# set_target_properties(kronkutils_static PROPERTIES
# 	OUTPUT_NAME kronkutils
# )

# set_target_properties(kronkutils_shared PROPERTIES
# 	OUTPUT_NAME kronkutils
# )

# target_include_directories(kronkutils_static PUBLIC
# 	${CMAKE_CURRENT_SOURCE_DIR}/dynarray/include
# )

# target_include_directories(kronkutils_shared PUBLIC
# 	${CMAKE_CURRENT_SOURCE_DIR}/dynarray/include
# )
cmake_minimum_required (VERSION 3.2.2)
project (scener::math)
enable_language(CXX)

# header files
file (GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

# source files
file (GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# library output
add_library (scener-math SHARED ${HEADER_FILES} ${SOURCE_FILES})

# include directories
target_include_directories (scener-math PRIVATE ${GSL_INCLUDE_DIRS})

# target links
target_link_libraries (scener-math)
set_target_properties (scener-math PROPERTIES LINKER_LANGUAGE CXX)

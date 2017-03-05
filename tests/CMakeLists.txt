cmake_minimum_required (VERSION 3.2.2)
project (scener::math::tests)
enable_language(CXX)

# google test
download_project(PROJ           googletest
                 GIT_REPOSITORY https://github.com/google/googletest.git
                 GIT_TAG        master)

add_subdirectory (${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)

# pthread
find_package (Threads REQUIRED)

# link directories
link_directories (${googletest_BINARY_DIR})

# header files
file (GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

# source files
file (GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# add execlutable
add_executable (test-runner ${HEADER_FILES} ${SOURCE_FILES})

# target include directories
target_include_directories (test-runner
                            PRIVATE ${googletest_SOURCE_DIR}/googletest/include
                            PRIVATE ${GSL_INCLUDE_DIRS}
                            PRIVATE ${SCENER_MATH_INCLUDE_DIRS})

# target link libraries
target_link_libraries (test-runner pthread gtest)

# unit tests
add_test (NAME scener_math_test_runner COMMAND test-runner)

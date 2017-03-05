cmake_minimum_required(VERSION 3.2.2)
project (scener::math::root)
enable_language(CXX)

#set (CMAKE_VERBOSE_MAKEFILE on)
#set (CMAKE_EXPORT_COMPILE_COMMANDS on)

include(cmake/DownloadProject.cmake)

# external dependencies
#
# base directory
set (EXTERNALS_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/externals)

# Microsoft/GSL
set (GSL_INCLUDE_DIRS ${EXTERNALS_BASE_DIR}/gsl/include)

# scener-math
set (SCENER_MATH_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/source)

# reconfigure final output directory
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})

# compiler flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=c++1z")

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
    # "-Weverything -Wno-undef -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-nested-anon-types -Wno-gnu-anonymous-struct"    
endif ()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # Workaround using a local build of libc++ & libc++abi under ubuntu 16.04
  ## c++abi
  if (CMAKE_LIBCXXABI_INCLUDE_PATH)
    include_directories (${CMAKE_LIBCXXABI_INCLUDE_PATH})
  endif ()
  if (CMAKE_LIBCXXABI_LIB_PATH)
    link_directories (${CMAKE_LIBCXXABI_LIB_PATH})
  endif ()
  ## c++
  if (CMAKE_LIBCXX_INCLUDE_PATH)
    include_directories (${CMAKE_LIBCXX_INCLUDE_PATH})
  endif ()
  if (CMAKE_LIBCXX_LIB_PATH)
    link_directories (${CMAKE_LIBCXX_LIB_PATH})
  endif ()

  # compiler flags
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

  # linker flags
  set (CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS}    -lc++ -lc++abi")
  set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -lc++ -lc++abi")
  set (CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -lc++ -lc++abi")  
endif ()

# tests subdirectory
enable_testing()
add_subdirectory(tests)

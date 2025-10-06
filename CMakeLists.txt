cmake_minimum_required(VERSION 3.10)
project(5g_cpp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Try pkg-config
find_package(PkgConfig QUIET)
if (PkgConfig_FOUND)
  pkg_check_modules(PKG_NGHTTP2 QUIET nghttp2)
endif()

# Try to discover nghttp2 headers and library
find_path(NGHTTP2_INCLUDE_DIR nghttp2/nghttp2.h)
find_library(NGHTTP2_LIB nghttp2)

if (PKG_NGHTTP2_FOUND)
  message(STATUS "Found nghttp2 via pkg-config")
  include_directories(${PKG_NGHTTP2_INCLUDE_DIRS})
  link_directories(${PKG_NGHTTP2_LIBRARY_DIRS})
  set(NGHTTP2_LIBS ${PKG_NGHTTP2_LIBRARIES})
  add_compile_definitions(HAVE_NGHTTP2)
elseif (NGHTTP2_INCLUDE_DIR AND NGHTTP2_LIB)
  message(STATUS "Found nghttp2: include=${NGHTTP2_INCLUDE_DIR}, lib=${NGHTTP2_LIB}")
  include_directories(${NGHTTP2_INCLUDE_DIR})
  set(NGHTTP2_LIBS ${NGHTTP2_LIB})
  add_compile_definitions(HAVE_NGHTTP2)
else()
  message(WARNING "nghttp2 not found. You can build it using [nghttp2/Makefile](nghttp2/Makefile)")
  set(NGHTTP2_LIBS "")
endif()

# Source layout
add_executable(5g_app src/main.cpp)
target_include_directories(5g_app PRIVATE ${CMAKE_SOURCE_DIR}/include)
if (NGHTTP2_LIBS)
  target_link_libraries(5g_app PRIVATE ${NGHTTP2_LIBS})
endif()

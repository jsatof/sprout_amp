cmake_minimum_required(VERSION 3.22)

#set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")  for when clang fails to compile test program
project(sproutAmp)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wpedantic -Wextra -Werror -include cstdint -fdiagnostics-color=always")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -03 -Wall -Wpedantic -Wextra -Werror -include cstdint -fdiagnostics-color=always")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THIRD_PARTY_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)
#include(cmake/dependencies.cmake)

find_package(JUCE CONFIG REQUIRED)
find_package(GTest REQUIRED)

enable_testing()

# reconfigure by passing -DLV2_INSTALL_PREFIX=<your custom path> to cmake
option(LV2_INSTALL_PREFIX "~/.lv2")
option(VST3_INSTALL_PREFIX "~/.vst3")
option(AU_INSTALL_PREFIX "~/.au")

add_subdirectory(src)
add_subdirectory(test)

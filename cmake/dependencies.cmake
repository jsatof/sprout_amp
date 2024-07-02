include(cmake/cpm.cmake)

#CPMAddPackage(NAME JUCE
#    GITHUB_REPOSITORY juce-framework/JUCE
#    GIT_TAG 7.0.11
#    VERSION 7.0.11
#    SOURCE_DIR ${THIRD_PARTY_LIB_DIR}/juce
#)

#CPMAddPackage(NAME GTEST
#    GITHUB_REPOSITORY google/googletest
#    VERSION 1.14.0
#    SOURCE_DIR ${THIRD_PARTY_LIB_DIR}/gtest
#    OPTIONS
#        "INSTALL_GTEST OFF"
#        "gtest_force_shared_crt ON"
#)

CPMAddPackage(NAME MAXIMILIAN
    GITHUB_REPOSITORY micknoise/Maximilian
    GIT_TAG 2.4
    VERSION 2.4
    SOURCE_DIR ${THIRD_PARTY_LIB_DIR}/Maximilian
)

# for use with clang tidy and clang format
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_program(CLANG_TIDY NAMES "clang-tidy")
set(CLANG_TIDY_COMMAND "${CLANG_TIDY}" "--config-file=${PROJECT_SOURCE_DIR}/.clang-tidy")
find_program(CLANG_FORMAT NAMES "clang-format")
set(CLANG_FORMAT_COMMAND "${CLANG_FORMAT}") # default is `--style=file`, where it looks for `.clang-format` in parent dir

# Prepend the full path to each source file
# Create custom target for running clang tidy
#list(TRANSFORM exampleGUIApp_SOURCES PREPEND ${CMAKE_SOURCE_DIR}/src/)

set(CLANG_TIDY_OPTIONS ${CLANG_TIDY_OPTIONS}
    -extra-arg=-Wno-unknown-warning-option
    -extra-arg=-Wno-ignored-optimization-argument
    -extra-arg=-Wno-unused-command-line-argument
    -warning-as-errors=*)

if("${CLANG_TIDY_OPTIONS_DRIVER_MODE}" STREQUAL "cl")
    set(CLANG_TIDY_OPTIONS ${CLANG_TIDY_OPTIONS} -extra-arg=/std:c++${CMAKE_CXX_STANDARD})
else()
    set(CLANG_TIDY_OPTIONS ${CLANG_TIDY_OPTIONS} -extra-arg=-std=c++${CMAKE_CXX_STANDARD})
endif()

file(GLOB APP_SOURCES ${PROJECT_SOURCE_DIR}/app/src/*.cpp ${PROJECT_SOURCE_DIR}/app/include/*.h)
file(GLOB HOUSE_SOURCES ${PROJECT_SOURCE_DIR}/01_house_tutorial/src/*.cpp ${PROJECT_SOURCE_DIR}/01_house_tutorial/include/*.h)

add_custom_target(tidy
    COMMAND clang-tidy --config-file=${CMAKE_SOURCE_DIR}/.clang-tidy --use-color ${APP_SOURCES} ${HOUSE_SOURCES}
    COMMENT "Running tidy checks"
    VERBATIM)

add_custom_target(format
    COMMAND clang-format --Werror --sort-includes --verbose ${APP_SOURCES} ${HOUSE_SOURCES}
    COMMENT "Running formatting checks"
    VERBATIM)

add_custom_target(formatw
    COMMAND clang-format --Werror --sort-includes --verbose -i ${APP_SOURCES} ${HOUSE_SOURCES}
    COMMENT "Running formatting checks"
    VERBATIM)

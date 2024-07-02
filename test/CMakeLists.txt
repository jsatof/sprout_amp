cmake_minimum_required(VERSION 3.22)
project(sproutAmpTest)
enable_testing()

add_executable(${PROJECT_NAME}
    src/AudioProcessorTest.cpp
    src/HouseTest.cpp)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${GTEST_SOURCE_DIR}/googletest/include
        ${PROJECT_SOURCE_DIR}/../plugin/include
        ${JUCE_SOURCE_DIR}/modules)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        sproutAmp
        GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

cmake_minimum_required(VERSION 3.10)
project(UTILS)

# Include directories
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Darray)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Globe)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/List)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/standalone)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Utils)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Window)

# Gather all source files from all directories except tests
file(GLOB_RECURSE PROJECT_SOURCES 
#    "${CMAKE_CURRENT_SOURCE_DIR}/Darray/*.c"
#    "${CMAKE_CURRENT_SOURCE_DIR}/Globe/*.c"
#    "${CMAKE_CURRENT_SOURCE_DIR}/List/*.c"
#    "${CMAKE_CURRENT_SOURCE_DIR}/standalone/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/Utils/*.c"
#    "${CMAKE_CURRENT_SOURCE_DIR}/Window/*.c"
)

# Gather test files
file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.c")

# Create an executable for each test source file
foreach(testsourcefile ${TEST_SOURCES})
    get_filename_component(testname ${testsourcefile} NAME_WE)
    # Append ".test" extension
    set(testname "${testname}.test")
    # Generate executable for each test source file
    message(STATUS "Building test: ${testname}")
    add_executable(${testname} ${testsourcefile} ${PROJECT_SOURCES})
    # Optionally, add a command to run the test
    add_test(NAME ${testname} COMMAND ${testname})
endforeach(testsourcefile ${TEST_SOURCES})

# Enable testing
enable_testing()


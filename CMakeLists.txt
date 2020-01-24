cmake_minimum_required (VERSION 3.5)
project (HollowTrace)

# Add dependency directories
add_subdirectory(HollowMac)

# Configure Environment
if (COVERAGE)
    find_program(GCOV_PATH gcov)
    if(NOT GCOV_PATH)
        message(FATAL_ERROR "gcov not found! Aborting...")
    endif()

    find_program(LCOV_PATH  NAMES lcov lcov.bat lcov.exe lcov.perl)
    if(NOT LCOV_PATH)
        message(FATAL_ERROR "lcov not found! Aborting...")
    endif()

    find_program(GENHTML_PATH NAMES genhtml genhtml.perl genhtml.bat)
    if(NOT GENHTML_PATH)
        message(FATAL_ERROR "genhtml not found! Aborting...")
    endif()

    set(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
    set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
    set(CMAKE_LD_FLAGS "-fprofile-arcs -ftest-coverage")
    set(CMAKE_C_OUTPUT_EXTENSION_REPLACE ON)
    set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)
endif ()

# HollowTrace Library
set(HOLLOWTRACE_LIBRARY_NAME hollowtrace)
set(SOURCES ${SOURCES} Source/Data/HCVector.c)
set(SOURCES ${SOURCES} Source/Data/HCRay.c)
set(SOURCES ${SOURCES} Source/Data/HCTriangle.c)
set(SOURCES ${SOURCES} Source/Light/HCLight.c)
set(SOURCES ${SOURCES} Source/Light/HCPointLight.c)
set(SOURCES ${SOURCES} Source/Primitive/HCPrimitive.c)
set(SOURCES ${SOURCES} Source/Primitive/HCSphere.c)
set(SOURCES ${SOURCES} Source/Primitive/HCPlane.c)
set(SOURCES ${SOURCES} Source/Primitive/HCMesh.c)
add_library(${HOLLOWTRACE_LIBRARY_NAME} ${SOURCES})

# HollowTrace Links
add_dependencies(${HOLLOWTRACE_LIBRARY_NAME} hollowcore)
target_link_libraries(${HOLLOWTRACE_LIBRARY_NAME} hollowcore)

# HollowTrace Test Suite
set(HOLLOWTRACE_TEST_NAME hollowtracetest)
set(TEST_SOURCES ${TEST_SOURCES} Test/main.c)
set(TEST_SOURCES ${TEST_SOURCES} Test/HCVector.c)
set(TEST_SOURCES ${TEST_SOURCES} Test/HCRay.c)
set(TEST_SOURCES ${TEST_SOURCES} Test/Trace.c)
add_executable(${HOLLOWTRACE_TEST_NAME} ${TEST_SOURCES})
add_dependencies(${HOLLOWTRACE_TEST_NAME} hollowcore)
target_link_libraries(${HOLLOWTRACE_TEST_NAME} hollowtrace)
enable_testing()
add_test(tests ${HOLLOWTRACE_TEST_NAME})

# HollowTrace Test Suite Code Coverage
if (COVERAGE)
    set(HOLLOWTRACE_COVERAGE hollowtracecoverage)
    set(OBJECT_DIR ${CMAKE_BINARY_DIR}/CMakeFiles/${HOLLOWTRACE_LIBRARY_NAME}.dir/Source)
    add_custom_target(${HOLLOWTRACE_COVERAGE}
        COMMAND mkdir -p ${HOLLOWTRACE_COVERAGE}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
    add_custom_command(TARGET ${HOLLOWTRACE_COVERAGE}
        COMMAND echo "-- LCOV running tests..."
        COMMAND ${CMAKE_BINARY_DIR}/${HOLLOWTRACE_TEST_NAME}
        COMMAND echo "-- LCOV tests complete"
        COMMAND echo "-- LCOV generating coverage..."
        COMMAND ${LCOV_PATH} --gcov-tool ${GCOV_PATH} -d ${OBJECT_DIR} -c -o coverage.info
        COMMAND ${LCOV_PATH} --gcov-tool ${GCOV_PATH} -a coverage.info -o coverage.total
        COMMAND ${GENHTML_PATH} coverage.total --output-directory html
        COMMAND echo "-- LCOV coverage generation complete"
        COMMAND echo "-- GCOV analysis"
        COMMAND ${GCOV_PATH} ${SOURCES} -o ${OBJECT_DIR} > summary.txt
        COMMAND cat summary.txt
        COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/${HOLLOWTRACE_COVERAGE}"
        COMMAND open ${CMAKE_BINARY_DIR}/${HOLLOWTRACE_COVERAGE}/html/index.html
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/${HOLLOWTRACE_COVERAGE}
    )
    add_custom_target(cumulative_${HOLLOWTRACE_COVERAGE}
        COMMAND mkdir -p ${HOLLOWTRACE_COVERAGE}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
    add_custom_command(TARGET cumulative_${HOLLOWTRACE_COVERAGE}
        COMMAND echo "-- LCOV establishing baseline..."
        COMMAND ${LCOV_PATH} --gcov-tool ${GCOV_PATH} -d ${OBJECT_DIR} -z
        COMMAND ${LCOV_PATH} --gcov-tool ${GCOV_PATH} -d ${OBJECT_DIR} -c -i -o coverage.base
        COMMAND echo "-- LCOV baseline established"
        COMMAND echo "-- LCOV running tests..."
        COMMAND ${CMAKE_BINARY_DIR}/${HOLLOWTRACE_TEST_NAME}
        COMMAND echo "-- LCOV tests complete"
        COMMAND echo "-- LCOV generating coverage..."
        COMMAND ${LCOV_PATH} --gcov-tool ${GCOV_PATH} -d ${OBJECT_DIR} -c -o coverage.info
        COMMAND ${LCOV_PATH} --gcov-tool ${GCOV_PATH} -a coverage.base -a coverage.info -o coverage.total
        COMMAND ${GENHTML_PATH} coverage.total --output-directory html
        COMMAND echo "-- LCOV coverage generation complete"
        COMMAND echo "-- GCOV analysis"
        COMMAND ${GCOV_PATH} ${SOURCES} -o ${OBJECT_DIR} > summary.txt
        COMMAND cat summary.txt
        COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/${HOLLOWTRACE_COVERAGE}"
        COMMAND open ${CMAKE_BINARY_DIR}/${HOLLOWTRACE_COVERAGE}/html/index.html
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/${HOLLOWTRACE_COVERAGE}
    )
    add_dependencies(${HOLLOWTRACE_COVERAGE} ${HOLLOWTRACE_TEST_NAME})
    set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${HOLLOWTRACE_COVERAGE})
endif ()

# HollowTrace Sample App
set(HOLLOWTRACE_APP_NAME raia)
set(APP_SOURCES ${APP_SOURCES} App/main.c)
add_executable(${HOLLOWTRACE_APP_NAME} ${APP_SOURCES})
add_dependencies(${HOLLOWTRACE_APP_NAME} hollowcore)
add_dependencies(${HOLLOWTRACE_APP_NAME} hollowmac)
target_link_libraries(${HOLLOWTRACE_APP_NAME} hollowcore)
target_link_libraries(${HOLLOWTRACE_APP_NAME} hollowmac)
target_link_libraries(${HOLLOWTRACE_APP_NAME} hollowtrace)
target_link_libraries(${HOLLOWTRACE_APP_NAME} m pthread "-framework AppKit")

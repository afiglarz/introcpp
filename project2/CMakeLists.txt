cmake_minimum_required(VERSION 3.11)

project(project2_cmake)

add_executable(project2_cmake)

target_sources(project2_cmake PRIVATE frameworkpractice.cpp)

target_include_directories(project2_cmake PRIVATE .)
target_include_directories(project2_cmake PUBLIC /Users/aef1/NIST/libbiomeval/src/include/)

add_subdirectory(/Users/aef1/NIST/libbiomeval ${CMAKE_CURRENT_BINARY_DIR}/biomeval)
add_dependencies(project2_cmake biomeval)
target_link_libraries(project2_cmake PUBLIC biomeval)

set_target_properties(project2_cmake PROPERTIES
    # Set RPATH to installed version of libs
    INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})

set_target_properties(project2_cmake PROPERTIES
    BUILD_WITH_INSTALL_RPATH TRUE)

target_compile_options(project2_cmake PRIVATE
    -Wall -Wextra -pedantic -Wconversion -Wsign-conversion)

install(TARGETS project2_cmake
    RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/../${CMAKE_INSTALL_BINDIR})
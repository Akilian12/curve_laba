cmake_minimum_required(VERSION 3.17)
project(curve_laba)

set(CMAKE_C_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Modules)
find_package(GMP REQUIRED)

INCLUDE_DIRECTORIES(
        "${GMP_INCLUDES}"
        "${CMAKE_SOURCE_DIR}/src"
)

add_executable(${PROJECT_NAME} main.c curve.c curve.h point.c point.h)

target_link_libraries(${PROJECT_NAME} ${GMP_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/)


add_custom_target(clean-all
        make clean && rm -fR ${CMAKE_BINARY_DIR}/CMakeCache.txt
        ${CMAKE_BINARY_DIR}/cmake_install.cmake
        ${CMAKE_BINARY_DIR}/Makefile
        ${CMAKE_BINARY_DIR}/CMakeFiles
        && rmdir  ${CMAKE_BINARY_DIR}/out
        )
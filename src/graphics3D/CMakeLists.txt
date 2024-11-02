cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)

project(StellarForgeGraphics3D
        LANGUAGES CXX
        VERSION 0.2.0
        DESCRIPTION "3D Graphics components and utilities for StellarForge"
)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if (CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif ()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(StellarForgeGraphics3D STATIC)
find_package(raylib REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(stellar-forge-common REQUIRED)
target_link_libraries(StellarForgeGraphics3D PUBLIC stellar-forge-common::stellar-forge-common glm::glm raylib glfw)

add_subdirectory(components)

target_sources(StellarForgeGraphics3D
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Graphics3D.hpp
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Graphics3D.cpp
)

install(TARGETS StellarForgeGraphics3D
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
        DESTINATION include/StellarForge/Graphics3D
        FILES_MATCHING PATTERN "*.hpp"
)

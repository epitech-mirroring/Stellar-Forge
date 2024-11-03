cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 17)

project(StellarForgeEngine3Dd
        LANGUAGES CXX
        VERSION 0.2.0
        DESCRIPTION "3D game engine for StellarForge"
)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if (CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif ()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(StellarForge3D STATIC)
find_package(stellar-forge-common REQUIRED)
find_package(stellar-forge-graphics-3d REQUIRED)
find_package(stellar-forge-physics REQUIRED)
find_package(glm REQUIRED)
find_package(raylib REQUIRED)
find_package(glfw3 REQUIRED)
target_link_libraries(StellarForge3D
        PUBLIC
        stellar-forge-common::stellar-forge-common
        stellar-forge-graphics-3d::stellar-forge-graphics-3d
        stellar-forge-physics::stellar-forge-physics
        glm::glm
        raylib
        glfw
)

target_sources(StellarForge3D
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine3D.hpp
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine3D.cpp
)

install(TARGETS StellarForge3D
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
        DESTINATION include/StellarForge/Engine3D
        FILES_MATCHING PATTERN "*.hpp"
)

cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 17)

project(StellarForgeEngine
        LANGUAGES CXX
        VERSION 0.2.0
        DESCRIPTION "2D game engine for StellarForge"
)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if (CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif ()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(StellarForge STATIC)
find_package(stellar-forge-common REQUIRED)
find_package(stellar-forge-graphics REQUIRED)
find_package(stellar-forge-physics REQUIRED)
find_package(glm REQUIRED)
find_package(SFML REQUIRED COMPONENTS graphics window system)
target_link_libraries(StellarForge
        PUBLIC
        stellar-forge-common::stellar-forge-common
        stellar-forge-graphics::stellar-forge-graphics
        stellar-forge-physics::stellar-forge-physics
        sfml::sfml
        glm::glm
)

target_sources(StellarForge
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine.hpp
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine.cpp
)

install(TARGETS StellarForge
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
        DESTINATION include/StellarForge/Engine
        FILES_MATCHING PATTERN "*.hpp"
)

cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 17)

project(StellarForgeGraphics
        LANGUAGES CXX
        VERSION 0.3.0
        DESCRIPTION "Graphics components and utilities for StellarForge"
)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if (CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif ()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(StellarForgeGraphics STATIC)
find_package(SFML REQUIRED COMPONENTS graphics window system)
find_package(glm REQUIRED)
find_package(stellar-forge-common REQUIRED)
find_package(lua-cpp REQUIRED)
target_link_libraries(StellarForgeGraphics PUBLIC stellar-forge-common::stellar-forge-common sfml::sfml glm::glm lua-cpp::lua-cpp lua)

add_subdirectory(components)

target_sources(StellarForgeGraphics
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Graphics.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GraphicsException.hpp
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Graphics.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GraphicsException.cpp
)

install(TARGETS StellarForgeGraphics
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
        DESTINATION include/StellarForge/Graphics
        FILES_MATCHING PATTERN "*.hpp"
)

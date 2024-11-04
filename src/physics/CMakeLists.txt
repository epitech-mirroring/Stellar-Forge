cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 17)

project(StellarForgePhysics
        LANGUAGES CXX
        VERSION 0.3.0
        DESCRIPTION "Physics components for StellarForge"
)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if (CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif ()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(glm REQUIRED)
find_package(stellar-forge-common REQUIRED)
find_package(lua-cpp REQUIRED)
add_library(StellarForgePhysics STATIC)
target_link_libraries(StellarForgePhysics PUBLIC glm::glm stellar-forge-common::stellar-forge-common lua-cpp::lua-cpp lua)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(components)

target_sources(StellarForgePhysics
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Physics.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Collider.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Box.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Sphere.hpp
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Physics.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Box.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Sphere.cpp
)

install(TARGETS StellarForgePhysics
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
        DESTINATION include/StellarForge/Physics
        FILES_MATCHING PATTERN "*.hpp"
)

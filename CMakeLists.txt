cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(StellarForge
        LANGUAGES CXX
        VERSION 0.1.0
        DESCRIPTION "A simple 2D game engine"
)

include(src/common/CMakeLists.txt)
include(src/physics/CMakeLists.txt)
include(src/graphics/CMakeLists.txt)

add_library(StellarForge STATIC
        ${StellarForge_SOURCES}
)
add_dependencies(StellarForge StellarForgeCommon StellarForgePhysics StellarForgeGraphics)
target_link_libraries(StellarForge
        StellarForgeCommon
        StellarForgePhysics
        StellarForgeGraphics
)

add_subdirectory(src/engine)
include_directories(src)

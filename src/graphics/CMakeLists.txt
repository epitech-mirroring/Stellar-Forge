add_library(StellarForgeGraphics STATIC)
add_library(StellarForge::Graphics ALIAS StellarForgeGraphics)
add_dependencies(StellarForgeGraphics StellarForgeCommon)

target_sources(StellarForgeGraphics
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Graphics.hpp
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Graphics.cpp
)

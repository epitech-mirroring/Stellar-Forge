add_library(StellarForge STATIC)
add_library(StellarForge::Core ALIAS StellarForge)
add_dependencies(StellarForge StellarForgeCommon StellarForgePhysics StellarForgeGraphics)
target_link_libraries(StellarForge
        PUBLIC
        StellarForgeCommon
        StellarForgePhysics
        StellarForgeGraphics
)

target_sources(StellarForge
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine.hpp
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine.cpp
)

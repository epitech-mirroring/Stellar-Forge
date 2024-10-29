add_library(StellarForge3D STATIC)
add_library(StellarForge::Core3D ALIAS StellarForge3D)
add_dependencies(StellarForge3D StellarForgeCommon StellarForgePhysics StellarForgeGraphics3D)
target_link_libraries(StellarForge3D
        PUBLIC
        StellarForgeCommon
        StellarForgePhysics
        StellarForgeGraphics3D
        # Add raylib here if necessary
)


target_sources(StellarForge3D
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine3D.hpp
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine3D.cpp
)

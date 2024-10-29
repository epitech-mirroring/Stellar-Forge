add_library(StellarForgeGraphics3D STATIC)
add_library(StellarForge::Graphics3D ALIAS StellarForgeGraphics3D)
add_dependencies(StellarForgeGraphics3D StellarForgeCommon)
target_link_libraries(StellarForgeGraphics3D PUBLIC StellarForge::Common sfml::sfml glm::glm raylib)

add_subdirectory(components)

target_sources(StellarForgeGraphics
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Graphics3D.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GraphicsException3D.hpp
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Graphics3D.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GraphicsException3D.cpp
)

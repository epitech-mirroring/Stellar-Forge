add_library(StellarForgeGraphics STATIC)
add_library(StellarForge::Graphics ALIAS StellarForgeGraphics)
add_dependencies(StellarForgeGraphics StellarForgeCommon)
target_link_libraries(StellarForgeGraphics PUBLIC SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image sdl_ttf::sdl_ttf)

target_sources(StellarForgeGraphics
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Graphics.hpp
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Graphics.cpp
)

add_library(StellarForgeGraphics STATIC)
add_library(StellarForge::Graphics ALIAS StellarForgeGraphics)
add_dependencies(StellarForgeGraphics StellarForgeCommon)
target_link_libraries(StellarForgeGraphics PUBLIC StellarForge::Common sfml::sfml glm:glm)

target_sources(StellarForgeGraphics
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Graphics.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GraphicsException.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/components/IGraphicsComponent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/components/AGraphicsComponent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/components/Sprite.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/components/SpriteSheet.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/components/AnimatedSprite.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/components/UIText.hpp
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Graphics.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GraphicsException.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/components/Sprite.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/components/SpriteSheet.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/components/AnimatedSprite.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/components/UIText.cpp
)

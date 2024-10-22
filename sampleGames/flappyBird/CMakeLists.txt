add_executable(flappy-bird)

target_link_libraries(flappy-bird PUBLIC StellarForge StellarForgeGraphics StellarForgePhysics StellarForgeCommon sfml::sfml glm::glm)

target_sources(flappy-bird
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/assets/objects/scripts/Background.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/assets/objects/scripts/Bird.hpp
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/assets/objects/scripts/Background.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/assets/objects/scripts/Bird.cpp
)

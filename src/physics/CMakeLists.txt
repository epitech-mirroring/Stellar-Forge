add_library(StellarForgePhysics STATIC)
add_library(StellarForge::Physics ALIAS StellarForgePhysics)
add_dependencies(StellarForgePhysics StellarForgeCommon)

target_sources(StellarForgePhysics
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Physics.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Math.hpp
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Physics.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Math.cpp
)

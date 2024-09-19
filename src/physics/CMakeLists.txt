add_library(StellarForgePhysics STATIC
        ${StellarForgePhysics_SOURCES})
add_library(StellarForge::Physics ALIAS StellarForgePhysics)
add_dependencies(StellarForgePhysics StellarForgeCommon)

target_sources(StellarForgePhysics
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/physics/Physics.hpp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/physics/Physics.cpp
)
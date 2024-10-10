add_library(StellarForgePhysics STATIC)
add_library(StellarForge::Physics ALIAS StellarForgePhysics)
add_dependencies(StellarForgePhysics StellarForgeCommon)
target_link_libraries(StellarForgePhysics PUBLIC glm::glm StellarForge::Common)

target_sources(StellarForgePhysics
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Physics.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Collider.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Box.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Sphere.hpp
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Physics.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Box.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Sphere.cpp
)

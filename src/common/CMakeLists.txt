add_library(StellarForgeCommon SHARED)
add_library(StellarForge::Common ALIAS StellarForgeCommon)
set_target_properties(StellarForgeCommon PROPERTIES LINKER_LANGUAGE CXX)

target_sources(StellarForgeCommon
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/IComponent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IObject.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IScene.hpp
)

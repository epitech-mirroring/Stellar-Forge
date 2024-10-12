add_library(StellarForgeCommon STATIC)
add_library(StellarForge::Common ALIAS StellarForgeCommon)
target_link_libraries(StellarForgeCommon PUBLIC stduuid::stduuid GSL::gsl glm::glm)

add_subdirectory(json)
add_subdirectory(factories)
add_subdirectory(fields)
add_subdirectory(components)
add_subdirectory(event)
add_subdirectory(managers)

target_sources(StellarForgeCommon
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/IComponent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IObject.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IScene.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IError.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/UUID.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/UUIDException.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/UncertainBool.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Utils.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/VirtualObject.hpp
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/UUID.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/UUIDException.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/VirtualObject.cpp
)

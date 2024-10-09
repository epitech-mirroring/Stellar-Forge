add_library(StellarForgeCommon STATIC)
add_library(StellarForge::Common ALIAS StellarForgeCommon)
target_link_libraries(StellarForgeCommon PUBLIC stduuid::stduuid GSL::gsl glm::glm)

add_subdirectory(json)

target_sources(StellarForgeCommon
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/IComponent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IObject.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IScene.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/fields/FieldGroup.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/fields/Vector3Field.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/fields/FileField.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/fields/IntRectFieldGroup.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/components/Transform.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/components/CPPMonoBehaviour.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IError.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AComponent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AMeta.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AField.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AFieldGroup.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/UUID.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/UUIDException.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/event/EventData.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/event/EventSystem.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/managers/ObjectManager.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/managers/SceneManager.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/managers/ManagerException.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/UncertainBool.hpp
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/AComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AMeta.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AField.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AFieldGroup.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/fields/FieldGroup.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/fields/Vector3Field.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/fields/FileField.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/fields/IntRectFieldGroup.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/components/Transform.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/components/CPPMonoBehaviour.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/UUID.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/UUIDException.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/event/EventSystem.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/managers/ObjectManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/managers/SceneManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/managers/ManagerException.cpp
)

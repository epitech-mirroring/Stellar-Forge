add_subdirectory(groups)

target_sources(StellarForgeCommon
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/AField.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FileField.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Vector3Field.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/StringField.hpp
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/AField.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FileField.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Vector3Field.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/StringField.cpp
)

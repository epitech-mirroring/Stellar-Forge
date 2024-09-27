add_library(StellarForgeCommon STATIC)
add_library(StellarForge::Common ALIAS StellarForgeCommon)

target_link_libraries(StellarForgeCommon PRIVATE unofficial::UUID::uuid)

target_sources(StellarForgeCommon
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/UtilExemple.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Uuid.hpp
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/UtilExemple.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Uuid.cpp
)

add_library(StellarForgeCommon STATIC
        ${StellarForgeCommon_SOURCES})
add_library(StellarForge::Common ALIAS StellarForgeCommon)


target_sources(StellarForgeCommon
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/common/UtilExemple.hpp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/common/UtilExemple.cpp
)
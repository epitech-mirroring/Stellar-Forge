target_sources(StellarForgeCommon
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/EventData.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/EventSystem.hpp
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/EventSystem.cpp
)

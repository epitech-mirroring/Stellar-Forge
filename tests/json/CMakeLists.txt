target_sources(StellarForgeTests
        PUBLIC
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/JsonParser.spec.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/JsonWriter.spec.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/JsonPrettyWriter.spec.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/JsonReader.spec.cpp
)

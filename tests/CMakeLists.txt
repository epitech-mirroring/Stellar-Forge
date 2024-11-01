set(CMAKE_CXX_STANDARD 17)
find_package(GTest REQUIRED)
find_package(stellar-forge-common REQUIRED)
find_package(stellar-forge-graphics REQUIRED)
find_package(stellar-forge-physics REQUIRED)
find_package(stellar-forge REQUIRED)
find_package(glm REQUIRED)
find_package(SFML REQUIRED COMPONENTS graphics window system)
include(GoogleTest)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/tests)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/tests)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/tests)

add_executable(StellarForgeTests main.cpp)

add_subdirectory(json)
add_subdirectory(components)
add_subdirectory(engine)
add_subdirectory(common)
add_subdirectory(assets/components)

gtest_discover_tests(StellarForgeTests)
add_dependencies(StellarForgeTests StellarForge StellarForge::Common StellarForge::Graphics StellarForge::Physics test_dynamic)
target_link_libraries(StellarForgeTests PRIVATE StellarForge StellarForge::Common StellarForge::Graphics StellarForge::Physics gtest::gtest)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/tests)

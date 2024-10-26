find_package(GTest)
include(GoogleTest)
enable_testing()
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

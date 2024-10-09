find_package(GTest)
include(GoogleTest)
enable_testing()
add_executable(StellarForgeTests main.cpp)

add_subdirectory(json)

gtest_discover_tests(StellarForgeTests)
target_link_libraries(StellarForgeTests PRIVATE StellarForge StellarForge::Common StellarForge::Graphics StellarForge::Physics gtest::gtest)

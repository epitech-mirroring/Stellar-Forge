set(CMAKE_CXX_STANDARD 17)
find_package(GTest)
find_package(stellar-forge-common REQUIRED)
find_package(stellar-forge-graphics REQUIRED)
find_package(stellar-forge-physics REQUIRED)
find_package(stellar-forge REQUIRED)
include(GoogleTest)
enable_testing()
add_executable(StellarForgeTests main.cpp)

add_subdirectory(json)
add_subdirectory(components)
add_subdirectory(engine)
add_subdirectory(common)

gtest_discover_tests(StellarForgeTests)
target_link_libraries(StellarForgeTests PRIVATE stellar-forge::stellar-forge stellar-forge-common::stellar-forge-common stellar-forge-graphics::stellar-forge-graphics stellar-forge-physics::stellar-forge-physics gtest::gtest)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/tests)

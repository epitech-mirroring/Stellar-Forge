cmake_minimum_required(VERSION 3.15)

project(Stellar-Forge
        LANGUAGES CXX)

add_subdirectory(src/common)
add_subdirectory(src/physics)
add_subdirectory(src/graphics)
add_subdirectory(src/engine)
add_subdirectory(tests)

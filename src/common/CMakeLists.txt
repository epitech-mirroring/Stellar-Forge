cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 17)

project(StellarForgeCommon
        LANGUAGES CXX
        VERSION 0.1.0
        DESCRIPTION "Common components for StellarForge"
)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if (CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif ()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(StellarForgeCommon STATIC)
find_package(glm REQUIRED)
target_link_libraries(StellarForgeCommon PUBLIC glm::glm)
set_target_properties(StellarForgeCommon PROPERTIES POSITION_INDEPENDENT_CODE ON)

# If windows add DbgHelp for stack traces
IF (WIN32 OR WIN64)
    target_link_libraries(StellarForgeCommon PUBLIC DbgHelp)
ENDIF ()

add_subdirectory(json)
add_subdirectory(factories)
add_subdirectory(fields)
add_subdirectory(components)
add_subdirectory(event)
add_subdirectory(managers)
add_subdirectory(utils)

target_sources(StellarForgeCommon
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/IComponent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IObject.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IScene.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IError.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/UUID.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/UUIDException.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/UncertainBool.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Utils.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/VirtualObject.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/VirtualScene.hpp
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/UUID.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/UUIDException.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/VirtualObject.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/VirtualScene.cpp
)

install(TARGETS StellarForgeCommon
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
        DESTINATION include/StellarForge/Common
        FILES_MATCHING PATTERN "*.hpp"
)

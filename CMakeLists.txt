cmake_minimum_required(VERSION 3.29)
set(CMAKE_CXX_STANDARD 20)

project(StellarForge
        LANGUAGES CXX
        VERSION 0.1.0
        DESCRIPTION "A simple 2D game engine"
)

# Check if clang-tidy is installed
# If it is, set it as the C++ clang-tidy checker
# If optional clang-tidy-18 is installed, set it as the C++ clang-tidy checker
# If CLANG_SEVERE is set to ON, set clang_tidy warnings as errors
option(CLANG_SEVERE "Set clang-tidy warnings as errors" OFF)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if (CLANG_TIDY_EXE)
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    if (CLANG_SEVERE)
        message(STATUS "Setting clang-tidy warnings as errors")
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-warnings-as-errors=*")
    else ()
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
    endif ()
else ()
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy-18")
    if (CLANG_TIDY_EXE)
        message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
        if (CLANG_SEVERE)
            message(STATUS "Setting clang-tidy warnings as errors")
            set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-warnings-as-errors=*")
        else ()
            set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
        endif ()
    else ()
        message(STATUS "clang-tidy not found")
    endif ()
endif ()

# Libraries
find_package(glm REQUIRED)
find_package(stduuid REQUIRED)
find_package(GSL REQUIRED)

# Include subdirectories for common, physics, and graphics
add_subdirectory(src/common)
add_subdirectory(src/physics)
add_subdirectory(src/graphics)

get_target_property(StellarForgeCommon_SOURCES StellarForgeCommon SOURCES)
get_target_property(StellarForgePhysics_SOURCES StellarForgePhysics SOURCES)
get_target_property(StellarForgeGraphics_SOURCES StellarForgeGraphics SOURCES)

# Collect sources from subdirectories
set(StellarForge_SOURCES
        ${StellarForgeCommon_SOURCES}
        ${StellarForgePhysics_SOURCES}
        ${StellarForgeGraphics_SOURCES}
)

# Add the main StellarForge library as a static library
add_library(StellarForge STATIC ${StellarForge_SOURCES})

# Ensure dependencies are built before StellarForge
add_dependencies(StellarForge StellarForgeCommon StellarForgePhysics StellarForgeGraphics)

# Link the dependent libraries statically
target_link_libraries(StellarForge
        PRIVATE
        StellarForgeCommon
        StellarForgePhysics
        StellarForgeGraphics
)

add_subdirectory(src/engine)
include_directories(src)

# Extract the public headers from the sources (all .hpp files, including those in subdirectories)
get_target_property(StellarForge_SOURCES StellarForge SOURCES)
foreach (source IN LISTS StellarForge_SOURCES)
    if (source MATCHES ".*\\.hpp$")
        list(APPEND StellarForge_HEADERS ${source})
    endif ()
endforeach ()
get_target_property(StellarForgeCommon_SOURCES StellarForgeCommon SOURCES)
foreach (source IN LISTS StellarForgeCommon_SOURCES)
    if (source MATCHES ".*\\.hpp$")
        list(APPEND StellarForge_HEADERS ${source})
    endif ()
endforeach ()
get_target_property(StellarForgePhysics_SOURCES StellarForgePhysics SOURCES)
foreach (source IN LISTS StellarForgePhysics_SOURCES)
    if (source MATCHES ".*\\.hpp$")
        list(APPEND StellarForge_HEADERS ${source})
    endif ()
endforeach ()
get_target_property(StellarForgeGraphics_SOURCES StellarForgeGraphics SOURCES)
foreach (source IN LISTS StellarForgeGraphics_SOURCES)
    if (source MATCHES ".*\\.hpp$")
        list(APPEND StellarForge_HEADERS ${source})
    endif ()
endforeach ()

# Set the public headers
target_sources(StellarForge
        PUBLIC
        ${StellarForge_HEADERS}
)

# Export headers in build directory
file(COPY ${StellarForge_HEADERS} DESTINATION ${CMAKE_BINARY_DIR}/includes/StellarForge)

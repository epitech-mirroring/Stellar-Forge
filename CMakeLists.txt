cmake_minimum_required(VERSION 3.29)
set(CMAKE_CXX_STANDARD 17)

project(StellarForge
        LANGUAGES CXX
        VERSION 0.1.0
        DESCRIPTION "A simple 2D game engine"
)

add_compile_options(-fPIE)

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
find_package(SFML REQUIRED)

include_directories(src)

# Include subdirectories for common, physics, and graphics
add_subdirectory(src/common)
add_subdirectory(src/physics)
add_subdirectory(src/graphics)
add_subdirectory(src/engine)

get_target_property(StellarForgeCommon_SOURCES StellarForgeCommon SOURCES)
get_target_property(StellarForgePhysics_SOURCES StellarForgePhysics SOURCES)
get_target_property(StellarForgeGraphics_SOURCES StellarForgeGraphics SOURCES)
get_target_property(StellarForge_SOURCES StellarForge SOURCES)

# Extract the public headers from the sources (all .hpp files, including those in subdirectories)
foreach (source IN LISTS StellarForge_SOURCES)
    if (source MATCHES ".*\\.hpp$")
        list(APPEND StellarForge_HEADERS ${source})
    endif ()
endforeach ()
foreach (source IN LISTS StellarForgeCommon_SOURCES)
    if (source MATCHES ".*\\.hpp$")
        list(APPEND StellarForge_HEADERS ${source})
    endif ()
endforeach ()
foreach (source IN LISTS StellarForgePhysics_SOURCES)
    if (source MATCHES ".*\\.hpp$")
        list(APPEND StellarForge_HEADERS ${source})
    endif ()
endforeach ()
foreach (source IN LISTS StellarForgeGraphics_SOURCES)
    if (source MATCHES ".*\\.hpp$")
        list(APPEND StellarForge_HEADERS ${source})
    endif ()
endforeach ()

foreach (header IN LISTS StellarForge_HEADERS)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/src/" "" new_header ${header})
    set(new_header "StellarForge/${new_header}")
    get_filename_component(header_dir ${new_header} DIRECTORY)
    file(COPY ${header} DESTINATION include/${header_dir})
endforeach ()

add_subdirectory(tests)

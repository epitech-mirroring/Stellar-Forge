#!/bin/bash

# Set script to exit on any errors.
set -e

# Variables for dependency directories
BUILD_DIR="build"
CONAN_PROFILE="default"

# Function to output information messages in yellow
function write_info {
    local message="$1"
    echo -e "\e[33m[Info] $message\e[0m"
}

# Check if a command exists, install if not
function check_and_install {
    local cmd="$1"
    local pkg="$2"
    write_info "Checking if $cmd is installed..."
    if ! command -v "$cmd" &> /dev/null; then
        write_info "$cmd not found. Installing $pkg..."
        sudo dnf install -y "$pkg"
        write_info "$cmd installed."
    else
        write_info "$cmd is already installed."
    fi
}

# Install dependencies
write_info "Installing required packages..."

# Conan
check_and_install "conan" "conan"

# CMake
check_and_install "cmake" "cmake"

# Ninja (for build tools)
check_and_install "ninja" "ninja-build"

# Python3 (includes pip)
check_and_install "pip3" "python3-pip"

# C++ compiler (gcc-c++)
check_and_install "g++" "gcc-c++"

write_info "All required packages are installed."

conan remote remove Epitech-Mirroring
conan remove '*' -c
conan cache clean '*'
conan profile detect --force


# Common
cd ./src/common && \
mkdir -p "build" && \
cd "build" && \
conan install .. --build=missing && \
cd .. && \
conan create . --build=missing && \
conan create . -s:a build_type=Debug --build=missing &&
cd ../../

# Physics
cd ./src/physics && \
mkdir -p "build" && \
cd "build" && \
conan install .. --build=missing && \
cd .. && \
conan create . --build=missing && \
conan create . -s:a build_type=Debug --build=missing &&
cd ../../

# Graphics
cd ./src/graphics && \
mkdir -p "build" && \
cd "build" && \
conan install .. --build=missing && \
cd .. && \
conan create . --build=missing && \
conan create . -s:a build_type=Debug --build=missing &&
cd ../../

# Engine
cd ./src/engine && \
mkdir -p "build" && \
cd "build" && \
conan install .. --build=missing && \
cd .. && \
conan create . --build=missing && \
conan create . -s:a build_type=Debug --build=missing &&
cd ../../


# Create build directory if it does not exist
info "Creating build directory if it does not exist..."
if [ ! -d "$BUILD_DIR" ]; then
  info "Creating build directory..."
  mkdir -p "$BUILD_DIR"
fi

# Run Conan to install missing dependencies
info "Changing to build directory..."
cd "$BUILD_DIR"

info "Ensuring Conan profile is available..."
if ! conan profile list | grep -q "$CONAN_PROFILE"; then
    info "Creating Conan profile: $CONAN_PROFILE"
    conan profile detect --name "$CONAN_PROFILE"
fi

info "Installing dependencies with Conan..."
conan install .. --build=missing --profile="$CONAN_PROFILE" -g CMakeDeps -g CMakeToolchain

# Run CMake to configure the build
info "Running CMake to configure the build..."
cmake -S .. -B . -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_PREFIX_PATH="." -DCMAKE_BUILD_TYPE=Release

# Build the project with CMake
info "Building the project with CMake..."
cmake --build . --target StellarForge

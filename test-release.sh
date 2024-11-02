#!/bin/bash

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

# Graphics 3D
cd ./src/graphics3D && \
mkdir -p "build" && \
cd "build" && \
conan install .. --build=missing && \
cd .. && \
conan create . --build=missing && \
conan create . -s:a build_type=Debug --build=missing &&
cd ../../

# Engine 3D
cd ./src/engine3D && \
mkdir -p "build" && \
cd "build" && \
conan install .. --build=missing && \
cd .. && \
conan create . --build=missing && \
conan create . -s:a build_type=Debug --build=missing &&
cd ../../

mkdir -p "build" && \
rm -rf build && \
mkdir "build" && \
cd "build" && \
conan install .. --build=missing -s:a build_type=Debug && \
cd .. && \
cmake --preset conan-debug && \
cmake --build build/Debug && \
cd build/Debug && \
cd tests && \
./StellarForgeTests

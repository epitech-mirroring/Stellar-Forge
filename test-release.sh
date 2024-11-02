#!/bin/bash

conan remote remove Epitech-Mirroring
conan remove 'stellar-forge*' -c
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


#!/bin/bash

function load_env() {
    if [ -f .env ]; then
        while IFS= read -r line; do
            if [[ $line == \#* ]]; then
                continue
            fi
            key=$(echo "$line" | cut -d'=' -f1)
            value=$(echo "$line" | cut -d'=' -f2)
            export "$key"="$value"
        done < .env
    fi
}

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

# Set-up the remote
conan remote add Epitech-Mirroring https://nexus.place2die.com/repository/Epitech-Mirroring/
load_env
echo "Logging in to Epitech-Mirroring with user $NEXUS_USER"
conan remote login Epitech-Mirroring "$NEXUS_USER" -p="$NEXUS_PASSWORD"

# Upload
conan upload stellar-forge-common -r=Epitech-Mirroring
conan upload stellar-forge-graphics -r=Epitech-Mirroring
conan upload stellar-forge-physics -r=Epitech-Mirroring
conan upload stellar-forge -r=Epitech-Mirroring
conan upload stellar-forge-graphics-3d -r=Epitech-Mirroring
conan upload stellar-forge-3d -r=Epitech-Mirroring

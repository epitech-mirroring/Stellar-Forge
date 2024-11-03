#!/usr/bin/env bash

function print_check() {
  # Print green checkmark
  echo -e -n "\033[32m✔\033[0m "
}
function print_cross() {
  # Print red cross
  echo -e -n "\033[31m✘\033[0m "
}
function print_question_mark() {
  # Print yellow question mark
  echo -e -n "\033[33m?\033[0m "
}

function show_options() {
  # $1 is the index of the selected option
  # $2 ... $n are the options
  selected_char="⬧"
  unselected_char="⬨"
  current_index=$((2 + $1))
  for i in $(seq 2 $#); do
    if [ "$i" -eq "$current_index" ]; then
      echo -e "$selected_char ${!i}"
    else
      echo -e "$unselected_char ${!i}"
    fi
  done
}

function clear_and_overwrite() {
  for ((i = 0; i < $1; i++)); do
    tput cuu1  # Move cursor up one line
    tput el    # Clear the entire line
  done
}

# Function to ask for user input
function ask() {
    # Display the message passed as argument
    echo -n -e "$1\n"
    selected_option=0
    show_options $selected_option "${@:2}"

    # listen for up and down arrow keys and enter key
    while true; do
      read -s -r -n 1 key

      # Up arrow key
      if [ "$key" == $'\e' ]; then
        read -s -r -n 2 key
        if [ "$key" == $'[A' ]; then
          selected_option=$((selected_option - 1))
          if [ $selected_option -lt 0 ]; then
            selected_option=$(( $# - 2 ))
          fi
        fi
        if [ "$key" == $'[B' ]; then
          selected_option=$((selected_option + 1))
          if [ $selected_option -ge $(( $# - 1 )) ]; then
            selected_option=0
          fi
        fi
      elif [[ "$key" == "" ]] || [[ "$key" == " " ]]; then
        break
      fi
      clear_and_overwrite $(( $# - 1 ))
      show_options $selected_option "${@:2}"
    done
    clear_and_overwrite $#
    selected_option=$((selected_option + 1))
    # Print the selected option
    print_check
    echo -e -n "$1: "
    echo "${@:selected_option+1:1}"

    # Return the selected option
    return $selected_option
}

function prompt() {
  # $1 is the message to display
  # $2 is the default value
  # $3 the result message
  >&2 echo -n "$1 [$2]: "

  # Read user input
  read -r input
  if [ -z "$input" ]; then
    clear_and_overwrite 1 >&2
    print_check >&2
    >&2 echo "$3 $2"
    echo "$2"
  else
    clear_and_overwrite 1 >&2
    print_check >&2
    >&2 echo "$3 $input"
    echo "$input"
  fi
}

ask "What is your build system?" "CMake" "Other"
build_system=$?

if [[ $build_system -eq 1 ]]; then
  ask "Do you want to use Conan?" "Yes" "No"
  conan=$?
  project_name=$(prompt "Enter project name" "my_project" "Project name:")
  project_version=$(prompt "Enter project version" "0.1" "Project version:")
  project_description=$(prompt "Enter project description" "A new project" "Project description:")

  # Check if directory already exists
  if [ -d "$project_name" ]; then
    print_cross
    echo "Directory '$project_name' already exists. Please remove it or choose another name."
    exit 1
  fi

  # Create project directory
  mkdir -p "$project_name"
  cd "$project_name" || exit 1

  # Create CMakeLists.txt
  cat > CMakeLists.txt <<EOF
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)

project($project_name
  VERSION $project_version
  DESCRIPTION "$project_description"
  LANGUAGES CXX)

add_executable(\${PROJECT_NAME} main.cpp)

EOF

  # If Conan is selected, create conanfile.txt
  if [[ $conan -eq 1 ]]; then
    # Check if conan is installed
    if ! command -v conan &> /dev/null; then
      ask "Conan is not installed. Do you want to install it?" "Yes" "No"
      install_conan=$?
      if [[ $install_conan -eq 2 ]]; then
        print_cross
        echo "Please install Conan and run this script again."
        exit 1
      else
        print_check
        echo "Installing Conan..."
        if ! pip install conan; then
          print_cross
          echo "Failed to install Conan. Please install it manually."
          exit 1
        fi
      fi
    fi
    # Check if remote is already added
    if ! conan remote list | grep -q "Epitech-Mirroring"; then
      print_check
      echo "Adding Epitech-Mirroring remote..."
      conan remote add Epitech-Mirroring https://nexus.place2die.com/repository/Epitech-Mirroring/
    else
      print_check
      echo "Epitech-Mirroring remote already added."
    fi
    cat > conanfile.txt <<EOF
[requires]
stellar-forge/v0.2.0

[generators]
CMakeDeps
CMakeToolchain
EOF

  # Add stellar-forge to CMakeLists.txt
  echo "find_package(stellar-forge REQUIRED)" >> CMakeLists.txt
  echo "target_link_libraries(\${PROJECT_NAME} PRIVATE stellar-forge::stellar-forge)" >> CMakeLists.txt
  else
    # Create lib directory
    mkdir -p lib
    mkdir -p includes
    echo -n -e "include_directories(includes)\nlink_directories(lib)\n" >> CMakeLists.txt
    echo -n -e "target_link_libraries(\${PROJECT_NAME} PRIVATE StellarForge)\n" >> CMakeLists.txt
    print_question_mark
    echo "Please refer to the documentation on how to install Stellar Forge."
  fi

  # Create assets directory
  mkdir -p assets
  mkdir -p assets/scenes
  mkdir -p assets/objects

  # Create a default scene
  cat > assets/scenes/default.json <<EOF
{
  "id": "0bcce674-956e-41b6-8ce6-74956e11b64b",
  "objects": []
}
EOF


  # Create main.cpp
  cat > main.cpp <<EOF
#include <StellarForge/Engine/Engine.hpp>

int main() {
    Engine const engine([]() {},
EOF
  echo -n -e "\"$project_name\");\n" >> main.cpp
  cat >> main.cpp <<EOF
  return 0;
}
EOF

  print_check
  echo "Project generated successfully."

  ask "Do you want to generate a build script?" "Yes" "No"
  generate_build_script=$?
  if [[ $generate_build_script -eq 1 ]]; then
    cat > build-linux.sh <<EOF
#!/bin/bash
mkdir -p build
conan install . --build=missing -s:a build_type=Debug -of build/Debug
cmake --preset conan-debug
cmake --build build/Debug
rm -rf $project_name
cp build/Debug/$project_name .
EOF
    chmod +x build-linux.sh

    cat > build-windows.ps1 <<EOF
mkdir build
conan install . --build=missing -s:a build_type=Debug -of build/Debug
cmake --preset conan-default
cmake --build build/Debug
Remove-Item -Recurse -Force $project_name
Copy-Item build/Debug/$project_name .
EOF
    print_check
    echo "Build script generated successfully."
  fi
  print_check
  echo "All done!"
  print_question_mark
  echo "Please refer to the documentation for further instructions. (https://wiki.simon-gl.fr)"
  echo "🎉 Happy coding!"
else
  print_cross
  echo "Please check documentation for instructions on how to generate project for other build systems."
fi

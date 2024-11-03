# Define functions for symbols
function Print-Check {
    Write-Host "✔" -ForegroundColor Green -NoNewline
}
function Print-Cross {
    Write-Host "✘" -ForegroundColor Red -NoNewline
}
function Print-QuestionMark {
    Write-Host "?" -ForegroundColor Yellow -NoNewline
}

# Function to display selectable options
function Show-Options {
    param (
        [int]$SelectedOption,
        [string[]]$Options
    )
    $selectedChar = "⬧"
    $unselectedChar = "⬨"
    for ($i = 0; $i -lt $Options.Length; $i++) {
        if ($i -eq $SelectedOption) {
            Write-Host "$selectedChar $($Options[$i])"
        } else {
            Write-Host "$unselectedChar $($Options[$i])"
        }
    }
}

# Function to clear and overwrite lines
function Clear-And-Overwrite {
    param ([int]$lines)
    for ($i = 0; $i -lt $lines; $i++) {
        [System.Console]::SetCursorPosition(0, [System.Console]::CursorTop - 1)
        Write-Host (" " * [System.Console]::WindowWidth) -NoNewline
        [System.Console]::SetCursorPosition(0, [System.Console]::CursorTop - 1)
    }
}

# Function to prompt user for input
function Prompt {
    param (
        [string]$message,
        [string]$defaultValue,
        [string]$resultMessage
    )
    Write-Host "$message [$defaultValue]: " -NoNewline
    $input = Read-Host
    if ([string]::IsNullOrEmpty($input)) {
        Clear-And-Overwrite 1
        Print-Check
        Write-Host "$resultMessage $defaultValue"
        return $defaultValue
    } else {
        Clear-And-Overwrite 1
        Print-Check
        Write-Host "$resultMessage $input"
        return $input
    }
}

# Ask function to capture selection from options
function Ask {
    param (
        [string]$message,
        [string[]]$options
    )
    $selectedOption = 0
    Write-Host "$message"
    Show-Options -SelectedOption $selectedOption -Options $options

    while ($true) {
        $key = [System.Console]::ReadKey($true)
        if ($key.Key -eq 'UpArrow') {
            $selectedOption = ($selectedOption - 1) % $options.Length
            if ($selectedOption -lt 0) { $selectedOption = $options.Length - 1 }
        } elseif ($key.Key -eq 'DownArrow') {
            $selectedOption = ($selectedOption + 1) % $options.Length
        } elseif ($key.Key -eq 'Enter') {
            break
        }
        Clear-And-Overwrite $options.Length
        Show-Options -SelectedOption $selectedOption -Options $options
    }
    Clear-And-Overwrite $options.Length
    Print-Check
    Write-Host "$message: $($options[$selectedOption])"
    return $selectedOption
}

# Main script logic
$buildSystem = Ask "What is your build system?" @("CMake", "Other")
if ($buildSystem -eq 0) {
    $useConan = Ask "Do you want to use Conan?" @("Yes", "No")
    $projectName = Prompt -message "Enter project name" -defaultValue "my_project" -resultMessage "Project name:"
    $projectVersion = Prompt -message "Enter project version" -defaultValue "0.1" -resultMessage "Project version:"
    $projectDescription = Prompt -message "Enter project description" -defaultValue "A new project" -resultMessage "Project description:"

    # Check if directory exists
    if (Test-Path $projectName) {
        Print-Cross
        Write-Host "Directory '$projectName' already exists. Please remove it or choose another name."
        exit 1
    }

    # Create project structure
    New-Item -Path $projectName -ItemType Directory | Out-Null
    Set-Location -Path $projectName

    # Create CMakeLists.txt
    @"
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)

project($projectName
  VERSION $projectVersion
  DESCRIPTION "$projectDescription"
  LANGUAGES CXX)

add_executable(\${PROJECT_NAME} main.cpp)
"@ | Out-File -FilePath CMakeLists.txt

    if ($useConan -eq 0) {
        # Check for conan installation
        if (-not (Get-Command conan -ErrorAction SilentlyContinue)) {
            $installConan = Ask "Conan is not installed. Do you want to install it?" @("Yes", "No")
            if ($installConan -eq 0) {
                Print-Check
                Write-Host "Installing Conan..."
                try {
                    pip install conan
                } catch {
                    Print-Cross
                    Write-Host "Failed to install Conan. Please install it manually."
                    exit 1
                }
            } else {
                Print-Cross
                Write-Host "Please install Conan and run this script again."
                exit 1
            }
        }
        # Add Conan remote if not already added
        if (-not (conan remote list | Select-String "Epitech-Mirroring")) {
            Print-Check
            Write-Host "Adding Epitech-Mirroring remote..."
            conan remote add Epitech-Mirroring https://nexus.place2die.com/repository/Epitech-Mirroring/
        } else {
            Print-Check
            Write-Host "Epitech-Mirroring remote already added."
        }

        @"
[requires]
stellar-forge/v0.2.0

[generators]
CMakeDeps
CMakeToolchain
"@ | Out-File -FilePath conanfile.txt

        Add-Content -Path CMakeLists.txt -Value "find_package(stellar-forge REQUIRED)"
        Add-Content -Path CMakeLists.txt -Value "target_link_libraries(\${PROJECT_NAME} PRIVATE stellar-forge::stellar-forge)"
    } else {
        New-Item -Path "lib" -ItemType Directory | Out-Null
        New-Item -Path "includes" -ItemType Directory | Out-Null
        Add-Content -Path CMakeLists.txt -Value "include_directories(includes)"
        Add-Content -Path CMakeLists.txt -Value "link_directories(lib)"
        Add-Content -Path CMakeLists.txt -Value "target_link_libraries(\${PROJECT_NAME} PRIVATE StellarForge)"
        Print-QuestionMark
        Write-Host "Please refer to the documentation on how to install Stellar Forge."
    }

    # Additional structure
    New-Item -Path "assets/scenes" -ItemType Directory -Force | Out-Null
    New-Item -Path "assets/objects" -ItemType Directory -Force | Out-Null
    @"
{
  "id": "0bcce674-956e-41b6-8ce6-74956e11b64b",
  "objects": []
}
"@ | Out-File -FilePath "assets/scenes/default.json"

    @"
#include <StellarForge/Engine/Engine.hpp>

int main() {
    Engine const engine([]() {}, \"$projectName\");
    return 0;
}
"@ | Out-File -FilePath main.cpp

    Print-Check
    Write-Host "Project generated successfully."

    $generateBuildScript = Ask "Do you want to generate a build script?" @("Yes", "No")
    if ($generateBuildScript -eq 0) {
        @"
mkdir build
conan install . --build=missing -s:a build_type=Debug -of build/Debug
cmake --preset conan-default
cmake --build build/Debug
Remove-Item -Recurse -Force $projectName
Copy-Item build/Debug/$projectName .
"@ | Out-File -FilePath "build-windows.ps1"

        Print-Check
        Write-Host "Build script generated successfully."
    }

    Print-Check
    Write-Host "All done!"
    Print-QuestionMark
    Write-Host "Please refer to the documentation for further instructions. (https://wiki.simon-gl.fr)"
    Write-Host "🎉 Happy coding!"
} else {
    Print-Cross
    Write-Host "Please check documentation for instructions on how to generate project for other build systems."
}

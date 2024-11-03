# Stellar Forge

![Stellar Forge](https://i.ibb.co/Y2v4Y2w/fc097271-6845-486f-8ede-f292f48c5c40.jpg)

![EPITECH Project](https://img.shields.io/badge/EPITECH-2024-007EC6?style=for-the-badge&logo=epitech&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![SFML](https://img.shields.io/badge/SFML-184F9C?style=for-the-badge&logo=SFML&logoColor=green)
![CMake](https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white)
![Fedora](https://img.shields.io/badge/Fedora-294172?style=for-the-badge&logo=fedora&logoColor=white)
![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)

**Stellar Forge** is the custom game engine that powers **R-Type: Reborn**, designed from
the ground up to support networked gameplay, modern graphics, and advanced game mechanics.

## Table of Contents

- [Project Purpose](#project-purpose)
- [Dependencies & Requirements](#dependencies--requirements)
- [Supported Platforms](#supported-platforms)
- [Build Instructions](#build-instructions)
- [Documentation](#documentation)
- [Example Games](#example-games)
- [Authors & Contact](#authors--contact)
- [Useful Links](#useful-links)

## Project Purpose

**Stellar Forge** is a custom-built game engine designed to power networked video games,
like **R-Type: Reborn**. It was created to support modern game development techniques,
such as multi-threading, network synchronization, and real-time 2D rendering, all while
offering flexibility for game designers using the **Orion Editor**.

This engine allows us to modernize classic games like R-Type by enabling new game
mechanics, improved graphics, and optimized performance, while demonstrating best
practices in software engineering.

## Dependencies & Requirements

To build and run **Stellar Forge**, you will need:

- **C++** compiler supporting C++17 or later
- **SFML** (Simple and Fast Multimedia Library) for graphics, audio and input (For the 2D Game Engine)
- **CMake** for building the project
- **Raylib** for graphics, audio and input (For the 3D Game Engine)
- **GLM** (OpenGL Mathematics) for vector and matrix operations
- **Conan** for managing dependencies

You can install the dependencies using your platform's package manager or follow the
official documentation for each tool.

## Supported Platforms

- Windows 10+
- Linux (Fedora, Ubuntu, etc.)

## Build Instructions

To build **Stellar Forge**, follow these steps:

### Windows

1. Clone the repository to your local machine.
2. Open a terminal and navigate to the project directory.
3. Launch the following commands:

```bash
./build-windows.ps1
```

4. Accept the installation of the dependencies.
5. The project will be built in the `build` directory and the libraries will be copied at the root of the project.

### Linux

1. Clone the repository to your local machine.
2. Open a terminal and navigate to the project directory.
3. Launch the following commands: (You need to have sudo rights)

```bash
sudo ./build-linux.sh
```

4. Accept the installation of the dependencies.
5. The project will be built in the `build` directory and the libraries will be copied at the root of the project.

## Documentation

You can find the documentation for **Stellar Forge** in
the [R-Type: Reborn](https://github.com/epitech-mirroring/R-Type-Reborn) repository or in
the [Documentation](https://github.com/epitech-mirroring/R-Type-docs) repository.
You can also find the documentation on the following
website: [Stellar Forge Documentation](https://wiki.simon-gl.fr/en/home).
If you have any questions or need help, feel free to reach out to the authors.

## Example Games

**Stellar Forge** can be used to create a wide range of games, from classic arcade shooters to modern multiplayer
experiences. Here are some examples of games that can be built using **Stellar Forge**:

- **Flappy-Bird-Reborn**: is a clone of the iconic game named Flappy Bird. Your goal is to survive and avoid the pipes
  that appears near you. [click here](https://github.com/epitech-mirroring/Flappy-Bird-Reborn) to try this game!
- **R-Type-Reborn**: is a modern reimagining of the classic arcade shoot 'em up, combining nostalgic gameplay with new
  features and enhancements. [click here](https://github.com/epitech-mirroring/R-Type-Reborn) to try this game!
- **Demo Sample 3D Engine**: is a simple 3D game engine that demonstrates the capabilities of the Stellar Forge engine
  3D. [click here](https://github.com/epitech-mirroring/Demo-Sample-3D-Engine) to try the demo!

## Authors & Contact

<table>
    <tbody>
        <tr>
            <td align="center"><a href="https://github.com/Marius-P1/"><img src="https://avatars.githubusercontent.com/u/114705049?&=4" width="100px;" alt="Marius-P1"/><br/><sub><b>Marius PAIN</b></sub></a><br/></td>
            <td align="center"><a href="https://github.com/AubaneNourry/"><img src="https://avatars.githubusercontent.com/u/114694895?v=4" width="100px;" alt="AubaneNourry"/><br/><sub><b>Aubane NOURRY</b></sub></a><br/></td>
            <td align="center"><a href="https://github.com/6im0n/"><img src="https://avatars.githubusercontent.com/u/46846093?v=4" width="100px;" alt="6im0n"/><br/><sub><b>Simon GANIER-LOMBARD</b></sub></a><br/></td>
            <td align="center"><a href="https://github.com/RenardFute/"><img src="https://avatars.githubusercontent.com/u/38489683?v=4" width="100px;" alt="RenardFute"/><br/><sub><b>Axel ECKENBERG</b></sub></a><br/></td>
            <td align="center"><a href="https://github.com/landryarki/"><img src="https://avatars.githubusercontent.com/u/114699649?v=4" width="100px;" alt="landryarki"/><br/><sub><b>Landry GIGANT</b></sub></a><br/></td>
        </tr>
    </tbody>
</table>

## Useful Links

- [EPITECH](https://www.epitech.eu/)
- [Stellar Forge](https://github.com/epitech-mirroring/Stellar-Forge)
- [Orion Editor](https://github.com/epitech-mirroring/Orion-Editor)
- [R-Type: Reborn](https://github.com/epitech-mirroring/R-Type-Reborn)
- [Documentation Repository](https://github.com/epitech-mirroring/R-Type-docs)

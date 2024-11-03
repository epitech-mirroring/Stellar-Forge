from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps

STELLAR_FORGE_VERSION = "rc-v0.2.0"


class StellarForge(ConanFile):
    name = "stellar-forge"
    version = STELLAR_FORGE_VERSION

    url = "https://github.com/epitech-mirroring/Stellar-Forge"
    description = "The game engine under Orion Editor"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {}
    default_options = {}

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "*", "!build/*"

    def config_options(self):
        pass

    def requirements(self):
        self.requires("glm/1.0.1")
        self.requires("sfml/2.6.1")
        self.requires("stellar-forge-common/" + STELLAR_FORGE_VERSION)
        self.requires("stellar-forge-graphics/" + STELLAR_FORGE_VERSION)
        self.requires("stellar-forge-physics/" + STELLAR_FORGE_VERSION)

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["StellarForge"]
        self.cpp_info.libdirs = ["lib"]

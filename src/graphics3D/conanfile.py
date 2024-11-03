from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps

STELLAR_FORGE_VERSION = "v0.3.0"


class StellarForgeGraphics3D(ConanFile):
    name = "stellar-forge-graphics-3d"
    version = STELLAR_FORGE_VERSION

    # Optional metadata
    url = "https://github.com/epitech-mirroring/Stellar-Forge"
    description = "Graphic 3D library for Stellar-Forge"

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
        self.requires("raylib/4.0.0")
        self.requires("glfw/3.4.0")
        self.requires("stellar-forge-common/" + STELLAR_FORGE_VERSION)

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
        self.cpp_info.libs = ["StellarForgeGraphics3D"]
        self.cpp_info.libdirs = ["lib"]

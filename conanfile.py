from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps

STELLAR_FORGE_VERSION = "v0.2.0"


class StellarForge(ConanFile):
    settings = "os", "compiler", "build_type", "arch"

    def config_options(self):
        pass

    def requirements(self):
        self.requires("glm/1.0.1")
        self.requires("sfml/2.6.1")
        self.requires("stellar-forge-common/" + STELLAR_FORGE_VERSION)
        self.requires("stellar-forge-physics/" + STELLAR_FORGE_VERSION)
        self.requires("stellar-forge-graphics/" + STELLAR_FORGE_VERSION)
        self.requires("stellar-forge/" + STELLAR_FORGE_VERSION)
        self.requires("stellar-forge-graphics-3d/" + STELLAR_FORGE_VERSION)
        self.requires("stellar-forge-3d/" + STELLAR_FORGE_VERSION)
        self.requires("gtest/1.15.0")
        self.requires("raylib/4.0.0")
        self.requires("glfw/3.4.0")

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

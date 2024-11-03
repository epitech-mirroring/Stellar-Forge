from conan import ConanFile
from conan.tools.build import check_min_cppstd, check_max_cppstd
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps

STELLAR_FORGE_VERSION = "rc-v0.2.0"


class StellarForgeCommon(ConanFile):
    name = "stellar-forge-common"
    version = STELLAR_FORGE_VERSION

    # Optional metadata
    url = "https://github.com/epitech-mirroring/Stellar-Forge"
    description = "Common library for Stellar-Forge"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {}
    default_options = {}
    exports_sources = "CMakeLists.txt", "*", "!build/*"

    def config_options(self):
        pass

    def layout(self):
        cmake_layout(self)

    def validate(self):
        check_min_cppstd(self, "17")
        check_max_cppstd(self, "20")

    def requirements(self):
        self.requires("glm/1.0.1")

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
        self.cpp_info.libs = ["StellarForgeCommon"]
        self.cpp_info.libdirs = ["lib"]

/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include "DynamicComponentLoader.hpp"
#include <filesystem>
#include <dlfcn.h>

#include "common/factories/ComponentFactory.hpp"

const Logger DynamicComponentLoader::LOG = Logger();

DynamicComponentLoader::DynamicComponentLoader(std::string path)
    : _directoryPath(std::move(path)) {
}

DynamicComponentLoader::~DynamicComponentLoader() {
    for (auto *const handle: this->_handles) {
        if (dlclose(handle) != 0) {
            LOG.error << "Failed to close handle: " << dlerror() << '\n';
        }
    }
}


void DynamicComponentLoader::loadComponents() {
    std::filesystem::path const path(this->_directoryPath);
    if (!exists(path)) {
        LOG.error << "Components directory: '" << absolute(path) << "' does not exists."
                << '\n';
        return;
    }
    this->_loadComponentsDirectory(path);
}

void DynamicComponentLoader::_loadComponentsDirectory(const std::filesystem::path &path) {
    if (!is_directory(path)) {
        LOG.error << "Path: '" << absolute(path) << "' is not a directory." << '\n';
        return;
    }
    for (const auto &entry: std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            this->_loadComponent(entry.path());
        }
        if (entry.is_directory()) {
            this->_loadComponentsDirectory(entry.path());
        }
    }
}

void DynamicComponentLoader::_loadComponent(const std::filesystem::path &path) {
#ifdef __linux__
    if (path.extension() != ".so") {
#else
#ifdef __APPLE__
    if (path.extension() != ".dylib") {
#elif defined(_WIN32) || defined(_WIN64)
    if (path.extension() != ".dll") {
#else
    if (true) {
        LOG.error << "Unsupported platform for dynamic component loading." << '\n';
#endif
#endif
        return;
    }

    void *handle = dlopen(path.c_str(), RTLD_LAZY);
    if (handle == nullptr) {
        LOG.error << "Failed to load components in: " << path << " - " << dlerror() <<
                '\n';
        return;
    }
    auto *getComponentNames = reinterpret_cast<const char **(*)()>(dlsym(
        handle, "getComponentName"));
    auto *registerComponents = reinterpret_cast<void (*)()>(dlsym(
        handle, "registerComponent"));
    if (getComponentNames == nullptr || registerComponents == nullptr) {
        LOG.error << "Failed to load components: " << path << " - " << dlerror() << '\n';
        return;
    }
    const char **componentNames = getComponentNames();
    for (auto i = 0; componentNames[i] != nullptr; i++) {
        LOG.info << "Loading component: " << componentNames[i] << '\n';
    }
    registerComponents();

    for (auto i = 0; componentNames[i] != nullptr; i++) {
        if (!ComponentFactory::getInstance().hasComponent(componentNames[i])) {
            LOG.error << "Failed to register component: " << componentNames[i] <<
                    '\n';
        } else {
            LOG.info << "Component: " << componentNames[i] << " registered." << '\n';
        }
    }
    this->_handles.push_back(handle);
}
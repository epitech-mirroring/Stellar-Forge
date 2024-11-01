/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include "DynamicComponentLoader.hpp"
#include <filesystem>


const Logger DynamicComponentLoader::LOG = Logger();

DynamicComponentLoader::DynamicComponentLoader(std::string path)
    : _directoryPath(std::move(path)) {
}

DynamicComponentLoader::~DynamicComponentLoader() {
    for (auto &[handle, components]: this->_handles) {
        for (const auto &component: components) {
            ComponentFactory::getInstance().safeUnregisterComponent(component);
        }
#ifdef _WIN32
        if (FreeLibrary(handle) == 0) {
            LOG.error << "Failed to close handle " << std::to_string(GetLastError()) << " with components: ";
            for (const auto &component: components) {
                LOG.error << component << ' ';
            }
            LOG.error << '\n';
        }
#else
        if (dlclose(handle) != 0) {
            LOG.error << "Failed to close handle: " << dlerror() << " with components: ";
            for (const auto &component: components) {
                LOG.error << component << ' ';
            }
            LOG.error << '\n';
        }
#endif
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

#ifdef __linux__
    void *handle = dlopen(path.c_str(), RTLD_LAZY);
    if (handle == nullptr) {
        LOG.error << "Failed to load components in: " << path << " - " << dlerror() <<
                '\n';
        return;
    }
    this->_handles.push_back({handle, {}});
    auto *getComponentNames = reinterpret_cast<const char **(*)()>(dlsym(
        handle, "getComponentName"));
    auto *registerComponents = reinterpret_cast<void (*)(ComponentFactory *)>(dlsym(
        handle, "registerComponents"));
    if (getComponentNames == nullptr || registerComponents == nullptr) {
        LOG.error << "Failed to load components: " << path << " - " << dlerror() << '\n';
        return;
    }
#else
    const std::string filepath = path.string();
    HINSTANCE handle = LoadLibrary(filepath.c_str());
    if (handle == nullptr) {
        LOG.error << "Failed to load components in: " << path << " - " << std::to_string(GetLastError()) << '\n';
        return;
    }
    this->_handles.push_back({handle, {}});
    auto *getComponentNames = reinterpret_cast<const char **(*)()>(GetProcAddress(handle, "getComponentName"));
    auto *registerComponents = reinterpret_cast<void (*)(ComponentFactory *)>(GetProcAddress(handle, "registerComponents"));
    if (getComponentNames == nullptr || registerComponents == nullptr) {
        LOG.error << "Failed to load components: " << path << " - " << std::to_string(GetLastError()) << '\n';
    }
#endif

    const char **componentNames = getComponentNames();
    for (auto i = 0; componentNames[i] != nullptr; i++) {
        LOG.info << "Loading component: " << componentNames[i] << '\n';
    }
    registerComponents(&ComponentFactory::getInstance());

    for (auto i = 0; componentNames[i] != nullptr; i++) {
        if (!ComponentFactory::getInstance().hasComponent(componentNames[i])) {
            LOG.error << "Failed to register component: " << componentNames[i] <<
                    '\n';
        } else {
            LOG.info << "Component: " << componentNames[i] << " registered." << '\n';
            this->_handles.back().second.emplace_back(componentNames[i]);
        }
    }

}

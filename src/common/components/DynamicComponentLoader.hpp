/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#ifndef COMPONENTLOADER_HPP
#define COMPONENTLOADER_HPP
#include <string>
#include <vector>

#ifdef _WIN32
    #define UUID UUID_WINDOWS
    #include <windows.h>
    #undef UUID
#else
    #include <dlfcn.h>
#endif

#include "../utils/Logger.hpp"
#include "../factories/ComponentFactory.hpp"

class DynamicComponentLoader {
protected:
    std::string _directoryPath;
    static const Logger LOG;


#ifdef _WIN32
    std::vector<std::pair<HINSTANCE, std::vector<std::string> > > _handles;

    typedef const char **(GetComponentNames)();
    typedef void (RegisterComponents)(ComponentFactory *);
#else
    std::vector<std::pair<void *, std::vector<std::string> > > _handles;
#endif

    void _loadComponentsDirectory(const std::filesystem::path &path);

    void _loadComponent(const std::filesystem::path &path);

public:
    explicit DynamicComponentLoader(std::string path);

    ~DynamicComponentLoader();

    void loadComponents();
};

#endif //COMPONENTLOADER_HPP

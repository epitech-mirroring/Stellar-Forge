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

#include "common/utils/Logger.hpp"

class DynamicComponentLoader {
protected:
    std::string _directoryPath;
    static const Logger LOG;
    std::vector<void *> _handles;

    void _loadComponentsDirectory(const std::filesystem::path &path);

    void _loadComponent(const std::filesystem::path &path);

public:
    explicit DynamicComponentLoader(std::string path);

    ~DynamicComponentLoader();

    void loadComponents();
};

#endif //COMPONENTLOADER_HPP

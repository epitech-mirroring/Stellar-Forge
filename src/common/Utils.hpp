/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#ifndef UTILS_HPP
#define UTILS_HPP
#if defined(__linux__) || defined(__APPLE__)
#include <cxxabi.h>

template<typename T>
std::string get_typename([[maybe_unused]] T *object) {
    return abi::__cxa_demangle(typeid(*object).name(), nullptr, nullptr, nullptr);
}

#else
#if defined(_WIN32)

#include <dbghelp.h>

template<typename T>
auto get_typename() {
    auto type_info = typeid(T);
    char *name = nullptr;
    auto status = UnDecorateSymbolName(type_info.name(), name, 0, 0);
    if (status == 0) {
        return std::string(type_info.name());
    }
    return std::string(name);
}
#endif

template<typename T>
std::string get_typename([[maybe_unused]] T *object) {
    return typeid(*object).name();
}

#endif

#endif //UTILS_HPP

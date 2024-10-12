/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#ifndef UTILS_HPP
#define UTILS_HPP
#include <cxxabi.h>

template<typename T>
std::string get_typename([[maybe_unused]] T *object) {
    return abi::__cxa_demangle(typeid(*object).name(), nullptr, nullptr, nullptr);
}

#endif //UTILS_HPP

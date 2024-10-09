/*
** EPITECH PROJECT, 2024
** Stellar-Forge
** File description:
** GraphicsException
*/

#include "GraphicsException.hpp"

GraphicsException::GraphicsException(std::string message): _message{std::move(message)} {
}

const char *GraphicsException::what() const noexcept {
    return _message.c_str();
}

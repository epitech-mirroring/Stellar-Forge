/*
** EPITECH PROJECT, 2024
** Stellar-Forge
** File description:
** UUIDException
*/

#include "UUIDException.hpp"

UUIDException::UUIDException(const std::string& message): _message{message}
{
}

const char* UUIDException::what() const noexcept
{
    return _message.c_str();
}

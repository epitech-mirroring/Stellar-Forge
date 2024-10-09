/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** FileField.cpp
*/

#include "FileField.hpp"
#include <utility>

FileField::FileField(std::string name, std::string description)
    : AField(std::move(name), std::move(description), STRING)
{
}

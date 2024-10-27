/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** AField.cpp
*/

#include "AField.hpp"

#ifndef __APPLE__
#include <utility>
#endif

AField::AField(std::string name, std::string description,
               const IComponent::IMeta::FieldType type): _name(std::move(name)),
                                                         _description(
                                                             std::move(description)),
                                                         _type(type) {
}

std::string AField::getName() const {
    return this->_name;
}

std::string AField::getDescription() const {
    return this->_description;
}

IComponent::IMeta::FieldType AField::getType() const {
    return this->_type;
}

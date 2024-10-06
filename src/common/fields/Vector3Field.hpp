/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#ifndef STELLARFORGE_VECTOR3FIELD_HPP
#define STELLARFORGE_VECTOR3FIELD_HPP

#include <utility>

#include "../AField.hpp"

class Vector3Field : public AField {
public:
    Vector3Field(std::string name, std::string description)
        : AField(std::move(name), std::move(description), IComponent::IMeta::IField::FieldType::VECTOR3) {}
};

#endif //STELLARFORGE_VECTOR3FIELD_HPP

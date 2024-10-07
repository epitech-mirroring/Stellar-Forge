/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#include "Vector3Field.hpp"

Vector3Field::Vector3Field(std::string name, std::string description)
    : AField(std::move(name), std::move(description), IComponent::IMeta::IField::FieldType::VECTOR3)
{
}

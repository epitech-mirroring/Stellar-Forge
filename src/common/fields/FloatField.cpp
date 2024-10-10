/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#include "FloatField.hpp"

FloatField::FloatField(std::string name, std::string description)
    : AField(std::move(name), std::move(description), IComponent::IMeta::IField::FieldType::FLOAT)
{
}

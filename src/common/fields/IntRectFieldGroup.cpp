/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#include "IntRectFieldGroup.hpp"

IntRectFieldGroup::IntRectFieldGroup(std::string name, std::string description)
    : AFieldGroup(name, description, {
        new AField("x", "The x-coordinate of the rectangle", AField::FieldType::INT), 
        new AField("y", "The y-coordinate of the rectangle", AField::FieldType::INT), 
        new AField("width", "The width of the rectangle", AField::FieldType::INT),
        new AField("height", "The height of the rectangle", AField::FieldType::INT)
    })
{
}

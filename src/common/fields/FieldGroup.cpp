/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#include "FieldGroup.hpp"

InvisibleFieldGroup::InvisibleFieldGroup(const std::vector<IComponent::IMeta::IField *> &fields)
    : AFieldGroup("", "", fields)
{
}

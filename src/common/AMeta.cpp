/*
** EPITECH PROJECT, 2024
** Stellar-Forge
** File description:
** AMeta
*/

#include "AMeta.hpp"

#include <utility>

AMeta::AMeta(std::string name, std::string description, const bool isUnique,
             const bool isRemovable,
             std::vector<IFieldGroup*>&& fieldGroups):
    _name(std::move(name)), _description(std::move(description)), _fieldGroups(std::move(fieldGroups)),
    _isUnique(isUnique), _isRemovable(isRemovable)
{
}

std::string AMeta::getName() const
{
    return this->_name;
}

std::string AMeta::getDescription() const
{
    return this->_description;
}

bool AMeta::isUnique() const
{
    return this->_isUnique;
}

bool AMeta::canBeRemoved() const
{
    return this->_isRemovable;
}

std::vector<IComponent::IMeta::IFieldGroup*> AMeta::getFieldGroups() const
{
    return this->_fieldGroups;
}

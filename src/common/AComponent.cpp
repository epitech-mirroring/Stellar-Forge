/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** AComponent.cpp
*/

#include "AComponent.hpp"

AComponent::AComponent(IObject *owner, IMeta &meta) : _owner(owner), _meta(meta), _isActive(true)
{
}

IObject *AComponent::getOwner()
{
    return this->_owner;
}

IComponent::IMeta &AComponent::getMeta() const
{
    return this->_meta;
}

bool AComponent::isActive()
{
    return this->_isActive;
}

void AComponent::setActive(bool active)
{
    this->_isActive = active;
}

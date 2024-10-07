/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** AGraphicsComponent.cpp
*/

#include "AGraphicsComponent.hpp"

AGraphicsComponent::AGraphicsComponent(IObject *owner, IMeta &meta) : _owner(owner), _meta(meta)
{
}

IObject *AGraphicsComponent::getOwner()
{
    return this->_owner;
}

IComponent::IMeta &AGraphicsComponent::getMeta() const
{
    return this->_meta;
}

bool AGraphicsComponent::isActive()
{
    return this->_isActive;
}

void AGraphicsComponent::setActive(bool active)
{
    this->_isActive = active;
}

/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** AComponent.cpp
*/

#include "AComponent.hpp"

AComponent::AComponent(IObject *owner, const IMeta &meta) : _owner(owner), _meta(meta), _isActive(true)
{
}

void AComponent::onStart()
{
}

void AComponent::beforeRendering()
{
}

void AComponent::afterRendering()
{
}

IObject* AComponent::getOwner()
{
    return this->_owner;
}

const IComponent::IMeta &AComponent::getMeta() const
{
    return this->_meta;
}

bool AComponent::isActive()
{
    return this->_isActive;
}

void AComponent::setActive(bool state)
{
    this->_isActive = state;
}

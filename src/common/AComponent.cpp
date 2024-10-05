/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** AComponent.cpp
*/

#include "AComponent.hpp"

AComponent::AComponent(IObject *owner, IMeta &meta) : _meta(meta)
{
    this->_uuid = ObjectManager::getInstance().get_component_UUID(owner, this);
}

IObject *AComponent::getOwner()
{
    return ObjectManager::getInstance().get_object_from_component(this->_uuid);
}

IComponent::IMeta &AComponent::getMeta() const
{
    return this->_meta;
}

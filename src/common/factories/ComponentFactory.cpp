/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include "ComponentFactory.hpp"

IComponent *ComponentFactory::create(const std::string &typeName, IObject *owner,
                                     const json::JsonObject *data) {
    if (registry.find(typeName) != registry.end()) {
        auto *comp = registry[typeName](owner, data);
        return comp;
    }
    return nullptr;
}

bool ComponentFactory::hasComponent(const std::string &typeName) const {
    return registry.find(typeName) != registry.end();
}

ComponentFactory *ComponentFactory::INSTANCE = new ComponentFactory();

/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include "ComponentFactory.hpp"

ComponentFactory *ComponentFactory::INSTANCE = nullptr;

ComponentFactory::ComponentFactory() {
    LOG = Logger("components");
}


IComponent *ComponentFactory::create(const std::string &typeName, IObject *owner,
                                     const json::JsonObject *data) {
    if (registry.find(typeName) != registry.end()) {
        auto *comp = registry[typeName](owner, data);
        return comp;
    }
    return nullptr;
}

ComponentFactory::~ComponentFactory() {
    for (auto &[typeName, constructor]: registry) {
        LOG.info << "Unregistering component: " << typeName << '\n';
    }
}

bool ComponentFactory::hasComponent(const std::string &typeName) const {
    return registry.find(typeName) != registry.end();
}

void ComponentFactory::safeUnregisterComponent(const std::string &typeName) {
    if (!hasComponent(typeName)) {
        return;
    }
    LOG.info << "Unregistering component: " << typeName << '\n';
    registry.erase(typeName);
}

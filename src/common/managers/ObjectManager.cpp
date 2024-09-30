/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** ObjectManager.cpp
*/

#include "ObjectManager.hpp"

std::unordered_map<UUID, IObject *> ObjectManager::getObjects() const
{
    return _objects;
}

size_t ObjectManager::getObjectCount() const
{
    return _objects.size();
}

bool ObjectManager::objectExists(const UUID& id) const
{
    return _objects.find(id) != _objects.end();
}

void ObjectManager::addObject(const UUID& id, IObject *object)
{
    if (_objects.find(id) != _objects.end()) {
        throw ManagerException("Object with ID " + id.getUuidString() + " already exists: overwriting.");
    }
    _objects[id] = object;
}

void ObjectManager::addObjects(const std::unordered_map<UUID, IObject *>& objects)
{
    for (const auto& object : objects) {
        addObject(object.first, object.second);
    }
}

void ObjectManager::removeObject(const UUID& id)
{
    if (_objects.erase(id) == 0) {
        throw ManagerException("Object with ID " + id.getUuidString() + " does not exist.");
    }
}

void ObjectManager::removeObjects(const std::vector<UUID>& ids)
{
    for (const auto& id : ids) {
        removeObject(id);
    }
}

void ObjectManager::updateObject(const UUID& id, IObject *updatedObject)
{
    if (!objectExists(id)) {
        throw ManagerException("Object with ID " + id.getUuidString() + " does not exist, creating a new one.");
    }
    _objects[id] = updatedObject;
}

IObject *ObjectManager::getObjectById(const UUID& id) const
{
    auto it = _objects.find(id);
    if (it != _objects.end()) {
        return it->second;
    }
    throw ManagerException("Object with ID " + id.getUuidString() + " not found.");
}

void ObjectManager::clearObjects()
{
    _objects.clear();
}

void ObjectManager::duplicateObject(const UUID& id)
{
    auto it = _objects.find(id);
    if (it != _objects.end()) {
        IObject *newObject = it->second->clone();
        UUID newId = UUID(id);
        newId.generateUuid();
        addObject(newId, newObject);
    } else {
        throw ManagerException("Object with ID " + id.getUuidString() + " not found.");
    }
}

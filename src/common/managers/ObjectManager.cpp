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

bool ObjectManager::objectExists(const UUID& uuid) const
{
    return _objects.find(uuid) != _objects.end();
}

void ObjectManager::addObject(const UUID& uuid, IObject *object)
{
    if (_objects.find(uuid) != _objects.end()) {
        throw ManagerException("Object with UUID " + uuid.getUuidString() + " already exists: overwriting.");
    }
    _objects[uuid] = object;
}

void ObjectManager::addObjects(const std::unordered_map<UUID, IObject *>& objects)
{
    for (const auto& object : objects) {
        addObject(object.first, object.second);
    }
}

void ObjectManager::removeObject(const UUID& uuid)
{
    if (_objects.erase(uuid) == 0) {
        throw ManagerException("Object with UUID " + uuid.getUuidString() + " does not exist.");
    }
}

void ObjectManager::removeObjects(const std::vector<UUID>& uuids)
{
    for (const auto& uuid : uuids) {
        removeObject(uuid);
    }
}

void ObjectManager::updateObject(const UUID& uuid, IObject *updatedObject)
{
    if (!objectExists(uuid)) {
        throw ManagerException("Object with UUID " + uuid.getUuidString() + " does not exist, creating a new one.");
    }
    _objects[uuid] = updatedObject;
}

IObject *ObjectManager::getObjectById(const UUID& uuid) const
{
    auto it = _objects.find(uuid);
    if (it != _objects.end()) {
        return it->second;
    }
    throw ManagerException("Object with UUID " + uuid.getUuidString() + " not found.");
}

void ObjectManager::clearObjects()
{
    _objects.clear();
}

void ObjectManager::duplicateObject(const UUID& uuid)
{
    auto it = _objects.find(uuid);
    if (it != _objects.end()) {
        IObject *newObject = it->second->clone();
        UUID newId = UUID(uuid);
        newId.generateUuid();
        addObject(newId, newObject);
    } else {
        throw ManagerException("Object with UUID " + uuid.getUuidString() + " not found.");
    }
}

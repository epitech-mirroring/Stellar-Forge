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

/*bool ObjectManager::objectExists(IObject object) const
{
    for (const auto& obj : _objects) {
        if (obj.second == object) {
            return true;
        }
    }
    return false;
}*/

void ObjectManager::addObject(const UUID& id, IObject *object)
{
    if (_objects.find(id) != _objects.end()) {
        //raise Warning Object with ID id already exists: overwriting
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
        //raise Warning Object with ID id does not exist
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
        //raise Warning Object does not exist, creating a new
    }
    _objects[id] = updatedObject;
}

IObject *ObjectManager::getObjectById(const UUID& id) const
{
    auto it = _objects.find(id);
    if (it != _objects.end()) {
        return it->second;
    }
    //raise Eroor Object not found
    return nullptr;
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
        //raise Error Object not found
    }
}

/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** ObjectManager.cpp
*/

#include "ObjectManager.hpp"

std::unordered_map<long, IObject *> ObjectManager::getObjects() const
{
    return _objects;
}

size_t ObjectManager::getObjectCount() const
{
    return _objects.size();
}

bool ObjectManager::objectExists(const long& id) const
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

void ObjectManager::addObject(const long& id, IObject *object)
{
    if (_objects.find(id) != _objects.end()) {
        //raise Warning Object with ID id already exists: overwriting
    }
    _objects[id] = object;
}

void ObjectManager::addObjects(const std::unordered_map<long, IObject *>& objects)
{
    for (const auto& object : objects) {
        addObject(object.first, object.second);
    }
}

void ObjectManager::removeObject(const long& id)
{
    if (_objects.erase(id) == 0) {
        //raise Warning Object with ID id does not exist
    }
}

void ObjectManager::removeObjects(const std::vector<long>& ids)
{
    for (const auto& id : ids) {
        removeObject(id);
    }
}

void ObjectManager::updateObject(const long& id, IObject *updatedObject)
{
    if (!objectExists(id)) {
        //raise Warning Object does not exist, creating a new
    }
    _objects[id] = updatedObject;
}

IObject *ObjectManager::getObjectById(const long& id) const
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

void ObjectManager::duplicateObject(const long& id)
{
    auto it = _objects.find(id);
    if (it != _objects.end()) {
        long newId = id + 1;

        while (_objects.find(newId) != _objects.end()) {
            newId++;
        }

        _objects[newId] = it->second;
    } else {
        //raise Eroor Object not found
    }
}

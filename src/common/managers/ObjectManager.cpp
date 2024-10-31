/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** ObjectManager.cpp
*/

#include "ObjectManager.hpp"
#include "ManagerException.hpp"
#include "SceneManager.hpp"

ObjectManager &ObjectManager::getInstance() {
    static ObjectManager instance;
    return instance;
}

std::unordered_map<UUID, IObject *> ObjectManager::getObjects() const {
    return _objects;
}

size_t ObjectManager::getObjectCount() const {
    return _objects.size();
}

bool ObjectManager::objectExists(const UUID &uuid) const {
    return _objects.find(uuid) != _objects.end();
}

void ObjectManager::addObject(const UUID &uuid, IObject *object) {
    if (objectExists(uuid)) {
        throw ManagerException(
            "Object with UUID " + uuid.getUuidString() +
            " already exists: overwriting.");
    }
    _objects[uuid] = object;
}

void ObjectManager::addObject(IObject *object) {
    UUID uuid;
    uuid.generateUuid();
    addObject(uuid, object);
}

void ObjectManager::addObjects(
    const std::unordered_map<UUID, IObject *> &objects) {
    for (const auto &[uuid, object_ptr]: objects) {
        addObject(uuid, object_ptr);
    }
}

void ObjectManager::addObjects(const std::vector<IObject *> &objects) {
    for (const auto &object: objects) {
        addObject(object);
    }
}

void ObjectManager::removeObject(const UUID &uuid) {
    if (!this->objectExists(uuid)) {
        throw ManagerException(
            "Object with UUID " + uuid.getUuidString() + " not found.");
    }
    _objects.erase(uuid);
}

void ObjectManager::removeObjects(const std::vector<UUID> &uuids) {
    for (const auto &uuid: uuids) {
        removeObject(uuid);
    }
}

void ObjectManager::updateObject(const UUID &uuid, IObject *updatedObject) {
    if (!objectExists(uuid)) {
        throw ManagerException(
            "Object with UUID " + uuid.getUuidString() +
            " does not exist, creating a new one.");
    }
    _objects[uuid] = updatedObject;
}

IObject *ObjectManager::getObjectById(const UUID &uuid) const {
    if (!this->objectExists(uuid)) {
        return nullptr;
    }
    return _objects.at(uuid);
}

void ObjectManager::clearObjects() {
    _objects.clear();
}

UUID ObjectManager::duplicateObject(const UUID &uuid) {
    const auto object = _objects.find(uuid);
    if (object != _objects.end()) {
        IObject *newObject = object->second->clone();
        auto newId = UUID(uuid);
        newId.generateUuid();
        addObject(newId, newObject);
        SceneManager::getInstance().getCurrentScene()->addObject(newObject);
        return newId;
    }
    throw ManagerException(
        "Object with UUID " + uuid.getUuidString() + " not found.");
}

void ObjectManager::clearInstance() {
    _objects.clear();
}

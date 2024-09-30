/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** ObjectManager.hpp
*/

#pragma once

#include <unordered_map>
#include <vector>
#include <stdexcept>
#include "../IObject.hpp"
#include "../UUID.hpp"
#include "ManagerException.hpp"

class ObjectManager {
public:
    ObjectManager() = default;
    ~ObjectManager() = default;

    std::unordered_map<UUID, IObject *> getObjects() const;
    size_t getObjectCount() const;
    bool objectExists(const UUID& id) const;
    void addObject(const UUID& id, IObject *object);
    void addObjects(const std::unordered_map<UUID, IObject *>& objects);
    void removeObject(const UUID& id);
    void removeObjects(const std::vector<UUID>& ids);
    void updateObject(const UUID& id, IObject *updatedObject);
    IObject *getObjectById(const UUID& id) const;
    void clearObjects();
    void duplicateObject(const UUID& id);
    
private:
    std::unordered_map<UUID, IObject *> _objects;
};

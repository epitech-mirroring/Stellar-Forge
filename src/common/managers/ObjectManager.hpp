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

// assuming ids are unique and are UUIDs

class ObjectManager {
public:
    ObjectManager() = default;
    ~ObjectManager() = default;

    std::unordered_map<UUID, IObject *> getObjects() const;
    size_t getObjectCount() const;
    bool objectExists(const UUID& id) const;

    // if we implement a equals function for the object class.
    //bool objectExists(IObject object) const;

    // If the id is in the object, change the function signature to:
    // void addObject(IObject object);
    // same for the following functions
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

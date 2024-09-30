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
#include "../common/IObject.hpp"

// assuming ids are unique and are longs

class ObjectManager {
public:
    ObjectManager() = default;
    ~ObjectManager() = default;

    std::unordered_map<long, IObject *> getObjects() const;
    size_t getObjectCount() const;
    bool objectExists(const long& id) const;

    // if we implement a equals function for the object class.
    //bool objectExists(IObject object) const;

    // If the id is in the object, change the function signature to:
    // void addObject(IObject object);
    // same for the following functions
    void addObject(const long& id, IObject *object);
    void addObjects(const std::unordered_map<long, IObject *>& objects);
    void removeObject(const long& id);
    void removeObjects(const std::vector<long>& ids);
    void updateObject(const long& id, IObject *updatedObject);
    IObject *getObjectById(const long& id) const;
    void clearObjects();
    void duplicateObject(const long& id);
    
private:
    std::unordered_map<long, IObject *> _objects;
};

/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** ObjectManager.hpp
*/

#pragma once

#include <string>
#include <unordered_map>
#include <memory>

// assuming ids are unique and are longs + objects are void pointers

class ObjectManager {
public:
    ObjectManager() = default;
    ~ObjectManager() = default;

    std::unordered_map<long, void *> getObjects() const;
    size_t getObjectCount() const;
    bool objectExists(const long& id) const;

    // if we implement a equals function for the object class.
    //bool objectExists(void * object) const;

    // If the id is in the object, change the function signature to:
    // void addObject(void * object);
    // same for the following functions
    void addObject(const long& id, void * object);
    void addObjects(const std::unordered_map<long, void *>& objects);
    void removeObject(const long& id);
    void removeObjects(const std::vector<long>& ids);
    void updateObject(const long& id, void * updatedObject);
    void * getObjectById(const long& id) const;
    void clearObjects();
    void duplicateObject(const long& id);
    
private:
    std::unordered_map<long, void *> _objects;
};

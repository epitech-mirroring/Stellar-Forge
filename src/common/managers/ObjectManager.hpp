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

/**
 * @class ObjectManager
 * @brief Manages objects in the StellarForge engine.
 * @details This class provides an interface for managing multiple objects, including adding, removing, and updating them.
 * @version v0.1.0
 * @since v0.1.0
 * @author Aubane NOURRY
 */
class ObjectManager {
public:
    /**
     * @brief Default constructor for ObjectManager.
     * @version v0.1.0
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    ObjectManager() = default;

    /**
     * @brief Destructor for ObjectManager.
     * @version v0.1.0
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    ~ObjectManager() = default;

    /**
     * @brief Retrieves all objects managed by the ObjectManager.
     * @return An unordered map of UUIDs to object pointers.
     * @version v0.1.0
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    std::unordered_map<UUID, IObject *> getObjects() const;

    /**
     * @brief Gets the total count of objects.
     * @return The number of objects managed by the ObjectManager.
     * @version v0.1.0
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    size_t getObjectCount() const;

    /**
     * @brief Checks if an object exists in the manager.
     * @param uuid The unique identifier of the object.
     * @return True if the object exists, false otherwise.
     * @version v0.1.0
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    bool objectExists(const UUID& uuid) const;

    /**
     * @brief Adds an object to the manager.
     * @param uuid The unique identifier of the object.
     * @param object The object to be added.
     * @version v0.1.0
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    void addObject(const UUID& id, IObject *object);

    /**
     * @brief Adds multiple objects to the manager.
     * @param objects An unordered map of UUIDs to object pointers.
     * @version v0.1.0
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    void addObjects(const std::unordered_map<UUID, IObject *>& objects);

    /**
     * @brief Removes an object from the manager.
     * @param uuid The unique identifier of the object to remove.
     * @version v0.1.0
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    void removeObject(const UUID& uuid);

    /**
     * @brief Removes multiple objects from the manager.
     * @param uuids A vector of UUIDs representing the objects to remove.
     * @version v0.1.0
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    void removeObjects(const std::vector<UUID>& uuids);

    /**
     * @brief Updates an object in the manager.
     * @param uuid The unique identifier of the object.
     * @param updatedObject The updated object.
     * @version v0.1.0
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    void updateObject(const UUID& uuid, IObject *updatedObject);

    /**
     * @brief Retrieves an object by its unique identifier.
     * @param uuid The unique identifier of the object.
     * @return A pointer to the object.
     * @version v0.1.0
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    IObject *getObjectById(const UUID& uuid) const;

    /**
     * @brief Clears all objects managed by the ObjectManager.
     * @version v0.1.0
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    void clearObjects();

    /**
     * @brief Duplicates an object within the manager.
     * @param uuid The unique identifier of the object to duplicate.
     * @version v0.1.0
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    void duplicateObject(const UUID& uuid);

private:
    std::unordered_map<UUID, IObject *> _objects;  ///< Unordered map of UUIDs to objects.
};

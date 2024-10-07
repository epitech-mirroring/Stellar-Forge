/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#ifndef STELLARFORGE_COLLIDER_HPP
#define STELLARFORGE_COLLIDER_HPP

#include <glm/glm.hpp>

using Vector3 = glm::vec3;

/**
 * @class ICollider
 * @brief Interface for colliders in the physics system.
 * @version v0.1.0
 * @since v0.1.0
 * @details This interface defines the basic structure for colliders, including a method to check for collisions.
 * @author Landry GIGANT
 */
class ICollider {
public:
    /**
     * @brief Virtual destructor for the ICollider interface.
     * @version v0.1.0
     * @since v0.1.0
     * @author Landry GIGANT
     */
    virtual ~ICollider() = default;

    /**
     * @brief Check if this collider collides with another collider.
     * @param collider Pointer to the other collider.
     * @return True if the colliders collide, false otherwise.
     * @version v0.1.0
     * @since v0.1.0
     * @author Landry GIGANT
     */
    virtual bool Collide(ICollider *collider) = 0;
};

/**
* @class Box
* @brief A class that represents a box in 3D space.
* @details This class contains the position and size of the box.
* @version v0.1.0
* @since v0.1.0
* @author Landry GIGANT
*/
class Box : public ICollider {
public:
    /**
     * @brief The position of the box in 3D space.
     */
    Vector3 position;

    /**
     * @brief The size of the box in 3D space.
     */
    Vector3 size;

    /**
     * @brief Constructor for the Box class.
     * @param position The position of the box in 3D space.
     * @param size The size of the box in 3D space.
     */
    Box(Vector3 position, Vector3 size) : position(position), size(size) {};

    /**
     * @brief Check if the box collides with another collider.
     * @param collider The collider to check for collision.
     * @return True if the box collides with the collider, false otherwise.
     */
    bool Collide(ICollider *collider) override;
};

/**
 * @class Sphere
 * @brief A class that represents a sphere in 3D space.
 * @details This class contains the position and radius of the sphere.
 * @version v0.1.0
 * @since v0.1.0
 * @author Landry GIGANT
 */
class Sphere : public ICollider {
public:
    /**
     * @brief The position of the sphere in 3D space.
     */
    Vector3 position;

    /**
     * @brief The radius of the sphere.
     */
    float radius;

    /**
     * @brief Constructor for the Sphere class.
     * @param position The position of the sphere in 3D space.
     * @param radius The radius of the sphere.
     */
    Sphere(Vector3 position, float radius) : position(position), radius(radius) {};

    /**
     * @brief Check if the sphere collides with another collider.
     * @param collider The collider to check for collision.
     * @return True if the sphere collides with the collider, false otherwise.
     */
    bool Collide(ICollider *collider) override;
};

#endif //STELLARFORGE_COLLIDER_HPP

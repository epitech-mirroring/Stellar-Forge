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
     * @brief Set the position of the collider.
     * @param position
     * @version v0.1.0
     * @since v0.1.0
     * @author Landry GIGANT
     */
    virtual void setPosition(Vector3 position) = 0;

    /**
     * @brief Get the position of the collider.
     * @return The position of the collider.
     * @version v0.1.0
     * @since v0.1.0
     * @author Landry GIGANT
     */
    [[nodiscard]] virtual Vector3 getPosition() const = 0;

    /**
     * @brief Set the relative position of the collider.
     * @param position
     * @version v0.1.0
     * @since v0.1.0
     * @author Landry GIGANT
     */
    virtual void setRelativePosition(Vector3 position) = 0;

    /**
     * @brief Get the relative position of the collider.
     * @return The relative position of the collider.
     * @version v0.1.0
     * @since v0.1.0
     * @author Landry GIGANT
     */
    [[nodiscard]] virtual Vector3 getRelativePosition() const = 0;

    /**
     * @brief Check if this collider collides with another collider.
     * @param collider Pointer to the other collider.
     * @return True if the colliders collide, false otherwise.
     * @version v0.1.0
     * @since v0.1.0
     * @author Landry GIGANT
     */
    virtual bool collide(ICollider *collider) = 0;

    /**
     * @brief Scale the collider by a factor.
     * @param scale The factor to scale the collider by.
     * @version v0.1.0
     * @since v0.1.0
     * @author Landry GIGANT
     */
    virtual void scale(float scale) = 0;
};

#endif //STELLARFORGE_COLLIDER_HPP

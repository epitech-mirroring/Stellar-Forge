/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
** Author: landry GIGANT
*/

#ifndef STELLARFORGE_RIGIDBODY_HPP
#define STELLARFORGE_RIGIDBODY_HPP

#include "../AComponent.hpp"
#include "../AMeta.hpp"
#include <glm/vec3.hpp>

using Vector3 = glm::vec3;

/**
 * @class RigidBody
 * @brief Represents a rigid body component in the physics system.
 * @version v0.1.0
 * @since v0.1.0
 * @author landry GIGANT
 */
class RigidBody : public AComponent {
private:
    Vector3 _velocity; ///< The velocity of the rigid body.
    Vector3 _acceleration; ///< The acceleration of the rigid body.
    float _terminalVelocity; ///< The terminal velocity of the rigid body.
    float _drag; ///< The drag coefficient of the rigid body.

public:
    /**
     * @class RigidBodyMeta
     * @brief Metadata class for the RigidBody component.
     * @version v0.1.0
     * @since v0.1.0
     * @author landry GIGANT
     */
    class RigidBodyMeta : public AMeta {
    public:
        /**
         * @brief Constructor for RigidBodyMeta.
         * @version v0.1.0
         * @since v0.1.0
         * @author landry GIGANT
         */
        RigidBodyMeta();
    };

    /**
     * @brief Constructor for RigidBody.
     * @param owner Pointer to the owner object.
     * @version v0.1.0
     * @since v0.1.0
     * @author landry GIGANT
     */
    RigidBody(IObject *owner);

    /**
     * @brief Destructor for RigidBody.
     * @version v0.1.0
     * @since v0.1.0
     * @author landry GIGANT
     */
    ~RigidBody() override = default;

    /**
     * @brief Applies movement to the rigid body based on its velocity and the elapsed time.
     * @param deltaTime The elapsed time since the last update.
     * @version v0.1.0
     * @since v0.1.0
     * @author landry GIGANT
     */
    void applyMovement(const float deltaTime);

    /**
     * @brief Applies drag to the rigid body based on its drag coefficient and the elapsed time.
     * @param deltaTime The elapsed time since the last update.
     * @version v0.1.0
     * @since v0.1.0
     * @author landry GIGANT
     */
    void applyDrag(const float deltaTime);

    /**
     * @brief Applies a force to the rigid body based on its acceleration and the elapsed time.
     * @param deltaTime The elapsed time since the last update.
     * @version v0.1.0
     * @since v0.1.0
     * @author landry GIGANT
     */
    void applyForce(const float deltaTime);

    /**
     * @brief Applies an impulse to the rigid body.
     * @param impulse The impulse vector to be applied.
     * @version v0.1.0
     * @since v0.1.0
     * @author landry GIGANT
     */
    void applyImpulse(const Vector3 &impulse);
};

#endif //STELLARFORGE_RIGIDBODY_HPP
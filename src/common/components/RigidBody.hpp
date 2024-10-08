/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#ifndef STELLARFORGE_RIGIDBODY_HPP
#define STELLARFORGE_RIGIDBODY_HPP

#include "../AComponent.hpp"
#include "../AMeta.hpp"
#include <glm/vec3.hpp>

using Vector3 = glm::vec3;

class RigidBody : public AComponent {
private:
    Vector3 _velocity;
    Vector3 _acceleration;
    float _terminalVelocity;
    float _drag;

public:

    class RigidBodyMeta : public AMeta {
    public:
        RigidBodyMeta();
    };

    RigidBody(IObject *owner);
    ~RigidBody() override = default;

    void applyMovement(const float deltaTime);
    void applyDrag(const float deltaTime);
    void applyForce(const float deltaTime);
    void applyImpulse(const Vector3 &impulse);
};

#endif //STELLARFORGE_RIGIDBODY_HPP

/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Physics.hpp"
#include <glm/geometric.hpp>

void Physics::Movement::applyMovement(Vector3 &pos, const Vector3 &vel,
                                      const float deltaTime) {
    pos += vel * deltaTime;
}

void Physics::Movement::applyMovement(Vector3 &pos, Vector3 &vel,
                                      const Vector3 &acc,
                                      const float deltaTime) {
    pos += vel * deltaTime + 0.5f * acc * deltaTime * deltaTime;

    vel += acc * deltaTime;
}

void Physics::Movement::applyMovement(Vector3 &pos, Vector3 &vel,
                                      const Vector3 &acc,
                                      const float terminalVelocity,
                                      const float deltaTime) {
    pos += vel * deltaTime + 0.5f * acc * deltaTime * deltaTime;

    vel += acc * deltaTime;

    const float distance = length(vel);

    if (distance > terminalVelocity) {
        vel *= terminalVelocity / distance;
    }
}

void Physics::Movement::applyDrag(Vector3 &vel, const float drag,
                                  const float deltaTime) {
    const float distance = length(vel);

    if (distance > drag * deltaTime) {
        vel -= vel * drag * deltaTime / distance;
    } else {
        vel = {0, 0, 0};
    }
}

void Physics::Movement::applyForce(Vector3 &vel, const Vector3 &force,
                                   const float deltaTime) {
    vel += force * deltaTime;
}

void Physics::Movement::applyImpulse(Vector3 &vel, const Vector3 &impulse) {
    vel += impulse;
}

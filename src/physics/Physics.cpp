/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Physics.hpp"

void Physics::Movement::applyMovement(Vector3 &pos, Vector3 &vel, float deltaTime)
{
    pos += vel * deltaTime;
}

void Physics::Movement::applyMovement(Vector3 &pos, Vector3 &vel, Vector3 &acc, float deltaTime)
{
    pos += vel * deltaTime + 0.5f * acc * deltaTime * deltaTime;

    vel += acc * deltaTime;
}

void Physics::Movement::applyMovement(Vector3 &pos, Vector3 &vel, Vector3 &acc, float terminalVelocity, float deltaTime)
{
    pos += vel * deltaTime + 0.5f * acc * deltaTime * deltaTime;

    vel += acc * deltaTime;

    float distance = glm::length(vel);
    if (distance > terminalVelocity) {
        vel *= terminalVelocity / distance;
    }
}

void Physics::Movement::applyDrag(Vector3 &vel, float drag, float deltaTime)
{
    float distance = glm::length(vel);
    if (distance > drag * deltaTime) {
        vel -= vel * drag * deltaTime / distance;
    } else {
        vel = {0, 0, 0};
    }
}

void Physics::Movement::applyForce(Vector3 &vel, Vector3 &force, float deltaTime)
{
    vel += force * deltaTime;
}

void Physics::Movement::applyImpulse(Vector3 &vel, Vector3 &impulse)
{
    vel += impulse;
}

/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Physics.hpp"
#include <cmath>

void Physics::Movement::applyMovement(Vector3f &pos, Vector3f &vel, float deltaTime)
{
    pos += vel * deltaTime;
}

void Physics::Movement::applyMovement(Vector3f &pos, Vector3f &vel, Vector3f &acc, float deltaTime)
{
    pos += vel * deltaTime + acc * 0.5 * deltaTime * deltaTime;

    vel += acc * deltaTime;
}

void Physics::Movement::applyMovement(Vector3f &pos, Vector3f &vel, Vector3f &acc, float terminalVelocity, float deltaTime)
{
    pos += vel * deltaTime + acc * 0.5 * deltaTime * deltaTime;

    vel += acc * deltaTime;

    float distance = vel.length();
    if (distance > terminalVelocity) {
        vel *= terminalVelocity / distance;
    }
}

void Physics::Movement::applyDrag(Vector3f &vel, float drag, float deltaTime)
{
    float distance = vel.length();
    if (distance > drag * deltaTime) {
        vel -= vel * drag * deltaTime / distance;
    } else {
        vel = {0, 0, 0};
    }
}

void Physics::Movement::applyForce(Vector3f &vel, Vector3f &force, float deltaTime)
{
    vel += force * deltaTime;
}

void Physics::Movement::applyImpulse(Vector3f &vel, Vector3f &impulse)
{
    vel += impulse;
}

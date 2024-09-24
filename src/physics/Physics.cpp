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
    pos.x += vel.x * deltaTime;
    pos.y += vel.y * deltaTime;
    pos.z += vel.z * deltaTime;
}

void Physics::Movement::applyMovement(Vector3f &pos, Vector3f &vel, Vector3f &acc, float deltaTime)
{
    pos.x += vel.x * deltaTime + 0.5 * acc.x * deltaTime * deltaTime;
    pos.y += vel.y * deltaTime + 0.5 * acc.y * deltaTime * deltaTime;
    pos.z += vel.z * deltaTime + 0.5 * acc.z * deltaTime * deltaTime;

    vel.x += acc.x * deltaTime;
    vel.y += acc.y * deltaTime;
    vel.z += acc.z * deltaTime;
}

void Physics::Movement::applyMovement(Vector3f &pos, Vector3f &vel, Vector3f &acc, float terminalVelocity, float deltaTime)
{
    pos.x += vel.x * deltaTime + 0.5 * acc.x * deltaTime * deltaTime;
    pos.y += vel.y * deltaTime + 0.5 * acc.y * deltaTime * deltaTime;
    pos.z += vel.z * deltaTime + 0.5 * acc.z * deltaTime * deltaTime;

    vel.x += acc.x * deltaTime;
    vel.y += acc.y * deltaTime;
    vel.z += acc.z * deltaTime;

    float distance = sqrt(vel.x * vel.x + vel.y * vel.y + vel.z * vel.z);
    if (distance > terminalVelocity) {
        vel.x = vel.x * terminalVelocity / distance;
        vel.y = vel.y * terminalVelocity / distance;
        vel.z = vel.z * terminalVelocity / distance;
    }
}

void Physics::Movement::applyDrag(Vector3f &vel, float drag, float deltaTime)
{
    float distance = sqrt(vel.x * vel.x + vel.y * vel.y + vel.z * vel.z);
    if (distance > drag * deltaTime) {
        vel.x -= drag * deltaTime * vel.x / distance;
        vel.y -= drag * deltaTime * vel.y / distance;
        vel.z -= drag * deltaTime * vel.z / distance;
    } else {
        vel.x = 0;
        vel.y = 0;
        vel.z = 0;
    }
}

void Physics::Movement::applyForce(Vector3f &vel, Vector3f &force, float deltaTime)
{
    vel.x += force.x * deltaTime;
    vel.y += force.y * deltaTime;
    vel.z += force.z * deltaTime;
}

void Physics::Movement::applyImpulse(Vector3f &vel, Vector3f &impulse)
{
    vel.x += impulse.x;
    vel.y += impulse.y;
    vel.z += impulse.z;
}

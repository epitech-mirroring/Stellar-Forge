/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Physics.hpp"
#include "glm/geometric.hpp"

void Physics::Movement::applyMovement(Vector3 &pos, Vector3 &vel, float deltaTime)
{
    pos += vel * deltaTime;
}
bool Physics::Collision::BoxVsBox(Box box1, Box box2) {
    return (box1.position.x < box2.position.x + box2.size.x &&
            box1.position.x + box1.size.x > box2.position.x &&
            box1.position.y < box2.position.y + box2.size.y &&
            box1.position.y + box1.size.y > box2.position.y &&
            box1.position.z < box2.position.z + box2.size.z &&
            box1.position.z + box1.size.z > box2.position.z);
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

    const float distance = glm::length(vel);

    if (distance > terminalVelocity) {
        vel *= terminalVelocity / distance;
    }
}

void Physics::Movement::applyDrag(Vector3 &vel, float drag, float deltaTime)
{
    const float distance = glm::length(vel);

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

bool Physics::Collision::SphereVsSphere(Sphere sphere1, Sphere sphere2) {
    return glm::distance(sphere1.position, sphere2.position) < sphere1.radius + sphere2.radius;
}

bool Physics::Collision::BoxVsSphere(Box box, Sphere sphere) {
    Vector3 closestPoint = glm::vec3(
            glm::clamp(sphere.position.x, std::min(box.position.x, box.position.x + box.size.x),
                       std::max(box.position.x, box.position.x + box.size.x)),
            glm::clamp(sphere.position.y, std::min(box.position.y, box.position.y + box.size.y),
                       std::max(box.position.y, box.position.y + box.size.y)),
            glm::clamp(sphere.position.z, std::min(box.position.z, box.position.z + box.size.z),
                       std::max(box.position.z, box.position.z + box.size.z))
    );
    return glm::distance(sphere.position, closestPoint) < sphere.radius;
}
bool Physics::Collision::SphereVsBox(Sphere sphere, Box box) {
    return BoxVsSphere(box, sphere);
}

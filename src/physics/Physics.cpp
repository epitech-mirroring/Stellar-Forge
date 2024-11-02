/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Physics.hpp"
#include <algorithm>
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

    if (terminalVelocity != 0 && distance > terminalVelocity) {
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

bool Physics::Collision::boxCollideBox(const Box &box1, const Box &box2)
{
    const Vector3 box1RelativePosition = box1.relativePosition + box1.position;
    const Vector3 box2RelativePosition = box2.relativePosition + box2.position;
    const Vector3 box1Min = box1RelativePosition;
    const Vector3 box1Max = box1RelativePosition + box1.size;
    const Vector3 box2Min = box2RelativePosition;
    const Vector3 box2Max = box2RelativePosition + box2.size;
    return (std::min(box1Min.x, box1Max.x) <= std::max(box2Min.x, box2Max.x) &&
            std::max(box1Min.x, box1Max.x) >= std::min(box2Min.x, box2Max.x) &&
            std::min(box1Min.y, box1Max.y) <= std::max(box2Min.y, box2Max.y) &&
            std::max(box1Min.y, box1Max.y) >= std::min(box2Min.y, box2Max.y) &&
            std::min(box1Min.z, box1Max.z) <= std::max(box2Min.z, box2Max.z) &&
            std::max(box1Min.z, box1Max.z) >= std::min(box2Min.z, box2Max.z));
}

bool Physics::Collision::sphereCollideSphere(const Sphere &sphere1, const Sphere &sphere2)
{
    return glm::distance(sphere1.position, sphere2.position) < sphere1.radius + sphere2.radius;
}

bool Physics::Collision::boxCollideSphere(const Box &box, const Sphere &sphere)
{
    const Vector3 boxRelativePosition = box.relativePosition + box.position;
    const Vector3 boxMin = boxRelativePosition;
    const Vector3 boxMax = boxRelativePosition + box.size;
    const Vector3 sphereRelativePosition = sphere.relativePosition + sphere.position;
    const Vector3 closestPoint = glm::vec3 (
            glm::clamp(sphereRelativePosition.x, std::min(boxMin.x, boxMax.x), std::max(boxMin.x, boxMax.x)),
            glm::clamp(sphereRelativePosition.y, std::min(boxMin.y, boxMax.y), std::max(boxMin.y, boxMax.y)),
            glm::clamp(sphereRelativePosition.z, std::min(boxMin.z, boxMax.z), std::max(boxMin.z, boxMax.z))
    );
    return glm::distance(sphereRelativePosition, closestPoint) < sphere.radius;
}

bool Physics::Collision::sphereCollideBox(const Sphere &sphere, const Box &box)
{
    return boxCollideSphere(box, sphere);
}

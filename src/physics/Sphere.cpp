/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#include "Sphere.hpp"
#include "Box.hpp"
#include "Physics.hpp"

Sphere::Sphere(Vector3 position, float radius) : relativePosition(position), radius(radius), position(0, 0, 0)
{
}

void Sphere::setPosition(Vector3 position) {
    this->position = position;
}

[[nodiscard]] Vector3 Sphere::getPosition() const {
    return position;
}

void Sphere::setRelativePosition(Vector3 RelativePosition) {
    this->relativePosition = RelativePosition;
}

[[nodiscard]] Vector3 Sphere::getRelativePosition() const {
    return relativePosition;
}

bool Sphere::collide(ICollider *collider) {
    if (dynamic_cast<Sphere *>(collider) != nullptr) {
        return Physics::Collision::sphereCollideSphere(*this, *dynamic_cast<Sphere *>(collider));
    } else if (dynamic_cast<Box *>(collider) != nullptr) {
        return Physics::Collision::sphereCollideBox(*this, *dynamic_cast<Box *>(collider));
    }
    return false;
}

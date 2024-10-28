/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#include "Sphere.hpp"
#include "Box.hpp"
#include "Physics.hpp"

Box::Box(Vector3 position, Vector3 size) : relativePosition(position), size(size), position(0, 0, 0)
{
}

void Box::setPosition(Vector3 position) {
    this->position = position;
}

[[nodiscard]] Vector3 Box::getPosition() const {
    return position;
}

void Box::setRelativePosition(Vector3 RelativePosition) {
    this->relativePosition = RelativePosition;
}

[[nodiscard]] Vector3 Box::getRelativePosition() const {
    return relativePosition;
}

bool Box::collide(ICollider *collider) {
    if (dynamic_cast<Box *>(collider) != nullptr) {
        return Physics::Collision::boxCollideBox(*this, *dynamic_cast<Box *>(collider));
    } else if (dynamic_cast<Sphere *>(collider) != nullptr) {
        return Physics::Collision::boxCollideSphere(*this, *dynamic_cast<Sphere *>(collider));
    }
    return false;
}

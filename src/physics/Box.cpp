/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#include "Sphere.hpp"
#include "Box.hpp"
#include "Physics.hpp"

Box::Box(const Vector3 position, const Vector3 size) : position(position), size(size) {
}

bool Box::collide(ICollider *collider) {
    if (dynamic_cast<Box *>(collider) != nullptr) {
        return Physics::Collision::boxCollideBox(*this, *dynamic_cast<Box *>(collider));
    }
    if (dynamic_cast<Sphere *>(collider) != nullptr) {
        return Physics::Collision::boxCollideSphere(
            *this, *dynamic_cast<Sphere *>(collider));
    }
    return false;
}

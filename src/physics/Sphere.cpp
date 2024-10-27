/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#include "Sphere.hpp"
#include "Box.hpp"
#include "Physics.hpp"

Sphere::Sphere(const Vector3 position, const float radius) : position(position),
    radius(radius) {
}

bool Sphere::collide(ICollider *collider) {
    if (dynamic_cast<Sphere *>(collider) != nullptr) {
        return Physics::Collision::sphereCollideSphere(
            *this, *dynamic_cast<Sphere *>(collider));
    }
    if (dynamic_cast<Box *>(collider) != nullptr) {
        return Physics::Collision::sphereCollideBox(
            *this, *dynamic_cast<Box *>(collider));
    }
    return false;
}

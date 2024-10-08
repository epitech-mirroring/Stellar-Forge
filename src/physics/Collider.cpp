/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#include "Collider.hpp"
#include "Physics.hpp"

bool Box::Collide(ICollider *collider) {
    if (dynamic_cast<Box *>(collider) != nullptr) {
        return Physics::Collision::BoxCollideBox(*this, *dynamic_cast<Box *>(collider));
    } else if (dynamic_cast<Sphere *>(collider) != nullptr) {
        return Physics::Collision::BoxCollideSphere(*this, *dynamic_cast<Sphere *>(collider));
    }
    return false;
}

bool Sphere::Collide(ICollider *collider) {
    if (dynamic_cast<Sphere *>(collider) != nullptr) {
        return Physics::Collision::SphereCollideSphere(*this, *dynamic_cast<Sphere *>(collider));
    } else if (dynamic_cast<Box *>(collider) != nullptr) {
        return Physics::Collision::SphereCollideBox(*this, *dynamic_cast<Box *>(collider));
    }
    return false;
}

/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#include "Sphere.hpp"
#include "Box.hpp"
#include "Physics.hpp"

bool Box::collide(ICollider *collider) {
    if (dynamic_cast<Box *>(collider) != nullptr) {
        return Physics::Collision::BoxCollideBox(*this, *dynamic_cast<Box *>(collider));
    } else if (dynamic_cast<Sphere *>(collider) != nullptr) {
        return Physics::Collision::BoxCollideSphere(*this, *dynamic_cast<Sphere *>(collider));
    }
    return false;
}

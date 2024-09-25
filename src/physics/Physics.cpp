/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Physics.hpp"

bool Physics::Collision::BoxVsBox(Box box1, Box box2) {
    return (box1.position.x < box2.position.x + box2.size.x &&
            box1.position.x + box1.size.x > box2.position.x &&
            box1.position.y < box2.position.y + box2.size.y &&
            box1.position.y + box1.size.y > box2.position.y &&
            box1.position.z < box2.position.z + box2.size.z &&
            box1.position.z + box1.size.z > box2.position.z);
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

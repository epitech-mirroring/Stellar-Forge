/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#ifndef PHYSICS_HPP
#define PHYSICS_HPP



#include "glm/glm.hpp"

class Physics {
public:

    using Vector3 = glm::vec3;

    class Box {
    public:
        Vector3 position;
        Vector3 size;

        Box(Vector3 position, Vector3 size) : position(position), size(size) {};
        ~Box() = default;
    };

    class Sphere {
    public:
        Vector3 position;
        float radius;

        Sphere(Vector3 position, float radius) : position(position), radius(radius) {};
        ~Sphere() = default;;
    };

    class Collision {
    public:
        static bool BoxVsBox(Box box1, Box box2);
        static bool SphereVsSphere(Sphere sphere1, Sphere sphere2);
        static bool BoxVsSphere(Box box, Sphere sphere);
        static bool SphereVsBox(Sphere sphere, Box box);
    };
};



#endif //PHYSICS_HPP

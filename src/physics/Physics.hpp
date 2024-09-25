/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#ifndef PHYSICS_HPP
#define PHYSICS_HPP



#include <glm/glm.hpp>

class Physics {
public:
    using Vector3 = glm::vec3;

    class Movement {
    public:
        static void applyMovement(Vector3 &pos, Vector3 &vel, float deltaTime);
        static void applyMovement(Vector3 &pos, Vector3 &vel, Vector3 &acc, float deltaTime);
        static void applyMovement(Vector3 &pos, Vector3 &vel, Vector3 &acc, float terminalVelocity, float deltaTime);

        static void applyDrag(Vector3 &vel, float drag, float deltaTime);

        static void applyForce(Vector3 &vel, Vector3 &force, float deltaTime);

        static void applyImpulse(Vector3 &vel, Vector3 &impulse);
    };
};



#endif //PHYSICS_HPP

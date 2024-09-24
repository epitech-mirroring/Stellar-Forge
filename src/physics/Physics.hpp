/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#ifndef PHYSICS_HPP
#define PHYSICS_HPP



#include "Math.hpp"

class Physics {
public:
    using Vector3f = Math::Vector3f;

    class Movement {
    public:
        static void applyMovement(Vector3f &pos, Vector3f &vel, float deltaTime);
        static void applyMovement(Vector3f &pos, Vector3f &vel, Vector3f &acc, float deltaTime);
        static void applyMovement(Vector3f &pos, Vector3f &vel, Vector3f &acc, float terminalVelocity, float deltaTime);

        static void applyDrag(Vector3f &vel, float drag, float deltaTime);

        static void applyForce(Vector3f &vel, Vector3f &force, float deltaTime);

        static void applyImpulse(Vector3f &vel, Vector3f &impulse);
    };
};



#endif //PHYSICS_HPP

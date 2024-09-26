/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#ifndef PHYSICS_HPP
#define PHYSICS_HPP


#include "glm/vec3.hpp"

/**
 * @class Physics
 * @brief A class that represents the physics of an object in a 3D space.
 */
class Physics {
public:
    /**
     * @typedef Vector3
     * @brief A type alias for glm::vec3, representing a 3D vector.
     */
    using Vector3 = glm::vec3;

    /**
     * @class Movement
     * @brief A nested class within Physics that provides static methods for applying physics principles.
     *
     * The methods in this class can be used to apply movement, drag, force, and impulse to an object.
     */
    class Movement {
    public:
        /**
         * @brief Apply movement to an object based on its current position, velocity, and a time delta.
         * @param pos The current position of the object.
         * @param vel The current velocity of the object.
         * @param deltaTime The time delta to apply.
         */
        static void applyMovement(Vector3 &pos, Vector3 &vel, float deltaTime);

        /**
         * @brief Apply movement to an object based on its current position, velocity, acceleration, and a time delta.
         * @param pos The current position of the object.
         * @param vel The current velocity of the object.
         * @param acc The current acceleration of the object.
         * @param deltaTime The time delta to apply.
         */
        static void applyMovement(Vector3 &pos, Vector3 &vel, Vector3 &acc, float deltaTime);

        /**
         * @brief Apply movement to an object based on its current position, velocity, acceleration, terminal velocity, and a time delta.
         * @param pos The current position of the object.
         * @param vel The current velocity of the object.
         * @param acc The current acceleration of the object.
         * @param terminalVelocity The terminal velocity of the object.
         * @param deltaTime The time delta to apply.
         */
        static void applyMovement(Vector3 &pos, Vector3 &vel, Vector3 &acc, float terminalVelocity, float deltaTime);

        /**
         * @brief Apply drag to an object based on its current velocity, a drag coefficient, and a time delta.
         * @param vel The current velocity of the object.
         * @param drag The drag coefficient to apply.
         * @param deltaTime The time delta to apply.
         */
        static void applyDrag(Vector3 &vel, float drag, float deltaTime);

        /**
         * @brief Apply a force to an object based on its current velocity, the force to apply, and a time delta.
         * @param vel The current velocity of the object.
         * @param force The force to apply.
         * @param deltaTime The time delta to apply.
         */
        static void applyForce(Vector3 &vel, Vector3 &force, float deltaTime);

        /**
         * @brief Apply an impulse to an object based on its current velocity and the impulse to apply.
         * @param vel The current velocity of the object.
         * @param impulse The impulse to apply.
         */
        static void applyImpulse(Vector3 &vel, Vector3 &impulse);
    };

    class Box {
    public:
        Vector3 position;
        Vector3 size;

        Box(Vector3 position, Vector3 size) : position(position), size(size) {};
    };

    class Sphere {
    public:
        Vector3 position;
        float radius;

        Sphere(Vector3 position, float radius) : position(position), radius(radius) {};
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

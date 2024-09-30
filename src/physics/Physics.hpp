/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#ifndef PHYSICS_HPP
#define PHYSICS_HPP
#include "glm/ext/vector_float3.hpp"


/**
 * @class Physics
 * @brief A class that represents the physics of an object in a 3D space.
 * @version v0.1.0
 * @since v0.1.0
 * @author Landry GIGANT
 */
class Physics {
public:
 /**
  * @typedef Vector3
  * @brief A type alias for glm::vec3, representing a 3D vector.
  * @version v0.1.0
  * @since v0.1.0
  * @author Landry GIGANT
  */
 using Vector3 = glm::vec3;

 /**
  * @class Movement
  * @brief A nested class within Physics that provides static methods for applying physics principles.
  * @details The methods in this class can be used to apply movement, drag, force, and impulse to an object.
  * @version v0.1.0
  * @since v0.1.0
  * @author Landry GIGANT
  */
 class Movement {
 public:
  /**
   * @brief Apply movement to an object based on its current position, velocity, and a time delta.
   * @param pos The current position of the object.
   * @param vel The current velocity of the object.
   * @param deltaTime The time delta to apply.
   * @version v0.1.0
   * @since v0.1.0
   * @author Landry GIGANT
   */
  static void applyMovement(Vector3 &pos, const Vector3 &vel, float deltaTime);

  /**
   * @brief Apply movement to an object based on its current position, velocity, acceleration, and a time delta.
   * @param pos The current position of the object.
   * @param vel The current velocity of the object.
   * @param acc The current acceleration of the object.
   * @param deltaTime The time delta to apply.
   * @version v0.1.0
   * @since v0.1.0
   * @author Landry GIGANT
   */
  static void applyMovement(Vector3 &pos, Vector3 &vel, const Vector3 &acc,
                            float deltaTime);

  /**
   * @brief Apply movement to an object based on its current position, velocity, acceleration, terminal velocity, and a time delta.
   * @param pos The current position of the object.
   * @param vel The current velocity of the object.
   * @param acc The current acceleration of the object.
   * @param terminalVelocity The terminal velocity of the object.
   * @param deltaTime The time delta to apply.
   * @version v0.1.0
   * @since v0.1.0
   * @author Landry GIGANT
   */
  static void applyMovement(Vector3 &pos, Vector3 &vel, const Vector3 &acc,
                            float terminalVelocity, float deltaTime);

  /**
   * @brief Apply drag to an object based on its current velocity, a drag coefficient, and a time delta.
   * @param vel The current velocity of the object.
   * @param drag The drag coefficient to apply.
   * @param deltaTime The time delta to apply.
   * @version v0.1.0
   * @since v0.1.0
   * @author Landry GIGANT
   */
  static void applyDrag(Vector3 &vel, float drag, float deltaTime);

  /**
   * @brief Apply a force to an object based on its current velocity, the force to apply, and a time delta.
   * @param vel The current velocity of the object.
   * @param force The force to apply.
   * @param deltaTime The time delta to apply.
   * @version v0.1.0
   * @since v0.1.0
   * @author Landry GIGANT
   */
  static void applyForce(Vector3 &vel, const Vector3 &force, float deltaTime);

  /**
   * @brief Apply an impulse to an object based on its current velocity and the impulse to apply.
   * @param vel The current velocity of the object.
   * @param impulse The impulse to apply.
   * @version v0.1.0
   * @since v0.1.0
   * @author Landry GIGANT
   */
  static void applyImpulse(Vector3 &vel, const Vector3 &impulse);
 };

 /**
 * @class Box
 * @brief A class that represents a box in 3D space.
 * @details This class contains the position and size of the box.
 * @version v0.1.0
 * @since v0.1.0
 * @author Landry GIGANT
 */
 class Box {
 public:
  /**
   * @brief The position of the box in 3D space.
   */
  Vector3 position;

  /**
   * @brief The size of the box in 3D space.
   */
  Vector3 size;

  /**
   * @brief Constructor for the Box class.
   * @param position The position of the box in 3D space.
   * @param size The size of the box in 3D space.
   */
  Box(Vector3 position, Vector3 size) : position(position), size(size) {};
 };

/**
 * @class Sphere
 * @brief A class that represents a sphere in 3D space.
 * @details This class contains the position and radius of the sphere.
 * @version v0.1.0
 * @since v0.1.0
 * @author Landry GIGANT
 */
 class Sphere {
 public:
  /**
   * @brief The position of the sphere in 3D space.
   */
  Vector3 position;

  /**
   * @brief The radius of the sphere.
   */
  float radius;

  /**
   * @brief Constructor for the Sphere class.
   * @param position The position of the sphere in 3D space.
   * @param radius The radius of the sphere.
   */
  Sphere(Vector3 position, float radius) : position(position), radius(radius) {};
 };

/**
 * @class Collision
 * @brief A class that provides static methods for collision detection.
 * @details This class contains methods for detecting collisions between boxes and spheres.
 * @version v0.1.0
 * @since v0.1.0
 * @author Landry GIGANT
 */
 class Collision {
 public:
  /**
   * @brief Check if two boxes collide.
   * @param box1 The first box.
   * @param box2 The second box.
   * @return True if the boxes collide, false otherwise.
   */
  static bool BoxCollideBox(Box box1, Box box2);

  /**
   * @brief Check if two spheres collide.
   * @param sphere1 The first sphere.
   * @param sphere2 The second sphere.
   * @return True if the spheres collide, false otherwise.
   */
  static bool SphereCollideSphere(Sphere sphere1, Sphere sphere2);

  /**
   * @brief Check if a box and a sphere collide.
   * @param box The box.
   * @param sphere The sphere.
   * @return True if the box and the sphere collide, false otherwise.
   */
  static bool BoxCollideSphere(Box box, Sphere sphere);

  /**
   * @brief Check if a sphere and a box collide.
   * @param sphere The sphere.
   * @param box The box.
   * @return True if the sphere and the box collide, false otherwise.
   */
  static bool SphereCollideBox(Sphere sphere, Box box);
 };
};


#endif //PHYSICS_HPP

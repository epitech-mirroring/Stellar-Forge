/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#ifndef STELLARFORGE_SPHERE_HPP
#define STELLARFORGE_SPHERE_HPP

#include "Collider.hpp"
#include "common/components/AComponent.hpp"
#include "common/fields/groups/InvisibleFieldGroup.hpp"

/**
 * @class Sphere
 * @brief A class that represents a sphere in 3D space.
 * @details This class contains the position and radius of the sphere.
 * @version v0.1.0
 * @since v0.1.0
 * @author Landry GIGANT
 */
class Sphere final : virtual public ICollider, public AComponent {
public:
 Vector3 position; ///< The position of the sphere in 3D space.
 Vector3 relativePosition; ///< The relative position of the sphere in 3D space, relative to the parent object.
 float radius; ///< The radius of the sphere.

 ///**
 // * @brief Constructor for the Sphere class.
 // * @param position The position of the sphere in 3D space.
 // * @param radius The radius of the sphere.
 // */
 //Sphere(Vector3 position, float radius);

 /**
  * @brief Set the position of the sphere.
  * @param position The new position of the sphere.
  */
 void setPosition(Vector3 position) override;

 /**
  * @brief Get the position of the sphere.
  * @return The position of the sphere.
  */
 [[nodiscard]] Vector3 getPosition() const override;

 /**
  * @brief Set the relative position of the sphere.
  * @param position The new relative position of the sphere.
  */
 void setRelativePosition(Vector3 RelativePosition) override;

 /**
  * @brief Get the relative position of the sphere.
  * @return The relative position of the sphere.
  */
 [[nodiscard]] Vector3 getRelativePosition() const override;

 /**
  * @brief Check if the sphere collides with another collider.
  * @param collider The collider to check for collision.
  * @return True if the sphere collides with the collider, false otherwise.
  */
 bool collide(ICollider *collider) override;

 /**
 * @brief Scale the sphere by a factor.
 * @param scale The factor to scale the sphere by.
 */
 void scale(float scale) override;

 class Meta : public IMeta {
 protected:
    Sphere *_owner;
    InvisibleFieldGroup _fieldGroup;
 public:
     explicit Meta(Sphere *owner);
     ~Meta() override = default;
     [[nodiscard]] std::string getName() const override;
     [[nodiscard]] std::string getDescription() const override;
     [[nodiscard]] bool isUnique() const override;
     [[nodiscard]] bool canBeRemoved() const override;
     [[nodiscard]] std::vector<const IFieldGroup *> getFieldGroups() const override;
 };

 explicit Sphere(IObject *owner, const json::JsonObject *data = nullptr);
 Sphere(IObject *owner, Vector3 position, float radius);

 void runComponent() override;
 [[nodiscard]] json::IJsonObject *serializeData() override;
 void deserialize(const json::IJsonObject *data) override;
 Sphere *clone(IObject *owner) const override;
};

#endif //STELLARFORGE_SPHERE_HPP

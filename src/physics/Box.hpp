/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#ifndef STELLARFORGE_BOX_HPP
#define STELLARFORGE_BOX_HPP

#include "Collider.hpp"
#include "StellarForge/Common/components/AComponent.hpp"
#include "StellarForge/Common/fields/groups/InvisibleFieldGroup.hpp"

/**
* @class Box
* @brief A class that represents a box in 3D space.
* @details This class contains the position and size of the box.
* @version v0.1.0
* @since v0.1.0
* @author Landry GIGANT
*/
class Box final : virtual public ICollider, public AComponent {
public:
 Vector3 position; ///< The position of the box in 3D space.
 Vector3 relativePosition; ///< The relative position of the box in 3D space, relative to the parent object.
 Vector3 size; ///< The size of the box in 3D space.

 /**
  * @brief Set the position of the box.
  * @param position The new position of the box.
  */
 void setPosition(Vector3 position) override;

 /**
  * @brief Get the position of the box.
  * @return The position of the box.
  */
 [[nodiscard]] Vector3 getPosition() const override;

 /**
  * @brief Set the relative position of the box.
  * @param position The new relative position of the box.
  */
 void setRelativePosition(Vector3 RelativePosition) override;

 /**
  * @brief Check if the box collides with another collider.
  * @param collider The collider to check for collision.
  * @return True if the box collides with the collider, false otherwise.
  */
 [[nodiscard]] Vector3 getRelativePosition() const override;

 /**
  * @brief Check if the box collides with another collider.
  * @param collider The collider to check for collision.
  * @return True if the box collides with the collider, false otherwise.
  */
 bool collide(ICollider *collider) override;

 /**
  * @brief Scale the box by a factor.
  * @param scale The factor to scale the box by.
  */
 void scale(float scale) override;

 class Meta final : public IMeta {
 protected:
    Box *_owner;
    InvisibleFieldGroup _fieldGroup;
 public:
    explicit Meta(Box *owner);
    ~Meta() override = default;
    [[nodiscard]] std::string getName() const override;
    [[nodiscard]] std::string getDescription() const override;
    [[nodiscard]] bool isUnique() const override;
    [[nodiscard]] bool canBeRemoved() const override;
    [[nodiscard]] std::vector<const IFieldGroup *> getFieldGroups() const override;
 };

 explicit Box(IObject *owner, const json::JsonObject *data = nullptr);
 Box(IObject *owner, Vector3 pos, Vector3 size);

 void runComponent() override;
 [[nodiscard]] json::IJsonObject *serializeData() const override;
 void deserialize(const json::IJsonObject *data) override;
 Box *clone(IObject *owner) const override;
};

#endif //STELLARFORGE_BOX_HPP

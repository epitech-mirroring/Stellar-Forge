/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** Cube.hpp
**/

#ifndef CUBE_HPP
#define CUBE_HPP

#include "I3DGraphicsComponent.hpp"
#include "common/components/AComponent.hpp"
#include "common/fields/groups/InvisibleFieldGroup.hpp"
#include "raylib.h"

class Cube final : public AComponent, public I3DGraphicsComponent {
public:
    /**
     * @brief Constructor for Cube class.
     * @param owner The owner of the component.
     * @param size The size of the cube.
     * @param color The color of the cube.
     */
    Cube(IObject *owner, float size, Color color);

    Cube(IObject *owner, const json::JsonObject *data);

    /**
     * @brief Destructor for Cube class.
     */
    ~Cube() override = default;

    /**
     * @brief Renders the cube.
     * @details This function handles the drawing of the cube in the scene, applying rotation.
     * @param camera The camera to render the cube from.
     */
    void render(Camera3D camera) override;

    void runComponent() override;
    glm::vec2 getSize() override;

 /**
  * @class Meta
  * @brief The metaclass for the Cube class
  * @version v0.1.0
  * @since v0.1.0
  * @author Aubane NOURRY
  */
 class Meta final : public IMeta {
 protected:
  Cube *_owner;
  InvisibleFieldGroup _fieldGroup;

 public:
  /**
   * @brief The constructor of the Meta class for the Cube class
   * @version v0.1.0
   * @since v0.1.0
   * @author Aubane NOURRY
   */
  explicit Meta(Cube *owner);

  [[nodiscard]] std::string getName() const override;

  [[nodiscard]] std::string getDescription() const override;

  [[nodiscard]] bool isUnique() const override;

  [[nodiscard]] bool canBeRemoved() const override;

  [[nodiscard]] std::vector<const IFieldGroup *> getFieldGroups() const override;
 };

 [[nodiscard]] json::IJsonObject *serializeData() override;
 void deserialize(const json::IJsonObject *data) override;
 [[nodiscard]] Cube *clone(IObject *owner) const override;

private:
    float size;       /**< Size of the cube. */
    Color color;      /**< Color of the cube. */
    Vector3 rotation; /**< Rotation axis and angle. */
};

#endif //CUBE_HPP

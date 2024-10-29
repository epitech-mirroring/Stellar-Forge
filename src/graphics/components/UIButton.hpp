/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** UIButton.hpp
**/

#ifndef UIBUTTON_HPP
#define UIBUTTON_HPP

#include "IGraphicsComponent.hpp"
#include "common/fields/groups/InvisibleFieldGroup.hpp"
#include "Button.hpp"

/**
 * @class UIButton
 * @brief A UI button component: a clickable button with text and a colored rectangle.
 * @details UIButton provides the functionality for detecting clicks within its area,
 *          triggering events when pressed or released, and allowing for configuration
 *          using position, size, and a unique identifier.
 * @version v0.1.0
 * @since v0.1.0
 * @author Aubane NOURRY
 */
class UIButton final : public Button, public IGraphicsComponent {
public:
  UIButton(IObject *owner, float rectX, float rectY, float width, float height, const std::string& buttonId, std::string label, int charSize);
  UIButton(IObject *owner, const json::JsonObject *data);
  void render(sf::RenderWindow *window) override;
  glm::vec2 getSize() override;
  static std::string findDefaultFontPath();
  [[nodiscard]] UIButton *clone(IObject *owner) const override;

  /**
  * @class Meta
  * @brief Metadata class for UIButton.
  * @details Provides metadata information and field groups for the UIButton component.
  * @version v0.1.0
  * @since v0.1.0
  */
   class Meta final : public IMeta {
   protected:
       UIButton *_owner; /**< Pointer to the owning UIButton instance. */
       InvisibleFieldGroup _fieldGroup; /**< Field group for invisible fields. */

   public:
       /**
        * @brief Constructor for Meta.
        * @param owner Pointer to the owning UIButton instance.
        * @version v0.1.0
        * @since v0.1.0
        */
       explicit Meta(UIButton *owner);

       /**
        * @brief Gets the name of the metadata.
        * @return The name of the metadata.
        * @version v0.1.0
        * @since v0.1.0
        */
       [[nodiscard]] std::string getName() const override;

       /**
        * @brief Gets the description of the metadata.
        * @return The description of the metadata.
        * @version v0.1.0
        * @since v0.1.0
        */
       [[nodiscard]] std::string getDescription() const override;

       /**
        * @brief Checks if the metadata is unique.
        * @return True if the metadata is unique, false otherwise.
        * @version v0.1.0
        * @since v0.1.0
        */
       [[nodiscard]] bool isUnique() const override;

       /**
        * @brief Checks if the metadata can be removed.
        * @return True if the metadata can be removed, false otherwise.
        * @version v0.1.0
        * @since v0.1.0
        */
       [[nodiscard]] bool canBeRemoved() const override;

       /**
        * @brief Gets the field groups associated with the metadata.
        * @return A vector of pointers to the field groups.
        * @version v0.1.0
        * @since v0.1.0
        */
       [[nodiscard]] std::vector<const IFieldGroup *> getFieldGroups() const override;
   };

private:
  std::string _label;
  sf::Font _font;
  sf::Text _text;
  sf::RectangleShape _rect;
  int _charSize{};
};

#endif //UIBUTTON_HPP

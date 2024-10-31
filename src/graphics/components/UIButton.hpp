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
  /**
   * @brief Constructor for UIButton.
   * @param owner Pointer to the owning IObject instance.
   * @param rectX The x-coordinate of the button's rectangle.
   * @param rectY The y-coordinate of the button's rectangle.
   * @param width The width of the button's rectangle.
   * @param height The height of the button's rectangle.
   * @param buttonId The unique identifier for the button.
   * @param label The text label for the button.
   * @param charSize The character size for the text label.
   * @version v0.1.0
   * @since v0.1.0
   */
  UIButton(IObject *owner, float rectX, float rectY, float width, float height, const std::string& buttonId, std::string label, int charSize);

  /**
   * @brief Alternative constructor for UIButton that accepts JSON data.
   * @param owner Pointer to the owning IObject instance.
   * @param data A JSON object for initializing UIButton properties.
   * @version v0.1.0
   * @since v0.1.0
   */
  UIButton(IObject *owner, const json::JsonObject *data);

  /**
   * @brief Renders the UIButton on the provided window.
   * @param window Pointer to the SFML render window where the button will be drawn.
   * @version v0.1.0
   * @since v0.1.0
   */
  void render(sf::RenderWindow *window) override;

  /**
   * @brief Retrieves the size of the UIButton as a 2D vector.
   * @return A glm::vec2 representing the width and height of the UIButton.
   * @version v0.1.0
   * @since v0.1.0
   */
  glm::vec2 getSize() override;

  /**
   * @brief Finds the default font path based on the operating system.
   * @return A string containing the path to the default font.
   * @throws GraphicsException if the OS is unsupported.
   * @version v0.1.0
   * @since v0.1.0
   */
  static std::string findDefaultFontPath();

  /**
   * @brief Hides or shows the rectangle of the UIButton.
   * @param hide True to hide the rectangle, false to show it.
   * @version v0.1.0
   * @since v0.1.0
   */
  void hideRect(bool hide);

  /**
   * @brief Clones the UIButton for a different owner.
   * @param owner The new owner for the cloned UIButton.
   * @return A pointer to the cloned UIButton instance.
   * @version v0.1.0
   * @since v0.1.0
   */
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

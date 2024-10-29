/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** Button.hpp
**/

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "IGraphicsComponent.hpp"
#include "common/components/AComponent.hpp"
#include "common/fields/groups/InvisibleFieldGroup.hpp"
#include "common/event/EventSystem.hpp"

/**
 * @class Button
 * @brief A clickable button component.
 * @details Button provides the functionality for detecting clicks within its area,
 *          triggering events when pressed or released, and allowing for configuration
 *          using position, size, and a unique identifier.
 * @version v0.1.0
 * @since v0.1.0
 * @author Aubane NOURRY
 */
class Button : public AComponent {
public:
  /**
   * @brief Primary constructor for Button with specified dimensions.
   * @param owner The owning object of this button component.
   * @param rectX X-coordinate of the button's position.
   * @param rectY Y-coordinate of the button's position.
   * @param width Width of the button.
   * @param height Height of the button.
   * @param buttonId Identifier for the button.
   * @details Initializes a Button instance with positional and sizing attributes.
   * @version v0.1.0
   * @since v0.1.0
   */
  Button(IObject *owner, float rectX, float rectY, float width, float height, std::string buttonId);

  /**
   * @brief Constructor that initializes Button with JSON data.
   * @param owner The owner of this button component.
   * @param data JSON object with initialization parameters.
   * @details Allows Button to be configured using JSON for added flexibility.
   * @version v0.1.0
   * @since v0.1.0
   */
  Button(IObject *owner, const json::JsonObject *data);

 /**
   * @brief Constructor that initializes Button without parsing JSON data, with a specified meta.
   * @param owner The owner of this button component.
   * @param meta The meta object for this button component.
   * @version v0.1.0
   * @since v0.1.0
   */
 explicit Button(IObject *owner, const IMeta *meta);

  /**
   * @brief Destructor for Button.
   * @version v0.1.0
   * @since v0.1.0
   */
  ~Button() override = default;

  /**
   * @brief Serializes the button component's data into JSON format.
   * @return A pointer to the JSON representation of the component's data.
   * @version v0.1.0
   * @since v0.1.0
   */
  [[nodiscard]] json::IJsonObject *serializeData() override;

  /**
   * @brief Deserializes the button component's data from JSON format.
   * @param data JSON object with the component's data.
   * @version v0.1.0
   * @since v0.1.0
   */
  void deserialize(const json::IJsonObject *data) override;

  /**
   * @brief Clones the Button component for a new owner.
   * @param owner The new owner of the cloned button component.
   * @return A pointer to the cloned Button instance.
   * @version v0.1.0
   * @since v0.1.0
   */
  [[nodiscard]] Button *clone(IObject *owner) const override;

  /**
   * @brief Handles the button press event.
   * @param eventData Data associated with the press event.
   * @version v0.1.0
   * @since v0.1.0
   */
  void onPressed(const EventData &eventData) const;

  /**
   * @brief Handles the button release event.
   * @param eventData Data associated with the release event.
   * @version v0.1.0
   * @since v0.1.0
   */
  void onReleased(const EventData &eventData) const;

  /**
   * @brief Checks if a given mouse position is within the button's area.
   * @param mousePos Mouse position event data.
   * @return True if the mouse position is within the button's area, false otherwise.
   * @version v0.1.0
   * @since v0.1.0
   */
  bool inButton(const sf::Event::MouseButtonEvent *mousePos) const;

  /**
   * @brief Runs the button component's logic.
   * @version v0.1.0
   * @since v0.1.0
   */
  void runComponent() override;

  /**
   * @class Meta
   * @brief Metadata class for Button.
   * @details Provides metadata information and field groups for the Button component.
   * @version v0.1.0
   * @since v0.1.0
   */
  class Meta final : public IMeta {
  protected:
    Button *_owner; /**< Pointer to the owning Button instance. */
    InvisibleFieldGroup _fieldGroup; /**< Field group for invisible fields. */

  public:
    /**
     * @brief Constructor for Meta.
     * @param owner Pointer to the owning Button instance.
     * @version v0.1.0
     * @since v0.1.0
     */
    explicit Meta(Button *owner);

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

protected:
  float _rectX{}; /**< X-coordinate of the button's position. */
  float _rectY{}; /**< Y-coordinate of the button's position. */
  float _width{}; /**< Width of the button. */
  float _height{}; /**< Height of the button. */
  std::string _buttonId; /**< Identifier for the button. */
};

#endif //BUTTON_HPP

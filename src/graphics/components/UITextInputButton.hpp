/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** UITextInputButton.hpp
**/

#ifndef UITEXTINPUTBUTTON_HPP
#define UITEXTINPUTBUTTON_HPP

#include "IGraphicsComponent.hpp"
#include "StellarForge/Common/fields/groups/InvisibleFieldGroup.hpp"
#include "UIButton.hpp"

class UITextInputButton : public UIButton {
public:

 UITextInputButton(IObject *owner, float rectX, float rectY, float width, float height,
          const std::string &buttonId, std::string label, int charSize);

 UITextInputButton(IObject *owner, const json::JsonObject *data);

 void toggleWriting(const EventData &eventData);
 void listenToKeys(const EventData &eventData);
 void releaseShift(const EventData &eventData);

 /**
 * @class Meta
 * @brief Metadata class for UITextInputButton.
 * @details Provides metadata information and field groups for the UITextInputButton component.
 * @version v0.1.0
 * @since v0.1.0
 */
 class Meta final : public IMeta {
 protected:
  UITextInputButton *_owner; /**< Pointer to the owning UITextInputButton instance. */
  InvisibleFieldGroup _fieldGroup; /**< Field group for invisible fields. */

 public:
  /**
   * @brief Constructor for Meta.
   * @param owner Pointer to the owning UITextInputButton instance.
   * @version v0.1.0
   * @since v0.1.0
   */
  explicit Meta(UITextInputButton *owner);

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
  bool _writing = false;
  bool _capsLock = false;
  bool _firstInput = true;
 int _maxNbChar;
  std::unordered_map<std::string, char> _specialKeyMap = {
        {"period", '.'}, {"comma", ','}, {"quote", '"'}, {"slash", '/'},
        {"dash", '-'}, {"equal", '='}, {"add", '+'}, {"multiply", '*'},
        {"space", ' '}, {"lbracket", '('}, {"rbracket", ')'}, {"semicolon", ';'},
        {"colon", ':'}, {"exclamation", '!'}, {"dollar", '$'}, {"asterisk", '*'},
        {"caret", '^'}, {"less", '<'}, {"greater", '>'}, {"hash", '#'},
        {"tilde", '~'}, {"left-bracket", '{'}, {"right-bracket", '}'}, {"pipe", '|'},
        {"backslash", '\\'}, {"grave", '`'}, {"at", '@'}
    };
    std::vector<std::string> _keysToListen = {
        "a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
        "k", "l", "m", "n", "o", "p", "q", "r", "s", "t",
        "u", "v", "w", "x", "y", "z",
        "numpad-0", "numpad-1", "numpad-2", "numpad-3", "numpad-4",
        "numpad-5", "numpad-6", "numpad-7", "numpad-8", "numpad-9",
        "period", "enter", "backspace", "quote", "slash", "dash", "equal",
        "add", "multiply", "space", "lbracket", "rbracket", "comma",
        "semicolon", "colon", "exclamation", "dollar", "asterisk", "caret",
        "less", "greater", "hash", "tilde", "right-bracket", "left-bracket", "pipe",
        "backslash", "grave", "at", "left-shift"
    };
};

#endif //UITEXTINPUTBUTTON_HPP

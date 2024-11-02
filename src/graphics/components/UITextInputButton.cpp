/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** UITextInputButton.cpp
**/

#include "UITextInputButton.hpp"

#include <iostream>
#include <utility>

#include "StellarForge/Common/fields/IntField.hpp"
#include "StellarForge/Common/fields/StringField.hpp"
#include "StellarForge/Common/fields/Vector2Field.hpp"
#include "StellarForge/Common/fields/FileField.hpp"
#include "../GraphicsException.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

UITextInputButton::UITextInputButton(IObject *owner, const float rectX, const float rectY,
                   const float width, const float height,
                   const std::string &buttonId, std::string label, const int charSize)
    : UIButton(owner, rectX, rectY, width, height, buttonId, std::move(label), charSize), _maxNbChar(10)
{
    EventSystem::getInstance().registerListener("mouse_pressed",
      [this](const EventData &eventData) {
          this->toggleWriting(eventData);
      });
    for (auto &key : _keysToListen) {
        EventSystem::getInstance().registerListener(key + "_pressed",
          [this](const EventData &eventData) {
              this->listenToKeys(eventData);
        });
    }
    EventSystem::getInstance().registerListener("left-shift_released",
      [this](const EventData &eventData) {
          this->releaseShift(eventData);
    });
}

UITextInputButton::UITextInputButton(IObject *owner, const json::JsonObject *data) : UIButton(owner, new Meta(this)) {
  this->deserializeFields(data);
  _font.loadFromFile(findDefaultFontPath());
  _text.setFont(_font);
  _text.setString(_label);
  _text.setCharacterSize(_charSize);
  _text.setFillColor(sf::Color::White);
  _text.setPosition(_rectX + (_width / 2) - (_text.getGlobalBounds().width / 2),
                    _rectY + (_height / 2) - (_text.getGlobalBounds().height / 2));
  _rect.setSize(sf::Vector2f(_width, _height));
  _rect.setPosition(_rectX, _rectY);
  _rect.setFillColor(sf::Color(100, 100, 100));
    EventSystem::getInstance().registerListener("mouse_pressed",
      [this](const EventData &eventData) {
          this->toggleWriting(eventData);
      });
    for (auto &key : _keysToListen) {
        EventSystem::getInstance().registerListener(key + "_pressed",
          [this](const EventData &eventData) {
              this->listenToKeys(eventData);
        });
    }
    EventSystem::getInstance().registerListener("left-shift_released",
      [this](const EventData &eventData) {
          this->releaseShift(eventData);
    });
}

std::string UITextInputButton::getValue() {
  return _label;
}

void UITextInputButton::releaseShift(const EventData &eventData) {
  (void)eventData;
  _capsLock = false;
}

UITextInputButton::Meta::Meta(UITextInputButton *owner)
    : IMeta(), _owner(owner), _fieldGroup({}) {
    const std::vector<IField *> fields = {
        new StringField("id", "The ID of the button",
                        [this](const std::string &value) {
                            this->_owner->_buttonId = value;
                        }, [this] {
                            return this->_owner->_buttonId;
                        }),
        new StringField("Text", "The text displayed on the button",
                        [this](const std::string &value) {
                            this->_owner->_label = value;
                        }, [this] {
                            return this->_owner->_label;
                        }),
        new IntField("TextSize", "The size of the text characters",
                     [this](const int &value) {
                         this->_owner->_charSize = value;
                     }, [this] {
                         return this->_owner->_charSize;
                     }),
        new IntField("MaximumSize", "The maximum number of characters",
                     [this](const int &value) {
                         this->_owner->_maxNbChar = value;
                     }, [this] {
                         return this->_owner->_maxNbChar;
                     }),
        new Vector2Field("Position", "The position of the button",
                         [this](const glm::vec2 &pos) {
                             this->_owner->_rectX = pos.x;
                             this->_owner->_rectY = pos.y;
                         }, [this] {
                             return glm::vec2(this->_owner->_rectX, this->_owner->_rectY);
                         }),
        new Vector2Field("Dimensions", "Height and width of the button",
                         [this](const glm::vec2 &pos) {
                             this->_owner->_width = pos.x;
                             this->_owner->_height = pos.y;
                         }, [this] {
                             return glm::vec2(this->_owner->_rectX, this->_owner->_rectY);
                         })
    };
    this->_fieldGroup = InvisibleFieldGroup(fields);
}

std::string UITextInputButton::Meta::getName() const {
    return "UITextInputButton";
}

std::string UITextInputButton::Meta::getDescription() const {
    return "A button that allows text input";
}

bool UITextInputButton::Meta::isUnique() const {
    return false;
}

bool UITextInputButton::Meta::canBeRemoved() const {
    return true;
}

std::vector<const IComponent::IMeta::IFieldGroup *>
UITextInputButton::Meta::getFieldGroups() const {
    return {&_fieldGroup};
}

void UITextInputButton::toggleWriting(const EventData &eventData) {
   _writing = inButton(static_cast<sf::Event::MouseButtonEvent *>(eventData.data));
    std::cout << "writing: " << _writing << std::endl;
}

void UITextInputButton::listenToKeys(const EventData &eventData) {
  if (_writing) {
      std::cout << "writing" << std::endl;
      if (_firstInput) {
          std::cout << "first input" << std::endl;
          _label = "";
          _firstInput = false;
      }
    std::string key = eventData.name;
    if (key.size() > 8 && key.substr(key.size() - 8) == "_pressed") {
      key = key.substr(0, key.size() - 8);
    }
    if (key == "backspace") {
      if (!_label.empty()) {
        _label.pop_back();
      }
    } else if (key == "enter") {
      _writing = false;
    } else if (key == "left-shift") {
      _capsLock = true;
    } else {
        if (_label.size() >= _maxNbChar) {
            return;
        }
      if (const auto mapKey = _specialKeyMap.find(key); mapKey != _specialKeyMap.end()) {
        _label += mapKey->second;
      } else if (key.rfind("numpad-", 0) == 0) {
        _label += key.substr(7);
      } else {
        if (_capsLock && key.length() == 1 && (std::isalpha(key[0]) != 0)) {
          _label += static_cast<char>(std::toupper(key[0]));
        } else {
          _label += key;
        }
      }
    }
      _text.setString(_label);
  }
}
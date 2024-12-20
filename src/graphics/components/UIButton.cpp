/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** UIButton.cpp
**/

#include "UIButton.hpp"

#include <utility>

#include "StellarForge/Common/fields/IntField.hpp"
#include "StellarForge/Common/fields/StringField.hpp"
#include "StellarForge/Common/fields/Vector2Field.hpp"
#include "StellarForge/Common/fields/FileField.hpp"
#include "StellarForge/Common/fields/ColorField.hpp"
#include "../GraphicsException.hpp"

UIButton::UIButton(IObject *owner, const float rectX, const float rectY,
                   const float width, const float height,
                   const std::string &buttonId, std::string label, const int charSize)
    : Button(owner, rectX, rectY, width, height, buttonId), _label(std::move(label)) {
    _font.loadFromFile(findDefaultFontPath());
    _text.setFont(_font);
    _text.setString(_label);
    _text.setCharacterSize(charSize);
    _text.setFillColor(*_textColor);
    _text.setPosition(_rectX + (_width / 2) - (_text.getGlobalBounds().width / 2),
                      _rectY + (_height / 2) - (_text.getGlobalBounds().height / 2) - 5);
    _rect.setSize(sf::Vector2f(width, height));
    _rect.setPosition(rectX, rectY);
    _rect.setFillColor(*_rectColor);
}

UIButton::UIButton(IObject *owner, const json::JsonObject *data) : Button(
    owner, new Meta(this)) {
    this->deserializeFields(data);
    _font.loadFromFile(findDefaultFontPath());
    _text.setFont(_font);
    _text.setString(_label);
    _text.setCharacterSize(_charSize);
    _text.setFillColor(*_textColor);
    _text.setPosition(_rectX + (_width / 2) - (_text.getGlobalBounds().width / 2),
                      _rectY + (_height / 2) - (_text.getGlobalBounds().height / 2) - 5);
    _rect.setSize(sf::Vector2f(_width, _height));
    _rect.setPosition(_rectX, _rectY);
    _rect.setFillColor(*_rectColor);
}

UIButton::UIButton(IObject *owner, const IMeta *meta) : Button(
    owner, meta) {
}

std::string UIButton::findDefaultFontPath() {
#ifdef _WIN32
    return "C:\\Windows\\Fonts\\arial.ttf";
#elif defined(__linux__)
    return "/usr/share/fonts/liberation-sans/LiberationSans-Regular.ttf";
#else
    throw GraphicsException("Unknown OS: No default font available");
#endif
}

void UIButton::hideRect(const bool hide) {
    _rect.setFillColor(hide ? sf::Color::Transparent : *_rectColor);
}

void UIButton::render(sf::RenderWindow *window) {
    window->draw(_rect);
    window->draw(_text);
}

glm::vec2 UIButton::getSize() {
    return {_rect.getSize().x, _rect.getSize().y};
}

UIButton::Meta::Meta(UIButton *owner)
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
        new ColorField("TextColor", "The color of the text",
         [this](const std::vector<unsigned char> &color) {
             this->_owner->_textColor = new sf::Color();
             if (color.size() != 4) {
                 this->_owner->_textColor = new sf::Color(255, 255, 255, 255);
                    return;
             }
             this->_owner->_textColor->r = color[0];
             this->_owner->_textColor->g = color[1];
             this->_owner->_textColor->b = color[2];
             this->_owner->_textColor->a = color[3];
          }, [this] {
              return std::vector{
                  this->_owner->_textColor->r,
                  this->_owner->_textColor->g,
                  this->_owner->_textColor->b,
                  this->_owner->_textColor->a
              };
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
                         }),
        new ColorField("Color", "The color of the cube",
         [this](const std::vector<unsigned char> &color) {
             this->_owner->_rectColor = new sf::Color();
             if (color.size() != 4) {
                 this->_owner->_rectColor = new sf::Color(100, 100, 100, 255);
                    return;
             }
             this->_owner->_rectColor->r = color[0];
             this->_owner->_rectColor->g = color[1];
             this->_owner->_rectColor->b = color[2];
             this->_owner->_rectColor->a = color[3];
          }, [this] {
              return std::vector{
                  this->_owner->_rectColor->r,
                  this->_owner->_rectColor->g,
                  this->_owner->_rectColor->b,
                  this->_owner->_rectColor->a
              };
          })
    };
    this->_fieldGroup = InvisibleFieldGroup(fields);
}

std::string UIButton::Meta::getName() const {
    return "UIButton";
}

std::string UIButton::Meta::getDescription() const {
    return "A button with a label";
}

bool UIButton::Meta::isUnique() const {
    return false;
}

bool UIButton::Meta::canBeRemoved() const {
    return true;
}

std::vector<const IComponent::IMeta::IFieldGroup *>
UIButton::Meta::getFieldGroups() const {
    return {&_fieldGroup};
}

UIButton *UIButton::clone(IObject *owner) const {
    return new UIButton(owner, _rectX, _rectY, _width, _height, _buttonId, _label,
                        _charSize);
}

void UIButton::setTextColor(sf::Color *color) {
    _textColor = color;
    _text.setFillColor(*color);
}

void UIButton::setLabel(const std::string &label) {
    _label = label;
    _text.setString(label);
    _text.setPosition(_rectX + (_width / 2) - (_text.getGlobalBounds().width / 2),
                      _rectY + (_height / 2) - (_text.getGlobalBounds().height / 2) - 5);
}

std::string UIButton::getLabel() const {
    return _label;
}

void UIButton::setRectColor(sf::Color *color) {
    _rectColor = color;
    _rect.setFillColor(*color);
}

sf::Color *UIButton::getTextColor() {
    return _textColor;
}

sf::Color *UIButton::getRectColor() {
    return _rectColor;
}

void UIButton::setFont(const std::string &fontPath) {
    if (!_font.loadFromFile(fontPath)) {
        throw GraphicsException(
            "Failed to load font from file: " + std::string(fontPath));
    }
    _text.setFont(_font);
    _text.setPosition(_rectX + (_width / 2) - (_text.getGlobalBounds().width / 2),
                      _rectY + (_height / 2) - (_text.getGlobalBounds().height / 2) - 5);
}

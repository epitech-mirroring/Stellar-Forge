/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** UIButton.cpp
**/

#include "UIButton.hpp"

#include <utility>

#include "common/fields/IntField.hpp"
#include "common/fields/StringField.hpp"
#include "common/fields/Vector2Field.hpp"
#include "common/fields/FileField.hpp"

UIButton::UIButton(IObject *owner, const float rectX, const float rectY, const float width, const float height, const std::string& buttonId, std::string label, const int charSize)
    : Button(owner, rectX, rectY, width, height, buttonId), _label(std::move(label)) {
    _font.loadFromFile(findDefaultFontPath());
    _text.setFont(_font);
    _text.setString(_label);
    _text.setCharacterSize(charSize);
    _text.setFillColor(sf::Color::White);
    _text.setPosition(rectX + (width / 2) - (_text.getGlobalBounds().width / 2), rectY + (height / 2) - (_text.getGlobalBounds().height / 2));
    _rect.setSize(sf::Vector2f(width, height));
    _rect.setPosition(rectX, rectY);
    _rect.setFillColor(sf::Color(100, 100, 100));
}

UIButton::UIButton(IObject *owner, const json::JsonObject *data) : Button(owner, new Meta(this)) {
    this->deserializeFields(data);
    _font.loadFromFile(findDefaultFontPath());
    _text.setFont(_font);
    _text.setString(_label);
    _text.setCharacterSize(_charSize);
    _text.setFillColor(sf::Color::White);
    _text.setPosition(_rectX + (_width / 2) - (_text.getGlobalBounds().width / 2), _rectY + (_height / 2) - (_text.getGlobalBounds().height / 2));
    std::cout << "Text position: " << _text.getPosition().x << ", " << _text.getPosition().y << std::endl;
    std::cout << "Text label " << _label << std::endl;
    _rect.setSize(sf::Vector2f(_width, _height));
    _rect.setPosition(_rectX, _rectY);
    _rect.setFillColor(sf::Color(100, 100, 100));
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
    _rect.setFillColor(hide ? sf::Color::Transparent : sf::Color(100, 100, 100));
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
                            std::cout << "Setting button id to " << value << std::endl;
                            this->_owner->_buttonId = value;
                        }, [this]
                        {
                            return this->_owner->_buttonId;
                        }),
        new StringField("Text", "The text displayed on the button",
                        [this](const std::string &value) {
                            std::cout << "Setting label text to " << value << std::endl;
                            this->_owner->_label = value;
                        }, [this]
                        {
                            return this->_owner->_label;
                        }),
        new IntField("TextSize", "The size of the text characters",
                     [this](const int &value) {
                         std::cout << "Setting char size to " << value << std::endl;
                         this->_owner->_charSize = value;
                     }, [this]
                     {
                         return this->_owner->_charSize;
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
                         })};
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

std::vector<const IComponent::IMeta::IFieldGroup *> UIButton::Meta::getFieldGroups() const
{
    return {&_fieldGroup};
}

UIButton *UIButton::clone(IObject *owner) const {
    return new UIButton(owner, _rectX, _rectY, _width, _height, _buttonId, _label, _charSize);
}

/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** UIButton.cpp
**/

#include "UIButton.hpp"

#include "common/json/JsonNull.hpp"
#include "common/fields/FloatField.hpp"
#include "common/fields/StringField.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <utility>

UIButton::UIButton(IObject *owner, const float rectX, const float rectY, const float width, const float height, std::string buttonId)
    : AComponent(owner, new Meta(this)), _rectX(rectX), _rectY(rectY), _width(width), _height(height), _buttonId(std::move(buttonId)) {
    this->_shape.setPosition(rectX, rectY);
    this->_shape.setSize(sf::Vector2f(width, height));
    this->_shape.setFillColor(sf::Color::Transparent);
    this->_shape.setOutlineColor(sf::Color::Transparent);
    this->_shape.setOutlineThickness(1);
    EventSystem::getInstance().registerListener("mouse_pressed", [this](const EventData &eventData) {
        this->onPressed(eventData);
    });
    EventSystem::getInstance().registerListener("mouse_released", [this](const EventData &eventData) {
        this->onReleased(eventData);
    });
}

UIButton::UIButton(IObject *owner, const json::JsonObject *data): AComponent(
        owner, new Meta(this), data) {
    this->deserializeFields(data);
    EventSystem::getInstance().registerListener("mouse_pressed", [this](const EventData &eventData) {
        this->onPressed(eventData);
    });
    EventSystem::getInstance().registerListener("mouse_released", [this](const EventData &eventData) {
        this->onReleased(eventData);
    });
}

json::IJsonObject *UIButton::serializeData() {
    return new json::JsonNull();
}

void UIButton::deserialize(const json::IJsonObject *data) {
}

UIButton *UIButton::clone(IObject *owner) const {
    return new UIButton(owner, this->_rectX, this->_rectY, this->_width, this->_height, this->_buttonId);
}

void UIButton::onPressed(const EventData &eventData) const
{
    if (const auto *mousePos = static_cast<sf::Event::MouseButtonEvent *>(eventData.data); this->_shape.getGlobalBounds().contains(static_cast<float>(mousePos->x), static_cast<float>(mousePos->y))) {
        EventSystem::getInstance().triggerEvents("button_" + this->_buttonId + "_pressed", nullptr);
    }
}

void UIButton::onReleased(const EventData &eventData) const
{
    if (const auto *mousePos = static_cast<sf::Event::MouseButtonEvent *>(eventData.data); this->_shape.getGlobalBounds().contains(static_cast<float>(mousePos->x), static_cast<float>(mousePos->y))) {
        EventSystem::getInstance().triggerEvents("button_" + this->_buttonId + "_released", nullptr);
    }
}

void UIButton::runComponent() {
}

UIButton::Meta::Meta(UIButton *owner)
    : IMeta(), _owner(owner), _fieldGroup({}) {
    auto *field = new StringField("id", "The ID of the button",
                                  [this](const std::string &value) {
                                      this->_owner->_buttonId = value;
                                  },
                                  [this] { return this->_owner->_buttonId; });
    auto *field2 = new FloatField("x", "The x position of the button",
                                [this](const float &value) {
                                    this->_owner->_rectX = value;
                                    this->_owner->_shape.setPosition(value, this->_owner->_rectY);
                                },
                                [this] { return this->_owner->_rectX; });
    auto *field3 = new FloatField("y", "The y position of the button",
                                [this](const float &value) {
                                    this->_owner->_rectY = value;
                                    this->_owner->_shape.setPosition(this->_owner->_rectX, value);
                                },
                                [this] { return this->_owner->_rectY; });
    auto *field4 = new FloatField("width", "The width of the button",
                                [this](const float &value) {
                                    this->_owner->_width = value;
                                    this->_owner->_shape.setSize(sf::Vector2f(value, this->_owner->_height));
                                },
                                [this] { return this->_owner->_width; });
    auto *field5 = new FloatField("height", "The height of the button",
                                [this](const float &value) {
                                    this->_owner->_height = value;
                                    this->_owner->_shape.setSize(sf::Vector2f(this->_owner->_width, value));
                                },
                                [this] { return this->_owner->_height; });
    _fieldGroup = InvisibleFieldGroup({field, field2, field3, field4, field5});
}

std::string UIButton::Meta::getName() const {
    return "Button";
}

std::string UIButton::Meta::getDescription() const {
    return "An area that can be clicked and triggers an event when clicked or released.";
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

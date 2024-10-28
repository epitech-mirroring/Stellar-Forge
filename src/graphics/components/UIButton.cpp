/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** UIButton.cpp
**/

#include "UIButton.hpp"

#include "common/json/JsonNull.hpp"
#include "common/fields/IntField.hpp"
#include "common/fields/StringField.hpp"

UIButton::UIButton(IObject *owner, int x, int y, int width, int height, std::string id)
    : AComponent(owner, new Meta(this)), _x(x), _y(y), _width(width), _height(height), _id(id) {
    this->_shape.setPosition(x, y);
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
    return new UIButton(owner, this->_x, this->_y, this->_width, this->_height, this->_id);
}

void UIButton::onPressed(const EventData &eventData) {
    auto *mousePos = static_cast<sf::Vector2i *>(eventData.data);
    if (this->_shape.getGlobalBounds().contains(mousePos->x, mousePos->y)) {
        EventSystem::getInstance().triggerEvents("button_" + this->_id + "_pressed", nullptr);
    }
}

void UIButton::onReleased(const EventData &eventData) {
    auto *mousePos = static_cast<sf::Vector2i *>(eventData.data);
    if (this->_shape.getGlobalBounds().contains(mousePos->x, mousePos->y)) {
        EventSystem::getInstance().triggerEvents("button_" + this->_id + "_released", nullptr);
    }
}

void UIButton::runComponent() {
}

UIButton::Meta::Meta(UIButton *owner)
    : IMeta(), _owner(owner), _fieldGroup({}) {
    auto *field = new StringField("id", "The ID of the button",
                                  [this](const std::string &value) {
                                      this->_owner->_id = value;
                                  },
                                  [this] { return this->_owner->_id; });
    auto *field2 = new IntField("x", "The x position of the button",
                                [this](const int &value) {
                                    this->_owner->_x = value;
                                    this->_owner->_shape.setPosition(value, this->_owner->_y);
                                },
                                [this] { return this->_owner->_x; });
    auto *field3 = new IntField("y", "The y position of the button",
                                [this](const int &value) {
                                    this->_owner->_y = value;
                                    this->_owner->_shape.setPosition(this->_owner->_x, value);
                                },
                                [this] { return this->_owner->_y; });
    auto *field4 = new IntField("width", "The width of the button",
                                [this](const int &value) {
                                    this->_owner->_width = value;
                                    this->_owner->_shape.setSize(sf::Vector2f(value, this->_owner->_height));
                                },
                                [this] { return this->_owner->_width; });
    auto *field5 = new IntField("height", "The height of the button",
                                [this](const int &value) {
                                    this->_owner->_height = value;
                                    this->_owner->_shape.setSize(sf::Vector2f(this->_owner->_width, value));
                                },
                                [this] { return this->_owner->_height; });
    _fieldGroup = InvisibleFieldGroup({field, field2, field3, field4, field5});
}
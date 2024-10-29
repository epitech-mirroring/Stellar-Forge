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

bool UIButton::inButton(const sf::Event::MouseButtonEvent* mousePos) const
{
    return static_cast<float>(mousePos->x) >= this->_rectX && static_cast<float>(mousePos->x) <= this->_rectX + this->_width &&
        static_cast<float>(mousePos->y) >= this->_rectY && static_cast<float>(mousePos->y) <= this->_rectY + this->_height;
}


void UIButton::onPressed(const EventData &eventData) const
{
    if (inButton(static_cast<sf::Event::MouseButtonEvent *>(eventData.data))) {
        std::cout << "button id " << this->_buttonId << " pressed" << std::endl;
        EventSystem::getInstance().triggerEvents("button_" + this->_buttonId + "_pressed", nullptr);
    }
}

void UIButton::onReleased(const EventData &eventData) const
{
    if (inButton(static_cast<sf::Event::MouseButtonEvent *>(eventData.data))) {
        std::cout << "button id " << this->_buttonId << " released" << std::endl;
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
                                },
                                [this] { return this->_owner->_rectX; });
    auto *field3 = new FloatField("y", "The y position of the button",
                                [this](const float &value) {
                                    this->_owner->_rectY = value;
                                },
                                [this] { return this->_owner->_rectY; });
    auto *field4 = new FloatField("width", "The width of the button",
                                [this](const float &value) {
                                    this->_owner->_width = value;
                                },
                                [this] { return this->_owner->_width; });
    auto *field5 = new FloatField("height", "The height of the button",
                                [this](const float &value) {
                                    this->_owner->_height = value;
                                },
                                [this] { return this->_owner->_height; });
    _fieldGroup = InvisibleFieldGroup({field, field2, field3, field4, field5});
}

std::string UIButton::Meta::getName() const {
    return "UIButton";
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

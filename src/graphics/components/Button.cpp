/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** Button.cpp
**/

#include "Button.hpp"

#include "common/json/JsonNull.hpp"
#include "common/fields/FloatField.hpp"
#include "common/fields/StringField.hpp"
#include "common/fields/Vector2Field.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <utility>

Button::Button(IObject *owner, const float rectX, const float rectY, const float width, const float height, std::string buttonId)
    : AComponent(owner, new Meta(this)), _rectX(rectX), _rectY(rectY), _width(width), _height(height), _buttonId(std::move(buttonId)) {
    EventSystem::getInstance().registerListener("mouse_pressed", [this](const EventData &eventData) {
        this->onPressed(eventData);
    });
    EventSystem::getInstance().registerListener("mouse_released", [this](const EventData &eventData) {
        this->onReleased(eventData);
    });
}

Button::Button(IObject *owner, const IMeta *meta) : AComponent(owner, meta) {
    EventSystem::getInstance().registerListener("mouse_pressed", [this](const EventData &eventData) {
        this->onPressed(eventData);
    });
    EventSystem::getInstance().registerListener("mouse_released", [this](const EventData &eventData) {
        this->onReleased(eventData);
    });
}

Button::Button(IObject *owner, const json::JsonObject *data): AComponent(
        owner, new Meta(this), data) {
    this->deserializeFields(data);
    EventSystem::getInstance().registerListener("mouse_pressed", [this](const EventData &eventData) {
        this->onPressed(eventData);
    });
    EventSystem::getInstance().registerListener("mouse_released", [this](const EventData &eventData) {
        this->onReleased(eventData);
    });
}

json::IJsonObject *Button::serializeData() const {
    return new json::JsonNull();
}

void Button::deserialize(const json::IJsonObject *data) {
}

Button *Button::clone(IObject *owner) const {
    return new Button(owner, this->_rectX, this->_rectY, this->_width, this->_height, this->_buttonId);
}

bool Button::inButton(const sf::Event::MouseButtonEvent* mousePos) const
{
    return static_cast<float>(mousePos->x) >= this->_rectX && static_cast<float>(mousePos->x) <= this->_rectX + this->_width &&
        static_cast<float>(mousePos->y) >= this->_rectY && static_cast<float>(mousePos->y) <= this->_rectY + this->_height;
}


void Button::onPressed(const EventData &eventData) const
{
    if (inButton(static_cast<sf::Event::MouseButtonEvent *>(eventData.data))) {
        EventSystem::getInstance().triggerEvents("button_" + this->_buttonId + "_pressed", nullptr);
    }
}

void Button::onReleased(const EventData &eventData) const
{
    if (inButton(static_cast<sf::Event::MouseButtonEvent *>(eventData.data))) {
        EventSystem::getInstance().triggerEvents("button_" + this->_buttonId + "_released", nullptr);
    }
}

void Button::runComponent() {
}

Button::Meta::Meta(Button *owner)
    : IMeta(), _owner(owner), _fieldGroup({}) {
    const std::vector<IField *> fields = {
        new StringField("id", "The ID of the button",
                        [this](const std::string &value) {
                            this->_owner->_buttonId = value;
                        }, [this]
                        {
                            return this->_owner->_buttonId;
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

std::string Button::Meta::getName() const {
    return "Button";
}

std::string Button::Meta::getDescription() const {
    return "An area that can be clicked and triggers an event when clicked or released.";
}

bool Button::Meta::isUnique() const {
    return false;
}

bool Button::Meta::canBeRemoved() const {
    return true;
}

std::vector<const IComponent::IMeta::IFieldGroup *> Button::Meta::getFieldGroups() const
{
    return {&_fieldGroup};
}

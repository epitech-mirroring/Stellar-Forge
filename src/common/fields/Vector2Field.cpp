/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
*/

#include "Vector2Field.hpp"
#include "common/json/JsonNumber.hpp"

Vector2Field::Vector2Field(std::string name, std::string description,
                           const std::function<void(glm::vec2)> &setCallback,
                           const std::function<glm::vec2()> &getCallback)
    : AField(std::move(name), std::move(description),
             IComponent::IMeta::VECTOR2), _setCallback(setCallback),
      _getCallback(getCallback) {
}

void Vector2Field::updateValue(const std::any value) {
    if (_setCallback) {
        _setCallback(std::any_cast<glm::vec2>(value));
    }
}

std::any Vector2Field::getValue() const {
    if (_getCallback) {
        return _getCallback();
    }
    return glm::vec2(0, 0);
}

json::JsonObject *Vector2Field::serialize() const {
    auto *object = new json::JsonObject(_name);
    const auto value = std::any_cast<glm::vec2>(getValue());
    object->add(new json::JsonNumber(value.x, "x"));
    object->add(new json::JsonNumber(value.y, "y"));
    return object;
}

void Vector2Field::deserialize(const json::IJsonObject *data) {
    if (data->getType() == json::OBJECT) {
        const auto *const obj = dynamic_cast<const json::JsonObject *>(data);
        if (obj->contains("x") && obj->contains("y")) {
            const auto xValue = obj->getValue<json::JsonNumber>("x")->getFloatValue();
            const auto yValue = obj->getValue<json::JsonNumber>("y")->getFloatValue();
            updateValue(glm::vec2(xValue, yValue));
        }
    }
}


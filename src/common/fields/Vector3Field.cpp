/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
*/

#include "Vector3Field.hpp"

#include "../json/JsonNumber.hpp"

Vector3Field::Vector3Field(std::string name, std::string description,
                           const std::function<void(glm::vec3)> &setCallback,
                           const std::function<glm::vec3()> &getCallback)
    : AField(std::move(name), std::move(description),
             IComponent::IMeta::VECTOR3), _setCallback(setCallback),
      _getCallback(getCallback) {
}

void Vector3Field::updateValue(const std::any value) {
    if (_setCallback) {
        _setCallback(std::any_cast<glm::vec3>(value));
    }
}

std::any Vector3Field::getValue() const {
    if (_getCallback) {
        return _getCallback();
    }
    return glm::vec3(0, 0, 0);
}

json::JsonObject *Vector3Field::serialize() const {
    auto *object = new json::JsonObject(_name);
    const auto value = std::any_cast<glm::vec3>(getValue());
    object->add(new json::JsonNumber(value.x, "x"));
    object->add(new json::JsonNumber(value.y, "y"));
    object->add(new json::JsonNumber(value.z, "z"));
    return object;
}

void Vector3Field::deserialize(const json::IJsonObject *data) {
    if (data->getType() == json::OBJECT) {
        const auto *const obj = dynamic_cast<const json::JsonObject *>(data);
        if (obj->contains("x") && obj->contains("y") && obj->contains("z")) {
            const auto xValue = obj->getValue<json::JsonNumber>("x")->getFloatValue();
            const auto yValue = obj->getValue<json::JsonNumber>("y")->getFloatValue();
            const auto zValue = obj->getValue<json::JsonNumber>("z")->getFloatValue();
            updateValue(glm::vec3(xValue, yValue, zValue));
        }
    }
}


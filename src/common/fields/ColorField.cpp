/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
*/

#include "ColorField.hpp"
#include <iostream>
#include "common/json/JsonNumber.hpp"

ColorField::ColorField(std::string name, std::string description,
                       const std::function<void(std::vector<unsigned char>)> &setCallback,
                       const std::function<std::vector<unsigned char>()> &getCallback)
    : AField(std::move(name), std::move(description), IComponent::IMeta::COLOR),
      _setCallback(setCallback),
      _getCallback(getCallback) {
}

void ColorField::updateValue(const std::any value) {
    if (_setCallback) {
        _setCallback(std::any_cast<std::vector<unsigned char>>(value));
    }
}

std::any ColorField::getValue() const {
    if (_getCallback) {
        return _getCallback();
    }
    return std::vector<unsigned char>(4, 0);
}

json::JsonObject *ColorField::serialize() const {
    auto *object = new json::JsonObject(_name);
    const auto value = std::any_cast<std::vector<unsigned char>>(getValue());
    object->add(new json::JsonNumber(value[0], "r"));
    object->add(new json::JsonNumber(value[1], "g"));
    object->add(new json::JsonNumber(value[2], "b"));
    object->add(new json::JsonNumber(value[3], "a"));
    return object;
}

void ColorField::deserialize(const json::IJsonObject *data) {
    if (data->getType() == json::OBJECT) {
        if (const auto *const obj = dynamic_cast<const json::JsonObject *>(data);
            obj->contains("r") && obj->contains("g") && obj->contains("b") && obj->contains("a")) {
            const auto rValue = static_cast<unsigned char>(obj->getValue<json::JsonNumber>("r")->getIntValue());
            const auto gValue = static_cast<unsigned char>(obj->getValue<json::JsonNumber>("g")->getIntValue());
            const auto bValue = static_cast<unsigned char>(obj->getValue<json::JsonNumber>("b")->getIntValue());
            const auto aValue = static_cast<unsigned char>(obj->getValue<json::JsonNumber>("a")->getIntValue());

            updateValue(std::vector{rValue, gValue, bValue, aValue});
        }
    }
}

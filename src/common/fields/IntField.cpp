/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include "IntField.hpp"

IntField::IntField(const std::string &name, const std::string &description,
                       const std::function<void(int)> &setCallback,
                       const std::function<int()> &
                       getCallback): AField(name, description, IComponent::IMeta::INT),
                                     _setCallback(setCallback),
                                     _getCallback(getCallback) {
}

void IntField::updateValue(const std::any value) {
    _setCallback(std::any_cast<int>(value));
}

std::any IntField::getValue() const {
    return _getCallback();
}

json::JsonNumber *IntField::serialize() const {
    return new json::JsonNumber(std::any_cast<int>(getValue()), _name);
}

void IntField::deserialize(const json::IJsonObject *data) {
    if (data->getType() == json::NUMBER) {
        const auto *const valueField = dynamic_cast<const json::JsonNumber *>(data);
        if (valueField == nullptr) {
            return;
        }
        updateValue(valueField->getIntValue());
    }
}

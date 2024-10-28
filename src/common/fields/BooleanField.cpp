/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include "BooleanField.hpp"

BooleanField::BooleanField(const std::string &name, const std::string &description,
                       const std::function<void(bool)> &setCallback,
                       const std::function<bool()> &
                       getCallback): AField(name, description, IComponent::IMeta::BOOL),
                                     _setCallback(setCallback),
                                     _getCallback(getCallback) {
}

void BooleanField::updateValue(const std::any value) {
    _setCallback(std::any_cast<bool>(value));
}

std::any BooleanField::getValue() const {
    return _getCallback();
}

json::JsonBoolean *BooleanField::serialize() const {
    return new json::JsonBoolean(std::any_cast<bool>(getValue()), _name);
}

void BooleanField::deserialize(const json::IJsonObject *data) {
    if (data->getType() == json::BOOLEAN) {
        const auto *const valueField = dynamic_cast<const json::JsonBoolean *>(data);
        if (valueField == nullptr) {
            return;
        }
        updateValue(valueField->getValue());
    }
}

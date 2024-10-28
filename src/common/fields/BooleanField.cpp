/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include "BooleanField.hpp"

BooleanField::BooleanField(const std::string &name, const std::string &description,
                       const std::function<void(float)> &setCallback,
                       const std::function<float()> &
                       getCallback): AField(name, description, IComponent::IMeta::FLOAT),
                                     _setCallback(setCallback),
                                     _getCallback(getCallback) {
}

void BooleanField::updateValue(const std::any value) {
    _setCallback(std::any_cast<float>(value));
}

std::any BooleanField::getValue() const {
    return _getCallback();
}

json::JsonBoolean *BooleanField::serialize() const {
    return new json::JsonBoolean(std::any_cast<float>(getValue()), _name);
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

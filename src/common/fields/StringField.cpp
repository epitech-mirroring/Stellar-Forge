/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include "StringField.hpp"

StringField::StringField(std::string name, std::string description,
                         const std::function<void(std::string)> &setCallback,
                         const std::function<std::string()> &getCallback): AField(
        std::move(name), std::move(description), IComponent::IMeta::STRING),
    _setCallback(setCallback), _getCallback(getCallback) {
}

void StringField::updateValue(const std::any value) {
    if (_setCallback) {
        _setCallback(std::any_cast<std::string>(value));
    }
}

std::any StringField::getValue() const {
    if (_getCallback) {
        return _getCallback();
    }
    return "";
}

json::JsonString *StringField::serialize() const {
    return new json::JsonString(std::any_cast<std::string>(getValue()), _name);
}

void StringField::deserialize(const json::IJsonObject *data) {
    if (data->getType() == json::STRING) {
        std::string const value = dynamic_cast<const json::JsonString *>(data)->
                getValue();
        updateValue(value);
    }
}

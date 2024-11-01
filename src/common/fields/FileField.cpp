/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** FileField.cpp
*/

#include "FileField.hpp"

FileField::FileField(std::string name, std::string description,
                     std::function<void(std::string)> setCallback,
                     std::function<std::string()> getCallback)
    : AField(std::move(name), std::move(description), IComponent::IMeta::STRING),
      _setCallback(std::move(setCallback)),
      _getCallback(std::move(getCallback)) {
}

void FileField::updateValue(const std::any value) {
    if (_setCallback) {
        _setCallback(std::any_cast<std::string>(value));
    }
}

std::any FileField::getValue() const {
    if (_getCallback) {
        return _getCallback();
    }
    return "";
}

json::JsonString *FileField::serialize() const {
    return new json::JsonString(std::any_cast<std::string>(getValue()), _name);
}

void FileField::deserialize(const json::IJsonObject *data) {
    if (data->getType() == json::STRING) {
        std::string const value = dynamic_cast<const json::JsonString *>(data)->
                getValue();
        updateValue(value);
    }
}

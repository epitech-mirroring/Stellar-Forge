/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#include "ComponentField.hpp"
#include "../managers/ObjectManager.hpp"

ComponentField::ComponentField(const std::string &name, const std::string &description,
                               const std::function<void(IComponent *)> &setCallback,
                               const std::function<IComponent *()> &getCallback)
    : AField(name, description, IComponent::IMeta::COMPONENT),
      _setCallback(setCallback),
      _getCallback(getCallback)
{
}

void ComponentField::updateValue(const std::any value)
{
    if (_setCallback) {
        _setCallback(std::any_cast<IComponent *>(value));
    }
}

std::any ComponentField::getValue() const
{
    if (_getCallback) {
        return _getCallback();
    }
    return nullptr;
}

json::IJsonObject *ComponentField::serialize() const
{
    if(_getCallback() == nullptr) {
        return new json::JsonNull(_name);
    }
    auto *component = std::any_cast<IComponent *>(getValue());
    if (component == nullptr) {
        return new json::JsonNull(_name);
    }
    return new json::JsonString(_name,  component->getUUID().getUuidString());
}

void ComponentField::deserialize(const json::IJsonObject *data)
{
    if (data->getType() == json::STRING) {
        const auto *const obj = dynamic_cast<const json::JsonString *>(data);
        _uuid.setUuidFromString(obj->getValue());
    }
}

void ComponentField::link()
{
    if (_uuid.getUuidString().empty()) {
        return;
    }
    for (auto [_, object] : ObjectManager::getInstance().getObjects()) {
        for (auto component : object->getComponents()) {
            if (component->getUUID() == _uuid) {
                updateValue(component);
                return;
            }
        }
    }
}

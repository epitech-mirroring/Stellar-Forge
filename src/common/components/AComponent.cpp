/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** AComponent.cpp
*/

#include "AComponent.hpp"

#include "common/IObject.hpp"
#include "common/json/JsonBoolean.hpp"
#include "common/json/JsonObject.hpp"
#include "common/json/JsonString.hpp"

AComponent::AComponent(IObject *owner, const IMeta *meta,
                       const json::JsonObject *data): _owner(owner),
                                                      _meta(meta),
                                                      _isActive(true) {
    if (data != nullptr) {
        if (data->contains("isActive")) {
            this->_isActive = data->getValue<json::JsonBoolean>("isActive")->getValue();
        }
    }
}

AComponent::~AComponent() {
    delete this->_meta;
}

void AComponent::beforeRendering() {
}

void AComponent::afterRendering() {
}

IObject *AComponent::getOwner() {
    return this->_owner;
}

const IComponent::IMeta &AComponent::getMeta() const {
    return *this->_meta;
}

bool AComponent::isActive() {
    return this->_isActive;
}

void AComponent::setActive(const bool state) {
    this->_isActive = state;
}

template<typename T>
T *AComponent::getParentComponent() {
    static_assert(std::is_base_of_v<IComponent, T>, "T must inherit from IComponent");
    for (auto &component: this->_owner->getComponents()) {
        if (dynamic_cast<T *>(component) != nullptr) {
            return dynamic_cast<T *>(component);
        }
    }
    return nullptr;
}

json::IJsonObject *AComponent::serialize() {
    auto *const obj = new json::JsonObject();
    obj->add(new json::JsonString(typeid(*this).name(), "type"));
    obj->add(new json::JsonBoolean(this->_isActive, "isActive"));
    return obj;
}

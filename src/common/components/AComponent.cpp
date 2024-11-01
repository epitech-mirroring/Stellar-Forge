/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** AComponent.cpp
*/

#include <vector>
#include <string>
#ifndef __APPLE__
#include <algorithm>
#endif
#include "AComponent.hpp"
#include "../IObject.hpp"
#include "../Utils.hpp"
#include "../json/JsonBoolean.hpp"
#include "../json/JsonObject.hpp"
#include "../json/JsonString.hpp"

AComponent::AComponent(IObject *owner, const IMeta *meta,
                       const json::JsonObject *data): _owner(owner),
                                                      _meta(meta),
                                                      _isActive(true) {
    LOG = Logger("components");
    if (data != nullptr) {
        if (data->contains("isActive")) {
            this->_isActive = data->getValue<json::JsonBoolean>("isActive")->getValue();
        }
    }
}

void AComponent::deserializeFields(const json::JsonObject *data) const {
    if (data == nullptr) {
        return;
    }
    if (data->contains("data")) {
        const auto *const fieldsData = data->getValue<json::JsonObject>("data");
        for (const auto *fieldGroup: this->_meta->getFieldGroups()) {
            if (!fieldsData->contains(fieldGroup->getName())) {
                continue;
            }
            const auto *group = fieldsData->getValue<json::JsonObject>(
                fieldGroup->getName());
            for (auto *field: fieldGroup->getFields()) {
                if (!group->contains(field->getName())) {
                    continue;
                }
                field->deserialize(
                    group->getValue<json::IJsonObject>(field->getName()));
            }
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

void AComponent::onCreation() {
}

void AComponent::onDeletion() {
}


json::IJsonObject *AComponent::serialize() {
    auto *const obj = new json::JsonObject();
    obj->add(new json::JsonString(get_typename(this), "type")
    );
    obj->add(new json::JsonBoolean(this->_isActive, "isActive"));
    auto *data = new json::JsonObject("data");
    std::vector<std::string> fieldGroupNames;
    for (const auto *fieldGroup: this->_meta->getFieldGroups()) {
        if (std::find(fieldGroupNames.begin(), fieldGroupNames.end(),
                      fieldGroup->getName()) != fieldGroupNames.end()) {
            LOG.warn << "Field group with name " << fieldGroup->getName()
                    << " already exists in component " << this->getMeta().getName()
                    << '\n';
            continue;
        }
        fieldGroupNames.push_back(fieldGroup->getName());
        auto *group = new json::JsonObject(fieldGroup->getName());
        for (const auto *field: fieldGroup->getFields()) {
            group->add(field->serialize());
        }
        data->add(group);
    }
    obj->add(data);
    obj->add("customData", this->serializeData());
    return obj;
}

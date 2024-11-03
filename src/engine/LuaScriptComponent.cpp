/*
** EPITECH PROJECT, 2024
** Stellar-Forge
** File description:
** No file there , just an epitech header example .
*/

#include "LuaScriptComponent.hpp"
#include "StellarForge/Common/fields/FileField.hpp"
#include "StellarForge/Common/json/JsonNull.hpp"
#include "StellarForge/Common/components/Transform.hpp"
#include "StellarForge/Physics/components/RigidBody.hpp"
#include "StellarForge/Graphics/components/UIText.hpp"
#include "StellarForge/Common/fields/Vector3Field.hpp"

LuaScriptComponent::LuaScriptComponent(IObject *owner, const json::JsonObject *data)
    : AComponent(owner, new Meta(this), data), file_path(""), ctx() {
    this->deserializeFields(data);
    if (owner->getComponent<Transform>() != nullptr) {
        this->ctx.AddGlobalVariable("transform", std::shared_ptr<LuaCpp::LuaMetaObject>(dynamic_cast<LuaCpp::LuaMetaObject *>(dynamic_cast<Transform *>(owner->getComponent<Transform>()))));
    }
    if (owner->getComponent<RigidBody>() != nullptr) {
        this->ctx.AddGlobalVariable("rigidbody", std::shared_ptr<LuaCpp::LuaMetaObject>(dynamic_cast<LuaCpp::LuaMetaObject *>(dynamic_cast<RigidBody *>(owner->getComponent<RigidBody>()))));
    }
    if (owner->getComponent<UIText>() != nullptr) {
        this->ctx.AddGlobalVariable("text", std::shared_ptr<LuaCpp::LuaMetaObject>(dynamic_cast<LuaCpp::LuaMetaObject *>(dynamic_cast<UIText *>(owner->getComponent<UIText>()))));
    }
    this->ctx.AddGlobalVariable("start", std::shared_ptr<LuaCpp::Engine::LuaTBoolean>(dynamic_cast<LuaCpp::Engine::LuaTBoolean *>(new LuaCpp::Engine::LuaTBoolean(true))));
}

LuaScriptComponent::Meta::Meta(LuaScriptComponent *owner) : _owner(owner), _fieldGroup({}) {
    std::vector<IField *> const fields = {
            new FileField("Script", "The lua script file to use",
                   [this](const std::string &value) {
                       this->_owner->file_path = value;
                       this->_owner->ctx.CompileFile(value, value);
                       std::cout << "Compiled file: " << value << std::endl;
                   },
                   [this] { return this->_owner->file_path; })
    };
    this->_fieldGroup = InvisibleFieldGroup(fields);
}

std::string LuaScriptComponent::Meta::getName() const {
    return "Lua Script";
}

std::string LuaScriptComponent::Meta::getDescription() const {
    return "Script component written in Lua";
}

bool LuaScriptComponent::Meta::isUnique() const {
    return false;
}

bool LuaScriptComponent::Meta::canBeRemoved() const {
    return true;
}

std::vector<const IComponent::IMeta::IFieldGroup *> LuaScriptComponent::Meta::getFieldGroups() const {
    return {&_fieldGroup};
}

void LuaScriptComponent::runComponent() {
    this->ctx.Run(this->file_path);
    this->ctx.AddGlobalVariable("start", std::shared_ptr<LuaCpp::Engine::LuaTBoolean>(dynamic_cast<LuaCpp::Engine::LuaTBoolean *>(new LuaCpp::Engine::LuaTBoolean(false))));
}

json::IJsonObject *LuaScriptComponent::serializeData() const {
    return new json::JsonNull();
}

void LuaScriptComponent::deserialize(const json::IJsonObject *data) {
}

IComponent *LuaScriptComponent::clone(IObject *owner) const {
    auto *newComp = new LuaScriptComponent(owner);
    return dynamic_cast<IComponent *>(newComp);
}

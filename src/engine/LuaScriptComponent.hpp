/*
** EPITECH PROJECT, 2024
** Stellar-Forge
** File description:
** No file there , just an epitech header example .
*/

#ifndef STELLAR_FORGE_LUASCRIPTCOMPONENT_HPP
#define STELLAR_FORGE_LUASCRIPTCOMPONENT_HPP

#include "StellarForge/Common/components/AComponent.hpp"
#include "StellarForge/Common/fields/groups/InvisibleFieldGroup.hpp"
#include <LuaCpp/LuaCpp.hpp>

class LuaScriptComponent final : public AComponent {
protected:
    std::string file_path;

    LuaCpp::LuaContext ctx;

public:
    class Meta final : public IMeta {
        LuaScriptComponent *_owner;
        InvisibleFieldGroup _fieldGroup;

    public:
        explicit Meta(LuaScriptComponent *owner);

        ~Meta() override = default;

        [[nodiscard]] std::string getName() const override;

        [[nodiscard]] std::string getDescription() const override;

        [[nodiscard]] bool isUnique() const override;

        [[nodiscard]] bool canBeRemoved() const override;

        [[nodiscard]] std::vector<const IFieldGroup *> getFieldGroups() const override;
    };

    explicit LuaScriptComponent(IObject *owner, const json::JsonObject *data = nullptr);

    ~LuaScriptComponent() override = default;

    void runComponent() override;

    [[nodiscard]] json::IJsonObject *serializeData() const override;

    void deserialize(const json::IJsonObject *data) override;

    [[nodiscard]] IComponent *clone(IObject *owner) const override;
};

#endif //STELLAR_FORGE_LUASCRIPTCOMPONENT_HPP

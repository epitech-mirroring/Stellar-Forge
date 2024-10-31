/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#ifndef STELLARFORGE_COMPONENTFIELD_HPP
#define STELLARFORGE_COMPONENTFIELD_HPP

#include "AField.hpp"

#include <functional>

#include "common/json/JsonString.hpp"
#include "common/json/JsonNull.hpp"

/**
 * @class ComponentField
 * @brief A class that represents a field in a component.
 * @details This class contains the name of the field and the value of the field.
 * @version v0.1.0
 * @since v0.1.0
 * @author Landry GIGANT
 */
class ComponentField final : public AField {
public:
    UUID _uuid;
protected:
    std::function<void(IComponent *)> _setCallback;
    std::function<IComponent *()> _getCallback;
public:
    /**
     * @brief Constructor for ComponentField.
     * @param name The name of the field.
     * @param description A brief description of the field.
     * @param setCallback The callback function to set the value of the field.
     * @param getCallback The callback function to get the value of the field.
     * @version v0.1.0
     * @since v0.1.0
     * @details Initializes the ComponentField with the given name and description.
     */
    ComponentField(const std::string &name, const std::string &description,
                   const std::function<void(IComponent *)> &setCallback = nullptr,
                   const std::function<IComponent *()> &getCallback = nullptr);

    void updateValue(std::any value) override;

    [[nodiscard]] std::any getValue() const override;

    [[nodiscard]] json::IJsonObject *serialize() const override;

    void deserialize(const json::IJsonObject *data) override;

    void link();
};

#endif //STELLARFORGE_COMPONENTFIELD_HPP

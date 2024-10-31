/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
*/

#ifndef STELLARFORGE_VECTOR2FIELD_HPP
#define STELLARFORGE_VECTOR2FIELD_HPP
#include <functional>
#include <glm/vec2.hpp>

#include "AField.hpp"

/**
 * @class Vector2Field
 * @brief Represents a field that holds a 2D vector.
 * @version v0.1.0
 * @since v0.1.0
 * @details This class inherits from AField and is used to store and manage a 2D vector field.
 */
class Vector2Field final : public AField {
protected:
    std::function<void(glm::vec2)> _setCallback;
    std::function<glm::vec2()> _getCallback;

public:
    /**
     * @brief Constructor for Vector2Field.
     * @param name The name of the field.
     * @param description A brief description of the field.
     * @param setCallback The callback function to set the value of the field.
     * @param getCallback The callback function to get the value of the field.
     * @version v0.1.0
     * @since v0.1.0
     * @details Initializes the Vector2Field with the given name and description.
     */
    Vector2Field(std::string name, std::string description,
                 const std::function<void(glm::vec2)> &setCallback = nullptr,
                 const std::function<glm::vec2()> &getCallback = nullptr);

    void updateValue(std::any value) override;

    [[nodiscard]] std::any getValue() const override;

    [[nodiscard]] json::JsonObject *serialize() const override;

    void deserialize(const json::IJsonObject *data) override;
};

#endif //STELLARFORGE_VECTOR2FIELD_HPP

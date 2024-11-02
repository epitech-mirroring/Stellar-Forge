/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
*/

#ifndef COLORFIELD_HPP
#define COLORFIELD_HPP

#include <functional>
#include <vector>  // For std::vector
#include "AField.hpp"

/**
 * @class ColorField
 * @brief Represents a field that holds an RGBA Color as a vector of unsigned chars.
 * @version v0.1.0
 * @since v0.1.0
 * @details This class inherits from AField and is used to store and manage a Color field.
 */
class ColorField final : public AField {
protected:
    std::function<void(std::vector<unsigned char>)> _setCallback; // Changed to vector
    std::function<std::vector<unsigned char>()> _getCallback; // Changed to vector

public:
    /**
     * @brief Constructor for ColorField.
     * @param name The name of the field.
     * @param description A brief description of the field.
     * @param setCallback The callback function to set the RGBA value of the field.
     * @param getCallback The callback function to get the RGBA value of the field.
     * @version v0.1.0
     * @since v0.1.0
     * @details Initializes the ColorField with the given name and description.
     */
    ColorField(std::string name, std::string description,
               const std::function<void(std::vector<unsigned char>)> &setCallback = nullptr,
               const std::function<std::vector<unsigned char>()> &getCallback = nullptr);

    void updateValue(std::any value) override;

    [[nodiscard]] std::any getValue() const override;

    [[nodiscard]] json::JsonObject *serialize() const override;

    void deserialize(const json::IJsonObject *data) override;
};

#endif //COLORFIELD_HPP

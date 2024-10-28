/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#ifndef BOOLEANFIELD_HPP
#define BOOLEANFIELD_HPP

#include <functional>

#include "AField.hpp"
#include "common/json/JsonBoolean.hpp"

class BooleanField final : public AField {
protected:
    std::function<void(float)> _setCallback;
    std::function<float()> _getCallback;

public:
    /**
     * @brief Constructor for FloatField.
     * @param name The name of the field.
     * @param description A brief description of the field.
     * @param setCallback The callback function to set the value of the field.
     * @param getCallback The callback function to get the value of the field.
     * @version v0.1.0
     * @since v0.1.0
     * @author Aubane NOURRY
     * @details Initializes the FloatField with the given name and description.
     */
    BooleanField(const std::string &name, const std::string &description,
               const std::function<void(float)> &setCallback = nullptr,
               const std::function<float()> &getCallback = nullptr);

    void updateValue(std::any value) override;

    [[nodiscard]] std::any getValue() const override;

    [[nodiscard]] json::JsonBoolean *serialize() const override;

    void deserialize(const json::IJsonObject *data) override;
};

#endif //BOOLEANFIELD_HPP

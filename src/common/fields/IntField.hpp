/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#ifndef INTFIELD_HPP
#define INTFIELD_HPP
#include "AField.hpp"

#include <functional>

#include "../json/JsonNumber.hpp"


class IntField final : public AField {
protected:
    std::function<void(int)> _setCallback;
    std::function<int()> _getCallback;

public:
    /**
     * @brief Constructor for IntField.
     * @param name The name of the field.
     * @param description A brief description of the field.
     * @param setCallback The callback function to set the value of the field.
     * @param getCallback The callback function to get the value of the field.
     * @version v0.1.0
     * @since v0.1.0
     * @details Initializes the IntField with the given name and description.
     * @author Aubane NOURRY
     */
    IntField(const std::string &name, const std::string &description,
             const std::function<void(int)> &setCallback = nullptr,
             const std::function<int()> &getCallback = nullptr);

    void updateValue(std::any value) override;

    [[nodiscard]] std::any getValue() const override;

    [[nodiscard]] json::JsonNumber *serialize() const override;

    void deserialize(const json::IJsonObject *data) override;
};

#endif //INTFIELD_HPP

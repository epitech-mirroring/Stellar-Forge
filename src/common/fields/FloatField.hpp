/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#ifndef STELLARFORGE_FLOATFIELD_HPP
#define STELLARFORGE_FLOATFIELD_HPP

#include "../AField.hpp"

/**
 * @class FloatField
 * @brief Represents a field that holds a floating-point value.
 * @version v0.1.0
 * @since v0.1.0
 * @author Landry GIGANT
 * @details This class extends the AField class to provide functionality specific to floating-point fields.
 */
class FloatField : public AField {
public:
    /**
     * @brief Constructor for FloatField.
     * @param name The name of the field.
     * @param description A brief description of the field.
     * @version v0.1.0
     * @since v0.1.0
     * @author Landry GIGANT
     */
    FloatField(std::string name, std::string description);
};

#endif //STELLARFORGE_FLOATFIELD_HPP

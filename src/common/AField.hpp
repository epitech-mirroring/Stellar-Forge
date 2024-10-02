/*** EPITECH PROJECT, 2024
** StellarForge
** File description:
** AField.hpp
*/

#ifndef AFIELD_HPP
#define AFIELD_HPP

#include "IComponent.hpp"

class AField : virtual public IComponent::IMeta::IField
{
public:
    AField(std::string name, std::string description, FieldType type);
    ~AField() override = default;

    [[nodiscard]] std::string getName() const override;
    [[nodiscard]] std::string getDescription() const override;
    [[nodiscard]] FieldType getType() const override;

private:
    std::string _name;
    std::string _description;
    FieldType _type;
};

#endif //AFIELD_HPP

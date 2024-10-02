/*** EPITECH PROJECT, 2024
** StellarForge
** File description:
** AFieldGroup.hpp
*/

#ifndef AFIELDGROUP_HPP
#define AFIELDGROUP_HPP

#include "IComponent.hpp"

class AFieldGroup : virtual public IComponent::IMeta::IFieldGroup
{
public:
    AFieldGroup(std::string name, std::string description,
                const std::vector<IComponent::IMeta::IField*>& fields);
    ~AFieldGroup() override = default;

    [[nodiscard]] std::string getName() const override;
    [[nodiscard]] std::string getDescription() const override;
    [[nodiscard]] std::vector<IComponent::IMeta::IField*> getFields() const override;

private:
    std::string _name;
    std::string _description;
    std::vector<IComponent::IMeta::IField*> _fields;
};


#endif //AFIELDGROUP_HPP

/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#ifndef STELLARFORGE_FIELDGROUP_HPP
#define STELLARFORGE_FIELDGROUP_HPP

#include <utility>

#include "../AFieldGroup.hpp"

class InvisibleFieldGroup : public AFieldGroup {
public:
    explicit InvisibleFieldGroup(const std::vector<IComponent::IMeta::IField *> &fields)
        : AFieldGroup("", "", fields) {}
};

#endif //STELLARFORGE_FIELDGROUP_HPP

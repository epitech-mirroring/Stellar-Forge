/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#ifndef STELLARFORGE_FIELDGROUP_HPP
#define STELLARFORGE_FIELDGROUP_HPP

#include <utility>

#include "../IComponent.hpp"

class InvisibleFieldGroup : virtual public IComponent::IMeta::IFieldGroup {
public:

    using IField = IComponent::IMeta::IField;

    InvisibleFieldGroup() = default;
    explicit InvisibleFieldGroup(std::vector<IField *> fields) : _fields(std::move(fields)) {}
    ~InvisibleFieldGroup() override = default;
    InvisibleFieldGroup(const InvisibleFieldGroup &other) = delete;
    InvisibleFieldGroup &operator=(const InvisibleFieldGroup &other) = delete;
    InvisibleFieldGroup(InvisibleFieldGroup &&other) = delete;
    InvisibleFieldGroup &operator=(InvisibleFieldGroup &&other) = delete;

    [[nodiscard]] std::string getName() const override { return ""; }
    [[nodiscard]] std::string getDescription() const override { return ""; }
    [[nodiscard]] std::vector<IField *> getFields() const override { return _fields; }

private:
    std::vector<IField *> _fields;
};

#endif //STELLARFORGE_FIELDGROUP_HPP

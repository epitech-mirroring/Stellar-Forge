/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#ifndef STELLARFORGE_VECTOR3FIELD_HPP
#define STELLARFORGE_VECTOR3FIELD_HPP

#include "../IComponent.hpp"

class Vector3Field : public IComponent::IMeta::IField {
private:
    const std::string _name;
    const std::string _description;
    const FieldType _type;

public:
    Vector3Field() : _name("Vector3"), _description("A 3D vector."), _type(FieldType::VECTOR3) {}
    Vector3Field(std::string &name, std::string &description) : _name(name), _description(description), _type(FieldType::VECTOR3) {}
    ~Vector3Field() override = default;
    Vector3Field(const Vector3Field &other) = delete;
    Vector3Field &operator=(const Vector3Field &other) = delete;
    Vector3Field(Vector3Field &&other) = delete;
    Vector3Field &operator=(Vector3Field &&other) = delete;

    [[nodiscard]] std::string getName() const override  { return _name; }
    [[nodiscard]] std::string getDescription() const override { return _description; }
    [[nodiscard]] FieldType getType() const override { return _type; }
};

#endif //STELLARFORGE_VECTOR3FIELD_HPP

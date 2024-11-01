/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** Cube.cpp
**/

#include "Cube.hpp"
#include "common/fields/FloatField.hpp"
#include "common/components/Transform.hpp"
#include "common/fields/groups/InvisibleFieldGroup.hpp"
#include "common/json/JsonNull.hpp"
#include "rlgl.h"

Cube::Cube(IObject *owner, const float size, const Color color): AComponent(owner, new Meta(this)), size(size), color(color), rotation({0, 0, 0}) {}

Cube::Cube(IObject *owner, const json::JsonObject *data): AComponent(owner, new Meta(this)) {
    this->deserializeFields(data);
}

void Cube::render(Camera3D *camera) {
    auto *transform = this->getParentComponent<Transform>();
    const auto position = transform->getPosition();
    const auto rotation = transform->getRotation();
    const auto scale = transform->getScale();
    BeginMode3D(*camera);

    const Matrix rotationMatrix = MatrixRotateXYZ((Vector3){ rotation.x, rotation.y, rotation.z });
    rlPushMatrix();
    rlMultMatrixf(MatrixToFloat(rotationMatrix));

    DrawCubeV({position.x, position.y, position.z}, {size * scale.x, size * scale.y, size * scale.z}, RED);
    DrawCubeWiresV({position.x, position.y, position.z}, {size * scale.x, size * scale.y, size * scale.z}, BLACK);

    rlPopMatrix();
    EndMode3D();
}

Cube *Cube::clone(IObject *owner) const {
    return new Cube(owner, size, color);
}

void Cube::runComponent() {
}

glm::vec2 Cube::getSize() {
    return {size, size};
}

Cube::Meta::Meta(Cube *owner): _owner(owner), _fieldGroup({}) {
    auto fields = std::vector<IField *>();
    auto *field = new FloatField("Size", "The size of the cube",
                                 [this](const float value) {
                                     this->_owner->size = value;
                                 },
                                 [this] { return this->_owner->size; });
    fields.push_back(field);
    this->_fieldGroup = InvisibleFieldGroup(fields);
}

std::string Cube::Meta::getName() const {
    return "Cube";
}

std::string Cube::Meta::getDescription() const {
    return "The Cube component is used to render a rotating cube in the scene.";
}

bool Cube::Meta::isUnique() const {
    return false;
}

bool Cube::Meta::canBeRemoved() const {
    return true;
}

std::vector<const IComponent::IMeta::IFieldGroup *> Cube::Meta::getFieldGroups() const {
    return {&_fieldGroup};
}

json::IJsonObject *Cube::serializeData() {
    return new json::JsonNull();
}

void Cube::deserialize(const json::IJsonObject *data) {
}

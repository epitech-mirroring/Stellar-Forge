/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
*/

#include "Transform.hpp"

#include "../fields/Vector3Field.hpp"
#include "../fields/groups/InvisibleFieldGroup.hpp"
#include "../json/JsonNull.hpp"
#include "../json/JsonNumber.hpp"
#include "../json/JsonObject.hpp"

Transform::Transform(IObject *owner, const json::JsonObject *data): AComponent(
        owner, new Meta(this), data), _position(Vector3(0, 0, 0)),
    _rotation(glm::quat(1, 0, 0, 0)), _scale(Vector3(1, 1, 1)) {
    this->deserializeFields(data);
}

Transform::Transform(IObject *owner, const Vector3 pos, const glm::quat rot,
                     const Vector3 scale): AComponent(owner, new Meta(this)),
                                           _position(pos),
                                           _rotation(rot), _scale(scale) {
}

Vector3 Transform::getPosition() const {
    return this->_position;
}

glm::quat Transform::getRotation() const {
    return this->_rotation;
}

float Transform::getRotation2D() const {
    return glm::degrees(glm::eulerAngles(this->_rotation).z);
}

Vector3 Transform::getScale() const {
    return this->_scale;
}

void Transform::setPosition(const Vector3 pos) {
    this->_position = pos;
}

void Transform::translate(const Vector3 pos) {
    this->_position += pos;
}

void Transform::setRotation(const glm::quat rot) {
    this->_rotation = rot;
}

void Transform::rotate(const Vector3 axis, const float angle) {
    this->_rotation = glm::rotate(this->_rotation, glm::radians(angle), axis);
}

void Transform::rotate2D(const float angle) {
    this->_rotation = glm::rotate(this->_rotation, glm::radians(angle), Vector3(0, 0, 1));
}

void Transform::setScale(const Vector3 scale) {
    this->_scale = scale;
}

void Transform::scaleBy(const Vector3 scale) {
    this->_scale *= scale;
}

Transform::Meta::Meta(Transform *owner): _owner(owner),
                                         _fieldGroup(InvisibleFieldGroup({})) {
    const std::vector<IField *> fields = {
        new Vector3Field("Position", "The position of the object",
                         [this](const Vector3 &pos) {
                             this->_owner->_position = pos;
                         }, [this] {
                             return this->_owner->_position;
                         }),
        new Vector3Field("Rotation", "The rotation of the object",
                         [this](const Vector3 &rot) {
                             this->_owner->_rotation = glm::quat(rot);
                         }, [this] {
                             return eulerAngles(this->_owner->_rotation);
                         }),
        new Vector3Field("Scale", "The scale of the object",
                         [this](const Vector3 &scale) {
                             this->_owner->_scale = scale;
                         }, [this] {
                             return this->_owner->_scale;
                         })
    };
    this->_fieldGroup = InvisibleFieldGroup(fields);
}

void Transform::runComponent() {
}

std::string Transform::Meta::getName() const {
    return "Transform";
}

std::string Transform::Meta::getDescription() const {
    return
            "The Transform component is used to store the position, rotation and scale of an object.";
}

bool Transform::Meta::isUnique() const {
    return true;
}

bool Transform::Meta::canBeRemoved() const {
    return false;
}

std::vector<const IComponent::IMeta::IFieldGroup *>
Transform::Meta::getFieldGroups() const {
    return {&_fieldGroup};
}

json::IJsonObject *Transform::serializeData() const {
    return new json::JsonNull();
}

void Transform::deserialize(const json::IJsonObject *data) {
}

Vector3 &Transform::getPosition() {
    return this->_position;
}

glm::quat &Transform::getRotation() {
    return this->_rotation;
}

Vector3 &Transform::getScale() {
    return this->_scale;
}

Transform *Transform::clone(IObject *owner) const {
    return new Transform(owner, this->_position,
                         this->_rotation, this->_scale);
}

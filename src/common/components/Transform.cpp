/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
*/

#include "Transform.hpp"

#include "common/fields/Vector3Field.hpp"
#include "common/fields/groups/InvisibleFieldGroup.hpp"
#include "common/json/JsonNull.hpp"
#include "common/json/JsonNumber.hpp"
#include "common/json/JsonObject.hpp"

Component::Transform::Transform(IObject *owner, const json::JsonObject *data): AComponent(
        owner, new Meta(this), data), _position(glm::vec3(0, 0, 0)),
    _rotation(glm::quat(1, 0, 0, 0)), _scale(glm::vec3(1, 1, 1)) {
    this->deserializeFields(data);
}

Component::Transform::Transform(IObject *owner, const glm::vec3 pos, const glm::quat rot,
                     const glm::vec3 scale): AComponent(owner, new Meta(this)),
                                           _position(pos),
                                           _rotation(rot), _scale(scale) {
}

glm::vec3 Component::Transform::getPosition() const {
    return this->_position;
}

glm::quat Component::Transform::getRotation() const {
    return this->_rotation;
}

glm::vec3 Component::Transform::getScale() const {
    return this->_scale;
}

void Component::Transform::setPosition(const glm::vec3 pos) {
    this->_position = pos;
}

void Component::Transform::translate(const glm::vec3 pos) {
    this->_position += pos;
}

void Component::Transform::setRotation(const glm::quat rot) {
    this->_rotation = rot;
}

void Component::Transform::rotate(const glm::vec3 axis, const float angle) {
    this->_rotation = glm::rotate(this->_rotation, angle, axis);
}

void Component::Transform::setScale(const glm::vec3 scale) {
    this->_scale = scale;
}

void Component::Transform::scaleBy(const glm::vec3 scale) {
    this->_scale *= scale;
}

Component::Transform::Meta::Meta(Transform *owner): _owner(owner),
                                         _fieldGroup(InvisibleFieldGroup({})) {
    const std::vector<IField *> fields = {
        new Vector3Field("Position", "The position of the object",
                         [this](const glm::vec3 &pos) {
                             this->_owner->_position = pos;
                         }, [this] {
                             return this->_owner->_position;
                         }),
        new Vector3Field("Rotation", "The rotation of the object",
                         [this](const glm::vec3 &rot) {
                             this->_owner->_rotation = glm::quat(rot);
                         }, [this] {
                             return eulerAngles(this->_owner->_rotation);
                         }),
        new Vector3Field("Scale", "The scale of the object",
                         [this](const glm::vec3 &scale) {
                             this->_owner->_scale = scale;
                         }, [this] {
                             return this->_owner->_scale;
                         })
    };
    this->_fieldGroup = InvisibleFieldGroup(fields);
}

void Component::Transform::runComponent() {
}

std::string Component::Transform::Meta::getName() const {
    return "Transform";
}

std::string Component::Transform::Meta::getDescription() const {
    return
            "The Transform component is used to store the position, rotation and scale of an object.";
}

bool Component::Transform::Meta::isUnique() const {
    return true;
}

bool Component::Transform::Meta::canBeRemoved() const {
    return false;
}

std::vector<const IComponent::IMeta::IFieldGroup *>
Component::Transform::Meta::getFieldGroups() const {
    return {&_fieldGroup};
}

json::IJsonObject *Component::Transform::serializeData() {
    return new json::JsonNull();
}

void Component::Transform::deserialize(const json::IJsonObject *data) {
}

glm::vec3 &Component::Transform::getPosition() {
    return this->_position;
}

glm::quat &Component::Transform::getRotation() {
    return this->_rotation;
}

glm::vec3 &Component::Transform::getScale() {
    return this->_scale;
}

Component::Transform *Component::Transform::clone(IObject *owner) const {
    return new Transform(owner, this->_position,
                         this->_rotation, this->_scale);
}

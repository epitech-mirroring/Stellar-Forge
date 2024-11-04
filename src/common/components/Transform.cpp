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
        owner, new Meta(this), data), _position(glm::vec3(0, 0, 0)),
    _rotation(glm::quat(1, 0, 0, 0)), _scale(glm::vec3(1, 1, 1)) {
    this->deserializeFields(data);
}

Transform::Transform(IObject *owner, const glm::vec3 pos, const glm::quat rot,
                     const glm::vec3 scale): AComponent(owner, new Meta(this)),
                                           _position(pos),
                                           _rotation(rot), _scale(scale) {
}

glm::vec3 Transform::getPosition() const {
    return this->_position;
}

glm::quat Transform::getRotation() const {
    return this->_rotation;
}

float Transform::getRotation2D() const {
    return glm::degrees(glm::eulerAngles(this->_rotation).z);
}

glm::vec3 Transform::getScale() const {
    return this->_scale;
}

void Transform::setPosition(const glm::vec3 pos) {
    this->_position = pos;
}

void Transform::translate(const glm::vec3 pos) {
    this->_position += pos;
}

void Transform::setRotation(const glm::quat rot) {
    this->_rotation = rot;
}

void Transform::rotate(const glm::vec3 axis, const float angle) {
    this->_rotation = glm::rotate(this->_rotation, glm::radians(angle), axis);
}

void Transform::rotate2D(const float angle) {
    this->_rotation = glm::rotate(this->_rotation, glm::radians(angle), glm::vec3(0, 0, 1));
}

void Transform::setScale(const glm::vec3 scale) {
    this->_scale = scale;
}

void Transform::scaleBy(const glm::vec3 scale) {
    this->_scale *= scale;
}

Transform::Meta::Meta(Transform *owner): _owner(owner),
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

glm::vec3 &Transform::getPosition() {
    return this->_position;
}

glm::quat &Transform::getRotation() {
    return this->_rotation;
}

glm::vec3 &Transform::getScale() {
    return this->_scale;
}

Transform *Transform::clone(IObject *owner) const {
    return new Transform(owner, this->_position,
                         this->_rotation, this->_scale);
}

using LuaType = LuaCpp::Engine::LuaType;
using LuaTNumber = LuaCpp::Engine::LuaTNumber;
using LuaTNil = LuaCpp::Engine::LuaTNil;

std::shared_ptr<LuaType> Transform::getValue(std::string &key) {
    std::cout << "Getting value for key: " << key << std::endl;
    if (key == "position_x") {
        return std::make_shared<LuaTNumber>(this->_position.x);
    }
    if (key == "position_y") {
        return std::make_shared<LuaTNumber>(this->_position.y);
    }
    if (key == "position_z") {
        return std::make_shared<LuaTNumber>(this->_position.z);
    }
    if (key == "rotation_x") {
        return std::make_shared<LuaTNumber>(this->_rotation.x);
    }
    if (key == "rotation_y") {
        return std::make_shared<LuaTNumber>(this->_rotation.y);
    }
    if (key == "rotation_z") {
        return std::make_shared<LuaTNumber>(this->_rotation.z);
    }
    if (key == "rotation_w") {
        return std::make_shared<LuaTNumber>(this->_rotation.w);
    }
    if (key == "scale_x") {
        return std::make_shared<LuaTNumber>(this->_scale.x);
    }
    if (key == "scale_y") {
        return std::make_shared<LuaTNumber>(this->_scale.y);
    }
    if (key == "scale_z") {
        return std::make_shared<LuaTNumber>(this->_scale.z);
    }
    return std::make_shared<LuaTNil>();
}

void Transform::setValue(std::string &key, std::shared_ptr<LuaType> value) {
    std::cout << "Setting value for key: " << key << std::endl;
    if (key == "position_x") {
        this->_position.x = std::dynamic_pointer_cast<LuaTNumber>(value)->getValue();
    }
    if (key == "position_y") {
        this->_position.y = std::dynamic_pointer_cast<LuaTNumber>(value)->getValue();
    }
    if (key == "position_z") {
        this->_position.z = std::dynamic_pointer_cast<LuaTNumber>(value)->getValue();
    }
    if (key == "rotation_x") {
        this->_rotation.x = std::dynamic_pointer_cast<LuaTNumber>(value)->getValue();
    }
    if (key == "rotation_y") {
        this->_rotation.y = std::dynamic_pointer_cast<LuaTNumber>(value)->getValue();
    }
    if (key == "rotation_z") {
        this->_rotation.z = std::dynamic_pointer_cast<LuaTNumber>(value)->getValue();
    }
    if (key == "rotation_w") {
        this->_rotation.w = std::dynamic_pointer_cast<LuaTNumber>(value)->getValue();
    }
    if (key == "scale_x") {
        this->_scale.x = std::dynamic_pointer_cast<LuaTNumber>(value)->getValue();
    }
    if (key == "scale_y") {
        this->_scale.y = std::dynamic_pointer_cast<LuaTNumber>(value)->getValue();
    }
    if (key == "scale_z") {
        this->_scale.z = std::dynamic_pointer_cast<LuaTNumber>(value)->getValue();
    }
}

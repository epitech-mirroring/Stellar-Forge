/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
*/

#include "RigidBody.hpp"
#include "StellarForge/Common/components/Transform.hpp"
#include "StellarForge/Common/json/JsonNull.hpp"
#include "../Physics.hpp"
#include "StellarForge/Common/fields/Vector3Field.hpp"
#include "StellarForge/Common/fields/FloatField.hpp"
#include "StellarForge/Common/fields/ComponentField.hpp"
#include "StellarForge/Common/fields/groups/InvisibleFieldGroup.hpp"
#include "StellarForge/Common/managers/SceneManager.hpp"


RigidBody::Meta::Meta(RigidBody *owner): _owner(owner), _fieldGroup(InvisibleFieldGroup({})) {
    const std::vector<IField *> &fields = {
        new Vector3Field("Velocity", "The velocity of the object",
                         [this](const Vector3 &velocity) {
                            this->_owner->_velocity = velocity;
                         }, [this]() {
                            return this->_owner->_velocity;
                         }),
        new Vector3Field("Acceleration", "The acceleration of the object",
                            [this](const Vector3 &acceleration) {
                                this->_owner->_acceleration = acceleration;
                            }, [this]() {
                                return this->_owner->_acceleration;
                            }),
        new FloatField("Terminal Velocity", "The terminal velocity of the object",
                          [this](const float &terminal_velocity) {
                            this->_owner->_terminalVelocity = terminal_velocity;
                          }, [this]() {
                            return this->_owner->_terminalVelocity;
                          }),
        new FloatField("Drag", "The drag coefficient of the object",
                            [this](const float &drag) {
                                this->_owner->_drag = drag;
                            }, [this]() {
                                return this->_owner->_drag;
                            }),
        new ComponentField("Collider", "The collider of the object",
                           [this](IComponent *collider) {
                               this->_owner->_collider = dynamic_cast<ICollider *>(collider);
                           }, [this]() {
                               return dynamic_cast<IComponent *>(this->_owner->_collider);
                           }),
    };
    _fieldGroup = InvisibleFieldGroup(fields);
}

RigidBody::RigidBody(IObject *owner, const json::JsonObject *data) : AComponent(
        owner, new Meta(this), data),
    _velocity(glm::vec3(0.0f)),
    _acceleration(glm::vec3(0.0f)),
    _terminalVelocity(0.0f),
    _drag(0.0f),
    _collider(nullptr)
{
    this->deserializeFields(data);
}

void RigidBody::applyMovement(const float deltaTime) {
    auto *transform = this->getParentComponent<Transform>();
    if (transform == nullptr) {
        return;
    }
    Physics::Movement::applyMovement(transform->getPosition(), _velocity,
                                     _acceleration, _terminalVelocity, deltaTime);
}

void RigidBody::applyDrag(const float deltaTime) {
    Physics::Movement::applyDrag(_velocity, _drag, deltaTime);
}

void RigidBody::applyForce(const float deltaTime) {
    Physics::Movement::applyForce(_velocity, _acceleration, deltaTime);
}

void RigidBody::applyImpulse(const Vector3 &impulse) {
    Physics::Movement::applyImpulse(_velocity, impulse);
}

std::vector<IObject *> RigidBody::collidingObjects() {
    std::vector<IObject *> colliding_objects;
    if (_collider == nullptr) {
        return colliding_objects;
    }
    for (auto &object : SceneManager::getInstance().getCurrentScene()->getObjects()) {
        if (object == this->getOwner()) {
            continue;
        }
        auto *other_body = object->getComponent<RigidBody>();
        if (other_body == nullptr || other_body->_collider == nullptr) {
            continue;
        }
        const Vector3 pos = this->getParentComponent<Transform>()->getPosition();
        const Vector3 pos2 = object->getComponent<Transform>()->getPosition();
        _collider->setPosition(pos);
        other_body->_collider->setPosition(pos2);
        if (other_body->_collider->collide(_collider)) {
            colliding_objects.push_back(object);
        }
    }
    return colliding_objects;
}

void RigidBody::runComponent() {
    this->applyMovement(1 / 60.0f); // Todo fetch delta time
}

std::string RigidBody::Meta::getName() const {
    return "RigidBody";
}


std::string RigidBody::Meta::getDescription() const {
    return
            "Compute the physics of the object. Velocity, acceleration, drag, terminal velocity.";
}

bool RigidBody::Meta::isUnique() const {
    return true;
}

bool RigidBody::Meta::canBeRemoved() const {
    return true;
}

std::vector<const IComponent::IMeta::IFieldGroup *>
RigidBody::Meta::getFieldGroups() const {
    return {&_fieldGroup};
}

json::IJsonObject *RigidBody::serializeData() const {
    return new json::JsonNull();
}

void RigidBody::deserialize(const json::IJsonObject *data) {
}

RigidBody *RigidBody::clone(IObject *owner) const {
    return new RigidBody(owner);
}

using LuaType = LuaCpp::Engine::LuaType;
using LuaTNumber = LuaCpp::Engine::LuaTNumber;
using LuaTNil = LuaCpp::Engine::LuaTNil;

std::shared_ptr<LuaType> RigidBody::getValue(std::string &key) {
    if (key == "velocity_x") {
        return std::make_shared<LuaTNumber>(_velocity.x);
    }
    if (key == "velocity_y") {
        return std::make_shared<LuaTNumber>(_velocity.y);
    }
    if (key == "velocity_z") {
        return std::make_shared<LuaTNumber>(_velocity.z);
    }
    if (key == "acceleration_x") {
        return std::make_shared<LuaTNumber>(_acceleration.x);
    }
    if (key == "acceleration_y") {
        return std::make_shared<LuaTNumber>(_acceleration.y);
    }
    if (key == "acceleration_z") {
        return std::make_shared<LuaTNumber>(_acceleration.z);
    }
    if (key == "terminal_velocity") {
        return std::make_shared<LuaTNumber>(_terminalVelocity);
    }
    if (key == "drag") {
        return std::make_shared<LuaTNumber>(_drag);
    }
    return std::make_shared<LuaTNil>();
}

void RigidBody::setValue(std::string &key, std::shared_ptr<LuaType> value) {
    if (key == "velocity_x") {
        _velocity.x = std::dynamic_pointer_cast<LuaTNumber>(value)->getValue();
    }
    if (key == "velocity_y") {
        _velocity.y = std::dynamic_pointer_cast<LuaTNumber>(value)->getValue();
    }
    if (key == "velocity_z") {
        _velocity.z = std::dynamic_pointer_cast<LuaTNumber>(value)->getValue();
    }
    if (key == "acceleration_x") {
        _acceleration.x = std::dynamic_pointer_cast<LuaTNumber>(value)->getValue();
    }
    if (key == "acceleration_y") {
        _acceleration.y = std::dynamic_pointer_cast<LuaTNumber>(value)->getValue();
    }
    if (key == "acceleration_z") {
        _acceleration.z = std::dynamic_pointer_cast<LuaTNumber>(value)->getValue();
    }
    if (key == "terminal_velocity") {
        _terminalVelocity = std::dynamic_pointer_cast<LuaTNumber>(value)->getValue();
    }
    if (key == "drag") {
        _drag = std::dynamic_pointer_cast<LuaTNumber>(value)->getValue();
    }
}

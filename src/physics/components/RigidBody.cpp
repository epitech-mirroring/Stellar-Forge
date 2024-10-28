/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
*/

#include "RigidBody.hpp"
#include "common/IObject.hpp"
#include "common/components/Transform.hpp"
#include "common/json/JsonNull.hpp"
#include "physics/Physics.hpp"
#include "common/managers/SceneManager.hpp"

RigidBody::Meta::Meta(RigidBody *owner): _owner(owner), _fieldGroup({}) {
}

RigidBody::RigidBody(IObject *owner, const json::JsonObject *data) : AComponent(
        owner, new Meta(this), data),
    _velocity(glm::vec3(0.0f)),
    _acceleration(glm::vec3(0.0f)),
    _terminalVelocity(0.0f),
    _drag(0.0f),
    _collider(nullptr)
{
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

json::IJsonObject *RigidBody::serializeData() {
    return new json::JsonNull();
}

void RigidBody::deserialize(const json::IJsonObject *data) {
}

RigidBody *RigidBody::clone(IObject *owner) const {
    return new RigidBody(owner);
}

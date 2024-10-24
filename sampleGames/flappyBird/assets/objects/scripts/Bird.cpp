/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#include "Bird.hpp"

Bird::Bird(IObject *owner, const json::IJsonObject *data) : CPPMonoBehaviour(owner)
{
}

void Bird::start()
{
    auto *rigidbody = getParentComponent<RigidBody>();
    rigidbody->_velocity = Vector3(0, 100, 0);
    rigidbody->_acceleration = Vector3(0, 500, 0);
    rigidbody->_terminalVelocity = 500;
    rigidbody->_drag = 10;
    rigidbody->_collider = new Box(Vector3(0, 0, 0), Vector3(10, 60, 0));

    EventSystem::getInstance().registerListener("space_pressed", [this](const EventData& data) {
        if (!isDead) {
            jump();
        }
    });
    EventSystem::getInstance().registerListener("z_pressed", [this](const EventData& data) {
        if (!isDead) {
            jump();
        }
    });
}

void Bird::update()
{
    auto *transform = getParentComponent<Transform>();
    auto *rigidbody = getParentComponent<RigidBody>();
    if (isDead) {
        return;
    }
    if (transform->getPosition().y < 0 || transform->getPosition().y > 1000) {
        die();
    }
    if (const std::vector<IObject *> colliding_objects = rigidbody->collidingObjects(); !colliding_objects.empty()) {
        die();
    }
}

void Bird::jump()
{
    auto *rigidbody = getParentComponent<RigidBody>();
    rigidbody->_velocity = Vector3(0, -jumpForce, 0);
}

void Bird::die()
{
    isDead = true;
    auto *rigidbody = getParentComponent<RigidBody>();
    rigidbody->_velocity = Vector3(0, 100, 0);
    rigidbody->_acceleration = Vector3(0, 1000, 0);
    rigidbody->_terminalVelocity = 0;
    EventSystem::getInstance().triggerEvents("bird_died", nullptr);
}

void Bird::setJumpForce(float newJumpForce)
{
    jumpForce = newJumpForce;
}

float Bird::getJumpForce() const
{
    return jumpForce;
}

IComponent *Bird::clone(IObject *owner) const
{
    auto *comp = new Bird(owner, nullptr);
    comp->jumpForce = jumpForce;
    return comp;
}

void Bird::deserialize(const json::IJsonObject *data)
{
}

void Bird::end()
{
}

json::IJsonObject *Bird::serializeData()
{
    return nullptr;
}

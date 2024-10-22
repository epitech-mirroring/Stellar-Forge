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
    startTime = std::chrono::high_resolution_clock::now();
    actualTime = std::chrono::high_resolution_clock::now();
    auto *transform = getParentComponent<Transform>();
    auto *rigidbody = getParentComponent<RigidBody>();
    rigidbody->_velocity = Vector3(0, 100, 0);
    rigidbody->_acceleration = Vector3(0, 400, 0);
    rigidbody->_terminalVelocity = 500;
    rigidbody->_drag = 10;


    EventSystem::getInstance().registerListener("space_pressed", [this](const EventData& data) {
        if (!isDead) {
            jump();
        }
    });
}

void Bird::update()
{
}

void Bird::jump()
{
    auto *rigidbody = getParentComponent<RigidBody>();
    rigidbody->_velocity = Vector3(0, -jumpForce, 0);
    rigidbody->applyImpulse(Vector3(0, -jumpForce / 4, 0));
}

void Bird::die()
{
    isDead = true;
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

/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#include "Pipes.hpp"

Pipes::Pipes(IObject *owner, const json::IJsonObject *data)
    : CPPMonoBehaviour(owner)
{
}

void Pipes::start()
{
    startTime = std::chrono::system_clock::now();
    actualTime = std::chrono::system_clock::now();
}

#include "graphics/components/Sprite.hpp"

void Pipes::spawnPipe(float offset)
{
    UUID baseUuid;
    baseUuid.setUuidFromString("9a24f7e2-edbb-4e54-a5dc-944454c8c1fd");
    UUID const uuid = ObjectManager::getInstance().duplicateObject(baseUuid);
    IObject *pipe = ObjectManager::getInstance().getObjectById(uuid);
    pipe->setActive(true);
    ObjectManager::getInstance().updateObject(uuid, pipe);
    auto *transform = pipe->getComponent<Transform>();
    auto *rigidbody = pipe->getComponent<RigidBody>();
    rigidbody->_velocity = Vector3(-speed, 0, 0);
    rigidbody->_acceleration = Vector3(0, 0, 0);
    rigidbody->_terminalVelocity = 0;
    rigidbody->_drag = 0;
    if (500 + offset > 0) {
        transform->rotate2D(180);
        rigidbody->_collider = new Box(Vector3(0, 0, 0), Vector3(-140, -890, 0));
        transform->setPosition(Vector3(1500 + 140, 500 + offset + 890, 0));
    } else {
        rigidbody->_collider = new Box(Vector3(0, 0, 0), Vector3(140, 890, 0));
        transform->setPosition(Vector3(1500, 500 + offset, 0));
    }
}

void Pipes::update()
{
    actualTime = std::chrono::system_clock::now();
    if (std::chrono::duration<float, std::chrono::seconds::period>(actualTime - startTime).count() >= spawnRate) {
        // Spawn pipes
        startTime = actualTime;
        const int offset = (rand() % 400) - 200;
        spawnPipe(offset - 150 - 890);
        spawnPipe(offset + 150);
    }
}

void Pipes::setSpeed(float newSpeed)
{
    speed = newSpeed;
}

float Pipes::getSpeed() const
{
    return speed;
}

void Pipes::setSpawnRate(float newSpawnRate)
{
    spawnRate = newSpawnRate;
}

float Pipes::getSpawnRate() const
{
    return spawnRate;
}

IComponent *Pipes::clone(IObject *owner) const
{
    auto *comp = new Pipes(owner, nullptr);
    comp->speed = speed;
    comp->spawnRate = spawnRate;
    return comp;
}

void Pipes::deserialize(const json::IJsonObject *data)
{
}

void Pipes::end()
{
}

json::IJsonObject *Pipes::serializeData()
{
    return nullptr;
}

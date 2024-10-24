/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#include "Pipes.hpp"
#include "graphics/components/Sprite.hpp"

Pipes::Pipes(IObject *owner, const json::IJsonObject *data)
    : CPPMonoBehaviour(owner)
{
}

void Pipes::onGameLost(const EventData& data)
{
    gameLost = true;
    for (auto &pipe : pipes) {
        ObjectManager::getInstance().removeObject(pipe);
    }
}


void Pipes::start()
{
    startTime = std::chrono::system_clock::now();
    actualTime = std::chrono::system_clock::now();
    EventSystem::getInstance().registerListener("bird_died", [this](const EventData& data) {
        onGameLost(data);
    });
}

void Pipes::spawnPipe(float offset)
{
    UUID baseUuid;
    baseUuid.setUuidFromString("9a24f7e2-edbb-4e54-a5dc-944454c8c1fd");
    UUID const uuid = ObjectManager::getInstance().duplicateObject(baseUuid);
    pipes.push_back(uuid);
    IObject *pipe = ObjectManager::getInstance().getObjectById(uuid);
    if (pipe == nullptr) {
        return;
    }
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
        rigidbody->_collider = new Box(Vector3(0, 0, 0), Vector3(-140, -890, -1));
        transform->setPosition(Vector3(2000 + 140, 500 + offset + 890, 1));
    } else {
        rigidbody->_collider = new Box(Vector3(0, 0, 0), Vector3(140, 890, -1));
        transform->setPosition(Vector3(2000, 500 + offset, 1));
    }
}

void Pipes::update()
{
    actualTime = std::chrono::system_clock::now();
    if (std::chrono::duration<float, std::chrono::seconds::period>(actualTime - startTime).count() >= spawnRate && !gameLost) {
        // Spawn pipes
        startTime = actualTime;
        const int offset = (rand() % 400) - 200;
        spawnPipe(static_cast<float>(offset - 150 - 890));
        spawnPipe(static_cast<float>(offset + 150));
    }
    for (auto &pipe : pipes) {
        const auto *object = ObjectManager::getInstance().getObjectById(pipe);
        if (object == nullptr) {
            continue;
        }
        if (auto *transform = object->getComponent<Transform>(); transform->getPosition().x < -200) {
            ObjectManager::getInstance().removeObject(pipe);
            pipes.erase(std::remove(pipes.begin(), pipes.end(), pipe), pipes.end());
        }
    }
}

void Pipes::setSpeed(const float newSpeed)
{
    speed = newSpeed;
}

float Pipes::getSpeed() const
{
    return speed;
}

void Pipes::setSpawnRate(const float newSpawnRate)
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

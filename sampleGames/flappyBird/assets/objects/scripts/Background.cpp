/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** Background.cpp
*/

#include "Background.hpp"

Background::Background(IObject *owner, const json::IJsonObject *data) : CPPMonoBehaviour(owner) {}

void Background::start() {
    startTime = std::chrono::high_resolution_clock::now();
    actualTime = std::chrono::high_resolution_clock::now();
    auto *transform = getParentComponent<Transform>();
    transform->setPosition(Vector3(0, 0, 0));
    EventSystem::getInstance().registerListener("bird_died", [this](const EventData& data) {
        onGameLost(data);
    });
}

void Background::onGameLost(const EventData &data)
{
    gameLost = true;
}

void Background::update() {
    actualTime = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration<float>(actualTime - startTime).count() >= 0.01f && !gameLost) {
        auto *transform = getParentComponent<Transform>();
        transform->setPosition(Vector3(transform->getPosition().x - 5, transform->getPosition().y, -10));
        if (transform->getPosition().x <= -1920) {
            transform->setPosition(Vector3(0, transform->getPosition().y, -10));
        }
        startTime = actualTime;
    }
}

void Background::setSpeed(float newSpeed) {
    speed = newSpeed;
}

float Background::getSpeed() const {
    return speed;
}

IComponent *Background::clone (IObject *owner) const {
    auto *comp = new Background(owner, nullptr);
    comp->speed = speed;
    return comp;
}

void Background::deserialize(const json::IJsonObject *data) {}

void Background::end() {}

json::IJsonObject *Background::serializeData() {
    return nullptr;
}

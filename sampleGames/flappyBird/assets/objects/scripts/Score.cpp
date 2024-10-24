/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** Score.cpp
*/

#include "Score.hpp"

Score::Score(IObject *owner, const json::IJsonObject *data) : CPPMonoBehaviour(owner) {}

void Score::onGameLost(const EventData &data) {
    auto *text = getParentComponent<UIText>();
    text->setText("Game Over! Your score is " + std::to_string(score));
    auto *transform = getParentComponent<Transform>();
    auto *sfText = text->getText();
    sf::FloatRect const getLocalBounds = sfText->getLocalBounds();
    sfText->setOrigin(getLocalBounds.width / 2, 0);
    transform->setPosition(Vector3(1920 / 2, 100, 20));
    gameLost = true;
}

void Score::start() {
    startTime = std::chrono::high_resolution_clock::now();
    actualTime = std::chrono::high_resolution_clock::now();
    score = 0;
    setUITextScore();
    EventSystem::getInstance().registerListener("bird_died", [this](const EventData& data) {
            onGameLost(data);
        });
}

void Score::setUITextScore() {
    auto *text = getParentComponent<UIText>();
    text->setText(std::to_string(score));
    auto *transform = getParentComponent<Transform>();
    auto *sfText = text->getText();
    sf::FloatRect const getLocalBounds = sfText->getLocalBounds();
    sfText->setOrigin(getLocalBounds.width / 2, 0);
    transform->setPosition(Vector3(1920 / 2, 100, 20));
}

void Score::update() {
    actualTime = std::chrono::system_clock::now();
    if (std::chrono::duration<float>(actualTime - startTime).count() >= timeBeforePipe && !gameLost) {
        startTime = actualTime;
        score++;
        setUITextScore();
        timeBeforePipe = 2.0f;
    }
}


IComponent *Score::clone (IObject *owner) const {
    auto *comp = new Score(owner, nullptr);
    return comp;
}

void Score::deserialize(const json::IJsonObject *data) {}

void Score::end() {}

json::IJsonObject *Score::serializeData() {
    return nullptr;
}

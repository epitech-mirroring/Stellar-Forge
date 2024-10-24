/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** Score.hpp
*/

#ifndef SCORE_HPP
#define SCORE_HPP

#include <chrono>
#include "common/components/CPPMonoBehaviour.hpp"
#include "common/components/Transform.hpp"
#include "graphics/components/UIText.hpp"
#include "common/json/JsonObject.hpp"
#include "common/event/EventSystem.hpp"

class Score final : public CPPMonoBehaviour {
public:
    Score(IObject *owner, const json::IJsonObject *data);
    ~Score() override = default;

    void start() override;
    void update() override;

    void setUITextScore();
    void onGameLost(const EventData &data);

    void setScore(const unsigned int newScore) { score = newScore; }
    [[nodiscard]] unsigned int getScore() const { return score; }

    IComponent *clone (IObject *owner) const override;
    void deserialize(const json::IJsonObject *data) override;
    void end() override;
    json::IJsonObject *serializeData() override;
private:
    std::chrono::time_point<std::chrono::system_clock> startTime;
    std::chrono::time_point<std::chrono::system_clock> actualTime;
    unsigned int score = 0;
    float timeBeforePipe = 8.5f;
    bool gameLost = false;
};

#endif //SCORE_HPP

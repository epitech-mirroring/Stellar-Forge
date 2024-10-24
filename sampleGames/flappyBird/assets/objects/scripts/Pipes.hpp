/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#ifndef STELLARFORGE_PIPES_HPP
#define STELLARFORGE_PIPES_HPP

#include <chrono>
#include "common/components/CPPMonoBehaviour.hpp"
#include "common/components/Transform.hpp"
#include "physics/components/RigidBody.hpp"
#include "common/json/JsonObject.hpp"
#include "common/event/EventSystem.hpp"
#include "common/managers/ObjectManager.hpp"
#include "physics/Box.hpp"

class Pipes : public CPPMonoBehaviour {
    public:
        Pipes(IObject *owner, const json::IJsonObject *data);
        ~Pipes() override = default;

        void start() override;
        void update() override;

        void setSpeed(float newSpeed);
        [[nodiscard]] float getSpeed() const;
        void setSpawnRate(float newSpawnRate);
        [[nodiscard]] float getSpawnRate() const;

        void spawnPipe(float offset);

        void onGameLost(const EventData &data);

        IComponent *clone(IObject *owner) const override;
        void deserialize(const json::IJsonObject *data) override;
        void end() override;
        json::IJsonObject *serializeData() override;
    private:
        float speed = 300.0f;
        float spawnRate = 2.00f;
        std::chrono::time_point<std::chrono::system_clock> startTime;
        std::chrono::time_point<std::chrono::system_clock> actualTime;
        std::vector<UUID> pipes;
        bool gameLost = false;
};

#endif //STELLARFORGE_PIPES_HPP

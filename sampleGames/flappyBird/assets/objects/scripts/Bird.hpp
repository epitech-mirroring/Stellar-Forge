/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#ifndef STELLARFORGE_BIRD_HPP
#define STELLARFORGE_BIRD_HPP

#include <chrono>
#include "common/components/CPPMonoBehaviour.hpp"
#include "common/components/Transform.hpp"
#include "physics/components/RigidBody.hpp"
#include "common/json/JsonObject.hpp"
#include "common/event/EventSystem.hpp"

class Bird : public CPPMonoBehaviour {
    public:
        Bird(IObject *owner, const json::IJsonObject *data);
        ~Bird() override = default;

        void start() override;
        void update() override;

        void jump();
        void die();
        void setJumpForce(float newJumpForce);
        [[nodiscard]] float getJumpForce() const;

        IComponent *clone(IObject *owner) const override;
        void deserialize(const json::IJsonObject *data) override;
        void end() override;
        json::IJsonObject *serializeData() override;
    private:
        float jumpForce = 200.0f;
        bool isDead = false;
        std::chrono::time_point<std::chrono::system_clock> startTime;
        std::chrono::time_point<std::chrono::system_clock> actualTime;
};

#endif //STELLARFORGE_BIRD_HPP

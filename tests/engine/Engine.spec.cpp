/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include <gtest/gtest.h>

#include "StellarForge/common/components/DynamicComponentLoader.hpp"
#include "StellarForge/Common/components/Transform.hpp"
#include "StellarForge/Common/managers/ObjectManager.hpp"
#include "StellarForge/Common/managers/SceneManager.hpp"
#include "StellarForge/Engine/Engine.hpp"
#include "StellarForge/Graphics/components/Sprite.hpp"

TEST(Engine, ally) {
    auto engine = Engine([] {
                         }, "test", "./assets/",
                         [](const std::string &/*gameName*/) {
                         });

    ObjectManager const &objectManager = ObjectManager::getInstance();
    const auto objects = objectManager.getObjects();
    ASSERT_EQ(objects.size(), 1);
    ASSERT_EQ(objects.begin()->first.getUuidString(),
              "9f19e43c-990b-4314-a039-d729a1dab876");
    const auto *const object = objects.begin()->second;
    ASSERT_EQ(object->getComponents().size(), 2);
    ASSERT_EQ(object->getComponents().at(0)->getMeta().getName(), "Transform");
    ASSERT_EQ(object->getComponents().at(1)->getMeta().getName(), "Sprite");
    auto *const transform = dynamic_cast<Transform *>(object->getComponents().at(0));
    auto *sprite = dynamic_cast<Sprite *>(object->getComponents().at(1));
    ASSERT_EQ(transform->getPosition().x, 0);
    ASSERT_EQ(transform->getPosition().y, 0);
    ASSERT_EQ(transform->getPosition().z, 0);
    ASSERT_EQ(transform->getScale().x, 1);
    ASSERT_EQ(transform->getScale().y, 1);
    ASSERT_EQ(transform->getScale().z, 1);

    ASSERT_EQ(sprite->getPath(), "./assets/images/ally.png");

    SceneManager const &sceneManager = SceneManager::getInstance();
    const auto scenes = sceneManager.getScenes();
    ASSERT_EQ(scenes.size(), 1);
    ASSERT_EQ(scenes.begin()->first.getUuidString(),
              "4548bf85-6bb2-4ba7-88bf-856bb22ba7d1");
    const auto *const scene = scenes.begin()->second;
    const auto objectsInScene = scene->getObjects();
    ASSERT_EQ(objectsInScene.size(), 1);
    ASSERT_EQ(objectsInScene.at(0)->getMeta().getName(), "Ally");
}

TEST(Engine, dynamicComponentLoader) {
    auto loader = DynamicComponentLoader("./assets/components/");
    auto engine = Engine([&loader]() {
                             loader.loadComponents();
                         }, "test", "./assets/",
                         [](const std::string &/*gameName*/) {
                         });

    ASSERT_TRUE(ComponentFactory::getInstance().hasComponent("Sprite"));
    ASSERT_TRUE(ComponentFactory::getInstance().hasComponent("Test1"));
}

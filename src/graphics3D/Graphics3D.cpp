/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** Graphics3D.cpp
*/

#include "Graphics3D.hpp"
#include "common/event/EventSystem.hpp"
#include "common/managers/SceneManager.hpp"
#include "common/components/Transform.hpp"
#include "components/I3DGraphicsComponent.hpp"
#include "common/IObject.hpp"
#include "common/VirtualObject.hpp"
#include <algorithm>

Graphics3D::Graphics3D(const int width, const int height, const std::string &title, const bool precharge)
    : width(width), height(height), title(title), prepared(false), precharge(precharge), camera() {
    InitWindow(width, height, title.c_str());
    if (!IsWindowReady()) {
        throw std::runtime_error("Failed to create window");
    }
    prepared = true;
    SetTargetFPS(60);
    EventSystem::getInstance().triggerEvents("window_created", nullptr);
    camera.position = {0.0f, 10.0f, 10.0f};
    camera.target = {0.0f, 0.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};

}

Graphics3D::~Graphics3D() {
    close();
}

template<typename T>
static T *getObjComponent(IObject *object) {
    for (auto *component: object->getComponents()) {
        if (auto *comp = dynamic_cast<T *>(component)) {
            return comp;
        }
    }
    return nullptr;
}

void Graphics3D::render(const std::function<void(IObject *)> &updateFunction) {
    if (!prepared) {
        return;
    }

    const IScene *currentScene = SceneManager::getInstance().getCurrentScene();
    if (currentScene == nullptr) {
        return;
    }
    std::cout << "Rendering scene" << std::endl;
    catchEvents();
    BeginDrawing();
    ClearBackground(BLACK);
    std::cout << "Rendering objects" << std::endl;

    sortedObjects = currentScene->getObjects();
    std::sort(sortedObjects.begin(), sortedObjects.end(),
              [](IObject *obja, IObject *objb) {
                  auto *aTransform = getObjComponent<Component::Transform>(obja);
                  auto *bTransform = getObjComponent<Component::Transform>(objb);
                  if (aTransform == nullptr || bTransform == nullptr) {
                      return false;
                  }
                  return aTransform->getPosition().z < bTransform->getPosition().z;
              });
    std::cout << "Sorted objects" << std::endl;
    for (auto *object : sortedObjects) {
        if (!object->isActive()) {
            continue;
        }
        std::cout << "Before update, object name: " << object->getMeta().getName() << std::endl;
        //updateFunction(object);
        std::cout << "After update" << std::endl;
        for (auto *const component: object->getComponents()) {
            if (auto *graphicsComponent = dynamic_cast<I3DGraphicsComponent *>(component)) {
                std::cout << "Rendering object" << std::endl;
                graphicsComponent->render(camera);
                std::cout << "Object redered" << std::endl;
            }
        }
    }
    std::cout << "Rendering done" << std::endl;
    EndDrawing();
}

void Graphics3D::catchEvents() {
    if (WindowShouldClose()) {
        close();
    }
    for (int key = 0; key <= 350; ++key) {
        if (IsKeyPressed(key)) {
            EventSystem::getInstance().triggerEvents(std::to_string(key) + "_pressed", nullptr);
        }
        if (IsKeyReleased(key)) {
            EventSystem::getInstance().triggerEvents(std::to_string(key) + "_released", nullptr);
        }
    }
}

void Graphics3D::close() {
    if (IsWindowReady()) {
        CloseWindow();
        prepared = false;
        EventSystem::getInstance().triggerEvents("window_closed", nullptr);
    }
}
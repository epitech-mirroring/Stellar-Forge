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
    camera = {0};
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

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
    catchEvents();
    if (WindowShouldClose()) {
        return;
    }
    UpdateCamera(&camera);
    BeginDrawing();
    ClearBackground(BLACK);

    sortedObjects = currentScene->getObjects();
    std::sort(sortedObjects.begin(), sortedObjects.end(),
              [](IObject *obja, IObject *objb) {
                  auto *aTransform = getObjComponent<Transform>(obja);
                  auto *bTransform = getObjComponent<Transform>(objb);
                  if (aTransform == nullptr || bTransform == nullptr) {
                      return false;
                  }
                  return aTransform->getPosition().z < bTransform->getPosition().z;
              });
    for (auto *object : sortedObjects) {
        if (!object->isActive()) {
            continue;
        }
        updateFunction(object);
        for (auto *const component: object->getComponents()) {
            if (auto *graphicsComponent = dynamic_cast<I3DGraphicsComponent *>(component)) {
                graphicsComponent->render(&camera);
            }
        }
    }
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
    prepared = false;
    EventSystem::getInstance().triggerEvents("window_closed", nullptr);
    CloseWindow();
}
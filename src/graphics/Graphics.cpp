/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Graphics.hpp"
#include "GraphicsException.hpp"
#include <iostream>
#include <algorithm>
#include <algorithmfwd.h>

Graphics::Graphics(int width, int height, const char *title, bool precharge)
    : width(width), height(height), title(title), precharge(precharge),
    window(sf::VideoMode(width, height), title), currentScene(nullptr), prepared(false)
{
    if (!window.isOpen()) {
        throw GraphicsException("Failed to create window");
    }
    prepared = true;
    window.setFramerateLimit(60);
    sortedObjects.reserve(100);
}

Graphics::~Graphics() {
    clean();
}

static void Graphics::addAndSortObject(IObject *object) {
    const float zValue = 0.0f;
    
    for (auto& component : object->getComponents()) {
        if (auto* transform = dynamic_cast<Transform *>(component.get())) {
            zValue = transform->getPosition().z;
            break;
        }
    }

    auto insertPos = sortedObjects.begin();
    for (; insertPos != sortedObjects.end(); ++insertPos) {
        const float currentZValue = 0.0f;

        for (auto& component : (*insertPos)->getComponents()) {
            if (auto* transform = dynamic_cast<Transform *>(component.get())) {
                currentZValue = transform->getPosition().z;
                break;
            }
        }
        if (zValue < currentZValue) {
            break;
        }
    }

    sortedObjects.insert(insertPos, object);
}

void Graphics::clear() {
    window.clear(sf::Color::Black);
}

void Graphics::present() {
    window.display();
}

void Graphics::render(void updateComponent(IObject *object)) {
    if (!prepared) {
        return;
    }
    clear();

    std::vector<IObject *> objects = currentScene->getObjects();
    for (auto object : objects) {
        addAndSortObject(object);
    }
    for (auto object : sortedObjects) {
        for (auto& component : object->getComponents()) {
            updateComponent(object);
            if (auto* graphicsComponent = dynamic_cast<IGraphicsComponent *>(component.get())) {
                graphicsComponent->render(window);
            }
        }
    }

    present();
}

void Graphics::clean() {
    window.close();
}

void Graphics::setScene(IScene *scene) {
    currentScene = scene;
    for (auto object : sortedObjects) {
        delete object;
    }
}

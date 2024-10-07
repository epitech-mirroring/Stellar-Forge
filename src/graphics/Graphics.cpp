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

class TransformComponent; // TODO replace with actual TransformComponent

Graphics::Graphics(int width, int height, const char *title, bool precharge)
    : width(width), height(height), title(title), precharge(precharge), initialized(false), currentScene(nullptr)
{
    window.create(sf::VideoMode(width, height), title);
    initialize();
}

Graphics::~Graphics() {
    clean();
}

void Graphics::addAndSortObject(IObject *object) {
    float zValue = 0.0f;
    
    for (auto& component : object->getComponents()) {
        /*if (auto* transform = dynamic_cast<TransformComponent*>(component.get())) {
            zValue = transform->getPosition().z;
            break;
        }*/
    }

    auto insertPos = sortedObjects.begin();
    for (; insertPos != sortedObjects.end(); ++insertPos) {
        float currentZValue = 0.0f;

        for (auto& component : (*insertPos)->getComponents()) {
            /*if (auto* transform = dynamic_cast<TransformComponent*>(component.get())) {
                currentZValue = transform->getPosition().z;
                break;
            }*/
        }
        if (zValue < currentZValue) {
            break;
        }
    }

    sortedObjects.insert(insertPos, object);
}


void Graphics::initialize() {
    if (!window.isOpen()) {
        throw GraphicsException("Failed to create window");
    }
    initialized = true;
}

void Graphics::clear() {
    window.clear(sf::Color::Black);
}

void Graphics::present() {
    window.display();
}

void Graphics::render() {
    if (!initialized) return;
    clear();

    std::vector<IObject *> objects = currentScene->getObjects();
    for (auto object : objects) {
        addAndSortObject(object);
    }
    for (auto object : sortedObjects) {
        for (auto& component : object->getComponents()) {
            /*if (component->getMeta() == "graphics") {
                auto* graphicsComponent = dynamic_cast<IGraphicsComponent*>(component.get());
                graphicsComponent->render(renderer);
            }*/
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

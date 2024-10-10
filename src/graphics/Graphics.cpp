/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Graphics.hpp"

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
    close();
}

void Graphics::addAndSortObject(IObject *object) {
    float zValue = 0.0f;
    
    for (auto& component : object->getComponents()) {
        if (auto* transform = dynamic_cast<Transform *>(component)) {
            zValue = transform->getPosition().z;
            break;
        }
    }

    auto insertPos = sortedObjects.begin();
    for (; insertPos != sortedObjects.end(); ++insertPos) {
        float currentZValue = 0.0f;

        for (auto& component : (*insertPos)->getComponents()) {
            if (auto* transform = dynamic_cast<Transform *>(component)) {
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

void Graphics::render(const std::function<void(IObject *)> &updateFunction) {
    if (!prepared) {
        return;
    }
    clear();

    const std::vector<IObject *> objects = currentScene->getObjects();
    for (auto *object : objects) {
        addAndSortObject(object);
    }
    for (auto *object : sortedObjects) {
        for (auto& component : object->getComponents()) {
            updateFunction(object);
            if (auto* graphicsComponent = dynamic_cast<IGraphicsComponent *>(component)) {
                graphicsComponent->render(&window);
            }
        }
    }

    present();
}

void Graphics::close() {
    window.close();
    prepared = false;
}

void Graphics::setScene(IScene *scene) {
    currentScene = scene;
    sortedObjects.clear();
}

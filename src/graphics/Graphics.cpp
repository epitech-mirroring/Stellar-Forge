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
}

Graphics::Graphics(int width, int height, const char *title, bool precharge)
    : window(nullptr), renderer(nullptr), width(width), height(height), title(title), initialized(false), precharge(precharge) {
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
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw GraphicsException("SDL_Init Error: " + std::string(SDL_GetError()));
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        throw GraphicsException("SDL_CreateWindow Error: " + std::string(SDL_GetError()));
        SDL_Quit();
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(window);
        throw GraphicsException("SDL_CreateRenderer Error: " + std::string(SDL_GetError()));
        SDL_Quit();
        return;
    }

    initialized = true;
}

void Graphics::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Graphics::present() {
    SDL_RenderPresent(renderer);
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
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

void Graphics::setScene(IScene *scene) {
    currentScene = scene;
    for (auto object : sortedObjects) {
        delete object;
    }
}

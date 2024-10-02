/*
** EPITECH PROJECT, 2024
** components
** File description:
** SpriteComponent.cpp
**/

#include "SpriteComponent.hpp"

SpriteComponent::SpriteComponent(const char *path) : path(path)
{
    texture = nullptr;
}

SpriteComponent::~SpriteComponent()
{
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void SpriteComponent::render(SDL_Renderer *renderer)
{
    if (!texture) {
        IMG_LoadTexture(renderer, path);
        if (!texture) {
            throw GraphicsException("IMG_LoadTexture Error: " + std::string(IMG_GetError()));
    }
    }
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}

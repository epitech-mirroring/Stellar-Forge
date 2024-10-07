/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** SpriteComponent.cpp
**/

#include "SpriteComponent.hpp"

using TransformComponent = TransformComponent; //TODO import Transform component

SpriteComponent::SpriteComponent(const char *path) : path(path)
{
    if (!texture.loadFromFile(path)) {
        throw GraphicsException("Failed to load texture from file: " + std::string(path));
    }
    sprite.setTexture(texture);
    AField field = AField("path", "path to the sprite image", IComponent::IMeta::IField::FieldType::STRING);
    AFieldGroup fieldGroup = AFieldGroup("path", "path to the sprite image", {&field});
    meta = AMeta("sprite", "sprite component", true, false, {&fieldGroup});
}

void SpriteComponent::render(sf::RenderWindow *window)
{
    for (auto &component : this->getOwner()->getComponents()) {
        if (component->getMeta().getName() == "transform") {
            auto transformComponent = dynamic_cast<TransformComponent *>(component);
            sprite.setPosition(transformComponent->getPosition());
            sprite.setRotation(transformComponent->getRotation().x);
            window->draw(sprite);
        }
    }
}

void SpriteComponent::setTexture(const char *path)
{
    if (!texture.loadFromFile(path)) {
        throw GraphicsException("Failed to load texture from file: " + std::string(path));
    }
    sprite.setTexture(texture);
}

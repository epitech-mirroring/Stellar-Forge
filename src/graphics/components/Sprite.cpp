/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** Sprite.cpp
**/

#include "Sprite.hpp"

Sprite::Sprite(const char *path) : path(path)
{
    if (!texture.loadFromFile(path)) {
        throw GraphicsException("Failed to load texture from file: " + std::string(path));
    }
    sprite.setTexture(texture);
    AField field = AField("path", "path to the sprite image", IComponent::IMeta::IField::FieldType::STRING);
    AFieldGroup fieldGroup = AFieldGroup("path", "path to the sprite image", {&field});
    meta = AMeta("sprite", "sprite component", true, false, {&fieldGroup});
}

void Sprite::render(sf::RenderWindow *window)
{
    for (auto &component : this->getOwner()->getComponents()) {
        if (component->getMeta().getName() == "Transform") {
            auto transformComponent = dynamic_cast<Transform *>(component);
            sprite.setPosition(transformComponent->getPosition().x, transformComponent->getPosition().y);
            sprite.setRotation(transformComponent->getRotation().x);
            sprite.setScale(transformComponent->getScale().x, transformComponent->getScale().y);
            window->draw(sprite);
        }
    }
}

void Sprite::setTexture(const char *path)
{
    if (!texture.loadFromFile(path)) {
        throw GraphicsException("Failed to load texture from file: " + std::string(path));
    }
    sprite.setTexture(texture);
}

glm::vec2 Sprite::getSize()
{
    return glm::vec2(texture.getSize().x, texture.getSize().y);
}

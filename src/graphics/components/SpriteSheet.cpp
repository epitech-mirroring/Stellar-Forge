/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** SpriteSheet.cpp
**/

#include "SpriteSheet.hpp"

SpriteSheet::SpriteSheet(IObject* owner, const char *path, std::vector<sf::IntRect> frames, int frame) : AGraphicsComponent(owner), path(path), frames(frames), currentFrame(frame)
{
    if (!texture.loadFromFile(path)) {
        throw GraphicsException("Failed to load texture from file: " + std::string(path));
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(frames[currentFrame]);
}

void SpriteSheet::render(sf::RenderWindow *window)
{
    for (auto &component : this->getOwner()->getComponents()) {
        if (component->getMeta().getName() == "Transform") {
            auto transformComponent = dynamic_cast<Transform *>(component);
            if (transformComponent) {
                sprite.setPosition(transformComponent->getPosition().x, transformComponent->getPosition().y);
                sprite.setRotation(transformComponent->getRotation().x);
                sprite.setScale(transformComponent->getScale().x, transformComponent->getScale().y);
                sprite.setTextureRect(frames[currentFrame]);
                window->draw(sprite);
            }
        }
    }
}

void SpriteSheet::setTexture(const char *path)
{
    if (!texture.loadFromFile(path)) {
        throw GraphicsException("Failed to load texture from file: " + std::string(path));
    }
    sprite.setTexture(texture);
}

void SpriteSheet::setFrames(std::vector<sf::IntRect> frames)
{
    this->frames = frames;
}

void SpriteSheet::setFrame(unsigned int frame)
{
    currentFrame = frame;
    sprite.setTextureRect(frames[currentFrame]);
}

void SpriteSheet::nextFrame()
{
    currentFrame++;
    if (currentFrame >= frames.size()) {
        currentFrame = 0;
    }
    sprite.setTextureRect(frames[currentFrame]);
}

void SpriteSheet::prevFrame()
{
    currentFrame--;
    if (currentFrame < 0) {
        currentFrame = frames.size() - 1;
    }
    sprite.setTextureRect(frames[currentFrame]);
}

SpriteSheet::Meta::Meta(): AMeta("SpriteSheet", "A sprite sheet component that renders a sprite sheet on the screen", true, false, {
    new InvisibleFieldGroup({ new AField("path", "path to the sprite sheet image", IComponent::IMeta::IField::FieldType::STRING)}),
    new IntRectFieldGroup("currentFrame", "The current frame of the sprite sheet"), //TODO list all the frames
})
{
}

/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** AnimatedSprite.cpp
**/

#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite(IObject* owner, const char *path, std::vector<sf::IntRect> frames, float frameTime, unsigned int currentFrame)
    : AGraphicsComponent(owner), path(path), frames(frames), frameTime(frameTime), currentFrame(currentFrame)
{
    if (!texture.loadFromFile(path)) {
        throw GraphicsException("Failed to load texture from file: " + std::string(path));
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(frames[currentFrame]);
}

void AnimatedSprite::runComponent()
{
    if (clock.getElapsedTime().asSeconds() >= frameTime) {
        nextFrame();
        clock.restart();
    }
}

void AnimatedSprite::render(sf::RenderWindow *window)
{
    auto *transformComponent = dynamic_cast<Transform *>(findOwnerTransform());
    if (transformComponent != nullptr) {
        sprite.setPosition(transformComponent->getPosition().x, transformComponent->getPosition().y);
        sprite.setRotation(transformComponent->getRotation().x);
        sprite.setScale(transformComponent->getScale().x, transformComponent->getScale().y);
        sprite.setTextureRect(frames[currentFrame]);
        window->draw(sprite);
    }
}

void AnimatedSprite::setTexture(const char *path)
{
    if (!texture.loadFromFile(path)) {
        throw GraphicsException("Failed to load texture from file: " + std::string(path));
    }
    sprite.setTexture(texture);
}

void AnimatedSprite::setFrames(std::vector<sf::IntRect> frames)
{
    this->frames = std::move(frames);
}

void AnimatedSprite::setFrame(unsigned int frame)
{
    if (frame >= frames.size()) {
        throw GraphicsException("Frame index out of range");
    }
    currentFrame = frame;
    sprite.setTextureRect(frames[currentFrame]);
}

void AnimatedSprite::nextFrame()
{
    currentFrame++;
    if (currentFrame >= frames.size()) {
        currentFrame = 0;
    }
    sprite.setTextureRect(frames[currentFrame]);
}

void AnimatedSprite::prevFrame()
{
    currentFrame--;
    if (currentFrame < 0) {
        currentFrame = (unsigned int) frames.size() - 1;
    }
    sprite.setTextureRect(frames[currentFrame]);
}

void AnimatedSprite::setFrameTime(float frameTime)
{
    this->frameTime = frameTime;
}

glm::vec2 AnimatedSprite::getSize()
{
    return {frames[currentFrame].width, frames[currentFrame].height};
}

AnimatedSprite::Meta::Meta(): AMeta("AnimatedSprite", "A sprite sheet component that renders a sprite sheet on the screen", true, false, {
    new InvisibleFieldGroup({ new AField("path", "path to the sprite sheet image", IComponent::IMeta::IField::FieldType::STRING)}),
    new IntRectFieldGroup("currentFrame", "The current frame of the sprite sheet"), //TODO list all the frames
})
{
}

/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** AnimatedSprite.cpp
**/

#include "AnimatedSprite.hpp"

#include "common/components/Transform.hpp"
#include "common/fields/FileField.hpp"
#include "common/json/JsonArray.hpp"
#include "common/json/JsonNull.hpp"
#include "common/json/JsonNumber.hpp"
#include "common/json/JsonString.hpp"
#include "graphics/GraphicsException.hpp"

AnimatedSprite::AnimatedSprite(IObject *owner, const std::string &path,
                               const std::vector<sf::IntRect> &frames,
                               const float frameTime,
                               const unsigned int currentFrame)
    : AComponent(owner, new Meta(this)), frames(frames), currentFrame(currentFrame),
      frameTime(frameTime),
      path(path) {
    if (!texture.loadFromFile(path)) {
        throw GraphicsException("Failed to load texture from file: " + std::string(path));
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(frames[currentFrame]);
}

AnimatedSprite::AnimatedSprite(IObject *owner, const json::JsonObject *data): AComponent(
        owner, new Meta(this), data), frames({}), currentFrame(0), frameTime(0.1f) {
    this->deserializeFields(data);
    if (!texture.loadFromFile(path)) {
        throw GraphicsException("Failed to load texture from file: " + std::string(path));
        // Todo: add sample texture and only log error
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(frames[currentFrame]);
}


void AnimatedSprite::runComponent() {
    if (clock.getElapsedTime().asSeconds() >= frameTime) {
        nextFrame();
        clock.restart();
    }
}

void AnimatedSprite::render(sf::RenderWindow *window) {
    const auto *transformComponent = getParentComponent<Transform>();
    if (transformComponent != nullptr) {
        sprite.setPosition(transformComponent->getPosition().x,
                           transformComponent->getPosition().y);
        sprite.setRotation(transformComponent->getRotation().x);
        sprite.setScale(transformComponent->getScale().x,
                        transformComponent->getScale().y);
        sprite.setTextureRect(frames[currentFrame]);
        window->draw(sprite);
    }
}

void AnimatedSprite::setTexture(const std::string &path) {
    if (!texture.loadFromFile(path)) {
        throw GraphicsException("Failed to load texture from file: " + std::string(path));
    }
    sprite.setTexture(texture);
}

void AnimatedSprite::setFrames(std::vector<sf::IntRect> frames) {
    this->frames = std::move(frames);
}

void AnimatedSprite::setFrame(const unsigned int frame) {
    if (frame >= frames.size()) {
        throw GraphicsException("Frame index out of range");
    }
    currentFrame = frame;
    sprite.setTextureRect(frames[currentFrame]);
}

void AnimatedSprite::nextFrame() {
    currentFrame++;
    if (currentFrame >= frames.size()) {
        currentFrame = 0;
    }
    sprite.setTextureRect(frames[currentFrame]);
}

void AnimatedSprite::prevFrame() {
    currentFrame--;
    if (currentFrame < 0) {
        currentFrame = static_cast<unsigned int>(frames.size()) - 1;
    }
    sprite.setTextureRect(frames[currentFrame]);
}

void AnimatedSprite::setFrameTime(const float frameTime) {
    this->frameTime = frameTime;
}

glm::vec2 AnimatedSprite::getSize() {
    return {frames[currentFrame].width, frames[currentFrame].height};
}

AnimatedSprite::Meta::Meta(AnimatedSprite *owner): IMeta(), _owner(owner),
                                                   _fieldGroup({}) {
    auto fields = std::vector<IField *>();
    auto *field = new FileField("Sprite", "The sprite file to use",
                                [this](const std::string &value) {
                                    this->_owner->path = value;
                                    this->_owner->setTexture(value);
                                },
                                [this] { return this->_owner->path; });
    fields.push_back(field);
    this->_fieldGroup = InvisibleFieldGroup(fields);
}

std::string AnimatedSprite::Meta::getName() const {
    return "Animated Sprite";
}

std::string AnimatedSprite::Meta::getDescription() const {
    return "Animate a sprite on the screen";
}

bool AnimatedSprite::Meta::isUnique() const {
    return false;
}

bool AnimatedSprite::Meta::canBeRemoved() const {
    return true;
}

std::vector<const IComponent::IMeta::IFieldGroup *>
AnimatedSprite::Meta::getFieldGroups() const {
    return {&_fieldGroup};
}

void AnimatedSprite::deserialize(const json::IJsonObject *data) {
}

json::IJsonObject *AnimatedSprite::serializeData() {
    return new json::JsonNull();
}

AnimatedSprite *AnimatedSprite::clone(IObject *owner) const {
    return new AnimatedSprite(owner, path, frames, frameTime, currentFrame);
}

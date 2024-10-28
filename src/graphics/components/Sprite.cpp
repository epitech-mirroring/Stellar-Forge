/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** Sprite.cpp
**/

#include "Sprite.hpp"

#include "common/components/Transform.hpp"
#include "common/fields/FileField.hpp"
#include "common/json/JsonNull.hpp"
#include "common/json/JsonString.hpp"
#include "graphics/GraphicsException.hpp"

Sprite::Sprite(IObject *owner, const std::string &path) : AComponent(
                                                              owner, new Meta(this)),
                                                          path(path) {
    if (!texture.loadFromFile(path)) {
        throw GraphicsException("Failed to load texture from file: " + std::string(path));
    }
    sprite.setTexture(texture);
}

Sprite::Sprite(IObject *owner, const json::JsonObject *data) : AComponent(
    owner, new Meta(this), data) {
    this->deserializeFields(data);
    if (!texture.loadFromFile(path)) {
        throw GraphicsException("Failed to load texture from file: " + std::string(path));
    }
    sprite.setTexture(texture);
}

void Sprite::render(sf::RenderWindow *window) {
    const auto *transformComponent = getParentComponent<Transform>();
    if (transformComponent != nullptr) {
        sprite.setPosition(transformComponent->getPosition().x,
                           transformComponent->getPosition().y);
        sprite.setRotation(transformComponent->getRotation2D());
        sprite.setScale(transformComponent->getScale().x,
                        transformComponent->getScale().y);
        window->draw(sprite);
    }
}

void Sprite::setTexture(const std::string &path) {
    if (!texture.loadFromFile(path)) {
        throw GraphicsException("Failed to load texture from file: " + std::string(path));
    }
    sprite.setTexture(texture);
}

glm::vec2 Sprite::getSize() {
    return {texture.getSize().x, texture.getSize().y};
}

void Sprite::runComponent() {
}

Sprite::Meta::Meta(Sprite *owner): _owner(owner), _fieldGroup({}) {
    auto fields = std::vector<IField *>();
    auto *field = new FileField("Texture", "The texture file to use",
                                [this](const std::string &value) {
                                    this->_owner->path = value;
                                    this->_owner->setTexture(value);
                                },
                                [this] { return this->_owner->path; });
    fields.push_back(field);
    this->_fieldGroup = InvisibleFieldGroup(fields);
}

std::string Sprite::Meta::getName() const {
    return "Sprite";
}

std::string Sprite::Meta::getDescription() const {
    return "The Sprite component is used to render a static image on the screen.";
}

bool Sprite::Meta::isUnique() const {
    return false;
}

bool Sprite::Meta::canBeRemoved() const {
    return true;
}

std::vector<const IComponent::IMeta::IFieldGroup *> Sprite::Meta::getFieldGroups() const {
    return {&_fieldGroup};
}

json::IJsonObject *Sprite::serializeData() {
    return new json::JsonNull();
}

void Sprite::deserialize(const json::IJsonObject *data) {
}

Sprite *Sprite::clone(IObject *owner) const {
    return new Sprite(owner, path);
}

std::string Sprite::getPath() const {
    return path;
}

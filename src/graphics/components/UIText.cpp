/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** UIText.cpp
**/

#include "UIText.hpp"

#ifndef __APPLE__
#include <utility>
#endif
#include "common/components/Transform.hpp"
#include "common/fields/StringField.hpp"
#include "common/json/JsonNull.hpp"
#include "common/json/JsonNumber.hpp"
#include "graphics/GraphicsException.hpp"
#include "common/fields/ColorField.hpp"

UIText::UIText(IObject *owner, std::string textStr, const unsigned int size, sf::Color *color, const std::string &fontPath)
    : AComponent(owner, new Meta(this)), textString(std::move(textStr)),
      fontPath(fontPath),
      fontSize(size), color(color) {
    if (std::string(fontPath) == "default") {
        this->fontPath = findDefaultFontPath();
    }
    if (!font.loadFromFile(fontPath)) {
        throw GraphicsException(
            "Failed to load font from file: " + std::string(fontPath));
    }
    text.setFont(font);
    text.setString(textString);
    text.setCharacterSize(fontSize);
    text.setFillColor(*color);
}

UIText::UIText(IObject *owner, const json::JsonObject *data): AComponent(
        owner, new Meta(this), data), fontPath(findDefaultFontPath()),
    fontSize(0), color(new sf::Color(sf::Color::White)) {
    this->deserializeFields(data);
    if (std::string(fontPath) == "default") {
        this->fontPath = findDefaultFontPath();
    }
    if (!font.loadFromFile(fontPath)) {
        throw GraphicsException(
            "Failed to load font from file: " + std::string(fontPath));
    }
    text.setFont(font);
    text.setString(textString);
    text.setCharacterSize(fontSize);
    text.setFillColor(*color);
}

std::string UIText::findDefaultFontPath() {
#ifdef _WIN32
        return "C:\\Windows\\Fonts\\arial.ttf";
#elif defined(__linux__)
        return "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
#else
    throw GraphicsException("Unknown OS: No default font available");
#endif
}

void UIText::render(sf::RenderWindow *window) {
    const auto *transformComponent = getParentComponent<Transform>();
    if (transformComponent != nullptr) {
        text.setPosition(transformComponent->getPosition().x,
                         transformComponent->getPosition().y);
        text.setRotation(transformComponent->getRotation().x);
        text.setScale(transformComponent->getScale().x,
                      transformComponent->getScale().y);
        window->draw(text);
    }
}

void UIText::setText(const std::string &textStr) {
    textString = textStr;
    text.setString(textString);
}

void UIText::setFont(const std::string &fontPath) {
    if (!font.loadFromFile(fontPath)) {
        throw GraphicsException(
            "Failed to load font from file: " + std::string(fontPath));
    }
    text.setFont(font);
    this->fontPath = fontPath;
}

void UIText::setSize(const unsigned int size) {
    if (size <= 0) {
        throw GraphicsException("Font size must be greater than 0");
    }
    fontSize = size;
    text.setCharacterSize(fontSize);
}

void UIText::setColor(sf::Color *color) {
    this->color = color;
    text.setFillColor(*color);
}

glm::vec2 UIText::getSize() {
    return {text.getGlobalBounds().width, text.getGlobalBounds().height};
}

void UIText::runComponent() {
}

UIText::Meta::Meta(UIText *owner)
    : IMeta(), _owner(owner), _fieldGroup({}) {
    auto fields = std::vector<IField *>();
    auto *field = new StringField("Text", "The text to display",
                                  [this](const std::string &value) {
                                      this->_owner->setText(value);
                                  },
                                  [this] { return this->_owner->textString; });
    auto *colorField = new ColorField("Color", "The color of the cube",
        [this](const std::vector<unsigned char> &color) {
            this->_owner->color = new sf::Color();
            this->_owner->color->r = color[0];
            this->_owner->color->g = color[1];
            this->_owner->color->b = color[2];
            this->_owner->color->a = color[3];
         }, [this] {
             return std::vector{
                 this->_owner->color->r,
                 this->_owner->color->g,
                 this->_owner->color->b,
                 this->_owner->color->a
             };
         });
    _fieldGroup = InvisibleFieldGroup({field, colorField});
}

std::string UIText::Meta::getName() const {
    return "UIText";
}

std::string UIText::Meta::getDescription() const {
    return "The UIText component is used to render text on the screen.";
}

bool UIText::Meta::isUnique() const {
    return false;
}

bool UIText::Meta::canBeRemoved() const {
    return true;
}

std::vector<const IComponent::IMeta::IFieldGroup *>
UIText::Meta::getFieldGroups() const {
    return {&_fieldGroup};
}

json::IJsonObject *UIText::serializeData() {
    return new json::JsonNull();
}

void UIText::deserialize(const json::IJsonObject *data) {
}

UIText *UIText::clone(IObject *owner) const {
    return new UIText(owner, textString, fontSize, color, fontPath);
}

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
#include "StellarForge/Common/components/Transform.hpp"
#include "StellarForge/Common/fields/StringField.hpp"
#include "StellarForge/Common/json/JsonNull.hpp"
#include "StellarForge/Common/json/JsonNumber.hpp"
#include "../GraphicsException.hpp"

UIText::UIText(IObject *owner, std::string textStr, const unsigned int size,
               const sf::Color color, const std::string &fontPath)
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
    text.setFillColor(color);
}

UIText::UIText(IObject *owner, const json::JsonObject *data): AComponent(
        owner, new Meta(this), data), fontPath(findDefaultFontPath()),
    fontSize(0), color(sf::Color::White) {
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
    text.setFillColor(color);
}

std::string UIText::findDefaultFontPath() {
#ifdef _WIN32
        return "C:\\Windows\\Fonts\\arial.ttf";
#elif defined(__linux__)
        return "/usr/share/fonts/liberation-sans/LiberationSans-Regular.ttf";
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
        text.setStyle(sf::Text::Regular);
        window->draw(text);
    }
}

sf::Text *UIText::getText() {
    return &text;
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

void UIText::setColor(const sf::Color color) {
    this->color = color;
    text.setFillColor(color);
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
    _fieldGroup = InvisibleFieldGroup({field});
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

json::IJsonObject *UIText::serializeData() const {
    return new json::JsonNull();
}

void UIText::deserialize(const json::IJsonObject *data) {
}

UIText *UIText::clone(IObject *owner) const {
    return new UIText(owner, textString, fontSize, color, fontPath);
}

using LuaType = LuaCpp::Engine::LuaType;
using LuaTNumber = LuaCpp::Engine::LuaTNumber;
using LuaTNil = LuaCpp::Engine::LuaTNil;
using LuaTString = LuaCpp::Engine::LuaTString;

std::shared_ptr<LuaType> UIText::getValue(std::string &key) {
    if (key == "text") {
        return std::make_shared<LuaTString>(textString);
    }
    if (key == "size") {
        return std::make_shared<LuaTNumber>(fontSize);
    }
    if (key == "color") {
        return std::make_shared<LuaTNumber>(color.toInteger());
    }
    if (key == "colorR") {
        return std::make_shared<LuaTNumber>(color.r);
    }
    if (key == "colorG") {
        return std::make_shared<LuaTNumber>(color.g);
    }
    if (key == "colorB") {
        return std::make_shared<LuaTNumber>(color.b);
    }
    if (key == "colorA") {
        return std::make_shared<LuaTNumber>(color.a);
    }
    return std::make_shared<LuaTNil>();
}

void UIText::setValue(std::string &key, std::shared_ptr<LuaType> value) {
    if (key == "text") {
        textString = std::dynamic_pointer_cast<LuaTString>(value)->getValue();
    }
    if (key == "size") {
        fontSize = std::dynamic_pointer_cast<LuaTNumber>(value)->getValue();
    }
    if (key == "color") {
        color = sf::Color(std::dynamic_pointer_cast<LuaTNumber>(value)->getValue());
    }
    if (key == "colorR") {
        color.r = std::dynamic_pointer_cast<LuaTNumber>(value)->getValue();
    }
    if (key == "colorG") {
        color.g = std::dynamic_pointer_cast<LuaTNumber>(value)->getValue();
    }
    if (key == "colorB") {
        color.b = std::dynamic_pointer_cast<LuaTNumber>(value)->getValue();
    }
    if (key == "colorA") {
        color.a = std::dynamic_pointer_cast<LuaTNumber>(value)->getValue();
    }
    text.setFillColor(color);
    text.setString(textString);
    text.setCharacterSize(fontSize);
}
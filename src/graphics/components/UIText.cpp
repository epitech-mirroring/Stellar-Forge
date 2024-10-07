/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** UIText.cpp
**/

#include "UIText.hpp"

UIText::UIText(IObject* owner, const char *textStr, int size, sf::Color color, const char *fontPath)
    : AGraphicsComponent(owner), textString(textStr), fontSize(size), color(color), fontPath(fontPath)
{
    if (std::string(fontPath) == "default") {
        #ifdef _WIN32
            fontPath = "C:\\Windows\\Fonts\\arial.ttf";
        #elif defined(__linux__)
            fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
        #else
            throw GraphicsException("Unknown OS: No default font available");
        #endif
    }
    if (!font.loadFromFile(fontPath)) {
        throw GraphicsException("Failed to load font from file: " + std::string(fontPath));
    }
    text.setFont(font);
    text.setString(textString);
    text.setCharacterSize(fontSize);
    text.setFillColor(color);
}

void UIText::render(sf::RenderWindow *window)
{
    for (auto &component : this->getOwner()->getComponents()) {
        if (component->getMeta().getName() == "Transform") {
            auto transformComponent = dynamic_cast<Transform *>(component);
            if (transformComponent) {
                text.setPosition(transformComponent->getPosition().x, transformComponent->getPosition().y);
                text.setRotation(transformComponent->getRotation().x);
                text.setScale(transformComponent->getScale().x, transformComponent->getScale().y);
                window->draw(text);
            }
        }
    }
}

void UIText::setText(const char *textStr)
{
    textString = text;
    text.setString(textString);
}

void UIText::setFont(const char *fontPath)
{
    if (!font.loadFromFile(fontPath)) {
        throw GraphicsException("Failed to load font from file: " + std::string(fontPath));
    }
    text.setFont(font);
}

void UIText::setSize(int size)
{
    fontSize = size;
    text.setCharacterSize(fontSize);
}

void UIText::setColor(sf::Color color)
{
    this->color = color;
    text.setFillColor(color);
}

glm::vec2 UIText::getSize()
{
    return glm::vec2(text.getGlobalBounds().width, text.getGlobalBounds().height);
}

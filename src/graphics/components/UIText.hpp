/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** UIText.hpp
**/

#ifndef UITEXT_HPP
#define UITEXT_HPP

#include "AGraphicsComponent.hpp"

//TODO add meta data

class UIText : public AGraphicsComponent {
public:
    UIText(IObject* owner, const char *text, int size, sf::Color color, const char *fontPath); //TODO add default font to arial: find
    ~UIText() override;

    void render(sf::RenderWindow *window) override;
    void setText(const char *text);
    void setFont(const char *fontPath);
    void setSize(int size);
    void setColor(sf::Color color);
    glm::vec2 getSize() override;

private:
    sf::Text text;
    sf::Font font;
    const char *textString;
    const char *fontPath;
    int fontSize;
    sf::Color color;
};

#endif //UITEXT_HPP

/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** UIText.hpp
**/

#ifndef UITEXT_HPP
#define UITEXT_HPP

#include "AGraphicsComponent.hpp"

class UIText : public AGraphicsComponent {
public:
    UIText(IObject* owner, const char *textStr, int size, sf::Color color, const char *fontPath = "default");
    ~UIText() = default;

    void render(sf::RenderWindow *window) override;
    void setText(const char *textStr);
    void setFont(const char *fontPath);
    void setSize(int size);
    void setColor(sf::Color color);
    glm::vec2 getSize() override;

    class Meta : public AMeta
    {
    public:
        Meta();
    };

private:
    sf::Text text;
    sf::Font font;
    const char *textString;
    const char *fontPath;
    int fontSize;
    sf::Color color;
};

#endif //UITEXT_HPP

/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** SpriteSheet.hpp
**/

#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

#include "AGraphicsComponent.hpp"

class SpriteSheet : public AGraphicsComponent {
public:
    SpriteSheet(IObject* owner, const char *path, std::vector<sf::IntRect> frames, int frame = 0);
    ~SpriteSheet() = default;

    void render(sf::RenderWindow *window) override;
    void setTexture(const char *path);
    void setFrames(std::vector<sf::IntRect> frames);
    void setFrame(unsigned int frame);
    void nextFrame();
    void prevFrame();
    glm::vec2 getSize() override;

    class Meta : public AMeta
    {
    public:
        Meta();
    };

private:
    sf::Texture texture;
    sf::Sprite sprite;
    std::vector<sf::IntRect> frames;
    int currentFrame;
    const char *path;
};

#endif //SPRITESHEET_HPP

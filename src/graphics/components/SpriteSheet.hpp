/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** SpriteSheet.hpp
**/

#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

#include "AGraphicsComponent.hpp"

//TODO add meta data

class SpriteSheet : public AGraphicsComponent {
public:
    SpriteSheet(IObject* owner, const char *path, std::vector<sf::IntRect> frames, int frame = 0);
    ~SpriteSheet() override;

    void render(sf::RenderWindow *window) override;
    void setTexture(const char *path);
    void setFrames(std::vector<sf::IntRect> frames);
    void setFrame(sf::IntRect frame);
    void setFrame(int frame);
    void nextFrame();
    void prevFrame();

private:
    sf::Texture texture;
    sf::Sprite sprite;
    std::vector<sf::IntRect> frames;
    int currentFrame;
};

#endif //SPRITESHEET_HPP

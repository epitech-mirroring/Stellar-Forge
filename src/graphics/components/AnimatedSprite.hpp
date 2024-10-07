/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** AnimatedSprite.hpp
**/

#ifndef ANIMATEDSPRITE_HPP
#define ANIMATEDSPRITE_HPP

#include "AGraphicsComponent.hpp"

//TODO add meta data

class AnimatedSprite : public AGraphicsComponent {
public:
    AnimatedSprite(IObject* owner, const char *path, std::vector<sf::IntRect> frames, float frameTime = 0.1f, int frame = 0);
    ~AnimatedSprite() override;

    void render(sf::RenderWindow *window) override;
    void setTexture(const char *path);
    void setFrames(std::vector<sf::IntRect> frames);
    void setFrame(sf::IntRect frame);
    void setFrame(int frame);
    void nextFrame();
    void prevFrame();
    void setFrameTime(float frameTime);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    std::vector<sf::IntRect> frames;
    int currentFrame;
    float frameTime;
};

#endif //ANIMATEDSPRITE_HPP

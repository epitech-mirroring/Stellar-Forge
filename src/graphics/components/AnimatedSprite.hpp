/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** AnimatedSprite.hpp
**/

#ifndef ANIMATEDSPRITE_HPP
#define ANIMATEDSPRITE_HPP

#include "AGraphicsComponent.hpp"

class AnimatedSprite : public AGraphicsComponent {
public:
    AnimatedSprite(IObject* owner, const char *path, std::vector<sf::IntRect> frames, float frameTime = 0.1f, int frame = 0);
    ~AnimatedSprite() = default;

    void render(sf::RenderWindow *window) override;
    void runComponent() override;
    void setTexture(const char *path);
    void setFrames(std::vector<sf::IntRect> frames);
    void setFrame(unsigned int frame);
    void nextFrame();
    void prevFrame();
    void setFrameTime(float frameTime);
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
    float frameTime;
    sf::Clock clock;
    const char *path;
};

#endif //ANIMATEDSPRITE_HPP

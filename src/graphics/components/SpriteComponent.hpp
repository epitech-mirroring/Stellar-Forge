/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** SpriteComponent.hpp
**/

#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include "IGraphicsComponent.hpp"

// TODO add meta data

/**
 * @class SpriteComponent
 * @brief A graphics component that renders a sprite on the screen.
 * @details The SpriteComponent class is responsible for rendering a sprite on the screen using an sf::RenderWindow object.
 *          It loads the texture from a file path and renders it at a specified position on the screen.
 * @version v0.1.0
 * @since v0.1.0
 * @author Aubane NOURRY
 */
class SpriteComponent : public IGraphicsComponent {
public:
    /**
     * @brief Constructor for the SpriteComponent class.
     * @param path The file path to the sprite image.
     * @details This constructor initializes the SpriteComponent with the specified file path.
     * @version v0.1.0
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    SpriteComponent(const char *path);

    /**
     * @brief Destructor for the SpriteComponent class.
     * @details Cleans up and releases any resources used by the SpriteComponent.
     * @version v0.1.0
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    ~SpriteComponent() = default;

    /**
     * @brief Renders the sprite on the screen using the provided window.
     * @param window A pointer to the sf::RenderWindow object used for rendering.
     * @details This method renders the sprite on the screen at the specified position using the provided window.
     * @version v0.1.0
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    void render(sf::RenderWindow *window) override;

private:
    sf::Texture texture; /**< The texture of the sprite. */
    sf::Sprite sprite; /**< The sprite object to render. */
    const char *path; /**< The file path to the sprite image. */
};

#endif //SPRITECOMPONENT_HPP

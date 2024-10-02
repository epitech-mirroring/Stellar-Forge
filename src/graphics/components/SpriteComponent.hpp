/*
** EPITECH PROJECT, 2024
** components
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
 * @details The SpriteComponent class is responsible for rendering a sprite on the screen using an SDL_Texture.
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
     *          The texture is loaded from the file path and stored internally for rendering.
     * @version v0.1.0
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    SpriteComponent(const char *path);

    /**
     * @brief Destructor for the SpriteComponent class.
     * @details Cleans up and releases any resources used by the SpriteComponent, including the SDL_Texture.
     * @version v0.1.0
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    ~SpriteComponent() override;

    /**
     * @brief Renders the sprite on the screen using the provided SDL_Renderer.
     * @param renderer A pointer to the SDL_Renderer object used for rendering.
     * @details This method renders the sprite on the screen at the specified position using the provided renderer.
     * @version v0.1.0
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    void render(SDL_Renderer *renderer) override;

private:
    SDL_Texture *texture; /**< The SDL_Texture used to render the sprite. */
    SDL_Rect srcRect; /**< The source rectangle for the sprite texture. */
    SDL_Rect destRect; /**< The destination rectangle for the sprite texture. */
    const char *path; /**< The file path to the sprite image. */
};

#endif //SPRITECOMPONENT_HPP

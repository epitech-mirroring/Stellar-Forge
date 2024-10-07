/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <memory>
#include "../common/IScene.hpp"
#include "../common/IObject.hpp"

/**
 * @class Graphics
 * @brief This class handles all graphics-related operations.
 * @details The Graphics class is responsible for initializing and managing the rendering
 *          of objects in the scenes, managing an SDL window and renderer, and ensuring 
 *          objects are sorted by their z-index for proper rendering order.
 * @version v0.1.0
 * @since v0.1.0
 * @author Aubane NOURRY
 */
class Graphics {
public:
    /**
     * @brief Constructor for the Graphics class.
     * @param width The width of the window.
     * @param height The height of the window.
     * @param title The title of the window. Default is "Game".
     * @param precharge Whether to preload all objects in all scenes. Default is false.
     * @details This prepares the window with the specified dimensions and title,
     *          and optionally precharges all objects if the precharge flag is set to true.
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    Graphics(int width, int height, const char *title = "Game", bool precharge = false);

    /**
     * @brief Destructor for the Graphics class.
     * @details Cleans up and releases all resources used by the Graphics class, including
     *          the SDL window and renderer.
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    ~Graphics();

    /**
     * @brief prepares the SDL window and renderer.
     * @details This method prepares the SDL window and renderer based on the provided 
     *          width, height, and title. It should be called before any rendering operations.
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    void prepare();

    /**
     * @brief Renders the objects in the current scene.
     * @details This method renders all objects in the current scene in the correct order
     *         based on their z-index. It should be called once per frame to render the
     *        scene.
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    void render();

    /**
     * @brief Clears the current rendering target.
     * @details Clears the renderer's drawing surface, typically called at the beginning of a frame
     *          before rendering the objects.
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    void clear();

    /**
     * @brief Presents the rendered frame to the window.
     * @details This method is called at the end of the rendering process to present the
     *          rendered frame on the screen.
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    void present();

    /**
     * @brief Cleans up the SDL resources used by the Graphics class.
     * @details Destroys the SDL window and renderer, and cleans up any resources used
     *          by the graphics system.
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    void clean();

    /**
     * @brief Adds an object to the sorted object list and maintains the correct order.
     * @param object A shared pointer to the object to add.
     * @details This method adds an object to the internal sortedObjects list and ensures
     *          that the objects are kept in the correct rendering order based on their 
     *          z-index. If the object is already in the list, it won't be added again.
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    void addAndSortObject(IObject *object);

    /**
     * @brief Changes the current scene to the specified scene.
     * @param scene A pointer to the scene to set as the current scene.
     * @details This method changes the current scene to the specified scene and sets the
     *         scene's objects to be rendered in the correct order. 
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    void setScene(IScene *scene);

private:
    sf::RenderWindow window;                     /**< The SFML window used for rendering. */
    int width;                                   /**< The width of the window. */
    int height;                                  /**< The height of the window. */
    const char *title;                           /**< The title of the window. */
    bool prepared;                            /**< Flag indicating if the graphics system is prepared. */
    std::vector<std::shared_ptr<IObject>> sortedObjects; /**< List of objects sorted by z-index for rendering. */
    bool precharge;                              /**< Flag to indicate if all objects should be preloaded in all scenes. */
    IScene *currentScene;                        /**< The current scene being rendered. */
};

#endif // GRAPHICS_HPP

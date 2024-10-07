/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#ifndef IGRAPHICSCOMPONENT_HPP
#define IGRAPHICSCOMPONENT_HPP

#include "../../common/IComponent.hpp"
#include "../../common/IObject.hpp"
#include "../GraphicsException.hpp"
#include <SFML/Graphics.hpp>
#include <glm/ext/vector_float3.hpp>

/**
 * @class IGraphicsComponent
 * @brief Interface for graphics components in the game engine.
 * @details This interface defines the basic structure and functionality for graphics-related components.
 *          Any component that handles graphics or rendering should inherit from this interface and implement
 *          its methods.
 * @version v0.1.0
 * @since v0.1.0
 * @author Aubane NOURRY
 */
class IGraphicsComponent : public IComponent {
public:
    /**
     * @brief Virtual destructor for the IGraphicsComponent class.
     * @details This ensures that derived classes can be properly destroyed, releasing all resources 
     *          when an object is deleted.
     * @since v0.1.0
     */
    virtual ~IGraphicsComponent() = default;

    /**
     * @brief Renders the component using the provided window.
     * @param renderer A pointer to the window object used for rendering.
     * @details This pure virtual function must be implemented by derived classes to define how the component
     *          should be drawn on the screen. It is called each frame to render the visual aspects of the 
     *          component.
     * @since v0.1.0
     */
    virtual void render(sf::RenderWindow *window) = 0;
};

#endif //IGRAPHICALCOMPONENT_HPP

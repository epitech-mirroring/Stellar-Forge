/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#ifndef I3DGRAPHICSCOMPONENT_HPP
#define I3DGRAPHICSCOMPONENT_HPP

#include "common/IComponent.hpp"
#define Transform RaylibTransform
#include "raylib.h"
#undef Transform
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float2.hpp>

/**
 * @class I3DGraphicsComponent
 * @brief Interface for graphics components in the game engine.
 * @details This interface defines the basic structure and functionality for graphics-related components.
 *          Any component that handles graphics or rendering should inherit from this interface and implement
 *          its methods.
 * @version v0.1.0
 * @since v0.1.0
 * @author Aubane NOURRY
 */
class I3DGraphicsComponent : public virtual IComponent {
public:
    /**
     * @brief Virtual destructor for the I3DGraphicsComponent class.
     * @details This ensures that derived classes can be properly destroyed, releasing all resources
     *          when an object is deleted.
     * @since v0.1.0
     * @author Aubane NOURRY
        */
    ~I3DGraphicsComponent() override = default;

    /**

     * @brief Renders the component using the provided window.
     * @details This pure virtual function must be implemented by derived classes to define how the component
     *          should be drawn on the screen. It is called each frame to render the visual aspects of the
     *          component.
     * @since v0.1.0
     *@author Aubane NOURRY
        */
    virtual void render(Camera3D *camera) = 0;

    /**
     * @brief Gets the size of the component on the screen.
     * @return The size of the component as a glm::vec2.
     * @details This pure virtual function must be implemented by derived classes to return the size of the
     *         component on the screen. The size is returned as a glm::vec2, where x is the width and y is the height.
     * @since v0.1.0
     * @author Aubane NOURRY
     */
    virtual glm::vec2 getSize() = 0;
};

#endif //I3DGRAPHICSCOMPONENT_HPP

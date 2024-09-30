/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#ifndef IGRAPHICSCOMPONENT_HPP
#define IGRAPHICSCOMPONENT_HPP

#include "../common/IComponent.hpp"
#include <SDL2/SDL.h>

class IGraphicsComponent : public IComponent {
public:
    virtual ~GraphicsComponent() = default;

    virtual void runComponent() = 0;
    virtual void render(SDL_Renderer *renderer) = 0;
}

#endif //IGRAPHICALCOMPONENT_HPP
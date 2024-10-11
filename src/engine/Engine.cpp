/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include "Engine.hpp"

#include "common/components/Transform.hpp"
#include "common/factories/ComponentFactory.hpp"
#include "graphics/components/AnimatedSprite.hpp"
#include "graphics/components/Sprite.hpp"
#include "graphics/components/SpriteSheet.hpp"
#include "graphics/components/UIText.hpp"

void Engine::_registerComponents() {
    REGISTER_COMPONENT(Transform);
    REGISTER_COMPONENT(AnimatedSprite);
    REGISTER_COMPONENT(Sprite);
    REGISTER_COMPONENT(SpriteSheet);
    REGISTER_COMPONENT(UIText);
}

Engine::Engine() {
    _registerComponents();
}

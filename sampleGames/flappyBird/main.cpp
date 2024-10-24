/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "assets/objects/scripts/Background.hpp"
#include "assets/objects/scripts/Bird.hpp"
#include "assets/objects/scripts/Pipes.hpp"
#include "assets/objects/scripts/Score.hpp"
#include "../../src/engine/Engine.hpp"
#include "../../src/common/factories/ComponentFactory.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    try {
        Engine const engine([]() {
            REGISTER_COMPONENT(Background);
            REGISTER_COMPONENT(Bird);
            REGISTER_COMPONENT(Pipes);
            REGISTER_COMPONENT(Score);
        }, "FlappyBird");
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

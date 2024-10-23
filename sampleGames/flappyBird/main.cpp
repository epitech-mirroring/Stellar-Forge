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
#include "../../src/engine/Engine.hpp"
#include "../../src/common/factories/ComponentFactory.hpp"
#include <iostream>
#include <thread>

int main(int argc, char* argv[])
{
    try {
        Engine const engine([]() {
            REGISTER_COMPONENT(Background);
            REGISTER_COMPONENT(Bird);
            REGISTER_COMPONENT(Pipes);
        }, "FlappyBird");
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

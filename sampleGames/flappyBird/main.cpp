/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "assets/objects/scripts/Background.hpp"
#include "../../src/engine/Engine.hpp"
#include "../../src/common/factories/ComponentFactory.hpp"
#include <iostream>
#include <thread>

int main(int argc, char* argv[])
{
    try {
        Engine const engine([]() {
            REGISTER_COMPONENT(Background);
        }, "FlappyBird");
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

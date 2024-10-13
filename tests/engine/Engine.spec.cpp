/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include <gtest/gtest.h>

#include "engine/Engine.hpp"

TEST(Engine, ally) {
    auto engine = Engine([]() {
                         }, "test", "./assets/",
                         [](const std::string &/*gameName*/) {
                         });
}

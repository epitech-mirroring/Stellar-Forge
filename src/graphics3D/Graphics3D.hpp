/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** Graphics3D.hpp
*/

#ifndef GRAPHICS3D_HPP
#define GRAPHICS3D_HPP

#include <string>
#include <functional>
#include <vector>
#include "common/IObject.hpp"
#include "raylib.h"

class Graphics3D {
public:
    Graphics3D(int width, int height, const std::string &title = "Game", bool precharge = false);
    ~Graphics3D();
    void render(const std::function<void(IObject *)> &updateFunction);

private:
    int width;
    int height;
    std::string title;
    bool prepared;
    bool precharge;
    std::vector<IObject *> sortedObjects;
    Camera3D camera;

    void catchEvents();
    void close();
};

#endif //GRAPHICS3D_HPP

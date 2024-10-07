/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Graphics.hpp"

Graphics::Graphics(int width, int height, const char *title, bool precharge)
    : width(width), height(height), title(title), precharge(precharge), initialized(false), currentScene(nullptr)
{
    window.create(sf::VideoMode(width, height), title);
}

/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "../common/IScene.hpp"
#include "../common/IObject.hpp"

class Graphics {
public:
    Graphics(int width, int height, const char *title, bool precharge = false);
    ~Graphics();

    void initialize();
    void render(void *SceneManager);
    void clear();
    void present();
    void clean();
    void addAndSortObject(std::shared_ptr<IObject> object);

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    int width;
    int height;
    const char *title;
    bool initialized;
    std::vector<std::shared_ptr<IObject>> sortedObjects;
    bool precharge; // if true, precharge all objects in all scenes
};

#endif // GRAPHICS_HPP

/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** SceneManager.hpp
*/

#pragma once

#include <map>
#include <vector>
#include <memory>
#include <algorithm>

// assuming ids are unique and are longs + scenes are void pointers
// assuming we will have a concept of order in the scenes

class SceneManager {
public:
    SceneManager() : _currentSceneIndex(-1) {}
    ~SceneManager() = default;

    void addScene(const long& id, std::shared_ptr<void *> scene, int position /*default -1*/);
    void removeScene(const long& id);
    void switchToScene(const long& id);

    void switchToNextScene();
    void switchToPreviousScene();
    void switchScenesOrder(const long& id1, const long& id2);

    std::shared_ptr<void *> getCurrentScene() const;
    std::shared_ptr<void *> getSceneById(const long& id) const;
    void clearScenes();
    std::map<long, std::shared_ptr<void*>> getScenes() const;
    std::vector<long> getSceneOrder() const;

private:
    std::map<long, std::shared_ptr<void*>> _scenes;
    std::vector<long> _sceneOrder;
    int _currentSceneIndex;
};

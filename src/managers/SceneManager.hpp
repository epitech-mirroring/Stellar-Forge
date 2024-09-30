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
#include "../common/IScene.hpp"

// assuming ids are unique and are longs

class SceneManager {
public:
    SceneManager() : _currentSceneIndex(-1) {}
    ~SceneManager() = default;

    void addScene(const long& id, std::shared_ptr<IScene> scene, int position /*default -1*/);
    void removeScene(const long& id);
    void switchToScene(const long& id);

    void switchToNextScene();
    void switchToPreviousScene();
    void switchScenesOrder(const long& id1, const long& id2);

    std::shared_ptr<IScene> getCurrentScene() const;
    std::shared_ptr<IScene> getSceneById(const long& id) const;
    void clearScenes();
    std::map<long, std::shared_ptr<IScene>> getScenes() const;
    std::vector<long> getSceneOrder() const;

private:
    std::map<long, std::shared_ptr<IScene>> _scenes;
    std::vector<long> _sceneOrder;
    int _currentSceneIndex;
};

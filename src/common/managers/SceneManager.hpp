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
#include "../IScene.hpp"
#include "../UUID.hpp"

// assuming ids are unique and are UUIDs

class SceneManager {
public:
    SceneManager() : _currentSceneIndex(-1) {}
    ~SceneManager() = default;

    void addScene(const UUID& id, std::shared_ptr<IScene> scene, int position /*default -1*/);
    void removeScene(const UUID& id);
    void switchToScene(const UUID& id);

    void switchToNextScene();
    void switchToPreviousScene();
    void switchScenesOrder(const UUID& id1, const UUID& id2);

    std::shared_ptr<IScene> getCurrentScene() const;
    std::shared_ptr<IScene> getSceneById(const UUID& id) const;
    void clearScenes();
    std::map<UUID, std::shared_ptr<IScene>> getScenes() const;
    std::vector<UUID> getSceneOrder() const;

private:
    std::map<UUID, std::shared_ptr<IScene>> _scenes;
    std::vector<UUID> _sceneOrder;
    int _currentSceneIndex;
};

/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** SceneManager.cpp
*/

#include "SceneManager.hpp"

void SceneManager::addScene(const UUID &id, std::shared_ptr<IScene> scene, int position)
{
    if (_scenes.find(id) != _scenes.end()) {
        throw ManagerException("Scene with ID " + id.getUuidString() + " already exists.");
    }
    _scenes[id] = scene;

    if (position < 0 || position >= _sceneOrder.size()) {
        _sceneOrder.push_back(id);
    } else {
        _sceneOrder.insert(_sceneOrder.begin() + position, id);
    }

    if (_currentSceneIndex == -1) {
        _currentSceneIndex = 0;
    }
}

void SceneManager::removeScene(const UUID& id)
{
    auto it = std::find(_sceneOrder.begin(), _sceneOrder.end(), id);
    if (it != _sceneOrder.end()) {
        _sceneOrder.erase(it);

        if (_sceneOrder.empty()) {
            _currentSceneIndex = -1;
        } else if (_currentSceneIndex >= _sceneOrder.size()) {
            _currentSceneIndex = _sceneOrder.size() - 1;
        }
    } else {
        throw ManagerException("Scene with ID " + id.getUuidString() + " not found in order.");
    }

    _scenes.erase(id);
}

void SceneManager::switchToScene(const UUID& id)
{
    auto it = std::find(_sceneOrder.begin(), _sceneOrder.end(), id);
    if (it != _sceneOrder.end()) {
        _currentSceneIndex = std::distance(_sceneOrder.begin(), it);
    } else {
        throw ManagerException("Scene with ID " + id.getUuidString() + " does not exist.");
    }
}

void SceneManager::switchToNextScene()
{
    if (_currentSceneIndex >= 0 && _currentSceneIndex < _sceneOrder.size() - 1) {
        _currentSceneIndex++;
    } else {
        throw ManagerException("No next scene available.");
    }
}

void SceneManager::switchToPreviousScene()
{
    if (_currentSceneIndex > 0) {
        _currentSceneIndex--;
    } else {
        throw ManagerException("No previous scene available.");
    }
}

void SceneManager::switchScenesOrder(const UUID& id1, const UUID& id2)
{
    auto it1 = std::find(_sceneOrder.begin(), _sceneOrder.end(), id1);
    auto it2 = std::find(_sceneOrder.begin(), _sceneOrder.end(), id2);

    if (it1 != _sceneOrder.end() && it2 != _sceneOrder.end()) {
        std::iter_swap(it1, it2);
    } else {
        throw ManagerException("One or both scenes not found.");
    }
}

std::shared_ptr<IScene> SceneManager::getCurrentScene() const
{
    if (_currentSceneIndex >= 0 && _currentSceneIndex < _sceneOrder.size()) {
        return _scenes.at(_sceneOrder[_currentSceneIndex]);
    }
    throw ManagerException("No current scene available.");
}

std::shared_ptr<IScene> SceneManager::getSceneById(const UUID& id) const
{
    auto it = _scenes.find(id);
    if (it != _scenes.end()) {
        return it->second;
    }
    throw ManagerException("Scene with ID " + id.getUuidString() + " not found.");
}

std::map<UUID, std::shared_ptr<IScene>> SceneManager::getScenes() const
{
    return _scenes;
}

std::vector<UUID> SceneManager::getSceneOrder() const
{
    return _sceneOrder;
}

void SceneManager::clearScenes()
{
    _scenes.clear();
    _sceneOrder.clear();
    _currentSceneIndex = -1;
}

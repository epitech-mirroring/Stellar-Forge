/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** SceneManager.cpp
*/

#include "SceneManager.hpp"

void SceneManager::addScene(const long &id, std::shared_ptr<IScene> scene, int position = -1)
{
    if (_scenes.find(id) != _scenes.end()) {
            //raise Warning ID already exists, does not do anything
            return;
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

void SceneManager::removeScene(const long& id) {
    auto it = std::find(_sceneOrder.begin(), _sceneOrder.end(), id);
    if (it != _sceneOrder.end()) {
        _sceneOrder.erase(it);

        if (_sceneOrder.empty()) {
            _currentSceneIndex = -1;
        } else if (_currentSceneIndex >= _sceneOrder.size()) {
            _currentSceneIndex = _sceneOrder.size() - 1;
        }
    }

    _scenes.erase(id);
}

void SceneManager::switchToScene(const long& id) {
    auto it = std::find(_sceneOrder.begin(), _sceneOrder.end(), id);
    if (it != _sceneOrder.end()) {
        _currentSceneIndex = std::distance(_sceneOrder.begin(), it);
    } else {
        //raise Warning ID does not exist
    }
}

void SceneManager::switchToNextScene() {
    if (_currentSceneIndex >= 0 && _currentSceneIndex < _sceneOrder.size() - 1) {
        _currentSceneIndex++;
    } else {
        //raise Warning No next scene
    }
}

void SceneManager::switchToPreviousScene() {
    if (_currentSceneIndex > 0) {
        _currentSceneIndex--;
    } else {
        //raise Warning No previous scene
    }
}

void SceneManager::switchScenesOrder(const long& id1, const long& id2) {
    auto it1 = std::find(_sceneOrder.begin(), _sceneOrder.end(), id1);
    auto it2 = std::find(_sceneOrder.begin(), _sceneOrder.end(), id2);

    if (it1 != _sceneOrder.end() && it2 != _sceneOrder.end()) {
        std::iter_swap(it1, it2);
    } else {
        //raise Error Scene not found
    }
}

std::shared_ptr<IScene> SceneManager::getCurrentScene() const {
    if (_currentSceneIndex >= 0 && _currentSceneIndex < _sceneOrder.size()) {
        return _scenes.at(_sceneOrder[_currentSceneIndex]);
    }
    return nullptr;
}

std::shared_ptr<IScene> SceneManager::getSceneById(const long& id) const {
    auto it = _scenes.find(id);
    if (it != _scenes.end()) {
        return it->second;
    }
    return nullptr;
}

std::map<long, std::shared_ptr<IScene>> SceneManager::getScenes() const {
    return _scenes;
}

std::vector<long> SceneManager::getSceneOrder() const {
    return _sceneOrder;
}

void SceneManager::clearScenes() {
    _scenes.clear();
    _sceneOrder.clear();
    _currentSceneIndex = -1;
}

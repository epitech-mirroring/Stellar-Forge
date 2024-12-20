/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** VirtualScene.cpp
*/

#include "VirtualScene.hpp"

#ifndef __APPLE__
#include <utility>
#endif

VirtualScene::VirtualScene(std::vector<IObject *> objects) : _objects(
    std::move(objects)) {
}

VirtualScene::~VirtualScene() {
    for (const auto &object: _objects) {
        removeObject(object);
        delete object;
    }
}

void VirtualScene::runScene() {
    for (const auto &object: _objects) {
        object->runObject();
    }
}

std::vector<IObject *> VirtualScene::getObjects() const {
    return _objects;
}

void VirtualScene::addObject(IObject *object) {
    _objects.push_back(object);
}

void VirtualScene::removeObject(IObject *object) {
    for (auto ite = _objects.begin(); ite != _objects.end(); ++ite) {
        if (*ite == object) {
            for (const auto &component: object->getComponents()) {
                component->onDeletion();
            }
            for (const auto &child: object->getChildren()) {
                removeObject(child);
            }
            _objects.erase(ite);
            return;
        }
    }
}

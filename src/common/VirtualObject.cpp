/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include "VirtualObject.hpp"

#include <algorithm>


VirtualObject::VirtualObject(IMeta *meta): _parent(nullptr), _children({}),
                                           _components({}),
                                           _meta(meta), _active(true), _hasRun(false) {
    this->LOG = Logger("objects");
    if (_meta == nullptr) {
        LOG.error("Meta cannot be null");
    }
}

IObject *VirtualObject::clone() const {
    auto *const newObject = new VirtualObject(new Meta(_meta->getName()));
    for (const auto *const component: _components) {
        newObject->addComponent(component->clone(newObject));
    }
    for (const auto *const child: _children) {
        newObject->addChild(child->clone());
    }
    return newObject;
}

std::vector<IComponent *> VirtualObject::getComponents() const {
    return _components;
}

std::vector<IObject *> VirtualObject::getChildren() const {
    return _children;
}

std::optional<IObject *> VirtualObject::getParent() const {
    return _parent;
}

void VirtualObject::setParent(IObject *parent) {
    if (_parent != nullptr) {
        _parent->removeChild(this);
    }
    _parent = parent;
    parent->addChild(this);
}

void VirtualObject::addChild(IObject *child) {
    if (std::find(_children.begin(), _children.end(), child) != _children.end()) {
        return;
    }
    _children.push_back(child);
    child->setParent(this);
}

void VirtualObject::removeChild(IObject *child) {
    const auto ite = std::find(_children.begin(), _children.end(), child);
    if (ite == _children.end()) {
        return;
    }
    _children.erase(ite);
    child->setParent(nullptr);
}

void VirtualObject::addComponent(IComponent *component) {
    if (_hasRun) {
        LOG.error("Cannot add component after object has been run. Object: " +
                  _meta->getName());
        return;
    }
    if (std::find(_components.begin(), _components.end(), component) != _components.
        end()) {
        return;
    }
    _components.push_back(component);
}

void VirtualObject::removeComponent(IComponent *component) {
    if (_hasRun) {
        LOG.error << "Cannot remove component after object has been run. Object: " +
                _meta->getName();
        return;
    }
    const auto ite = std::find(_components.begin(), _components.end(), component);
    if (ite == _components.end()) {
        return;
    }
    _components.erase(ite);
}

void VirtualObject::runObject() {
    if (!_hasRun) {
        for (auto *const component: _components) {
            component->onCreation();
        }
        _hasRun = true;
    }
    if (!_active) {
        return;
    }
    for (auto *const component: _components) {
        component->runComponent();
    }
    for (auto *const child: _children) {
        child->runObject();
    }
}

bool VirtualObject::isActive() {
    return _active;
}

void VirtualObject::setActive(const bool active) {
    _active = active;
}

IObject::IMeta &VirtualObject::getMeta() const {
    return *_meta;
}

VirtualObject::Meta::Meta(std::string name): name(std::move(name)) {
}

std::string VirtualObject::Meta::getName() const {
    return name;
}

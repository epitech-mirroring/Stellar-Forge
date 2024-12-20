/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** Engine3D3D.cpp
*/

#include "Engine3D.hpp"

#include <fstream>
#include <string>
#include <filesystem>

#include "StellarForge/Common/VirtualObject.hpp"
#include "StellarForge/Common/VirtualScene.hpp"
#include "StellarForge/Common/components/Transform.hpp"
#include "StellarForge/Common/event/EventSystem.hpp"
#include "StellarForge/Common/factories/ComponentFactory.hpp"
#include "StellarForge/Common/json/JsonArray.hpp"
#include "StellarForge/Common/json/JsonBoolean.hpp"
#include "StellarForge/Common/json/JsonParser.hpp"
#include "StellarForge/Common/json/JsonReader.hpp"
#include "StellarForge/Common/json/JsonString.hpp"
#include "StellarForge/Common/managers/ObjectManager.hpp"
#include "StellarForge/Common/managers/SceneManager.hpp"
#include "StellarForge/Common/utils/LoggerScopes.hpp"
#include "StellarForge/Graphics3D/Graphics3D.hpp"
#include "StellarForge/Graphics3D/components/Cube.hpp"

void Engine3D::_registerComponents() {
    REGISTER_COMPONENT(Transform);
    REGISTER_COMPONENT(Cube);
}

void Engine3D::_registerLoggerScopes() {
    LoggerScopes::getInstance()->addScope("engine");
    LoggerScopes::getInstance()->addScope("objects");
    LoggerScopes::getInstance()->addScope("components");
    LoggerScopes::getInstance()->addScope("components.fields");
    LoggerScopes::getInstance()->addScope("graphics");
}

Engine3D::Engine3D(const std::function<void()> &initComponents,
               const std::string &gameName,
               const std::string &assetsPath,
               const std::function<void(const std::string &gameName)> &startGraphics) {
    _registerLoggerScopes();
    this->LOG = Logger("engine");
    _registerComponents();
    initComponents();
    SceneManager::getInstance();
    ObjectManager::getInstance();
    _loadObjects(assetsPath + "objects/");
    for (auto [_, obj]: _objects) {
        for (auto childUUID: obj.second) {
            auto *child = _objects[childUUID].first;
            obj.first->addChild(child);
        }
    }
    for (const auto &[uuid, obj]: _objects) {
        if (obj.first->getParent() == nullptr) {
            ObjectManager::getInstance().addObject(uuid, obj.first);
        }
    }
    _loadScenes(assetsPath + "scenes/");
    startGraphics(gameName);
}

void Engine3D::_startGraphics(const std::string &gameName) {
    bool isRunning = true;
    auto graphics = Graphics3D(1920, 1080, gameName);
    EventSystem::getInstance().registerListener("window_closed",
                                                [&isRunning](const EventData &) {
                                                    isRunning = false;
                                                });
    while (isRunning) {
        graphics.render([](IObject *object) {
            object->runObject();
        });
    }
}

void Engine3D::_loadObjects(const std::string &pathName) {
    std::filesystem::path const path(pathName);
    if (!exists(path)) {
        LOG.error << "Path does not exist: " << absolute(path) << '\n';
        return;
    }
    const std::filesystem::directory_iterator start(path);
    const std::filesystem::directory_iterator end;
    for (auto ite = start; ite != end; ++ite) {
        if (ite->is_directory()) {
            _loadObjects(ite->path().string());
        } else if (ite->is_regular_file() && ite->path().extension() == ".json") {
            _loadObject(ite->path().string());
        }
    }
}

bool Engine3D::_isValideScene(const json::IJsonObject *data) {
    if (data->getType() != json::OBJECT) {
        return false;
    }
    auto const *const obj = dynamic_cast<const json::JsonObject *>(data);
    if (obj == nullptr) {
        return false;
    }
    if (!obj->contains("objects")) {
        return false;
    }
    if (!obj->contains("id")) {
        return false;
    }
    auto const *const uid = obj->getValue<json::IJsonObject>("id");
    if (uid == nullptr) {
        return false;
    }
    if (uid->getType() != json::STRING) {
        return false;
    }
    auto const *const objs = obj->getValue<json::IJsonObject>("objects");
    if (objs == nullptr) {
        return false;
    }
    if (objs->getType() != json::ARRAY) {
        return false;
    }
    return true;
}

bool Engine3D::_isValideObject(const json::IJsonObject *data) {
    if (data->getType() != json::OBJECT) {
        return false;
    }
    auto const *const obj = dynamic_cast<const json::JsonObject *>(data);
    if (obj == nullptr) {
        return false;
    }
    if (!obj->contains("components")) {
        return false;
    }
    if (!obj->contains("id")) {
        return false;
    }
    if (!obj->contains("meta")) {
        return false;
    }
    if (!obj->contains("child")) {
        return false;
    }
    if (!obj->contains("isActive")) {
        return false;
    }
    auto const *const uid = obj->getValue<json::IJsonObject>("id");
    auto const *const meta = obj->getValue<json::IJsonObject>("meta");
    auto const *const child = obj->getValue<json::IJsonObject>("child");
    auto const *const comps = obj->getValue<json::IJsonObject>("components");
    auto const *const active = obj->getValue<json::IJsonObject>("isActive");

    if (uid == nullptr) {
        return false;
    }
    if (uid->getType() != json::STRING) {
        return false;
    }

    if (meta == nullptr) {
        return false;
    }
    if (meta->getType() != json::OBJECT) {
        return false;
    }

    if (child == nullptr) {
        return false;
    }
    if (child->getType() != json::ARRAY) {
        return false;
    }

    if (comps == nullptr) {
        return false;
    }
    if (comps->getType() != json::ARRAY) {
        return false;
    }

    if (active == nullptr) {
        return false;
    }
    if (active->getType() != json::BOOLEAN) {
        return false;
    }
    return true;
}

void Engine3D::_loadObject(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        LOG.error << "Failed to open file: " << path << '\n';
        return;
    }
    auto *const parser = new json::JsonParser();
    const auto reader = json::JsonReader(parser);
    const json::IJsonObject *const raw = reader << file;
    if (raw == nullptr) {
        LOG.error << "Failed to parse file: " << path << '\n';
        return;
    }
    if (!_isValideObject(raw)) {
        LOG.error << "Invalid object file: " << path << '\n';
        return;
    }
    auto const *const obj = dynamic_cast<const json::JsonObject *>(raw);
    auto const *const uid = obj->getValue<json::JsonString>("id");
    auto const *const meta = obj->getValue<json::JsonObject>("meta");
    auto const *const child = obj->getValue<json::JsonArray<json::JsonString> >("child");
    auto const *const comps = obj->getValue<json::JsonArray<json::JsonObject> >(
        "components");
    auto uuid = UUID();
    uuid.setUuidFromString(uid->getValue());
    std::string name;
    if (meta->contains("name")) {
        auto const *const rawName = meta->getValue<json::JsonString>("name");
        name = rawName->getValue();
    }
    auto *object = new VirtualObject(new VirtualObject::Meta(name));
    if (obj->contains("isActive")) {
        auto const *const active = obj->getValue<json::JsonBoolean>("isActive");
        object->setActive(active->getValue());
    }
    if (comps != nullptr) {
        for (int i = 0; i < comps->size(); i++) {
            const auto *const compData = comps->at(i);
            const auto compName = compData->getValue<json::JsonString>("name")->
                    getValue();
            auto *comp = ComponentFactory::getInstance().create(compName, object, compData);
            object->addComponent(comp);
        }
    }
    std::vector<UUID> children;
    if (child != nullptr) {
        for (int i = 0; i < child->size(); i++) {
            const auto *const childData = child->getValue(i);
            UUID childUuid;
            childUuid.setUuidFromString(childData->getValue());
            children.push_back(childUuid);
        }
    }
    this->_objects[uuid] = std::make_pair(object, children);
}

void Engine3D::_loadScenes(const std::string &pathName) {
    std::filesystem::path const path(pathName);
    const std::filesystem::directory_iterator start(path);
    const std::filesystem::directory_iterator end;
    for (auto ite = start; ite != end; ++ite) {
        if (ite->is_directory()) {
            _loadScenes(ite->path().string());
        } else if (ite->is_regular_file() && ite->path().extension() == ".json") {
            _loadScene(ite->path().string());
        }
    }
}

void Engine3D::_loadScene(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        LOG.error << "Failed to open file: " << path << '\n';
        return;
    }
    auto *const parser = new json::JsonParser();
    const auto reader = json::JsonReader(parser);
    const json::IJsonObject *const raw = reader << file;
    if (raw == nullptr) {
        LOG.error << "Failed to parse file: " << path << '\n';
        return;
    }
    if (!_isValideScene(raw)) {
        LOG.error << "Invalid scene file: " << path << '\n';
        return;
    }
    auto const *const obj = dynamic_cast<const json::JsonObject *>(raw);
    auto const *const uid = obj->getValue<json::JsonString>("id");
    auto const *const objs = obj->getValue<json::JsonArray<json::JsonString> >("objects");
    auto sceneUuid = UUID();
    sceneUuid.setUuidFromString(uid->getValue());
    auto *scene = new VirtualScene();
    if (objs != nullptr) {
        for (int i = 0; i < objs->size(); i++) {
            const auto *const objData = objs->getValue(i);
            UUID objUuid;
            objUuid.setUuidFromString(objData->getValue());
            scene->addObject(_objects[objUuid].first);
        }
    }
    SceneManager::getInstance().addScene(sceneUuid, scene); // TODO : Add scene position ?
    this->_scenes[sceneUuid] = scene;
}


/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include "Engine.hpp"

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
#include "StellarForge/Graphics/components/AnimatedSprite.hpp"
#include "StellarForge/Graphics/components/Sprite.hpp"
#include "StellarForge/Graphics/components/SpriteSheet.hpp"
#include "StellarForge/Graphics/components/UIText.hpp"
#include "StellarForge/Common/managers/SceneManager.hpp"
#include "StellarForge/Common/utils/LoggerScopes.hpp"
#include "StellarForge/Graphics/Graphics.hpp"
#include "StellarForge/Graphics/components/AudioSource.hpp"
#include "StellarForge/Physics/components/RigidBody.hpp"
#include "StellarForge/Graphics/components/Button.hpp"
#include "StellarForge/Graphics/components/UIButton.hpp"
#include "StellarForge/Physics/Box.hpp"
#include "StellarForge/Physics/Sphere.hpp"
#include "StellarForge/Common/fields/ComponentField.hpp"
#include "StellarForge/Graphics/components/UITextInputButton.hpp"
#include "LuaScriptComponent.hpp"

void Engine::_registerComponents() {
    REGISTER_COMPONENT(Transform);
    REGISTER_COMPONENT(AnimatedSprite);
    REGISTER_COMPONENT(Sprite);
    REGISTER_COMPONENT(SpriteSheet);
    REGISTER_COMPONENT(UIText);
    REGISTER_COMPONENT(Button);
    REGISTER_COMPONENT(UIButton);
    REGISTER_COMPONENT(RigidBody);
    REGISTER_COMPONENT(Box);
    REGISTER_COMPONENT(Sphere);
    REGISTER_COMPONENT(AudioSource);
    REGISTER_COMPONENT(UITextInputButton);
    REGISTER_COMPONENT(LuaScriptComponent);
}

void Engine::_registerLoggerScopes() {
    LoggerScopes::getInstance()->addScope("engine");
    LoggerScopes::getInstance()->addScope("objects");
    LoggerScopes::getInstance()->addScope("components");
    LoggerScopes::getInstance()->addScope("components.fields");
    LoggerScopes::getInstance()->addScope("graphics");
}

Engine::Engine(const std::function<void()> &initComponents,
               const std::string &gameName,
               const std::string &assetsPath,
               const std::function<void(const std::string &gameName)> &startGraphics) {
    _registerLoggerScopes();
    this->LOG = Logger("engine");
    _registerComponents();
    initComponents();
    SceneManager::getInstance();
    ObjectManager::getInstance();
    if (!_loadObjects(assetsPath + "objects/")) {
        LOG.error << "An error occurred while loading objects" << '\n';
        return;
    }
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
    //look at each objects and remove any null component
    label:
    for (auto [_, obj]: ObjectManager::getInstance().getObjects()) {
        for (auto *comp: obj->getComponents()) {
            if (comp == nullptr) {
                obj->removeComponent(comp);
                goto label;
            }
        }
    }
    for (auto [_, obj]: ObjectManager::getInstance().getObjects()) {
        for (auto *comp: obj->getComponents()) {
            for (const auto *fieldGroup: comp->getMeta().getFieldGroups()) {
                for (auto *field: fieldGroup->getFields()) {
                    if (dynamic_cast<ComponentField *>(field) != nullptr) {
                        auto *compField = dynamic_cast<ComponentField *>(field);
                        compField->link();
                    }
                }
            }
        }
    }
    if (!_loadScenes(assetsPath + "scenes/") || _scenes.empty()) {
        LOG.error << "An error occurred while loading scenes" << '\n';
        return;
    }
    startGraphics(gameName);
}

Engine::~Engine() {
    SceneManager::getInstance().clearInstance();
    ObjectManager::getInstance().clearInstance();
    ComponentFactory::resetInstance();
}


void Engine::_startGraphics(const std::string &gameName) {
    bool isRunning = true;
    auto graphics = Graphics(1920, 1080, gameName);
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

bool Engine::_loadObjects(const std::string &pathName) {
    std::filesystem::path const path(pathName);
    if (!exists(path)) {
        LOG.error << "Path does not exist: " << absolute(path) << '\n';
        return false;
    }
    const std::filesystem::directory_iterator start(path);
    const std::filesystem::directory_iterator end;
    for (auto ite = start; ite != end; ++ite) {
        if (ite->is_directory()) {
            if (!_loadObjects(ite->path().string())) {
                return false;
            }
        } else if (ite->is_regular_file() && ite->path().extension() == ".json") {
            if (!_loadObject(ite->path().string())) {
                return false;
            }
        }
    }
    return true;
}

bool Engine::_isValideScene(const json::IJsonObject *data) {
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

bool Engine::_isValideObject(const json::IJsonObject *data) {
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

bool Engine::_loadObject(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        LOG.error << "Failed to open file: " << path << '\n';
        return false;
    }
    auto *const parser = new json::JsonParser();
    const auto reader = json::JsonReader(parser);
    const json::IJsonObject *const raw = reader << file;
    if (raw == nullptr) {
        LOG.error << "Failed to parse file: " << path << '\n';
        return false;
    }
    if (!_isValideObject(raw)) {
        LOG.error << "Invalid object file: " << path << '\n';
        return false;
    }
    auto const *const obj = dynamic_cast<const json::JsonObject *>(raw);
    auto const *const uid = obj->getValue<json::JsonString>("id");
    auto const *const meta = obj->getValue<json::JsonObject>("meta");
    auto const *const child = obj->getValue<json::JsonArray<json::JsonString> >("child");
    auto const *const comps = obj->getValue<json::JsonArray<json::JsonObject> >(
        "components");
    auto uuid = UUID();
    try {
        uuid.setUuidFromString(uid->getValue());
    } catch (const std::exception &e) {
        LOG.error << "Failed to parse UUID: " << e.what() << '\n';
        delete parser;
        return false;
    }
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
            try {
                auto *comp = ComponentFactory::getInstance().create(
                    compName, object, compData);
                if (comp != nullptr) {
                    object->addComponent(comp);
                } else {
                    LOG.error << "Failed to create component: " << compName << '\n';
                    LOG.error << "Object: " << uuid.getUuidString() << '\n';
                    delete parser;
                    delete object;
                    return false;
                }
            } catch (const std::exception &e) {
                LOG.error << "Failed to create component: " << compName << ", reason: "
                        << e.what() << '\n';
                LOG.error << "Object: " << uuid.getUuidString() << '\n';
                delete parser;
                delete object;
                return false;
            }
        }
    }
    std::vector<UUID> children;
    if (child != nullptr) {
        for (int i = 0; i < child->size(); i++) {
            const auto *const childData = child->getValue(i);
            UUID childUuid;
            try {
                childUuid.setUuidFromString(childData->getValue());
            } catch (const std::exception &e) {
                LOG.error << "Failed to parse UUID: " << e.what() << '\n';
                delete parser;
                delete object;
                return false;
            }
            children.push_back(childUuid);
        }
    }
    this->_objects[uuid] = std::make_pair(object, children);
    delete parser;
    return true;
}

bool Engine::_loadScenes(const std::string &pathName) {
    std::filesystem::path const path(pathName);
    const std::filesystem::directory_iterator start(path);
    const std::filesystem::directory_iterator end;
    for (auto ite = start; ite != end; ++ite) {
        if (ite->is_directory()) {
            if (!_loadScenes(ite->path().string())) {
                return false;
            }
        } else if (ite->is_regular_file() && ite->path().extension() == ".json") {
            if (!_loadScene(ite->path().string())) {
                return false;
            }
        }
    }
    return true;
}

bool Engine::_loadScene(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        LOG.error << "Failed to open file: " << path << '\n';
        return false;
    }
    auto *const parser = new json::JsonParser();
    const auto reader = json::JsonReader(parser);
    const json::IJsonObject *const raw = reader << file;
    if (raw == nullptr) {
        LOG.error << "Failed to parse file: " << path << '\n';
        return false;
    }
    if (!_isValideScene(raw)) {
        LOG.error << "Invalid scene file: " << path << '\n';
        return false;
    }
    auto const *const obj = dynamic_cast<const json::JsonObject *>(raw);
    auto const *const uid = obj->getValue<json::JsonString>("id");
    auto const *const objs = obj->getValue<json::JsonArray<json::JsonString> >("objects");
    auto sceneUuid = UUID();
    try {
        sceneUuid.setUuidFromString(uid->getValue());
    } catch (const std::exception &e) {
        LOG.error << "Failed to parse UUID: " << e.what() << '\n';
        delete parser;
        return false;
    }
    auto *scene = new VirtualScene();
    if (objs != nullptr) {
        for (int i = 0; i < objs->size(); i++) {
            const auto *const objData = objs->getValue(i);
            UUID objUuid;
            try {
                objUuid.setUuidFromString(objData->getValue());
            } catch (const std::exception &e) {
                LOG.error << "Failed to parse UUID: " << e.what() << '\n';
                delete parser;
                delete scene;
                return false;
            }
            scene->addObject(_objects[objUuid].first);
        }
    }
    SceneManager::getInstance().addScene(sceneUuid, scene); // TODO : Add scene position ?
    this->_scenes[sceneUuid] = scene;
    delete parser;
    return true;
}


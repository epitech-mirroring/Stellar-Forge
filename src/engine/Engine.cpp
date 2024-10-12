/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include "Engine.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

#include "common/VirtualObject.hpp"
#include "common/components/Transform.hpp"
#include "common/factories/ComponentFactory.hpp"
#include "common/json/JsonArray.hpp"
#include "common/json/JsonNumber.hpp"
#include "common/json/JsonParser.hpp"
#include "common/json/JsonReader.hpp"
#include "common/json/JsonString.hpp"
#include "common/managers/ObjectManager.hpp"
#include "graphics/components/AnimatedSprite.hpp"
#include "graphics/components/Sprite.hpp"
#include "graphics/components/SpriteSheet.hpp"
#include "graphics/components/UIText.hpp"
#include "common/managers/SceneManager.hpp"

void Engine::_registerComponents() {
    REGISTER_COMPONENT(Transform);
    REGISTER_COMPONENT(AnimatedSprite);
    REGISTER_COMPONENT(Sprite);
    REGISTER_COMPONENT(SpriteSheet);
    REGISTER_COMPONENT(UIText);
}

Engine::Engine(const std::function<void()> &initComponents) {
    _registerComponents();
    initComponents();
    SceneManager::getInstance();
    ObjectManager::getInstance();
    _loadObjects("./assets/objects/");
}

void Engine::_loadObjects(const std::string &pathName) {
    std::filesystem::path const path(pathName);
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
    if (uid->getType() != json::NUMBER) {
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
    if (!obj->contains("active")) {
        return false;
    }
    auto const *const uid = obj->getValue<json::IJsonObject>("id");
    auto const *const meta = obj->getValue<json::IJsonObject>("meta");
    auto const *const child = obj->getValue<json::IJsonObject>("child");
    auto const *const comps = obj->getValue<json::IJsonObject>("components");
    auto const *const active = obj->getValue<json::IJsonObject>("active");

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

void Engine::_loadObject(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << path << '\n';
        return;
    }
    auto *const parser = new json::JsonParser();
    const auto reader = json::JsonReader(parser);
    const json::IJsonObject *const raw = reader << file;
    if (raw == nullptr) {
        std::cerr << "Failed to parse file: " << path << '\n';
        return;
    }
    if (!_isValideObject(raw)) {
        std::cerr << "Invalid object file: " << path << '\n';
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
    for (int i = 0; i < comps->size(); i++) {
        const auto *const compData = comps->getValue(i);
        const auto compName = compData->getValue<json::JsonString>("name")->getValue();
        auto *comp = ComponentFactory::create(compName, object, compData);
        object->addComponent(comp);
    }
    std::vector<UUID> children;
    for (int i = 0; i < child->size(); i++) {
        const auto *const childData = child->getValue(i);
        UUID childUuid;
        childUuid.setUuidFromString(childData->getValue());
        children.push_back(childUuid);
    }
    this->_objects[uuid] = std::make_pair(object, children);
}

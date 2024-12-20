/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <functional>

#include "StellarForge/Common/IObject.hpp"
#include "StellarForge/Common/IScene.hpp"
#include "StellarForge/Common/UUID.hpp"
#include "StellarForge/Common/json/IJsonObject.hpp"
#include "StellarForge/Common/utils/Logger.hpp"

class Engine {
protected:
    std::unordered_map<UUID, std::pair<IObject *, std::vector<UUID> > > _objects;

    std::unordered_map<UUID, IScene *> _scenes;
    Logger LOG;

public:
    Engine(const std::function<void()> &initComponents, const std::string &gameName,
           const std::string &assetsPath = "./assets/",
           const std::function<void(const std::string &gameName)> &startGraphics =
                   _startGraphics);

    ~Engine();

    static void _startGraphics(const std::string &gameName);

private:
    static void _registerComponents();

    static void _registerLoggerScopes();

    bool _loadObjects(const std::string &pathName);

    bool _loadObject(const std::string &path);

    bool _loadScenes(const std::string &pathName);

    bool _loadScene(const std::string &path);

    static bool _isValideScene(const json::IJsonObject *data);

    static bool _isValideObject(const json::IJsonObject *data);
};

#endif //ENGINE_HPP

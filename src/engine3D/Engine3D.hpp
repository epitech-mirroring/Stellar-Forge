/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** Engine3D.hpp
*/

#ifndef ENGINE3D_HPP
#define ENGINE3D_HPP

#include <functional>

#include "StellarForge/Common/IObject.hpp"
#include "StellarForge/Common/IScene.hpp"
#include "StellarForge/Common/UUID.hpp"
#include "StellarForge/Common/json/IJsonObject.hpp"
#include "StellarForge/Common/utils/Logger.hpp"

class Engine3D {
protected:
    std::unordered_map<UUID, std::pair<IObject *, std::vector<UUID> > > _objects;
    std::unordered_map<UUID, IScene *> _scenes;
    Logger LOG;

public:
    Engine3D(const std::function<void()> &initComponents, const std::string &gameName,
           const std::string &assetsPath = "./assets/",
           const std::function<void(const std::string &gameName)> &startGraphics =
                   _startGraphics);
    ~Engine3D() = default;
private:
    static void _startGraphics(const std::string &gameName);
    static void _registerComponents();
    static void _registerLoggerScopes();
    void _loadObjects(const std::string &pathName);
    void _loadObject(const std::string &path);
    void _loadScenes(const std::string &pathName);
    void _loadScene(const std::string &path);
    static bool _isValideScene(const json::IJsonObject *data);
    static bool _isValideObject(const json::IJsonObject *data);
};

#endif //ENGINE3D_HPP

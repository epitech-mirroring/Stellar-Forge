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

#include "common/IObject.hpp"
#include "common/IScene.hpp"
#include "common/UUID.hpp"
#include "common/json/IJsonObject.hpp"

class Engine {
protected:
    std::unordered_map<UUID, std::pair<IObject *, std::vector<UUID> > > _objects;

    std::unordered_map<UUID, IScene*> _scenes;

public:
    explicit Engine(const std::function<void()> &initComponents);

    ~Engine() = default;

private:
    static void _registerComponents();

    void _loadObjects(const std::string &pathName);

    void _loadObject(const std::string &path);
    void _loadScenes(const std::string& pathName);

    void _loadScene(const std::string& path);

    static bool _isValideScene(const json::IJsonObject *data);

    static bool _isValideObject(const json::IJsonObject *data);
};

#endif //ENGINE_HPP

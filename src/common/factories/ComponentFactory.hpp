/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#ifndef COMPONENTFACTORY_HPP
#define COMPONENTFACTORY_HPP

#include <functional>
#ifndef __APPLE__
#include <memory>
#endif
#include "common/IComponent.hpp"
#include "common/components/AComponent.hpp"
#include "common/json/JsonObject.hpp"


class ComponentFactory {
public:
    using Constructor = std::function<std::unique_ptr<IComponent>(
        IObject *, const json::JsonObject *)>;

    template<typename T>
    static void registerComponent(const std::string &typeName) {
        registry()[typeName] = [
                ](IObject *owner,
                  const json::JsonObject *data) -> std::unique_ptr<IComponent> {
                    auto comp = construct<T>(owner, data);
                    if (data->contains("data") && std::is_base_of_v<AComponent, T>) {
                        const auto *customData = data->getValue<
                            json::JsonObject>("data");
                        dynamic_cast<AComponent *>(comp.get())->deserialize(customData);
                    }
                    return comp;
                };
    }

    static std::unique_ptr<IComponent> create(const std::string &typeName,
                                              IObject *owner,
                                              const json::JsonObject *data) {
        if (registry().find(typeName) != registry().end()) {
            return registry()[typeName](owner, data);
        }
        return nullptr;
    }

private:
    static std::unordered_map<std::string, Constructor> &registry() {
        static std::unordered_map<std::string, Constructor> reg;
        return reg;
    }

    template<typename T>
    static std::unique_ptr<IComponent> construct(IObject *owner,
                                                 const json::JsonObject *data) {
        return std::make_unique<T>(owner, data);
    }
};


#define REGISTER_COMPONENT(name) \
    static_assert(IsValidComponent<name>::value, "Check documentation for valid components"); \
    ComponentFactory::registerComponent<name>(#name)


#endif //COMPONENTFACTORY_HPP

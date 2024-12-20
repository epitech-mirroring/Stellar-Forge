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
#include "../IComponent.hpp"
#include "../components/AComponent.hpp"
#include "../json/JsonObject.hpp"
#include "../utils/Logger.hpp"


class ComponentFactory {
    static ComponentFactory *INSTANCE;
    Logger LOG;

public:
    using Constructor = std::function<IComponent *(
        IObject *, const json::JsonObject *)>;

    ComponentFactory();

    ~ComponentFactory();

    template<typename T>
    void registerComponent(const std::string &typeName) {
        if (registry.find(typeName) != registry.end()) {
            LOG.warn << "Component already registered: " << typeName << '\n';
            return;
        }
        registry[typeName] = [
                ](IObject *owner,
                  const json::JsonObject *data) -> IComponent *{
                    auto comp = construct<T>(owner, data);
                    if (data->contains("customData") && std::is_base_of_v<AComponent,
                            T>) {
                        const auto *customData = data->getValue<
                            json::IJsonObject>("customData");
                        dynamic_cast<AComponent *>(comp)->deserialize(customData);
                    }
                    return comp;
                };
        LOG.info << "Registering component: " << typeName << '\n';
    }

    [[nodiscard]]
    IComponent *create(const std::string &typeName,
                       IObject *owner,
                       const json::JsonObject *data);

    [[nodiscard]]
    bool hasComponent(const std::string &typeName) const;

    static ComponentFactory &getInstance() {
        if (INSTANCE == nullptr) {
            INSTANCE = new ComponentFactory();
        }
        return *INSTANCE;
    }

    static void resetInstance() {
        delete INSTANCE;
        INSTANCE = nullptr;
    }

    void safeUnregisterComponent(const std::string &typeName);

private:
    std::unordered_map<std::string, Constructor> registry;

    template<typename T>
    static IComponent *construct(IObject *owner,
                                 const json::JsonObject *data) {
        return new T(owner, data);
    }
};


#define REGISTER_COMPONENT(name) \
    static_assert(IsValidComponent<name>::value, "Check documentation for valid components"); \
    ComponentFactory::getInstance().registerComponent<name>(#name)


#endif //COMPONENTFACTORY_HPP

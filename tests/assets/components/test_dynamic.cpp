/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include "StellarForge/common/factories/ComponentFactory.hpp"
#include "StellarForge/common/fields/StringField.hpp"
#include "StellarForge/common/fields/groups/InvisibleFieldGroup.hpp"
#include "StellarForge/common/json/JsonNull.hpp"
#include "StellarForge/common/utils/Logger.hpp"

extern "C"  {
    SYMBOL const char **getComponentName() {
        static const char *components[] = {
            "Test1",
            nullptr
        };
        return components;
    }
}

class Test1 final : public AComponent {
public:
    class Meta final : public IMeta {
    protected:
        Test1 *_owner;
        InvisibleFieldGroup _fieldGroup;

    public:
        explicit Meta(Test1 *owner): _owner(owner), _fieldGroup(InvisibleFieldGroup({})) {
        }

        [[nodiscard]] std::string getName() const override {
            return "Test1";
        }

        [[nodiscard]] std::string getDescription() const override {
            return "Test1 component dynamically loaded.";
        }

        [[nodiscard]] bool isUnique() const override {
            return true;
        }

        [[nodiscard]] bool canBeRemoved() const override {
            return true;
        }

        [[nodiscard]] std::vector<const IFieldGroup *>
        getFieldGroups() const override {
            return {&_fieldGroup};
        }
    };

    explicit Test1(IObject *owner,
                   const json::JsonObject *data = nullptr): AComponent(
        owner, new Meta(this), data) {
    }

    ~Test1() override = default;

    [[nodiscard]] IComponent *clone(IObject *owner) const override {
        return new Test1(owner, dynamic_cast<json::JsonObject *>(this->serializeData()));
    }

    void runComponent() override {
        this->_log.info << "Test1 is running on object " << this->_owner->getMeta().
                getName() << '\n';
    }

    void deserialize(const json::IJsonObject *data) override {
    }

protected:
    Logger _log;

    [[nodiscard]] json::IJsonObject *serializeData() const override {
        return new json::JsonNull();
    }
};

extern "C" {
    SYMBOL void registerComponents(ComponentFactory *factory) {
        factory->registerComponent<Test1>("Test1");
    }
}

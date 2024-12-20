/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include <gtest/gtest.h>

#include "StellarForge/Common/components/Transform.hpp"
#include "StellarForge/Common/json/JsonArray.hpp"
#include "StellarForge/Common/json/JsonParser.hpp"

TEST(ComponentDeserialization, Transform) {
    std::string const json = R"({
        "type": "Transform",
        "isActive": true,
        "data": {
            "invisible": {
                "Position": {
                    "x": 1.0,
                    "y": 2.0,
                    "z": 3.0
                },
                "Rotation": {
                    "x": 4.0,
                    "y": 5.0,
                    "z": 6.0
                },
                "Scale": {
                    "x": 7.0,
                    "y": 8.0,
                    "z": 9.0
                }
            }
        }
    })";

    REGISTER_COMPONENT(Transform);
    json::JsonParser const parser;
    const auto *const raw = parser.parse(json);
    ASSERT_EQ(raw->getType(), json::OBJECT);
    ASSERT_EQ(raw->getName(), "");
    const auto *const data = dynamic_cast<const json::JsonObject *>(raw);
    IComponent *r_component = ComponentFactory::getInstance().create(
        "Transform", nullptr, data);
    ASSERT_NE(r_component, nullptr);
    ASSERT_EQ(r_component->isActive(), true);
    ASSERT_NE(dynamic_cast<Transform *>(r_component), nullptr);
    const Transform *transform = dynamic_cast<Transform *>(r_component);
    ASSERT_FLOAT_EQ(transform->getPosition().x, 1);
    ASSERT_FLOAT_EQ(transform->getPosition().y, 2);
    ASSERT_FLOAT_EQ(transform->getPosition().z, 3);
    //ASSERT_FLOAT_EQ(transform->getRotation().x, 4);
    //ASSERT_FLOAT_EQ(transform->getRotation().y, 5);
    //ASSERT_FLOAT_EQ(transform->getRotation().z, 6);
    ASSERT_FLOAT_EQ(transform->getScale().x, 7);
    ASSERT_FLOAT_EQ(transform->getScale().y, 8);
    ASSERT_FLOAT_EQ(transform->getScale().z, 9);
}

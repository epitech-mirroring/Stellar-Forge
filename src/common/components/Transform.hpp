/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#ifndef STELLARFORGE_TRANSFORM_HPP
#define STELLARFORGE_TRANSFORM_HPP

#include "../../physics/Physics.hpp"
#include "../IComponent.hpp"
#include "../fields/Vector3Field.hpp"
#include "../fields/FieldGroup.hpp"
#include "../AMeta.hpp"
#include "../AComponent.hpp"

using Vector3 = glm::vec3;

class Transform : public AComponent {
private:
    Vector3 position;
    glm::quat rotation;
    Vector3 scale;

public:
    class TransformMeta : public AMeta {
    private:
        class FieldGroup : public InvisibleFieldGroup {
        public:
            FieldGroup() : InvisibleFieldGroup({
                new Vector3Field("Position", "The position of the object."),
                new Vector3Field("Rotation", "The rotation of the object."),
                new Vector3Field("Scale", "The scale of the object.")
            }) {}
        };
    public:
        TransformMeta()
            : AMeta("Transform", "The transform of the object.", true, false,
            std::vector<IComponent::IMeta::IFieldGroup *>{ new FieldGroup() }) {}
    };

    explicit Transform(IObject *owner) : AComponent(owner, TransformMeta()), position(0, 0, 0), rotation(0, 0, 0, 1), scale(1, 1, 1) {}

    [[nodiscard]] Vector3 getPosition() const;
    [[nodiscard]] glm::quat getRotation() const;
    [[nodiscard]] Vector3 getScale() const;
    void setPosition(Vector3 pos);
    void translate(Vector3 pos);
    void setRotation(glm::quat rot);
    void rotate(Vector3 axis, float angle);
    void setScale(Vector3 sca);
    void scaleBy(Vector3 sca);
};

#endif //STELLARFORGE_TRANSFORM_HPP

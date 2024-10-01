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

using Vector3 = glm::vec3;

class Transform : virtual public IComponent {
private:
    Vector3 position;
    glm::quat rotation;
    Vector3 scale;

public:
    Transform() : position(0, 0, 0), rotation(0, 0, 0, 1), scale(1, 1, 1) {}
    Transform(Vector3 pos, glm::quat rot, Vector3 sca) : position(pos), rotation(rot), scale(sca) {}
    ~Transform() override = default;
    Transform(const Transform &other) = delete;
    Transform &operator=(const Transform &other) = delete;
    Transform(Transform &&other) = delete;
    Transform &operator=(Transform &&other) = delete;

    [[nodiscard]] Vector3 getPosition() const { return position; }
    [[nodiscard]] glm::quat getRotation() const { return rotation; }
    [[nodiscard]] Vector3 getScale() const { return scale; }
    void setPosition(Vector3 pos) { position = pos; }
    void translate(Vector3 pos) { position += pos; }
    void setRotation(glm::quat rot) { rotation = rot; }
    void rotate(Vector3 axis, float angle) { rotation = glm::rotate(rotation, angle, axis); }
    void setScale(Vector3 sca) { scale = sca; }
    void scaleBy(Vector3 sca) { scale *= sca; }

    class Meta : virtual public IMeta {
    private:
        class FieldGroup : public InvisibleFieldGroup {
        public:
            FieldGroup() : InvisibleFieldGroup({
                new Vector3Field("Position", "The position of the object."),
                new Vector3Field("Rotation", "The rotation of the object."),
                new Vector3Field("Scale", "The scale of the object.")
            }) {}
            ~FieldGroup() override = default;
            FieldGroup(const FieldGroup &other) = delete;
            FieldGroup &operator=(const FieldGroup &other) = delete;
            FieldGroup(FieldGroup &&other) = delete;
            FieldGroup &operator=(FieldGroup &&other) = delete;
        };

        std::vector<IFieldGroup *> _fieldGroups = { new FieldGroup() };

    public:
        Meta() = default;
        ~Meta() override = default;
        Meta(const Meta &other) = delete;
        Meta &operator=(const Meta &other) = delete;
        Meta(Meta &&other) = delete;
        Meta &operator=(Meta &&other) = delete;

        [[nodiscard]] std::string getName() const override { return "Transform"; }
        [[nodiscard]] std::string getDescription() const override { return "A component that represents the position and rotation of an object in a 3D space."; }
        [[nodiscard]] bool isUnique() const override { return true; }
        [[nodiscard]] bool canBeRemoved() const override { return false; }

        [[nodiscard]] std::vector<IFieldGroup *> getFieldGroups() const override { return _fieldGroups; }
    };
};

#endif //STELLARFORGE_TRANSFORM_HPP

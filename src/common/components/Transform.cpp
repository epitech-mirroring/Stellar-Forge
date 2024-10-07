/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#include "Transform.hpp"

Transform::Transform(IObject *owner): AComponent(owner, TransformMeta()), position({0, 0, 0}), rotation(glm::quat(1, 0, 0, 0)), scale({1, 1, 1})
{
}

Transform::Transform(IObject *owner, Vector3 pos, glm::quat rot, Vector3 sca): AComponent(owner, TransformMeta()), position(pos), rotation(rot), scale(sca)
{
}

Vector3 Transform::getPosition() const
{
    return position;
}

glm::quat Transform::getRotation() const
{
    return rotation;
}

Vector3 Transform::getScale() const
{
    return scale;
}

void Transform::setPosition(Vector3 pos)
{
    position = pos;
}

void Transform::translate(Vector3 pos)
{
    position += pos;
}

void Transform::setRotation(glm::quat rot)
{
    rotation = rot;
}

void Transform::rotate(Vector3 axis, float angle)
{
    rotation = glm::rotate(rotation, angle, axis);
}

void Transform::setScale(Vector3 sca)
{
    scale = sca;
}

void Transform::scaleBy(Vector3 sca)
{
    scale *= sca;
}

Transform::TransformMeta::TransformMeta(): AMeta("Transform", "The transform of the object.", true, false,
        std::vector<IComponent::IMeta::IFieldGroup *>{ new TransformFieldGroup() })
{
}

Transform::TransformMeta::TransformFieldGroup::TransformFieldGroup(): InvisibleFieldGroup({
        new Vector3Field("Position", "The position of the object."),
        new Vector3Field("Rotation", "The rotation of the object."),
        new Vector3Field("Scale", "The scale of the object.")
    })
{
}

/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#include "Sphere.hpp"
#include "Box.hpp"
#include "Physics.hpp"
#include "common/fields/Vector3Field.hpp"
#include "common/fields/FloatField.hpp"
#include "common/json/JsonNull.hpp"

//Sphere::Sphere(Vector3 position, float radius) : relativePosition(position), radius(radius), position(0, 0, 0)
//{
//}

void Sphere::setPosition(Vector3 position) {
    this->position = position;
}

[[nodiscard]] Vector3 Sphere::getPosition() const {
    return position;
}

void Sphere::setRelativePosition(Vector3 RelativePosition) {
    this->relativePosition = RelativePosition;
}

[[nodiscard]] Vector3 Sphere::getRelativePosition() const {
    return relativePosition;
}

bool Sphere::collide(ICollider *collider) {
    if (dynamic_cast<Sphere *>(collider) != nullptr) {
        return Physics::Collision::sphereCollideSphere(
            *this, *dynamic_cast<Sphere *>(collider));
    }
    if (dynamic_cast<Box *>(collider) != nullptr) {
        return Physics::Collision::sphereCollideBox(
            *this, *dynamic_cast<Box *>(collider));
    }
    return false;
}

void Sphere::scale(float scale) {
    this->radius *= scale;
}

Sphere::Meta::Meta(Sphere *owner) : _owner(owner),
                                    _fieldGroup(InvisibleFieldGroup({})) {
    const std::vector<IField *> fields = {
        new Vector3Field("Position", "The position of the sphere relative to the parent object",
                         [this](Vector3 pos) { this->_owner->setPosition(pos); },
                         [this] { return this->_owner->getPosition(); }),
        new FloatField("Radius", "The radius of the sphere",
                       [this](float radius) { this->_owner->radius = radius; },
                       [this] { return this->_owner->radius; }),
    };
    this->_fieldGroup = InvisibleFieldGroup(fields);
}

std::string Sphere::Meta::getName() const {
    return "Sphere";
}

std::string Sphere::Meta::getDescription() const {
    return "A sphere collider";
}

bool Sphere::Meta::isUnique() const {
    return false;
}

bool Sphere::Meta::canBeRemoved() const {
    return true;
}

std::vector<const IComponent::IMeta::IFieldGroup *> Sphere::Meta::getFieldGroups() const {
    return {&_fieldGroup};
}

Sphere::Sphere(IObject *owner, const json::JsonObject *data) : AComponent(owner, new Meta(this), data),
                                                               radius(1), position(0, 0, 0), relativePosition(0, 0, 0) {
    this->deserializeFields(data);
}

Sphere::Sphere(IObject *owner, Vector3 pos, float radius) : AComponent(owner, new Meta(this)),
                                                            position(pos), radius(radius), relativePosition(0, 0, 0) {
}

void Sphere::runComponent() {
}

json::IJsonObject *Sphere::serializeData() {
    return new json::JsonNull();
}

void Sphere::deserialize(const json::IJsonObject *data) {
}

Sphere *Sphere::clone(IObject *owner) const {
    return new Sphere(owner, this->position, this->radius);
}

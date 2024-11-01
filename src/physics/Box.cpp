/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#include "Sphere.hpp"
#include "Box.hpp"
#include "Physics.hpp"
#include "StellarForge/Common/fields/Vector3Field.hpp"
#include "StellarForge/Common/json/JsonNull.hpp"

void Box::setPosition(Vector3 position) {
    this->position = position;
}

[[nodiscard]] Vector3 Box::getPosition() const {
    return position;
}

void Box::setRelativePosition(Vector3 RelativePosition) {
    this->relativePosition = RelativePosition;
}

[[nodiscard]] Vector3 Box::getRelativePosition() const {
    return relativePosition;
}

bool Box::collide(ICollider *collider) {
    if (dynamic_cast<Box *>(collider) != nullptr) {
        return Physics::Collision::boxCollideBox(*this, *dynamic_cast<Box *>(collider));
    }
    if (dynamic_cast<Sphere *>(collider) != nullptr) {
        return Physics::Collision::boxCollideSphere(
            *this, *dynamic_cast<Sphere *>(collider));
    }
    return false;
}

void Box::scale(float scale) {
    this->size *= scale;
}

Box::Meta::Meta(Box *owner) : _owner(owner),
                              _fieldGroup(InvisibleFieldGroup({})) {
    const std::vector<IField *> fields = {
        new Vector3Field("Position", "The position of the box relative to the parent object",
                         [this](Vector3 pos) { this->_owner->setPosition(pos); },
                         [this] { return this->_owner->getPosition(); }),
        new Vector3Field("Size", "The size of the box",
                         [this](Vector3 size) { this->_owner->size = size; },
                         [this] { return this->_owner->size; }),
    };
    this->_fieldGroup = InvisibleFieldGroup(fields);
}

std::string Box::Meta::getName() const {
    return "Box";
}

std::string Box::Meta::getDescription() const {
    return "A box collider";
}

bool Box::Meta::isUnique() const {
    return false;
}

bool Box::Meta::canBeRemoved() const {
    return true;
}

std::vector<const IComponent::IMeta::IFieldGroup *> Box::Meta::getFieldGroups() const {
    return {&_fieldGroup};
}

Box::Box(IObject *owner, const json::JsonObject *data) : AComponent(owner, new Meta(this), data),
                                                         position(0, 0, 0), size(1, 1, 1), relativePosition(0, 0, 0) {
    this->deserializeFields(data);
}

Box::Box(IObject *owner, Vector3 pos, Vector3 size) : AComponent(owner, new Meta(this)),
                                                      position(pos), size(size), relativePosition(0, 0, 0) {
}

void Box::runComponent() {
}

json::IJsonObject *Box::serializeData() const {
    return new json::JsonNull();
}

void Box::deserialize(const json::IJsonObject *data) {
}

Box *Box::clone(IObject *owner) const {
    return new Box(owner, this->position, this->size);
}

/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there , just an epitech header example .
*/

#include "RigidBody.hpp"
#include "Transform.hpp"
#include "../fields/FieldGroup.hpp"
#include "../fields/Vector3Field.hpp"
#include "../fields/FloatField.hpp"
#include "../../physics/Physics.hpp"
#include "../IObject.hpp"

RigidBody::RigidBodyMeta::RigidBodyMeta() : AMeta("RigidBody", "A rigid body with physics properties",
                                                  true, true,
                                                  std::vector<IFieldGroup *>({
                                                      new InvisibleFieldGroup(std::vector<IField *>{
                                                          new Vector3Field("Velocity", "The velocity of the rigid body"),
                                                          new Vector3Field("Acceleration", "The acceleration of the rigid body"),
                                                          new FloatField("TerminalVelocity", "The terminal velocity of the rigid body"),
                                                          new FloatField("Drag", "The drag of the rigid body")
                                                      })
                                                  }))
{
}

RigidBody::RigidBody(IObject *owner) : AComponent(owner, RigidBodyMeta()), _velocity(Vector3(0.0f)), _acceleration(Vector3(0.0f)), _terminalVelocity(0.0f), _drag(0.0f)
{
}

void RigidBody::applyMovement(const float deltaTime)
{
    auto *transform = _owner->getComponent(&typeid(Transform));
    if (transform == nullptr) {
        return;
    }
    auto *transformComponent = dynamic_cast<Transform *>(transform);
    Physics::Movement::applyMovement(transformComponent->getPosition(), _velocity, _acceleration, _terminalVelocity, deltaTime);
}

void RigidBody::applyDrag(const float deltaTime)
{
    Physics::Movement::applyDrag(_velocity, _drag, deltaTime);
}

void RigidBody::applyForce(const float deltaTime)
{
    Physics::Movement::applyForce(_velocity, _acceleration, deltaTime);
}

void RigidBody::applyImpulse(const Vector3 &impulse)
{
    Physics::Movement::applyImpulse(_velocity, impulse);
}

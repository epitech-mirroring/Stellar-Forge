/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** AComponent.hpp
*/

#ifndef ACOMPONENT_HPP
#define ACOMPONENT_HPP

#include "IComponent.hpp"

/**
 * @class AComponent
 * @brief This class is the abstract class for the Component class
 * @version v0.1.0
 * @since v0.1.0
 * @author Marius PAIN
 */
class AComponent : virtual public IComponent
{
public:
 /**
  * @brief The destructor of the AComponent class
  * @version v0.1.0
  * @since v0.1.0
  * @author Marius PAIN
  */
 ~AComponent() override = default;

 /**
  * @brief The update function of the component.
  * This is meant to be runt by the parent object and update the component every frame
  * @note This is a pure virtual function and must be implemented in the child class
  * @see IComponent::runComponent
  * @version v0.1.0
  * @since v0.1.0
  * @author Marius PAIN
  */
 void runComponent() override = 0;

 /**
  * @brief This function is used to check if the component is active
  * @see IComponent::isActive
  * @return True if the component is active, false otherwise
  * @version v0.1.0
  * @since v0.1.0
  * @author Aubane NOURRY
  */
 bool isActive();

 /**
  * @brief This function is used to set the state of the component
  * @param state The state of the component
  * @version v0.1.0
  * @since v0.1.0
  * @author Aubane NOURRY
  */
 void setActive(bool state);

 /**
  * @brief Returns a non-owning and non-null pointer to the owner of the component
  * @see IComponent::getOwner
  * @return the owner of the component
  * @version v0.1.0
  * @since v0.1.0
  * @author Marius PAIN
  */
 [[nodiscard]] IObject* getOwner() override;

 /**
  * @brief Get the meta of the component
  * @see IComponent::getMeta
  * @return the meta of the component
  * @version v0.1.0
  * @since v0.1.0
  * @author Marius PAIN
  */
 [[nodiscard]] IMeta& getMeta() const override;

protected:
 /**
  * @brief The constructor of the AComponent class
  * @param owner The owner of the component
  * @param meta The meta of the component
  * @version v0.1.0
  * @since v0.1.0
  * @author Marius PAIN
  */
 AComponent(IObject* owner, IMeta& meta);

 /**
  * @brief The owner of the component
  * @version v0.1.0
  * @since v0.1.0
  * @author Marius PAIN
 */
 IObject* _owner;

 /**
  * @brief The meta of the component
  * @version v0.1.0
  * @since v0.1.0
  * @author Marius PAIN
  */
 IMeta& _meta;

 bool _isActive; //< The state of the component
};

#endif //ACOMPONENT_HPP

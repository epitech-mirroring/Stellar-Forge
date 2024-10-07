/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** AGraphicsComponent.hpp
*/

#ifndef AGRAPHICSCOMPONENT_HPP
#define AGRAPHICSCOMPONENT_HPP

#include "IGraphicsComponent.hpp"
#include "../../common/AMeta.hpp"
#include "../../common/AField.hpp"
#include "../../common/AFieldGroup.hpp"

/**
 * @class AGraphicsComponent
 * @brief This class is the abstract class for the GraphicsComponent class
 * @version v0.1.0
 * @since v0.1.0
 * @author Aubane NOURRY
 */
class AGraphicsComponent : virtual public IGraphicsComponent
{
public:
 /**
  * @brief The destructor of the AGraphicsComponent class
  * @version v0.1.0
  * @since v0.1.0
  * @author Aubane NOURRY
  */
 ~AGraphicsComponent() override = default;

 /**
  * @brief The update function of the component.
  * This is meant to be runt by the parent object and update the component every frame
  * @note This is a pure virtual function and must be implemented in the child class
  * @see IGraphicsComponent::runComponent
  * @version v0.1.0
  * @since v0.1.0
  * @author Aubane NOURRY
  */
 void runComponent() override = 0;

 /**
  * @brief Returns a non-owning and non-null pointer to the owner of the component
  * @see IComponent::getOwner
  * @return the owner of the component
  * @version v0.1.0
  * @since v0.1.0
  * @author Aubane NOURRY
  */
 [[nodiscard]] IObject* getOwner() override;

 /**
  * @brief Get the meta of the component
  * @see IComponent::getMeta
  * @return the meta of the component
  * @version v0.1.0
  * @since v0.1.0
  * @author Aubane NOURRY
  */
 [[nodiscard]] IMeta& getMeta() const override;

protected:
 /**
  * @brief The constructor of the AGraphicsComponent class
  * @param owner The owner of the component
  * @param meta The meta of the component
  * @version v0.1.0
  * @since v0.1.0
  * @author Aubane NOURRY
  */
 AGraphicsComponent(IObject* owner, IMeta& meta);

 /**
  * @brief The owner of the component
  * @version v0.1.0
  * @since v0.1.0
  * @author Aubane NOURRY
 */
 IObject* _owner;

 /**
  * @brief The meta of the component
  * @version v0.1.0
  * @since v0.1.0
  * @author Aubane NOURRY
  */
 IMeta& _meta;
};

#endif //AGRAPHICSCOMPONENT_HPP

/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** CPPMonoBehaviour.hpp
*/

#ifndef CPPMONOBEHAVIOUR_HPP
#define CPPMONOBEHAVIOUR_HPP

#include "AComponent.hpp"

/**
 * @class CPPMonoBehaviour
 * @brief This class is the abstract class for the All the MonoBehaviours in the game
 * @version v0.1.0
 * @since v0.1.0
 * @author Marius PAIN
 */
class CPPMonoBehaviour : virtual public AComponent
{
public:
 /**
  * @brief The destructor of the CPPMonoBehaviour class
  * @version v0.1.0
  * @since v0.1.0
  * @author Marius PAIN
  */
 ~CPPMonoBehaviour() override = default;

 /**
  * @brief The before function of the component
  * This is meant to be runt by the parent object and update the component before the rendering
  * @note This is not supposed to be overriden in the child class (you should modify the before function instead)
  * @see IComponent::beforeRendering
  * @version v0.1.0
  * @since v0.1.0
  * @author Marius PAIN
  */
 void beforeRendering() final;

 /**
  * @brief The update function of the component.
  * This is meant to be runt by the parent object and update the component every frame
  * @note This is not supposed to be overriden in the child class (you should modify the update function instead)
  * @see IComponent::runComponent
  * @version v0.1.0
  * @since v0.1.0
  * @author Marius PAIN
  */
 void runComponent() final;

 /**
  * @brief The after function of the component
  * This is meant to be runt by the parent object and update the component after the rendering
  * @note This is not supposed to be overriden in the child class (you should modify the after function instead)
  * @see IComponent::afterRendering
  * @version v0.1.0
  * @since v0.1.0
  * @author Marius PAIN
  */
 void afterRendering() final;

 /**
  * @brief The start function of the component
  * This is meant to be runt by the parent object and initialize the component
  * @note This is not a pure virtual function, but it can be overriden in the child class
  * @see IComponent::beforeRendering
  * @version v0.1.0
  * @since v0.1.0
  * @author Marius PAIN
  */
 void before();

 /**
  * @brief The after function of the component
  * This is meant to be runt by the parent object and update the component after the rendering
  * @note This is a pure virtual function and must be implemented in the child class
  * @see IComponent::afterRendering
  * @version v0.1.0
  * @since v0.1.0
  * @author Marius PAIN
  */
 virtual void update() = 0;

 /**
  * @brief The after function of the component
  * This is meant to be runt by the parent object and update the component after the rendering
  * @note This is not a pure virtual function, but it can be overriden in the child class
  * @see IComponent::afterRendering
  * @version v0.1.0
  * @since v0.1.0
  * @author Marius PAIN
  */
 void after();
};

#endif //CPPMONOBEHAVIOUR_HPP

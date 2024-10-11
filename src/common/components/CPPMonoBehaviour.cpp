/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** CPPMonoBehaviour.cpp
*/

#include "CPPMonoBehaviour.hpp"
#include "../fields/FieldGroup.hpp"
#include "../fields/FileField.hpp"

void CPPMonoBehaviour::onStart()
{
    start();
}

void CPPMonoBehaviour::onDelete()
{
    end();
}

void CPPMonoBehaviour::beforeRendering()
{
    before();
}

void CPPMonoBehaviour::runComponent()
{
    update();
}

void CPPMonoBehaviour::afterRendering()
{
    after();
}

void CPPMonoBehaviour::before()
{
}

void CPPMonoBehaviour::after()
{
}

CPPMonoBehaviour::Meta::Meta(): AMeta("CPPMonoBehaviour",
                                      "CPP file that contains the logic of an object", false,
                                      true, {
                                          new InvisibleFieldGroup({
                                              new FileField("File Path",
                                                            "The path to the file that contains the logic of the object")
                                          })
                                      })
{
}


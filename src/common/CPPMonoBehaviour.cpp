/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** CPPMonoBehaviour.cpp
*/

#include "CPPMonoBehaviour.hpp"

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

void CPPMonoBehaviour::start()
{
}

void CPPMonoBehaviour::before()
{
}

void CPPMonoBehaviour::after()
{
}

void CPPMonoBehaviour::onDestroy()
{
}


/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#ifndef IJSONREADER_HPP
#define IJSONREADER_HPP
#include <iostream>

#include "IJsonObject.hpp"

namespace json {
    class IJsonReader {
    public:
        virtual ~IJsonReader() = default;

        IJsonObject *operator<<(std::istream &input) {
            return this->read(input);
        }

        [[nodiscard]]
        virtual IJsonObject *read(std::istream &input) = 0;
    };
}

#endif //IJSONREADER_HPP

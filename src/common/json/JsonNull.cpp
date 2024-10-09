/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include "JsonNull.hpp"
using namespace json;

JsonNull::JsonNull(std::string name) noexcept: _name(std::move(name)) {
}

JsonNull::operator nullptr_t() const {
    return nullptr;
}

std::string JsonNull::stringify() const {
    return "null";
}

void JsonNull::parse(const IJsonParser & /*parser*/, const std::string &string) {
    if (string != "null") {
        throw std::runtime_error("Invalid null value");
    }
}

JsonType JsonNull::getType() const {
    return NULL_VALUE;
}

std::string JsonNull::getName() const {
    return this->_name;
}

nullptr_t JsonNull::getValue() const {
    return nullptr;
}

void JsonNull::setValue(const nullptr_t & /*value*/) {
}

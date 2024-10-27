/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include "LoggerScopes.hpp"

LoggerScopes *LoggerScopes::INSTANCE = nullptr;

LoggerScopes *LoggerScopes::getInstance() {
    if (INSTANCE == nullptr) {
        INSTANCE = new LoggerScopes();
    }
    return INSTANCE;
}

void LoggerScopes::addScope(const std::string &scope, std::ostream &output,
                            std::ostream &error) {
    if (hasScope(scope)) {
        return;
    }
    _scopes.insert({scope, {output, error}});
}

std::pair<std::ostream &, std::ostream &> &LoggerScopes::getScope(
    const std::string &scope) {
    return _scopes.at(scope);
}

void LoggerScopes::removeScope(const std::string &scope) {
    if (!hasScope(scope)) {
        return;
    }
    _scopes.erase(scope);
}

bool LoggerScopes::hasScope(const std::string &scope) const {
    return _scopes.find(scope) != _scopes.end();
}

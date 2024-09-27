/*
** EPITECH PROJECT, 2024
** Stellar-Forge
** File description:
** Uuid
*/

#include "Uuid.hpp"

UUID::UUID()
{
    uuid_clear(this->_uuid);
}

UUID::~UUID()
{
    uuid_clear(this->_uuid);
}

const uuid_t &UUID::getUuid() const
{
    return this->_uuid;
}

std::string UUID::getUuidString() const
{
    char str[37] = {0};

    uuid_unparse(this->_uuid, str);
    return std::string(str);
}

void UUID::generateUuid()
{
    uuid_generate(this->_uuid);
}

void UUID::copyUuid(uuid_t uuid)
{
    uuid_copy(this->_uuid, uuid);
}

void UUID::copyUuid(const uuid_t &uuid)
{
    uuid_copy(this->_uuid, uuid);
}

void UUID::copyUuid(UUID uuid)
{
    uuid_copy(this->_uuid, uuid._uuid);
}

bool UUID::compareUuid(uuid_t uuid)
{
    return uuid_compare(this->_uuid, uuid) == 0;
}

bool UUID::compareUuid(UUID uuid)
{
    return uuid_compare(this->_uuid, uuid._uuid) == 0;
}

void UUID::clearUuid()
{
    uuid_clear(this->_uuid);
}

bool UUID::isNullUuid()
{
    return uuid_is_null(this->_uuid);
}

void UUID::setUuidFromString(std::string uuid)
{
    uuid_parse(uuid.c_str(), this->_uuid);
}

const uuid_t &UUID::getUuidStruct() const
{
    return this->_uuid;
}

UUID &UUID::operator=(const UUID &uuid)
{
    uuid_copy(this->_uuid, uuid._uuid);
    return *this;
}

UUID &UUID::operator=(const uuid_t &uuid)
{
    uuid_copy(this->_uuid, uuid);
    return *this;
}

bool UUID::operator==(const UUID &uuid)
{
    return uuid_compare(this->_uuid, uuid._uuid) == 0;
}

bool UUID::operator==(const uuid_t &uuid)
{
    return uuid_compare(this->_uuid, uuid) == 0;
}

bool UUID::operator!=(const UUID &uuid)
{
    return uuid_compare(this->_uuid, uuid._uuid) != 0;
}

bool UUID::operator!=(const uuid_t &uuid)
{
    return uuid_compare(this->_uuid, uuid) != 0;
}

std::ostream &operator<<(std::ostream &os, const UUID &uuid)
{
    os << uuid.getUuidString();
    return os;
}

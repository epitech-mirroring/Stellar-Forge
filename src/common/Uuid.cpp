/*
** EPITECH PROJECT, 2024
** Stellar-Forge
** File description:
** Uuid
*/

#include "Uuid.hpp"

#include <array>

UUID::UUID(): _uuid()
{
    uuid_clear(this->_uuid);
}

UUID::UUID(const UUID& uuid): _uuid()
{
    uuid_copy(this->_uuid, uuid._uuid);
}

UUID::UUID(const UUID&& uuid) noexcept: _uuid()
{
    uuid_copy(this->_uuid, uuid._uuid);
}

UUID::~UUID()
{
    uuid_clear(this->_uuid);
}

const uuid_t& UUID::getUuid() const
{
    return this->_uuid;
}

std::string UUID::getUuidString() const
{
    std::array<char, 37> str{};

    uuid_unparse(this->_uuid, str.data());
    return {str.data()};
}

void UUID::generateUuid()
{
    uuid_generate(this->_uuid);
}

void UUID::copyUuid(const uuid_t& uuid)
{
    uuid_copy(this->_uuid, uuid);
}

void UUID::copyUuid(const UUID uuid)
{
    uuid_copy(this->_uuid, uuid._uuid);
}

bool UUID::compareUuid(const uuid_t& uuid) const
{
    return uuid_compare(this->_uuid, uuid) == 0;
}

bool UUID::compareUuid(const UUID& uuid) const
{
    return uuid_compare(this->_uuid, uuid._uuid) == 0;
}

void UUID::clearUuid()
{
    uuid_clear(this->_uuid);
}

bool UUID::isNullUuid() const
{
    return uuid_is_null(this->_uuid) != 0;
}

void UUID::setUuidFromString(const std::string& uuid)
{
    uuid_parse(uuid.c_str(), this->_uuid);
}

const uuid_t& UUID::getUuidStruct() const
{
    return this->_uuid;
}

UUID& UUID::operator=(const UUID& uuid)
{
    if (this == &uuid)
    {
        return *this;
    }
    uuid_copy(this->_uuid, uuid._uuid);
    return *this;
}

UUID& UUID::operator=(const uuid_t& uuid)
{
    uuid_copy(this->_uuid, uuid);
    return *this;
}


UUID& UUID::operator=(const UUID uuid)
{
    uuid_copy(this->_uuid, uuid._uuid);
    return *this;
}

UUID& UUID::operator=(uuid_t uuid)
{
    uuid_copy(this->_uuid, uuid);
    return *this;
}

bool UUID::operator==(const UUID& uuid) const
{
    return uuid_compare(this->_uuid, uuid._uuid) == 0;
}

bool UUID::operator==(const uuid_t& uuid) const
{
    return uuid_compare(this->_uuid, uuid) == 0;
}

bool UUID::operator!=(const UUID& uuid) const
{
    return uuid_compare(this->_uuid, uuid._uuid) != 0;
}

bool UUID::operator!=(const uuid_t& uuid) const
{
    return uuid_compare(this->_uuid, uuid) != 0;
}

std::ostream& operator<<(std::ostream& ostream, const UUID& uuid)
{
    ostream << uuid.getUuidString();
    return ostream;
}

/*
** EPITECH PROJECT, 2024
** Stellar-Forge
** File description:
** Uuid
*/

#include "UUID.hpp"
#include "UUIDException.hpp"

UUID::UUID(const UUID &&uuid) noexcept : _uuid(uuid._uuid) {
}

const uuids::uuid &UUID::getUuid() const {
    return this->_uuid;
}

std::string UUID::getUuidString() const {
    return to_string(this->_uuid);
}

void UUID::generateUuid() {
    try {
        std::random_device randD;
        auto seedData = std::array<int, std::mt19937::state_size>{};
        std::generate(std::begin(seedData), std::end(seedData),
                      std::ref(randD));
        std::seed_seq seq(std::begin(seedData), std::end(seedData));
        std::mt19937 generator(seq);
        uuids::uuid_random_generator gen{generator};

        this->_uuid = gen();
    } catch (const std::exception &e) {
        throw UUIDException(
            "Error while generating UUID : " + std::string(e.what()));
    }
}

void UUID::copyUuid(const UUID &uuid) {
    this->_uuid = uuid._uuid;
}

bool UUID::compareUuid(const UUID &uuid) const {
    return this->_uuid == uuid._uuid;
}

bool UUID::isNullUuid() const {
    return this->_uuid.is_nil();
}

void UUID::setUuidFromString(const std::string &uuid) {
    try {
        const std::optional<uuids::uuid> optUuid =
                uuids::uuid::from_string(uuid);
        if (!optUuid.has_value()) {
            throw UUIDException(
                "Error while setting UUID from string : invalid UUID");
        }
        this->_uuid = optUuid.value();
    } catch (const std::exception &e) {
        throw UUIDException(
            "Error while setting UUID from string : " + std::string(e.what()));
    }
}

UUID &UUID::operator=(const UUID &uuid) {
    if (this == &uuid) {
        return *this;
    }
    this->_uuid = uuid._uuid;
    return *this;
}

bool UUID::operator==(const UUID &uuid) const {
    return this->_uuid == uuid._uuid;
}

bool UUID::operator!=(const UUID &uuid) const {
    return this->_uuid != uuid._uuid;
}

bool UUID::operator<(const UUID &uuid) const {
    return this->_uuid < uuid._uuid;
}

std::ostream &operator<<(std::ostream &ostream, const UUID &uuid) {
    ostream << uuid.getUuidString();
    return ostream;
}

UUID &UUID::operator=(UUID &&uuid) noexcept {
    if (this != &uuid) {
        this->_uuid = uuid._uuid;
        uuid._uuid = {};
    }

    return *this;
}

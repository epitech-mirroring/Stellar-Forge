/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** AudioSource.cpp
**/

#include "AudioSource.hpp"
#include "common/fields/StringField.hpp"
#include "common/json/JsonNumber.hpp"
#include "common/json/JsonString.hpp"
#include "common/json/JsonBoolean.hpp"

AudioSource::AudioSource(IObject *owner, const json::JsonObject *data) : AComponent(
    owner, new Meta(this), data), _clipPath(""), _volume(0), _loop(false), _playOnAwake(false) {
}

AudioSource::AudioSource(IObject *owner, const std::string &clipPath, int volume, bool loop, bool playOnAwake) : AComponent(
    owner, new Meta(this)), _clipPath(clipPath), _volume(volume), _loop(loop), _playOnAwake(playOnAwake) {
    _buffer.loadFromFile(_clipPath);
    _sound.setBuffer(_buffer);
    _sound.setVolume(_volume);
    _sound.setLoop(_loop);
    if (_playOnAwake)
        _sound.play();
}

AudioSource::AudioSource(IObject *owner) : AComponent(owner, new Meta(this)) {
}

AudioSource::Meta::Meta(AudioSource *owner): _owner(owner), _fieldGroup({}) {
    auto fields = std::vector<IField *>();
    auto *field = new StringField("ClipPath", "The path to the audio clip",
                                  [this](const std::string &value) {
                                      this->_owner->_clipPath = value;
                                      this->_owner->_buffer.loadFromFile(value);
                                      this->_owner->_sound.setBuffer(this->_owner->_buffer);
                                  },
                                  [this] { return this->_owner->_clipPath; });
    _fieldGroup = InvisibleFieldGroup({field});
}

std::string AudioSource::Meta::getName() const {
    return "AudioSource";
}

std::string AudioSource::Meta::getDescription() const {
    return "An AudioSource component plays audio clips.";
}

bool AudioSource::Meta::isUnique() const {
    return false;
}

bool AudioSource::Meta::canBeRemoved() const {
    return true;
}

std::vector<const IComponent::IMeta::IFieldGroup *> AudioSource::Meta::getFieldGroups() const {
    return {&_fieldGroup};
}

json::IJsonObject *AudioSource::serializeData() {
    auto *const data = new json::JsonObject("data");
    data->add(new json::JsonString(_clipPath, "path"));
    data->add(new json::JsonNumber(_volume, "volume"));
    data->add(new json::JsonBoolean(_loop, "loop"));
    data->add(new json::JsonBoolean(_playOnAwake, "playOnAwake"));
    return data;
}

void AudioSource::deserialize(const json::IJsonObject *data) {
    if (data == nullptr || data->getType() != json::OBJECT) {
        return;
    }
    const auto *const obj = dynamic_cast<const json::JsonObject *>(data);
    if (obj->contains("path")) {
        _clipPath = obj->getValue<json::JsonString>("path")->getValue();
        _buffer.loadFromFile(_clipPath);
    }
    if (obj->contains("volume")) {
        _volume = obj->getValue<json::JsonNumber>("volume")->getIntValue();
    }
    if (obj->contains("loop")) {
        _loop = obj->getValue<json::JsonBoolean>("loop")->getValue();
    }
    if (obj->contains("playOnAwake")) {
        _playOnAwake = obj->getValue<json::JsonBoolean>("playOnAwake")->getValue();
    }
    _sound.setBuffer(_buffer);
    _sound.setVolume(_volume);
    _sound.setLoop(_loop);
    if (_playOnAwake) {
        _sound.play();
    }
}

AudioSource *AudioSource::clone(IObject *owner) const {
    return new AudioSource(owner, _clipPath, _volume, _loop, _playOnAwake);
}

void AudioSource::runComponent() {
}

void AudioSource::play() {
    _sound.play();
}

void AudioSource::pause() {
    _sound.pause();
}

void AudioSource::stop() {
    _sound.stop();
}

void AudioSource::setVolume(int volume) {
    _volume = volume;
    _sound.setVolume(volume);
}

void AudioSource::setLoop(bool loop) {
    _loop = loop;
    _sound.setLoop(loop);
}

void AudioSource::mute() {
    _mute = !_mute;
    if (_mute)
        _sound.setVolume(0);
    else
        _sound.setVolume(_volume);
}

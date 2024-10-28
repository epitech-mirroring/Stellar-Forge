/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** AudioSource.cpp
**/

#include "AudioSource.hpp"

#include <utility>
#include "common/fields/FileField.hpp"
#include "common/fields/FloatField.hpp"
#include "common/fields/BooleanField.hpp"
#include "common/json/JsonString.hpp"
#include "common/json/JsonNull.hpp"

AudioSource::AudioSource(IObject *owner, const json::JsonObject *data) : AComponent(
    owner, new Meta(this), data) {
    this->deserializeFields(data);
}

AudioSource::AudioSource(IObject *owner, std::string clipPath, const float volume, const bool loop, const bool playOnAwake)
    : AComponent(owner, new Meta(this)), _clipPath(std::move(clipPath)), _volume(volume), _loop(loop), _playOnAwake(playOnAwake) {
    _buffer.loadFromFile(_clipPath);
    _sound.setBuffer(_buffer);
    _sound.setVolume(_volume);
    _sound.setLoop(_loop);
    if (_playOnAwake) {
        _sound.play();
    }
}

AudioSource::AudioSource(IObject *owner) : AComponent(owner, new Meta(this)) {
}

AudioSource::Meta::Meta(AudioSource *owner): _owner(owner), _fieldGroup({}) {
    auto fields = std::vector<IField *>();
    auto *field = new FileField("ClipPath", "The path to the audio clip",
                                  [this](const std::string &value) {
                                      this->_owner->_clipPath = value;
                                      this->_owner->_buffer.loadFromFile(value);
                                      this->_owner->_sound.setBuffer(this->_owner->_buffer);
                                  },
                                  [this] { return this->_owner->_clipPath; });
    auto *volumeField = new FloatField("Volume", "The volume of the audio clip",
                                       [this](const float value) {
                                           this->_owner->_volume = value;
                                           this->_owner->_sound.setVolume(value);
                                       },
                                       [this] { return this->_owner->_volume; });
    auto *loopField = new BooleanField("Loop", "Enable or disable looping of the audio clip",
                                       [this](const bool value) {
                                           this->_owner->_loop = value;
                                           this->_owner->_sound.setLoop(value);
                                       },
                                       [this] { return this->_owner->_loop; });
    auto *playOnAwakeField = new BooleanField("PlayOnAwake", "Enable or disable auto-plau of the audio clip on start",
                                       [this](const bool value) {
                                           this->_owner->_playOnAwake = value;
                                           if (value) {
                                               this->_owner->_sound.play();
                                           }
                                       },
                                       [this] { return this->_owner->_playOnAwake; });


    _fieldGroup = InvisibleFieldGroup({field, volumeField, loopField, playOnAwakeField});
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
    return new json::JsonNull();
}

void AudioSource::deserialize(const json::IJsonObject *data) {
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

void AudioSource::setVolume(const float volume) {
    _volume = volume;
    _sound.setVolume(volume);
}

void AudioSource::setLoop(const bool loop) {
    _loop = loop;
    _sound.setLoop(loop);
}

void AudioSource::mute() {
    _mute = !_mute;
    if (_mute) {
        _sound.setVolume(0);
    } else {
        _sound.setVolume(_volume);
    }
}

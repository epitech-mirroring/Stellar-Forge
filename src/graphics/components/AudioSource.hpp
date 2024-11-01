/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** AudioSource.hpp
**/

#ifndef AUDIO_SOURCE_HPP
#define AUDIO_SOURCE_HPP

#include <SFML/Audio.hpp>

#include "StellarForge/Common/components/AComponent.hpp"
#include "StellarForge/Common/fields/groups/InvisibleFieldGroup.hpp"

/**
 * @class AudioSource
 * @brief An audio component for playing, pausing, and controlling sound clips.
 * @details The AudioSource class allows the integration of audio clips, supporting features like volume control,
 *          looping, muting, and options for autoplay. It utilizes SFML's sound functionalities for playback.
 * @version v0.1.0
 * @since v0.1.0
 * @author Aubane NOURRY
 */
class AudioSource final : public AComponent {
private:
 sf::Sound _sound; /**< The sound instance used for playback. */
 sf::SoundBuffer _buffer; /**< The buffer containing the audio data. */
 std::string _clipPath; /**< Path to the audio clip file. */
 float _volume{}; /**< The playback volume level. */
 bool _loop{}; /**< Flag for enabling/disabling audio looping. */
 bool _isPlaying{}; /**< Status flag indicating if the audio is currently playing. */
 bool _mute{}; /**< Flag to mute/unmute the audio. */
 bool _playOnAwake{};
 /**< Flag to play audio automatically on component initialization. */

public:
 /**
  * @brief Primary constructor for the AudioSource class.
  * @param owner The owner of this audio component.
  * @details Initializes an AudioSource instance associated with the given owner.
  * @version v0.1.0
  * @since v0.1.0
  */
 explicit AudioSource(IObject *owner);

 /**
  * @brief Overloaded constructor for AudioSource with initial parameters.
  * @param owner The owner of this audio component.
  * @param clipPath Path to the audio clip file.
  * @param volume Initial volume level for playback.
  * @param loop Boolean to enable or disable looping.
  * @param playOnAwake Boolean to enable auto-playback on initialization.
  * @version v0.1.0
  * @since v0.1.0
  */
 AudioSource(IObject *owner, std::string clipPath, float volume, bool loop,
             bool playOnAwake);

 /**
  * @brief Constructor that initializes AudioSource with JSON data.
  * @param owner The owner of this audio component.
  * @param data JSON object with initialization parameters.
  * @details Allows AudioSource to be configured using JSON for added flexibility.
  * @version v0.1.0
  * @since v0.1.0
  */
 AudioSource(IObject *owner, const json::JsonObject *data);

 /**
  * @brief Destructor for the AudioSource class.
  * @details Cleans up resources used by the AudioSource instance.
  * @version v0.1.0
  * @since v0.1.0
  */
 ~AudioSource() override = default;

  /**
   * @brief Serializes the audio component's data into a JSON format.
   * @return A pointer to the JSON representation of the component's data.
   * @version v0.1.0
   * @since v0.1.0
   */
  [[nodiscard]] json::IJsonObject *serializeData() const override;

 /**
  * @brief Deserializes JSON data into the AudioSource component.
  * @param data The JSON object containing the data to initialize.
  * @version v0.1.0
  * @since v0.1.0
  */
 void deserialize(const json::IJsonObject *data) override;

 /**
  * @brief Creates a clone of the AudioSource component.
  * @param owner The new owner of the cloned component.
  * @return A pointer to the cloned AudioSource component.
  * @version v0.1.0
  * @since v0.1.0
  */
 [[nodiscard]] AudioSource *clone(IObject *owner) const override;

 /**
  * @brief Method to process or update the audio component.
  * @details Called each frame to manage playback and control state.
  * @version v0.1.0
  * @since v0.1.0
  */
 void runComponent() override;

 /**
  * @brief Plays the audio clip.
  * @version v0.1.0
  * @since v0.1.0
  */
 void play();

 /**
  * @brief Pauses the audio clip if it is currently playing.
  * @version v0.1.0
  * @since v0.1.0
  */
 void pause();

 /**
  * @brief Stops the audio clip playback.
  * @version v0.1.0
  * @since v0.1.0
  */
 void stop();

 /**
  * @brief Sets the audio volume.
  * @param volume The volume level to set.
  * @version v0.1.0
  * @since v0.1.0
  */
 void setVolume(float volume);

 /**
  * @brief Configures looping for the audio clip.
  * @param loop Boolean to enable or disable looping.
  * @version v0.1.0
  * @since v0.1.0
  */
 void setLoop(bool loop);

 /**
  * @brief Toggles mute on or off.
  * @version v0.1.0
  * @since v0.1.0
  */
 void mute();

 /**
  * @class Meta
  * @brief The metaclass for AudioSource, providing metadata for reflection and UI.
  * @version v0.1.0
  * @since v0.1.0
  */
 class Meta final : public IMeta {
 protected:
  AudioSource *_owner; /**< The AudioSource instance associated with this Meta object. */
  InvisibleFieldGroup _fieldGroup; /**< Field group for organizing invisible fields. */

 public:
  /**
   * @brief Constructor for the Meta class of AudioSource.
   * @param owner Pointer to the AudioSource instance this meta data is for.
   * @version v0.1.0
   * @since v0.1.0
   */
  explicit Meta(AudioSource *owner);

  /**
   * @brief Returns the name of the AudioSource component.
   * @return The name of the component.
   * @version v0.1.0
   * @since v0.1.0
   */
  [[nodiscard]] std::string getName() const override;

  /**
   * @brief Provides a description of the AudioSource component.
   * @return A descriptive string.
   * @version v0.1.0
   * @since v0.1.0
   */
  [[nodiscard]] std::string getDescription() const override;

  /**
   * @brief Indicates if the AudioSource component is unique.
   * @return Boolean value indicating uniqueness.
   * @version v0.1.0
   * @since v0.1.0
   */
  [[nodiscard]] bool isUnique() const override;

  /**
   * @brief Determines if the AudioSource component can be removed.
   * @return Boolean value indicating if it can be removed.
   * @version v0.1.0
   * @since v0.1.0
   */
  [[nodiscard]] bool canBeRemoved() const override;

  /**
   * @brief Gets the field groups associated with this component.
   * @return A vector of field group pointers.
   * @version v0.1.0
   * @since v0.1.0
   */
  [[nodiscard]] std::vector<const IFieldGroup *> getFieldGroups() const override;
 };
};

#endif // AUDIO_SOURCE_HPP

/*
** EPITECH PROJECT, 2024
** Stellar-Forge components
** File description:
** UIButton.hpp
**/

#ifndef UIBUTTON_HPP
#define UIBUTTON_HPP

#include "IGraphicsComponent.hpp"
#include "common/components/AComponent.hpp"
#include "common/fields/groups/InvisibleFieldGroup.hpp"

#include "common/event/EventSystem.hpp"

class UIButton final : public AComponent {
public:
  UIButton(IObject *owner, float rectX, float rectY, float width, float height, std::string buttonId);
  UIButton(IObject *owner, const json::JsonObject *data);
  ~UIButton() override = default;

  [[nodiscard]] json::IJsonObject *serializeData() override;
  void deserialize(const json::IJsonObject *data) override;
  [[nodiscard]] UIButton *clone(IObject *owner) const override;

  void onPressed(const EventData &eventData) const;
  void onReleased(const EventData &eventData) const;

  bool inButton(const sf::Event::MouseButtonEvent *mousePos) const;

  void runComponent() override;

  class Meta final : public IMeta {
  protected:
    UIButton *_owner;
    InvisibleFieldGroup _fieldGroup;

  public:
    explicit Meta(UIButton *owner);
    [[nodiscard]] std::string getName() const override;
    [[nodiscard]] std::string getDescription() const override;
    [[nodiscard]] bool isUnique() const override;
    [[nodiscard]] bool canBeRemoved() const override;
    [[nodiscard]] std::vector<const IFieldGroup *> getFieldGroups() const override;
  };

private:
  float _rectX{};
  float _rectY{};
  float _width{};
  float _height{};
  std::string _buttonId;
};

#endif // UIBUTTON_HPP

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

class UIButton : public AComponent {
  UIButton(IObject *owner, int x, int y, int width, int height, std::string id);
  UIButton(IObject *owner, const json::JsonObject *data);
  ~UIButton() override = default;

  [[nodiscard]] json::IJsonObject *serializeData() override;
  void deserialize(const json::IJsonObject *data) override;
  [[nodiscard]] UIButton *clone(IObject *owner) const override;

  void onPressed(const EventData &eventData);
  void onReleased(const EventData &eventData);

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
  sf::RectangleShape _shape;
  int _x;
  int _y;
  int _width;
  int _height;
  std::string _id;
};

#endif // UIBUTTON_HPP
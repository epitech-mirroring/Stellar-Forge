//
// Created by marius_pain on 02/10/24.
//

#ifndef AMETA_HPP
#define AMETA_HPP

#include "IComponent.hpp"

class AMeta : virtual public IComponent::IMeta
{
public:
    AMeta(std::string name, std::string description, bool isUnique, bool isRemovable,
          std::vector<IFieldGroup*>&& fieldGroups);
    ~AMeta() override = default;

    [[nodiscard]] std::string getName() const override;
    [[nodiscard]] std::string getDescription() const override;
    [[nodiscard]] bool isUnique() const override;
    [[nodiscard]] bool canBeRemoved() const override;
    [[nodiscard]] std::vector<IFieldGroup*> getFieldGroups() const override;

private:
    std::string _name;
    std::string _description;
    std::vector<IFieldGroup*> _fieldGroups;
    bool _isUnique{};
    bool _isRemovable{};
};

#endif //AMETA_HPP

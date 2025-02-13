#pragma once

#include "../Sets/Base/Set.h"
#include "Base/Property.h"

namespace SatisfactorySave {

    class SetProperty : public Property {
    public:
        static constexpr std::string_view TypeName = "SetProperty";

        SetProperty(PropertyTag tag, std::string parentClassName);

        void serialize(Archive& ar) override;

        void accept(PropertyVisitor& v) override;

        [[nodiscard]] const FName& setType() const {
            return Tag.InnerType;
        }

        [[nodiscard]] const std::unique_ptr<Set>& set() const {
            return set_;
        }

    protected:
        std::string parentClassName_;
        std::unique_ptr<Set> set_;
    };
} // namespace SatisfactorySave

#pragma once

#include <vector>

#include "../Structs/Base/Struct.h"
#include "../UE/Misc/Guid.h"
#include "Property.h"

namespace SatisfactorySave {

    class StructProperty : public Property {
    public:
        using Property::Property;

        void serialize(Archive& ar) override;

        void accept(PropertyVisitor& v) override;

        [[nodiscard]] const std::string& structName() const {
            return tag_.StructName.Name;
        }

        [[nodiscard]] const FGuid& guid() const {
            return tag_.StructGuid;
        }

        [[nodiscard]] const std::unique_ptr<Struct>& value() const {
            return struct_;
        }

    protected:
        std::unique_ptr<Struct> struct_;
    };
} // namespace SatisfactorySave

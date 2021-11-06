#ifndef SATISFACTORY3DMAP_ENUMPROPERTY_H
#define SATISFACTORY3DMAP_ENUMPROPERTY_H

#include "Property.h"

namespace Satisfactory3DMap {

    class EnumProperty : public Property {
    public:
        EnumProperty(std::string property_name, std::string property_type, std::istream& stream);

        void serialize(std::ostream& stream) const override;

        void accept(PropertyVisitor& v) override;

        const std::string& enumType() const {
            return enum_type_;
        }

        const std::string& value() const {
            return value_;
        }

    protected:
        std::string enum_type_;
        std::string value_;
    };
} // namespace Satisfactory3DMap

#endif // SATISFACTORY3DMAP_ENUMPROPERTY_H

#ifndef SATISFACTORY3DMAP_INT64PROPERTY_H
#define SATISFACTORY3DMAP_INT64PROPERTY_H

#include "Property.h"

namespace Satisfactory3DMap {

    class Int64Property : public Property {
    public:
        Int64Property(PropertyTag tag, std::istream& stream);

        void serialize(std::ostream& stream) const override;

        void accept(PropertyVisitor& v) override;

        int64_t value() const {
            return value_;
        }

    protected:
        int64_t value_;
    };
} // namespace Satisfactory3DMap

#endif // SATISFACTORY3DMAP_INT64PROPERTY_H

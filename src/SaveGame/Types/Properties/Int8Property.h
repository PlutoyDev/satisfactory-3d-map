#ifndef SATISFACTORY3DMAP_INT8PROPERTY_H
#define SATISFACTORY3DMAP_INT8PROPERTY_H

#include "Property.h"

namespace Satisfactory3DMap {

    class Int8Property : public Property {
    public:
        Int8Property(PropertyTag tag, std::istream& stream);

        void serialize(std::ostream& stream) const override;

        void accept(PropertyVisitor& v) override;

        int8_t value() const {
            return value_;
        }

    protected:
        int8_t value_;
    };
} // namespace Satisfactory3DMap

#endif // SATISFACTORY3DMAP_INT8PROPERTY_H

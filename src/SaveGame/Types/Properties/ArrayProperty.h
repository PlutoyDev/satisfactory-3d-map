#ifndef SATISFACTORY3DMAP_ARRAYPROPERTY_H
#define SATISFACTORY3DMAP_ARRAYPROPERTY_H

#include <vector>

#include "Property.h"

namespace Satisfactory3DMap {

    class ArrayProperty : public Property {
    public:
        ArrayProperty(std::string property_name, std::string property_type, std::istream& stream);

        const std::string& arrayType() const {
            return array_type_;
        }

    protected:
        std::string array_type_;
    };
} // namespace Satisfactory3DMap

#endif // SATISFACTORY3DMAP_ARRAYPROPERTY_H

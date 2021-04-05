#ifndef SATISFACTORY3DMAP_STRUCTPROPERTY_H
#define SATISFACTORY3DMAP_STRUCTPROPERTY_H

#include <vector>

#include "../Guid.h"
#include "Property.h"

namespace Satisfactory3DMap {

    class StructProperty : public Property {
    public:
        StructProperty(std::string property_name, std::string property_type, std::istream& stream);

        const std::string& structName() const {
            return struct_name_;
        }

        std::string guid() const {
            return guid_.toString();
        }

    protected:
        std::string struct_name_;
        Guid guid_;
    };
} // namespace Satisfactory3DMap

#endif // SATISFACTORY3DMAP_STRUCTPROPERTY_H

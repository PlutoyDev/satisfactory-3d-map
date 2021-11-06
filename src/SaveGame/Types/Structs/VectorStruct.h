#ifndef SATISFACTORY3DMAP_VECTORSTRUCT_H
#define SATISFACTORY3DMAP_VECTORSTRUCT_H

#include <glm/vec3.hpp>

#include "Struct.h"

namespace Satisfactory3DMap {

    class VectorStruct : public Struct {
    public:
        VectorStruct(std::string struct_name, std::istream& stream);

        void serialize(std::ostream& stream) const override;

        void accept(StructVisitor& v) override;

        const glm::vec3& value() const {
            return value_;
        }

    protected:
        glm::vec3 value_;
    };
} // namespace Satisfactory3DMap

#endif // SATISFACTORY3DMAP_VECTORSTRUCT_H

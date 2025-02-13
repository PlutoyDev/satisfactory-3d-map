#pragma once

#include "../UE/Satisfactory/ObjectReference.h"
#include "Base/ArrayImpl.h"

namespace SatisfactorySave {

    class ObjectArray : public ArrayImpl<ObjectArray, FObjectReferenceDisc> {
    public:
        static constexpr std::string_view TypeName = "ObjectProperty";
    };
} // namespace SatisfactorySave

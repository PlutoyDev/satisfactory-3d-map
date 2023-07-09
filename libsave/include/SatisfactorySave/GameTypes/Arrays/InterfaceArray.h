#pragma once

#include "../Misc/ObjectReference.h"
#include "Base/ArrayImpl.h"

namespace SatisfactorySave {

    class InterfaceArray : public ArrayImpl<InterfaceArray, ObjectReference> {
    public:
        static constexpr std::string_view TypeName = "InterfaceProperty";
    };
} // namespace SatisfactorySave

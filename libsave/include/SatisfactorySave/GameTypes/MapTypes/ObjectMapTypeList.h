#pragma once

#include "../UE/Satisfactory/ObjectReference.h"
#include "Base/MapTypeListImpl.h"

namespace SatisfactorySave {

    class ObjectMapTypeList : public MapTypeListImpl<ObjectMapTypeList, FObjectReferenceDisc> {
    public:
        static constexpr std::string_view TypeName = "ObjectProperty";
    };
} // namespace SatisfactorySave

#pragma once

#include "../UE/UObject/SoftObjectPath.h"
#include "Base/ArrayImpl.h"

namespace SatisfactorySave {

    class SoftObjectArray : public ArrayImpl<SoftObjectArray, FSoftObjectPath> {
    public:
        static constexpr std::string_view TypeName = "SoftObjectProperty";
    };
} // namespace SatisfactorySave

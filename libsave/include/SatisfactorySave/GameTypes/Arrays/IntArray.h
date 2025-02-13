#pragma once

#include "Base/ArrayImpl.h"

namespace SatisfactorySave {

    class IntArray : public ArrayImpl<IntArray, int32_t> {
    public:
        static constexpr std::string_view TypeName = "IntProperty";
    };
} // namespace SatisfactorySave

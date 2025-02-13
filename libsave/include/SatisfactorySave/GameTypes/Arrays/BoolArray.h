#pragma once

#include "Base/ArrayImpl.h"

namespace SatisfactorySave {

    class BoolArray : public ArrayImpl<BoolArray, int8_t> {
    public:
        static constexpr std::string_view TypeName = "BoolProperty";
    };
} // namespace SatisfactorySave

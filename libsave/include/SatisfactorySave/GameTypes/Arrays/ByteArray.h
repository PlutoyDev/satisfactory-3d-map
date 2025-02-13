#pragma once

#include "Base/ArrayImpl.h"

namespace SatisfactorySave {

    class ByteArray : public ArrayImpl<ByteArray, int8_t> {
    public:
        static constexpr std::string_view TypeName = "ByteProperty";
    };
} // namespace SatisfactorySave

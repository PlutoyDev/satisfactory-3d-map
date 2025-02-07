#pragma once

#include <string>

#include "Base/ArrayImpl.h"

namespace SatisfactorySave {

    class StrArray : public ArrayImpl<StrArray, std::string> {
    public:
        static constexpr std::string_view TypeName = "StrProperty";
    };
} // namespace SatisfactorySave

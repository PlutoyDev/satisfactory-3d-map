#pragma once

#include "Base/PropertyImpl.h"

namespace SatisfactorySave {

    class UInt64Property : public PropertyImpl<UInt64Property, uint64_t> {
    public:
        static constexpr std::string_view TypeName = "UInt64Property";

        using PropertyImpl<UInt64Property, uint64_t>::PropertyImpl;
    };
} // namespace SatisfactorySave

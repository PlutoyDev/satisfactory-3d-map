#pragma once

#include <string>

#include "Base/PropertyImpl.h"

namespace SatisfactorySave {

    class StrProperty : public PropertyImpl<StrProperty, std::string> {
    public:
        static constexpr std::string_view TypeName = "StrProperty";

        using PropertyImpl<StrProperty, std::string>::PropertyImpl;
    };
} // namespace SatisfactorySave

#pragma once

#include "../../../IO/Archive/Archive.h"

namespace SatisfactorySave {

    // TQuat
    template<typename T>
    struct TQuat {
        T X = 0.0;
        T Y = 0.0;
        T Z = 0.0;
        T W = 0.0;

        void serialize(Archive& ar) {
            ar << X;
            ar << Y;
            ar << Z;
            ar << W;
        }

        static inline const TQuat<T> Identity{0.0, 0.0, 0.0, 1.0};
    };

    using FQuat = TQuat<double>;
} // namespace SatisfactorySave

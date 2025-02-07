#pragma once

#include "../../../IO/Archive/Archive.h"

namespace SatisfactorySave {

    // FColor
    struct FColor {
    public:
        uint8_t B = 0;
        uint8_t G = 0;
        uint8_t R = 0;
        uint8_t A = 0;

        void serialize(Archive& ar) {
            ar << B;
            ar << G;
            ar << R;
            ar << A;
        }
    };

    // FLinearColor
    struct FLinearColor {
        float R = 0.0f;
        float G = 0.0f;
        float B = 0.0f;
        float A = 0.0f;

        void serialize(Archive& ar) {
            ar << R;
            ar << G;
            ar << B;
            ar << A;
        }
    };
} // namespace SatisfactorySave

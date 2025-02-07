#pragma once

#include "../UE/Satisfactory/RailroadTrackPosition.h"
#include "Base/StructImpl.h"

namespace SatisfactorySave {

    class RailroadTrackPositionStruct : public StructImpl<RailroadTrackPositionStruct, FRailroadTrackPosition> {
    public:
        using StructImpl<RailroadTrackPositionStruct, FRailroadTrackPosition>::StructImpl;
    };
} // namespace SatisfactorySave

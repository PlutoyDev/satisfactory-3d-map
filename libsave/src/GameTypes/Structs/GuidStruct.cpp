#include "GameTypes/Structs/GuidStruct.h"

#include "GameTypes/Structs/StructVisitor.h"

void SatisfactorySave::GuidStruct::serialize(Archive& ar) {
    ar << guid_;
}

void SatisfactorySave::GuidStruct::accept(SatisfactorySave::StructVisitor& v) {
    v.visit(*this);
}

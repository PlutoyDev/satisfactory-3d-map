#include "GameTypes/Arrays/StrArray.h"

#include "GameTypes/Arrays/ArrayVisitor.h"

void Satisfactory3DMap::StrArray::serialize(Archive& ar) {
    ar << array_;
}

void Satisfactory3DMap::StrArray::accept(Satisfactory3DMap::ArrayVisitor& v) {
    v.visit(*this);
}

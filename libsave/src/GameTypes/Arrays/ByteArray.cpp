#include "GameTypes/Arrays/ByteArray.h"

#include "GameTypes/Arrays/ArrayVisitor.h"

void Satisfactory3DMap::ByteArray::serialize(Archive& ar) {
    ar << array_;
}

void Satisfactory3DMap::ByteArray::accept(Satisfactory3DMap::ArrayVisitor& v) {
    v.visit(*this);
}

#include "IntArray.h"

#include "ArrayVisitor.h"

void Satisfactory3DMap::IntArray::serialize(Archive& ar) {
    ar << array_;
}

void Satisfactory3DMap::IntArray::accept(Satisfactory3DMap::ArrayVisitor& v) {
    v.visit(*this);
}

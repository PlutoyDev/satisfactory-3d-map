#include "Int64Property.h"

#include <utility>

#include "PropertyVisitor.h"
#include "Utils/StreamUtils.h"

Satisfactory3DMap::Int64Property::Int64Property(
    std::string property_name, std::string property_type, std::istream& stream)
    : Property(std::move(property_name), std::move(property_type), stream) {
    read_assert_zero<int8_t>(stream);
    value_ = read<int64_t>(stream);
}

void Satisfactory3DMap::Int64Property::accept(Satisfactory3DMap::PropertyVisitor& v) {
    v.visit(*this);
}

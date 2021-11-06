#include "EnumProperty.h"

#include <utility>

#include "PropertyVisitor.h"
#include "Utils/StreamUtils.h"

Satisfactory3DMap::EnumProperty::EnumProperty(std::string property_name, std::string property_type,
    std::istream& stream)
    : Property(std::move(property_name), std::move(property_type), stream) {
    enum_type_ = read_length_string(stream);
    read_assert_zero<int8_t>(stream);
    value_ = read_length_string(stream);
}

void Satisfactory3DMap::EnumProperty::serialize(std::ostream& stream) const {
    Property::serialize(stream);
    write_length_string(stream, enum_type_);
    write<int8_t>(stream, 0);
    write_length_string(stream, value_);
}

void Satisfactory3DMap::EnumProperty::accept(Satisfactory3DMap::PropertyVisitor& v) {
    v.visit(*this);
}

#include "NameProperty.h"

#include <utility>

#include "PropertyVisitor.h"
#include "Utils/StreamUtils.h"

Satisfactory3DMap::NameProperty::NameProperty(
    std::string property_name, std::string property_type, std::istream& stream)
    : Property(std::move(property_name), std::move(property_type), stream) {
    read_assert_zero<int8_t>(stream);
    value_ = read_length_string(stream);
}

void Satisfactory3DMap::NameProperty::accept(Satisfactory3DMap::PropertyVisitor& v) {
    v.visit(*this);
}

#include "StructProperty.h"

#include <utility>

#include "Utils/StreamUtils.h"

Satisfactory3DMap::StructProperty::StructProperty(
    std::string property_name, std::string property_type, std::istream& stream)
    : Property(std::move(property_name), std::move(property_type), stream) {
    struct_name_ = read_length_string(stream);
    guid_ = Guid(stream);
    read_assert_zero<int8_t>(stream);

    buf_ = read_vector<char>(stream, size_); // TODO
}

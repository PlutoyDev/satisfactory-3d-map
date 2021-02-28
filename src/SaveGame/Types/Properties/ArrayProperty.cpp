#include "ArrayProperty.h"

#include <utility>

#include "../../Utils/StreamUtils.h"

SatisfactorySaveGame::ArrayProperty::ArrayProperty(
    std::string property_name, std::string property_type, std::istream& stream)
    : Property(std::move(property_name), std::move(property_type), stream) {
    array_type_ = read_length_string(stream);
    read_assert_zero<int8_t>(stream);
    stream.ignore(size_); // TODO
}

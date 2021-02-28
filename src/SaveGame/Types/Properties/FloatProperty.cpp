#include "FloatProperty.h"

#include <utility>

#include "../../Utils/StreamUtils.h"

SatisfactorySaveGame::FloatProperty::FloatProperty(
    std::string property_name, std::string property_type, std::istream& stream)
    : Property(std::move(property_name), std::move(property_type), stream) {
    read_assert_zero<int8_t>(stream);
    value_ = read<float>(stream);
}

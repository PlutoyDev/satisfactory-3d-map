#include "SaveObjectBase.h"

#include "Utils/StreamUtils.h"

Satisfactory3DMap::SaveObjectBase::SaveObjectBase(int32_t id, int32_t type, std::istream& stream)
    : id_(id), type_(type) {
    class_name_ = read_length_string(stream);
    reference_ = ObjectReference(stream);
}

void Satisfactory3DMap::SaveObjectBase::parseData(int32_t length, std::istream& stream) {
    auto pos_before = stream.tellg();

    bool done = false;
    do {
        auto property = Property::parse(stream);
        if (property == nullptr) {
            done = true;
        } else {
            properties_.emplace_back(std::move(property));
        }
    } while (!done);

    auto pos_after = stream.tellg();

    if (pos_after - pos_before != length) {
        extraProperties_ = read_vector<char>(stream, length - (pos_after - pos_before));
    }
}

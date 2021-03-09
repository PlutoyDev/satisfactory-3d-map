#ifndef SATISFACTORY3DMAP_OBJECTREFERENCE_H
#define SATISFACTORY3DMAP_OBJECTREFERENCE_H

#include <string>
#include <utility>

#include "Utils/StreamUtils.h"

namespace Satisfactory3DMap {

    // FObjectReferenceDisc
    class ObjectReference {
    public:
        ObjectReference() = default;
        ObjectReference(std::string level_name, std::string path_name)
            : level_name_(std::move(level_name)), path_name_(std::move(path_name)){};
        explicit ObjectReference(std::istream& stream) {
            level_name_ = read_length_string(stream);
            path_name_ = read_length_string(stream);
        };

    private:
        std::string level_name_;
        std::string path_name_;
    };
} // namespace Satisfactory3DMap

#endif // SATISFACTORY3DMAP_OBJECTREFERENCE_H

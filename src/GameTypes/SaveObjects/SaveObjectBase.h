#ifndef SATISFACTORY3DMAP_SAVEOBJECTBASE_H
#define SATISFACTORY3DMAP_SAVEOBJECTBASE_H

#include <cstdint>
#include <istream>
#include <memory>
#include <ostream>
#include <string>

#include "GameTypes/ObjectReference.h"
#include "GameTypes/Properties/Property.h"
#include "IO/Archive/IStreamArchive.h"

namespace Satisfactory3DMap {

    // FObjectBaseSaveHeader
    class SaveObjectBase {
    public:
        static std::shared_ptr<SaveObjectBase> create(int32_t id, IStreamArchive& ar);

        SaveObjectBase(int32_t id);
        virtual ~SaveObjectBase() = default;

        virtual void serialize(Archive& ar);

        virtual void parseData(int32_t length, std::istream& stream);

        virtual void serializeData(std::ostream& stream) const;

        [[nodiscard]] int32_t id() const {
            return id_;
        }

        [[nodiscard]] int32_t type() const {
            return type_;
        }

        [[nodiscard]] const std::string& className() const {
            return class_name_;
        }

        [[nodiscard]] const ObjectReference& reference() const {
            return reference_;
        }

        [[nodiscard]] const std::vector<std::unique_ptr<Property>>& properties() const {
            return properties_;
        }

        [[nodiscard]] const std::vector<char>& extraProperties() const {
            return extraProperties_;
        }

    protected:
        int32_t id_ = 0;
        int32_t type_ = 0;
        std::string class_name_;
        ObjectReference reference_;

        std::vector<std::unique_ptr<Property>> properties_;
        std::vector<char> extraProperties_;
    };
} // namespace Satisfactory3DMap

#endif // SATISFACTORY3DMAP_SAVEOBJECTBASE_H

#ifndef SATISFACTORY3DMAP_SAVEOBJECT_H
#define SATISFACTORY3DMAP_SAVEOBJECT_H

#include "SaveObjectBase.h"

namespace Satisfactory3DMap {

    // FObjectSaveHeader
    class SaveObject : public SaveObjectBase {
    public:
        SaveObject(int32_t id, int32_t type, std::istream& stream);

        [[nodiscard]] const std::string& outerPathName() const {
            return outer_path_name_;
        }

    protected:
        std::string outer_path_name_;
    };
} // namespace Satisfactory3DMap

#endif // SATISFACTORY3DMAP_SAVEOBJECT_H

#ifndef SATISFACTORY3DMAP_SAVEACTOR_H
#define SATISFACTORY3DMAP_SAVEACTOR_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "SaveObjectBase.h"

namespace Satisfactory3DMap {

    // FActorSaveHeader
    class SaveActor : public SaveObjectBase {
    public:
        SaveActor(int32_t id, int32_t type, std::istream& stream);

        void parseData(int32_t length, std::istream& stream) override;

        glm::mat4 transformation() const;

        const glm::quat& rotation() const {
            return rotation_;
        }

        const glm::vec3& position() const {
            return position_;
        }

        const glm::vec3& scale() const {
            return scale_;
        }

    protected:
        // Type size validation
        static_assert(sizeof(glm::quat) == 4 * sizeof(float));
        static_assert(sizeof(glm::vec3) == 3 * sizeof(float));

        int32_t need_transform_;
        glm::quat rotation_;
        glm::vec3 position_;
        glm::vec3 scale_;
        int32_t was_placed_in_level_;

        std::unique_ptr<ObjectReference> parent_reference_;
        std::unique_ptr<std::vector<ObjectReference>> child_references_;
    };
} // namespace Satisfactory3DMap

#endif // SATISFACTORY3DMAP_SAVEACTOR_H

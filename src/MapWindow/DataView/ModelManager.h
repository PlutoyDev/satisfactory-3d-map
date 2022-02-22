#ifndef SATISFACTORY3DMAP_MODELMANAGER_H
#define SATISFACTORY3DMAP_MODELMANAGER_H

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "../OpenGL/GltfModel.h"
#include "../OpenGL/StaticMeshVAO.h"
#include "IO/Pak/PakFile.h"

namespace Satisfactory3DMap {
    class SaveActor;

    class ModelManager {
    public:
        enum class ModelType {
            None,
            PakStaticMesh,
            Model,
            SplineModel,
        };

        explicit ModelManager(std::shared_ptr<PakFile> pak);
        ~ModelManager() = default;

        std::pair<ModelType, int32_t> classifyActor(const Satisfactory3DMap::SaveActor& actor);

        [[nodiscard]] const std::vector<std::unique_ptr<StaticMeshVAO>>& pakModels() const {
            return pakModels_;
        };

        [[nodiscard]] const std::vector<std::unique_ptr<GltfModel>>& models() const {
            return models_;
        };

        [[nodiscard]] const std::vector<std::unique_ptr<GltfModel>>& splineModels() const {
            return splineModels_;
        };

    protected:
        std::optional<int32_t> findPakModel(const std::string& className);
        std::size_t loadAsset(const std::string& className);

        std::shared_ptr<PakFile> pak_;

        std::vector<std::unique_ptr<StaticMeshVAO>> pakModels_;
        std::unordered_map<std::string, std::size_t> classNameToPakModelMap_;
        std::unordered_set<std::string> classNamesNotInPak_;

        std::vector<std::unique_ptr<GltfModel>> models_;
        std::vector<std::unique_ptr<GltfModel>> splineModels_;

        std::vector<std::vector<std::string>> modelSavePaths_;
        std::vector<std::vector<std::string>> splineModelSavePaths_;
    };
} // namespace Satisfactory3DMap

#endif // SATISFACTORY3DMAP_MODELMANAGER_H

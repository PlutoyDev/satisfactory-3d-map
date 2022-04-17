#ifndef SATISFACTORY3DMAP_PAKMANAGER_H
#define SATISFACTORY3DMAP_PAKMANAGER_H

#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "IO/Pak/PakFile.h"

namespace Satisfactory3DMap {

    class PakManager {
    public:
        static inline std::string classNameToAssetPath(const std::string& className) {
            // Remove leading /
            std::string assetName = className;
            if (!assetName.empty() && assetName[0] == '/') {
                assetName = assetName.substr(1);
            }
            // Remove object name
            assetName = assetName.substr(0, assetName.find_last_of('.')) + ".uasset";
            return assetName;
        }

        explicit PakManager(const std::filesystem::path& gameDir);
        ~PakManager() = default;

        [[nodiscard]] std::vector<std::string> getAllAssetFilenames() const;

        [[nodiscard]] inline bool containsAssetFilename(const std::string& filename) {
            return packageNames_.count(filename) > 0;
        };

        inline AssetFile readAsset(const std::string& filename) {
            const auto& [pakIdx, pakFilename] = packageNames_.at(filename);
            return pakFiles_.at(pakIdx)->readAsset(pakFilename);
        };

    protected:
        void cacheLatestPakNames(const std::optional<std::string>& modPrefix = std::nullopt);

        std::vector<std::shared_ptr<PakFile>> pakFiles_;

        std::unordered_map<std::string, std::pair<std::size_t, std::string>> packageNames_;
    };
} // namespace Satisfactory3DMap

#endif // SATISFACTORY3DMAP_PAKMANAGER_H

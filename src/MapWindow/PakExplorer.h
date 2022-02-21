#ifndef SATISFACTORY3DMAP_PAKEXPLORER_H
#define SATISFACTORY3DMAP_PAKEXPLORER_H

#include <memory>
#include <string>

#include "DataView/DataView.h"
#include "GameTypes/Properties/Properties.h"
#include "UI/PropertyTableGuiRenderer.h"

namespace Satisfactory3DMap {

    class PakExplorer {
    public:
        explicit PakExplorer(std::shared_ptr<DataView> dataView);
        ~PakExplorer() = default;

        void renderGui();

        bool& show() {
            return show_;
        }

    protected:
        struct AssetPathNode {
            std::map<std::string, AssetPathNode> childNodes;
            std::map<std::string, std::string> assetFiles;
        };

        void drawAssetFileTree(const AssetPathNode& node);

        void selectAsset(const std::string& assetFile);

        void showExport(int idx);

        std::shared_ptr<DataView> dataView_;
        PropertyTableGuiRenderer propertyRenderer_;
        AssetPathNode rootNode_;
        bool show_;
        std::string selectedAssetFile_;
        std::unique_ptr<AssetFile> asset_;
        std::unique_ptr<Properties> assetExport_;
    };
} // namespace Satisfactory3DMap

#endif // SATISFACTORY3DMAP_PAKEXPLORER_H

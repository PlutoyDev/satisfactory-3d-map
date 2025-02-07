#include "Utils/SaveTextExporter.h"

#include <fstream>
#include <string>

#include "GameTypes/Properties/Base/PropertyAll.h"
#include "GameTypes/Properties/Base/PropertyVisitor.h"

namespace {
    class PropertyValueWriter : public SatisfactorySave::PropertyVisitor {
    private:
        std::ofstream& file_;

    public:
        explicit PropertyValueWriter(std::ofstream& file) : file_(file) {}

        void visit(SatisfactorySave::ArrayProperty& p) override {
            file_ << "  " << p.arrayType();
            // TODO values
        }

        void visit(SatisfactorySave::BoolProperty& p) override {
            file_ << "  " << static_cast<int>(p.value());
        }

        void visit(SatisfactorySave::ByteProperty& p) override {
            file_ << "  ByteType: " << p.byteType() << "  ";
            if (p.byteType() == "None") {
                file_ << static_cast<int>(p.valueByte());
            } else {
                file_ << p.valueName();
            }
        }

        void visit(SatisfactorySave::DoubleProperty& p) override {
            file_ << "  " << p.Value;
        }

        void visit(SatisfactorySave::EnumProperty& p) override {
            file_ << "  EnumType: " << p.enumType() << "  " << p.Value;
        }

        void visit(SatisfactorySave::FloatProperty& p) override {
            file_ << "  " << p.Value;
        }

        void visit(SatisfactorySave::Int64Property& p) override {
            file_ << "  " << p.Value;
        }

        void visit(SatisfactorySave::Int8Property& p) override {
            file_ << "  " << static_cast<int>(p.Value);
        }

        void visit(SatisfactorySave::IntProperty& p) override {
            file_ << "  " << p.Value;
        }

        void visit(SatisfactorySave::MapProperty& p) override {
            file_ << "  " << p.keyType() << "  " << p.valueType();
            // TODO values
        }

        void visit([[maybe_unused]] SatisfactorySave::MulticastSparseDelegateProperty& p) override {
            // only used in pak
        }

        void visit(SatisfactorySave::NameProperty& p) override {
            file_ << "  " << p.Value;
        }

        void visit(SatisfactorySave::ObjectProperty& p) override {
            file_ << "  Lvl: " << p.Value.LevelName << "  Path: " << p.Value.PathName;
        }

        void visit(SatisfactorySave::SetProperty& p) override {
            file_ << "  " << p.setType();
            // TODO values
        }

        void visit(SatisfactorySave::SoftObjectProperty& p) override {
            file_ << "  AssetPathName: " << p.value().AssetPathName().toString()
                  << "  SubPathString: " << p.value().SubPathString();
        }

        void visit(SatisfactorySave::StrProperty& p) override {
            file_ << "  " << p.Value;
        }

        void visit(SatisfactorySave::StructProperty& p) override {
            file_ << "  " << p.structName() << "  " << p.guid().toString();
            // TODO values
        }

        void visit(SatisfactorySave::TextProperty& p) override {
            file_ << "  " << p.Value.string();
        }

        void visit(SatisfactorySave::UInt32Property& p) override {
            file_ << "  " << p.Value;
        }

        void visit(SatisfactorySave::UInt64Property& p) override {
            file_ << "  " << p.Value;
        }

        void visit(SatisfactorySave::UnknownProperty& p) override {
            file_ << "  [UnknownProperty] " << p.Tag.Type;
        }
    };

    void writeObjects(std::ofstream& file,
        const std::vector<std::shared_ptr<SatisfactorySave::SaveObjectBase>>& saveObjects,
        const std::vector<SatisfactorySave::FObjectReferenceDisc>& destroyedActors) {
        // Objects
        file << "=== objects ===" << std::endl;
        for (const auto& obj : saveObjects) {
            file << obj->ClassName << "::" << obj->Reference.PathName << " [" << (obj->type() == 1 ? "A" : "O") << "]"
                 << std::endl;

            for (const auto& p : obj->Properties) {
                file << "    " << p->Tag.Name << "  " << p->Tag.Type;
                PropertyValueWriter w(file);
                p->accept(w);
                file << std::endl;
            }

            if (!obj->ExtraProperties.empty()) {
                file << "    EXTRA SIZE:" << obj->ExtraProperties.size() << std::endl;
            }
        }
        file << std::endl;

        // Destroyed actors
        file << "=== destroyed actors ===" << std::endl;
        for (const auto& obj : destroyedActors) {
            file << obj.LevelName << "  " << obj.PathName << std::endl;
        }
        file << std::endl;
    }
} // namespace

void SatisfactorySave::saveToTextFile(const SaveGame& savegame, const std::filesystem::path& filename) {
    std::ofstream file(filename);

    // Header
    file << "=== header ===" << std::endl;
    file << savegame.header().toString() << std::endl;

    file << "=== levels [" << savegame.levelData().size() << "] ===" << std::endl;
    for (auto& lvl : savegame.levelData()) {
        writeObjects(file, lvl.save_objects, lvl.destroyed_actors_TOC);
    }

    file << "=== main level ===" << std::endl;
    writeObjects(file, savegame.saveObjects(), savegame.destroyedActors());

    // Unresolved world data
    file << "=== unresolved world data ===" << std::endl;
    for (const auto& obj : savegame.unresolvedWorldSaveData()) {
        file << obj.LevelName << "  " << obj.PathName << std::endl;
    }

    file.close();
}

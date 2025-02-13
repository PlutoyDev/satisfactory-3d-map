#include "GameTypes/MapTypes/StructMapTypeList.h"

#include "GameTypes/MapTypes/Base/MapTypeListVisitor.h"

SatisfactorySave::StructMapTypeList::StructMapTypeList(const FName& name, const std::string& parentClassName,
    bool isKey) {

    if (!isKey && parentClassName == "/Game/FactoryGame/Events/BP_EventSubsystem.BP_EventSubsystem_C" &&
        (name == "mStoredCalendarData" || name == "mCalendarData")) {
        struct_name_.Name = "CalendarData";
    } else if (parentClassName == "/Script/FactoryGame.FGFoliageRemovalSubsystem" && name == "mSaveData") {
        if (isKey) {
            struct_name_.Name = "IntVector";
        } else {
            struct_name_.Name = "FoliageRemovalSaveDataPerCell";
        }
    } else if (parentClassName == "/Script/FactoryGame.FGFoliageRemovalSubsystem" && name == "mUnresolvedSaveData") {
        if (isKey) {
            struct_name_.Name = "IntVector";
        } else {
            struct_name_.Name = "FoliageRemovalUnresolvedSaveDataPerCell";
        }
    } else if (!isKey && parentClassName == "/Script/FactoryGame.FGStatisticsSubsystem" &&
               name == "mActorsBuiltCount") {
        struct_name_.Name = "ActorBuiltData";
    } else if (!isKey &&
               (parentClassName == "FoliageRemovalSaveDataPerCell" ||
                   parentClassName == "FoliageRemovalUnresolvedSaveDataPerCell") &&
               name == "SaveDataMap") {
        struct_name_.Name = "FoliageRemovalSaveDataForFoliageType";
    } else if (!isKey && parentClassName == "LBBalancerData" && name == "mIndexMapping") {
        // https://github.com/mklierman/SatisfactoryMods/blob/6a9ed9c315c8f58dbbda22efc788e66566c93321/LoadBalancers/Source/LoadBalancers/Public/LBBuild_ModularLoadBalancer.h#L92
        struct_name_.Name = "LBBalancerIndexing";
    } else {
        // Unknown struct types will be parsed as property struct anyway,
        // provide type information in struct name for debug logging.
        struct_name_.Name = "MapType;" + parentClassName + ";" + name.toString() + ";" + (isKey ? "key" : "val");
    }
}

void SatisfactorySave::StructMapTypeList::accept(SatisfactorySave::MapTypeListVisitor& v) {
    v.visit(*this);
}

void SatisfactorySave::StructMapTypeList::serializeEntry(Archive& ar, std::size_t i) {
    if (ar.isIArchive()) {
        if (List.size() <= i) {
            List.resize(i + 1);
        }
        List[i] = Struct::create(struct_name_, ar);
    } else {
        ar << *List[i];
    }
}

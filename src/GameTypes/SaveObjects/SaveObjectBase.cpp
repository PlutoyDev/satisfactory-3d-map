#include "SaveObjectBase.h"

#include "IO/Archive/OStreamArchive.h"
#include "SaveActor.h"
#include "SaveObject.h"

std::shared_ptr<Satisfactory3DMap::SaveObjectBase> Satisfactory3DMap::SaveObjectBase::create(int32_t id,
    IStreamArchive& ar) {
    const auto type = ar.read_ahead<int32_t>();
    std::shared_ptr<SaveObjectBase> object;
    if (type == 0) { // object
        object = std::make_shared<SaveObject>(id);
    } else if (type == 1) { // actor
        object = std::make_shared<SaveActor>(id);
    } else {
        throw std::runtime_error("Unknown object type!");
    }
    ar << *object;
    return object;
}

Satisfactory3DMap::SaveObjectBase::SaveObjectBase(int32_t id) : id_(id) {}

void Satisfactory3DMap::SaveObjectBase::serialize(Archive& ar) {
    ar << type_;
    ar << class_name_;
    ar << reference_;
}

void Satisfactory3DMap::SaveObjectBase::serializeProperties(Satisfactory3DMap::Archive& ar, int32_t length) {
    if (ar.isIArchive()) {
        auto& inAr = dynamic_cast<IStreamArchive&>(ar);

        auto pos_before = inAr.tell();

        ar << properties_;

        // TODO unknown
        inAr.read_assert_zero<int32_t>();

        auto pos_after = inAr.tell();

        // Read extras as binary buffer
        if (pos_after - pos_before != length) {
            extraProperties_ = inAr.read_vector<char>(length - (pos_after - pos_before));
        }
    } else {
        auto& outAr = dynamic_cast<OStreamArchive&>(ar);

        ar << properties_;

        outAr.write<int32_t>(0);

        if (!extraProperties_.empty()) {
            outAr.write_vector(extraProperties_);
        }
    }
}

#ifndef SATISFACTORY3DMAP_OSTREAMARCHIVE_H
#define SATISFACTORY3DMAP_OSTREAMARCHIVE_H

#include <fstream>
#include <memory>

#include "Archive.h"

namespace Satisfactory3DMap {
    class OStreamArchive : public Archive {
    public:
        explicit OStreamArchive(std::unique_ptr<std::ostream> ostream) : ostream_(std::move(ostream)) {}

        template<typename T>
        void write(T value) {
            serialize(&value, sizeof(T));
        }

        template<typename T>
        void write_vector(std::vector<T>& vec) {
            serialize(vec.data(), vec.size() * sizeof(T));
        }

        [[nodiscard]] bool isIArchive() const override {
            return false;
        };

        [[nodiscard]] bool isOArchive() const override {
            return true;
        };

        std::size_t tell() override {
            return static_cast<std::size_t>(ostream_->tellp());
        };

        void seek(std::size_t pos) override {
            ostream_->seekp(static_cast<std::istream::pos_type>(pos));
        };

        std::ostream& rawStream() {
            return *ostream_;
        };

    protected:
        OStreamArchive() = default;

        void serialize(void* data, std::size_t size) override {
            ostream_->write(reinterpret_cast<char*>(data), static_cast<std::streamsize>(size));
            if (!ostream_->good()) {
                throw std::runtime_error("Error writing to stream!");
            }
        }

        void serializeString(std::string& s) override {
            write_length_string(*ostream_, s);
        }

        std::unique_ptr<std::ostream> ostream_;
    };

    class OFStreamArchive : public OStreamArchive {
    public:
        explicit OFStreamArchive(const std::filesystem::path& filepath) {
            auto file = std::make_unique<std::ofstream>(filepath, std::ios::binary);
            if (!file->is_open()) {
                throw std::runtime_error("Cannot write file!");
            }

            ostream_ = std::move(file);
        }
    };

    class OMemStreamArchive : public OStreamArchive {
    public:
        explicit OMemStreamArchive(std::unique_ptr<MemOStream> ostream) {
            ostream_ = std::move(ostream);
        }

        [[nodiscard]] const std::vector<char>& data() const {
            return dynamic_cast<MemOStream&>(*ostream_).data();
        }
    };
} // namespace Satisfactory3DMap

#endif // SATISFACTORY3DMAP_OSTREAMARCHIVE_H

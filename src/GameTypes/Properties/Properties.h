#pragma once

#include <memory>
#include <vector>

#include "IO/Archive/Archive.h"
#include "Property.h"

namespace Satisfactory3DMap {

    class Properties {
    public:
        explicit Properties() = default;
        ~Properties() = default;

        void serialize(Archive& ar);

        [[nodiscard]] const std::vector<std::unique_ptr<Property>>& properties() const {
            return properties_;
        }

        auto begin() {
            return properties_.begin();
        }

        auto end() {
            return properties_.end();
        }

        auto cbegin() const {
            return properties_.cbegin();
        }

        auto cend() const {
            return properties_.cend();
        }

        auto begin() const {
            return properties_.begin();
        }

        auto end() const {
            return properties_.end();
        }

        auto empty() const {
            return properties_.empty();
        }

        auto size() const {
            return properties_.size();
        }

        const Property& at(std::size_t n) const {
            return *properties_.at(n);
        }

        template<typename T>
        inline const T& get(const std::string& name) {
            for (const auto& p : properties_) {
                if (p->tag().Name == name) {
                    const T* property = dynamic_cast<const T*>(p.get());
                    if (property != nullptr) {
                        return *property;
                    }
                    throw std::runtime_error("Property type invalid!");
                }
            }
            throw std::runtime_error("Property name invalid!");
        }

    protected:
        std::vector<std::unique_ptr<Property>> properties_;
    };
} // namespace Satisfactory3DMap

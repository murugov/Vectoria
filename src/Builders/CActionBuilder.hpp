#ifndef C_ACTION_BUILDER_HPP
#define C_ACTION_BUILDER_HPP

#include <string>
#include <nlohmann/json.hpp>

#include "Base/CAction.hpp"

using json = nlohmann::json;

namespace Vectoria {

class CActionBuilder {
public:
    static CAction* build(const json& action_json) {
        int id = action_json.value("id", 0);
        std::string name = action_json.value("name", "Unknown");

        CAction* action = new CAction(static_cast<unsigned int>(id), name.c_str(), []() { /* Logic */ });

        if (action_json.contains("children") && action_json["children"].is_array()) {
            for (const auto& child_json : action_json["children"]) {
                CAction* child = build(child_json);
                action->addChild(child);
                child->release();
            }
        }
        return action;
    }
};

} // namespace Vectoria

#endif

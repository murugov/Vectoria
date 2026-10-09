#include "UI/ToolManager.hpp"

namespace UI {

// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---

void ToolManager::registerTool(std::unique_ptr<ToolObject> tool) {
    if (tool) {
        tools_.push_back(std::move(tool));
    }
}

void ToolManager::selectTool(size_t index) {
    if (index < tools_.size()) {
        active_tool_index_ = index;
    }
}

void ToolManager::clear () {
    tools_.clear();
}


} // namespace Core

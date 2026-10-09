#ifndef TOOL_MANAGER_HPP
#define TOOL_MANAGER_HPP

#include <vector>
#include <memory>
#include "UI/ToolObject.hpp"

namespace UI {

class ToolManager {
private:
    std::vector<std::unique_ptr<ToolObject>> tools_ {};
    size_t active_tool_index_ = 0; 

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    ToolManager () = default;

    // --- Destructor ---
    
    ~ToolManager () = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---

    const ToolObject& activeTool () const { return *tools_[active_tool_index_]; }
    ToolObject&       activeTool ()       { return *tools_[active_tool_index_]; }
    
    size_t activeToolIndex () const { return active_tool_index_; }
    size_t toolCount ()       const { return tools_.size(); }

    // -------------------------------------------------------------------------------
    // --- Methods Prototypes ---
    
    void registerTool (std::unique_ptr<ToolObject> tool);
    void selectTool   (size_t index);

    void clear ();
};

} // namespace UI

#endif
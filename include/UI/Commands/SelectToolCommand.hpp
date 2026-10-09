#ifndef SELECT_TOOL_COMMAND_HPP
#define SELECT_TOOL_COMMAND_HPP

#include "UI/Command.hpp"
#include "UI/ToolManager.hpp"

namespace UI {

class SelectToolCommand : public Command {
private:
    ToolManager& tool_manager_;
    size_t tool_index_;
public:
    SelectToolCommand(ToolManager& manager, size_t index) 
        : tool_manager_(manager), tool_index_(index) {}

    void execute() override { tool_manager_.selectTool(tool_index_); }
};

} // namespace UI

#endif
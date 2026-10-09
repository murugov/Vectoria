#ifndef SELLECT_TOOL_HPP
#define SELLECT_TOOL_HPP

#include "Core/DrawObject.hpp"
#include "UI/ToolObject.hpp"

namespace UI {

class SelectionTool : public ToolObject, public DrawableToolObject {
private:
    Math::Vector2D start_pos_;
    bool is_dragging_ = false;
    
    Core::DrawObject* selected_object_ = nullptr; 

public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---
    
    SelectionTool() = default;

    // --- Virtual Destructor ---
    
    ~SelectionTool() override = default;

    // -------------------------------------------------------------------------------
    // --- Virtual Methods Prototypes ---
    
    void onMouseDown (Math::Vector2D world_pos, Core::Scene& active_scene) override;
    void onMouseMove (Math::Vector2D world_pos, Core::Scene& active_scene) override;
    void onMouseUp   (Math::Vector2D world_pos, Core::Scene& active_scene) override;

    void draw () const override;
};

} // namespace UI
#endif

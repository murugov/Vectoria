#ifndef RECTANGLE_TOOL_HPP
#define RECTANGLE_TOOL_HPP

#include "Core/Shapes/RectangleObject.hpp"
#include "UI/ToolObject.hpp"

namespace UI {

class RectangleTool : public ToolObject {
private:
    Math::Vector2D start_pos_;
    bool is_drawing_ = false;
    
    Core::RectangleObject* current_shape_ = nullptr; 

public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---
    
    RectangleTool() = default;

    // --- Virtual Destructor ---
    
    ~RectangleTool() override = default;

    // -------------------------------------------------------------------------------
    // --- Virtual Methods Prototypes ---
    
    void onMouseDown (Math::Vector2D world_pos, Core::Scene& active_scene) override;
    void onMouseMove (Math::Vector2D world_pos, Core::Scene& active_scene) override;
    void onMouseUp   (Math::Vector2D world_pos, Core::Scene& active_scene) override;
};

} // namespace UI
#endif

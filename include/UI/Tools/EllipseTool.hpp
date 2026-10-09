#ifndef ELLIPSE_TOOL_HPP
#define ELLIPSE_TOOL_HPP

#include "Core/Shapes/EllipseObject.hpp"
#include "UI/ToolObject.hpp"

namespace UI {

class EllipseTool : public ToolObject {
private:
    Math::Vector2D start_pos_;
    bool is_drawing_ = false;
    
    Core::EllipseObject* current_shape_ = nullptr; 

public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---
    
    EllipseTool () = default;

    // --- Virtual Destructor ---
    
    ~EllipseTool () override = default;

    // -------------------------------------------------------------------------------
    // --- Virtual Methods Prototypes ---
    
    void onMouseDown (Math::Vector2D world_pos, Core::Scene& active_scene) override;
    void onMouseMove (Math::Vector2D world_pos, Core::Scene& active_scene) override;
    void onMouseUp   (Math::Vector2D world_pos, Core::Scene& active_scene) override;
};

} // namespace UI
#endif

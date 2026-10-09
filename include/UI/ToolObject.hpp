#ifndef TOOL_OBJECT_HPP
#define TOOL_OBJECT_HPP

#include "Core/Scene.hpp"
#include "Math/Vector.hpp"

namespace UI {

class ToolObject {
public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---

    ToolObject () = default;
    
    // --- Virtual Destructor ---
    virtual ~ToolObject() = default;
    
    // -------------------------------------------------------------------------------
    // --- Virtual Methods Prototypes ---
    
    // NOTE: Called in the controller when the user clicks the mouse button on the canvas.
    virtual void onMouseDown (Math::Vector2D mouse_pos, Core::Scene& active_scene) = 0;

    // NOTE: Called in the controller when the user moves the mouse across the canvas.
    virtual void onMouseMove (Math::Vector2D mouse_pos, Core::Scene& active_scene) = 0;

    // NOTE: Called in the controller when the user releases the mouse button.
    virtual void onMouseUp   (Math::Vector2D mouse_pos, Core::Scene& active_scene) = 0;
};

class DrawableToolObject {
public:
    // --- Virtual Destructor ---

    virtual ~DrawableToolObject() = default;
    
    // -------------------------------------------------------------------------------
    // --- Virtual Methods Prototypes ---

    virtual void draw() const = 0; 
};

} // namespace UI

#endif
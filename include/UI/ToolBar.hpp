#ifndef TOOL_BAR_HPP
#define TOOL_BAR_HPP

#include <vector>
#include <memory>
#include "Core/Object.hpp"
#include "Graphic/Canvas.hpp"
#include "Math/Vector.hpp"
#include "UI/Button.hpp"

namespace UI {

class ToolBar : public Core::Object {
private:
    Graphic::Canvas ui_canvas_; 
    std::vector<std::unique_ptr<Button>> buttons_;  // tool_buttons_

public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---
    
    ToolBar(Math::Vector2D pos, Math::Vector2D size)
        : Core::Object(pos, size, true)
        , ui_canvas_(pos, static_cast<int>(size.x()), static_cast<int>(size.y()), Graphic::Colors::Red) 
    {}

    // --- Virtual Destructor ---
    
    ~ToolBar() override = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---
    
    const Graphic::Canvas& canvas() const { return ui_canvas_; }
    Graphic::Canvas&       canvas()       { return ui_canvas_; }

    const std::vector<std::unique_ptr<Button>>& buttons     () const { return buttons_; }
    size_t                                      buttonCount () const { return buttons_.size(); }
        
    // -------------------------------------------------------------------------------
    // --- Methods Prototypes ---
    
    void addButton        (std::unique_ptr<Button> button);
    bool handleMouseClick (Math::Vector2D mouse_pos);

    void draw ();

    // -------------------------------------------------------------------------------
    // --- Virtual Methods Prototypes ---
    
    bool contains (const Math::Vector2D& point) const override;
};

} // namespace UI

#endif

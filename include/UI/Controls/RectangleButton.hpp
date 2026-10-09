#ifndef RECTANGLE_BUTTON_HPP
#define RECTANGLE_BUTTON_HPP

#include "UI/Button.hpp"

namespace UI {

class RectangleButton : public Button {
public:
    // -------------------------------------------------------------------------------
    // --- Base Class Constructor ---
    
    using Button::Button;

    // --- Virtual Destructor ---

    ~RectangleButton() override = default;

    // -------------------------------------------------------------------------------
    // Virtual Methods Prototypes
    
    void draw () const override;
};

} // namespace UI

#endif
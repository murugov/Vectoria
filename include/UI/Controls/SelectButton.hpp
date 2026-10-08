#ifndef SELECT_BUTTON_HPP
#define SELECT_BUTTON_HPP

#include "UI/Button.hpp"

namespace UI {
class SelectButton : public Button {
public:
    // -------------------------------------------------------------------------------
    // --- Base Class Constructor ---

    using Button::Button;

    // --- Destrctor ---

    ~SelectButton () override;

    // -------------------------------------------------------------------------------
    // --- Virtual Methods Prototypes ---
        
    void draw() const override;
};

} // namespace UI

#endif
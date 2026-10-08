#include "UI/ToolBar.hpp"

namespace UI {

// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---

void ToolBar::addButton (std::unique_ptr<Button> button) {
    if (button) buttons_.push_back(std::move(button));
}

#include "UI/ToolBar.hpp"


bool ToolBar::handleMouseClick(Math::Vector2D mouse_pos) {
    if (!isEnabled()) {
        return false;
    }

    if (!this->contains(mouse_pos)) return false; 

    for (auto& btn : buttons_) {
        if (btn && btn->isEnabled() && btn->contains(mouse_pos)) {
            
            btn->setState(ButtonState::Pressed);
            btn->click(); 
            
            return true; 
        }
    }

    return false;
}


void ToolBar::draw () {
    if (!isEnabled()) return;

    ui_canvas_.draw();

    for (const auto& btn : buttons_) {
        btn->draw(); 
    }
}

// -------------------------------------------------------------------------------
// --- Implementation Of Virtual Methods ---

bool ToolBar::contains(const Math::Vector2D& point) const {
    return (point.x() >= pos_.x() && point.x() <= pos_.x() + size_.x()) &&
           (point.y() >= pos_.y() && point.y() <= pos_.y() + size_.y());
}

} // namespace UI
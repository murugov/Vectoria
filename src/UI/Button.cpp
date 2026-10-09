#include "UI/Button.hpp"

namespace UI {
    
// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---

void Button::click () {
    if (command_) {
        command_->execute();
    }
}

// -------------------------------------------------------------------------------
// --- Implementation Of Virtual Methods ---

bool Button::contains(const Math::Vector2D& point) const {
    return (point.x() >= pos_.x() && point.x() <= pos_.x() + size_.x()) &&
           (point.y() >= pos_.y() && point.y() <= pos_.y() + size_.y());
}

} // namespace UI
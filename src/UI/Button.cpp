#include "UI/Button.hpp"

namespace UI {

Button::~Button () = default;

// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---

void Button::click () {
    if (command_) {
        command_->execute();
    }
}

bool Button::contains(const Math::Vector2D& point) const {
    return (point.x() >= pos_.x() && point.x() <= pos_.x() + size_.x()) &&
           (point.y() >= pos_.y() && point.y() <= pos_.y() + size_.y());
}

void Button::draw() const {
    if (!isEnabled()) return;

    Math::Transform2D transform {};
    transform.pos      = pos_;
    transform.size     = size_;          

    material_.draw(transform);
}

} // namespace UI
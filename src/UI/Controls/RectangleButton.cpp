#include "UI/Controls/RectangleButton.hpp"

namespace UI {

// -------------------------------------------------------------------------------
// --- Implementation Of Virtual Methods ---

void RectangleButton::draw() const {
    if (!isEnabled()) return;

    Math::Transform2D transform {};
    transform.pos      = pos_;
    transform.size     = size_;          

    material_.draw(transform);
}

} // namespace UI
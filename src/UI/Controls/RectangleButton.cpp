#include "Graphic/Adapter.hpp"
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

    Graphic::Color stroke_color = Graphic::Colors::Black;
        
    Graphic::Adapter::drawLine({pos_.x(), pos_.y()}, {pos_.x() + size_.x(), pos_.y()}, stroke_color, 1.0f);
    Graphic::Adapter::drawLine({pos_.x(), pos_.y() + size_.y()}, {pos_.x() + size_.x(), pos_.y() + size_.y()}, stroke_color, 1.0f);
    Graphic::Adapter::drawLine({pos_.x(), pos_.y()}, {pos_.x(), pos_.y() + size_.y()}, stroke_color, 1.0f);
    Graphic::Adapter::drawLine({pos_.x() + size_.x(), pos_.y()}, {pos_.x() + size_.x(), pos_.y() + size_.y()}, stroke_color, 1.0f);
}

} // namespace UI
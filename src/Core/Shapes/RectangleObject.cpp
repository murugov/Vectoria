#include "Core/Shapes/RectangleObject.hpp"
#include "Graphic/Adapter.hpp"

namespace Core {

// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---

bool RectangleObject::contains(const Math::Vector2D& point) const {
    return (point.x() >= pos_.x() && point.x() <= pos_.x() + size_.x()) &&
           (point.y() >= pos_.y() && point.y() <= pos_.y() + size_.y());
}

void RectangleObject::draw () const {
    Graphic::Adapter::drawRectangle({ pos_, size_ }, fillColor_);     // FIXME: Hardcoded color
}

} // namespace Core
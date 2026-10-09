#include "Core/Shapes/EllipseObject.hpp"
#include "Graphic/Adapter.hpp"
#include "Graphic/Colors.hpp"

namespace Core {

// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---

bool EllipseObject::contains(const Math::Vector2D& point) const {
     float r_x = size_.x() / 2.0f;
     float r_y = size_.y() / 2.0f;
     Math::Vector2D center = pos_ + Math::Vector2D{r_x, r_y};

     float dx = point.x() - center.x();
     float dy = point.y() - center.y();

     // Canonical equation of an ellipse: (x^2 / a^2) + (y^2 / b^2) <= 1
     return (dx * dx) * (r_y * r_y) + (dy * dy) * (r_x * r_x) <= (r_x * r_x) * (r_y * r_y);
}

void EllipseObject::draw() const {
    Graphic::Adapter::drawEllipse({ pos_, size_ }, fillColor_);
}

} // namespace Core
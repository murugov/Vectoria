#include "Core/Scene.hpp"
#include "Graphic/Adapter.hpp"
#include "Graphic/Colors.hpp"
#include "Math/Vector.hpp"
#include "UI/Tools/EllipseTool.hpp"

namespace UI {
    
// -------------------------------------------------------------------------------
// --- Implementation Of Virtual Methods ---

void EllipseTool::onMouseDown(Math::Vector2D world_pos, Core::Scene& active_scene) {
    start_pos_ = world_pos;
    is_drawing_ = true;

    auto new_rect = std::make_unique<Core::EllipseObject>(
        world_pos, 
        Math::Vector2D { 0.0f, 0.0f }
    );

    current_shape_ = new_rect.get();
    active_scene.drawManager().addObject(std::move(new_rect));
}

void EllipseTool::onMouseMove(Math::Vector2D world_pos, Core::Scene& /*active_scene*/) {
    if (!is_drawing_ || !current_shape_) return;

    float min_x = std::min(start_pos_.x(), world_pos.x());
    float min_y = std::min(start_pos_.y(), world_pos.y());
    float width = std::abs(world_pos.x() - start_pos_.x());
    float height = std::abs(world_pos.y() - start_pos_.y());

    current_shape_->setPos(Math::Vector2D{ min_x, min_y });
    current_shape_->setSize(Math::Vector2D{ width, height });
}


void EllipseTool::onMouseUp(Math::Vector2D /*world_pos*/, Core::Scene& /*active_scene*/) {
    if (!is_drawing_) return;
    
    is_drawing_ = false;
    current_shape_ = nullptr; 
}

void EllipseTool::draw () const {
    if (is_drawing_) {
        Graphic::Adapter::drawSelectBox({ current_shape_->pos(), current_shape_->size() }, Graphic::Colors::Gray);
    }
}

} // namespace UI
#include "UI/Tools/RectangleTool.hpp"
#include "Core/Scene.hpp"

namespace UI {

// -------------------------------------------------------------------------------
// --- Implementation Of Virtual Methods ---

void RectangleTool::onMouseDown (Math::Vector2D world_pos, Core::Scene& active_scene) {
    start_pos_ = world_pos;
    is_drawing_ = true;

    auto new_rect = std::make_unique<Core::RectangleObject>(
        world_pos, 
        Math::Vector2D { 0.0f, 0.0f }
    );

    current_shape_ = new_rect.get();
    active_scene.drawManager().addObject(std::move(new_rect));
}

void RectangleTool::onMouseMove(Math::Vector2D world_pos, Core::Scene& /*active_scene*/) {
    if (!is_drawing_ || !current_shape_) return;

    float min_x = std::min(start_pos_.x(), world_pos.x());
    float min_y = std::min(start_pos_.y(), world_pos.y());

    float width = std::abs(world_pos.x() - start_pos_.x());
    float height = std::abs(world_pos.y() - start_pos_.y());

    current_shape_->setPos(Math::Vector2D{ min_x, min_y }); 
    current_shape_->setSize(Math::Vector2D{ width, height });
}


void RectangleTool::onMouseUp (Math::Vector2D /*world_pos*/, Core::Scene& /*active_scene*/) {
    if (!is_drawing_) return;
    
    is_drawing_ = false;
    current_shape_ = nullptr; 
}

} // namespace UI
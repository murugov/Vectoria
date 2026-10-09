#include "Core/Scene.hpp"
#include "Graphic/Adapter.hpp"
#include "Graphic/Colors.hpp"
#include "UI/Tools/SelectionTool.hpp"

namespace UI {

// -------------------------------------------------------------------------------
// --- Implementation Of Virtual Methods ---

void SelectionTool::onMouseDown(Math::Vector2D world_pos, Core::Scene& active_scene) {
    start_pos_ = world_pos;
    is_dragging_ = true;
    
    selected_object_ = nullptr; 

    auto& objects = active_scene.drawManager().objects();

    for (auto obj = objects.rbegin(); obj != objects.rend(); ++obj) {
        if ((*obj)->contains(world_pos)) {
            selected_object_ = obj->get();
            break; 
        }
    }
}

void SelectionTool::onMouseMove(Math::Vector2D /*world_pos*/, Core::Scene& /*active_scene*/) {
    if (!is_dragging_) return;

    // TODO: Здесь можно добавить перемещение (Move) объекта selected_object_, 
}

void SelectionTool::onMouseUp(Math::Vector2D /*world_pos*/, Core::Scene& /*active_scene*/) {
    is_dragging_ = false;
}

void SelectionTool::draw () const {
    if (selected_object_) {
        Graphic::Adapter::drawSelectBox({ selected_object_->pos(), selected_object_->size() }, Graphic::Colors::Gray);
    }
}

} // namespace UI
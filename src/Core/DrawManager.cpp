#include "Core/DrawManager.hpp"

namespace Core {

// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---

void DrawManager::addObject (std::unique_ptr<DrawObject> obj) {
    if (obj) {
            obj->setFillColor(active_palette_color_);
            
            objects_.push_back(std::move(obj));
    }
}

void DrawManager::setAllObjects (bool state) {
    for (auto& object : objects_) {
        object->setEnabled(state);
    }
}

void DrawManager::update (float dt) {
    for (auto& obj : objects_) {
        if (obj && obj->isEnabled()) {
            obj->update(dt); 
        }
    }
}

void DrawManager::draw () const {
    for (const auto& obj : objects_) {
        if (obj->isEnabled()) {
            obj->draw();
        }
    }
}

void DrawManager::clear () {
    objects_.clear();
}


} // namespace Core
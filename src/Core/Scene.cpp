#include "Core/Scene.hpp"
#include "Core/DrawManager.hpp"
#include "Graphic/Adapter.hpp"

namespace Core {

// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---

void Scene::bind () const {
    // NOTE: Begin scissor mode (define screen area for following drawing)
    Graphic::Adapter::beginScissorMode({ document_canvas_.pos(), document_canvas_.size() });
    camera_.begin();
}

void Scene::unbind () const {
    camera_.end();
    Graphic::Adapter::endScissorMode();
}

void Scene::update (float dt) {
    // TODO: Add updating light_manager_

    for (auto& obj : draw_manager_.objects()) {
        if (obj && obj->isEnabled()) {
            obj->update(dt); 
        }
    }
}

void Scene::draw () const {
    this->bind();
    
    document_canvas_.draw();
    
    for (const auto& obj : draw_manager_.objects()) {
        if (obj->isEnabled()) {
            obj->draw();
        }
    }

    this->unbind();
}

void Scene::clear () {
    draw_manager_.clear();
}

} // namespace Core
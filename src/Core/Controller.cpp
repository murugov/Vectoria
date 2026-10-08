#include "Core/Controller.hpp"
#include "Graphic/Adapter.hpp"
#include "Math/Vector.hpp"
#include "UI/Commands/SelectToolCommand.hpp"
#include "UI/Button.hpp"

namespace Core {

// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---

void Controller::run() {
    const int screenWidth = 1280;
    const int screenHeight = 720;
    Graphic::Adapter::initWindow(screenWidth, screenHeight, "Vectoria Prototype");

    tool_manager_.selectTool(0);

    tool_bar_ = std::make_unique<UI::ToolBar>(Math::Vector2D{ 0.0f, 0.0f }, Math::Vector2D{ 60.0f, static_cast<float>(screenHeight) });

    // Button for the Select tool
    auto select_btn = std::make_unique<UI::Button>(
        Math::Vector2D{10.0f, 20.0f}, Math::Vector2D{40.0f, 40.0f}, 
        Graphic::SpriteMaterial(Graphic::Colors::Gray)
    );
    select_btn->setCommand(std::make_unique<UI::SelectToolCommand>(tool_manager_, 0));
    tool_bar_->addButton(std::move(select_btn));

    // Button for the Rectangle tool
    auto rect_btn = std::make_unique<UI::Button>(
        Math::Vector2D{10.0f, 70.0f}, Math::Vector2D{40.0f, 40.0f}, 
        Graphic::SpriteMaterial(Graphic::Colors::LightGray)
    );
    rect_btn->setCommand(std::make_unique<UI::SelectToolCommand>(tool_manager_, 1));
    tool_bar_->addButton(std::move(rect_btn));

    createNewScene({ 200.0f, 60.0f }, 800, 600, Graphic::Colors::White);

    // --- Main Loop ---
    
    while (!Graphic::Adapter::shouldClose()) {
        float dt = Graphic::Adapter::getFrameTime();

        if (Graphic::Adapter::isMouseButtonPressed(MOUSE_BUTTON_LEFT)) {        // FIXME: Add custom button's keys
            Math::Vector2D mousePos = Graphic::Adapter::getMousePosition();
            handleMouseClick(Math::Vector2D{mousePos.x(), mousePos.y()});
        }

        update(dt);

        Graphic::Adapter::beginDrawing();
        
            Controller::renderAll();
            
        Graphic::Adapter::endDrawing();
    }

    Graphic::Adapter::closeWindow();
}


void Controller::createNewScene (Math::Vector2D pos, int width, int height, Graphic::Color bg_color) {
    scenes_.push_back(std::make_unique<Scene>(pos, width, height, bg_color));
    active_scene_index_ = scenes_.size() - 1;
}

void Controller::update (float dt) {
    if (!scenes_.empty() && active_scene_index_ < scenes_.size()) {
        scenes_[active_scene_index_]->update(dt);
    }
}

void Controller::closeActiveScene() {
    if (scenes_.empty()) return;
    
    scenes_.erase(scenes_.begin() + static_cast<ptrdiff_t>(active_scene_index_));

    if (active_scene_index_ >= scenes_.size() && !scenes_.empty()) {
        active_scene_index_ = scenes_.size() - 1;
    }
}

void Controller::handleMouseClick(Math::Vector2D mouse_pos) {
    if (tool_bar_ && tool_bar_->handleMouseClick(mouse_pos)) return;
    
    if (!scenes_.empty()) {
        UI::ToolObject& current_tool = tool_manager_.activeTool();
        current_tool.onMouseDown(mouse_pos, activeScene());
    
    }
}

void Controller::renderAll() {
    app_background_canvas_.draw(); 

    if (!scenes_.empty()) {
        activeScene().draw(); 
    }

    if (tool_bar_) {
        tool_bar_->draw();
    }
}


} // namespace Core

#include "Core/Controller.hpp"
#include "Graphic/Adapter.hpp"
#include "Math/Vector.hpp"
#include "UI/Commands/SelectToolCommand.hpp"
#include "UI/Controls/RectangleButton.hpp"
#include "UI/Tools/EllipseTool.hpp"
#include "UI/Tools/RectangleTool.hpp"

namespace Core {

// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---

void Controller::run() {                // TODO: Make config.json
    const int screenWidth = 1280;
    const int screenHeight = 720;
    Graphic::Adapter::initWindow(screenWidth, screenHeight, "Vectoria Prototype");

    app_background_canvas_.setSize({ screenWidth, screenHeight });
    
    tool_manager_.selectTool(0);

    tool_bar_ = std::make_unique<UI::ToolBar>(Math::Vector2D{ 0.0f, 0.0f }, Math::Vector2D{ 60.0f, static_cast<float>(screenHeight) });

    registerTool({ 10.0f, 70.0f },  { 40.0f, 40.0f }, std::make_unique<UI::RectangleTool>(), Graphic::SpriteMaterial(Graphic::Colors::LightGray));
    registerTool({ 10.0f, 120.0f }, { 40.0f, 40.0f }, std::make_unique<UI::EllipseTool>(),   Graphic::SpriteMaterial(Graphic::Colors::Gray));

    createNewScene({ 200.0f, 60.0f }, 800, 600, Graphic::Colors::White);

    // --- Main Loop ---
    
    while (!Graphic::Adapter::shouldClose()) {
        float dt = Graphic::Adapter::getFrameTime();

        Math::Vector2D mousePos = Graphic::Adapter::getMousePosition();
        
        if (Graphic::Adapter::isMouseButtonPressed(MOUSE_BUTTON_LEFT)) {        // FIXME: Add custom button's keys
            handleMouseClick(Math::Vector2D{ mousePos.x(), mousePos.y() });
        }
        if (Graphic::Adapter::isMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if (tool_bar_ && !tool_bar_->contains(mousePos) && !scenes_.empty()) {
                Math::Vector2D world_mouse = activeScene().camera().screenToWorld(mousePos);
                
                tool_manager_.activeTool().onMouseMove(world_mouse, activeScene());
            }
        }

        if (Graphic::Adapter::isMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            if (!scenes_.empty()) {
                Math::Vector2D world_mouse = activeScene().camera().screenToWorld(mousePos);
                
                tool_manager_.activeTool().onMouseUp(world_mouse, activeScene());
            }
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

void Controller::registerTool(Math::Vector2D pos, Math::Vector2D size, std::unique_ptr<UI::ToolObject> tool, Graphic::SpriteMaterial&& material) {
    size_t index = tool_manager_.toolCount();
    
    tool_manager_.registerTool(std::move(tool));

    auto btn = std::make_unique<UI::RectangleButton>(pos, size, std::move(material));
    
    btn->setCommand(std::make_unique<UI::SelectToolCommand>(tool_manager_, index));

    tool_bar_->addButton(std::move(btn));
}


} // namespace Core

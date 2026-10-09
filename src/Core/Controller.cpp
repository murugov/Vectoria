#include "Core/Controller.hpp"
#include "Graphic/Adapter.hpp"
#include "Graphic/Texture.hpp"
#include "Math/Vector.hpp"
#include "UI/Commands/ChangeColorCommand.hpp"
#include "UI/Commands/SelectToolCommand.hpp"
#include "UI/Controls/RectangleButton.hpp"
#include "UI/Tools/EllipseTool.hpp"
#include "UI/Tools/RectangleTool.hpp"
#include "UI/Tools/SelectionTool.hpp"
#include <raylib.h>
#include <utility>

namespace Core {

// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---

void Controller::run() {                // TODO: Make config.json
    const int screen_width = 1280;
    const int screen_height = 720;
    Graphic::Adapter::initWindow(screen_width, screen_height, "Vectoria Prototype");

    app_background_canvas_.setSize({ screen_width, screen_height });
    
    tool_manager_.selectTool(0);

    tool_bar_ = std::make_unique<UI::ToolBar>(Math::Vector2D{ 0.0f, 0.0f }, Math::Vector2D{ 60.0f, static_cast<float>(screen_height) });

    Graphic::Texture cursor_tex("textures/Cursor.png");
    registerTool({ 10.0f, 70.0f },  { 40.0f, 40.0f }, std::make_unique<UI::SelectionTool>(), Graphic::SpriteMaterial(std::move(cursor_tex)));
    Graphic::Texture rectangle_tex("textures/Rectangle.png");
    registerTool({ 10.0f, 120.0f }, { 40.0f, 40.0f }, std::make_unique<UI::RectangleTool>(), Graphic::SpriteMaterial(std::move(rectangle_tex)));
    Graphic::Texture ellipse_tex("textures/Ellipse.png");
    registerTool({ 10.0f, 170.0f }, { 40.0f, 40.0f }, std::make_unique<UI::EllipseTool>(),   Graphic::SpriteMaterial(std::move(ellipse_tex)));

    float palette_width = 30.0f;
    float palette_x = static_cast<float>(screen_width) - palette_width;
    
    initColorPalette({ palette_x, 0.0f }, { palette_width, static_cast<float>(screen_height) });
    
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
    auto new_scene = std::make_unique<Scene>(pos, width, height, bg_color);
    
    new_scene->drawManager().setActivePaletteColor(active_color_); 
    
    scenes_.push_back(std::move(new_scene));
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
    if (color_palette_ && color_palette_->handleMouseClick(mouse_pos)) return;
    
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
    
    UI::ToolObject& active_tool = tool_manager_.activeTool();
    
    if (const auto* drawable_tool = dynamic_cast<const UI::DrawableToolObject*>(&active_tool)) {
        drawable_tool->draw(); 
    }
    
    if (tool_bar_) {
        tool_bar_->draw();
    }

    if (color_palette_) {
        color_palette_->draw();
    }
}

void Controller::registerTool(Math::Vector2D pos, Math::Vector2D size, std::unique_ptr<UI::ToolObject> tool, Graphic::SpriteMaterial&& material) {
    size_t index = tool_manager_.toolCount();
    
    tool_manager_.registerTool(std::move(tool));

    auto btn = std::make_unique<UI::RectangleButton>(pos, size, std::move(material));
    
    btn->setCommand(std::make_unique<UI::SelectToolCommand>(tool_manager_, index));

    tool_bar_->addButton(std::move(btn));
}

void Controller::initColorPalette(Math::Vector2D pos, Math::Vector2D size) {
    std::vector<Graphic::Color> available_colors = {
        Graphic::Colors::LightGray, Graphic::Colors::Gray, Graphic::Colors::DarkGray,
        Graphic::Colors::Yellow,    Graphic::Colors::Gold, Graphic::Colors::Orange,
        Graphic::Colors::Pink,      Graphic::Colors::Red,  Graphic::Colors::Maroon,
        Graphic::Colors::Green,     Graphic::Colors::Lime, Graphic::Colors::DarkGreen,
        Graphic::Colors::SkyBlue,   Graphic::Colors::Blue, Graphic::Colors::DarkBlue,
        Graphic::Colors::Purple,    Graphic::Colors::Violet, Graphic::Colors::DarkPurple,
        Graphic::Colors::Beige,     Graphic::Colors::Brown, Graphic::Colors::DarkBrown,
        Graphic::Colors::White,     Graphic::Colors::Black, Graphic::Colors::Magenta
    };

    color_palette_ = std::make_unique<UI::ToolBar>(pos, size);

    const float btn_size = 20.0f; 
    const float spacing = 5.0f;
    
    float current_x = pos.x() + (size.x() - btn_size) / 2.0f;
    
    float current_y = pos.y() + 40.0f; 

    for (const auto& color : available_colors) {
        if (current_y + btn_size > pos.y() + size.y() - 10.0f) {
            break;
        }

        auto btn = std::make_unique<UI::RectangleButton>(
            Math::Vector2D{ current_x, current_y }, 
            Math::Vector2D{ btn_size, btn_size }, 
            Graphic::SpriteMaterial(color)
        );

        btn->setCommand(std::make_unique<UI::ChangeColorCommand>(*this, color));
        
        color_palette_->addButton(std::move(btn));
        
        // TODO: Initializing the color change command

        color_palette_->addButton(std::move(btn));
        
        current_y += btn_size + spacing;
    }
}

} // namespace Core

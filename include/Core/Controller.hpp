#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <vector>
#include <memory>
#include "Core/Scene.hpp"
#include "Graphic/Colors.hpp"
#include "UI/ToolBar.hpp"
#include "UI/ToolManager.hpp"

namespace Core {

class Controller {
private:
    Graphic::Canvas app_background_canvas_; 

    std::vector<std::unique_ptr<Scene>> scenes_;
    size_t active_scene_index_ = 0; 

    UI::ToolManager tool_manager_;
    std::unique_ptr<UI::ToolBar> tool_bar_;
    
public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---
    
    Controller () : app_background_canvas_({ 0.0f, 0.0f }, 800, 600, Graphic::Colors::LightGray) {}

    // --- Destructor ---
    
    ~Controller () = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---

    const Scene& activeScene () const { return *scenes_[active_scene_index_]; }
    Scene&       activeScene ()       { return *scenes_[active_scene_index_]; }

    UI::ToolManager&       toolManager()       { return tool_manager_; }
    const UI::ToolManager& toolManager() const { return tool_manager_; }
        
    // -------------------------------------------------------------------------------
    // --- Setters ---

    void setActiveScene (size_t index) {
        if (index < scenes_.size()) {
            active_scene_index_ = index;
        }
    };
    
    // -------------------------------------------------------------------------------
    // --- Methods Prototypes ---

    void run    ();
    void update (float dt);

    void createNewScene (Math::Vector2D pos, int width, int height, Graphic::Color bg_color = Graphic::Colors::White);
    void closeActiveScene ();

    // TODO: void closeAllScenes ();

    void handleMouseClick(Math::Vector2D mouse_pos);

    void renderAll();

    void registerTool(Math::Vector2D pos,Math::Vector2D size, std::unique_ptr<UI::ToolObject> tool, Graphic::SpriteMaterial&& material);
};

} // namespace Core

#endif

#include "Core/Scene.hpp"
#include "Graphic/Adapter.hpp"
#include "Graphic/Camera.hpp"
#include "Graphic/Colors.hpp"
#include "Math/Vector.hpp"

int main() {
    const int window_width  = 800;
    const int window_height = 450;

    // -------------------------------------------------------------------------------
    // --- Initialize Window ---
    
    Graphic::Adapter::initWindow(window_width, window_height, "Reactor");
    
    Graphic::Camera main_camera(Math::Vector2D { 0.0f, 0.0f }, Math::Vector2D { 0.0f, 0.0f }, 1.0f);
    Core::Scene main_scene({ 0.0f, 0.0f }, window_width, window_height, Graphic::Colors::Blue);

    // -------------------------------------------------------------------------------
    // --- Main Loop ---
    
    while (!Graphic::Adapter::shouldClose()) {
        Graphic::Adapter::beginDrawing();
            Graphic::Adapter::clearBackground(Graphic::Colors::Black);

            main_scene.bind(main_camera);
                main_scene.draw();
            main_scene.unbind(main_camera);
        Graphic::Adapter::endDrawing();
    }
  
    Graphic::Adapter::closeWindow();
    return 0;
}
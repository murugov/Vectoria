#include "Vectoria/Interfaces/Core/IGraphicsAdapter.hpp"
#include "Vectoria/Interfaces/Windows/IDocumentWindow.hpp"
#include "Vectoria/Interfaces/Core/IDesktop.hpp"

#include "Core/CDesktop.hpp"
#include "Core/CGraphicsAdapter.hpp"
#include "Windows/CDocumentWindow.hpp"

int main() {
    Vectoria::IGraphicsAdapter* graphics_adapter = nullptr;
    
    if (!Vectoria::createGraphicsAdapter(1280, 720, "Vectoria (COM Edition)", &graphics_adapter)) {
        return -1; 
    }

    Vectoria::CDesktop* controller_impl = new Vectoria::CDesktop();
    Vectoria::IDesktop* app_controller = nullptr;
    
    controller_impl->queryInterface(Vectoria::IID_IDesktop, (void**)&app_controller);
    controller_impl->release();

    app_controller->initialize(graphics_adapter);

    while (!graphics_adapter->shouldClose()) {
        app_controller->update();

        graphics_adapter->beginDrawing();
        
        graphics_adapter->clearBackground(Graphic::Colors::DarkGray);
        
        app_controller->render();
        
        graphics_adapter->endDrawing();
    }

    app_controller->release();
    
    graphics_adapter->release(); 

    return 0;
}

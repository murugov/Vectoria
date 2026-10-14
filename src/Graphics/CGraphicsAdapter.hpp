#ifndef C_GRAPHICS_ADAPTER_HPP
#define C_GRAPHICS_ADAPTER_HPP

#include <raylib.h>
#include "Vectoria/Base/CUnknown.hpp"
#include "Vectoria/Interfaces/Core/IGraphicsAdapter.hpp"

namespace Vectoria {

class CGraphicsAdapter : public CUnknown, public IGraphicsAdapter {
public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    CGraphicsAdapter () = default;

    // --- Destructor ---
    
    ~CGraphicsAdapter () override {
        ::CloseWindow();
    }

    // -------------------------------------------------------------------------------
    // --- Implementing IUnknown ---

    bool queryInterface (const IID& iid, void** ppv) override {
        if (ppv == nullptr) return false;
        if (iid == IID_IUnknown || iid == IID_IGraphicsAdapter) {
            *ppv = static_cast<IGraphicsAdapter*>(this);
        } else {
            *ppv = nullptr;
            return false;
        }
        static_cast<IUnknown*>(*ppv)->addRef();
        return true;
    }

    void addRef  () override { CUnknown::addRef(); }
    void release () override { CUnknown::release(); }

    // -------------------------------------------------------------------------------
    // --- Implementing IGraphicsAdapter ---

    // -------------------------------------------------------------------------------
    // --- Window-related Functions ---
    
    bool shouldClose () override {
        return ::WindowShouldClose();
    }

    // -------------------------------------------------------------------------------
    // --- Window-related Functions ---

    void beginDrawing() override {
        ::BeginDrawing();
    }
    
    void endDrawing() override {
        ::EndDrawing();
    }

    void clearBackground(const Graphic::Color& color) override {
        ::ClearBackground(color);
    }

    void beginScissorMode (const Math::Vector2D& pos, const Math::Vector2D& size) override {
        ::BeginScissorMode(static_cast<int>(pos.x()),  static_cast<int>(pos.y()),
                           static_cast<int>(size.x()), static_cast<int>(size.y()));
    }
    
    void endScissorMode () override {
        ::EndScissorMode();
    }

    // -------------------------------------------------------------------------------
    // --- Input-related Functions: Keyboard ---

    bool isKeyPressed (int key) override {
        return ::IsKeyPressed(key);
    }
    
    bool isKeyPressedRepeat (int key) override {
        return ::IsKeyPressedRepeat(key);
    }
    
    bool isKeyDown (int key) override {
        return ::IsKeyDown(key);
    }
    
    bool isKeyReleased (int key) override {
        return ::IsKeyReleased(key);
    }
    
    bool isKeyUp (int key) override {
        return ::IsKeyUp(key);
    }

    // -------------------------------------------------------------------------------
    // --- Input-related Functions: Mouse ---
    
    bool isMouseButtonPressed(int button) override {
        return ::IsMouseButtonPressed(button);
    }
    
    bool isMouseButtonDown(int button) override {
        return ::IsMouseButtonDown(button);
    }
    
    bool isMouseButtonReleased(int button) override { 
        return ::IsMouseButtonReleased(button);
    }
    
    Math::Vector2D getMousePosition() override {
        ::Vector2 mouse_pos = ::GetMousePosition();
        return Math::Vector2D { mouse_pos.x, mouse_pos.y } ;
    }

    float getMouseWheelMove () override {
        return ::GetMouseWheelMove();
    }
    
    Math::Vector2D getMouseWheelMoveV () override {
        ::Vector2 wheel_move = ::GetMouseWheelMoveV();
        return Math::Vector2D { wheel_move.x, wheel_move.y } ;
    }
    
    // -------------------------------------------------------------------------------
    // --- Basic Shapes Drawing Functions ---

    void drawPixel (const Math::Vector2D& pos, const Graphic::Color& color) override {
        ::DrawPixelV(::Vector2 { pos.x(), pos.y() }, color);
    }
    
    void drawLine (const Math::Vector2D& start, const Math::Vector2D& end, const Graphic::Color& color, float thick) override {
        ::DrawLineEx(::Vector2 {start.x(), start.y()}, ::Vector2 {end.x(), end.y()}, thick, color);
    }

    void drawCircle (const Math::Vector2D& pos, float radius, const Graphic::Color& color) override {
        ::DrawCircleV(::Vector2 { pos.x(), pos.y() }, radius, color);
    }

    void drawEllipse (const Math::Vector2D& center, const Math::Vector2D& radii, const Graphic::Color& color) override {
        float r_x = radii.x() / 2.0f;
        float r_y = radii.y() / 2.0f;
    
        float center_x = center.x() + r_x;
        float center_y = center.y() + r_y;
    
        ::DrawEllipse(static_cast<int>(center_x), static_cast<int>(center_y), r_x, r_y, color);
    }

    void drawRectangle (const Math::Vector2D& pos, const Math::Vector2D& size, const Graphic::Color& color) override {
        ::DrawRectangleV(::Vector2 {pos.x(), pos.y()}, ::Vector2 {size.x(), size.y()}, color);
    }

    void drawTriangle (const Math::Vector2D& vec1, const Math::Vector2D& vec2, const Math::Vector2D& vec3, const Graphic::Color& color) override {
        ::DrawTriangle({ vec1.x(), vec1.y() },
                       { vec2.x(), vec2.y() },
                       { vec3.x(), vec3.y() }, color);
    }
    
    void drawSelectBox (const Math::Vector2D& pos, const Math::Vector2D& size, const Graphic::Color& color, float thick) override {
        float x = pos.x();
        float y = pos.y();
        float w = size.x();
        float h = size.y();
    
        const float dash_length = 6.0f; 
        const float gap_length = 4.0f;  
        const float step = dash_length + gap_length;
    
        for (float dx = 0; dx < w; dx += step) {
            float current_dash = std::min(dash_length, w - dx);
            drawLine(Math::Vector2D { x + dx, y },     Math::Vector2D { x + dx + current_dash, y },     color, thick);
            drawLine(Math::Vector2D { x + dx, y + h }, Math::Vector2D { x + dx + current_dash, y + h }, color, thick);
        }
    
        for (float dy = 0; dy < h; dy += step) {
            float current_dash = std::min(dash_length, h - dy);
            drawLine(Math::Vector2D { x, y + dy },     Math::Vector2D { x, y + dy + current_dash },     color, thick);
            drawLine(Math::Vector2D { x + w, y + dy }, Math::Vector2D { x + w, y + dy + current_dash }, color, thick);
        }
    
        float center_x = x + w / 2.0f;
        float center_y = y + h / 2.0f;
        const float cross_size = 5.0f;
    
        drawLine(Math::Vector2D { center_x - cross_size, center_y }, Math::Vector2D { center_x + cross_size, center_y }, color, thick);
        drawLine(Math::Vector2D { center_x, center_y - cross_size }, Math::Vector2D { center_x, center_y + cross_size }, color, thick);    }
};

// -------------------------------------------------------------------------------
// --- Implementing Factory ---

bool createGraphicsAdapter(int width, int height, const char* title, IGraphicsAdapter** adapter) {
    if (adapter == nullptr) return false;

    #ifndef NDEBUG
        ::SetTraceLogLevel(LOG_WARNING); 
    #else
        ::SetTraceLogLevel(LOG_NONE); 
    #endif
    
    ::InitWindow(width, height, title);
    ::SetTargetFPS(60);

    CGraphicsAdapter* adapter_temp = new CGraphicsAdapter();
    
    bool result = adapter_temp->queryInterface(IID_IGraphicsAdapter, (void**)adapter);
    
    adapter_temp->release(); 

    return result;
}

} // namespace Vectoria

#endif
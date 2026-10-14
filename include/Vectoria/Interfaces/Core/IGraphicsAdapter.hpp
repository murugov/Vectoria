#ifndef I_GRAPHICS_ADAPTER_HPP
#define I_GRAPHICS_ADAPTER_HPP

#include "Vectoria/Interfaces/Core/IUnknown.hpp"
#include "Vectoria/Shared/Colors.hpp"
#include "Vectoria/Shared/Vector.hpp"

namespace Vectoria {

extern const IID IID_IGraphicsAdapter;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"

interface IGraphicsAdapter : public IUnknown {
    // -------------------------------------------------------------------------------
    // --- Window-related Functions ---

    virtual bool shouldClose () = 0;

    // -------------------------------------------------------------------------------
    // --- Drawing-related Functions ---
    
    virtual void beginDrawing () = 0;
    virtual void endDrawing   () = 0;
    
    virtual void clearBackground (const Graphic::Color& color) = 0;
    
    virtual void beginScissorMode (const Math::Vector2D& pos, const Math::Vector2D& size) = 0;
    virtual void endScissorMode   () = 0; 
    
    // -------------------------------------------------------------------------------
    // --- Input-related Functions: Keyboard ---

    virtual bool isKeyPressed       (int key) = 0;
    virtual bool isKeyPressedRepeat (int key) = 0;
    virtual bool isKeyDown          (int key) = 0;
    virtual bool isKeyReleased      (int key) = 0;
    virtual bool isKeyUp            (int key) = 0;

    // -------------------------------------------------------------------------------
    // --- Input-related Functions: Mouse ---
    
    virtual bool isMouseButtonPressed  (int button) = 0;
    virtual bool isMouseButtonDown     (int button) = 0;
    virtual bool isMouseButtonReleased (int button) = 0;
    
    virtual Math::Vector2D getMousePosition () = 0;
    
    virtual float          getMouseWheelMove  () = 0;
    virtual Math::Vector2D getMouseWheelMoveV () = 0;
    
    // -------------------------------------------------------------------------------
    // --- Basic Shapes Drawing Functions ---

    virtual void drawPixel     (const Math::Vector2D& pos, const Graphic::Color& color) = 0;
    virtual void drawLine      (const Math::Vector2D& start, const Math::Vector2D& end, const Graphic::Color& color, float thick = 1.0f) = 0;
    virtual void drawCircle    (const Math::Vector2D& pos, float radius, const Graphic::Color& color) = 0;
    virtual void drawEllipse   (const Math::Vector2D& center, const Math::Vector2D& radii, const Graphic::Color& color) = 0;
    virtual void drawRectangle (const Math::Vector2D& pos, const Math::Vector2D& size, const Graphic::Color& color) = 0;
    virtual void drawTriangle  (const Math::Vector2D& vec1, const Math::Vector2D& vec2, const Math::Vector2D& vec3, const Graphic::Color& color) = 0;
    virtual void drawSelectBox (const Math::Vector2D& pos, const Math::Vector2D& size, const Graphic::Color& color, float thick = 1.0f) = 0;
};

bool createGraphicsAdapter(int width, int height, const char* title, IGraphicsAdapter** adapter);

#pragma clang diagnostic pop

} // namespace Vectoria

#endif
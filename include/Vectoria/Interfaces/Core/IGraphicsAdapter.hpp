#ifndef I_GRAPHICS_ADAPTER_HPP
#define I_GRAPHICS_ADAPTER_HPP

#include <string>

#include "Vectoria/Interfaces/Base/IUnknown.hpp"
#include "Vectoria/Shared/Graphic/Colors.hpp"
#include "Vectoria/Shared/Graphic/Font.hpp"
#include "Vectoria/Shared/Graphic/Texture.hpp"
#include "Vectoria/Shared/Math/Vector.hpp"

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
    
    virtual int getKeyPressed  () = 0;
    virtual int getCharPressed () = 0;

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

    virtual void drawCircleLines    (const Math::Vector2D& pos, float radius, const Graphic::Color& color, float thick = 1.0f) = 0;
    virtual void drawEllipseLines   (const Math::Vector2D& center, const Math::Vector2D& radii, const Graphic::Color& color, float thick = 1.0f) = 0;
    virtual void drawRectangleLines (const Math::Vector2D& pos, const Math::Vector2D& size, const Graphic::Color& color, float thick = 1.0f) = 0;
    virtual void drawTriangleLines  (const Math::Vector2D& vec1, const Math::Vector2D& vec2, const Math::Vector2D& vec3, const Graphic::Color& color, float thick = 1.0f) = 0;
        
    virtual void drawSelectBox (const Math::Vector2D& pos, const Math::Vector2D& size, const Graphic::Color& color, float thick = 1.0f) = 0;

    // -------------------------------------------------------------------------------
    // --- Texture Drawing Functions ---
    
    virtual void drawTexture (const Graphic::Texture& texture, const Math::Vector2D& pos, const Math::Vector2D& size,
                                float rotation = 0.0f, float scale = 1.0f, const Graphic::Color& color = Graphic::Colors::White) = 0;
    
    // -------------------------------------------------------------------------------
    // --- Text Drawing Functions ---

    virtual Graphic::Font loadFont   (const std::string& file_name, int font_size) = 0;
    virtual void          unloadFont (const Graphic::Font& font) = 0;
    
    virtual void drawText (const std::string& text, Math::Vector2D pos, int font_size, const Graphic::Color& color,
                                const Graphic::Font& font = { 0, 0 }, float spacing = 0.0f) = 0;
};

#pragma clang diagnostic pop

} // namespace Vectoria

#endif
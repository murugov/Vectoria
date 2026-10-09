#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "Graphic/SpriteMaterial.hpp"
#include "Math/Transform.hpp"
#include "Math/Vector.hpp"

namespace Graphic {

class Canvas {
private:
    Math::Transform2D transform_;
    SpriteMaterial material_;
    
public:
    // -------------------------------------------------------------------------------
    // --- Constructors ---

    Canvas (Math::Vector2D pos, int width, int height)
          : transform_{pos, {static_cast<float>(width), static_cast<float>(height)}, 1.0f, 0.0f}
          , material_() {}

    Canvas (Math::Vector2D pos, int width, int height, Color color, float scale = 1.0f)
          : transform_{pos, {static_cast<float>(width), static_cast<float>(height)}, scale, 0.0f}
          , material_(color) {}

    Canvas (Math::Vector2D pos, int width, int height, SpriteMaterial&& material, float scale = 1.0f)
          : transform_{pos, {static_cast<float>(width), static_cast<float>(height)}, scale, 0.0f}
          , material_(std::move(material)) {}

    Canvas (Math::Vector2D pos, Math::Vector2D size, Color color, float scale = 1.0f)
        : transform_{pos, size, scale, 0.0f}
        , material_(color) {}
        
    Canvas (Math::Vector2D pos, Math::Vector2D size, SpriteMaterial&& material, float scale = 1.0f)
        : transform_{pos, size, scale, 0.0f}
        , material_(std::move(material)) {}

    // --- Copy Semantics Disabled ---

    Canvas (const Canvas& other) = delete;
    Canvas& operator = (const Canvas& other) = delete;

    // --- Move Semantics ---
    
    Canvas (Canvas&& other) noexcept = default;
    Canvas& operator = (Canvas&& other) noexcept = default;

    ~Canvas () = default;
    
    // -------------------------------------------------------------------------------
    // --- Getters ---
    
    Math::Vector2D pos ()     const { return transform_.pos; }
    float          x ()       const { return transform_.pos.x(); }
    float          y ()       const { return transform_.pos.y(); }
    Math::Vector2D size ()    const { return transform_.size; }
    int            width ()   const { return static_cast<int>(transform_.size.x()); }
    int            height ()  const { return static_cast<int>(transform_.size.y()); }
    float          scale ()   const { return transform_.scale; }
    
    const SpriteMaterial& material () const { return material_; }

    // -------------------------------------------------------------------------------
    // --- Setters ---

    void setPos    (Math::Vector2D pos)  { transform_.pos = pos; }
    void setX      (int x)               { transform_.pos.setX(static_cast<float>(x)); }
    void setY      (int y)               { transform_.pos.setX(static_cast<float>(y)); }
    void setSize   (Math::Vector2D size) { transform_.size = size; }
    void setWidth  (int width)           { transform_.size.setX(static_cast<float>(width)); }
    void setHeight (int height)          { transform_.size.setX(static_cast<float>(height)); }
    void setScale  (float scale)         { transform_.scale = scale; }
    
    // -------------------------------------------------------------------------------
    // --- Methods Prototypes ---
    
    void draw () const;
};

} // namespace Graphic

#endif

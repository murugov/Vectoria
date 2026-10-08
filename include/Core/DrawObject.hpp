#ifndef DRAW_OBJECT_HPP
#define DRAW_OBJECT_HPP

#include "Core/Object.hpp"
#include "Graphic/Colors.hpp"
#include "Math/Vector.hpp"

namespace Core {
    
class DrawObject : public Object {
protected:
    Graphic::Color fillColor_;
    Graphic::Color strokeColor_;
    float strokeWidth_ = 1.0f;
    
public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---

    DrawObject (Math::Vector2D pos, Math::Vector2D size, bool state = true)
        : Object(pos, size, state) {}


    // --- Destructor ---
    
    ~DrawObject () override = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---

    Graphic::Color fillColor   () { return fillColor_; }
    Graphic::Color strokeColor () { return strokeColor_; }
    float          strokeWidth () { return strokeWidth_; }

    // -------------------------------------------------------------------------------
    // --- Pure Virtual Methods ---
    
    virtual void draw () const = 0;
};

} // namespace Core

#endif
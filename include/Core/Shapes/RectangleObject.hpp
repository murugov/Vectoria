#ifndef RECTANGLE_OBJECT_HPP
#define RECTANGLE_OBJECT_HPP

#include "Core/DrawObject.hpp"

namespace Core {

class RectangleObject : public DrawObject {
public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---
    
    RectangleObject(Math::Vector2D pos, Math::Vector2D size)
        : DrawObject(pos, size) {}

    // --- Destructor ---
    
    ~RectangleObject() override = default;

    // -------------------------------------------------------------------------------
    // --- Pure Virtual Methods ---

    bool contains (const Math::Vector2D& point) const override;

    virtual void draw () const override;
};

} // namespace Core

#endif
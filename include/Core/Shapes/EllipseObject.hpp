#ifndef ELLIPSE_OBJECT_HPP
#define ELLIPSE_OBJECT_HPP

#include "Core/DrawObject.hpp"
#include "Math/Vector.hpp"

namespace Core {

class EllipseObject : public DrawObject {
public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---
    
    EllipseObject(Math::Vector2D pos, Math::Vector2D size)
        : DrawObject(pos, size) {}

    // --- Virtual Destructor ---
    
    ~EllipseObject() override = default;

    // -------------------------------------------------------------------------------
    // --- Virtual Methods Prototypes ---

    bool contains (const Math::Vector2D& point) const override;
    
    virtual void draw () const override;
};

} // namespace Core

#endif
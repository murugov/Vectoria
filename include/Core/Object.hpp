#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Math/Vector.hpp"

namespace Core {

class Object {
protected:
    Math::Vector2D pos_;
    Math::Vector2D size_;
    bool enabled_;
    
public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---

    Object (Math::Vector2D pos, Math::Vector2D size, bool state = true)
        : pos_(pos), size_(size), enabled_(state) {}

    // --- Virtual Destructor ---
    
    virtual ~Object () = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---
    
    Math::Vector2D pos       () const { return pos_; }
    Math::Vector2D size      () const { return size_; }
    bool           isEnabled () const { return enabled_; }

    // -------------------------------------------------------------------------------
    // --- Setters ---
    
    void setPosition (const Math::Vector2D& pos)  { pos_ = pos; }
    void setSize     (const Math::Vector2D& size) { size_ = size; }
    void setEnabled  (bool enabled)               { enabled_ = enabled; }
    
    // -------------------------------------------------------------------------------
    // --- Pure Virtual Methods ---
    
    virtual void update   (float /*dt*/) {}
    virtual bool contains (const Math::Vector2D& point) const = 0;
};

} // namespace Core

#endif
#ifndef C_ELLIPSE_HPP
#define C_ELLIPSE_HPP

#include "Vectoria/Base/CUnknown.hpp"
#include "Vectoria/Interfaces/Components/IShape.hpp"
#include "Vectoria/Shared/Colors.hpp"

namespace Vectoria {

class CEllipse : public CUnknown, public IShape {
private:
    Math::Vector2D pos_;
    Math::Vector2D size_;
    Graphic::Color color_;

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    CEllipse () = default;

    // --- Virtual Destructor ---
    
    ~CEllipse () override = default;

    // -------------------------------------------------------------------------------
    // --- Implementing IUnknown ---

    bool queryInterface (const IID& iid, void** ppv) override {
        if (ppv == nullptr) return false;

        if (iid == IID_IUnknown || iid == IID_IShape) {
            *ppv = static_cast<IShape*>(this);
        }
        else {
            *ppv = nullptr;
            return false;
        }

        static_cast<IUnknown*>(*ppv)->addRef();
        return true;
    }

    void addRef  () override { CUnknown::addRef(); }
    void release () override { CUnknown::release(); }

    // -------------------------------------------------------------------------------
    // --- Implementing IShape ---
    
    void draw (IGraphicsAdapter* adapter) override {
        if (adapter) {
            adapter->drawEllipse(pos_, size_, color_);
        }
    }

    void setBounds (const Math::Vector2D& pos, const Math::Vector2D& size) override {
        pos_  = pos;
        size_ = size;
    }

    void getBounds (Math::Vector2D* pos, Math::Vector2D* size) override {
        if (pos && size) {
            *pos  = pos_;
            *size = size_;
        }
    }

    void setColor (const Graphic::Color& color) override {
        color_ = color;
    }

    bool contains (const Math::Vector2D& point) override {
        float r_x = size_.x() / 2.0f;
        float r_y = size_.y() / 2.0f;
        Math::Vector2D center = pos_ + Math::Vector2D {r_x, r_y};
   
        float dx = point.x() - center.x();
        float dy = point.y() - center.y();
   
        return (dx * dx) * (r_y * r_y) + (dy * dy) * (r_x * r_x) <= (r_x * r_x) * (r_y * r_y);
    }
};

} // namespace Vectoria

#endif
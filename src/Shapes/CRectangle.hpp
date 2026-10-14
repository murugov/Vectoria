#ifndef C_RECTANGLE_HPP
#define C_RECTANGLE_HPP

#include "Vectoria/Base/CUnknown.hpp"
#include "Vectoria/Interfaces/Components/IShape.hpp"
#include "Vectoria/Shared/Colors.hpp"

namespace Vectoria {

class CRectangle : public CUnknown, public IShape {
private:
    Math::Vector2D pos_;
    Math::Vector2D size_;
    Graphic::Color color_;

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    CRectangle () = default;

    // --- Virtual Destructor ---
    
    ~CRectangle () override = default;

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
            adapter->drawRectangle(pos_, size_, color_);
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
        return (point.x() >= pos_.x() && point.x() <= pos_.x() + size_.x()) &&
               (point.y() >= pos_.y() && point.y() <= pos_.y() + size_.y());
    }
};

} // namespace Vectoria

#endif
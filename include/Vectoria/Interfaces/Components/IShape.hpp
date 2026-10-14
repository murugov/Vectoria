#ifndef I_SHAPE_HPP
#define I_SHAPE_HPP

#include "Vectoria/Interfaces/Core/IGraphicsAdapter.hpp"
#include "Vectoria/Interfaces/Core/IUnknown.hpp"
#include "Vectoria/Shared/Colors.hpp"
#include "Vectoria/Shared/Vector.hpp"

namespace Vectoria {

extern const IID IID_IShape;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"

interface IShape : public IUnknown {
    virtual void setBounds (const Math::Vector2D& pos, const Math::Vector2D& size) = 0;
    virtual void getBounds (Math::Vector2D* pos, Math::Vector2D* size) = 0;
    virtual void setColor  (const Graphic::Color& color) = 0;
    
    virtual void draw (IGraphicsAdapter* adapter) = 0;
    virtual bool contains (const Math::Vector2D& point) = 0; 
};

#pragma clang diagnostic pop

} // namespace Vectoria

#endif
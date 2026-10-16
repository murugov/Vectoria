#ifndef I_WINDOW_HPP
#define I_WINDOW_HPP

#include "Vectoria/Interfaces/Base/IUnknown.hpp"
#include "Vectoria/Interfaces/Core/IGraphicsAdapter.hpp"
#include "Vectoria/Shared/Math/Vector.hpp"

namespace Vectoria {

extern const IID IID_IWindow;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"

interface IWindow : public IUnknown {
    virtual void setBounds (const Math::Vector2D& pos, const Math::Vector2D& size) = 0;
    virtual void getBounds (Math::Vector2D* pos, Math::Vector2D* size) = 0;
    
    virtual void show    (bool visible) = 0;
    virtual void refresh (IGraphicsAdapter* adapter) = 0;
};

#pragma clang diagnostic pop

} // namespace Vectoria

#endif
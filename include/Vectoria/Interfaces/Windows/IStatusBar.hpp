#ifndef I_STATUS_BAR_HPP
#define I_STATUS_BAR_HPP

#include "Vectoria/Interfaces/Base/IWindow.hpp"
#include "Vectoria/Shared/Math/Vector.hpp"

namespace Vectoria {

extern const IID IID_IStatusBar;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"

interface IStatusBar : public IWindow {
    virtual void setMessage       (const char* text) = 0;
    virtual void setMousePosition (const Math::Vector2D& pos) = 0;
    virtual void clearMessage     () = 0;
};

#pragma clang diagnostic pop

} // namespace Vectoria

#endif

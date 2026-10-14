#ifndef I_STATUS_BAR_HPP
#define I_STATUS_BAR_HPP

#include "Vectoria/Interfaces/Core/IWindow.hpp"
#include "Vectoria/Shared/Vector.hpp"

namespace Vectoria {

extern const IID IID_IStatusBar;

interface IStatusBar : public IWindow {
    virtual void setMessage       (const char* text) = 0;
    virtual void setMousePosition (const Math::Vector2D& pos) = 0;
    virtual void clearMessage     () = 0;
};

} // namespace Vectoria

#endif

#ifndef I_COLOR_BAR_HPP
#define I_COLOR_BAR_HPP

#include "Vectoria/Interfaces/Base/IWindow.hpp"
#include "Vectoria/Shared/Graphic/Colors.hpp"

namespace Vectoria {

extern const IID IID_IColorBar;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"

interface IColorBar : public IWindow {
    virtual bool setActiveColor (const Graphic::Color& color) = 0;
    virtual bool getActiveColor (Graphic::Color* color) = 0;
    virtual void updateSelection () = 0;
};

#pragma clang diagnostic pop

} // namespace Vectoria

#endif

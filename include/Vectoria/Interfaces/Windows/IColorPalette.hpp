#ifndef I_COLOR_PALETTE_HPP
#define I_COLOR_PALETTE_HPP

#include "Vectoria/Interfaces/Core/IWindow.hpp"
#include "Vectoria/Shared/Colors.hpp"

namespace Vectoria {

extern const IID IID_IColorPalette;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"

interface IColorPalette : public IWindow {
    virtual bool setActiveColor (const Graphic::Color& color) = 0;
    virtual bool getActiveColor (Graphic::Color* color) = 0;
    virtual void updateSelection () = 0;
};

#pragma clang diagnostic pop

} // namespace Vectoria

#endif

#ifndef I_COLOR_PALETTE_HPP
#define I_COLOR_PALETTE_HPP

#include "Vectoria/Interfaces/Core/IWindow.hpp"
#include "Vectoria/Shared/Colors.hpp"

namespace Vectoria {

extern const IID IID_IColorPalette;

interface IColorPalette : public IWindow {
    virtual void selectColor    (const Graphic::Color& color) = 0;
    virtual void getActiveColor (Graphic::Color* color) = 0;
    virtual void updateSelection () = 0;
};

} // namespace Vectoria

#endif

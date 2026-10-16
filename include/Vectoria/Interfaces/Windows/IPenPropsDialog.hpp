#ifndef I_PEN_PROPS_DIALOG_HPP
#define I_PEN_PROPS_DIALOG_HPP

#include "Vectoria/Interfaces/Windows/IDialogWindow.hpp"
#include "Vectoria/Shared/Graphic/Colors.hpp"

namespace Vectoria {

extern const IID IID_IpenPropsDialog;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"

interface IpenPropsDialog : public IDialogWindow {
    virtual void setSizeProperty  (int px) = 0;
    virtual void setColorProperty (const Graphic::Color& color) = 0;
};

#pragma clang diagnostic pop

} // namespace Vectoria

#endif
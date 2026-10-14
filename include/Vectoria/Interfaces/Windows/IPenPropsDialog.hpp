#ifndef I_PEN_PROPS_DIALOG_HPP
#define I_PEN_PROPS_DIALOG_HPP

#include "Vectoria/Interfaces/Windows/IDialogWindow.hpp"
#include "Vectoria/Shared/Colors.hpp"

namespace Vectoria {

extern const IID IID_IpenPropsDialog;

interface IpenPropsDialog : public IDialogWindow {
    virtual void setSizeProperty  (int px) = 0;
    virtual void setColorProperty (const Graphic::Color& color) = 0;
};

} // namespace Vectoria

#endif
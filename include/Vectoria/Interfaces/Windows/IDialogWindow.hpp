#ifndef I_DIALOG_WINDOW_HPP
#define I_DIALOG_WINDOW_HPP

#include "Vectoria/Interfaces/Base/IWindow.hpp"

namespace Vectoria {

extern const IID IID_IDialogWindow;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"

interface IDialogWindow : public IWindow {
    virtual bool doModal () = 0; 
};

#pragma clang diagnostic pop

} // namespace Vectoria

#endif
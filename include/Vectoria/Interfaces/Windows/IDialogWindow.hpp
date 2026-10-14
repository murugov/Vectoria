#ifndef I_DIALOG_WINDOW_HPP
#define I_DIALOG_WINDOW_HPP

#include "Vectoria/Interfaces/Core/IWindow.hpp"

namespace Vectoria {

extern const IID IID_IDialogWindow;

interface IDialogWindow : public IWindow {
    virtual bool doModal () = 0; 
};

} // namespace Vectoria

#endif
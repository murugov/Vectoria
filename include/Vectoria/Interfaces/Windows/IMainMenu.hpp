#ifndef I_MAIN_MENU_HPP
#define I_MAIN_MENU_HPP

#include "Vectoria/Interfaces/Core/IWindow.hpp"

namespace Vectoria {

extern const IID IID_IMainMenu;

interface IMainMenu : public IWindow {
    virtual void setItemEnabled (unsigned int command_id, bool enabled) = 0;
    virtual void onMenuCommand  (unsigned int command_Id) = 0;
};

} // namespace Vectoria

#endif

#ifndef I_MAIN_MENU_HPP
#define I_MAIN_MENU_HPP

#include "Vectoria/Interfaces/Base/IWindow.hpp"
#include "Vectoria/Shared/Graphic/Colors.hpp"

namespace Vectoria {

extern const IID IID_IMainMenu;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"

interface IMainMenu : public IWindow {
    virtual void setColor       (const Graphic::Color& color) = 0;
    virtual void setFont        (const Graphic::Font& font) = 0;
    virtual void setItemEnabled (unsigned int command_id, bool enabled) = 0;
    virtual void onMenuCommand  (unsigned int command_Id) = 0;
};

#pragma clang diagnostic pop

} // namespace Vectoria

#endif

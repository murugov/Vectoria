#ifndef I_CONTEXT_BAR_HPP
#define I_CONTEXT_BAR_HPP

#include "Vectoria/Interfaces/Base/IWindow.hpp"

namespace Vectoria {

extern const IID IID_IContextBar;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"

interface IContextBar : public IWindow {
    virtual void updateContext (const IID& active_tool_id) = 0;
    virtual void clearContext  () = 0;
};

#pragma clang diagnostic pop

} // namespace Vectoria

#endif

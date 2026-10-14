#ifndef I_CONTEXT_BAR_HPP
#define I_CONTEXT_BAR_HPP

#include "Vectoria/Interfaces/Core/IWindow.hpp"

namespace Vectoria {

extern const IID IID_IContextBar;

interface IContextBar : public IWindow {
    virtual void updateContext (const IID& active_tool_id) = 0;
    virtual void clearContext  () = 0;
};

} // namespace Vectoria

#endif

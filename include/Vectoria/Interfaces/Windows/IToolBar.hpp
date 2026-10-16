#ifndef I_TOOL_BAR_HPP
#define I_TOOL_BAR_HPP

#include "Vectoria/Interfaces/Base/ITool.hpp"
#include "Vectoria/Interfaces/Base/IWindow.hpp"

namespace Vectoria {

extern const IID IID_IToolBar;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"

interface IToolBar : public IWindow {
    virtual bool setActiveTool   (const IID& tool_id, ITool** tool) = 0;
    virtual bool getActiveTool   (ITool** tool) = 0;
    virtual void updateSelection () = 0;
};

#pragma clang diagnostic pop

} // namespace Vectoria

#endif

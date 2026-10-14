#ifndef I_TOOL_PALETTE_HPP
#define I_TOOL_PALETTE_HPP

#include "Vectoria/Interfaces/Components/ITool.hpp"
#include "Vectoria/Interfaces/Core/IWindow.hpp"

namespace Vectoria {

extern const IID IID_IToolPalette;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"

interface IToolPalette : public IWindow {
    virtual bool setActiveTool   (const IID& tool_id, ITool** tool) = 0;
    virtual bool getActiveTool   (ITool** tool) = 0;
    virtual void updateSelection () = 0;
};

#pragma clang diagnostic pop

} // namespace Vectoria

#endif

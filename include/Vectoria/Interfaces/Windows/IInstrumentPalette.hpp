#ifndef I_INSTRUMENT_PALETTE_HPP
#define I_INSTRUMENT_PALETTE_HPP

#include "Vectoria/Interfaces/Components/ITool.hpp"
#include "Vectoria/Interfaces/Core/IWindow.hpp"

namespace Vectoria {

extern const IID IID_IInstrumentPalette;

interface IInstrumentPalette : public IWindow {
    virtual bool selectInstrument    (const IID& tool_id, ITool** tool) = 0;
    virtual bool getActiveInstrument (ITool** tool) = 0;
    virtual void updateSelection     () = 0;
};

} // namespace Vectoria

#endif

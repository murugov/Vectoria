#ifndef I_CONTROLLER_HPP
#define I_CONTROLLER_HPP

#include "Vectoria/Interfaces/Core/IUnknown.hpp"
#include "Vectoria/Interfaces/Core/IGraphicsAdapter.hpp"
#include "Vectoria/Interfaces/Windows/IDocumentWindow.hpp"

namespace Vectoria {

extern const IID IID_IController;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"

interface IController : public IUnknown {
    virtual void initialize    (IGraphicsAdapter* adapter, IDocumentWindow* doc) = 0;
    virtual bool setInstrument (const IID& tool_id) = 0;
    
    virtual void update () = 0;
    virtual void render () = 0;
};

#pragma clang diagnostic pop

} // namespace Vectoria

#endif

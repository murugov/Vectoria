#ifndef I_CONTROLLER_HPP
#define I_CONTROLLER_HPP

#include "Vectoria/Interfaces/Core/IUnknown.hpp"
#include "Vectoria/Interfaces/Core/IGraphicsAdapter.hpp"

namespace Vectoria {

extern const IID IID_IDesktop;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"

interface IDesktop : public IUnknown {
    virtual void initialize        (IGraphicsAdapter* adapter) = 0;
    virtual bool setActiveDocument (const IID& doc_id) = 0;
    
    virtual void update () = 0;
    virtual void render () = 0;
};

#pragma clang diagnostic pop

} // namespace Vectoria

#endif

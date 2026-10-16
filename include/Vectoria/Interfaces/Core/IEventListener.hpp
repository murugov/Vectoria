#ifndef I_EVENT_LISTENER_HPP
#define I_EVENT_LISTENER_HPP

#include "Vectoria/Interfaces/Base/IUnknown.hpp"
#include "Vectoria/Shared/Input/InputEvents.hpp"

namespace Vectoria {

extern const IID IID_IEventListener;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"

interface IEventListener : public IUnknown {
    virtual bool onEvent (const Event& event) = 0;
};

#pragma clang diagnostic pop

} // namespace Vectoria

#endif
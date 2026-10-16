#ifndef I_ACTION_HPP
#define I_ACTION_HPP

#include "Vectoria/Interfaces/Base/IUnknown.hpp"

namespace Vectoria {

extern const IID IID_IAction;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"

interface IAction : public IUnknown {
    virtual unsigned int getID () = 0;
    virtual const char*  getLabel () = 0;

    virtual bool isEnabled () = 0;
    virtual void setEnabled (bool enabled) = 0;

    virtual void execute () = 0;
};

#pragma clang diagnostic pop

} // namespace Vectoria

#endif
#ifndef I_ACTION_GROUP_HPP
#define I_ACTION_GROUP_HPP

#include "Vectoria/Interfaces/Base/IAction.hpp"

namespace Vectoria {

extern const IID IID_IActionGroup;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"

interface IActionGroup : public IAction {
    virtual void         addChild (IAction* action) = 0;
    virtual unsigned int getChildren (IAction** actions_buffer, unsigned int max_count) = 0;
};

#pragma clang diagnostic pop

} // namespace Vectoria

#endif

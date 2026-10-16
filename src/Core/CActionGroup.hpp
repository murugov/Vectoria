#ifndef C_ACTION_GROUP_HPP
#define C_ACTION_GROUP_HPP

#include <vector>
#include <algorithm>

#include "Vectoria/Interfaces/Core/IActionGroup.hpp"

#include "Base/CAction.hpp"

namespace Vectoria {

class CActionGroup : public CAction, public IActionGroup {
private:
    std::vector<IAction*> children_ {};

public:
    // -------------------------------------------------------------------------------
    // --- Constructors ---

    CActionGroup (unsigned int id, const char* label, std::function<void()> callback = nullptr)
            : CAction(id, label, callback) {}

    // --- Virtual Destructor ---
    
    ~CActionGroup () override {
        for (auto* child : children_) {
            if (child) {
                child->release();
            }
        }
    }

    // -------------------------------------------------------------------------------
    // --- Implementing IUncnown ---

    bool queryInterface (const IID& iid, void** ppv) override {
        if (ppv == nullptr) return false;
        if (iid == IID_IUnknown || iid == IID_IAction || iid == IID_IActionGroup) {
            *ppv = static_cast<IActionGroup*>(this);
        }
        else {
            *ppv = nullptr;
            return false;
        }
        static_cast<IUnknown*>(*ppv)->addRef();
        return true;
    }
    
    void addRef  () override { CUnknown::addRef(); }
    void release () override { CUnknown::release(); }

    // -------------------------------------------------------------------------------
    // --- Implementing IActionGroup ---
    
    void addChild (IAction* action) override {
        if (action != nullptr) {
            action->addRef();
            children_.push_back(action);
        }
    }

    unsigned int getChildren (IAction** actions, unsigned int max_count) override {
        unsigned int count = static_cast<unsigned int>(std::min(max_count, static_cast<unsigned int>(children_.size())));
        for (unsigned int i = 0; i < count; ++i) {
            actions[i] = children_[i];
            actions[i]->addRef();
        }
        return static_cast<unsigned int>(children_.size());
    }
};

} // namespace Vectoria

#endif
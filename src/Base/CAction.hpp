#ifndef C_ACTION_HPP
#define C_ACTION_HPP

#include <cstddef>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

#include "Vectoria/Interfaces/Base/IAction.hpp"

#include "Base/CUnknown.hpp"

namespace Vectoria {

class CAction : public CUnknown, public IAction {
private:
    unsigned int id_;
    std::string  label_;
    bool         is_enabled_ = true;
    
    std::function<void()> execute_callback_ = nullptr;

public:
    // -------------------------------------------------------------------------------
    // --- Constructors ---

    CAction (unsigned int id, const char* label, std::function<void()> callback = nullptr)
        : id_(id), label_(label), execute_callback_(callback) {}

    // --- Virtual Destructor ---
    
    ~CAction () override = default;
    
    // -------------------------------------------------------------------------------
    // --- Implementing IUncnown ---

    bool queryInterface (const IID& iid, void** ppv) override {
        if (ppv == nullptr) return false;
        if (iid == IID_IUnknown || iid == IID_IAction) {
            *ppv = static_cast<IAction*>(this);
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
    // --- Implementing IAction ---

    unsigned int getID ()    override { return id_; }
    const char*  getLabel () override { return label_.c_str(); }
    
    bool isEnabled ()              override { return is_enabled_; }
    void setEnabled (bool enabled) override { is_enabled_ = enabled; }
    
    void execute() override {
        if (is_enabled_ && execute_callback_) {
            execute_callback_();
        }
    }
};

} // namespace Vectoria

#endif
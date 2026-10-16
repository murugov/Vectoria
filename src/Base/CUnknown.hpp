#ifndef C_UNKNOWN_HPP
#define C_UNKNOWN_HPP

#include <atomic>

#include "Vectoria/Interfaces/Base/IUnknown.hpp"

namespace Vectoria {

class CUnknown : public IUnknown {
protected:
    // NOTE: `std::atomic` is needed here to protect the program from data races in a multithreaded environment.
    std::atomic<unsigned long> count_refs_;

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    CUnknown () : count_refs_(1) {}

    // --- Virtual Destructor ---
    
    virtual ~CUnknown () {}

    // -------------------------------------------------------------------------------
    // --- Implementing IUnknown ---
    
    void addRef () override {
        count_refs_++;
    }

    void release () override {
        if (--count_refs_ == 0) {
            delete this;
        }
    }

    // --- Pure Virtual Functions ---

    virtual bool queryInterface (const IID& iid, void** ppv) override = 0;
};

} // namespace Vectoria

#endif
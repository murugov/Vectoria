#ifndef C_WINDOW_HPP
#define C_WINDOW_HPP

#include "Vectoria/Interfaces/Base/IWindow.hpp"
#include "Vectoria/Interfaces/Core/IGraphicsAdapter.hpp"

#include "Base/CUnknown.hpp"

namespace Vectoria {

class CWindow : public CUnknown, public IWindow {
protected:
    Math::Vector2D pos_ { 0.0f, 0.0f };
    Math::Vector2D size_ { 800.0f, 600.0f };
    bool visible_ = true;

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    CWindow () = default;

    // --- Virtual Destructor ---
    
    ~CWindow () override = default;

    // -------------------------------------------------------------------------------
    // --- Implementing IWindow ---
    
    void setBounds (const Math::Vector2D& pos, const Math::Vector2D& size) override {
        pos_  = pos;
        size_ = size;
    }

    void getBounds (Math::Vector2D* pos, Math::Vector2D* size) override {
        if (pos && size) {
            *pos  = pos_;
            *size = size_;
        }
    }

    void show (bool visible) override { visible_ = visible; }

    // --- Pure Virtual Functions ---

    void refresh (IGraphicsAdapter* adapter) override = 0;
};

} // namespace Vectoria

#endif
#ifndef C_INPUT_CONTROLLER_HPP
#define C_INPUT_CONTROLLER_HPP

#include <vector>

#include "Vectoria/Interfaces/Core/IGraphicsAdapter.hpp"
#include "Vectoria/Shared/Input/InputEvents.hpp"

namespace Vectoria {

class CInputController {
private:
    std::vector<Event> accumulated_events_ {};
    Math::Vector2D     last_mouse_pos_ {};

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    CInputController () = default;

    // --- Destructor ---
    
    ~CInputController () = default;

    // -------------------------------------------------------------------------------
    // --- Implementing Of Methods ---
    
    void update (IGraphicsAdapter* adapter) {
        if (adapter == nullptr) return;

        accumulated_events_.clear();
        
        // Mouse Handling: Movement
        Math::Vector2D current_mouse_pos = adapter->getMousePosition();
        if (current_mouse_pos != last_mouse_pos_) {
            last_mouse_pos_ = current_mouse_pos;
            
            accumulated_events_.push_back(
                 Event::create_mouse_event(EventType::mouse_move, current_mouse_pos, -1)
             );        }

        // Mouse Handling: Click (0 - Left, 1 - Right)
        for (int button = 0; button <= 1; ++button) {
            // Button press
            if (adapter->isMouseButtonPressed(button)) {
                accumulated_events_.push_back(
                    Event::create_mouse_event(EventType::mouse_down, current_mouse_pos, button)
                );
            }
            // Button Release
            if (adapter->isMouseButtonReleased(button)) {
                accumulated_events_.push_back(
                    Event::create_mouse_event(EventType::mouse_up, current_mouse_pos, button)
                );
            }
        }

        int key_code = adapter->getKeyPressed();
        while (key_code != 0) {
            accumulated_events_.push_back(
                Event::create_key_event(EventType::key_pressed, key_code, false)
            );
            key_code = adapter->getKeyPressed();
        }
    }

    const std::vector<Event>& get_events() const {
        return accumulated_events_;
    }
};

} // namespace Vectoria

#endif
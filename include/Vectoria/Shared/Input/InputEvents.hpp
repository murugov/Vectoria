#ifndef INPUT_EVENTS_HPP
#define INPUT_EVENTS_HPP

#include "Vectoria/Shared/Math/Vector.hpp"

namespace Vectoria {

enum class EventType {
    mouse_down,
    mouse_up,
    mouse_move,
    key_pressed
};

struct MouseEvent {
    Math::Vector2D position;
    int            button; // 0 - Left, 1 - Right
};

struct KeyboardEvent {
    int  key_code;
    bool is_repeat;
};

struct Event {
    EventType type;
    union {
        MouseEvent    mouse;
        KeyboardEvent key;
    };

    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    Event () : type(EventType::mouse_move), mouse{} {}

    // --- Destructor ---

    ~Event () = default;

    // -------------------------------------------------------------------------------
    // --- Implementing Of Methods ---

    static Event create_mouse_event(EventType t, const Math::Vector2D& pos, int btn) {
        Event e;
        e.type = t;
        e.mouse.position = pos;
        e.mouse.button = btn;
        return e;
    }

    static Event create_key_event(EventType t, int code, bool repeat) {
        Event e;
        e.type = t;
        e.key.key_code = code;
        e.key.is_repeat = repeat;
        return e;
    }
};

} // namespace Vectoria

#endif
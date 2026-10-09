#include "Graphic/Camera.hpp"
#include "Graphic/Adapter.hpp"

namespace Graphic {

// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---

void Camera::begin () const {
    BeginMode2D(raw_camera_);
}

void Camera::end () const {
    EndMode2D();
}

void Camera::lookAt (const Math::Vector2D& world_pos) {
    raw_camera_.target = ::Vector2{ world_pos.x(), world_pos.y() };
}

Math::Vector2D Camera::screenToWorld (const Math::Vector2D& screen_pos) const {
    ::Vector2 world = GetScreenToWorld2D(
        ::Vector2{ screen_pos.x(), screen_pos.y() }, 
        raw_camera_
    );
    return Math::Vector2D{ world.x, world.y };
}

}
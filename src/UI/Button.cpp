#include <iostream>
#include "UI/Button.hpp"

namespace UI {

// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---

void Button::click () {
    if (command_) {
        command_->execute();
    }
}

} // namespace UI
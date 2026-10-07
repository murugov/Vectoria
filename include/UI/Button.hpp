#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Graphic/SpriteMaterial.hpp"
#include "Math/Vector.hpp"
#include "UI/Command.hpp"

namespace UI {

enum class ButtonState {
    Normal,
    Hovered,
    Pressed
};

class Button {
private:
    Graphic::SpriteMaterial material_;
    Math::Vector2D size_;
    ButtonState state_;
    std::unique_ptr<Command> command_;
    
public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    Button (
            Graphic::SpriteMaterial&& material,
            Math::Vector2D size)
            : material_(std::move(material))
            , size_(size)
            , state_(ButtonState::Normal)
            , command_(nullptr)
            {}

    // -------------------------------------------------------------------------------
    // --- Getters ---

    Math::Vector2D size  () const { return size_; };
    ButtonState    state () const { return state_; };
    
    // -------------------------------------------------------------------------------
    // --- Setters ---
    
    void setCommand (std::unique_ptr<Command> command) { command_ = std::move(command); };
    void setState   (ButtonState state)                { state_ = state; };    

    // -------------------------------------------------------------------------------
    // --- Methods Prototypes ---
    
    void click ();
};

} // namespace UI

#endif
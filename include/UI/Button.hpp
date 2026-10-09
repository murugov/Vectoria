#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <memory>
#include "Core/Object.hpp"
#include "Graphic/SpriteMaterial.hpp"
#include "Math/Vector.hpp"
#include "UI/Command.hpp"

namespace UI {

enum class ButtonState {
    Normal,
    Hovered,
    Pressed
};

class Button : public Core::Object {
protected:
    Graphic::SpriteMaterial material_;
    ButtonState state_;
    std::unique_ptr<Command> command_;
        
public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    Button (Math::Vector2D pos,
            Math::Vector2D size,
            Graphic::SpriteMaterial&& material)
            : Core::Object(pos, size, true)
            , material_(std::move(material))
            , state_(ButtonState::Normal)
            , command_(nullptr)
            {}

    // --- Virtual Destructor ---

    ~Button () override = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---

    ButtonState state () const { return state_; }
    
    // -------------------------------------------------------------------------------
    // --- Setters ---
    
    void setState   (ButtonState state)                { state_ = state; }    
    void setCommand (std::unique_ptr<Command> command) { command_ = std::move(command); }
    
    // -------------------------------------------------------------------------------
    // --- Methods Prototypes ---
    
    void click ();

    // -------------------------------------------------------------------------------
    // --- Virtual Methods Prototypes ---
    
    virtual void draw () const = 0;
    
    bool contains (const Math::Vector2D& point) const override;
};

} // namespace UI

#endif
#ifndef CHANGE_COLOR_COMMAND_HPP
#define CHANGE_COLOR_COMMAND_HPP

#include "UI/Command.hpp"
#include "Core/Controller.hpp"
#include "Graphic/Colors.hpp"

namespace UI {

class ChangeColorCommand : public Command {
private:
    Core::Controller& controller_;
    Graphic::Color color_;

public:
    ChangeColorCommand(Core::Controller& controller, Graphic::Color color)
        : controller_(controller), color_(color) {}

    void execute() override {
        controller_.setActiveColor(color_);
    }
};

} // namespace UI

#endif

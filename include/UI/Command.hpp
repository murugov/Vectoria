#ifndef COMMAND_HPP
#define COMMAND_HPP

namespace UI {

class Command {
public:
    virtual ~Command () = default;
    virtual void execute () = 0;
};

} // namespace UI

#endif
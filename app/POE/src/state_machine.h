#ifndef STATE_MACHING_H
#define STATE_MACHING_H

#include "niu2x_alias.h"

namespace sm {

class State {
public:
    virtual ~State() { }
    virtual void enter() { }
    virtual void exit() { }
    virtual void step(double dt) { }
};

class StateMachine : private Noncopyable {
public:
    StateMachine();
    void set_init_state(UPtr<State> init_state);
    ~StateMachine();

    void step(double t);
    void change_state(UPtr<State> new_state);

private:
    Vector<UPtr<State>> states_;
    State* cur_state_ = nullptr;
};

} // namespace sm

#endif
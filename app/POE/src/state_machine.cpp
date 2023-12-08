#include "state_machine.h"

namespace sm {

StateMachine::StateMachine() { }

void StateMachine::set_init_state(UPtr<State> init_state)
{
    cur_state_ = init_state.get();
    states_.clear();
    states_.push_back(std::move(init_state));

    cur_state_->enter();
}

void StateMachine::step(double t) { cur_state_->step(t); }

StateMachine::~StateMachine() { }

void StateMachine::change_state(UPtr<State> new_state)
{
    cur_state_->exit();
    states_.erase(states_.end() - 1);

    cur_state_ = new_state.get();
    states_.push_back(std::move(new_state));

    cur_state_->enter();
}

} // namespace sm

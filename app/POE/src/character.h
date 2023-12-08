#ifndef CHARACTER_H
#define CHARACTER_H

#include <functional>
#include "ogre_alias.h"
#include "niu2x_alias.h"
#include "state_machine.h"

// class CharacterStateFactory {
// public:
//     virtual ~CharacterStateFactory() { }
//     virtual UPtr<State> create_run_state()  { return nullptr; }
// };

#define create_character_state_imp(enter, exit, step)                          \
    std::make_unique<Character::StateHandler>(                                 \
        [this]() { (enter)(); },                                               \
        [this]() { (exit)(); },                                                \
        [this](double dt) { (step)(dt); })

#define create_character_state(state)                                          \
    create_character_state_imp(                                                \
        NIU2X_PP_CAT(state, _enter),                                           \
        NIU2X_PP_CAT(state, _exit),                                            \
        NIU2X_PP_CAT(state, _step))

class Character : private Noncopyable {
public:
    class StateHandler : public sm::State {
    public:
        using ENTER_EXIT_HANDLER = std::function<void()>;
        using STEP_HANDLER = std::function<void(double dt)>;

        StateHandler(
            ENTER_EXIT_HANDLER enter_handler,
            ENTER_EXIT_HANDLER exit_handler,
            STEP_HANDLER step_handler)
        : enter_handler_(std::move(enter_handler))
        , exit_handler_(std::move(exit_handler))
        , step_handler_(std::move(step_handler))
        {
        }
        ~StateHandler() { }
        virtual void enter() { }
        virtual void exit() { }
        virtual void step(double dt) { }

    private:
        ENTER_EXIT_HANDLER enter_handler_;
        ENTER_EXIT_HANDLER exit_handler_;
        STEP_HANDLER step_handler_;
    };

    Character(SceneManager* scn_mgr, const String& mesh);
    virtual ~Character();
    void set_scale(double scale);
    // void play_animation(const String& name);

    void step(double delta);

    const Entity* entity() const { return ent_; }
    const SceneNode* node() const { return node_; }

    void walk_to(const Vector3& target);

    virtual void idle_enter() { }
    virtual void idle_exit() { }
    virtual void idle_step(double) { }

    virtual void run_enter() { }
    virtual void run_exit() { }
    virtual void run_step(double) { }

private:
    SceneNode* node_ = nullptr;
    Entity* ent_ = nullptr;
    SceneManager* scn_mgr_ = nullptr;
    HashMap<String, AnimationState*> anim_states_;
    Vector3 walk_target_;
    double base_speed_ = 1;
    double speed_ = 5;
    sm::StateMachine state_machine_;
};

#endif
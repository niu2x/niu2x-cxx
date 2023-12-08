#include "character.h"

Character::Character(SceneManager* scn_mgr, const String& mesh)
: scn_mgr_(scn_mgr)
{
    ent_ = scn_mgr_->createEntity(mesh);
    node_ = scn_mgr_->getRootSceneNode()->createChildSceneNode();
    node_->attachObject(ent_);

    anim_states_["run"]
        = ent_->getAnimationState("tryndamere_run.anm_skinned_mesh");

    anim_states_["idle1"]
        = ent_->getAnimationState("tryndamere_idle1.anm_skinned_mesh");

    anim_states_["spell3"]
        = ent_->getAnimationState("tryndamere_spell3.anm_skinned_mesh");

    state_machine_.set_init_state(create_character_state(idle));
}

Character::~Character()
{
    node_->detachObject(ent_);
    scn_mgr_->destroyEntity(ent_);
    node_->getParent()->removeChild(node_);
    scn_mgr_->destroySceneNode(node_);
}

void Character::set_scale(double scale)
{
    node_->setScale(Ogre::Vector3(scale, scale, scale));
}

void Character::casting_skill()
{
    state_machine_.change_state(create_character_state(casting_skill));
}

void Character::casting_skill_enter()
{
    anim_states_["spell3"]->setEnabled(true);
    skill_duration_ = 0.1;
}

void Character::casting_skill_exit()
{
    anim_states_["spell3"]->setEnabled(false);
}

void Character::casting_skill_step(double dt)
{
    anim_states_["spell3"]->addTime(dt);
    skill_duration_ -= dt;
    if (skill_duration_ <= 0)
        state_machine_.change_state(create_character_state(idle));
}

// void Character::play_animation(const String& name)
// {

// }

void Character::step(double delta) { state_machine_.step(delta); }

void Character::walk_to(const Vector3& target)
{
    walk_target_ = target;
    state_machine_.change_state(create_character_state(run));
}

void Character::run_enter() { anim_states_["run"]->setEnabled(true); }

void Character::run_exit() { anim_states_["run"]->setEnabled(false); }

void Character::run_step(double dt)
{
    anim_states_["run"]->addTime(dt * speed_ / base_speed_);
    auto distance = walk_target_ - node_->_getDerivedPosition();
    if (distance.length() > 0.1) {
        auto direction = distance;
        direction.normalise();
        auto move = std::min((float)(speed_ * dt), distance.length());
        node_->translate(direction * move, Ogre::Node::TS_WORLD);
        node_->setDirection(-direction);

    } else {
        state_machine_.change_state(create_character_state(idle));
    }
}

void Character::idle_enter() { anim_states_["idle1"]->setEnabled(true); }

void Character::idle_exit() { anim_states_["idle1"]->setEnabled(false); }

void Character::idle_step(double dt) { anim_states_["idle1"]->addTime(dt); }

#include "character.h"

Character::Character(SceneManager* scn_mgr, const String& mesh)
: scn_mgr_(scn_mgr)
{
    ent_ = scn_mgr_->createEntity(mesh);
    node_ = scn_mgr_->getRootSceneNode()->createChildSceneNode();
    node_->attachObject(ent_);
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

void Character::play_animation(const String& name)
{
    anim_state_ = ent_->getAnimationState(name);
    anim_state_->setEnabled(true);
}

void Character::step(double delta)
{
    if (anim_state_)
        anim_state_->addTime(delta);

    auto distance = walk_target_ - node_->_getDerivedPosition();

    if (distance.length() > 10) {
        auto direction = distance;
        direction.normalise();

        auto move = std::min((float)(speed_ * delta), distance.length());
        node_->translate(direction * move, Ogre::Node::TS_WORLD);
        node_->setDirection(-direction);
    } else {
        if (anim_state_)
            anim_state_->setEnabled(false);
        anim_state_ = nullptr;
    }
}

void Character::walk_to(const Vector3& target)
{
    walk_target_ = target;
    play_animation("tryndamere_run.anm_skinned_mesh");
}

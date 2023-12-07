#ifndef CHARACTER_H
#define CHARACTER_H

#include <Ogre.h>
#include <OgreInput.h>
#include <OgreRTShaderSystem.h>
#include <niu2x/type.h>

using String = niu2x::String;
using Noncopyable = niu2x::Noncopyable;

class Character : private Noncopyable {
public:
    using SceneManager = Ogre::SceneManager;
    using Entity = Ogre::Entity;
    using AnimationState = Ogre::AnimationState;
    using SceneNode = Ogre::SceneNode;

    Character(SceneManager* scn_mgr, const String& mesh);
    virtual ~Character();
    void set_scale(double scale);
    void play_animation(const String& name);

    void step(double delta);

private:
    SceneNode* node_ = nullptr;
    Entity* ent_ = nullptr;
    SceneManager* scn_mgr_ = nullptr;
    AnimationState* anim_state_ = nullptr;
};

#endif
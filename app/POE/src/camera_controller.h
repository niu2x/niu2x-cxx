#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "ogre_alias.h"
#include <niu2x/type.h>
using Noncopyable = niu2x::Noncopyable;

class CameraController : private Noncopyable, public Ogre::FrameListener {
public:
    CameraController(Ogre::Root* root, SceneNode* camera_node);
    ~CameraController();
    void step();

    bool frameRenderingQueued(const FrameEvent& evt) override;
    void set_auto_tracking(const SceneNode* node);
    void set_tracking_offset(const Vector3& off) { tracking_offset_ = off; }

private:
    SceneNode* camera_;
    Ogre::Root* root_;
    const SceneNode* tracking_target_ = nullptr;
    Vector3 tracking_offset_ = Vector3(4, 4, 4);
};

#endif
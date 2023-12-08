#include "camera_controller.h"

CameraController::CameraController(Ogre::Root* root, SceneNode* camera_node)
: camera_(camera_node)
, root_(root)
{
    root_->addFrameListener(this);
}

CameraController::~CameraController() { root_->removeFrameListener(this); }

void CameraController::set_auto_tracking(const SceneNode* node)
{
    tracking_target_ = node;
}

bool CameraController::frameRenderingQueued(const FrameEvent& evt)
{
    if (tracking_target_) {
        auto pos = tracking_target_->_getDerivedPosition();
        camera_->setPosition(pos + tracking_offset_);
        camera_->lookAt(pos, Ogre::Node::TS_WORLD);
    }
    return true;
}

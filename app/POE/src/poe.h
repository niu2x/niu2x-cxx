#ifndef POE_H
#define POE_H

#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreRTShaderSystem.h>
#include <OgreTrays.h>
#include <niu2x/type.h>
#include <niu2x/fs.h>
#include "character.h"

template <class T>
using UPtr = niu2x::UPtr<T>;

class POE : public OgreBites::ApplicationContext,
            public OgreBites::InputListener,
            public OgreBites::TrayListener {
public:
    using SceneManager = Ogre::SceneManager;
    using SceneNode = Ogre::SceneNode;
    using FrameEvent = Ogre::FrameEvent;
    using Camera = Ogre::Camera;

    POE();
    virtual ~POE() { }

    virtual void setup() override;
    virtual void shutdown() override;

    virtual bool frameRenderingQueued(const FrameEvent& evt) override;
    bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
    bool mouseWheelRolled(const OgreBites::MouseWheelEvent& evt) override;

    bool mouseMoved(const OgreBites::MouseMotionEvent& evt) override;
    bool mousePressed(const OgreBites::MouseButtonEvent& evt) override;
    bool mouseReleased(const OgreBites::MouseButtonEvent& evt) override;

    void create_ground();
    void create_camera();
    void create_light();
    void buttonHit(OgreBites::Button* button) override;

private:
    std::unique_ptr<OgreBites::TrayManager> tray_mgr_;
    SceneManager* scn_mgr_ = nullptr;
    SceneNode* cam_node_ = nullptr;
    bool mouse_mid_btn_pressed_ = false;
    UPtr<Character> character_ = nullptr;
    Camera* camera_ = nullptr;
};

#endif
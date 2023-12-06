#include <iostream>
#include <memory>

#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreRTShaderSystem.h>
#include <OgreTrays.h>

#include <niu2x/app.h>
#include <niu2x/fs.h>

class POE : public OgreBites::ApplicationContext,
            public OgreBites::InputListener,
            public OgreBites::TrayListener {
public:
    POE();
    virtual ~POE() { }

    virtual void setup() override;
    virtual void shutdown() override;

    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt) override;
    bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
    bool mouseWheelRolled(const OgreBites::MouseWheelEvent& evt) override;

    bool mouseMoved(const OgreBites::MouseMotionEvent& evt) override;
    bool mousePressed(const OgreBites::MouseButtonEvent& evt) override;
    bool mouseReleased(const OgreBites::MouseButtonEvent& evt) override;

    void create_ground();
    void create_camera();
    void create_light();
    void create_coord_system();

    void buttonHit(OgreBites::Button* button) override;

private:
    std::unique_ptr<OgreBites::TrayManager> tray_mgr_;
    Ogre::SceneManager* scn_mgr_ = nullptr;
    Ogre::AnimationState* animation_state_ = nullptr;
    Ogre::SceneNode* cam_node_ = nullptr;
    bool mouse_mid_btn_pressed_ = false;
    Ogre::Entity* character_ = nullptr;
};

POE::POE()
: OgreBites::ApplicationContext("POE")
{
}

void POE::create_camera()
{
    cam_node_ = scn_mgr_->getRootSceneNode()->createChildSceneNode();
    auto* cam = scn_mgr_->createCamera("my_camera");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    cam_node_->attachObject(cam);
    cam_node_->setPosition(200, 200, 200);
    cam_node_->lookAt(
        Ogre::Vector3(0, 0, 0),
        Ogre::Node::TransformSpace::TS_WORLD);
    getRenderWindow()->addViewport(cam);
}

void POE::buttonHit(OgreBites::Button* button)
{

    if (animation_state_)
        animation_state_->setEnabled(false);

    animation_state_ = character_->getAnimationState(button->getName());
    animation_state_->setEnabled(true);
}

void POE::shutdown()
{
    tray_mgr_.reset();
    OgreBites::ApplicationContext::shutdown();
}

bool POE::mouseMoved(const OgreBites::MouseMotionEvent& evt) { return true; }
bool POE::mousePressed(const OgreBites::MouseButtonEvent& evt)
{
    if (evt.button == 2)
        mouse_mid_btn_pressed_ = true;
    return true;
}
bool POE::mouseReleased(const OgreBites::MouseButtonEvent& evt)
{
    if (evt.button == 2)
        mouse_mid_btn_pressed_ = false;
    return true;
}

void POE::setup()
{
    // do not forget to call the base first
    OgreBites::ApplicationContext::setup();

    auto* root = getRoot();
    scn_mgr_ = root->createSceneManager();

    // register our scene with the RTSS
    auto* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scn_mgr_);

    // scn_mgr_->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    scn_mgr_->setShadowTechnique(
        Ogre::ShadowTechnique::SHADOWTYPE_TEXTURE_MODULATIVE);

    scn_mgr_->addRenderQueueListener(getOverlaySystem());

    tray_mgr_ = std::make_unique<OgreBites::TrayManager>(
        "InterfaceName",
        getRenderWindow());
    addInputListener(tray_mgr_.get());
    addInputListener(this);
    tray_mgr_->showAll();
    tray_mgr_->setListener(this);

    create_camera();
    create_light();
    create_ground();
}
void POE::create_light()
{
    auto light = scn_mgr_->createLight("light0");
    light->setDiffuseColour(Ogre::ColourValue(1000, 1000, 1000));
    // light->setSpecularColour(Ogre::ColourValue(5000, 5000, 5000));
    light->setType(Ogre::Light::LT_POINT);
    auto node = scn_mgr_->getRootSceneNode()->createChildSceneNode();
    node->attachObject(light);
    node->setPosition(-300, 500, -300);
}

void POE::create_coord_system()
{
    auto coord_system = scn_mgr_->getRootSceneNode()->createChildSceneNode();

    auto manual_obj = scn_mgr_->createManualObject("coord_axis");
    manual_obj->begin(
        "BaseWhiteNoLighting",
        Ogre::RenderOperation::OT_LINE_LIST);
    manual_obj->position(Ogre::Vector3(0, 0, 0));
    manual_obj->position(Ogre::Vector3(1000, 0, 0));

    manual_obj->position(Ogre::Vector3(0, 0, 0));
    manual_obj->position(Ogre::Vector3(0, 1000, 0));

    manual_obj->position(Ogre::Vector3(0, 0, 0));
    manual_obj->position(Ogre::Vector3(0, 0, 1000));
    manual_obj->end();

    coord_system->createChildSceneNode()->attachObject(manual_obj);
}

void POE::create_ground()
{
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane(
        "ground",
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane,
        1500,
        1500,
        100,
        100,
        true,
        1,
        5,
        5,
        Ogre::Vector3::UNIT_Z);

    Ogre::Entity* groundEntity
        = scn_mgr_->createEntity("GroundEntity", "ground");
    scn_mgr_->getRootSceneNode()->createChildSceneNode()->attachObject(
        groundEntity);
    groundEntity->setCastShadows(false);
    groundEntity->setMaterialName("Examples/Rockwall");
}

bool POE::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    tray_mgr_->frameRendered(evt);
    if (animation_state_)
        animation_state_->addTime(evt.timeSinceLastFrame);

    return OgreBites::ApplicationContext::frameRenderingQueued(evt);
}

bool POE::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == OgreBites::SDLK_ESCAPE) {
        getRoot()->queueEndRendering();
    }

    return true;
}

bool POE::mouseWheelRolled(const OgreBites::MouseWheelEvent& evt)
{
    return true;
}

int main(int argc, const char** argv)
{
    // using ArgParser = niu2x::app::ArgParser;
    // ArgParser arg_parser("POE", "niu2x's POE");
    try {
        POE app;
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();
    } catch (const std::exception& e) {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;
}

//! [fullsource]

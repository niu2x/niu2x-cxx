#include "poe.h"

POE::POE()
: OgreBites::ApplicationContext("POE")
{
}

void POE::create_camera()
{
    cam_node_ = scn_mgr_->getRootSceneNode()->createChildSceneNode();
    camera_ = scn_mgr_->createCamera("my_camera");
    camera_->setNearClipDistance(1); // specific to this sample
    camera_->setAutoAspectRatio(true);
    // cam->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
    // cam->setOrthoWindow();
    cam_node_->attachObject(camera_);
    cam_node_->setPosition(500, 500, 500);
    cam_node_->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
    getRenderWindow()->addViewport(camera_);
}

void POE::buttonHit(OgreBites::Button* button) { }

void POE::shutdown()
{
    character_.reset();
    tray_mgr_.reset();
    OgreBites::ApplicationContext::shutdown();
}

bool POE::mouseMoved(const OgreBites::MouseMotionEvent& evt) { return true; }

bool POE::mousePressed(const OgreBites::MouseButtonEvent& evt)
{

    float width = getRenderWindow()->getWidth();
    float height = getRenderWindow()->getHeight();

    Ogre::Ray mouseRay
        = camera_->getCameraToViewportRay(evt.x / width, evt.y / height);
    Ogre::RaySceneQuery* raySceneQuery = scn_mgr_->createRayQuery(Ogre::Ray());

    raySceneQuery->setRay(mouseRay);
    raySceneQuery->setSortByDistance(true);

    Ogre::RaySceneQueryResult& result = raySceneQuery->execute();
    Ogre::RaySceneQueryResult::iterator itr;

    auto ground = scn_mgr_->getEntity("GroundEntity");

    for (itr = result.begin(); itr != result.end(); itr++) {
        if (itr->movable == ground) {
            Ogre::Vector3 hitPoint = mouseRay.getPoint(itr->distance);
            character_->walk_to(hitPoint);
            break;
        }
    }

    scn_mgr_->destroyQuery(raySceneQuery);
    return true;
}
bool POE::mouseReleased(const OgreBites::MouseButtonEvent& evt)
{




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

    scn_mgr_->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
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

    character_ = std::make_unique<Character>(scn_mgr_, "tryndamere.mesh");
    // character_->play_animation("tryndamere_spell3.anm_skinned_mesh");

    scn_mgr_->setShadowTextureSize(512);
    scn_mgr_->setShadowFarDistance(5000);
}
void POE::create_light()
{
    auto light = scn_mgr_->createLight("light0");
    light->setDiffuseColour(Ogre::ColourValue(2, 2, 2));
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    auto node = scn_mgr_->getRootSceneNode()->createChildSceneNode();
    node->attachObject(light);
    node->setDirection(1, -1, 1);
}

void POE::create_ground()
{
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane(
        "ground",
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane,
        10000,
        10000,
        10,
        10,
        true,
        1,
        50,
        50,
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
    character_->step(evt.timeSinceLastFrame);
    tray_mgr_->frameRendered(evt);
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
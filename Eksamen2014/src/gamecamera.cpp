#include "gamecamera.h"

GameCamera::GameCamera(Ogre::Camera *setCam, Ogre::SceneManager* mgr)
{
    mForward = false;
    mBack = false;
    mLeft = false;
    mRight = false;
    mUp = false;
    mDown = false;

    name = "GameCamera";

    horizontalSens = 5;
    verticalSens = 7;

    sceneMgr = mgr;
    camera = setCam;

    camMode = 0;

    camNode = sceneMgr->getRootSceneNode()->createChildSceneNode(name);
    targetNode = sceneMgr->getRootSceneNode()->createChildSceneNode(name+"_target");
    camNode->setAutoTracking(true, targetNode);
    camNode->setFixedYawAxis(true);

    debugNode = sceneMgr->getRootSceneNode()->createChildSceneNode(name+"_debug");
    yawNode = debugNode->createChildSceneNode("yawNode");
    pitchNode = yawNode->createChildSceneNode("pitchNode");
    debugNode->setPosition(0,500,0);
    pitchNode->pitch(Ogre::Degree(-40));

    camera = sceneMgr->createCamera(name);

    camNode->attachObject(camera);
    camera->setNearClipDistance(.1f);
    tightness = 0.05f;
}

GameCamera::~GameCamera()
{
    camNode->removeAndDestroyAllChildren();
    sceneMgr->destroySceneNode(camNode);
    sceneMgr->destroySceneNode(name+"_debug");
}

void GameCamera::attachCamera()
{
    camera->detachFromParent();

    if (camMode == 0 || camMode == 1)
        camNode->attachObject(camera);
    else
        pitchNode->attachObject(camera);
}

void GameCamera::keyPress(const OIS::KeyEvent &arg)
{
    if (arg.key == OIS::KC_W)
        mForward = true;
    if (arg.key == OIS::KC_S)
        mBack = true;
    if (arg.key == OIS::KC_A)
        mLeft = true;
    if (arg.key == OIS::KC_D)
        mRight = true;
    if (arg.key == OIS::KC_PGUP)
        mUp = true;
    if (arg.key == OIS::KC_PGDOWN)
        mDown = true;
}

void GameCamera::keyRelease(const OIS::KeyEvent &arg)
{
    if (arg.key == OIS::KC_W)
        mForward = false;
    if (arg.key == OIS::KC_S)
        mBack = false;
    if (arg.key == OIS::KC_A)
        mLeft = false;
    if (arg.key == OIS::KC_D)
        mRight = false;
    if (arg.key == OIS::KC_PGUP)
        mUp = false;
    if (arg.key == OIS::KC_PGDOWN)
        mDown = false;
}

void GameCamera::mouseMoved(const OIS::MouseEvent &e, Ogre::Real elapsedTime)
{
    if (camMode == 2)
    {
        yawNode->yaw(Ogre::Degree(-horizontalSens * elapsedTime * e.state.X.rel));
        pitchNode->pitch(Ogre::Degree(-verticalSens * elapsedTime * e.state.Y.rel));
    }
}

void GameCamera::instantUpdate(Ogre::Vector3 cameraPosition, Ogre::Vector3 targetPosition)
{
    camNode->setPosition(cameraPosition);
    targetNode->setPosition(targetPosition);
}

void GameCamera::update(Ogre::Real elapsedTime, Ogre::Vector3 cameraPosition, Ogre::Vector3 targetPosition)
{
    camNode->setAutoTracking(true, targetNode);
    Ogre::Vector3 displacement;

    displacement = (cameraPosition - camNode->getPosition())*tightness;
    camNode->translate(displacement);

    displacement = (targetPosition - targetNode->getPosition())*tightness;
    targetNode->translate(displacement);

    if (camMode == 2)
        debugUpdate(elapsedTime);
}

void GameCamera::debugUpdate(Ogre::Real elapsedTime)
{
    attachCamera();
    debugNode->setAutoTracking(false);

    if (mForward)
        debugNode->translate(yawNode->getOrientation()*Ogre::Vector3(0,0,elapsedTime*-100));
    if (mBack)
        debugNode->translate(yawNode->getOrientation()*Ogre::Vector3(0,0,elapsedTime*100));
    if (mLeft)
        debugNode->translate(yawNode->getOrientation()*Ogre::Vector3(elapsedTime*-100,0,0));
    if (mRight)
        debugNode->translate(yawNode->getOrientation()*Ogre::Vector3(elapsedTime*100,0,0));

    if (mUp)
        debugNode->translate(debugNode->getOrientation()*Ogre::Vector3(0,elapsedTime*80,0));
    if (mDown)
        debugNode->translate(debugNode->getOrientation()*Ogre::Vector3(0,elapsedTime*-80,0));
}

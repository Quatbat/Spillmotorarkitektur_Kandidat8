#include "player.h"

Player::Player(Ogre::String giveName, Ogre::SceneManager *mgr)
{
    name = giveName;
    sceneMgr = mgr;

    entity = sceneMgr->createEntity(name, "penguin.mesh");
    entity->setCastShadows(true);
    mainNode = sceneMgr->getRootSceneNode()->createChildSceneNode(name, Ogre::Vector3(-40.0f, 5.0f, 0.0f));
    mainNode->attachObject(entity);
    mainNode->scale(.2f,.2f,.2f);
    mainNode->yaw(Ogre::Degree(90));

    animState = entity->getAnimationState("amuse");
    animState->setLoop(true);
    animState->setEnabled(true);
}

void Player::keyPress(const OIS::KeyEvent &arg)
{

}

void Player::keyRelease(const OIS::KeyEvent &arg)
{

}

void Player::update(const Ogre::FrameEvent &evt)
{

}

void Player::render(const Ogre::FrameEvent &evt)
{
    animState->addTime(evt.timeSinceLastFrame);
}

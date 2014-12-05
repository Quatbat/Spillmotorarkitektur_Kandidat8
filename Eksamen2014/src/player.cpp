#include "player.h"
#include "playerstatus.h"

Player::Player(Ogre::String giveName, Ogre::SceneManager *mgr)
{
    moveSpeed = 30;
    numHealth = 3;
    numPickups = 0;

    mForward = false;
    mBack = false;
    mLeft = false;
    mRight = false;

    lost = false;
    won = false;

    name = giveName;
    sceneMgr = mgr;

    //creating scenenode and entity
    entity = sceneMgr->createEntity(name, "penguin.mesh");
    entity->setCastShadows(true);
    mainNode = sceneMgr->getRootSceneNode()->createChildSceneNode(name, Ogre::Vector3(-40.0f, 5.0f, 0.0f));
    mainNode->attachObject(entity);
    mainNode->scale(.2f,.2f,.2f);
    mainNode->yaw(Ogre::Degree(90));
    animState = entity->getAnimationState("amuse");
    animState->setLoop(true);
    animState->setEnabled(true);

    //node for camera
    sightNode = mainNode->createChildSceneNode(name+"_sight", Ogre::Vector3(100,0,0));//(0,0,100));
    camNode = mainNode->createChildSceneNode(name+"_camera", Ogre::Vector3(-500,300,0));//(0,50,-100));

    //legger til health-klasse
    health = new PlayerStatus;

    health->healthEnt = sceneMgr->createEntity(name+"_health", "knot.mesh");
    health->healthNode = mainNode->createChildSceneNode("health", Ogre::Vector3(0,50,0));
    health->healthNode->attachObject(health->healthEnt);
    health->healthNode->scale(numHealth*.2f,numHealth*.2f,numHealth*.2f);
}

Player::~Player()
{
    delete health;
}

void Player::keyPress(const OIS::KeyEvent &arg)
{
    if (arg.key == OIS::KC_UP) mForward = true;
    if (arg.key == OIS::KC_DOWN) mBack = true;
    if (arg.key == OIS::KC_LEFT) mLeft = true;
    if (arg.key == OIS::KC_RIGHT) mRight = true;
}

void Player::keyRelease(const OIS::KeyEvent &arg)
{
    if (arg.key == OIS::KC_UP) mForward = false;
    if (arg.key == OIS::KC_DOWN) mBack = false;
    if (arg.key == OIS::KC_LEFT) mLeft = false;
    if (arg.key == OIS::KC_RIGHT) mRight = false;
}

void Player::update(const Ogre::FrameEvent &evt)
{
    Ogre::Real dTime = evt.timeSinceLastFrame;
    if (!lost)
    {
        if (mForward)
            mainNode->translate(Ogre::Vector3(0,0,-moveSpeed * dTime));
        if (mBack)
            mainNode->translate(Ogre::Vector3(0,0,moveSpeed * dTime));
        if (mLeft)
            mainNode->translate(Ogre::Vector3(-moveSpeed * dTime,0,0));
        if (mRight)
            mainNode->translate(Ogre::Vector3(moveSpeed * dTime,0,0));

        if (mainNode->getPosition().z < -25)
            mainNode->translate(0.0, -2.0 * moveSpeed * dTime, 0.0);
        if (mainNode->getPosition().z > 25)
            mainNode->translate(0.0, -2.0 * moveSpeed * dTime, 0.0);
        if (mainNode->getPosition().y < -30)
            mainNode->setPosition(Ogre::Vector3(-40.0f, 5.0f, 0.0f));
    }

    if(entity->getWorldBoundingBox().intersects
            (sceneMgr->getEntity("PickupEntity1")->getWorldBoundingBox()))
    {
        if (sceneMgr->getEntity("PickupEntity1")->isVisible())
        {
            sceneMgr->getEntity("PickupEntity1")->setVisible(false);
            numPickups ++;
        }
    }
    if(entity->getWorldBoundingBox().intersects
            (sceneMgr->getEntity("PickupEntity2")->getWorldBoundingBox()))
    {
        if (sceneMgr->getEntity("PickupEntity2")->isVisible())
        {
            sceneMgr->getEntity("PickupEntity2")->setVisible(false);
            numPickups ++;
        }
    }
    if(entity->getWorldBoundingBox().intersects
            (sceneMgr->getEntity("PickupEntity3")->getWorldBoundingBox()))
    {
        if (sceneMgr->getEntity("PickupEntity3")->isVisible())
        {
            sceneMgr->getEntity("PickupEntity3")->setVisible(false);
            numPickups ++;
        }
    }
    if(entity->getWorldBoundingBox().intersects
            (sceneMgr->getEntity("PickupEntity4")->getWorldBoundingBox()))
    {
        if (sceneMgr->getEntity("PickupEntity4")->isVisible())
        {
            sceneMgr->getEntity("PickupEntity4")->setVisible(false);
            numPickups ++;
        }
    }

    if(entity->getWorldBoundingBox().intersects
            (sceneMgr->getEntity("Goal")->getWorldBoundingBox()))
    {
        if (numPickups == 4 && !won)
        {
            mForward = false;
            mBack = false;
            mLeft = false;
            mRight = false;
            numPickups = 10; //no reset

            Ogre::ParticleSystem* fireworks = sceneMgr->createParticleSystem("Fireworks", "Examples/Fireworks");
            mainNode->attachObject(fireworks);
            won = true;
        }
    }

    if(entity->getWorldBoundingBox().intersects
            (sceneMgr->getEntity("shrek")->getWorldBoundingBox()))
    {
        recieveDamage(1);
        mainNode->setPosition(Ogre::Vector3(-40.0f, 5.0f, 0.0f));
    }
}

void Player::render(const Ogre::FrameEvent &evt)
{
    animState->addTime(evt.timeSinceLastFrame);
}

void Player::recieveDamage(int damage)
{

    numHealth -= damage;
    health->healthNode->scale(numHealth*.2f,numHealth*.2f,numHealth*.2f);

    if (numHealth < 0)
        died();
}

void Player::died()
{
    std::cout << "\nUFFDA";
    lost = true;
}

#include "EksamensApp.h"

//-------------------------------------------------------------------------------------
EksamensApp::EksamensApp(void)
{
    forward = false;
    backwards = false;
    left = false;
    right = false;
    mPickups = 0;
}
//-------------------------------------------------------------------------------------
EksamensApp::~EksamensApp(void)
{
}

//-------------------------------------------------------------------------------------
void EksamensApp::createScene(void)
{
    // creating the scene here.

	// Set the scene's ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.4f, 0.4f, 0.4f));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_ADDITIVE);

    //Skybox
    mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox", 500, false);
 
    // Create the player
    Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "penguin.mesh");
    ogreHead->setCastShadows(true);
    // Create a SceneNode and attach the Entity to it
    playerNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode", Ogre::Vector3(-40.0f, 5.0f, 0.0f));
    playerNode->attachObject(ogreHead);
    playerNode->scale(0.2f, 0.2f, 0.2f);
    playerNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(90));
    // Set walking animation
    mAnimationState = ogreHead->getAnimationState("amuse");
    mAnimationState->setLoop(true);
    mAnimationState->setEnabled(true);


    // Create the enemy
    Ogre::Entity* mEntEnemy = mSceneMgr->createEntity("Enemy", "ogrehead.mesh");
    mEnemyNode = mSceneMgr->getRootSceneNode()->
            createChildSceneNode("RobotNode", Ogre::Vector3(0.0f, 2.0f, 0.0f));
    mEnemyNode->attachObject(mEntEnemy);
    mEnemyNode->scale(0.1f, 0.1f, 0.1f);

    // Create the goal
    Ogre::Entity* mEntGoal = mSceneMgr->createEntity("Goal", "athene.mesh");
    mGoalNode = mSceneMgr->getRootSceneNode()->
            createChildSceneNode("GoalNode", Ogre::Vector3(50.0f, 8.0f, 0.0f));
    mGoalNode->attachObject(mEntGoal);
    mGoalNode->scale(0.1f, 0.1f, 0.1f);
    mGoalNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(-90));
 
    // Create a Light and set its position
    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(2.0f, 25.0f, 22.0f);


    //Create floor
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                                  plane, 300, 50, 10, 5, true, 1, 8, 1, Ogre::Vector3::UNIT_Z);

    Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
    Ogre::SceneNode* groundNode =mSceneMgr->getRootSceneNode()->createChildSceneNode("GroundNode");
    groundNode->attachObject(entGround);
    entGround->setMaterialName("Examples/Rockwall");
    entGround->setCastShadows(false);
    groundNode->setPosition(0.0, -0.0, 0.0);

    // Create the enemy walking list
    mWalkList.push_back(Ogre::Vector3(18.0f,   2.0f,  18.0f ));
    mWalkList.push_back(Ogre::Vector3(9.0f,   2.0f,  9.0f ));
    mWalkList.push_back(Ogre::Vector3(-18.0f,  2.0f, 18.0f));
    mWalkList.push_back(Ogre::Vector3(-9.0f,   2.0f,  9.0f ));
    mWalkList.push_back(Ogre::Vector3(0.0f,  2.0f, 0.0f));
    mWalkList.push_back(Ogre::Vector3(18.0f,  2.0f, -18.0f));
    mWalkList.push_back(Ogre::Vector3(9.0f,   2.0f,  -9.0f ));
    mWalkList.push_back(Ogre::Vector3(-18.0f,  2.0f, -18.0f));
    mWalkList.push_back(Ogre::Vector3(-9.0f,   2.0f,  -9.0f ));
    mListIterator = 0;

    // Create pickups:
    Ogre::Entity* entPickup = mSceneMgr->createEntity("PickupEntity1", "Barrel.mesh");
    mPickupNode1 = mSceneMgr->getRootSceneNode()->
            createChildSceneNode("PickupNode1", Ogre::Vector3(20.0f, 3.0f, 20.0f));
    mPickupNode1->attachObject(entPickup);
    mPickupNode1->scale(0.9f, 0.9f, 0.9f);

    entPickup = mSceneMgr->createEntity("PickupEntity2", "Barrel.mesh");
    mPickupNode2 = mSceneMgr->getRootSceneNode()->
            createChildSceneNode("PickupNode2", Ogre::Vector3(-20.0f, 3.0f, 20.0f));
    mPickupNode2->attachObject(entPickup);
    mPickupNode2->scale(0.9f, 0.9f, 0.9f);

    entPickup = mSceneMgr->createEntity("PickupEntity3", "Barrel.mesh");
    mPickupNode3 = mSceneMgr->getRootSceneNode()->
            createChildSceneNode("PickupNode3", Ogre::Vector3(20.0f, 3.0f, -20.0f));
    mPickupNode3->attachObject(entPickup);
    mPickupNode3->scale(0.9f, 0.9f, 0.9f);

    entPickup = mSceneMgr->createEntity("PickupEntity4", "Barrel.mesh");
    mPickupNode4 = mSceneMgr->getRootSceneNode()->
            createChildSceneNode("PickupNode4", Ogre::Vector3(-20.0f, 3.0f, -20.0f));
    mPickupNode4->attachObject(entPickup);
    mPickupNode4->scale(0.9f, 0.9f, 0.9f);

}

bool EksamensApp::nextLocation(){
    if (mWalkList.empty()) return false;
    mDestination = mWalkList[mListIterator];  // this gets a position from the list
    mDirection = mDestination - mEnemyNode->getPosition();
    mDistance = mDirection.normalise();
    mListIterator = rand()% mWalkList.size();

    return true;
}

bool EksamensApp::keyPressed(const OIS::KeyEvent &arg)
{
    switch (arg.key)
    {
    case OIS::KC_ESCAPE:
        mShutDown = true;
        break;

    case OIS::KC_UP:
        forward = true;
        break;

    case OIS::KC_DOWN:
        backwards = true;
        break;

    case OIS::KC_LEFT:
        left = true;
        break;

    case OIS::KC_RIGHT:
        right = true;
        break;
    case OIS::KC_RETURN:
        //reset penguin
        if (mEnemyWalkSpeed == 0 && mPickups != 10)
        {
            mEnemyWalkSpeed = 45;
            mPlayerWalkSpeed = 25;
            playerNode->setPosition(Ogre::Vector3(-40.0f, 5.0f, 0.0f));
            mSceneMgr->setAmbientLight(Ogre::ColourValue(0.4f, 0.4f, 0.4f));
        }
        break;
    default:
        OgreFramework::keyPressed(arg);
    }
    return true;
}

bool EksamensApp::keyReleased(const OIS::KeyEvent &arg)
{
    switch (arg.key)
    {
    case OIS::KC_UP:
        forward = false;
        break;

    case OIS::KC_DOWN:
        backwards = false;
        break;

    case OIS::KC_LEFT:
        left = false;
        break;

    case OIS::KC_RIGHT:
        right = false;
        break;
    default:
        OgreFramework::keyReleased(arg);
    }
    return true;
}

bool EksamensApp::mouseMoved(const OIS::MouseEvent &arg)
{
    return true;
}

void EksamensApp::createFrameListener(void){
    OgreFramework::createFrameListener();
    mEnemyWalkSpeed = 45.0f;
    mPlayerWalkSpeed = 20.0f;
    mDirection = Ogre::Vector3::ZERO;
}

void EksamensApp::createCamera(void)
{
    // create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");
    // set its position, direction
    mCamera->setPosition(Ogre::Vector3(0,20,60));
    mCamera->lookAt(Ogre::Vector3(0,6,0));
    // set the near clip distance
    mCamera->setNearClipDistance(5);

    // the rest is set up by default Sdk config
    mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

bool EksamensApp::frameRenderingQueued(const Ogre::FrameEvent &evt){

    //update player
    Ogre::Real playerMove = mPlayerWalkSpeed * evt.timeSinceLastFrame;
    mAnimationState->addTime(evt.timeSinceLastFrame);

    //update enemy
    if (mDirection == Ogre::Vector3::ZERO) {
        nextLocation();
    }else{
        Ogre::Real enemyMove = mEnemyWalkSpeed * evt.timeSinceLastFrame;
        mDistance -= enemyMove;
        if (mDistance <= 0.0f){
            mEnemyNode->setPosition(mDestination);
            mDirection = Ogre::Vector3::ZERO;
            if (nextLocation()){
                // Correct Rotation Code will go here later
                Ogre::Vector3 src = mEnemyNode->getOrientation() * Ogre::Vector3::UNIT_X;
                if ((1.0f + src.dotProduct(mDirection)) < 0.0001f) {
                    mEnemyNode->yaw(Ogre::Degree(180));
                }else{
                    Ogre::Quaternion quat = src.getRotationTo(mDirection);
                    mEnemyNode->rotate(quat);
                } // else
            }//if
        }else{
            mEnemyNode->translate(mDirection * enemyMove);
        } // else
    } // else


    //Move player
    if (forward)
        playerNode->translate(0.0, 0.0, -1.0 * playerMove);
    if (backwards)
        playerNode->translate(0.0, 0.0, 1.0 * playerMove);
    if (left)
        playerNode->translate(-1.0 * playerMove, 0.0, 0.0);
    if (right)
        playerNode->translate(1.0 * playerMove, 0.0, 0.0);

    //update camera
    mCamera->lookAt(playerNode->getPosition());


    //Collisions

    //fall down
    if (playerNode->getPosition().z < -25){
        playerNode->translate(0.0, -2.0 * playerMove, 0.0);
    }
    if (playerNode->getPosition().z > 25) {
        playerNode->translate(0.0, -2.0 * playerMove, 0.0);
    }
    if (playerNode->getPosition().y < -30) {
        //Could take damage or reset game or something here...
        playerNode->setPosition(Ogre::Vector3(-40.0f, 5.0f, 0.0f));
    }

    //Pickups
    if(mSceneMgr->getEntity("Head")->
            getWorldBoundingBox().intersects(mSceneMgr->getEntity("PickupEntity1")->getWorldBoundingBox()))
    {
        if (mSceneMgr->getEntity("PickupEntity1")->isVisible())
        {
            mSceneMgr->getEntity("PickupEntity1")->setVisible(false);
            mPickups ++;
        }
    }
    if(mSceneMgr->getEntity("Head")->
            getWorldBoundingBox().intersects(mSceneMgr->getEntity("PickupEntity2")->getWorldBoundingBox()))
    {
        if (mSceneMgr->getEntity("PickupEntity2")->isVisible())
        {
            mSceneMgr->getEntity("PickupEntity2")->setVisible(false);
            mPickups ++;
        }
    }
    if(mSceneMgr->getEntity("Head")->
            getWorldBoundingBox().intersects(mSceneMgr->getEntity("PickupEntity3")->getWorldBoundingBox()))
    {
        if (mSceneMgr->getEntity("PickupEntity3")->isVisible())
        {
            mSceneMgr->getEntity("PickupEntity3")->setVisible(false);
            mPickups ++;
        }
    }
    if(mSceneMgr->getEntity("Head")->
            getWorldBoundingBox().intersects(mSceneMgr->getEntity("PickupEntity4")->getWorldBoundingBox()))
    {
        if (mSceneMgr->getEntity("PickupEntity4")->isVisible())
        {
            mSceneMgr->getEntity("PickupEntity4")->setVisible(false);
            mPickups ++;
        }
    }

    //Goal
    if(mSceneMgr->getEntity("Head")->
            getWorldBoundingBox().intersects(mSceneMgr->getEntity("Goal")->getWorldBoundingBox()))
    {
        if (mPickups == 4 && mPlayerWalkSpeed != 0)
        {
            mPlayerWalkSpeed = 0;
            mEnemyWalkSpeed = 0;
            mPickups = 10; //no reset
        }
    }

    //Enemy
    if(mSceneMgr->getEntity("Head")->
            getWorldBoundingBox().intersects(mSceneMgr->getEntity("Enemy")->getWorldBoundingBox()))
    {
        //mSceneMgr->setAmbientLight(Ogre::ColourValue(0.9f, 0.1f, 0.1f));
        mPlayerWalkSpeed = 0;
        mEnemyWalkSpeed = 0;
    }

    return OgreFramework::frameRenderingQueued(evt);
}


/*
 *
 *Just the main function of the program
 *
 *
 */


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        EksamensApp app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

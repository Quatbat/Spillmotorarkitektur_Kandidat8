#ifndef GAMECAMERA_H
#define GAMECAMERA_H

#include "OgreFramework.h"

class GameCamera
{
public:
    GameCamera(Ogre::Camera* setCam, Ogre::SceneManager* mgr);
    ~GameCamera();

    void attachCamera ();

    void keyPress (const OIS::KeyEvent &arg);
    void keyRelease (const OIS::KeyEvent &arg);
    void mouseMoved(const OIS::MouseEvent &e, Ogre::Real elapsedTime);

    void setTightness (Ogre::Real tight) {tightness = tight;}
    void instantUpdate (Ogre::Vector3 cameraPosition, Ogre::Vector3 targetPosition);
    void update (Ogre::Real elapsedTime, Ogre::Vector3 cameraPosition, Ogre::Vector3 targetPosition);
    void debugUpdate(Ogre::Real elapsedTime);

    Ogre::SceneManager* sceneMgr;
    Ogre::String name;
    int camMode;

    Ogre::SceneNode* targetNode;
    Ogre::SceneNode* camNode;
    Ogre::SceneNode* debugNode;

    Ogre::SceneNode* yawNode;
    Ogre::SceneNode* pitchNode;
    Ogre::Camera* camera;

    Ogre::Real tightness;

private:
    float horizontalSens;
    float verticalSens;

    bool mForward;
    bool mBack;
    bool mLeft;
    bool mRight;
    bool mUp;
    bool mDown;
};

#endif // GAMECAMERA_H

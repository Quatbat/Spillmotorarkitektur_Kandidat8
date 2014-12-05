#ifndef PLAYER_H
#define PLAYER_H

#include "OgreFramework.h"
#include "enemy.h"

class PlayerStatus;

class Player
{
public:
    Player(Ogre::String giveName, Ogre::SceneManager *mgr);

    void keyPress (const OIS::KeyEvent &arg);
    void keyRelease (const OIS::KeyEvent &arg);

    void update(const Ogre::FrameEvent &evt);
    void render(const Ogre::FrameEvent &evt);

    void recieveDamage (int damage);
    void died();

    ///Returns players Camera SceneNode.
    Ogre::SceneNode* getCameraNode () {return camNode;}
    ///Returns players sightNode.
    Ogre::SceneNode* getSightNode () {return sightNode;}

    Ogre::String name;

    //Enemy* enemy;

    Ogre::SceneManager* sceneMgr;
    Ogre::SceneNode* mainNode;
    Ogre::Entity* entity;
    Ogre::AnimationState* animState;

    Ogre::SceneNode* healthNode;
    Ogre::Entity* healthEnt;

private:
    ///Node assigned to camera.
    Ogre::SceneNode* camNode;
    ///Players forward.
    Ogre::SceneNode* sightNode;
    ///First person node.
    Ogre::SceneNode* fpNode;

    int numPickups;
    int numHealth;
    float moveSpeed;

    bool mForward;
    bool mBack;
    bool mLeft;
    bool mRight;
};

#endif // PLAYER_H

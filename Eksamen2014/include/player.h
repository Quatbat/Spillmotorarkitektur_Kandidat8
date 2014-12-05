#ifndef PLAYER_H
#define PLAYER_H

#include "OgreFramework.h"
#include "enemy.h"

class Player
{
public:
    Player(Ogre::String giveName, Ogre::SceneManager *mgr);

    void keyPress (const OIS::KeyEvent &arg);
    void keyRelease (const OIS::KeyEvent &arg);

    void update(const Ogre::FrameEvent &evt);
    void render(const Ogre::FrameEvent &evt);

    Ogre::String name;
    int numPickups;
    float moveSpeed;

    //Enemy* enemy;

    Ogre::SceneManager* sceneMgr;
    Ogre::SceneNode* mainNode;
    Ogre::Entity* entity;
    Ogre::AnimationState* animState;
};

#endif // PLAYER_H

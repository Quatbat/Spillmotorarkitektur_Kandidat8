#ifndef ENEMY_H
#define ENEMY_H

#include "OgreFramework.h"
#include "player.h"

class Enemy
{
public:
    Enemy(Ogre::String setName, Ogre::SceneManager *mgr);

    void update(const Ogre::FrameEvent &evt);

    Ogre::String name;
    float viewDistance;

    Ogre::SceneManager* sceneMgr;
    Ogre::SceneNode* mainNode;
    Ogre::Entity* entity;
};

#endif // ENEMY_H

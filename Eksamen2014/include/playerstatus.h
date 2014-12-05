#ifndef PLAYERSTATUS_H
#define PLAYERSTATUS_H

#include "OgreFramework.h"

class PlayerStatus
{
public:
    PlayerStatus();

    int numHealth;

    Ogre::SceneNode* healthNode;
    Ogre::Entity* healthEnt;
};

#endif // PLAYERSTATUS_H

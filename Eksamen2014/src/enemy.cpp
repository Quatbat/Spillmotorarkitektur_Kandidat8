#include "enemy.h"

Enemy::Enemy(Ogre::String setName, Ogre::SceneManager* mgr)
{
    name = setName;
    sceneMgr = mgr;
}

void Enemy::update(const Ogre::FrameEvent &evt)
{

}

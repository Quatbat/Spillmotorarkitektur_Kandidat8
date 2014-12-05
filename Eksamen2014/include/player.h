#ifndef PLAYER_H
#define PLAYER_H

#include "OgreFramework.h"
#include "enemy.h"

class PlayerStatus;

class Player
{
public:
    Player(Ogre::String giveName, Ogre::SceneManager *mgr);
    ~Player();

    ///Funksjon som mottar keypress fra EksamensApp-klassen.
    void keyPress (const OIS::KeyEvent &arg);

    ///Funksjon som mottar keyreleases fra EksamensApp-klassen.
    void keyRelease (const OIS::KeyEvent &arg);

    ///Update-funksjon som kjøres hver frame fra frameRendereingQueued-funksjonen.
    void update(const Ogre::FrameEvent &evt);
    ///Kjøres også hver frame fra frameStarted().
    void render(const Ogre::FrameEvent &evt);

    ///Fikser skade-mottakelse.
    void recieveDamage (int damage);
    ///Game-over funksjon.
    void died();

    ///Returns players Camera SceneNode.
    Ogre::SceneNode* getCameraNode () {return camNode;}
    ///Returns players sightNode.
    Ogre::SceneNode* getSightNode () {return sightNode;}

    Ogre::String name;

    //Enemy* enemy;
    Ogre::SceneNode* mainNode;

    bool lost;
    bool won;

private:
    Ogre::SceneManager* sceneMgr;
    Ogre::Entity* entity;
    Ogre::AnimationState* animState;

    ///Node assigned to camera.
    Ogre::SceneNode* camNode;
    ///Players forward.
    Ogre::SceneNode* sightNode;
    ///First person node.
    Ogre::SceneNode* fpNode;

    PlayerStatus* health;

    int numPickups;
    int numHealth;
    float moveSpeed;

    bool mForward;
    bool mBack;
    bool mLeft;
    bool mRight;
};

#endif // PLAYER_H

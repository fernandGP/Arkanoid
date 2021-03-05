#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "GameObjects/Ball.h"
#include "GameObjects/Player.h"
#include "GameObjects/Background.h"
#include "GameObjects/BrickManager.h"
#include "cocos2d.h"

class MainScene : public cocos2d::Scene
{
private:
    bool _gameStarted;

    Background _bgr;
    Player _player;
    Ball _ball;
    BrickManager _brickManager;

    cocos2d::EventListenerPhysicsContact* _contactListener; 
    cocos2d::EventListenerMouse*            _mouseListener;        // Desktop implementation
    //cocos2d::EventListenerKeyboard*         _keyListener;        // Desktop implementation

public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    void gameWon();
    void gameReset();
    void gameLaunch();
    void tick(float dt);

    void menuCloseCallback(cocos2d::Ref* pSender);

    // Mobile (touch) implementation
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    bool onTouchMove(cocos2d::Touch* touch, cocos2d::Event* unused_event);

    // Desktop (mouse) implementation
    void onMouseDown(cocos2d::Event* event);
    void onMouseMove(cocos2d::Event* event);

    // Contact listener
    //bool onContactBegin(cocos2d::PhysicsContact& contact);
    bool onContactSeparate(cocos2d::PhysicsContact& contact);

    CREATE_FUNC(MainScene);
};

#endif // __MAIN_SCENE_H__

#include "MainScene.h"
#include "math/CCMath.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    return MainScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MainScene::init()
{
    // --------------------------------------------------
    // super init first
    if (!Scene::init()){
        return false;
    }

    if (!Scene::initWithPhysics()) {
        return false;
    }

    _gameStarted = false;

    auto winSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Initialize Event Listeners
    // Mouse & Keyboard
    _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseMove = CC_CALLBACK_1(MainScene::onMouseMove, this);
    _mouseListener->onMouseDown = CC_CALLBACK_1(MainScene::onMouseDown, this);

    // Contact event listener
    _contactListener = EventListenerPhysicsContact::create();
    _contactListener->onContactSeparate = CC_CALLBACK_1(MainScene::onContactSeparate, this);
   
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_contactListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

    schedule(CC_SCHEDULE_SELECTOR(MainScene::tick), 0.3f);

    // set Background with black 
    auto backgroundColor = DrawNode::create();
    backgroundColor->drawSolidRect(origin, winSize, cocos2d::Color4F(0, 0, 0, 1.0));
    this->addChild(backgroundColor);

    _bgr = Background(this, winSize);
    _player = Player(this, winSize);
    _ball = Ball(this, winSize);
    _brickManager = BrickManager(this, winSize);
    
    // Collider Debug Mode Enable
    //getPhysicsWorld()->setDebugDrawMask(0xffff);

    return true;
}

void MainScene::gameWon() {

    _bgr.runGameWonAnimation();
    gameReset();
}

void MainScene::gameReset() {

    _gameStarted = false;

    _ball.MoveTo(_player.getPosition());
    _brickManager.ResetLevel();

    _bgr.setLabelsVisible(true, false);
    _bgr.resetScore();
}

void MainScene::gameLaunch() {
    
    _gameStarted = true;
    
    // Hide "Click to Start" Label
    _bgr.setLabelsVisible(false, false);

    // Launch ball
    _ball.Launch();
}

void MainScene::tick(float dt) {
    
    _ball.updatePosition();
}

void MainScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  
    ,do not use Director::getInstance()->end() as given above,instead trigger a custom event 
    created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

// ----------------------------------------------------------------------------------
// Touch events
// Android (mobile) implementation

bool MainScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event) {
    

    return true;
}

bool MainScene::onTouchMove(cocos2d::Touch* touch, cocos2d::Event* unused_event) {
    

    return true;
}

// -----------------------------------------------------------------------------------
// Desktop (windows) implementation

void MainScene::onMouseDown(cocos2d::Event* event) {

    if (!_gameStarted) {
        gameLaunch();
    }
}

void MainScene::onMouseMove(cocos2d::Event* event) {
    
    EventMouse* e = static_cast<EventMouse*>(event);
    _player.MoveTo(e->getLocation());

    if (!_gameStarted) {

        _ball.MoveTo(_player.getPosition());
    }
}

bool MainScene::onContactSeparate(cocos2d::PhysicsContact& contact) {
    
    auto bodyA = contact.getShapeA()->getBody();
    auto bodyB = contact.getShapeB()->getBody();

    // Collision cases
    // 1. Check category bitmask collision handling first 
    // (avoid walls colliding between them)
    if ((bodyA->getCategoryBitmask() & bodyB->getCategoryBitmask()) == 0) {
        return false;
    }

    int tagA = bodyA->getTag();
    int tagB = bodyB->getTag();
    PhysicsBody* ballBody;
    PhysicsBody* collidedBody;

    // 2. Check if ball is involved in the collision (tag 1)
    if (tagA == 1) {
        ballBody = bodyA;
        collidedBody = bodyB;
    }
    else if (tagB == 1) {
        ballBody = bodyB;
        collidedBody = bodyA;
    }
    else {
        return false;
    }
   
    // 3. collidedBody tags:
    // - 10: wall
    // - 11: player
    // - 12: brick
    // -  2: death

    if (collidedBody->getTag() == 10 || collidedBody->getTag() == 12) {
        // conservation of scalar speed
        float xVelocity = (ballBody->getVelocity().x >= 0) ? ballBody->getVelocity().x + 2 : ballBody->getVelocity().x - 2;
        float yVelocity = (ballBody->getVelocity().y >= 0) ? ballBody->getVelocity().y + 5 : ballBody->getVelocity().y - 6;
        auto ballBodyVelocity = Vec2(xVelocity, ballBody->getVelocity().y);
        ballBodyVelocity.normalize();
        ballBody->setVelocity(ballBodyVelocity * _ball.getScalarSpeed());

        if (collidedBody->getTag() == 12) {
            // brick collision subroutine
            auto brickPos = collidedBody->getPosition();
            int scoreEarned = _brickManager.ApplyCollisionToBrickAtPos(brickPos);

            // add score and check win condition
            _bgr.addScore(scoreEarned);
            if (_brickManager.CheckWinCond()) {
                gameWon();
            }
        }
    }
    else if (collidedBody->getTag() == 11) {
        // angular velocity tweak
        cocos2d::Vec2 hitPoint = _ball.getPosition();
        cocos2d::Vec2 paddlePos = _player.getPosition();

        float ballBodyVelocityX = ballBody->getVelocity().x;
        ballBody->setVelocity(cocos2d::Vec2::ZERO);

        float diff = paddlePos.x - hitPoint.x;
        Vec2 force;

        if (ballBodyVelocityX < 0) {
            force = Vec2(ballBodyVelocityX - fabs(diff * 2), _ball.getScalarSpeed());
        }
        else {
            force = Vec2(ballBodyVelocityX + fabs(diff * 2), _ball.getScalarSpeed());
        }

        ballBody->setVelocity(force);
        _bgr.setLabelsVisible(false, false);
    }
    else if (collidedBody->getTag() == 2) {
        // trigger game restart subroutine
        gameReset();
    }

    return true;
}
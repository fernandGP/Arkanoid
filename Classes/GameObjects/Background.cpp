#include "Background.h"

Background::Background() {}

Background::Background(cocos2d::Scene* parent, const cocos2d::Size& winSize) {
    
    // set _bgr image position
    _bgrSprite = cocos2d::Sprite::create("background.jpg");
    _bgrSprite->setPosition(cocos2d::Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
    parent->addChild(_bgrSprite);

    // initialize space constraints
    this->_winSize = winSize;
    this->_spriteSize = _bgrSprite->getContentSize();

    initWalls(parent);
    initLabels(parent);
    setLabelsVisible(true, false);
}

Background::~Background() {}

void Background::initWalls(cocos2d::Scene* parent) {
    
    // top wall
    // --------------------------------------------------------------------------------------------------------------------------------
    _topWall = cocos2d::DrawNode::create();
    auto originTW = cocos2d::Vec2(_winSize.width * 0.07f, _winSize.height * 0.89f);
    auto destinTW = cocos2d::Vec2(_winSize.width * 0.93f, (_winSize.height * 0.89f) + 5);
    _topWall->drawSolidRect(originTW, destinTW, cocos2d::Color4F(1, 1, 1, 0));

    auto topPB = cocos2d::PhysicsBody::createBox(cocos2d::Size(_winSize.width * 0.86f, 5), cocos2d::PhysicsMaterial(0.1f, 1.0f, 0.0f));
    topPB->setPositionOffset(cocos2d::Vec2(_winSize.width / 2, _winSize.height * 0.89f));
    topPB->setDynamic(false);
    topPB->setCategoryBitmask(0x01);
    topPB->setContactTestBitmask(0x01);
    topPB->setTag(10);

    _topWall->addComponent(topPB);
    parent->addChild(_topWall);

    // left wall
    // --------------------------------------------------------------------------------------------------------------------------------
    _leftWall = cocos2d::DrawNode::create();
    auto originLW = cocos2d::Vec2(_winSize.width * 0.07f - 5, _winSize.height * 0.89f);
    auto destinLW = cocos2d::Vec2(_winSize.width * 0.07f, 0.0f);
    _leftWall->drawSolidRect(originLW, destinLW, cocos2d::Color4F(1, 1, 1, 0));

    auto leftPB = cocos2d::PhysicsBody::createBox(cocos2d::Size(5, _winSize.height * 0.89f), cocos2d::PhysicsMaterial(0.1f, 1.0f, 0.0f));
    leftPB->setPositionOffset(cocos2d::Vec2(_winSize.width * 0.07f, _winSize.height * 0.89f / 2));
    leftPB->setDynamic(false);
    leftPB->setCategoryBitmask(0x02);
    leftPB->setContactTestBitmask(0x02);
    leftPB->setTag(10);

    _leftWall->addComponent(leftPB);
    parent->addChild(_leftWall);

    // right wall
    // --------------------------------------------------------------------------------------------------------------------------------
    _rightWall = cocos2d::DrawNode::create();
    auto originRW = cocos2d::Vec2(_winSize.width * 0.93f, _winSize.height * 0.89f);
    auto destinRW = cocos2d::Vec2(_winSize.width * 0.93f + 5, 0.0f);
    _rightWall->drawSolidRect(originRW, destinRW, cocos2d::Color4F(1, 1, 1, 0));

    auto rightPB = cocos2d::PhysicsBody::createBox(cocos2d::Size(5, _winSize.height * 0.89f), cocos2d::PhysicsMaterial(0.1f, 1.0f, 0.0f));
    rightPB->setPositionOffset(cocos2d::Vec2(_winSize.width * 0.93f, _winSize.height * 0.89f / 2));
    rightPB->setDynamic(false);
    rightPB->setCategoryBitmask(0x02);
    rightPB->setContactTestBitmask(0x02);
    rightPB->setTag(10);

    _rightWall->addComponent(rightPB);
    parent->addChild(_rightWall);

    // bottom wall (death trigger)
    // --------------------------------------------------------------------------------------------------------------------------------
    _bottomWall = cocos2d::DrawNode::create();
    auto originBW = cocos2d::Vec2(_winSize.width * 0.07f, _winSize.height * 0.05f);
    auto destinBW = cocos2d::Vec2(_winSize.width * 0.93f, 0);
    _bottomWall->drawSolidRect(originBW, destinBW, cocos2d::Color4F(1, 1, 1, 0));

    auto bottomPB = cocos2d::PhysicsBody::createBox(cocos2d::Size(_winSize.width * 0.86f, _winSize.height * 0.05f), cocos2d::PhysicsMaterial(0.1f, 1.0f, 0.0f));
    bottomPB->setPositionOffset(cocos2d::Vec2(_winSize.width / 2, _winSize.height * 0.05f / 2));
    bottomPB->setDynamic(false);
    bottomPB->setCategoryBitmask(0x01);
    bottomPB->setContactTestBitmask(0x01);
    bottomPB->setTag(2);

    _bottomWall->addComponent(bottomPB);
    parent->addChild(_bottomWall);
}

void Background::initLabels(cocos2d::Scene* parent) {

    _gamePausedLabel = cocos2d::Label::createWithTTF("Left click to start!", "fonts/DBXLNEW_.ttf", 32);
    _gamePausedLabel->setPosition(cocos2d::Vec2(_winSize.width / 2, _winSize.height / 2));
    
    _youWonLabel = cocos2d::Label::createWithTTF("You Win!", "fonts/DBXLNEW_.ttf", 32);
    _youWonLabel->setPosition(cocos2d::Vec2(_winSize.width / 2, _winSize.height / 2 - 64));
    
    currentScore = 0;
    _scoreLabel = cocos2d::Label::createWithTTF("Score: 0", "fonts/DBXLNEW_.ttf", 30);
    _scoreLabel->setPosition(cocos2d::Vec2(_winSize.width * 0.26f, _winSize.height * 0.92f));

    parent->addChild(_gamePausedLabel);
    parent->addChild(_youWonLabel);
    parent->addChild(_scoreLabel);
}

void Background::setLabelsVisible(bool gamePausedVisible, bool youWonVisible) {

    _gamePausedLabel->setVisible(gamePausedVisible);
    _youWonLabel->setVisible(youWonVisible);
}

void Background::resetScore() {
    
    currentScore = 0;
    _scoreLabel->setString("Score: 0");
}

void Background::addScore(int score) {
    
    std::stringstream ss;
    currentScore += score;

    ss << "Score: " << currentScore;
    _scoreLabel->setString(ss.str());
}

void Background::runGameWonAnimation() {

    auto callBackShowLabel = cocos2d::CallFunc::create([this]() {
        setLabelsVisible(false, true);
    });
    auto callBackHideLabel = cocos2d::CallFunc::create([this]() {
        setLabelsVisible(false, false);
    });
    auto actionWait = cocos2d::DelayTime::create(2.0f);
    _youWonLabel->runAction(cocos2d::Sequence::create(callBackShowLabel, actionWait, callBackHideLabel, nullptr));
}
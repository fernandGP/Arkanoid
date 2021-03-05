#include "Ball.h"

// --------------------------------------------------------
// constructor-destructor

Ball::Ball() {}

Ball::Ball(cocos2d::Scene* parent, const cocos2d::Size& winSize) {

    // set _ball init position
    const float SPRITE_SCALE_FACTOR = 0.35f;

    _sprite = cocos2d::Sprite::create("ball.png");
    auto pos = cocos2d::Vec2(winSize.width * 0.5f, winSize.height * 0.13f);
    _sprite->setPosition(pos);
    _sprite->setScale(SPRITE_SCALE_FACTOR);
    _position = pos;
    
    auto collider = cocos2d::PhysicsBody::createCircle(_sprite->getContentSize().width / 2);
    collider->setDynamic(true);
    collider->setGravityEnable(false);
    collider->setRotationEnable(false);
    collider->setCategoryBitmask(0xFFFFFFFF);
    collider->setContactTestBitmask(0xFFFFFFFF);
    collider->setTag(1);

    _sprite->addComponent(collider);
    parent->addChild(_sprite);

    // initialize space constraints
    this->_winSize = winSize;
    this->_spriteSize = _sprite->getContentSize();
}

Ball::~Ball() {
    
}

void Ball::MoveTo(const cocos2d::Vec2& pos) {

    // Moves towards point given player position (idle)
    auto fixedPos = cocos2d::Vec2(pos.x, _winSize.height * 0.13f);

    _position = fixedPos;
    _sprite->setPosition(fixedPos);

    _sprite->getPhysicsBody()->setVelocity(cocos2d::Vec2::ZERO);
}

void Ball::Launch() {
    
    cocos2d::Vec2 normalUp = cocos2d::Vec2::UNIT_Y;
    auto launchAmount = normalUp * SCALAR_SPEED;

    auto physicsBody = _sprite->getPhysicsBody();
    physicsBody->setVelocity(launchAmount);
}

void Ball::updatePosition() {
    _position = _sprite->getPhysicsBody()->getPosition();
}

cocos2d::Vec2 Ball::getPosition() {
    return _position;
}

float Ball::getScalarSpeed() { 
    return SCALAR_SPEED;  
}

void Ball::setScalarSpeed(float speed) { 
    SCALAR_SPEED = speed; 
}
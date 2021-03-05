#include "Player.h"

// --------------------------------------------------------
// constructor-destructor

Player::Player() {}

Player::Player(cocos2d::Scene* parent, const cocos2d::Size& winSize) {

    // set _player init position
    _sprite = cocos2d::Sprite::create("paddle.png");
    auto pos = cocos2d::Vec2(winSize.width * 0.5f, winSize.height * 0.1f);
    _sprite->setPosition(pos);
    _position = pos;

    auto collider = cocos2d::PhysicsBody::createBox(_sprite->getContentSize());
    collider->setDynamic(false);
    collider->setGravityEnable(false);
    collider->setRotationEnable(false);
    collider->setCategoryBitmask(0x04);
    collider->setContactTestBitmask(0x04);
    collider->setTag(11);

    _sprite->addComponent(collider);
    parent->addChild(_sprite);
    
    // initialize space constraints
    this->_winSize = winSize;
    this->_spriteSize = _sprite->getContentSize();
}

Player::~Player() {

}

// --------------------------------------------------------
// proper methods

void Player::MoveTo(const cocos2d::Vec2& pos) {
    
    float offsetX = _spriteSize.width / 2 + (_winSize.width * 0.07f);
    float posX = cocos2d::clampf(pos.x, offsetX, _winSize.width - offsetX);
    float posY = _winSize.height * 0.1f;

    auto fixedPos = cocos2d::Vec2(posX, posY);
    _position = fixedPos;
    _sprite->setPosition(fixedPos);
}

cocos2d::Vec2 Player::getPosition() {
    
    return _position;
}
#include "Brick.h"

static std::map<int, cocos2d::Color3B> _colors = {
        { -2, cocos2d::Color3B(100, 100, 100) },
        {  1, cocos2d::Color3B(255, 0, 0)},
        {  2, cocos2d::Color3B(0, 255, 0) }
};

Brick::Brick() {}

Brick::Brick(cocos2d::Scene* parent, float offsetX, float offsetY, int hp) {
    SetBrick(offsetX, offsetY, hp);

    auto collider = cocos2d::PhysicsBody::createBox(_sprite->getContentSize());
    collider->setDynamic(false);
    collider->setGravityEnable(false);
    collider->setRotationEnable(false);
    collider->setCategoryBitmask(0x04);
    collider->setContactTestBitmask(0x04);
    collider->setTag(12);

    _sprite->addComponent(collider);
    parent->addChild(_sprite);
}

Brick::~Brick() {
    //DestroySelf();
}

void Brick::SetPosition(float offsetX, float offsetY) {
    
    auto pos = cocos2d::Vec2(offsetX, offsetY);
    _sprite->setPosition(pos);
    _position = pos;
}

void Brick::SetHP(int hp) {
    
    this->hp = hp;
    _sprite->setColor(_colors[this->hp]);
}

void Brick::HideSelf() {

    //_sprite->getPhysicsBody()->getNode()->removeFromParentAndCleanup(true);
    _sprite->getPhysicsBody()->getNode()->setVisible(false);
    _sprite->getPhysicsBody()->setEnabled(false);
}

void Brick::ShowSelf() {

    _sprite->getPhysicsBody()->getNode()->setVisible(true);
    _sprite->getPhysicsBody()->setEnabled(true);
}

void Brick::SetBrick(float offsetX, float offsetY, int hp) {
    
    _sprite = cocos2d::Sprite::create("brick.png");
    _sprite->setScale(0.35f);
    this->_spriteSize = _sprite->getContentSize();
    
    SetPosition(offsetX, offsetY);
    SetHP(hp);
}

bool Brick::ApplyCollisionLogic(int& hitHp) {

    if (this->hp != -2) {

        hitHp = this->hp;

        this->hp--;

        if (this->hp <= 0) {
            HideSelf();
            return true;
        }
        else {
            // change sprite color
            _sprite->setColor(_colors[this->hp]);
            return false;
        }
    }

    return false;
}

void Brick::Dispose() {
    
    HideSelf();
}

void Brick::Show() {

    ShowSelf();
}

cocos2d::Vec2 Brick::getPosition() {
    
    return _position;
}
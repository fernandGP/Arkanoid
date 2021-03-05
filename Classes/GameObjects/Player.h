#pragma once

#include "cocos2d.h"

class Player
{
private:
	cocos2d::Size _winSize;
	cocos2d::Size _spriteSize;

	cocos2d::Sprite* _sprite;
	cocos2d::Vec2 _position;
public:
	Player();		// Default constructor necessary
	Player(cocos2d::Scene* parent, const cocos2d::Size& winSize);
	~Player();

	void MoveTo(const cocos2d::Vec2& pos);

	cocos2d::Vec2 getPosition();
};




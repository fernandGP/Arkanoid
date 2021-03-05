#pragma once

#include "cocos2d.h"

class Ball
{
private:
	float SCALAR_SPEED = 500;

	cocos2d::Size _winSize;
	cocos2d::Size _spriteSize;

	cocos2d::Sprite* _sprite;
	cocos2d::Vec2 _position;
public:
	Ball();		// Default constructor necessary
	Ball(cocos2d::Scene* parent, const cocos2d::Size& winSize);
	~Ball();

	void MoveTo(const cocos2d::Vec2& pos);
	void Launch();

	void updatePosition();
	cocos2d::Vec2 getPosition();
	float getScalarSpeed();
	void setScalarSpeed(float speed);
};